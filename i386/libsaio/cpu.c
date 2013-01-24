/*
 * Copyright (c) 2009 by Master Chief.
 *
 * Updates:
 *			- Refactoring for Revolution done by DHP in 2010/2011.
 *			- Expanded (requestMaxTurbo added) by DHP in May 2011.
 *			- Simplified by DHP in Juni 2011 (thanks to MC and flAked for the idea).
 *			- Code copied from Intel/dynamic_data.h  by DHP in juni 2011.
 *			- New compiler directive (BOOT_TURBO_RATIO) added by Jeroen (June 2011).
 *			- Function checkFlexRatioMSR added by DHP (August 2011).
 *			- Fixed error: use of undeclared identifier 'NUMBER_OF_TURBO_STATES' (Pike, January 2013).
 */


#include "platform.h"
#include "cpu/cpuid.h"
#include "cpu/proc_reg.h"

#if INTEL_CORE_TECHNOLOGY

#if AUTOMATIC_SSDT_PR_CREATION || DEBUG_CPU_TDP
//==============================================================================
// Called from dynamic_data.h and i386/libsaio/ACPI/ssdt_pr_generator.h

uint8_t getTDP(void)
{
	uint8_t		powerUnit = bitfield32(rdmsr64(MSR_RAPL_POWER_UNIT), 3, 0);
	uint32_t	powerLimit = bitfield32(rdmsr64(MSR_PKG_RAPL_POWER_LIMIT), 14, 0);

	uint8_t		tdp = (powerLimit / (1 << powerUnit));

	if (tdp == 255)
	{
		powerLimit = bitfield32(rdmsr64(MSR_PKG_POWER_INFO), 14, 0);
		tdp = (powerLimit / (1 << powerUnit));
	}

#if DEBUG_CPU_TDP
	printf("RAPL Power Limit : %d\n", powerLimit);	// 0x7F8 / 2040
	printf("RAPL Power Unit  : %d\n", powerUnit);	// 3 (1/8 Watt)
	printf("RAPL Package TDP : %d\n", tdp);			// 255
	printf("RAPL Power Limit : %d\n", powerLimit);
	printf("CPU IA (Core) TDP: %d\n", tdp);			// 95
	sleep(5);
#endif

	return tdp;
}
#endif


//==============================================================================

void initTurboRatios()
{
	// Get turbo ratio(s).
	uint64_t msr = rdmsr64(MSR_TURBO_RATIO_LIMIT);
	
#if AUTOMATIC_SSDT_PR_CREATION || DEBUG_CPU_TURBO_RATIOS
	// All CPU's have at least two cores (think mobility CPU here).
	gPlatform.CPU.CoreTurboRatio[0] = bitfield32(msr, 7, 0);
	gPlatform.CPU.CoreTurboRatio[1] = bitfield32(msr, 15, 8);
	
	// Additionally for quad and six core CPU's.
	if (gPlatform.CPU.NumCores >= 4)	// Up to 8 threads.
	{
		gPlatform.CPU.CoreTurboRatio[2] = bitfield32(msr, 23, 16);
		gPlatform.CPU.CoreTurboRatio[3] = bitfield32(msr, 31, 24);

#if STATIC_CPU_NumCores >= 6			// 12 threads.
		// For the lucky few with a six core Gulftown CPU.
		//
		// bitfield32() supports 32 bit values only and thus we 
		// have to do it a little different here (bit shifting).
		gPlatform.CPU.CoreTurboRatio[4] = ((msr >> 32) & 0xff);
		gPlatform.CPU.CoreTurboRatio[5] = ((msr >> 40) & 0xff);
#endif

#if STATIC_CPU_NumCores == 8			// 16 threads.
		// Westmere-EX support (E7-2820/E7-2830).
		gPlatform.CPU.CoreTurboRatio[6] = ((msr >> 48) & 0xff);
		gPlatform.CPU.CoreTurboRatio[7] = ((msr >> 56) & 0xff);
#endif
	}

	// Jeroen:	This code snippet was copied from ACPI/ssdt_pr_generator.h 
	//			so that the call to initTurboRatios from Intel/dynamic_data.h 
	//			or Intel/static_data.h ready the data for generateSSDT_PR.
	//
	// Note:	Let's use this to our advantage for DEBUG_CPU_TURBO_RATIOS!

	// We need to have something to work with so check for it, and the 
	// way we do that (trying to be smart) supports any number of cores.

	uint8_t	numberOfCores = gPlatform.CPU.NumCores;

	if (gPlatform.CPU.CoreTurboRatio[0] != 0)
	{
		uint8_t i, duplicatedRatios = 0;

		// Simple check to see if all ratios are the same.
		for (i = 0; i < numberOfCores; i++)
		{
			// First check for duplicates (against the next value).
			if (gPlatform.CPU.CoreTurboRatio[i] != gPlatform.CPU.CoreTurboRatio[i + 1])
			{
				break;
			}

			duplicatedRatios++;
		}

#ifdef NUMBER_OF_TURBO_STATES
		uint8_t numberOfTurboStates = NUMBER_OF_TURBO_STATES;
#else
		uint8_t numberOfTurboStates = numberOfCores;
#endif
		// Should we add only one turbo P-State?
		if (duplicatedRatios == 0)
		{
			gPlatform.CPU.NumberOfTurboRatios = numberOfTurboStates;	// Default for AICPUPM.
		}
		else // Meaning that we found duplicated ratios.
		{
			// Do we need to inject one Turbo P-State only?
			if (duplicatedRatios == numberOfTurboStates)
			{
				// Yes. Wipe the rest (keeping the one with the highest multiplier).
				for (i = 1; i < numberOfCores; i++)		// i set to 1 to preserve the first one.
				{
					gPlatform.CPU.CoreTurboRatio[i] = 0;
				}
			}
			else
			{
				// There are only 3 Turbo ratios on the i5-2400, and people 
				// may make mistakes, or want to use duplicated ratios, but  
				// we'll have to ignore that for now because I have no idea 
				// what we should be doing in this case.
			}
		}

		// Jeroen: Used in ACPI/ssdt_pr_generator.h / for DEBUG_CPU_TURBO_RATIOS.
		gPlatform.CPU.NumberOfTurboRatios = (numberOfTurboStates - duplicatedRatios);
		
		/* if (duplicatedRatios == 4)
		{
			wrmsr64(MSR_TURBO_RATIO_LIMIT, 0x28282828);
		
			// Reinitialize the multipliers.
			for (i = 0; i < numberOfCores; i++)
			{
				gPlatform.CPU.CoreTurboRatio[i] = 0x28;
			}
		} */
		
		// _CPU_DEBUG_DUMP("Turbo Ratios: %d (%d dups)\n", gPlatform.CPU.NumberOfTurboRatios, duplicatedRatios);
	}
#else	// AUTOMATIC_SSDT_PR_CREATION || DEBUG_CPU_TURBO_RATIOS
	gPlatform.CPU.CoreTurboRatio[0] = bitfield32(msr, 7, 0);
#endif	// AUTOMATIC_SSDT_PR_CREATION || DEBUG_CPU_TURBO_RATIOS
}


//==============================================================================

void requestMaxTurbo(uint8_t aMaxMultiplier)
{
	// Testing with MSRDumper.kext confirmed that the CPU isn't always running at top speed,
	// up to 5.9 GHz on a good i7-2600K, which is why we check for it here (a quicker boot).
	
	initTurboRatios();

	// Is the maximum turbo ratio reached already?
	if (gPlatform.CPU.CoreTurboRatio[0] > aMaxMultiplier)	// 0x26 (3.8GHz) > 0x22 (3.4GHz)
	{
		// No. Request (maximum/limited) turbo boost (in case EIST is disabled).
#if BOOT_TURBO_RATIO
		wrmsr64(MSR_IA32_PERF_CONTROL, BOOT_TURBO_RATIO);

		// Note: The above compiler directive was added, on request, to trigger the required 
		//		 boot turbo multiplier (SB 'iMac' running at 5.4+ GHz did not want to boot).
#else
		wrmsr64(MSR_IA32_PERF_CONTROL, gPlatform.CPU.CoreTurboRatio[0] << 8);
#endif
		_CPU_DEBUG_DUMP("Max/limited (%x) turbo boost requested.\n", rdmsr64(MSR_IA32_PERF_CONTROL));
	}
}


//==============================================================================

void checkFlexRatioMSR(void)
{
	// The processor’s maximum non-turbo core frequency is configured during power-on reset 
	// by using its manufacturing default value. This value is the highest non-turbo core 
	// multiplier at which the processor can operate. If lower maximum speeds are desired, 
	// the appropriate ratio can be configured using the FLEX_RATIO MSR. 
	
	uint64_t msr = rdmsr64(MSR_FLEX_RATIO);
	
	if (msr & bit(16)) // Flex ratio enabled?
	{
		uint8_t flexRatio = ((msr >> 8) & 0xff);
		
		// Sanity checks.
		if (flexRatio < gPlatform.CPU.MinBusRatio || flexRatio > gPlatform.CPU.MaxBusRatio)
		{
			// Invalid flex ratio found. Disable flex ratio by clearing bit 16.
			wrmsr64(MSR_FLEX_RATIO, (msr & 0xFFFFFFFFFFFEFFFFULL));
		}
		else
		{
			// Overriding the maximum non-turbo core frequency (ratio) with the new value.
			gPlatform.CPU.MaxBusRatio = flexRatio;
		}
	}
}
#endif

#if USE_STATIC_CPU_DATA

	#if CPU_VENDOR_ID == CPU_VENDOR_INTEL
		#include "cpu/intel/static_data.h"
	#else
		#include "cpu/amd/static_data.h"
	#endif

#else

	#if CPU_VENDOR_ID == CPU_VENDOR_INTEL
		#include "cpu/intel/dynamic_data.h"
	#else
		#include "cpu/amd/dynamic_data.h"
	#endif

#endif

