/*
 * Copyright (c) 2009 Master Chief.
 *
 * This file, included by acpi.c, efi.c and smbios.c includes data files
 * for the target build model (based on MODEL=MacModelNN) or default.h
 *
 * Updates:
 *
 *			- Refactored by DHP in 2010-2011.
 *			- Automatic model data selection (PikerAlpha, October 2012).
 *
 */


#if (PATCH_ACPI_TABLE_DATA && INCLUDE_ACPI_DATA)
	#undef INCLUDE_ACPI_DATA

	#include STRING(ACPI_DATA_FILE)
#endif

#if (INJECT_EFI_DEVICE_PROPERTIES && INCLUDE_EFI_DATA)
	#undef INCLUDE_EFI_DATA

	#include STRING(EFI_DATA_FILE)
#endif

#if (USE_STATIC_SMBIOS_DATA && INCLUDE_SMBIOS_DATA)
	#undef INCLUDE_SMBIOS_DATA

	#include STRING(SMBIOS_DATA_FILE)
#endif
