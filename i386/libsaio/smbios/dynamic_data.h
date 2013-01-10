/*
 * The first SMBIOS patcher was developped by mackerintel in 2008, which 
 * was ripped apart and rewritten by Master Chief for Revolution in 2009.
 *
 * Updates:
 *
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- Complete rewrite / overhaul by DHP in Februari 2011.
 *			- More work, including bug fixes by DHP in Februari 2011.
 *			- Do more with cleaner and faster code in less bytes (DHP in March 2012).
 *			- SMBIOS data logic moved to preprocessor code (PikerAlpha, October 2012).
 *			- SMBProperties changed for speed and simplicity (PikerAlpha, October 2012).
 *			- Calls with SMBProperties.keyString cleaned up (PikerAlpha, October 2012).
 *			- Fixed requiredStructures.start/stop values (PikerAlpha, October 2012).
 *			- STATIC_SMSERIALNUMBER renamed to SMB_SYSTEM_SERIAL_NUMBER (PikerAlpha, October 2012).
 *			- Removed some unused experimental code snippets (PikerAlpha, November 2012).
 *			- Option SET_MAX_STRUCTURE_LENGTH to verify/fix newEPS->maxStructureSize (PikerAlpha, November 2012).
 *			- Allow DEBUG_SMBIOS = 2 to filter out some of the output (PikerAlpha, November 2012).
 *			- Pre-compiler directive PROBOARD removed, which is required for iMessage (PikerAlpha, January 2013).
 *
 * Credits:
 *			- Kabyl (see notes in source code)
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 *
 * Tip:		The idea is to use dynamic SMBIOS generation in RevoBoot only to 
 *			let it strip your factory table, after which you should do this:
 *
 *			1.) Extract the new OS X compatible SMBIOS table with: tools/smbios2struct3
 *			2.) Add the data structure to: RevoBoot/i386/config/SMBIOS/data.h
 *			3.) Recompile RevoBoot, and be happy with your quicker boot time.
 *
 * Note:	Repeat this procedure after adding memory or other SMBIOS relevant 
 *			hardware changes, like replacing the motherboard and/or processor.
 */


#ifndef __LIBSAIO_SMBIOS_PATCHER_H
#define __LIBSAIO_SMBIOS_PATCHER_H

#include "libsaio.h"

#include "smbios.h"
#include "model_data.h"

#define IOSERVICE_PLATFORM_FEATURE	0x0000000000000001

//------------------------------------------------------------------------------

struct SMBStructure
{
	SMBByte	type;			// Structure type.
	SMBByte	start;			// Turbo index (start location in properties array).
	SMBByte	stop;			// Turbo index end (start + properties).
	SMBBool	copyStrings;	// True for structures where string data should be copied.
	SMBByte	hits;			// Number of located structures of a given type.
};


//------------------------------------------------------------------------------

struct SMBStructure requiredStructures[] =
{
	{ kSMBTypeBIOSInformation			/*   0 */ ,  0,					 5,					false,	0	},
	{ kSMBTypeSystemInformation			/*   1 */ ,	 6,					10,					false,	0	},
	{ kSMBTypeBaseBoard					/*   2 */ ,	13,					14,					false,	0	},
	{ kSMBUnused						/*   3 */ ,	 0,					 0,					false,	0	},
	{ kSMBTypeProcessorInformation		/*   4 */ ,	15,					16,					true,	0	},
	{ kSMBUnused						/*   5 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*   6 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*   7 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*   8 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*   9 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  10 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  11 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  12 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  13 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  14 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  15 */ ,	 0,					 0,					false,	0	},
	{ kSMBUnused						/*  16 */ ,	 0,					 0,					false,	0	},
	{ kSMBTypeMemoryDevice				/*  17 */ ,	17,					22,					true,	0	},
	{ kSMBUnused						/*  18 */ ,	 0,					 0,					false,	0	},
	{ kSMBTypeMemoryArrayMappedAddress	/*	19 */ ,	-1,					-1,					false,	0	}
};


#include "getters.h"	// Depends on 'requiredStructures'.

//------------------------------------------------------------------------------

struct SMBProperty
{
	uint8_t		type;

	int			offset;

	enum
	{
		kSMBString,
		kSMBByte,
		kSMBWord,
		kSMBDWord,
		kSMBQWord
	} valueType;
	
	UInt8	(* getSMBByte)	(void);
	UInt16	(* getSMBWord)	(void);
	UInt32	(* getSMBDWord)	(void);
	UInt64	(* getSMBQWord)	(void);

	const char *(* getSMBString)	(void);

	const char *plainData;
};

#define APPLE_INC			"Apple Inc."

//------------------------------------------------------------------------------

struct SMBProperty SMBProperties[] =
{
	//----------------------------------------------------------------------------------------------------
	
	{ kSMBTypeBIOSInformation,		0x04,	kSMBString,		.plainData		= APPLE_INC					},
	{ kSMBTypeBIOSInformation,		0x05,	kSMBString,		.plainData		= SMB_BIOS_VERSION			},
	{ kSMBTypeBIOSInformation,		0x06,	kSMBWord,		.getSMBWord		= getBIOSLocation			},
	{ kSMBTypeBIOSInformation,		0x08,	kSMBString,		.getSMBString	= getBIOSDate				},
	{ kSMBTypeBIOSInformation,		0x0a,	kSMBQWord,		.getSMBQWord	= getBIOSFeatures			},
	{ kSMBTypeBIOSInformation,		0x12,	kSMBDWord,		.getSMBDWord	= getBIOSFeaturesEX			},

	//----------------------------------------------------------------------------------------------------
	
	{ kSMBTypeSystemInformation,	0x04,	kSMBString,		.plainData		= APPLE_INC					},
	{ kSMBTypeSystemInformation,	0x05,	kSMBString,		.plainData		= SMB_PRODUCT_NAME			},
	{ kSMBTypeSystemInformation,	0x06,	kSMBString,		.plainData		= "1.0"						},
	{ kSMBTypeSystemInformation,	0x07,	kSMBString,		.plainData		= SMB_SYSTEM_SERIAL_NUMBER	},
	{ kSMBTypeSystemInformation,	0x1a,	kSMBString,		.plainData		= SMB_FAMILY				},
	
	//----------------------------------------------------------------------------------------------------
	
	{ kSMBTypeBaseBoard,			0x04,	kSMBString,		.plainData		= APPLE_INC					},
	{ kSMBTypeBaseBoard,			0x05,	kSMBString,		.plainData		= SMB_BOARD_PRODUCT			},

    { kSMBTypeBaseBoard,			0x07,	kSMBString,		.plainData		= SMB_BOARD_SERIAL_NUMBER	},
	{ kSMBTypeBaseBoard,			0x0d,	kSMBByte,		.getSMBByte		= getBoardType				},

	//----------------------------------------------------------------------------------------------------
	
	{ kSMBTypeProcessorInformation,	0x12,	kSMBWord,		.getSMBWord		= getFSBFrequency			},
	{ kSMBTypeProcessorInformation,	0x14,	kSMBWord,		.getSMBWord		= getCPUFrequency			},
	
	//----------------------------------------------------------------------------------------------------

#if DYNAMIC_RAM_OVERRIDE_ERROR_HANDLE
	// Handle or instance number associated with any error that was previously detected for the device.
	// If the system does not provide the error information structure, then this field contains FFFEh;
	// otherwise this field contains either FFFFh (if no error was detected) or the handle (number) of
	// the error information structure. See 7.18.4 and 7.34 of the SMBIOS specification.
	{ kSMBTypeMemoryDevice,			0x06,	kSMBWord,		.plainData		= 0xFFFE					},
#endif

#if DYNAMIC_RAM_OVERRIDE_SIZE
	{ kSMBTypeMemoryDevice,			0x0c,	kSMBWord,		.getSMBWord		= getRAMSize				},
#endif
	
	{ kSMBTypeMemoryDevice,			0x10,	kSMBString,		.getSMBString	= NULL						},
	{ kSMBTypeMemoryDevice,			0x11,	kSMBString,		.getSMBString	= NULL						},

#if DYNAMIC_RAM_OVERRIDE_TYPE
	{ kSMBTypeMemoryDevice,			0x12,	kSMBByte,		.getSMBByte		= getRAMType				},
#endif

#if DYNAMIC_RAM_OVERRIDE_FREQUENCY  
	{ kSMBTypeMemoryDevice,			0x15,	kSMBWord,		.getSMBWord		= getRAMFrequency			},
#endif

	{ kSMBTypeMemoryDevice,			0x17,	kSMBString,		.getSMBString	= getRAMVendor				},
	{ kSMBTypeMemoryDevice,			0x18,	kSMBString,		.getSMBString	= getRAMSerialNumber		},
	{ kSMBTypeMemoryDevice,			0x1a,	kSMBString,		.getSMBString	= getRAMPartNumber			},
};


//==============================================================================

void setupSMBIOS(void)
{
	_SMBIOS_DEBUG_DUMP("Entering setupSMBIOS(dynamic)\n");

	struct SMBEntryPoint *factoryEPS = (struct SMBEntryPoint *) getEPSAddress();
	
	_SMBIOS_DEBUG_DUMP("factoryEPS->dmi.structureCount: %d - tableLength: %d\n", factoryEPS->dmi.structureCount, factoryEPS->dmi.tableLength);

	//--------------------------------------------------------------------------
	// Uncomment this when you want to use the factory SMBIOS data structures.
	//
	// gPlatform.SMBIOS.BaseAddress = (uint32_t) factoryEPS;
	// return;
	//--------------------------------------------------------------------------

	// Allocate 1 page of kernel memory (sufficient for a stripped SMBIOS table).
	void * kernelMemory = (void *)AllocateKernelMemory(4096);

	// Setup a new Entry Point Structure at the beginning of the newly allocated memory page.
	struct SMBEntryPoint * newEPS = (struct SMBEntryPoint *) kernelMemory;

	// Clear the first K bytes (new table will be even shorter).
	bzero(kernelMemory, 1024);

	newEPS->anchor[0]			= 0x5f;							// _
	newEPS->anchor[1]			= 0x53;							// S
	newEPS->anchor[2]			= 0x4d;							// M
	newEPS->anchor[3]			= 0x5f;							// _
	newEPS->checksum			= 0;							// Updated at the end of this run.
	newEPS->entryPointLength	= 0x1f;							// sizeof(* newEPS)
	newEPS->majorVersion		= 2;							// SMBIOS version 2.4
	newEPS->minorVersion		= 4;
	newEPS->maxStructureSize	= factoryEPS->maxStructureSize;	// Optionally checked and updated later on.
	newEPS->entryPointRevision	= 0;

	newEPS->formattedArea[0]	= 0;
	newEPS->formattedArea[1]	= 0;
	newEPS->formattedArea[2]	= 0;
	newEPS->formattedArea[3]	= 0;
	newEPS->formattedArea[4]	= 0;

	newEPS->dmi.anchor[0]		= 0x5f;							// _
	newEPS->dmi.anchor[1]		= 0x44;							// D
	newEPS->dmi.anchor[2]		= 0x4d;							// M
	newEPS->dmi.anchor[3]		= 0x49;							// I
	newEPS->dmi.anchor[4]		= 0x5f;							// _
	newEPS->dmi.checksum		= 0;							// Updated at the end of this run.
	newEPS->dmi.tableLength		= 0;							// Updated at the end of this run.
	newEPS->dmi.tableAddress	= (uint32_t) (kernelMemory + sizeof(struct SMBEntryPoint));
	newEPS->dmi.structureCount	= 0;							// Updated during this run.
	newEPS->dmi.bcdRevision		= 0x24;							// SMBIOS version 2.4

	char * stringsPtr			= NULL;
	char * newtablesPtr			= (char *)newEPS->dmi.tableAddress;
	char * structurePtr			= (char *)factoryEPS->dmi.tableAddress;

	int i, j, numberOfStrings	= 0;
	int structureCount			= factoryEPS->dmi.structureCount;

	SMBWord handle = 1;

	//------------------------------------------------------------------------------
	// Add SMBOemProcessorType structure.

	struct SMBStructHeader * newHeader = (struct SMBStructHeader *) newtablesPtr;

	newHeader->type		= kSMBTypeOemProcessorType;
	newHeader->length	= 6;
	newHeader->handle	= handle;

	*((uint16_t *)(((char *)newHeader) + 4)) = getCPUType();

	// Update EPS
	newEPS->dmi.tableLength += 8;
	newEPS->dmi.structureCount++;

	newtablesPtr += 8;

	//------------------------------------------------------------------------------
	// Add SMBOemProcessorBusSpeed structure (when we have something to inject).

	if (gPlatform.CPU.QPISpeed)
	{
		newHeader = (struct SMBStructHeader *) newtablesPtr;

		newHeader->type		= kSMBTypeOemProcessorBusSpeed;
		newHeader->length	= 6;
		newHeader->handle	= ++handle;

		*((uint16_t *)(((char *)newHeader) + 4)) = gPlatform.CPU.QPISpeed;

		// Update EPS
		newEPS->dmi.tableLength += 8;
		newEPS->dmi.structureCount++;

		newtablesPtr += 8;
	}

#if (DYNAMIC_RAM_OVERRIDE_ERROR_HANDLE || DYNAMIC_RAM_OVERRIDE_SIZE || DYNAMIC_RAM_OVERRIDE_TYPE || DYNAMIC_RAM_OVERRIDE_FREQUENCY)
	requiredStructures[17].stop = (sizeof(SMBProperties) / sizeof(SMBProperties[0])) -1;
#endif

	//------------------------------------------------------------------------------
	// Main loop

	for (i = 0; i < structureCount; i++)
	{
		struct SMBStructHeader * factoryHeader = (struct SMBStructHeader *) structurePtr;
		SMBByte currentStructureType = factoryHeader->type;

		if ((currentStructureType > 19) || (requiredStructures[currentStructureType].type == kSMBUnused))
		{
			// _SMBIOS_DEBUG_DUMP("Dropping SMBIOS structure: %d\n", currentStructureType);

			// Skip the formatted area of the structure.
			structurePtr += factoryHeader->length;

			// Skip the unformatted structure area at the end (strings).
			// Using word comparison instead of checking two bytes (thanks to Kabyl).
			for (; ((uint16_t *)structurePtr)[0] != 0; structurePtr++);

			// Adjust pointer after locating the double 0 terminator.
			structurePtr += 2;

#if (DEBUG_SMBIOS & 2)
			_SMBIOS_DEBUG_DUMP("currentStructureType: %d (length: %d)\n", currentStructureType, factoryHeader->length);
			_SMBIOS_DEBUG_SLEEP(1);
#endif
			continue;
		}

		newHeader = (struct SMBStructHeader *) newtablesPtr;

		// Copy structure data from factory table to new table (not the strings).
		memcpy(newHeader, factoryHeader, factoryHeader->length);

		// Init handle in the new header.
		newHeader->handle = ++handle;

		// Update structure counter.
		newEPS->dmi.structureCount++;

		// Update pointers (pointing to the end of the formatted area).
		structurePtr	+= factoryHeader->length;
		stringsPtr		= structurePtr;
		newtablesPtr	+= factoryHeader->length;

		// Reset string counter.
		numberOfStrings	= 0;

		// Get number of strings in the factory structure.
		// Using word comparison instead of checking two bytes (thanks to Kabyl).
		for (; ((uint16_t *)structurePtr)[0] != 0; structurePtr++)
		{
			// Is this the end of a string?
			if (structurePtr[0] == 0)
			{
				// Yes. Add one.
				numberOfStrings++;
			}
		}

		if (structurePtr != stringsPtr)
		{
			// Yes. Add one.
			numberOfStrings++;
		}

		structurePtr += 2;

#if SET_MAX_STRUCTURE_LENGTH
		/*
		 * Size of the longest factory SMBIOS structure, in bytes, encompasses the structure’s formatted area
		 * and text strings. In our case a kSMBTypeProcessorInformation structure, because we strip out all
		 * unwanted data. And safe to check it at this point, because we don't add anything this long ourself.
		 *
		 * Note: The maximum structure length is only checked when SET_MAX_STRUCTURE_LENGTH is set to 1 but 
		 *		 is not required, because it is only available since RevoBoot v1.5.35. Never checked before.
		 */

		UInt16 maxStructureSize = (structurePtr - (stringsPtr - factoryHeader->length));

		if (newEPS->maxStructureSize < maxStructureSize)
		{
			newEPS->maxStructureSize = maxStructureSize;
		}

	#if (DEBUG_SMBIOS & 2)
		_SMBIOS_DEBUG_DUMP("Structure (%d) length: %3d bytes.\n", currentStructureType, maxStructureSize);
		_SMBIOS_DEBUG_SLEEP(1);
	#endif
#endif // if SET_MAX_STRUCTURE_LENGTH

		// Do we need to copy the string data?
		if (requiredStructures[currentStructureType].copyStrings)
		{
			// Yes, copy string data from the factory structure and paste it to the new table data.
			memcpy(newtablesPtr, stringsPtr, structurePtr - stringsPtr);

			// Point to the next possible position for a string (deducting the second 0 char at the end).
			int stringDataLength = structurePtr - stringsPtr - 1;

			// Point to the next possible position for a string (deducting the second 0 char at the end).
			newtablesPtr += stringDataLength;
		}
		else
		{
			newtablesPtr++;
			numberOfStrings = 0;
		}

		// If no string was found then rewind to the first 0 of the double null terminator.
		if (numberOfStrings == 0)
		{
			newtablesPtr--;
		}

		// Initialize turbo index.
		int start	= requiredStructures[currentStructureType].start;
		int stop	= requiredStructures[currentStructureType].stop;

		// Jump to the target start index in the properties array (looping to the target end) and update the SMBIOS structure.
		for (j = start; j <= stop; j++)
		{
			const char * str = "";

			if (SMBProperties[j].type != currentStructureType)
			{
#if (DEBUG_SMBIOS & 2)
				/*
				 * When SMBProperties[j].start and SMBProperties[j].stop are set to -1
				 * then there isn't anything to add/replace, but that is not an error.
				 */
				if ((SMBProperties[j].start > -1) && (SMBProperties[j].stop > -1))
				{
					printf("SMBIOS Patcher Error: Turbo Index [%d != %d] Mismatch!\n", SMBProperties[j].type, currentStructureType);
				}
#endif
				continue;
			}

			switch (SMBProperties[j].valueType)
			{
				case kSMBByte:
					*((uint8_t *)(((char *)newHeader) + SMBProperties[j].offset)) = SMBProperties[j].getSMBByte();
					break;
					
				case kSMBWord:
					*((uint16_t *)(((char *)newHeader) + SMBProperties[j].offset)) = SMBProperties[j].getSMBWord();
					break;

				case kSMBDWord:
					*((uint32_t *)(((char *)newHeader) + SMBProperties[j].offset)) = SMBProperties[j].getSMBDWord();
					break;

				case kSMBQWord:
					*((uint64_t *)(((char *)newHeader) + SMBProperties[j].offset)) = SMBProperties[j].getSMBQWord();
					break;

				case kSMBString:
					// Newly added to support preprocessor data (for speed and simplicity).
					if (SMBProperties[j].plainData)
					{
						str = SMBProperties[j].plainData;
					}
					else if (SMBProperties[j].getSMBString)
					{
						str = SMBProperties[j].getSMBString();
					}

					size_t size = strlen(str);

					if (size)
					{
						memcpy(newtablesPtr, str, size);
						newtablesPtr[size]	= 0;
						newtablesPtr		+= (size + 1);
						*((uint8_t *)(((char *)newHeader) + SMBProperties[j].offset)) = ++numberOfStrings;
					}
					break;
			}
		}
	
		if (numberOfStrings == 0)
		{
			newtablesPtr[0] = 0;
			newtablesPtr++;
		}
	
		newtablesPtr[0] = 0;
		newtablesPtr++;
		requiredStructures[currentStructureType].hits++;
	}

	//------------------------------------------------------------------------------
	// Add Platform Feature structure (Apple Specific Type 0x85/133).
	//
	// Note: AppleSMBIOS.kext will use this data for: IOService:/platform-feature

	newHeader = (struct SMBStructHeader *) newtablesPtr;
  
	newHeader->type		= kSMBTypeOemPlatformFeature;
	newHeader->length	= 0x0C;
	newHeader->handle	= ++handle;
  
	*((uint64_t *)(((char *)newHeader) + 4)) = IOSERVICE_PLATFORM_FEATURE;
  
	// Update EPS
	newEPS->dmi.tableLength += 0x0E; // 0x0C + two (00 00)
	newEPS->dmi.structureCount++;
  
	newtablesPtr += 0x0E;

	//------------------------------------------------------------------------------
	// Add EndOfTable structure.

	newHeader = (struct SMBStructHeader *) newtablesPtr;

	newHeader->type		= kSMBTypeEndOfTable;
	newHeader->length	= 4;
	newHeader->handle	= 0xFFFD; // ++handle;

	newtablesPtr += 6;

	// Update EPS
	newEPS->dmi.tableLength += 6;
	newEPS->dmi.structureCount++;

	//------------------------------------------------------------------------------

	newEPS->dmi.tableLength = (newtablesPtr - (char *)newEPS->dmi.tableAddress);

	// Calculate new checksums.
	newEPS->dmi.checksum	= 256 - checksum8(&newEPS->dmi, sizeof(newEPS->dmi));
	newEPS->checksum		= 256 - checksum8(newEPS, sizeof(* newEPS));

	_SMBIOS_DEBUG_DUMP("newEPS->dmi.structureCount: %d - tableLength: %d\n", newEPS->dmi.structureCount, newEPS->dmi.tableLength);

	// Used to update the EFI Configuration Table (in efi.c) which is 
	// what AppleSMBIOS.kext reads to setup the SMBIOS table for OS X.
	gPlatform.SMBIOS.BaseAddress = (uint32_t) newEPS;

	_SMBIOS_DEBUG_DUMP("New SMBIOS replacement setup.\n");
	_SMBIOS_DEBUG_SLEEP(15);
}


#endif /* !__LIBSAIO_SMBIOS_PATCHER_H */
