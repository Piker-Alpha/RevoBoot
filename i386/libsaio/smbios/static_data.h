/*
 * Copyright 2009 by Master Chief.
 *
 * Updates:
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- New path for static EFI data (PikerAlpha, October 2012).
 *			- Optionally check /Extra/SMBIOS/[MacModelNN.bin] for static SMBIOS data (PikerAlpha, October 2012).
 *			- Get maxStructureSize/structureCount from factory EPS (PikerAlpha, October 2012).
 *			- Cleanups/simplification of code (Pike, April 2013).
 *			- iMessage fix for static SMBIOS data / init gPlatform.UUID from static data (Pike, April 2013).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 */

#ifndef __LIBSAIO_SMBIOS_STATIC_DATA_H
#define __LIBSAIO_SMBIOS_STATIC_DATA_H

#include "essentials.h"

int offset		= 0;
int tableLength	= 0;

long fileSize	= 0L;

void * staticSMBIOSData = (void *)kLoadAddr;

#if LOAD_MODEL_SPECIFIC_SMBIOS_DATA
	char dirSpec[32] = "";

	sprintf(dirSpec, "/Extra/SMBIOS/%s.bin", COMMA_STRIPPED_MODEL_ID);
	_SMBIOS_DEBUG_DUMP("Loading: %s", dirSpec);
	fileSize = loadBinaryData(dirSpec, &staticSMBIOSData);

	if (fileSize > 0)
	{
		tableLength = fileSize;
		_SMBIOS_DEBUG_DUMP("\n");
	}
	else // File not found. Use static data defined in: RevoBoot/i386/config/SMBIOS/MacModelNN.h
	{
		_SMBIOS_DEBUG_DUMP("Error: File not found!\n");
	}
#endif /* LOAD_MODEL_SPECIFIC_SMBIOS_DATA */

	if (fileSize == 0)
	{
		// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
		#include STRING(SMBIOS_DATA_FILE)
		
		static uint32_t SMBIOS_Table[] =
		{
			// Replaced with data from: RevoBoot/i386/config/SMBIOS/MacModelNN.h
			STATIC_SMBIOS_DATA
		};

		tableLength = sizeof(SMBIOS_Table);
		staticSMBIOSData = SMBIOS_Table;
		_SMBIOS_DEBUG_DUMP("Using statically linked SMBIOS data: %d bytes\n", tableLength);
	}

	if (*(uint32_t *) staticSMBIOSData == 0x44495555) // "UUID" in little endian.
	{
		offset = 20; // "UUID" + 16 bytes data
	}

	// Copy the static SMBIOS data into the newly allocated memory page. Right after the new EPS.
	memcpy((kernelMemory + sizeof(* newEPS)), staticSMBIOSData + offset, (tableLength - offset));

#ifdef SMB_STATIC_SYSTEM_UUID
	// This enables you to override the factory UUID from the settings file.
	static unsigned char SMB_SYSTEM_UUID[] = SMB_STATIC_SYSTEM_UUID;

	// Replace factory UUID with the one specified in: RevoBoot/i386/config/SETTINGS/MacModelNN.h
	memcpy(gPlatform.UUID, SMB_SYSTEM_UUID, 16);
#else
	if (offset)
	{
		// Get UUID from (dynamically loaded) SMBIOS data (/Extra/SMBIOS/MacModelNN.bin)
		memcpy(gPlatform.UUID, staticSMBIOSData + 4, 16);
	}
#endif

#endif /* !__LIBSAIO_SMBIOS_STATIC_DATA_H */
