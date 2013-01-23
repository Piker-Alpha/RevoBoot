/*
 * Copyright (c) 2009 by Master Chief.
 *
 * Refactored (static and dynamic CPU data gathering) by DHP in 2010.
 * Expanded (requestMaxTurbo added) by DHP in May 2011.
 * Simplified by DHP in Juni 2011 (thanks to MC and flAked for the idea).
 * Bug fix: gPlatform.CPU.minBusRatio/maxBusRatio added by Jeroen (Juni 2011).
 * Call to checkFlexRatioMSR added by DHP (August 2011).
 */

#ifndef __LIBSAIO_CPU_STATIC_CPU_DATA_H
#define __LIBSAIO_CPU_STATIC_CPU_DATA_H

//==============================================================================

void initCPUStruct(void)
{
	gPlatform.CPU.Vendor		= CPU_VENDOR_ID;			// Used in ACPI/patcher.h

	gPlatform.CPU.Type			= STATIC_CPU_Type;			// Used in SMBIOS/dynamic_data.h and ACPI/SSDT_PR
															// Affects CPU type in 'About This Mac' and System Profiler.

	gPlatform.CPU.NumCores		= STATIC_CPU_NumCores;		// machdep.cpu.cores_per_package - used in: ACPI/ssdt_pm_generator.h
	gPlatform.CPU.NumThreads	= STATIC_CPU_NumThreads;	// machdep.cpu.logical_per_package - used in: ACPI/ssdt_pm_generator.h

	gPlatform.CPU.FSBFrequency	= STATIC_CPU_FSBFrequency;	// hw.busfrequency - very important to get this right!

	gPlatform.CPU.QPISpeed		= STATIC_CPU_QPISpeed;		// QuickPath Interconnect - used in: libsaio/SMBIOS/dynamic_data.h

#if INTEL_CORE_TECHNOLOGY
	uint64_t msr = rdmsr64(MSR_PLATFORM_INFO);				// Jeroen: Copied over from i386/libsaio/cpu/Intel/dynamic_data.h

	gPlatform.CPU.MinBusRatio = ((msr >> 40) & 0xff);		// Example: 16 with Intel i7-2600 processor.

	gPlatform.CPU.MaxBusRatio = ((msr >> 8) & 0xff);		// Example: 34 with Intel i7-2600 processor and 33 with Intel i7-2500.

	// Is Turbo Mode Enabled?
	if (!((rdmsr64(IA32_MISC_ENABLES) >> 32) & 0x40))		// Jeroen: Using the same check here as we do in Intel/dynamic_data.h
	{
		requestMaxTurbo(gPlatform.CPU.MaxBusRatio);
	}

	checkFlexRatioMSR();
#endif
}

#endif /* !__LIBSAIO_CPU_STATIC_CPU_DATA_H */