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

#if LOAD_MODEL_SPECIFIC_SMBIOS_DATA

	#define SMBIOS_SEARCH_BASE		0x000F0000
	#define SMBIOS_SEARCH_END		0x000FFFFF
	#define SMBIOS_ANCHOR			0x5f4d535f	// '_SM_' in Little Endian.
	#define SMBIOS_MPS_ANCHOR		0x5f504d5f	// '_MP_' in Little Endian.

	_SMBIOS_DEBUG_DUMP("in getEPSAddress()\n");

	void *baseAddress = (void *)SMBIOS_SEARCH_BASE;

	for(; baseAddress <= (void *)SMBIOS_SEARCH_END; baseAddress += 16)
	{
		if (*(uint32_t *)baseAddress == SMBIOS_ANCHOR) // _SM_
		{
			if (checksum8(baseAddress, sizeof(struct SMBEntryPoint)) == 0)
			{
	#if INCLUDE_MP_TABLE
				// SMBIOS table located. Use this address as starting point.
				void * mpsAddress = baseAddress;
			
				// Now search for the Multi Processor table.
				for(; mpsAddress <= (void *)SMBIOS_SEARCH_END; mpsAddress += 16)
				{
					if (*(uint32_t *)mpsAddress == SMBIOS_MPS_ANCHOR)
					{
						gPlatform.MP.BaseAddress = (uint32_t)mpsAddress;
						break;
					}
				}
	#endif // INCLUDE_MP_TABLE

				break;

				_SMBIOS_DEBUG_DUMP("SMBIOS baseAddress: 0x%08x\n", baseAddress);
			}
		}
	}

	char dirSpec[32] = "";

	void * staticSMBIOSData = (void *)kLoadAddr;

	struct SMBEntryPoint *factoryEPS;

	sprintf(dirSpec, "/Extra/SMBIOS/%s.bin", COMMA_STRIPPED_MODEL_ID);

	_SMBIOS_DEBUG_DUMP("Loading: %s\n", dirSpec);

	long fileSize = loadBinaryData(dirSpec, &staticSMBIOSData);

	if (fileSize > 0)
	{
		memcpy((kernelMemory + sizeof(* newEPS)), staticSMBIOSData, fileSize);

		factoryEPS = (struct SMBEntryPoint *) baseAddress;
	}
	else // File not found. Use static data defined in RevoBoot/i386/config/SMBIOS/
	{
		tableLength = useStaticSMBIOSData((kernelMemory + sizeof(* newEPS)));
	}
#else
		tableLength = useStaticSMBIOSData((kernelMemory + sizeof(* newEPS)));
#endif /* LOAD_MODEL_SPECIFIC_SMBIOS_DATA */

#endif /* !__LIBSAIO_SMBIOS_STATIC_DATA_H */
