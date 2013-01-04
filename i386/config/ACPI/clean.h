/*
 * Copyright (c) 2009 Master Chief. All rights reserved.
 *
 * Note: This is an essential part of the build process for Revolution v0.6.43 and greater.
 *
 *
 * Latest cleanups and additional directives added by DHP in 2011
 */


//--------------------------------------------------------- ESSENTIAL ACPI TABLES -------------------------------------------------------------


#if STATIC_APIC_TABLE_INJECTION
	#define STATIC_APIC_TABLE_DATA \
	/* 0x0000 */	// Insert your APIC table replacement here (optional).
#endif


#if STATIC_ECDT_TABLE_INJECTION
	#define STATIC_ECDT_TABLE_DATA \
	/* 0x0000 */	// Insert your ECDT table replacement here (optional).
#endif


#if STATIC_HPET_TABLE_INJECTION
	#define STATIC_HPET_TABLE_DATA \
	/* 0x0000 */	// Insert your HPET table replacement here (optional).
#endif


#if STATIC_MCFG_TABLE_INJECTION
	#define STATIC_MCFG_TABLE_DATA \
	/* 0x0000 */	// Insert your MCFG table replacement here (optional).
#endif


#if STATIC_SBST_TABLE_INJECTION
	#define STATIC_SBST_TABLE_DATA \
	/* 0x0000 */	// Insert your SBST table replacement here (optional).
#endif


#if STATIC_SSDT_TABLE_INJECTION
	#define STATIC_SSDT_TABLE_DATA \
	/* 0x0000 */	// Insert your SSDT table replacement here (optional).
#endif


//--------------------------------------------------------- SECONDARY ACPI TABLES -------------------------------------------------------------


#if STATIC_DSDT_TABLE_INJECTION
	#define STATIC_DSDT_TABLE_DATA \
	/* 0x0000 */	// Insert your DSDT table replacement here (optional).
#endif


#if STATIC_FACS_TABLE_INJECTION
	#define STATIC_FACS_TABLE_DATA \
	/* 0x0000 */	// Insert your FACS table replacement here (optional).
#endif


//---------------------------------------------------------- OPTIONAL ACPI TABLES -------------------------------------------------------------


#if STATIC_APIC2_TABLE_INJECTION
	#define STATIC_APIC2_TABLE_DATA \
	/* 0x0000 */	// Insert a second APIC table (replacement) here (optional).
#endif


#if STATIC_SSDT_GPU_TABLE_INJECTION
	#define STATIC_SSDT_GPU_TABLE_DATA \
	/* 0x0000 */	// Insert your SSDT_GPU table replacement here (optional).
#endif


#if STATIC_SSDT_PR_TABLE_INJECTION
	#define STATIC_SSDT_PR_TABLE_DATA \
	/* 0x0000 */	// Insert your SSDT_PR table replacement here (optional).
#endif


#if STATIC_SSDT_SATA_TABLE_INJECTION
	#define STATIC_SSDT_SATA_TABLE_DATA \
	/* 0x0000 */	// Insert your SSDT_SATA table replacement here (optional).
#endif


#if STATIC_SSDT_USB_TABLE_INJECTION
	#define STATIC_SSDT_USB_TABLE_DATA \
	/* 0x0000 */	// Insert your SSDT_USB table replacement here (optional).
#endif

//================================================================= END ====================================================================
