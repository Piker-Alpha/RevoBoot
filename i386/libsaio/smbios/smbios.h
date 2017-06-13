/*
 * Copyright (c) 1998-2009 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

// #include <IOKit/IOLib.h>

//
// Based on System Management BIOS Reference Specification v2.5
//

typedef bool	SMBBool;
typedef UInt8	SMBString;
typedef UInt8	SMBByte;
typedef UInt16	SMBWord;
typedef UInt32	SMBDWord;
typedef UInt64	SMBQWord;

typedef struct DMIEntryPoint
{
    SMBByte    anchor[5];
    SMBByte    checksum;
    SMBWord    tableLength;
    SMBDWord   tableAddress;
    SMBWord    structureCount;
    SMBByte    bcdRevision;
} __attribute__((packed)) DMIEntryPoint;

typedef struct SMBEntryPoint
{
    SMBByte    anchor[4];
    SMBByte    checksum;
    SMBByte    entryPointLength;
    SMBByte    majorVersion;
    SMBByte    minorVersion;
    SMBWord    maxStructureSize;
    SMBByte    entryPointRevision;
    SMBByte    formattedArea[5];
    struct DMIEntryPoint dmi;
} __attribute__((packed)) SMBEntryPoint;

//
// Header common to all SMBIOS structures
//

typedef struct SMBStructHeader
{
    SMBByte    type;
    SMBByte    length;
    SMBWord    handle;
} __attribute__((packed)) SMBStructHeader;

#define SMB_STRUCT_HEADER  SMBStructHeader header;

typedef struct SMBAnchor
{
	const SMBStructHeader *	header;
	const UInt8 *			next;
	const UInt8 *			end;
} SMBAnchor;

#define SMB_ANCHOR_IS_VALID(x)	\
	((x) && ((x)->header) && ((x)->next) && ((x)->end))

#define SMB_ANCHOR_RESET(x)		\
	bzero(x, sizeof(struct SMBAnchor));

//
// SMBIOS structure types.
//

enum {
    kSMBTypeBIOSInformation             =  0,
    kSMBTypeSystemInformation           =  1,
    kSMBTypeBaseBoard					=  2,
    kSMBTypeSystemEnclosure             =  3,
    kSMBTypeProcessorInformation        =  4,
    kSMBTypeMemoryModule                =  6,
    kSMBTypeCacheInformation            =  7,
    kSMBTypeSystemSlot                  =  9,
    kSMBTypeOemStrings                  = 11,
    kSMBTypePhysicalMemoryArray         = 16,
    kSMBTypeMemoryDevice                = 17,
    kSMBType32BitMemoryErrorInfo        = 18,
    kSMBTypeMemoryArrayMappedAddress	= 19,
    kSMBType64BitMemoryErrorInfo        = 33,

    kSMBTypeEndOfTable                  = 127,

    // Apple Specific Structures.
    kSMBTypeFirmwareVolume              = 128,
    kSMBTypeMemorySPD                   = 130,
    kSMBTypeOemProcessorType            = 131,
    kSMBTypeOemProcessorBusSpeed        = 132,
	kSMBTypeOemPlatformFeature          = 133,
	kSMBTypeOemSMCVersion				= 134,

	// Structures dropped by RevoBoot.
	kSMBUnused							= 255
};

//
// BIOS Information (Type 0)
//
typedef struct SMBBIOSInformation
{
    SMB_STRUCT_HEADER               // Type 0
    SMBString  vendor;              // BIOS vendor name
    SMBString  version;             // BIOS version
    SMBWord    startSegment;        // BIOS segment start
    SMBString  releaseDate;         // BIOS release date
    SMBByte    romSize;             // (n); 64K * (n+1) bytes
    SMBQWord   characteristics;     // supported BIOS functions
} __attribute__((packed)) SMBBIOSInformation;

//
// System Information (Type 1)
//

typedef struct SMBSystemInformation
{
    // 2.0+ spec (8 bytes)
    SMB_STRUCT_HEADER               // Type 1
    SMBString	manufacturer;
    SMBString	productName;
    SMBString	version;
    SMBString	serialNumber;
    // 2.1+ spec (25 bytes)
    SMBByte		uuid[16];            // can be all 0 or all 1's
    SMBByte		wakeupReason;        // reason for system wakeup
    // 2.4+ spec (27 bytes)
	SMBString	SKUNumber;			// System SKU#
	SMBString	family;				// Mac, Macmini etc
} __attribute__((packed)) SMBSystemInformation;

//
// Base Board (Type 2)
//

typedef struct SMBBaseBoard
{
    SMB_STRUCT_HEADER               // Type 2
    SMBString	manufacturer;
    SMBString	product;
    SMBString	version;
    SMBString	serialNumber;
    SMBString	assetTagNumber;
    SMBByte		featureFlags;
    SMBString	locationInChassis;
    SMBWord		chassisHandle;
    SMBByte		boardType;
    SMBByte		numberOfContainedHandles;
	// 0 - 255 contained handles go here but we do not include
	// them in our structure. Be careful to use numberOfContainedHandles
	// times sizeof(SMBWord) when computing the actual record size,
	// if you need it.
} __attribute__((packed)) SMBBaseBoard;

// Values for boardType in Type 2 records
enum
{
    kSMBBaseBoardUnknown				= 0x01,
    kSMBBaseBoardOther					= 0x02,
    kSMBBaseBoardServerBlade			= 0x03,
    kSMBBaseBoardConnectivitySwitch		= 0x04,
    kSMBBaseBoardSystemMgmtModule		= 0x05,
    kSMBBaseBoardProcessorModule		= 0x06,
    kSMBBaseBoardIOModule				= 0x07,
    kSMBBaseBoardMemoryModule			= 0x08,
    kSMBBaseBoardDaughter				= 0x09,
    kSMBBaseBoardMotherboard			= 0x0A,
    kSMBBaseBoardProcessorMemoryModule	= 0x0B,
    kSMBBaseBoardProcessorIOModule		= 0x0C,
    kSMBBaseBoardInterconnect			= 0x0D,
};


//
// System Enclosure (Type 3)
//

typedef struct SMBSystemEnclosure
{
    SMB_STRUCT_HEADER               // Type 3
    SMBString  manufacturer;
    SMBByte    type;
    SMBString  version;
    SMBString  serialNumber;
    SMBString  assetTagNumber;
    SMBByte    bootupState;
    SMBByte    powerSupplyState;
    SMBByte    thermalState;
    SMBByte    securityStatus;
    SMBDWord   oemDefined;
} __attribute__((packed)) SMBSystemEnclosure;

//
// Processor Information (Type 4)
//

typedef struct SMBProcessorInformation
{
	// 2.0+ spec (26 bytes)
	SMB_STRUCT_HEADER               // Type 4
	SMBString  socketDesignation;
	SMBByte    processorType;       // CPU = 3
	SMBByte    processorFamily;     // processor family enum
	SMBString  manufacturer;
	SMBQWord   processorID;         // based on CPUID
	SMBString  processorVersion;
	SMBByte    voltage;             // bit7 cleared indicate legacy mode
	SMBWord    externalClock;       // external clock in MHz
	SMBWord    maximumClock;        // max internal clock in MHz
	SMBWord    currentClock;        // current internal clock in MHz
	SMBByte    status;
	SMBByte    processorUpgrade;    // processor upgrade enum
	// 2.1+ spec (32 bytes)
	SMBWord    L1CacheHandle;
	SMBWord    L2CacheHandle;
	SMBWord    L3CacheHandle;
	// 2.3+ spec (35 bytes)
	SMBString  serialNumber;
	SMBString  assetTag;
	SMBString  partNumber;
	// 2.5+ spec (40 bytes)
	SMBByte    coreCount;				// Number of cores detected by the BIOS.
	SMBByte    coreEnabled;				// Number of cores that are enabled by the BIOS.
	SMBByte    threadCount;				// Number of threads that are supported by this CPU (not per core).
	SMBWord    processorFuncSupport;	// Defines which functions the processor supports.
	/* 2.6+ spec (42 bytes)
	SMBWord    processorFamily;		*/
} __attribute__((packed)) SMBProcessorInformation;

#define kSMBProcessorInformationMinSize     26

//
// Memory Module Information (Type 6)
// Obsoleted since SMBIOS version 2.1
//

typedef struct SMBMemoryModule
{
    SMB_STRUCT_HEADER               // Type 6
    SMBString  socketDesignation;
    SMBByte    bankConnections;
    SMBByte    currentSpeed;
    SMBWord    currentMemoryType;
    SMBByte    installedSize;
    SMBByte    enabledSize;
    SMBByte    errorStatus;
} __attribute__((packed)) SMBMemoryModule;

#define kSMBMemoryModuleSizeNotDeterminable 0x7D
#define kSMBMemoryModuleSizeNotEnabled      0x7E
#define kSMBMemoryModuleSizeNotInstalled    0x7F

//
// Cache Information (Type 7)
//

typedef struct SMBCacheInformation
{
    SMB_STRUCT_HEADER               // Type 7
    SMBString  socketDesignation;
    SMBWord    cacheConfiguration;
    SMBWord    maximumCacheSize;
    SMBWord    installedSize;
    SMBWord    supportedSRAMType;
    SMBWord    currentSRAMType;
	// 2.1+ spec (12 ??? bytes)
    SMBByte    cacheSpeed;
    SMBByte    errorCorrectionType;
    SMBByte    systemCacheType;
    SMBByte    associativity;
} __attribute__((packed)) SMBCacheInformation;

typedef struct SMBSystemSlot
{
    // 2.0+ spec (12 bytes)
    SMB_STRUCT_HEADER               // Type 9
    SMBString   slotDesignation;
    SMBByte     slotType;
    SMBByte     slotDataBusWidth;
    SMBByte     currentUsage;
    SMBByte     slotLength;
    SMBWord     slotID;
    SMBByte     slotCharacteristics1;
    // 2.1+ spec (13 bytes)
    SMBByte     slotCharacteristics2;
    // 2.6+ spec (17 bytes)
	SMBWord		segmentGroupNumber;
	SMBByte		busNumber;
	SMBByte		deviceFunctionNumber;
} __attribute__((packed)) SMBSystemSlot;

//
// OEM Strings - Type 11 (AppleSMBIOS-43)
//
// Note: Used to add IODeviceTree:/rom@0/apple-rom-version (Data)
//

typedef struct SMBOemStrings
{
    SMB_STRUCT_HEADER               // Length is a fixed value (5)
    SMBByte     count;
} __attribute__((packed)) SMBOemStrings;

//
// Physical Memory Array (Type 16)
//

typedef struct SMBPhysicalMemoryArray
{
    // 2.1+ spec (15 bytes)
    SMB_STRUCT_HEADER               // Type 16
    SMBByte    physicalLocation;    // physical location
    SMBByte    arrayUse;            // the use for the memory array
    SMBByte    errorCorrection;     // error correction/detection method
    SMBDWord   maximumCapacity;     // maximum memory capacity in kilobytes
    SMBWord    errorHandle;         // handle of a previously detected error
    SMBWord    numMemoryDevices;    // number of memory slots or sockets
} __attribute__((packed)) SMBPhysicalMemoryArray;

// Memory Array - Use
enum
{
    kSMBMemoryArrayUseOther             = 0x01,
    kSMBMemoryArrayUseUnknown           = 0x02,
    kSMBMemoryArrayUseSystemMemory      = 0x03,
    kSMBMemoryArrayUseVideoMemory       = 0x04,
    kSMBMemoryArrayUseFlashMemory       = 0x05,
    kSMBMemoryArrayUseNonVolatileMemory = 0x06,
    kSMBMemoryArrayUseCacheMemory       = 0x07
};

// Memory Array - Error Correction Types
enum
{
    kSMBMemoryArrayErrorCorrectionTypeOther         = 0x01,
    kSMBMemoryArrayErrorCorrectionTypeUnknown       = 0x02,
    kSMBMemoryArrayErrorCorrectionTypeNone          = 0x03,
    kSMBMemoryArrayErrorCorrectionTypeParity        = 0x04,
    kSMBMemoryArrayErrorCorrectionTypeSingleBitECC  = 0x05,
    kSMBMemoryArrayErrorCorrectionTypeMultiBitECC   = 0x06,
    kSMBMemoryArrayErrorCorrectionTypeCRC           = 0x07
};

//
// Memory Device (Type 17)
//

typedef struct SMBMemoryDevice
{
    // 2.1+ spec (21 bytes)
    SMB_STRUCT_HEADER               // Type 17
    SMBWord    arrayHandle;         // handle of the parent memory array
    SMBWord    errorHandle;         // handle of a previously detected error
    SMBWord    totalWidth;          // total width in bits; including ECC bits
    SMBWord    dataWidth;           // data width in bits
    SMBWord    memorySize;          // bit15 is scale, 0 = MB, 1 = KB
    SMBByte    formFactor;          // memory device form factor
    SMBByte    deviceSet;           // parent set of identical memory devices
    SMBString  deviceLocator;       // labeled socket; e.g. "SIMM 3"
    SMBString  bankLocator;         // labeled bank; e.g. "Bank 0" or "A"
    SMBByte    memoryType;          // type of memory
    SMBWord    memoryTypeDetail;    // additional detail on memory type
    // 2.3+ spec (27 bytes)
    SMBWord    memorySpeed;         // speed of device in MHz (0 for unknown)
    SMBString  manufacturer;
    SMBString  serialNumber;
    SMBString  assetTag;
    SMBString  partNumber;
    // 2.6+ spec (28 bytes)
    SMBByte    attributes;
} __attribute__((packed)) SMBMemoryDevice;

///
/// Memory Array Mapped Address (Type 19).
///
/// This structure provides the address mapping for a Physical Memory Array.
/// One structure is present for each contiguous address range described.
///
typedef struct SMBMemoryArrayMappedAddress
{
	SMB_STRUCT_HEADER				// Type 19
	SMBDWord	StartingAddress;
	SMBDWord	EndingAddress;
	SMBWord		MemoryArrayHandle;
	SMBByte		PartitionWidth;
	//
	// Added for SMBIOS v2.7
	//
	// SMBQWord	ExtendedStartingAddress;
	// SMBQWord	ExtendedEndingAddress;
} __attribute__((packed))  SMBMemoryArrayMappedAddress;

//
// Firmware Volume Description (Apple Specific - Type 128)
//

enum
{
    FW_REGION_RESERVED   = 0,
    FW_REGION_RECOVERY   = 1,
    FW_REGION_MAIN       = 2,
    FW_REGION_NVRAM      = 3,
    FW_REGION_CONFIG     = 4,
    FW_REGION_DIAGVAULT  = 5,

    NUM_FLASHMAP_ENTRIES = 8
};

typedef struct FW_REGION_INFO
{
    SMBDWord   StartAddress;
    SMBDWord   EndAddress;
} __attribute__((packed)) FW_REGION_INFO;

typedef struct SMBFirmwareVolume
{
    SMB_STRUCT_HEADER               // Type 0x80/128
    SMBByte           RegionCount;
    SMBByte           Reserved[3];
    SMBDWord          FirmwareFeatures;
    SMBDWord          FirmwareFeaturesMask;
    SMBByte           RegionType[ NUM_FLASHMAP_ENTRIES ];
    FW_REGION_INFO    FlashMap[   NUM_FLASHMAP_ENTRIES ];
} __attribute__((packed)) SMBFirmwareVolume;

//
// Memory SPD Data   (Apple Specific - Type 130)
//

typedef struct SMBMemorySPD
{
	SMB_STRUCT_HEADER               // Type 0x82/130
	SMBWord           Type17Handle;
	SMBWord           Offset;
	SMBWord           Size;
	SMBWord           Data[];
} __attribute__((packed)) SMBMemorySPD;


#if (DEBUG_SMBIOS == 4)
static const char * SMBMemoryDeviceTypes[] =
{
    "RAM",          /* 00h  Undefined */
    "RAM",          /* 01h  Other */
    "RAM",          /* 02h  Unknown */
    "DRAM",         /* 03h  DRAM */
    "EDRAM",        /* 04h  EDRAM */
    "VRAM",         /* 05h  VRAM */
    "SRAM",         /* 06h  SRAM */
    "RAM",          /* 07h  RAM */
    "ROM",          /* 08h  ROM */
    "FLASH",        /* 09h  FLASH */
    "EEPROM",       /* 0Ah  EEPROM */
    "FEPROM",       /* 0Bh  FEPROM */
    "EPROM",        /* 0Ch  EPROM */
    "CDRAM",        /* 0Dh  CDRAM */
    "3DRAM",        /* 0Eh  3DRAM */
    "SDRAM",        /* 0Fh  SDRAM */
    "SGRAM",        /* 10h  SGRAM */
    "RDRAM",        /* 11h  RDRAM */
    "DDR SDRAM",    /* 12h  DDR */
    "DDR2 SDRAM",   /* 13h  DDR2 */
    "DDR2 FB-DIMM", /* 14h  DDR2 FB-DIMM */
    "RESERVED",		/* 15h  Reserved */
    "RESERVED",		/* 16h  Reserved */
    "RESERVED",		/* 17h  Reserved */
    "DDR3",			/* 18h  DDR3, chosen in [5776134] */
    "FBD2",			/* 19h  FBD2 */
    "DDR4",			/* 1Ah  DDR4 */
    "LPDDR",		/* 1Bh  LPDDR */
    "LPDDR2",		/* 1Ch  LPDDR2 */
    "LPDDR3",		/* 1Dh  LPDDR3 */
    "LPDDR3",		/* 1Eh  LPDDR5 */
};

static const int kSMBMemoryDeviceTypeCount = sizeof(SMBMemoryDeviceTypes) / sizeof(SMBMemoryDeviceTypes[0]);
#endif


//
// OEM – Apple Processor Type (type 0x83/131)
//

struct SMBOemProcessorType
{
	SMB_STRUCT_HEADER
	SMBWord		ProcessorType;
} __attribute__((packed)) SMBOemProcessorType;


//
// OEM – Apple Processor Bus Speed (type 0x84/132)
//
struct SMBOemProcessorBusSpeed
{
	SMB_STRUCT_HEADER
	SMBWord		ProcessorBusSpeed;   // MT/s unit
} __attribute__((packed)) SMBOemProcessorBusSpeed;


//
// OEM – Apple Platform Features (type 0x85/133 / AppleSMBIOS-43)
//
struct SMBOemPlatformFeature
{
	SMB_STRUCT_HEADER
	SMBWord		PlatformFeature;
} __attribute__((packed)) SMBOemPlatformFeature;

//
// OEM – Apple SMC Version (type 0x86/134)
//
struct SMBOemSMCVersion
{
	SMB_STRUCT_HEADER
	SMBString	SMCVersion;
} __attribute__((packed)) SMBOemSMCVersion;
