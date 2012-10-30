/*
 * Copyright (c) 2009 by Master Chief.
 *
 * Updates:
 *
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- Refactorized by DHP in 2011.
 *			- Get static EFI data (optional) from /Extra/EFI/[MacModelNN].bin (PikerAlpha, October 2012).
 */

#include "platform.h"

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
    newEPS->minorVersion		= 4;
    newEPS->maxStructureSize	= STATIC_SMBIOS_SM_MAX_STRUCTURE_SIZE; // Defined in: config/smbios/data.h
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
    newEPS->dmi.structureCount	= STATIC_SMBIOS_DMI_STRUCTURE_COUNT; // Defined in: config/smbios/data.h
    newEPS->dmi.bcdRevision		= 0x24;
    
    // Take care of possible checksum errors
    newEPS->dmi.checksum		= 256 - checksum8(&newEPS->dmi, sizeof(newEPS->dmi));
    newEPS->checksum			= 256 - checksum8(newEPS, sizeof(* newEPS));

	_SMBIOS_DEBUG_DUMP("newEPS->dmi.structureCount: %d - tableLength: %d\n", newEPS->dmi.structureCount, newEPS->dmi.tableLength);

	// Used to update the EFI Configuration Table (in efi.c) which is 
	// what AppleSMBIOS.kext reads to setup the SMBIOS table for OS X.
	gPlatform.SMBIOS.BaseAddress = (uint32_t) newEPS;

	_SMBIOS_DEBUG_DUMP("New SMBIOS replacement setup.\n");
	_SMBIOS_DEBUG_SLEEP(5);
}
#else

#include "smbios/dynamic_data.h"

#endif // #if USE_STATIC_SMBIOS_DATA
