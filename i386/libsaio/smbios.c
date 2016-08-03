/*
 * Copyright (c) 2009 by Master Chief.
 *
 * Updates:
 *
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- Refactorized by DHP in 2011.
 *			- Get static EFI data (optional) from /Extra/EFI/[MacModelNN].bin (PikerAlpha, October 2012).
 *			- Set newEPS->dmi.tableLength to fileSize when model specific data is loaded (PikerAlpha, November 2012).
 *			- Get number of table structures from loaded model specific SMBIOS data (PikerAlpha, November 2012).
 *			- Set newEPS->maxStructureSize when SET_MAX_STRUCTURE_LENGTH is set (PikerAlpha, November 2012).
 *			- Check/correct errors in RevoBoot/i386/config/SMBIOS/[data-template/MacModelNN].h (PikerAlpha, November 2012).
 */

#include "platform.h"
#include "smbios/smbios.h"

#if USE_STATIC_SMBIOS_DATA
//==============================================================================

void setupSMBIOS(void)
{
	_SMBIOS_DEBUG_DUMP("Entering setupSMBIOS(static)\n");

	// Allocate 1 page of kernel memory (sufficient for a stripped SMBIOS table).
    void * kernelMemory = (void *)AllocateKernelMemory(4096);
	
	// Setup a new Entry Point Structure at the beginning of the newly allocated memory page.
	struct SMBEntryPoint * newEPS = (struct SMBEntryPoint *) kernelMemory;

	// Include additional/conditional code snippet.
	#include "smbios/static_data.h"

    newEPS->anchor[0]			= 0x5f;		// _
    newEPS->anchor[1]			= 0x53;		// S
    newEPS->anchor[2]			= 0x4d;		// M
    newEPS->anchor[3]			= 0x5f;		// _
    newEPS->checksum			= 0;
    newEPS->entryPointLength	= 0x1f;		// sizeof(* newEPS)
    newEPS->majorVersion		= 2;
    newEPS->minorVersion		= 6;
	newEPS->maxStructureSize	= STATIC_SMBIOS_SM_MAX_STRUCTURE_SIZE;	// Defined in RevoBoot/i386/config/SMBIOS/data-template.h
    newEPS->entryPointRevision	= 0;
    
    newEPS->formattedArea[0]	= 0;
    newEPS->formattedArea[1]	= 0;
    newEPS->formattedArea[2]	= 0;
    newEPS->formattedArea[3]	= 0;
    newEPS->formattedArea[4]	= 0;
    
    newEPS->dmi.anchor[0]		= 0x5f;		// _
    newEPS->dmi.anchor[1]		= 0x44;		// D
    newEPS->dmi.anchor[2]		= 0x4d;		// M
    newEPS->dmi.anchor[3]		= 0x49;		// I
    newEPS->dmi.anchor[4]		= 0x5f;		// _
    newEPS->dmi.checksum		= 0;
    newEPS->dmi.tableLength		= tableLength;
    newEPS->dmi.tableAddress	= (uint32_t) (kernelMemory + sizeof(struct SMBEntryPoint)); 
    newEPS->dmi.bcdRevision		= 0x24;
	newEPS->dmi.structureCount	= STATIC_SMBIOS_DMI_STRUCTURE_COUNT;	// Defined in RevoBoot/i386/config/SMBIOS/[data-template/MacModelNN].h

	// Safety measure to protect people from doing something that breaks the boot process.
	// #define FORCED_CHECK ((STATIC_SMBIOS_DMI_STRUCTURE_COUNT == 0) || (SET_MAX_STRUCTURE_LENGTH && (STATIC_SMBIOS_SM_MAX_STRUCTURE_SIZE == 0)))
	#define FORCED_CHECK	((STATIC_SMBIOS_DMI_STRUCTURE_COUNT == 0) || SET_MAX_STRUCTURE_LENGTH)

#if (LOAD_MODEL_SPECIFIC_SMBIOS_DATA || FORCED_CHECK)
	/*
	 * Get number of SMBIOS table structures from the loaded model specific SMBIOS data, or
	 * when we have 0 values in: RevoBoot/i386/config/SMBIOS/[data-template/MacModelNN].bin
	 */
	if ((fileSize > 0) || FORCED_CHECK)
	{
		UInt16 structureCount = 0;

		char * structurePtr = (char *)newEPS->dmi.tableAddress;
		char * structureEnd = (structurePtr + newEPS->dmi.tableLength);
	
		while (structureEnd > (structurePtr + sizeof(SMBStructHeader)))
		{
			struct SMBStructHeader * header = (struct SMBStructHeader *) structurePtr;
			SMBByte currentStructureType = header->type;

			if (currentStructureType == kSMBTypeMemoryDevice)
			{
				UInt64 memorySize = 0;
#if STATIC_RAM_OVERRIDE_SIZE
				memorySize = getRAMSize();
#else
				memorySize = ((SMBMemoryDevice *)header)->memorySize;
#endif
				if (memorySize > 0 && memorySize < 0xffff)
				{
					gPlatform.RAM.MemorySize += (memorySize << ((memorySize & 0x8000) ? 10 : 20));
				}
			}

#if SET_MAX_STRUCTURE_LENGTH
			char * stringsPtr = structurePtr;
#endif
			// Skip the formatted area of the structure.
			structurePtr += header->length;

			/*
			 * Skip the unformatted structure area at the end (strings).
			 * Using word comparison instead of checking two bytes (thanks to Kabyl).
			 */
			for (; ((uint16_t *)structurePtr)[0] != 0; structurePtr++);

			// Adjust pointer after locating the double 0 terminator.
			structurePtr += 2;

			// Update structure counter.
			structureCount++;
	
			_SMBIOS_DEBUG_DUMP("structureCount: %d\n", structureCount);

#if SET_MAX_STRUCTURE_LENGTH
			UInt16 maxStructureSize = (structurePtr - stringsPtr);

			if (newEPS->maxStructureSize < maxStructureSize)
			{
				newEPS->maxStructureSize = maxStructureSize;
			}
			
			_SMBIOS_DEBUG_DUMP("Structure (%d) length: %3d bytes.\n", currentStructureType, maxStructureSize);
			_SMBIOS_DEBUG_SLEEP(1);
#endif	// #if SET_MAX_STRUCTURE_LENGTH
		}
		// Uodate number of structures (boot hang without the correct value).
		newEPS->dmi.structureCount = structureCount;
	}
#endif	// #if (LOAD_MODEL_SPECIFIC_SMBIOS_DATA || FORCED_CHECK)
	/*
	 * newEPS->dmi.tableLength represents the length of the static data, or the size
	 * of the model specific SMBIOS data file from: /Extra/SMBIOS/MacModelNN.bin
	 */
	_SMBIOS_DEBUG_DUMP("newEPS->dmi.structureCount: %d\nnewEPS.dmi.tableLength: %d\n", newEPS->dmi.structureCount, newEPS->dmi.tableLength);

    // Calculate checksums
    newEPS->dmi.checksum		= checksum8(&newEPS->dmi, sizeof(newEPS->dmi));
    newEPS->checksum			= checksum8(newEPS, sizeof(* newEPS));

	// Used to update the EFI Configuration Table (in efi.c) which is
	// what AppleSMBIOS.kext reads to setup the SMBIOS table for OS X.
	gPlatform.SMBIOS.BaseAddress = (uint32_t) newEPS;

	_SMBIOS_DEBUG_DUMP("New SMBIOS replacement setup.\n");
	_SMBIOS_DEBUG_SLEEP(5);
}
#else // #if USE_STATIC_SMBIOS_DATA

#include "smbios/dynamic_data.h"

#endif // #if USE_STATIC_SMBIOS_DATA
