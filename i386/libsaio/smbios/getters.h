/*
 * The first SMBIOS patcher was developped by mackerintel in 2008, which 
 * was ripped apart and rewritten by Master Chief for Revolution in 2009.
 *
 * Updates:
 *
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- Complete rewrite / overhaul by DHP in Februari 2011.
 *			- Coding style change by DHP in Februari 2011.
 *			- EFI fix for FSB speed added by DHP in June 2011 (tested by flaKed).
 *			- Function getOverrideString removed (PikerAlpha, October 2012).
 *			- Function getBIOSDate added (PikerAlpha, October 2012).
 *			- Unused arguments removed (PikerAlpha, October 2012).
  *			- Pre-compiler directive PROBOARD removed, which is required for iMessage (PikerAlpha, January 2013).
 *
 * Credits:
 *			- macerintel (see note in source code)
 *			- blackosx, DB1, dgsga, FKA, flaKed, humph, scrax and STLVNUB (testers).
 */


#define SMBIOS_SEARCH_BASE		0x000F0000
#define SMBIOS_SEARCH_END		0x000FFFFF
#define SMBIOS_ANCHOR			0x5f4d535f	// '_SM_' in Little Endian.
#define SMBIOS_MPS_ANCHOR		0x5f504d5f	// '_MP_' in Little Endian.

#define NOT_AVAILABLE	"N/A"
#define RAM_SLOT_EMPTY	""

#ifndef STATIC_RAM_OVERRIDE_TYPE
	#define STATIC_RAM_OVERRIDE_TYPE	SMB_MEM_TYPE_DDR3
#endif

#ifndef STATIC_RAM_OVERRIDE_FREQUENCY
	#define STATIC_RAM_OVERRIDE_FREQUENCY 1066
#endif

/*==============================================================================
 * On non-EFI systems, like our hackintosh, the SMBIOS Entry Point Structure can 
 * be located by searching for the anchor-string on paragraph (16-byte) 
 * boundaries within the physical memory address range 000F0000h to 000FFFFFh.
 */

static inline struct SMBEntryPoint * getEPSAddress(void)
{
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

						_SMBIOS_DEBUG_DUMP("SMBIOS baseAddress: 0x%8x\n", baseAddress);
						_SMBIOS_DEBUG_DUMP("MultiP baseAddress: 0x%8x\n", mpsAddress);
						_SMBIOS_DEBUG_SLEEP(10);

						break;
					}
				}
#endif // INCLUDE_MP_TABLE

				return baseAddress;
			}
			else
			{
				verbose("Found SMBIOS anchor with bad checksum. ");
			}
		}
	}

	verbose("Unable to locate SMBIOS table anchor.\n");
	sleep(5);

	return 0;
}


//==============================================================================

static SMBWord getFSBFrequency(void)
{
	// _SMBIOS_DEBUG_DUMP("In getFSBFrequency() = %d Hz\n", (gPlatform.CPU.FSBFrequency < 100500000) ? 0 : (gPlatform.CPU.FSBFrequency / 1000000));
	_SMBIOS_DEBUG_DUMP("In getFSBFrequency() = %d Hz\n", (gPlatform.CPU.FSBFrequency == 0) ? 0 : (gPlatform.CPU.FSBFrequency / 1000000));

	if (gPlatform.CPU.QPISpeed == 0)
	{
		return ((gPlatform.CPU.FSBFrequency / 1000000) / 4);
	}

	/*
	 * Returning zero (0) here is invalid, but we can get away with it because 
	 * of XNU's check in tsc_init() which effectively catches the invalid value
	 * and set it to 100 MHz for Sandy Bridge CPU's (133 MHz when quad pumped).
	 *
	 * Note: We don't want to lose the OC feedback in GeekBench et all and that 
	 *		 is why we first check the value, to detect a OC'ed BCLK setting, 
	 *		 and use that when found. This also requires you to comment out the 
	 *		 Quad Pump lines in the AppleSMBIOS.kext source code, or it will 
	 *		 (for example) report 412 MHz instead of 103 MHz.
	 */

	return 100; // (gPlatform.CPU.FSBFrequency < 100500000) ? 0 : (gPlatform.CPU.FSBFrequency / 1000000);
}


//==============================================================================

static SMBWord getCPUFrequency(void)
{
	_SMBIOS_DEBUG_DUMP("In getCPUFrequency() = %d Hz\n", (gPlatform.CPU.CPUFrequency / 1000000));

	return (gPlatform.CPU.CPUFrequency / 1000000);
}


//==============================================================================

static SMBWord getCPUType(void)
{
	_SMBIOS_DEBUG_DUMP("In getCPUType() = 0x%x\n", gPlatform.CPU.Type);

	return gPlatform.CPU.Type;
}


#if OVERRIDE_DYNAMIC_MEMORY_DETECTION
//==============================================================================

int getSlotNumber(int slotNumber)
{
	_SMBIOS_DEBUG_DUMP("In getSlotNumber(%d)\n", slotNumber);

	// Return -1 for empty slots.
	if (gPlatform.RAM.MODULE[slotNumber].InUse == false)
	{
		return -1;
	}

	// Limit structureIndex to STATIC_RAM_SLOTS (defined in: config/settings.h)
	if (slotNumber > gPlatform.RAM.SlotCount)
	{
		slotNumber = 0;
	}

#if DEBUG_SMBIOS
	sleep(1);	// Silent sleep (for debug only / slows down the process).
#endif

	return slotNumber;
}
#endif


#if STATIC_RAM_OVERRIDE_SIZE
//==============================================================================

static SMBWord getRAMSize(void)
{
	int slotNumber = getSlotNumber(requiredStructures[kSMBTypeMemoryDevice].hits);

	_SMBIOS_DEBUG_DUMP("In getRAMSize(%d) = %d\n", kSMBTypeMemoryDevice, gPlatform.RAM.MODULE[slotNumber].Size);

	if (!gPlatform.RAM.MODULE[slotNumber].InUse || gPlatform.RAM.MODULE[slotNumber].Size == SMB_MEM_BANK_EMPTY)
	{
		return 0;
	}

	return gPlatform.RAM.MODULE[slotNumber].Size;
}
#endif


#if STATIC_RAM_OVERRIDE_TYPE
//==============================================================================

static SMBByte getRAMType(void)
{
#if (DEBUG_SMBIOS == 2)
	_SMBIOS_DEBUG_DUMP("In getRAMType() = %s\n", SMBMemoryDeviceTypes[STATIC_RAM_OVERRIDE_TYPE]);
#endif

	return STATIC_RAM_OVERRIDE_TYPE;
}
#endif


#if STATIC_RAM_OVERRIDE_FREQUENCY
//==============================================================================

static SMBWord getRAMFrequency(void)
{
	_SMBIOS_DEBUG_DUMP("In getRAMFrequency() = %d\n", STATIC_RAM_OVERRIDE_FREQUENCY);

	return STATIC_RAM_OVERRIDE_FREQUENCY;
}
#endif


//==============================================================================

static const char * getRAMVendor(void)
{
#if OVERRIDE_DYNAMIC_MEMORY_DETECTION || DEBUG_SMBIOS
	uint8_t structureIndex = requiredStructures[kSMBTypeMemoryDevice].hits;
#endif

#if OVERRIDE_DYNAMIC_MEMORY_DETECTION
	_SMBIOS_DEBUG_DUMP("In getRAMVendor(%d)", structureIndex);

	int slotNumber = getSlotNumber(structureIndex);

	if (slotNumber == -1)
	{
		_SMBIOS_DEBUG_DUMP("\n");

		return RAM_SLOT_EMPTY;
	}

	_SMBIOS_DEBUG_DUMP(" = %s\n", gPlatform.RAM.MODULE[slotNumber].Vendor);

	return gPlatform.RAM.MODULE[slotNumber].Vendor;
#else
	_SMBIOS_DEBUG_DUMP("In getRAMVendor(%d) = N/A\n", structureIndex);

	return NOT_AVAILABLE;
#endif
}


//==============================================================================

static const char * getRAMSerialNumber(void)
{
#if OVERRIDE_DYNAMIC_MEMORY_DETECTION || DEBUG_SMBIOS
	uint8_t structureIndex = requiredStructures[kSMBTypeMemoryDevice].hits;
#endif

#if OVERRIDE_DYNAMIC_MEMORY_DETECTION
	_SMBIOS_DEBUG_DUMP("In getRAMSerialNumber(%d)", structureIndex);

	int slotNumber = getSlotNumber(structureIndex);

	if (slotNumber == -1)
	{
		_SMBIOS_DEBUG_DUMP("\n");

		return RAM_SLOT_EMPTY;
	}

	_SMBIOS_DEBUG_DUMP(" = %s\n", gPlatform.RAM.MODULE[slotNumber].SerialNumber);

	return gPlatform.RAM.MODULE[slotNumber].SerialNumber;
#else
	_SMBIOS_DEBUG_DUMP("In getRAMSerialNumber(%d) = N/A\n", structureIndex);

	return NOT_AVAILABLE;
#endif
}


//==============================================================================

static const char * getRAMPartNumber(void)
{
#if OVERRIDE_DYNAMIC_MEMORY_DETECTION || DEBUG_SMBIOS
	uint8_t structureIndex = requiredStructures[kSMBTypeMemoryDevice].hits;
#endif

#if OVERRIDE_DYNAMIC_MEMORY_DETECTION
	_SMBIOS_DEBUG_DUMP("In getRAMPartNumber(%d)", structureIndex);

	int slotNumber = getSlotNumber(structureIndex);

	if (slotNumber == -1)
	{
		_SMBIOS_DEBUG_DUMP("\n");
		
		return RAM_SLOT_EMPTY;
	}

	_SMBIOS_DEBUG_DUMP(" = %s\n", gPlatform.RAM.MODULE[slotNumber].PartNumber);

	return gPlatform.RAM.MODULE[slotNumber].PartNumber;
#else
	_SMBIOS_DEBUG_DUMP("In getRAMPartNumber(%d) = N/A\n", structureIndex);

	return NOT_AVAILABLE;
#endif
}


//==============================================================================
// This function returns the BIOS date, extracted from SMB_BIOS_VERSION
//==============================================================================

static const char * getBIOSDate(void)
{
	//  0123456789 123456789 1234567
	// "MM51.88Z.0077.B10.1201241549"
	// "01/24/2012"

	const char smbBIOSVersion[] = SMB_BIOS_VERSION;

	size_t len = strlen(smbBIOSVersion);

	char biosDate[len];
	bzero(biosDate, len);

	strncpy(biosDate,		smbBIOSVersion + (len -  8), 2);
	strncpy(biosDate + 2,	"/", 1);
	strncpy(biosDate + 3,	smbBIOSVersion + (len - 6), 2);
	strncpy(biosDate + 5,	"/20", 3);
	strncpy(biosDate + 8,	smbBIOSVersion + (len -  10), 2);

	// biosDate[10] = 0;

	_SMBIOS_DEBUG_DUMP("biosDate = %s\n", biosDate);
	_SMBIOS_DEBUG_SLEEP(5);

	const char * retValue = biosDate;

	return "05/01/2017"; // retValue; // Example: "01/24/2012";
}

//==============================================================================

static SMBWord getBIOSLocation(void)
{
	return (0); // rom@0 so that the 'EFI Firmware Updates' will be offered. 
}

//==============================================================================

static SMBQWord getBIOSFeatures(void)
{
	return 0x0000000000019880ULL;
}

//==============================================================================

static SMBDWord getBIOSFeaturesEX(void)
{
	return (0x010002c1);
}

//==============================================================================

static SMBByte getBoardType(void)
{
#if TARGET_MODEL & MACPRO
	return 0x0b;
#else
	return 0x0a;
#endif
}

//==============================================================================

static SMBDWord getFirmwareFeatures(void)
{
	return 0xE907F537;
}

//==============================================================================

static SMBDWord getFirmwareFeaturesEx(void)
{
	return 0xFFFFFFFF;
}

//==============================================================================

static SMBDWord getROMFeatures(void)
{
	return 0xFFFFFFFF;
}
