/*
 * Original source code (dsdt_patcher) by mackerintel (2008)
 * Overhaul by Master Chief in 2009
 *
 * Refactorizing for Revolution done by DHP in 2010/2011
 */

#ifndef __LIBSAIO_ACPI_ESSENTIALS_H
#define __LIBSAIO_ACPI_ESSENTIALS_H

#define UINT64_LE_FROM_CHARS(a,b,c,d,e,f,g,h) ( \
	((uint64_t)h << 56)	| ((uint64_t)g << 48) | \
	((uint64_t)f << 40) | ((uint64_t)e << 32) | \
	((uint64_t)d << 24) | ((uint64_t)c << 16) | \
	((uint64_t)b <<  8) | ((uint64_t)a <<  0) )

#define ACPI_SIGNATURE_UINT64_LE UINT64_LE_FROM_CHARS('R','S','D',' ','P','T','R',' ')


#if ACPI_10_SUPPORT
	#define	ADDRESS_WIDTH 4
	#define	RSDP_LENGTH 20
	#define ACPI_RXSDT_ADDRESS (uint32_t)factoryRSDP->RsdtAddress
	#define VALID_ADDRESS(rsdp, rsdt) ((uint32_t)rsdt != 0xffffffff)

	typedef uint32_t ENTRIES;
#else
	#define	ADDRESS_WIDTH 8
	#define	RSDP_LENGTH 36
	#define ACPI_RXSDT_ADDRESS (uint32_t)factoryRSDP->XsdtAddress
	#define VALID_ADDRESS(rsdp, xsdt) (((uint64_t)rsdp->XsdtAddress) < 0xffffffff)

	typedef uint64_t ENTRIES;
#endif


#if PATCH_ACPI_TABLE_DATA
//------------------------------------------------------------------------------

#include "acpi/static_data.h"

#define _PTS_SIGNATURE	0x5354505F
#define _WAK_SIGNATURE	0x4B41575F

extern bool replaceTable(ENTRIES * xsdtEntries, int entryIndex, int tableIndex);
extern bool patchFACPTable(ENTRIES * xsdtEntries, int tableIndex, int dropOffset);


typedef struct static_acpi_2_table
{
	char	name[10];
	void	* table;
	int		tableLength;
	bool	loaded;
	void	* tableAddress;
#if LOAD_MODEL_SPECIFIC_ACPI_DATA
	char	fileName[32];
#endif
} __attribute__((packed)) ACPITable;


static ACPITable customTables[] =
{
#if LOAD_MODEL_SPECIFIC_ACPI_DATA
	// Essential tables.
	{ "APIC",		APIC_Table,			sizeof(APIC_Table),			false,	0,	""	},
	{ "DMAR",		DMAR_Table,			sizeof(DMAR_Table),			false,	0,	""	},
	{ "ECDT",		ECDT_Table,			sizeof(ECDT_Table),			false,	0,	""	},
	{ "HPET",		HPET_Table,			sizeof(HPET_Table),			false,	0,	""	},
	{ "MCFG",		MCFG_Table,			sizeof(MCFG_Table),			false,	0,	""	},
	{ "SBST",		SBST_Table,			sizeof(SBST_Table),			false,	0,	""	},
	{ "SSDT",		SSDT_Table,			sizeof(SSDT_Table),			false,	0,	""	},

	// Special essential tables.
	{ "DSDT",		DSDT_Table,			sizeof(DSDT_Table),			false,	0,	""	},
	{ "FACS",		FACS_Table,			sizeof(FACS_Table),			false,	0,	""	},

	// Optional tables.
	{ "APIC-1",		APIC2_Table,		sizeof(APIC2_Table),		false,	0,	""	},
	{ "SSDT_GPU",	SSDT_GPU_Table,		sizeof(SSDT_GPU_Table),		false,	0,	""	},
	{ "SSDT_PR",	SSDT_PR_Table,		sizeof(SSDT_PR_Table),		false,	0,	""	},
	{ "SSDT_SATA",	SSDT_SATA_Table,	sizeof(SSDT_SATA_Table),	false,	0,	""	},
	{ "SSDT_USB",	SSDT_USB_Table,		sizeof(SSDT_USB_Table),		false,	0,	""	},
	{ "",			0,					0,							false,	0,	""	}
#else
	// Essential tables.
	{ "APIC",		APIC_Table,			sizeof(APIC_Table),			false,	0	},
	{ "DMAR",		DMAR_Table,			sizeof(DMAR_Table),			false,	0	},
	{ "ECDT",		ECDT_Table,			sizeof(ECDT_Table),			false,	0	},
	{ "HPET",		HPET_Table,			sizeof(HPET_Table),			false,	0	},
	{ "MCFG",		MCFG_Table,			sizeof(MCFG_Table),			false,	0	},
	{ "SBST",		SBST_Table,			sizeof(SBST_Table),			false,	0	},
	{ "SSDT",		SSDT_Table,			sizeof(SSDT_Table),			false,	0	},
	
	// Special essential tables.
	{ "DSDT",		DSDT_Table,			sizeof(DSDT_Table),			false,	0	},
	{ "FACS",		FACS_Table,			sizeof(FACS_Table),			false,	0	},
	
	// Optional tables.
	{ "APIC-1",		APIC2_Table,		sizeof(APIC2_Table),		false,	0	},
	{ "SSDT_GPU",	SSDT_GPU_Table,		sizeof(SSDT_GPU_Table),		false,	0	},
	{ "SSDT_PR",	SSDT_PR_Table,		sizeof(SSDT_PR_Table),		false,	0	},
	{ "SSDT_SATA",	SSDT_SATA_Table,	sizeof(SSDT_SATA_Table),	false,	0	},
	{ "SSDT_USB",	SSDT_USB_Table,		sizeof(SSDT_USB_Table),		false,	0	},
	{ "",			0,					0,							false,	0	}
#endif
};


// Keep this in sync with the above array.
typedef enum
{
	NONE = -1,

	// Essential tables.
	APIC,
	DMAR,
    ECDT,
	HPET,
	MCFG,
	SBST,
	SSDT,

	// Secundary tables.
    DSDT,
	FACS,

	// Optional tables.
	APIC2,
	SSDT_GPU,
	SSDT_PR,
	SSDT_SATA,
	SSDT_USB,
} injectableTables;


typedef enum 
{
	kDoNothing		= 0,
	kAddTable		= 1,
	kCopyTable		= 2,
	kDropTable		= 4,
	kPatchTable		= 8,
	kReplaceTable	= 16
} acpi_table_actions;


// ACPI table signatures in little endian format.
#define APIC_TABLE_SIGNATURE 0x43495041
#define DMAR_TABLE_SIGNATURE 0x52414d44
#define DSDT_TABLE_SIGNATURE 0x54445344
#define ECDT_TABLE_SIGNATURE 0x54444345
#define FACP_TABLE_SIGNATURE 0x50434146
#define FACS_TABLE_SIGNATURE 0x53434146
#define HPET_TABLE_SIGNATURE 0x54455048
#define MCFG_TABLE_SIGNATURE 0x4746434d
#define RSDP_TABLE_SIGNATURE 0x50445352
#define RSDT_TABLE_SIGNATURE 0x54445352
#define SBST_TABLE_SIGNATURE 0x54534253
#define SSDT_TABLE_SIGNATURE 0x54445353
#define XSDT_TABLE_SIGNATURE 0x54445358

typedef struct acpi_2_tables
{
	uint8_t		type;
	uint32_t	tableSignature;
	bool		(*tableAction)(ENTRIES * xsdtEntries, int tableIndex, int dropOffset); // , int * customTableCount);
	uint8_t		action;
} __attribute__((packed)) ACPITables;


static ACPITables essentialTables[] =
{
	{ APIC, APIC_TABLE_SIGNATURE,	replaceTable,		kReplaceTable | kAddTable	},
#if DROP_FACTORY_DMAR_TABLE
	{ DMAR, DMAR_TABLE_SIGNATURE,	NULL,				kDropTable					},
#else
	{ DMAR, DMAR_TABLE_SIGNATURE,	NULL,				kReplaceTable | kAddTable	},
#endif
	{ NONE,	FACP_TABLE_SIGNATURE,	patchFACPTable,		kPatchTable					},
	{ HPET, HPET_TABLE_SIGNATURE,	replaceTable,		kReplaceTable				},
	{ MCFG, MCFG_TABLE_SIGNATURE,	NULL,				kReplaceTable				},
	{ NONE,	RSDT_TABLE_SIGNATURE,	NULL,				kDoNothing					},
#if DROP_FACTORY_SSDT_TABLES
	{ SSDT, SSDT_TABLE_SIGNATURE,	NULL,				kDropTable					},
#elif REPLACE_EXISTING_SSDT_TABLES 
	{ SSDT, SSDT_TABLE_SIGNATURE,	replaceTable,		kReplaceTable				},
#else
	{ SSDT, SSDT_TABLE_SIGNATURE,	NULL,				kAddTable					},
#endif
	{ NONE,	XSDT_TABLE_SIGNATURE,	NULL,				kDoNothing					},
	{ ECDT, ECDT_TABLE_SIGNATURE,	replaceTable,		kReplaceTable				},
	{ SBST, SBST_TABLE_SIGNATURE,	replaceTable,		kReplaceTable				},
	{ 0,	0,						NULL,				0							}
};


typedef struct acpi_2_rsdt
{
	char            Signature[4];
	uint32_t        Length;
	uint8_t         Revision;
	uint8_t         Checksum;
	char            OEMID[6];
	char            OEMTableID[8];
	uint32_t        OEMRevision;
	uint32_t        CreatorID;
	uint32_t        CreatorRevision;
} __attribute__((packed)) ACPI_RSDT;


typedef struct acpi_2_ssdt
{
	char            Signature[4];
	uint32_t        Length;
	uint8_t         Revision;
	uint8_t         Checksum;
	char            OEMID[6];
	char            OEMTableId[8];
	uint32_t        OEMRevision;
	uint32_t        CreatorId;
	uint32_t        CreatorRevision;
} __attribute__((packed)) ACPI_SSDT, ACPI_DSDT;

//------------------------------------------------------------------------------
#endif // PATCH_ACPI_TABLE_DATA


typedef struct acpi_2_rsdp
{
    char            Signature[8];
    uint8_t         Checksum;
    char            OEMID[6];
    uint8_t         Revision;
    uint32_t        RsdtAddress;
	
    uint32_t        Length;
    uint64_t        XsdtAddress;
    uint8_t         ExtendedChecksum;
    char            Reserved[3];
} __attribute__((packed)) ACPI_RSDP;


typedef struct acpi_2_xsdt
{
	char            Signature[4];
	uint32_t        Length;
	uint8_t         Revision;
	uint8_t         Checksum;
	char            OEMID[6];
	char            OEMTableID[8];
	uint32_t        OEMRevision;
	uint32_t        CreatorID;
	uint32_t        CreatorRevision;
} __attribute__((packed)) ACPI_XSDT;


typedef struct ACPI_GAS								// ACPI General Address Structure.
{
	uint8_t			AddressSpaceID;
	uint8_t			RegisterBitWidth;
	uint8_t			RegisterBitOffset;
	uint8_t			RegisterAccessSize;
	uint64_t		Address;						// This can't be right for 32-bit only platforms?!?
} __attribute__((packed)) GAS;


typedef struct acpi_2_fadt
{
	char            Signature[4];					// FADT
	uint32_t        Length;							// Length varies per revision.
	uint8_t         Revision;						// 1-5.
	uint8_t         Checksum;
	char            OEMID[6];
	char            OEMTableID[8];
	uint32_t        OEMRevision;
	uint32_t        CreatorID;
	uint32_t        CreatorRevision;
	uint32_t        FIRMWARE_CTRL;					// 32-bit physical address of the FACS.
	uint32_t        DSDT;							// 32-bit physical address of the DSDT.

	uint8_t         Model;							// Use 0 for ACPI 2.0 and greater. May use 1 to maintain 
													// compatibility with ACPI 1.0 platforms, but this field
													// was renamed (to Reserved) and eliminated in ACPI 2.0 

	uint8_t         PM_Profile;						// Unspecified 0, Desktop 1, Mobile 2, Workstation 4,
													// Enterprise Server 4, SOHO Server 5, Appliance PC 6,
													// Performance Server 7 and values greater than 7 
													// are Reserved (and thus should not be used).
	uint16_t		SCI_Interrupt;
	uint32_t		SMI_Command_Port;
	uint8_t			ACPI_Enable;
	uint8_t			ACPI_Disable;
	uint8_t			S4BIOS_Command;
	uint8_t			PState_Control;
	uint32_t		PM1A_Event_Block_Address;
	uint32_t		PM1B_Event_Block_Address;
	uint32_t		PM1A_Control_Block_Address;
	uint32_t		PM1B_Control_Block_Address;
	uint32_t		PM2_Control_Block_Address;
	uint32_t		PM_Timer_Block_Address;
	uint32_t		GPE0_Block_Address;
	uint32_t		GPE1_Block_Address;
	uint8_t			PM1_Event_Block_Length;
	uint8_t			PM1_Control_Block_Length;
	uint8_t			PM2_Control_Block_Length;
	uint8_t			PM_Timer_Block_Length;
	uint8_t			GPE0_Block_Length;
	uint8_t			GPE1_Block_Length;
	uint8_t			GPE1_Base_Offset;
	uint8_t			CST_Support;
	uint16_t		C2_Latency;
	uint16_t		C3_Latency;
	uint16_t		CPU_Cache_Size;
	uint16_t		Cache_Flush_Stride;
	uint8_t			Duty_Cycle_Offset;
	uint8_t			Duty_Cycle_Width;
	uint8_t			RTC_Day_Alarm_Index;
	uint8_t			RTC_Month_Alarm_Index;
	uint8_t			RTC_Century_Index;
	uint16_t		Boot_Flags;
	uint8_t			Reserved_1;						// Must be 0.
	uint32_t        Flags;

	uint8_t         ResetSpaceID;
	uint8_t         ResetBitWidth;
	uint8_t         ResetBitOffset;
	uint8_t         ResetAccessWidth;
	uint64_t        ResetAddress;
	uint8_t         ResetValue;

	uint8_t         Reserved_2[3];					// Must be 0.
	
	uint64_t	    X_FIRMWARE_CTRL;				// 64-bit physical address of the FACS.
	uint64_t	    X_DSDT;							// 64-bit physical address of the DSDT.
	
	GAS				X_PM1a_EVT_BLK;
	GAS				X_PM1b_EVT_BLK;
	GAS				X_PM1a_CNT_BLK;
	GAS				X_PM1b_CNT_BLK;
	GAS				X_PM2_CNT_BLK;
	GAS				X_PM_TMR_BLK;
	GAS				X_GPE0_BLK;
	GAS				X_GPE1_BLK;
} __attribute__((packed)) ACPI_FADT;


#endif /* !__LIBSAIO_ACPI_ESSENTIALS_H */
