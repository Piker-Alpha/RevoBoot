/*
 * Copyright 2009 by Master Chief.
 *
 * Updates:
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- New path for static EFI data (PikerAlpha, October 2012).
 *			- Optionally check /Extra/SMBIOS/[MacModelNN.bin] for static SMBIOS data (PikerAlpha, October 2012).
 *			- Get maxStructureSize/structureCount from factory EPS (PikerAlpha, October 2012).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 */

#ifndef __LIBSAIO_SMBIOS_STATIC_DATA_H
#define __LIBSAIO_SMBIOS_STATIC_DATA_H

	#include "essentials.h"

	int tableLength = 0;
	long fileSize = 0; // FIXME: This variable <i>is used</i> but conditionally!

	#if LOAD_MODEL_SPECIFIC_SMBIOS_DATA
		char dirSpec[32] = "";
		void * staticSMBIOSData = (void *)kLoadAddr;

		sprintf(dirSpec, "/Extra/SMBIOS/%s.bin", COMMA_STRIPPED_MODEL_ID);

		_SMBIOS_DEBUG_DUMP("Loading: %s", dirSpec);

		fileSize = loadBinaryData(dirSpec, &staticSMBIOSData);

		if (fileSize > 0)
		{
			memcpy((kernelMemory + sizeof(* newEPS)), staticSMBIOSData, fileSize);

			// factoryEPS = (struct SMBEntryPoint *) baseAddress;
		
			tableLength = fileSize;

			_SMBIOS_DEBUG_DUMP("\n");
		}
		else // File not found. Use static data defined in RevoBoot/i386/config/SMBIOS/
		{
			// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
			#include STRING(SMBIOS_DATA_FILE)
		
			static uint32_t SMBIOS_Table[] =
			{
				// Replaced with data from: RevoBoot/i386/config/SMBIOS/[data-template/MacModelNN].h
				STATIC_SMBIOS_DATA
			};

			tableLength = sizeof(SMBIOS_Table);

			_SMBIOS_DEBUG_DUMP("Error: File not found!\nNow trying statically linked SMBIOS data: %d bytes\n", tableLength);

			// Copy the static SMBIOS data into the newly allocated memory page. Right after the new EPS.
			memcpy((kernelMemory + sizeof(* newEPS)), SMBIOS_Table, tableLength);
		}
	#else
		// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
		#include STRING(SMBIOS_DATA_FILE)
		
		static uint32_t SMBIOS_Table[] =
		{
			// Replaced with data from: RevoBoot/i386/config/SMBIOS/[data-template/MacModelNN].h
			STATIC_SMBIOS_DATA
		};
		
		_SMBIOS_DEBUG_DUMP("Using statically linked SMBIOS data\n");
		
		tableLength = sizeof(SMBIOS_Table);
		
		// Copy the static SMBIOS data into the newly allocated memory page. Right after the new EPS.
		memcpy((kernelMemory + sizeof(* newEPS)), SMBIOS_Table, tableLength);
	#endif /* LOAD_MODEL_SPECIFIC_SMBIOS_DATA */

#endif /* !__LIBSAIO_SMBIOS_STATIC_DATA_H */
