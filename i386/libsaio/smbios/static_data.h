/*
 * Copyright 2009 by Master Chief.
 *
 * Updates:
 *			- Dynamic and static SMBIOS data gathering added by DHP in 2010.
 *			- New path for static EFI data (PikerAlpha, October 2012).
 *
 * Credits:
 *			- blackosx, DB1, dgsga, FKA, humph, scrax and STLVNUB (testers).
 */

#ifndef __LIBSAIO_SMBIOS_STATIC_DATA_H
#define __LIBSAIO_SMBIOS_STATIC_DATA_H

#include "essentials.h"

// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
#include STRING(SMBIOS_DATA_FILE)

static uint32_t SMBIOS_Table[] = 
{
	STATIC_SMBIOS_DATA	// Will get replaced with the data from: config/smbios/data.h
};

#endif /* !__LIBSAIO_SMBIOS_STATIC_DATA_H */
