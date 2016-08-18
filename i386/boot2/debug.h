/*
 * Copyright (c) 2011 by DHP.
 */


//------------------------------------------------------------------------------

#ifndef __REVO_CONFIG_SETTINGS
#define __REVO_CONFIG_SETTINGS

#include "../config/settings.h"
#define DEBUG_STATE_ENABLED		(DEBUG_ACPI || DEBUG_BOOT || DEBUG_CPU || DEBUG_DISK || \
					DEBUG_DRIVERS|| DEBUG_EFI || DEBUG_BOOT_GRAPHICS || \
					DEBUG_PLATFORM || DEBUG_SMBIOS)

#endif // __REVO_CONFIG_SETTINGS


//------------------------------------------------------------------------------

#ifndef __REVO_DEBUG_H
#define __REVO_DEBUG_H


#if DEBUG_STATE_ENABLED
	#define _DEBUG_DUMP(x...)				printf(x)
	#define _DEBUG_ELSE_DUMP(x...)			else { printf(x); }
	#define _DEBUG_SLEEP(seconds)			printf("Sleeping for %d second%s...\n", seconds, (seconds > 1) ? "s" : ""); sleep(seconds)
#else
	#define _DEBUG_DUMP(x...)
	#define _DEBUG_ELSE_DUMP(x...)
	#define _DEBUG_SLEEP(seconds)
#endif


#if DEBUG_ACPI
	#define _ACPI_DEBUG_DUMP(x...)			_DEBUG_DUMP(x)
	#define _ACPI_DEBUG_SLEEP(seconds)		_DEBUG_SLEEP(seconds)
#else
	#define _ACPI_DEBUG_DUMP(x...)
	#define _ACPI_DEBUG_SLEEP(seconds)
#endif


#if DEBUG_BOOT
	#define _BOOT_DEBUG_DUMP(x...)			_DEBUG_DUMP(x)
	#define _BOOT_DEBUG_ELSE_DUMP(x...)		_DEBUG_ELSE_DUMP(x)
	#define _BOOT_DEBUG_SLEEP(seconds)		_DEBUG_SLEEP(seconds)
#else
	#define _BOOT_DEBUG_DUMP(x...)
	#define _BOOT_DEBUG_ELSE_DUMP(x...)
	#define _BOOT_DEBUG_SLEEP(seconds)
#endif


#if DEBUG_CPU
	#define _CPU_DEBUG_DUMP(x...)			_DEBUG_DUMP(x)
	#define _CPU_DEBUG_SLEEP(seconds)		_DEBUG_SLEEP(seconds)
#else
	#define _CPU_DEBUG_DUMP(x...)
	#define _CPU_DEBUG_SLEEP(seconds)
#endif


#if DEBUG_DISK
	#define _DISK_DEBUG_DUMP(x...)			_DEBUG_DUMP(x)
	#define _DISK_DEBUG_SLEEP(seconds)		_DEBUG_SLEEP(seconds)
	#define _DISK_DEBUG_ELSE_DUMP(x...)		_DEBUG_ELSE_DUMP(x)
#else
	#define _DISK_DEBUG_DUMP(x...)
	#define _DISK_DEBUG_SLEEP(seconds)
	#define _DISK_DEBUG_ELSE_DUMP(x...)
#endif


#if DEBUG_DRIVERS
	#define _DRIVERS_DEBUG_DUMP(x...)		_DEBUG_DUMP(x)
	#define _DRIVERS_DEBUG_SLEEP(seconds)	_DEBUG_SLEEP(seconds)
#else
	#define _DRIVERS_DEBUG_DUMP(x...)
	#define _DRIVERS_DEBUG_SLEEP(seconds)
#endif


#if DEBUG_EFI
	#define _EFI_DEBUG_DUMP(x...)			_DEBUG_DUMP(x)
	#define _EFI_DEBUG_SLEEP(seconds)		_DEBUG_SLEEP(seconds)
#else
	#define _EFI_DEBUG_DUMP(x...)
	#define _EFI_DEBUG_SLEEP(seconds)
#endif


#if DEBUG_PLATFORM
	#define _PLATFORM_DEBUG_DUMP(x...)		_DEBUG_DUMP(x)
	#define _PLATFORM_DEBUG_SLEEP(seconds)	_DEBUG_SLEEP(seconds)
#else
	#define _PLATFORM_DEBUG_DUMP(x...)
	#define _PLATFORM_DEBUG_SLEEP(seconds)
#endif


#if DEBUG_SMBIOS
	#define _SMBIOS_DEBUG_DUMP(x...)		_DEBUG_DUMP(x)
	#define _SMBIOS_DEBUG_SLEEP(seconds)	_DEBUG_SLEEP(seconds)
#else
	#define _SMBIOS_DEBUG_DUMP(x...)
	#define _SMBIOS_DEBUG_SLEEP(seconds)
#endif


#if (DEBUG_KERNEL_PATCHER & 1)
	#define DEBUG_SYMBOL_FOUND(symbol, offset, vmaddr, fileoff, start, end)	\
						printf("Symbol %s found!\n", symbol);				\
						printf("offset..............: 0x%llx\n", offset);	\
						printf("textSegment->vmaddr.: 0x%llx\n", vmaddr);	\
						printf("textSegment->fileoff: 0x%llx\n", fileoff);	\
						printf("startAddress........: 0x%llx\n", start);	\
						printf("endAddress..........: 0x%llx\n", end);		\
						sleep(1);
#else
	#define DEBUG_SYMBOL_FOUND(symbol, offset, vmaddr, fileoff, start, end)
#endif

#if (DEBUG_KERNEL_PATCHER & 2)
	#define DEBUG_PATCH_STATUS(symbol, address, seconds)					\
						printf("Patched %s(@ 0x%x)\n", symbol, address);	\
																			\
						if (seconds)										\
						{													\
							sleep(seconds);									\
						}
#else
	#define DEBUG_PATCH_STATUS(symbol, address, seconds)
#endif

#if (DEBUG_KERNEL_PATCHER & 4)
	#define DEBUG_DISABLED_MSR(msr, seconds)					\
						printf("Disabling MSR: 0x%x\n", msr);	\
																\
						if (seconds)							\
						{										\
							sleep(seconds);						\
						}
#else
	#define DEBUG_DISABLED_MSR(msr, seconds)
#endif

#endif // __REVO_DEBUG_H
