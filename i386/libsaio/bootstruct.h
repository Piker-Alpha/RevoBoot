/*
 * Copyright (c) 2002-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 2002-2003 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 2.0 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __BOOTSTRUCT_H
#define __BOOTSTRUCT_H

#include <pexpert/i386/boot.h>
#include "saio_types.h"
#include "bios.h"
#include "platform.h"

#define kDefaultKernel	"mach_kernel"

// Snapshot constants with supported version / revision info.
#define kBootArgsVersion_SnowLeopard	1
#define kBootArgsRevision_SnowLeopard	6

#define kBootArgsRevision_Leopard		5

#define kBootArgsVersion_Lion			2
#define kBootArgsRevision_Lion			0

#define VGA_TEXT_MODE	0

/*
 * Maximum number of boot drivers that can be loaded.
 */
#define NDRIVERS	500

#define CONFIG_SIZE (40 * 4096)

#define kMemoryMapCountMax	40

/*
 * PCI bus information.
 */
typedef struct _PCI_bus_info_t
{
	union
	{
		struct
		{
			unsigned char configMethod1	:1;
			unsigned char configMethod2	:1;
			unsigned char				:2;
			unsigned char specialCycle1	:1;
			unsigned char specialCycle2	:1;
		} s;
		unsigned char d;
	} u_bus;

	unsigned char maxBusNum;
	unsigned char majorVersion;
	unsigned char minorVersion;
	unsigned char BIOSPresent;
} PCI_bus_info_t;


typedef struct
{
	unsigned long address;	// address where driver was loaded
	unsigned long size;		// number of bytes
	unsigned long type;		// driver type
} driver_config_t;

/*
 * INT15, E820h - Query System Address Map.
 *
 * Documented in ACPI Specification Rev 2.0,
 * Chapter 15 (System Address Map Interfaces).
 */

/*
 * ACPI defined memory range types.
 */
enum
{
	kMemoryRangeUsable		= 1,	// RAM usable by the OS.
	kMemoryRangeReserved	= 2,	// Reserved. (Do not use)
	kMemoryRangeACPI		= 3,	// ACPI tables. Can be reclaimed.
	kMemoryRangeNVS			= 4,	// ACPI NVS memory. (Do not use)

	/* Undefined types should be treated as kMemoryRangeReserved */
};

/*!
    PrivateBootInfo has fields used by the booter that used to be part of
    KernelBootArgs_t *bootArgs.  When the switch was made to EFI the structure
    completely changed to boot_args *bootArgs.  This (new to boot-132) structure
    contains the fields the kernel no longer cares about but the booter still
    uses internally.  Some fields (e.g. the video information) remain interesting
    to the kernel and are thus located in bootArgs although with different field names.
 */
typedef struct PrivateBootInfo
{
    int              convmem;                      // conventional memory
    int              extmem;                       // extended memory

    char             bootFile[128];                // kernel file name

    unsigned long    memoryMapCount;
    MemoryRange      memoryMap[kMemoryMapCountMax];

    PCI_bus_info_t   pciInfo;

    char *           configEnd;                    // pointer to end of config files
    char             config[CONFIG_SIZE];

    config_file_t    bootConfig;		           // com.apple.Boot.plist

    config_file_t    smbiosConfig;				   // smbios.plist

#if RAMDISK_SUPPORT
    config_file_t    ramdiskConfig;                // RAMDisk.plist
#endif
} PrivateBootInfo_t;

extern PrivateBootInfo_t *bootInfo; 


typedef struct boot_args_new
{
    uint16_t    Revision;							// Revision of boot_args structure.
    uint16_t    Version;							// Version of boot_args structure.

#if ((MAKE_TARGET_OS & LION) == LION)				// Mavericks and Mountain Lion also have bit 2 set like Lion.
    uint8_t     efiMode;							// 32 = 32-bit, 64 = 64-bit.

    uint8_t     debugMode;							// Bit field with behavior changes.

#if ((MAKE_TARGET_OS & MOUNTAIN_LION) == MOUNTAIN_LION)
    uint8_t     __reserved0;
    uint8_t     __reserved1;
#else
    uint8_t     __reserved1[2];
#endif

#endif	
    char        CommandLine[BOOT_LINE_LENGTH];		// Passed in command line.
	
    uint32_t    MemoryMap;							// Physical address of memory map.
    uint32_t    MemoryMapSize;
    uint32_t    MemoryMapDescriptorSize;
    uint32_t    MemoryMapDescriptorVersion;
	
    Boot_Video	Video;								// Video Information.
	
    uint32_t    deviceTreeP;						// Physical address of flattened device tree.
    uint32_t    deviceTreeLength;					// Length of flattened tree.
	
    uint32_t    kaddr;								// Physical address of beginning of kernel text.
    uint32_t    ksize;								// Size of combined kernel text+data+efi.
	
    uint32_t    efiRuntimeServicesPageStart;		// Physical address of defragmented runtime pages.
    uint32_t    efiRuntimeServicesPageCount;

#if ((MAKE_TARGET_OS & LION) == LION)				// Mavericks and Mountain Lion also have bit 2 set like Lion.
    uint64_t    efiRuntimeServicesVirtualPageStart;	// Virtual address of defragmented runtime pages.
#endif

    uint32_t    efiSystemTable;						// Physical address of system table in runtime area.

#if ((MAKE_TARGET_OS & LION) == LION)				// Mavericks and Mountain Lion also have bit 2 set like Lion.
    uint32_t    __reserved2;

    uint32_t    performanceDataStart;				// Physical address of log.
    uint32_t    performanceDataSize;

    uint32_t    keyStoreDataStart;					// Physical address of key store data.
    uint32_t    keyStoreDataSize;

    uint64_t	bootMemStart;						// Physical address of interperter boot memory.
    uint64_t	bootMemSize;

    uint64_t    PhysicalMemorySize;
    uint64_t    FSBFrequency;
    
#if ((MAKE_TARGET_OS & MOUNTAIN_LION) == MOUNTAIN_LION)
    uint64_t    pciConfigSpaceBaseAddress;
    uint32_t    pciConfigSpaceStartBusNumber;
    uint32_t    pciConfigSpaceEndBusNumber;
    uint32_t    __reserved4[730];
#else
    uint32_t    __reserved4[734];
#endif

#else
    uint8_t     efiMode;							// 32 = 32-bit, 64 = 64-bit.

    uint8_t     __reserved1[3];
    uint32_t    __reserved2[3];

    uint64_t    efiRuntimeServicesVirtualPageStart;	// Virtual address of defragmented runtime pages.

    uint32_t    __reserved3[2];
#endif
} kernel_boot_args;

kernel_boot_args *bootArgs;

#endif /* __BOOTSTRUCT_H */
