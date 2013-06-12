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
 * Reworked for automatic address calculation, 
 * Copyright (c) 2010 by DHP. All Rights Reserved.
 */

#ifndef __BOOT_MEMORY_H
#define __BOOT_MEMORY_H

/* Memory addresses used by booter and friends */

/*  DFE 2007-12-21: Changed BASE_SEG to be conditional
    This allows boot1u and other planned first-stage booters to avoid
    maintaining their own copies of asm.s and bios.s and instead
    simply build the files from libsaio with the right preprocessor
    definitions.

    This affects BASE_ADDR and OFFSET16() thus obviating the need for
    separate BASE1U_ADDR and OFFSET1U16() macros.

    Be careful though as changing these values with preprocessor macros
    obviously requires rebuilding the source files.  That means in particular
    that libsaio.a is only suitable for boot2.
 */

#if defined(BASE_SEG)
	// Assuming that the personebuilding the boot loader knows what to do.
#elif defined(BOOT1)
	# define BASE_SEG		BOOT1U_SEG
#else
	# define BASE_SEG		BOOT2_SEG
#endif

#define STACK_SEG			0x8000								// zef: old STACK_SEG 0x5000.
#define STACK_OFS			0xFFF0								// Stack pointer.

#define BOOT1U_SEG			0x1000
#define BOOT1U_OFS			0x0200

#define BOOT2_SEG			0x2000								// Disk sector offset.
#define BOOT2_OFS			0x0200								// 512 Bytes.

#define BIOS_ADDR			0x8000								// BIOS disk I/O buffer.
#define BIOS_LEN			0x8000								// 32 KB (dividable by 512 and 2048).

#define BOOT0_ADDR			0x7E00								// Load address of boot0.

#define ADDR32(seg, ofs)	(((seg) << 4 ) + (ofs))

#define BASE_ADDR			ADDR32(BASE_SEG, 0)
#define BOOT1U_ADDR			ADDR32(BOOT1U_SEG, BOOT1U_OFS)
#define BOOT2_ADDR			ADDR32(BOOT2_SEG, BOOT2_OFS)

#define MEMBASE				0x0

#define BOOTSTRUCT_ADDR		0x00011000L
#define BOOTSTRUCT_LEN		0x0000F000L							// Size: 60 KB (overkill, is even smaller).

//							0x00020000L
#define VOID_ADDR			(BOOTSTRUCT_ADDR + BOOTSTRUCT_LEN)
#define VOID_LEN			0x00020000L							// Size: 256 KB.

//							0x00040000L
#define HIB_ADDR			(VOID_ADDR + VOID_LEN)				// Special hibernation area.
#define HIB_LEN				0x00060000L							// Size: 384 KB.

//							0x000A0000L
#define VIDEO_ADDR			(HIB_ADDR + HIB_LEN)				// Unusable space.
#define VIDEO_LEN			0x00060000L							// Size: 384 KB.

//							0x00100000L
#define KERNEL_ADDR			(VIDEO_ADDR + VIDEO_LEN)			// Kernel and MKexts/drivers.
#define KERNEL_LEN			0x06000000L							// Size: 96 MB (128 MB for Chameleon).
																//
																// Note: Can cause a stop("Kernel overflows available space")
// Based on KERNEL_LEN		0x04100000L
#define ZALLOC_ADDR			(KERNEL_ADDR + KERNEL_LEN)			// Zalloc area.
#define ZALLOC_LEN			0x10000000L							// Size: 256 MB.

// Based on ZALLOC_LEN		0x14100000L
#define LOAD_ADDR			(ZALLOC_ADDR + ZALLOC_LEN)			// File load buffer.
#define LOAD_LEN			0x05F80000L							// Size: 95 MB.

																// Location of data fed to boot2 by the prebooter
// Based on LOAD_LEN		0x1A080000L
#define PREBOOT_DATA		(LOAD_ADDR + LOAD_LEN)				// Room for a 195 MB RAM disk image (with 512 MB System Memory).


#define TFTP_ADDR			LOAD_ADDR							// TFTP download buffer (not used in RevoBoot).
#define TFTP_LEN			LOAD_LEN


#define kLoadAddr			LOAD_ADDR
#define kLoadSize			LOAD_LEN

#define CONVENTIONAL_LEN	0x0A0000							// 640 KB
#define EXTENDED_ADDR		0x100000							// 1024 KB

#define ptov(paddr)			((paddr) - MEMBASE)
#define vtop(vaddr)			((vaddr) + MEMBASE)

// Extract segment/offset from a linear address.
#define OFFSET16(addr)		((addr) - BASE_ADDR)
#define OFFSET(addr)		((addr) & 0xFFFF)
#define SEGMENT(addr)		(((addr) & 0xF0000) >> 4)

/*
 * Extract segment/offset in normalized form so that the resulting far pointer
 * will point to something that is very unlikely to straddle a segment.
 * This is sometimes known as a "huge" pointer.
 */
#define NORMALIZED_OFFSET(addr)		((addr) & 0x000F)
#define NORMALIZED_SEGMENT(addr)	(((addr) & 0xFFFF0) >> 4)

// We need a minimum of 32MB of system memory.
#define MIN_SYS_MEM_KB  (32 * 1024)

// The number of descriptor entries in the GDT (Global Descriptor Table).
#define NGDTENT   7

// The total size of the GDT in bytes. Each descriptor entry require 8 bytes.
#define GDTLIMIT  (NGDTENT * 8)

#endif /* !__BOOT_MEMORY_H */
