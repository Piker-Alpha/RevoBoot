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

int useStaticSMBIOSData(void * aMemoryAddress)
{
	// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
	#include STRING(SMBIOS_DATA_FILE)

	static uint32_t SMBIOS_Table[] =
	{
		// Replaced with data from: RevoBoot/i386/config/SMBIOS/[data-template/MacModelNN].h
		STATIC_SMBIOS_DATA
	};

	_SMBIOS_DEBUG_DUMP("Using statically linked SMBIOS data\n");

	int tableLength = sizeof(SMBIOS_Table);

	// Copy the static SMBIOS data into the newly allocated memory page. Right after the new EPS.
	memcpy(aMemoryAddress, SMBIOS_Table, tableLength);
	
	return tableLength;
}


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
	newEPS->dmi.structureCount	= STATIC_SMBIOS_DMI_STRUCTURE_COUNT;	// Defined in RevoBoot/i386/config/SMBIOS/data-template.h

#if LOAD_MODEL_SPECIFIC_SMBIOS_DATA
	/*
	 * This is nothing more than a mere stop gap solution, since using the factory values here, instead of walking over 
	 * staticSMBIOSData to get them, may hang the kernel at boot time (will be fixed in a next update of RevoBoot).
	 */
	if (fileSize > 0)
	{
		newEPS->maxStructureSize	= factoryEPS->maxStructureSize;		// Defined in RevoBoot/i386/libsaio/SMBIOS/static_data.h
		newEPS->dmi.structureCount	= factoryEPS->dmi.structureCount;	// Defined in RevoBoot/i386/libsaio/SMBIOS/static_data.h
		
		_SMBIOS_DEBUG_DUMP("factoryEPS->maxStructureSize  : %d\n", factoryEPS->maxStructureSize);
		_SMBIOS_DEBUG_DUMP("factoryEPS->dmi.structureCount: %d\n", factoryEPS->dmi.structureCount);
		_SMBIOS_DEBUG_SLEEP(1);
	}
#endif

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
