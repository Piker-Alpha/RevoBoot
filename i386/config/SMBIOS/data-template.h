/*
 * Copyright (c) 2009 Master Chief. All rights reserved.
 *
 * Note: This is an essential part of the build process for Revolution v0.6.44 and greater.
 *
 *
 * Update:  - Cleanups and additional directives added by DHP in 2011.
 *			- Tip / Note added by DHP (march 2012).
 *
 * Tip:		The idea is to use dynamic SMBIOS generation in RevoBoot only to 
 *			let it strip your factory table, after which you should do this:
 *
 *			1.) Extract the new OS X compatible SMBIOS table with: tools/smbios2struct
 *			2.) Add the data structure to: RevoBoot/i386/config/SMBIOS/data.h
 *			3.) Recompile RevoBoot, and be happy with your quicker boot time.
 *
 * Note:	Repeat this procedure after adding memory or other SMBIOS relevant 
 *			hardware changes, like replacing the motherboard and/or processor.
 *
 */

//--------------------------------------------------------------- SMBIOS -------------------------------------------------------------------

#define	STATIC_SMBIOS_SM_MAX_STRUCTURE_SIZE 0

#define	STATIC_SMBIOS_DMI_STRUCTURE_COUNT 0

#define STATIC_SMBIOS_DATA \
/* 0x0000 */	// Insert your SMBIOS data here.

//================================================================= END ====================================================================
