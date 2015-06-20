/*
 * platform.h
 *
 * Updates:
 *
 *			- SMBIOS data logic moved to preprocessor code (Pike R. Alpha, October 2012).
 *			- Now includes: RevoBoot/libsaoi/i386/SMBIOS/model_data.h (Pike R. Alpha, October 2012).
 *			- DDR4 support added (Pike R. Alpha, June 2014).
 *			- Yosemite support added (Pike R. Alpha, June 2014).
 *			- El Capitan support added (Pike R. Alpha, June 2015).
 *
 */

#ifndef __LIBSAIO_PLATFORM_H
#define __LIBSAIO_PLATFORM_H

#define __LP64__	1

#include "libsaio.h"
#include "cpu/essentials.h"
#include "efi/essentials.h"
#include "efi/efi.h"
#include "device_tree.h"



//------------------------------------------------------------------------------

#define	SNOW_LEOPARD			1	// Snow Leopard.
#define LION					2	// Lion (the default).
#define MOUNTAIN_LION			6	// Mountain Lion (includes Lion changes).
#define MAVERICKS				10	// Mavericks (includes Lion changes).
#define YOSEMITE				26	// Yosemite (incl. Lion/Mavericks changes).
#define EL_CAPITAN				62	// El Capitan (incl. Lion/Mavericks/Yosemite changes).

//------------------------------------------------------------------------------

#define SMB_MEM_TYPE_DDR2		19
#define SMB_MEM_TYPE_FBDIMM		20
#define SMB_MEM_TYPE_DDR3		24
#define SMB_MEM_TYPE_DDR4		26

//------------------------------------------------------------------------------

#define SMB_MEM_BANK_EMPTY		1			// For empty slots.
#define SMB_MEM_SIZE_1GB		1024
#define SMB_MEM_SIZE_2GB		(SMB_MEM_SIZE_1GB * 2)
#define SMB_MEM_SIZE_4GB		(SMB_MEM_SIZE_1GB * 4)
#define SMB_MEM_SIZE_8GB		(SMB_MEM_SIZE_1GB * 8)
#define SMB_MEM_SIZE_16GB		(SMB_MEM_SIZE_1GB * 16)
#define SMB_MEM_SIZE_32GB		(SMB_MEM_SIZE_1GB * 32)	// May not be supported!
#define SMB_MEM_SIZE_64GB		(SMB_MEM_SIZE_1GB * 64)	// May not be supported!

//------------------------------------------------------------------------------
// All currently supported models are defined below.
//------------------------------------------------------------------------------

#define IMAC					1
#define MACBOOK					2
#define MACBOOK_AIR				4
#define MACBOOK_PRO				8
#define MACMINI					16
#define MACPRO					32

//------------------------------------------------------------------------------
// Additional model selectors to select a specific target model.
//------------------------------------------------------------------------------

#define IMAC_111				(IMAC | ( 1 << 15))
#define IMAC_121				(IMAC | ( 2 << 15))
#define IMAC_122				(IMAC | ( 3 << 15))
#define IMAC_131				(IMAC | ( 4 << 15))
#define IMAC_132				(IMAC | ( 5 << 15))
#define IMAC_141				(IMAC | ( 6 << 15))
#define IMAC_142				(IMAC | ( 7 << 15))
#define IMAC_143				(IMAC | ( 8 << 15))
#define IMAC_144				(IMAC | ( 9 << 15))
#define IMAC_152				(IMAC | (10 << 15))
#define IMAC_151				 IMAC						// Defaults to iMac15,1

#define MACBOOK_41				(MACBOOK | ( 1 << 15))
#define MACBOOK_81				(MACBOOK | ( 2 << 15))		// Defaults to MacBook8,1

#define MACBOOK_AIR_41			(MACBOOK_AIR | (1 << 15))
#define MACBOOK_AIR_42			(MACBOOK_AIR | (2 << 15))
#define MACBOOK_AIR_51			(MACBOOK_AIR | (3 << 15))
#define MACBOOK_AIR_52			(MACBOOK_AIR | (4 << 15))
#define MACBOOK_AIR_61			(MACBOOK_AIR | (5 << 15))
#define MACBOOK_AIR_62			(MACBOOK_AIR | (6 << 15))
#define MACBOOK_AIR_71			(MACBOOK_AIR | (7 << 15))
#define MACBOOK_AIR_72			 MACBOOK_AIR				// Defaults to MacBookAir7,2

#define MACBOOK_PRO_61			(MACBOOK_PRO | ( 1 << 15))
#define MACBOOK_PRO_81			(MACBOOK_PRO | ( 2 << 15))
#define MACBOOK_PRO_82			(MACBOOK_PRO | ( 3 << 15))
#define MACBOOK_PRO_83			(MACBOOK_PRO | ( 4 << 15))
#define MACBOOK_PRO_91			(MACBOOK_PRO | ( 5 << 15))
#define MACBOOK_PRO_92			(MACBOOK_PRO | ( 6 << 15))
#define MACBOOK_PRO_101			(MACBOOK_PRO | ( 7 << 15))
#define MACBOOK_PRO_102			(MACBOOK_PRO | ( 8 << 15))
#define MACBOOK_PRO_111			(MACBOOK_PRO | ( 9 << 15))
#define MACBOOK_PRO_112			(MACBOOK_PRO | (10 << 15))
#define MACBOOK_PRO_113			(MACBOOK_PRO | (11 << 15))
#define MACBOOK_PRO_121			 MACBOOK_PRO				// Defaults to MacBookPro12,1

#define MACMINI_41				(MACMINI | (1 << 15))
#define MACMINI_51				(MACMINI | (2 << 15))
#define MACMINI_52				(MACMINI | (3 << 15))
#define MACMINI_53				(MACMINI | (4 << 15))
#define MACMINI_61				(MACMINI | (5 << 15))
#define MACMINI_62				(MACMINI | (6 << 15))
#define MACMINI_71				 MACMINI					// Defaults to Macmini7,1

#define MACPRO_31				(MACPRO | (1 << 15))
#define MACPRO_41				(MACPRO | (2 << 15))
#define MACPRO_51				(MACPRO | (3 << 15))
#define MACPRO_61				 MACPRO						// Defaults to MacPro6,1

#if ((TARGET_MODEL & MACPRO) == MACPRO)
	#define PM_PROFILE_OVERRIDE	3
#else
	#define PM_PROFILE_OVERRIDE	1
#endif

//------------------------------------------------------------------------------

// #define	LOAD_MODEL_SPECIFIC_STATIC_DATA	(LOAD_MODEL_SPECIFIC_ACPI_DATA || LOAD_MODEL_SPECIFIC_EFI_DATA || LOAD_MODEL_SPECIFIC_SMBIOS_DATA)

#include "smbios/model_data.h"

//------------------------------------------------------------------------------

#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite and El Capitan.
	#define kKernelCachePath		"/System/Library/Prelinkedkernels"
	#define kKernelCache			"prelinkedkernel"
#else
	#define kKernelCachePath		"/System/Library/Caches/com.apple.kext.caches/Startup"
	#define kKernelCache			"kernelcache"
#endif

//------------------------------------------------------------------------------

#define EFI_SMBIOS_TABLE_GUID	{ 0xeb9d2d31, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

#define EFI_ACPI_20_TABLE_GUID	{ 0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 } }

#if INCLUDE_MPS_TABLE
	#define EFI_MPS_TABLE_GUID	{ 0xeb9d2d2f, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }
#endif

//------------------------------------------------------------------------------
// Number of physical memory slots.

#ifndef STATIC_RAM_SLOTS
	#define MAX_SLOTS	4
#else
	#define MAX_SLOTS	STATIC_RAM_SLOTS		// Defined in config/settings.h
#endif

//==============================================================================
// Kernel boot modes (moved from boot.h)

enum
{
	kBootModeNormal = 0,
	kBootModeSafe   = 1,
	kBootModeSecure = 2,
	kBootModeQuiet  = 4
};

//==============================================================================

typedef struct _RamSlotInfo_t
{
	uint32_t		Size;						// Module size in MB
	uint32_t		Frequency;					// Frequency in Mhz.
	const char *	Vendor;
	const char *	PartNumber;
	const char *	SerialNumber;
	char *			spd;						// SPD Dump
	bool			InUse;
	uint8_t			Type;
	uint8_t			BankConnections;			// Table type 6, see (3.3.7)
	uint8_t			BankConnCnt;
} RamSlotInfo_t;


//==============================================================================

typedef struct _PlatformInfo_t
{
	cpu_type_t			ArchCPUType;			// Replacement for gArchCPUType
	
	int					AddressWidth;
	
	int					Type;					// Initialized in platform.c to 2 for MacBook [Pro/Air]
												// or 1 for desktop PC's like: MacPro, Mac mini and iMac.
	
	long				LastKernelAddr;			// Used in AllocateKernelMemory
	
	char *				RevoBootVersionInfo;	// Introduced in Revolution v0.6.45
	
	int					OSType;					// Type of Operating System.
	
	char *				OSVersion;				// OS version initialized with "10.6" in platform.c and
												// later updated in boot.c with the actual version info.
	
	char *				ModelID;				// Initialized in platform.c and used in boot.c
	char *				CommaLessModelID;		// Initialized in platform.c and used in i386/libsaio/ACPI/patcher.h,
	char *				KextFileName;			// Initialized and used in drivers.c
	char *				KextFileSpec;			// Initialized and used in drivers.c
	char *				KextPlistSpec;			// Initialized and used in drivers.c
	char *				KernelCachePath;		// Initialized in platform.c and used in boot.c, driver.c
	char *				HelperPath;				// Initialized in stringTable.c and used in boot.c 	
#if PRE_LINKED_KERNEL_SUPPORT
	bool				KernelCacheSpecified;	// Set to indicate that a full path is specified.
#endif
	
	int					BIOSDevice;				// Initialized in platform.c (formely know as gBIOSDev).

	long				BootMode;				// Initialized in platform.c

	BVRef				BootVolume;				// Initialized in disk.c
	BVRef				BootPartitionChain;		// Initialized in sys.c
	BVRef				RootVolume;				// Initialized in disk.c (used in sys.c).
	
	bool				BootRecoveryHD;			//
	
	uint32_t			allocatedVRAM;			// Amount of allocated graphics memory (UEFI-BIOS settings).

	uint8_t *			UUID;					// Allocated/set in RevoBoot/i386/libsaio/smbios/[dynamic/static]_data.h

	struct ACPI									// Used in acpi_patcher.h
	{
		uint8_t			Type;					// System type. Referring to FACP->PM_Profile.
		
		EFI_GUID		Guid;
		
		EFI_UINT		BaseAddress;			// Either 32 or 64-bit (depends on platform info).
	} ACPI;
	
	// Copied from: chameleon/i386/libsaio/platform.h
	struct CPU
	{
		bool		Mobile;						// Set to true (in cpu/dynamic_data.h) for Mobile CPU's.
		uint16_t	Type;						// CPU type ('cpu-type') used in the SMBIOS patcher.
		uint32_t	Features;					// CPU Features like MMX, SSE2, VT, MobileCPU
		uint32_t	Vendor;						// Vendor
		uint32_t	Signature;					// Signature
		uint32_t	Stepping;					// Stepping
		uint32_t	Model;						// Model
		uint32_t	ExtModel;					// Extended Model
		uint32_t	Family;						// Family
		uint32_t	ExtFamily;					// Extended Family
		uint32_t	NumCores;					// Number of cores per package
		uint32_t	NumThreads;					// Number of threads per package
		
#if USE_STATIC_CPU_DATA == 0 && DEBUG_CPU
		uint8_t		CurrCoef;					// Current Multiplier (busratio).
		uint8_t		MaxCoef;					// Max multiplier
		uint8_t		CurrDiv;
		uint8_t		MaxDiv;
#endif
		uint64_t	TSCFrequency;				// TSC Frequency Hz
		uint64_t	FSBFrequency;				// FSB Frequency Hz
		uint64_t	CPUFrequency;				// CPU Frequency Hz
		
		uint32_t	QPISpeed;					// QuickPath Interconnect Bus Speed
		
		uint8_t		NumberOfTurboRatios;		// Jeroen: initialized in cpu.c and used in ACPI/ssdt_pr_generator.h
		
		uint8_t		CoreTurboRatio[STATIC_CPU_NumCores]; // Used in cpu Intel/dynamic_data.h and ACPI/ssdt_pr_generator.h
		
		uint8_t		MinBusRatio;				// Used in ACPI/apss_generator.h
		uint8_t		MaxBusRatio;				// Used in cpu/Intel/dynamic_data.h and ACPI/ssdt_pr_generator.h
		
#if AUTOMATIC_SSDT_PR_CREATION || DEBUG_CPU_TDP
		uint8_t		TDP;						// Used in cpu/Intel/dynamic_data.h and ACPI/ssdt_pr_generator.h
#endif
		char		BrandString[48];			// Brand/frequency string
		uint32_t	ID[MAX_CPUID_LEAVES][4];	// CPUID 0..4, 80..81 Raw Values
	} CPU;
	
	struct DMI									// Patch by: Asere / Rekursor.
	{
		int		RAMSlotsPopulated;				// Number of memory slots populated by SMBIOS.
		int		RAMSlotsSupported;				// Total number of on-board memory slots.
		int		RAMSlotsActive;					// Total number of active slots (with module inserted).
		int		MODULE[MAX_SLOTS];				// Information and SPD mapping for each slot.
	} DMI;
	
#if INCLUDE_MPS_TABLE
	struct MPS									// Multi Procesor Table
	{
		EFI_GUID	Guid;
		
		EFI_UINT	BaseAddress;				// Either 32 or 64-bit (depends on platform info).
	} MPS;
#endif // INCLUDE_MP_TABLE
	
	struct RAM									// Patch by: Asere / Rekursor.
	{
		uint64_t	Frequency;					// RAM Frequency
		uint32_t	Divider;					// Memory divider
		uint8_t		CAS;						// CAS 1/2/2.5/3/4/5/6/7
		uint8_t		TRC;
		uint8_t		TRP;
		uint8_t		RAS;
		uint8_t		Channels;					// Channel Configuration Single, Dual or Triple
		uint8_t		SlotCount;					// Previously NoSlots; - Maximum no of slots available
		uint8_t		Type;						// Standard SMBIOS v2.5 Memory Type
		/* Remove me */
		char *		BrandString;				// Branding String Memory Controller
		RamSlotInfo_t	MODULE[MAX_SLOTS];		// Information about each slot
	} RAM;
	
	struct DT									// Device Tree
	{
		Node *	RootNode;						// Path: /
	} DT;

	struct EFI
	{
		EFI_SYSTEM_TABLE * SystemTable;			// Used to re-calculate the checksum at the end of the run.
		
		struct Nodes
		{
			Node *	Chosen;						// Path: /chosen
			Node *	MemoryMap;					// Path: /chosen/memory-map
			
			// EFI specific stuff.
			Node *	ConfigurationTable;			// Path: /efi/configuration-table
			// Node *	ACPI_Tables;				// Path: /efi/configuration-table/ACPI Tables
			Node *	RuntimeServices;			// Path: /efi/runtime-services
			Node *	Platform;					// Path: /efi/platform
		} Nodes;
	} EFI;
	
	struct SMBIOS
	{
		EFI_GUID	Guid;
		
		EFI_UINT	BaseAddress;				// Either 32 or 64-bit (depends on platform info).
		
		/* UInt8	Anchor[4];					// DHP: Not used yet =]\._oOo_./[=
		 UInt8	Checksum;
		 UInt8	EntryPointLength;
		 UInt8	MajorVersion;
		 UInt8	MinorVersion;
		 UInt16	MaxStructureSize;
		 UInt8	EntryPointRevision;
		 UInt8	FormattedArea[5];
		 
		 struct DMI
		 {
		 UInt8	Anchor[5];
		 UInt8	Checksum;
		 UInt16	TableLength;
		 UInt32	TableAddress;
		 UInt16	StructureCount;
		 UInt8	CcdRevision;
		 } DMI; */
	} SMBIOS;
	
} PlatformInfo_t;


//------------------------------------------------------------------------------

/* cpu/static_data.h & cpu/dynamic_data.h */
extern void initCPUStruct(void);

/* platform.c */
extern PlatformInfo_t	gPlatform;

extern void initPlatform(int biosDevice, bool bootRecoveryHD);

extern cpu_type_t getArchCPUType(void);

#endif /* !__LIBSAIO_PLATFORM_H */
