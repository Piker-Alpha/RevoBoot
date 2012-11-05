/*
 * Copyright (c) 1998-2009 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 *
 * Stripped and rewritten for Revolution by Master Chief in 2009.
 * Refactored (dynamic and static SMBIOS data gathering) by DHP in 2010.
 * Copyright header error (false copyright claim) fixed by DHP in 2011.
 */

#ifndef __LIBSAIO_SMBIOS_ESSENTIALS_H
#define __LIBSAIO_SMBIOS_ESSENTIALS_H

// Copied from SMBIOS.h

typedef UInt8  SMBString;
typedef UInt8  SMBByte;
typedef UInt16 SMBWord;
typedef UInt32 SMBDWord;
typedef UInt64 SMBQWord;

struct DMIEntryPoint
{
    SMBByte		anchor[5];
	SMBByte		checksum;
	SMBWord		tableLength;
	SMBDWord	tableAddress;
	SMBWord		structureCount;
	SMBByte		bcdRevision;
} __attribute__((packed));

struct SMBEntryPoint
{
	SMBByte		anchor[4];
	SMBByte		checksum;
	SMBByte		entryPointLength;
	SMBByte		majorVersion;
	SMBByte		minorVersion;
	SMBWord		maxStructureSize;
	SMBByte		entryPointRevision;
	SMBByte		formattedArea[5];
	struct DMIEntryPoint dmi;
} __attribute__((packed));

typedef struct SMBStructHeader
{
    SMBByte    type;
    SMBByte    length;
    SMBWord    handle;
} __attribute__((packed)) SMBStructHeader;

#endif /* !__LIBSAIO_SMBIOS_ESSENTIALS_H */
