/*
 * Copyright 2009 by Master Chief.
 *
 * Updates:
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- New path for static EFI data (PikerAlpha, October 2012).
 *			- Optionally check /Extra/SMBIOS/[MacModelNN.bin] for static SMBIOS data (PikerAlpha, October 2012).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 */

#ifndef __LIBSAIO_SMBIOS_STATIC_DATA_H
#define __LIBSAIO_SMBIOS_STATIC_DATA_H

#include "essentials.h"

#if LOAD_STATIC_SMBIOS_DATA_FROM_EXTRA

	#define STATIC_SMBIOS_DMI_STRUCTURE_COUNT	0
	#define STATIC_SMBIOS_SM_MAX_STRUCTURE_SIZE	0

	extern long loadBinaryData(char *aFilePath, void **aMemoryAddress);

	int tableLength = 0;
	char dirSpec[32] = "";
	sprintf(dirSpec, "/Extra/SMBIOS/%s", STRING(STATIC_DATA_FILENAME));

	void * staticSMBIOSData = (void *)kLoadAddr;

	_SMBIOS_DEBUG_DUMP("Loading: %s\n", dirSpec);

	long fileSize = loadBinaryData(dirSpec, &staticSMBIOSData);

	if (fileSize)
	{
		tableLength = (int)fileSize;
		
		memcpy((kernelMemory + sizeof(* newEPS)), staticSMBIOSData, tableLength);
	}
#else
	// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
	#include STRING(SMBIOS_DATA_FILE)

	static uint32_t SMBIOS_Table[] =
	{
		STATIC_SMBIOS_DATA	// Replaced with data from: RevoBoot/i386/config/SMBIOS/[default/MacModelNN].h
	};

	int tableLength = sizeof(SMBIOS_Table);
#endif

#endif /* !__LIBSAIO_SMBIOS_STATIC_DATA_H */
