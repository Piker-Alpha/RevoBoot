/*
 * Copyright (c) 1999-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights
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
 *
 * Copyright 1993 NeXT, Inc. All rights reserved.
 *
 * Refactored by DHP in 2010.  All rights reserved.
 */


#include "bootstruct.h"
#include "sl.h"

PrivateBootInfo_t *bootInfo;


//==============================================================================
// Called from function initPlatform in platform.c

void initKernelBootConfig(void)
{
	bootArgs = (kernel_boot_args *)malloc(sizeof(boot_args));
	bootInfo = (PrivateBootInfo_t *)malloc(sizeof(PrivateBootInfo_t));

	if (bootArgs == 0 || bootInfo == 0)
	{
		stop("Couldn't allocate boot info\n");
	}

	bzero(bootArgs, sizeof(boot_args));
	bzero(bootInfo, sizeof(PrivateBootInfo_t));

	// Set kernel name to: '/System/Library/Kernels/kernel' for 10.10 and greater
	// and 'mach_kernel' for all previous versions of OS X.
	// strcpy(bootInfo->bootFile, kDefaultKernel);
	sprintf(bootInfo->bootFile, "%s", kDefaultKernel);

	// Get system memory map. Also update the size of the
	// conventional/extended memory for backwards compatibility.

	bootInfo->memoryMapCount = getMemoryMap(bootInfo->memoryMap, kMemoryMapCountMax,
											(unsigned long *) &bootInfo->convmem, 
											(unsigned long *) &bootInfo->extmem);

	if (bootInfo->memoryMapCount == 0)
	{
		// BIOS did not provide a memory map, systems with discontiguous
		// memory or unusual memory hole locations may have problems.

		bootInfo->convmem = getConventionalMemorySize();
		bootInfo->extmem  = getExtendedMemorySize();
	}

	bootInfo->configEnd = bootInfo->config;
	bootArgs->Video.v_display = VGA_TEXT_MODE;

	// What Lion species is screaming here?
	if ((gPlatform.OSType & LION) == LION)
	{
		bootArgs->Version  = kBootArgsVersion_Lion;			// Defined in bootstruct.h
		bootArgs->Revision = kBootArgsRevision_Lion;		// Defined in bootstruct.h
	}
	else
	{
		bootArgs->Version  = kBootArgsVersion_SnowLeopard;	// Defined in bootstruct.h
		bootArgs->Revision = kBootArgsRevision_SnowLeopard;	// Defined in bootstruct.h
	}
	
	// EFI selection is based on the CPU type.
	bootArgs->efiMode = (gPlatform.ArchCPUType == CPU_TYPE_X86_64) ? kBootArgsEfiMode64 : kBootArgsEfiMode32;

#if ((MAKE_TARGET_OS & LION) == LION) // El Capitan, Yosemite, Mavericks and Mountain Lion also have bit 1 set like Lion.
	// Lion's new debug output (replacing a couple of former boot arguments).
	bootArgs->debugMode = EFI_DEBUG_MODE;					// Defined in config/settings.h
#endif
	
#if ((MAKE_TARGET_OS & LION) == LION) // El Capitan, Yosemite, Mavericks and Mountain Lion also have bit 1 set like Lion.
	// Adding a 16 KB log space.
	bootArgs->performanceDataSize	= 0;
	bootArgs->performanceDataStart	= 0;
	
	// AppleKeyStore.kext
	bootArgs->keyStoreDataSize		= 0;
	bootArgs->keyStoreDataStart		= 0;
	
	bootArgs->bootMemSize			= 0;
	bootArgs->bootMemStart			= 0;
	
#if ((MAKE_TARGET_OS & MOUNTAIN_LION) == MOUNTAIN_LION)
	bootArgs->flags					= 0;

#if REBOOT_ON_PANIC
	bootArgs->flags					= kBootArgsFlagRebootOnPanic;
#endif

#if UISCALE_2X
	bootArgs->flags					|= kBootArgsFlagHiDPI;
#endif

#if BLACKMODE
	bootArgs->flags					|= kBootArgsFlagBlackTheme; // (kBootArgsFlagBlack + kBootArgsFlagBlackTheme);
#endif

#endif // #if ((MAKE_TARGET_OS & MOUNTAIN_LION) == MOUNTAIN_LION)

#if ((MAKE_TARGET_OS & EL_CAPITAN) == EL_CAPITAN)
	bootArgs->flags					|= (kBootArgsFlagCSRConfigMode + kBootArgsFlagCSRBoot);

	bootArgs->csrActiveConfig		= CSR_ALLOW_DEVICE_CONFIGURATION;

	bootArgs->csrCapabilities		= CSR_CAPABILITY_UNLIMITED;

	bootArgs->boot_SMC_plimit		= 0;
#endif

	bootArgs->kslide				= 0;
#endif // #if ((MAKE_TARGET_OS & LION) == LION)
}


//==============================================================================
// Called from: execKernel() in boot.c

void finalizeKernelBootConfig(void)
{
    uint32_t size;
    void *addr;
    int i;
    EfiMemoryRange *memoryMap;
    MemoryRange *range;
    int memoryMapCount = bootInfo->memoryMapCount;

    if (memoryMapCount == 0)
	{
        // XXX could make a two-part map here
        stop("Unable to convert memory map into proper format\n");
    }

    // Convert memory map to boot_args memory map
    memoryMap = (EfiMemoryRange *)AllocateKernelMemory(sizeof(EfiMemoryRange) * memoryMapCount);

    bootArgs->MemoryMap						= (uint32_t)memoryMap;
    bootArgs->MemoryMapSize					= sizeof(EfiMemoryRange) * memoryMapCount;
    bootArgs->MemoryMapDescriptorSize		= sizeof(EfiMemoryRange);
    bootArgs->MemoryMapDescriptorVersion	= 0;

    for (i = 0; i < memoryMapCount; i++, memoryMap++)
	{
        range = &bootInfo->memoryMap[i];

        switch (range->type)
		{
			case kMemoryRangeACPI:
				memoryMap->Type = kEfiACPIReclaimMemory;
				break;

			case kMemoryRangeNVS:
				memoryMap->Type = kEfiACPIMemoryNVS;
				break;

			case kMemoryRangeUsable:
				memoryMap->Type = kEfiConventionalMemory;
				break;

			case kMemoryRangeReserved:

			default:
				memoryMap->Type = kEfiReservedMemoryType;
				break;
        }

        memoryMap->PhysicalStart	= range->base;
        memoryMap->VirtualStart		= range->base;
        memoryMap->NumberOfPages	= range->length >> I386_PGSHIFT;
        memoryMap->Attribute		= 0;
    }
    
    // copy bootFile into device tree
    // XXX

    // add PCI info somehow into device tree
    // XXX

    // Flatten device tree
    DT__FlattenDeviceTree(0, &size);
    addr = (void *)AllocateKernelMemory(size);

    if (addr == 0)
	{
        stop("Couldn't allocate device tree\n");
	}
    
    DT__FlattenDeviceTree((void **)&addr, &size);

    bootArgs->deviceTreeP = (uint32_t)addr;
    bootArgs->deviceTreeLength = size;
	
#if ((MAKE_TARGET_OS & LION) == LION) // All OS versions greater than Lion have bit 1 set.
	// Adding a 16 KB log space.
	bootArgs->performanceDataSize	= 0;
	bootArgs->performanceDataStart	= 0;

	// AppleKeyStore.kext
	bootArgs->keyStoreDataSize	= 0;
	bootArgs->keyStoreDataStart	= 0;

	bootArgs->bootMemSize	= 0;
	bootArgs->bootMemStart	= 0;
	
	bootArgs->kslide		= 0;
#endif
	
#if (((MAKE_TARGET_OS & MOUNTAIN_LION) == MOUNTAIN_LION) && (BLACKMODE == 1))
	bootArgs->flags			|= kBootArgsFlagBlack;
#endif

#if ((MAKE_TARGET_OS & LION) == LION) // El Capitan, Yosemite, Mavericks and Mountain Lion also have bit 1 set like Lion.
	bootArgs->PhysicalMemorySize	= gPlatform.RAM.MemorySize;
	bootArgs->FSBFrequency			= gPlatform.CPU.FSBFrequency;
#endif
}


//==============================================================================
// Copies boot args after kernel and record address 
// Called from: execKernel() in boot.c

void moveKernelBootArgs(void)
{
    void *oldAddr = bootArgs;
    bootArgs = (kernel_boot_args *)AllocateKernelMemory(sizeof(boot_args));
    bcopy(oldAddr, bootArgs, sizeof(boot_args));
}

