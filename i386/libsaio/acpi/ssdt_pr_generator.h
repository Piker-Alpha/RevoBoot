/*
 *	Original source code developed by DHP in May-June 2011.
 *
 *	Updates:
 *
 *			- First bug fixes / comments added by DHP.
 *			- CPU specs gathering / added by Jeroen.
 *			- Turbo range detection implemented by DHP.
 *			- P-State number limitation implemented by DHP.
 *			- Single turbo state support (TODO list) implemented by DHP.
 *			- Device (SBUS) injection added (required for AICPUPM) by DHP.
 *			- New global directive (AUTOMATIC_SSDT_PR_CREATION) added by DHP.
 *
 *	Credits:
 *			- Master Chief for his ongoing hands-on ACPI table lessons.
 *			- Intel's ACPICA project.
 *			- Mozodojo (for Scope/Package size calculations).
 *			- Master Chief for his idea to also inject device SBUS, to use a 
 *			  SSDT table instead of a modified DSDT (for new/initial setups)
 *			  and to simplify the global directives (just use 1 instead of 3).
 *
 *			- Thanks to flAked et all for helping me with tiny ssdt_pr.dsl
 *			- flAked, Jeroen and Pike (coders and testers).
 *
 *	Notes:
 *
 *			- We <i>only</i> want to support Sandy Bridge processors.
 *
 *			- Wrong UEFI settings will lead to:
 *				AppleIntelCPUPowerManagement: Turbo Ratio 19999 / 1BBBA (?)
 *				AppleIntelCPUPowerManagement: Turbo Ratio DEF0
 *				Note: This can be fixed by changing your UEFI settings.
 */


#include "cpu/proc_reg.h"

//------------------------------------------------------------------------------
// Adding two local directives, for backward compatibility, but we prefer that
// you use the new global directive AUTOMATIC_SSDT_PR_CREATION from now on.
//------------------------------------------------------------------------------

#if AUTOMATIC_SSDT_PR_CREATION & 1
 	#define AUTOMATIC_P_STATES_CREATION			1
#endif

#if AUTOMATIC_SSDT_PR_CREATION & 2
	#define AUTOMATIC_PROCESSOR_BLOCK_CREATION	1
#endif

#if AUTOMATIC_SSDT_PR_CREATION & 4
	#define AUTOMATIC_DEVICE_SBUS_CREATION		1
#endif


//==============================================================================

void generateSSDT_PR(void)
{
	//--------------------------------------------------------------------------
	// This directive enables you to use a custom name (CPUn) instead of the 
	// factory name (P00n) for processor definition blocks (think namespace).
	//--------------------------------------------------------------------------
	
#define _CPU_LABEL_REPLACEMENT	0x43, 0x50, 0x55, 0x30	// CPU0

	//--------------------------------------------------------------------------
	// Our pre-defined AML data blocks.

	uint8_t SSDT_PM_HEADER[] =
	{
		/* 0000 */	0x53, 0x53, 0x44, 0x54, 0x24, 0x00, 0x00, 0x00, 
		/* 0008 */	0x01, 0xFF, 0x41, 0x50, 0x50, 0x4C, 0x45, 0x20, 
		/* 0010 */	0x43, 0x70, 0x75, 0x50, 0x6D, 0x00, 0x00, 0x00, 
		/* 0018 */	0x00, 0x10, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C, 
		/* 0020 */	0x16, 0x03, 0x11, 0x20
	};
	
#if AUTOMATIC_DEVICE_SBUS_CREATION
	uint8_t SCOPE_PCI0_SBUS[] =						// Scope (\_SB.PCI0) { ... }
	{
		/* 0000 */	0x10, 0x46, 0x05, 0x5C, 0x2E, 0x5F, 0x53, 0x42, 
		/* 0008 */	0x5F, 0x50, 0x43, 0x49, 0x30, 0x5B, 0x82, 0x48, 
		/* 0010 */	0x04, 0x53, 0x42, 0x55, 0x53, 0x08, 0x5F, 0x41, 
		/* 0018 */	0x44, 0x52, 0x0C, 0x03, 0x00, 0x1F, 0x00, 0x5B, 
		/* 0020 */	0x82, 0x36, 0x42, 0x55, 0x53, 0x30, 0x08, 0x5F, 
		/* 0028 */	0x43, 0x49, 0x44, 0x0D, 0x73, 0x6D, 0x62, 0x75, 
		/* 0030 */	0x73, 0x00, 0x08, 0x5F, 0x41, 0x44, 0x52, 0x00, 
		/* 0038 */	0x5B, 0x82, 0x1D, 0x44, 0x56, 0x4C, 0x30, 0x08, 
		/* 0040 */	0x5F, 0x41, 0x44, 0x52, 0x0A, 0x57, 0x08, 0x5F, 
		/* 0048 */	0x43, 0x49, 0x44, 0x0D, 0x64, 0x69, 0x61, 0x67, 
		/* 0050 */	0x73, 0x76, 0x61, 0x75, 0x6C, 0x74, 0x00
	};
#endif

#if AUTOMATIC_PROCESSOR_BLOCK_CREATION
	uint8_t SCOPE_PR[] =							// Scope (\_PR_) { }
	{
		/* 0000 */	0x10, 0xFF, 0xFF, 0x5C, 0x5F, 0x50, 0x52, 0x5F

		/* 0000 * /	0x10, 0xFF, 0xFF, 0x5C, 0x2E, 0x5F, 0x50, 0x52
		/ *0008 * /	0x5F */
	};

	uint8_t PROCESSOR_DEF_BLOCK[] =
	{
		/* 0000 */	0x5B, 0x83, 0x0B, _CPU_LABEL_REPLACEMENT, 0xFF, 
		/* 0008 */	0x10, 0x04, 0x00, 0x00, 0x06
	};
	
#define INDEX_OF_PROCESSOR_CPU_ID	0x06			// Points to 0x30 in _CPU_LABEL_REPLACEMENT
#define INDEX_OF_PROCESSOR_NUMBER	0x07			// Points to 0x01
	
#endif	// AUTOMATIC_PROCESSOR_BLOCK_CREATION

#define INDEX_OF_SCOPE_LENGTH		0x01		// Points to 0xFF 0xFF in SCOPE_PR_CPU0

#if AUTOMATIC_P_STATES_CREATION

	uint8_t SCOPE_PR_CPU0[] =						// Scope (\_PR.CPU0) { }
	{
		/* 0000 */	0x10, 0xFF, 0xFF, 0x5C, 0x2E, 0x5F, 0x50, 0x52,
		/* 0008 */	0x5F, _CPU_LABEL_REPLACEMENT
	};

	uint8_t NAME_APSN[] =							// Name (APSN, 0xFF)
	{
		/* 0000 */	0x08, 0x41, 0x50, 0x53, 0x4E, 0x0A, 0xFF
	};

	#define INDEX_OF_APSN				0x06		// Points to 0xFF in NAME_APSN

	uint8_t NAME_APSS[] =							// Name (APSS, Package(0xFF) { })
	{
		/* 0000 */	0x08, 0x41, 0x50, 0x53, 0x53, 0x12, 0xFF, 0xFF, 
		/* 0008 */	0xFF
	};

	#define INDEX_OF_PACKAGE_LENGTH		0x06		// Points to 0xFF 0xFF in NAME_APSS
	#define INDEX_OF_P_STATES			0x08		// Points to 0xFF (first one) in NAME_APSS

	uint8_t PACKAGE_P_STATE[] =						// Package(0x06) { ... }
	{
		/* 0000 */	0x12, 0x14, 0x06, 0x0B, 0x00, 0x00, 0x0C, 0x00, 
		/* 0008 */	0x00, 0x00, 0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B, 
		/* 0010 */	0x00, 0x00, 0x0B, 0x00, 0x00
	};
	
	uint8_t METHOD_ACST[] =							// Method (ACST, Package(NN) { ... }
	{
		/* 0000 */	0x14, 0x49, 0x08, 0x41, 0x43, 0x53, 0x54, 0x00,
		/* 0008 */	0xA4, 0x12, 0x40, 0x08, 0x06, 0x01, 0x0A, 0x04, 
		/* 0010 */	0x12, 0x1D, 0x04, 0x11, 0x14, 0x0A, 0x11, 0x82, 
		/* 0018 */	0x0C, 0x00, 0x7F, 0x01, 0x02, 0x01, 0x00, 0x00, 
		/* 0020 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 
		/* 0028 */	0x01, 0x0A, 0x03, 0x0B, 0xE8, 0x03, 0x12, 0x1E, 
		/* 0030 */	0x04, 0x11, 0x14, 0x0A, 0x11, 0x82, 0x0C, 0x00, 
		/* 0038 */	0x7F, 0x01, 0x02, 0x03, 0x10, 0x00, 0x00, 0x00, 
		/* 0040 */	0x00, 0x00, 0x00, 0x00, 0x79, 0x00, 0x0A, 0x03, 
		/* 0048 */	0x0A, 0xCD, 0x0B, 0xF4, 0x01, 0x12, 0x1E, 0x04, 
		/* 0050 */	0x11, 0x14, 0x0A, 0x11, 0x82, 0x0C, 0x00, 0x7F, 
		/* 0058 */	0x01, 0x02, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00, 
		/* 0060 */	0x00, 0x00, 0x00, 0x79, 0x00, 0x0A, 0x06, 0x0A, 
		/* 0068 */	0xF5, 0x0B, 0x5E, 0x01, 0x12, 0x1D, 0x04, 0x11, 
		/* 0070 */	0x14, 0x0A, 0x11, 0x82, 0x0C, 0x00, 0x7F, 0x01, 
		/* 0078 */	0x02, 0x03, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
		/* 0080 */	0x00, 0x00, 0x79, 0x00, 0x0A, 0x07, 0x0A, 0xF5, 
		/* 0088 */	0x0A, 0xC8
	};
	
	uint8_t SCOPE_CPU_N[] =							// Scope (\_PR.CPUn) { ... }
	{
		/* 0000 */	0x10, 0x22, 0x5C, 0x2E, 0x5F, 0x50, 0x52, 0x5F, 
		/* 0008 */	_CPU_LABEL_REPLACEMENT, 0x14, 0x16, 0x41, 0x50, 
		/* 0010 */	0x53, 0x53, 0x00, 0xA4, 0x5C, 0x2F, 0x03, 0x5F, 
		/* 0018 */	0x50, 0x52, 0x5F, _CPU_LABEL_REPLACEMENT, 0x41, 
		/* 0020 */	0x50, 0x53, 0x53
	};

	#define INDEX_OF_CPU_NUMBER			0x0b		// Points to 0x30 in SCOPE_CPU_N (in second _CPU_LABEL_REPLACEMENT).

	typedef struct acpi_2_pss
	{
		char		ignored_1[4];					// type, length and package items.
		uint16_t	Frequency;
		char		ignored_2;						// var type
		uint32_t	Power;
		char		ignored_3[5];					// var type, latency, var type, latency, var type.
		uint16_t	Ratio;
		char		ignored_4;						// var type
		uint16_t	Status;
	} __attribute__((packed)) ACPI_PSS;

	//--------------------------------------------------------------------------
	// Initialization.

	uint8_t		i = 0;
	uint8_t		numberOfTurboStates	= 0;
	uint32_t	tdp = (gPlatform.CPU.TDP * 1000);	// See: i386/libsaio/cpu.c
#endif	// AUTOMATIC_P_STATES_CREATION

	struct acpi_2_ssdt * header = (struct acpi_2_ssdt *) SSDT_PM_HEADER;

#if AUTOMATIC_P_STATES_CREATION
	// When this is false then initTurboRatios (in cpu.c) didn't find any.
	if (gPlatform.CPU.NumberOfTurboRatios > 0)
	{
#if NUMBER_OF_TURBO_STATES > 4						// See: config/settings.h

		uint8_t numberOfCores = (gPlatform.CPU.NumCores - 1);
		// Get turbo range from multipliers.
		uint8_t	turboRange = (gPlatform.CPU.CoreTurboRatio[0] - gPlatform.CPU.CoreTurboRatio[numberOfCores]);

		// Do we have an extended range of P-States?
		if (turboRange > 3) // 3 means 4 P-States [0 - 3].
		{
			// Yes we do.
			numberOfTurboStates = (turboRange + 1);
		}
		else
		{
			// No. Use the default 4 for AICPUPM.
			numberOfTurboStates	= NUMBER_OF_TURBO_STATES;
		}
#else	// NUMBER_OF_TURBO_STATES > 4
		numberOfTurboStates	= gPlatform.CPU.NumberOfTurboRatios;
#endif	// NUMBER_OF_TURBO_STATES > 4

		//----------------------------------------------------------------------
		// Intel's 2nd generation i5 Desktop Processors (with Turbo 2.0)
		//
		// i5-2300  @2.8 - 3.1 GHz / TDP 95 W /  3 banks (each bank represents a 100 MHz speed jump)
		// i5-2310  @2.9 - 3.2 GHz / TDP 95 W /  3
		// i5-2390T @2.7 - 3.5 GHz / TDP 35 W /  8
		// i5-2400  @3.1 - 3.4 GHz / TDP 95 W /  3
		// i5-2400S @2.5 - 3.3 GHz / TDP 65 W /  8
		// i5-2405S @2.5 - 3.3 GHz / TDP 65 W /  8
		// i5-2500  @3.3 - 3.7 GHz / TDP 95 W /  4
		// i5-2500T @2.3 - 3.3 GHz / TDP 45 W / 10
		// i5-2500S @2.7 - 3.7 GHz / TDP 65 W / 10
		// i5-2500K @3.3 - 3.7 GHz / TDP 95 W /  4
		//	
		//----------------------------------------------------------------------
		// Intel's 2nd generation i7 Desktop Processors (with Turbo 2.0)
		//
		// i7-2600  @3.4 - 3.8 GHz / TDP 95 W /  4	banks
		// i7-2600S @2.8 - 3.8 GHz / TDP 65 W / 10
		// i7-2600K @3.4 - 3.8 GHz / TDP 95 W /  4
		//
		//----------------------------------------------------------------------
		// Intel's 2nd generation i5 Mobility Processors (with Turbo 2.0)
		//
		// i5-2410M @2.3 - 2.9 GHz / TDP 35 W / 6	banks
		// i5-2510E @2.5 - 3.1 GHz / TDP 35 W / 6
		// i5-2520M @2.5 - 3.2 GHz / TDP 35 W / 7
		// i5-2537M @1.4 - 2.3 GHz / TDP 17 W / 9
		// i5-2540M @2.6 - 3.3 GHz / TDP 35 W / 7
		// i5-2557M @1.7 - 2.7 GHz / TDP 17 W / 10
		//	
		//----------------------------------------------------------------------
		// Intel's 2nd generation i7 Mobility Processors (with Turbo 2.0)
		//
		// i7-2820QM @2.3 - 3.4 GHz / TDP 45 W /  3	banks
		// i7-2720QM @2.2 - 3.3 GHz / TDP 45 W / 11
		// i7-2710QE @2.1 - 3.0 GHz / TDP 45 W /  9
		// i7-2657M  @1.6 - 2.7 GHz / TDP 17 W / 11
		// i7-26349M @2.3 - 3.2 GHz / TDP 25 W /  9
		// i7-2635QM @2.0 - 2.9 GHz / TDP 45 W /  9
		// i7-2630QM @2.0 - 2.9 GHz / TDP 45 W /  9
		// i7-2629M  @2.1 - 3.0 GHz / TDP 25 W /  9
		// i7-2620M  @2.7 - 3.4 GHz / TDP 35 W /  7
		// i7-2617M  @1.5 - 2.6 GHz / TDP 17 W / 11
		// i7-2637M  @1.7 - 2.8 GHz / TDP 17 W / 11
		// i7-2677M  @1.8 - 2.9 GHz / TDP 17 W / 11
	}

	uint8_t numberOfPStates = (gPlatform.CPU.MaxBusRatio - gPlatform.CPU.MinBusRatio) + numberOfTurboStates + 1;

	// Limit number of P-States.
	if (numberOfPStates > MAX_NUMBER_OF_P_STATES)
	{
		numberOfPStates = MAX_NUMBER_OF_P_STATES;
	}

	//--------------------------------------------------------------------------
	// Calculate the buffer size for the AML code.
	
	uint32_t bufferSize =	header->Length + 
							sizeof(SCOPE_PR_CPU0) + 
							sizeof(NAME_APSN) + 
							sizeof(NAME_APSS) + 
							(sizeof(PACKAGE_P_STATE) * numberOfPStates) + 
							sizeof(METHOD_ACST) + 
							(sizeof(SCOPE_CPU_N) * (gPlatform.CPU.NumThreads - 1));
#else
	uint32_t bufferSize = header->Length;	
#endif	// #if AUTOMATIC_P_STATES_CREATION

#if AUTOMATIC_DEVICE_SBUS_CREATION					// See: config/settings.h

	bufferSize += sizeof(SCOPE_PCI0_SBUS);			// Increase buffer when required.

#endif	// AUTOMATIC_DEVICE_SBUS_CREATION

#if AUTOMATIC_PROCESSOR_BLOCK_CREATION				// See; config/settings.h

	// Increase buffer for the processor blocks, or we will run out of space.
	bufferSize += sizeof(SCOPE_PR) + (sizeof(PROCESSOR_DEF_BLOCK) * gPlatform.CPU.NumThreads);

#endif	// AUTOMATIC_PROCESSOR_BLOCK_CREATION

	uint16_t size = 0;
	void * buffer = malloc(bufferSize);
	void * bufferPointer = buffer;

	bzero(buffer, bufferSize);						// Clear buffer.

	//--------------------------------------------------------------------------
	// Copy SSDT header into the newly created buffer.
	
	bcopy(SSDT_PM_HEADER, buffer, sizeof(SSDT_PM_HEADER));
	bufferPointer += sizeof(SSDT_PM_HEADER);

#if AUTOMATIC_DEVICE_SBUS_CREATION					// See: config/settings.h
	//--------------------------------------------------------------------------
	// Here we add the following AML code:
	//
	//    Scope (\_SB.PCI0)
	//    {
	//        Device (SBUS)
	//        {
	//            Name (_ADR, 0x001F0003)
	//            Device (BUS0)
	//            {
	//                Name (_CID, "smbus")
	//                Name (_ADR, Zero)
	//                Device (DVL0)
	//                {
	//                    Name (_ADR, 0x57)
	//                    Name (_CID, "diagsvault")
	//                }
	//            }
	//        }
	//    }

	//--------------------------------------------------------------------------
	// Getting / setting the (static) Scope size.

	size = sizeof(SCOPE_PCI0_SBUS);

	// DHP: Jeroen please check this - we shouldn't need the next two lines.

#if AUTOMATIC_P_STATES_CREATION
	SCOPE_PCI0_SBUS[ INDEX_OF_SCOPE_LENGTH ]		= (0x40 | (size & 0x0f)) - 1;
	SCOPE_PCI0_SBUS[ INDEX_OF_SCOPE_LENGTH + 1 ]	= ((size >> 4) & 0xff);
#endif	// AUTOMATIC_P_STATES_CREATION

	bcopy(SCOPE_PCI0_SBUS, bufferPointer, sizeof(SCOPE_PCI0_SBUS));
	bufferPointer += sizeof(SCOPE_PCI0_SBUS);

#endif

#if AUTOMATIC_PROCESSOR_BLOCK_CREATION				// See: config/settings.h
	//--------------------------------------------------------------------------
	// Here we add the following AML code:
	//
	//	Scope (\_PR)
	//	{
	//        Processor (CPUn, 0x0n, 0x00000410, 0x06) {}
	//	      ...
	
	/*
	 * What we do here is to inject the Processor declaration blocks so that  
	 * you don't have to add them to your DSDT anymore. This way you can boot  
	 * a new Sandy Bridge setup, with AICPUPM loaded, without even having a 
	 * (modified) DSDT for it.
	 *
	 * Does this sound familiar to you: "<i>I have this and that board and I 
	 * wanted to know if your DSDT will work for my board</i>"?
	 *
	 * Right. Well. This concept might not be new. In fact it isn't, MC did this 
	 * for his P5K PRO in 2009 already, but it will be a lot more portable.
	 *
	 * Let's stop messing with zillions of different (Sandy Bridge) DSDT's and 
	 * just use a Secondary System Device Table instead, because this is exactly 
	 * why that was being developed... so let's use it to our advantage ;)
	 */

	//--------------------------------------------------------------------------
	// Taking care of the Scope size.
	
	size =	sizeof(SCOPE_PR) + (sizeof(PROCESSOR_DEF_BLOCK) * gPlatform.CPU.NumThreads) - 1;
	
	SCOPE_PR[ INDEX_OF_SCOPE_LENGTH ]		= (0x40 | (size & 0x0f)) - 1;
	SCOPE_PR[ INDEX_OF_SCOPE_LENGTH + 1 ]	= ((size >> 4) & 0xff);

	bcopy(SCOPE_PR, bufferPointer, sizeof(SCOPE_PR));
	bufferPointer += sizeof(SCOPE_PR);

	uint8_t	ctn = 0;

	for (ctn = 0; ctn < gPlatform.CPU.NumThreads; ctn++)
	{
		PROCESSOR_DEF_BLOCK[INDEX_OF_PROCESSOR_CPU_ID] = (0x30 + ctn); // Setting CPU name number.
		PROCESSOR_DEF_BLOCK[INDEX_OF_PROCESSOR_NUMBER] = (ctn + 1); // Setting CPU number.
		bcopy(PROCESSOR_DEF_BLOCK, bufferPointer, sizeof(PROCESSOR_DEF_BLOCK));
		bufferPointer += sizeof(PROCESSOR_DEF_BLOCK);
	}

#endif	// AUTOMATIC_PROCESSOR_BLOCK_CREATION

#if AUTOMATIC_P_STATES_CREATION
	//--------------------------------------------------------------------------
	// Taking care of the Scope size.
	
	size =	sizeof(SCOPE_PR_CPU0) + 
			sizeof(NAME_APSN) + 
			sizeof(NAME_APSS) + 
			(sizeof(PACKAGE_P_STATE) * numberOfPStates) +
			sizeof(METHOD_ACST);
	
	SCOPE_PR_CPU0[ INDEX_OF_SCOPE_LENGTH ]		= (0x40 | (size & 0x0f)) - 1;
	SCOPE_PR_CPU0[ INDEX_OF_SCOPE_LENGTH + 1 ]	= ((size >> 4) & 0xff);

	//--------------------------------------------------------------------------
	// Here we add the following AML code:
	//
	//	Scope (\_PR.CPU0)
	//	{
	//

	bcopy(SCOPE_PR_CPU0, bufferPointer, sizeof(SCOPE_PR_CPU0));
	bufferPointer += sizeof(SCOPE_PR_CPU0);
	
	//--------------------------------------------------------------------------
	// This step adds the following AML code:
	//
	//		Name (APSN, NN)

	// Setting NN in: Name (APSN, NN)
	NAME_APSN[ INDEX_OF_APSN ] = gPlatform.CPU.NumCores;

	bcopy(NAME_APSN, bufferPointer, sizeof(NAME_APSN));
	bufferPointer += sizeof(NAME_APSN);

	//--------------------------------------------------------------------------
	// Taking care of the Package size.

	size = (sizeof(PACKAGE_P_STATE) * numberOfPStates) + 4; // See note below!

	// Note: The explanation for the additional 4 bytes above is as follow:
	//
	// Scope/Package with content length + 1 <= 0x3f		= 1
	// Scope/Package with content length + 2 <= 0x3fff		= 2
	// Scope/Package with content length + 3 <= 0x3fffff	= 3
	// Scope/Package with content length + 3  > 0x3fffff	= 4;

	NAME_APSS[ INDEX_OF_PACKAGE_LENGTH ]		= (0x40 | (size & 0x0f)) - 1;
	NAME_APSS[ INDEX_OF_PACKAGE_LENGTH + 1 ]	= ((size >> 4) & 0xff);

	//--------------------------------------------------------------------------
	// This step adds the following AML code:
	//
	//		Name (APSS, Package (NN)
	//		{

	// Setting NN in: Name (APSS, Package (NN)
	NAME_APSS[ INDEX_OF_P_STATES ] = numberOfPStates;

	bcopy(NAME_APSS, bufferPointer, sizeof(NAME_APSS));
	bufferPointer += sizeof(NAME_APSS);

	//--------------------------------------------------------------------------
	// This step injects the AML code with the P-States:
	//
	//		Package (0x06) { 0xNNNN, 0xNNNN, 10, 10, 0xNN00, 0xNN00 }
	//		../..

	uint8_t	aPSSPackageCount = 0;

	uint16_t ratio, frequency, status;

	float m, power;

	struct acpi_2_pss * aPSS = (struct acpi_2_pss *) PACKAGE_P_STATE;

	uint8_t	maxRatio = gPlatform.CPU.MaxBusRatio;	// Max non-turbo frequency (see CPU specs).

	//--------------------------------------------------------------------------
	// First inject the Turbo P-States.

	for (i = 0; i < numberOfTurboStates; i++)
	{
		if (numberOfTurboStates	<= 4)
		{
			ratio = gPlatform.CPU.CoreTurboRatio[i];
		}
		else
		{
			// Having more than the usual four P-States means that we have to 
			// inject additional P-States (like a MacBookPro8,3) but in this 
			// case we can't just use <i>i</i> but (have to) do it like this:
			ratio = (gPlatform.CPU.CoreTurboRatio[0] - i);
		}
		
		// Check multiplier to prevent out-of-bound frequency - following BITS here. See also: biosbits.org
		if (ratio == 59 && numberOfTurboStates == 1)
		{
			frequency = (maxRatio * 100) + 1;		// Example: 3400 + 1 makes 3401 MHz (instead of 5900)
		}
		else
		{
			frequency = (ratio * 100);
		}

		aPSS->Power		= (uint32_t) tdp;			// Turbo States use TDP.

		//---------------- D O U B L E  V I S I O N  A L E R T! ----------------

		ratio			= status = (ratio << 8);

		aPSS->Frequency	= frequency;
		aPSS->Ratio		= ratio;
		aPSS->Status	= ratio;

		aPSSPackageCount++;

		bcopy(PACKAGE_P_STATE, bufferPointer, sizeof(PACKAGE_P_STATE));
		bufferPointer += sizeof(PACKAGE_P_STATE);

		//----------------------------------------------------------------------
	}

	i = gPlatform.CPU.MaxBusRatio;

	//--------------------------------------------------------------------------
	// And now the 'normal' P-States.

	for (; i >= gPlatform.CPU.MinBusRatio; i--)
	{
		// Do we need to limit the number of P-States?
		if ((i != gPlatform.CPU.MinBusRatio) && (aPSSPackageCount >= (MAX_NUMBER_OF_P_STATES - 1)))
		{
			continue;
		}

		ratio		= i;
		frequency	= (i * 100);

		m			= ((1.1 - ((maxRatio - ratio) * 0.00625)) / 1.1);
		power		= (((float)ratio / maxRatio) * (m * m) * tdp);

		aPSS->Power		= (uint32_t) power; // We are using a 32-bit value, even when a  
											// 16-bit value would be fine, but doing 
											// that would complicate things even more.

		//---------------- D O U B L E  V I S I O N  A L E R T! ----------------

		ratio			= status = (ratio << 8);

		aPSS->Frequency	= frequency;
		aPSS->Ratio		= ratio;
		aPSS->Status	= ratio;

		aPSSPackageCount++;

		bcopy(PACKAGE_P_STATE, bufferPointer, sizeof(PACKAGE_P_STATE));
		bufferPointer += sizeof(PACKAGE_P_STATE);

		//----------------------------------------------------------------------
	}

	//--------------------------------------------------------------------------
	// This step injects the following AML code:
	//
	//	Method (ACST, 0, NotSerialized)
	//	{
	//		Return (Package (0x06)
	//		{
	//			One,
	//			0x04,
	//			Package (0x04)
	//			{
	//				ResourceTemplate ()
	//				{
	//						Register (FFixedHW,
	//							0x01,
	//							0x02,
	//							0x0000000000000000,
	//							0x01,
	//							)
	//				},
	//
	//				One,
	//				0x03,
	//				0x03E8
	//			},
	//
	//			Package (0x04)
	//			{	
	//				ResourceTemplate ()
	//				{
	//						Register (FFixedHW,
	//							0x01,
	//							0x02,
	//							0x0000000000000010,
	//							0x03,
	//							)
	//				},
	//
	//				0x03,
	//				0xCD, 
	//				0x01F4
	//			},
	//
	//			Package (0x04)
	//			{	
	//				ResourceTemplate ()
	//				{
	//						Register (FFixedHW,
	//							0x01,
	//							0x02,
	//							0x0000000000000020,
	//							0x03,
	//							)
	//				},
	//
	//				0x06,
	//				0xF5, 
	//				0x015E
	//			},
	//
	//			Package (0x04)
	//			{	
	//				ResourceTemplate ()
	//				{
	//						Register (FFixedHW,
	//							0x01,
	//							0x02,
	//							0x0000000000000030,
	//							0x03,
	//							)
	//				},
	//
	//				0x07,
	//				0xF5, 
	//				0xC8
	//			},
	//		})
	//	}

	bcopy(METHOD_ACST, bufferPointer, sizeof(METHOD_ACST));
	bufferPointer += sizeof(METHOD_ACST);

	//--------------------------------------------------------------------------
	// This step adds the following AML code - one for each logical core:
	//
	//	Scope (\_PR.CPUn)
	//	{
	//		Method (APSS, 0, NotSerialized)
	//		{
	//			Return (\_PR.CPU0.APSS)
	//		}
	//	}

	for (i = 1; i < gPlatform.CPU.NumThreads; i++)
	{
		SCOPE_CPU_N[INDEX_OF_CPU_NUMBER] = (0x30 + i);		// Setting CPU number.
		bcopy(SCOPE_CPU_N, bufferPointer, sizeof(SCOPE_CPU_N));
		bufferPointer += sizeof(SCOPE_CPU_N);
	}

#endif	// AUTOMATIC_P_STATES_CREATION

	//--------------------------------------------------------------------------
	// Here we generate a new checksum.
	// Note:	The length and checksum should be the same as a normal ssdt_pr.aml
	//			but might vary due to (lack of) optimization.

	header = (struct acpi_2_ssdt *) buffer;
	
	header->Length		= bufferSize;
	header->Checksum	= 0;
	header->Checksum	= 256 - checksum8(buffer, header->Length);

	//--------------------------------------------------------------------------
	// Updating customTables with the required data.

	customTables[SSDT_PR].table			= (void *)(uint32_t)buffer;
	customTables[SSDT_PR].tableLength	= bufferSize;
	customTables[SSDT_PR].loaded		= true;		// Simulate a file load - to let it call free()
}
