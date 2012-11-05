/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 2003 Apple Computer, Inc.  All Rights
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

#include "sl.h"
#include "saio_internal.h"
#include "bootstruct.h"
#include "device_tree.h"
#include "platform.h"

#define kPageSize     4096
#define RoundPage(x)  ((((unsigned)(x)) + kPageSize - 1) & ~(kPageSize - 1))


//==============================================================================

long AllocateMemoryRange(char * rangeName, long start, long length, long type)
{
	char *nameBuf = malloc(strlen(rangeName) + 1);

	if (nameBuf == 0)
	{
		return -1;
	}

	strcpy(nameBuf, rangeName);

	uint32_t *buffer = malloc(2 * sizeof(uint32_t));

	if (buffer == 0)
	{
		free(nameBuf);

		return -1;
	}
    
	buffer[0] = start;
	buffer[1] = length;

#if DEBUG
	printf("AllocateMemoryRange : %s - 0x%lx - 0x%lx\n", nameBuf, length, start);
#endif

	DT__AddProperty(gPlatform.EFI.Nodes.MemoryMap, nameBuf, 2 * sizeof(uint32_t), (char *)buffer);
    
	return 0;
}


//==============================================================================

long AllocateKernelMemory(long inSize)
{
	if (gPlatform.LastKernelAddr == 0)
	{
		gPlatform.LastKernelAddr = RoundPage(bootArgs->kaddr + bootArgs->ksize);
	}

	long address = gPlatform.LastKernelAddr;
	gPlatform.LastKernelAddr += RoundPage(inSize);
	
	if (gPlatform.LastKernelAddr >= (KERNEL_ADDR + KERNEL_LEN))
	{
		stop ("AllocateKernelMemory error");
	}
	
	bootArgs->ksize = gPlatform.LastKernelAddr - bootArgs->kaddr;

#if DEBUG
	printf("AllocateKernelMemory: 0x%lx - 0x%lx\n", address, inSize);
	getchar();
#endif

	return address;
}
