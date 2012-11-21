/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * EFI implementation for Revolution Copyright (c) 2010 by DHP.
 * All rights reserved.
 *
 */

#ifndef __LIBSAIO_EFI_ESSENTIALS_H
#define __LIBSAIO_EFI_ESSENTIALS_H

// #include "../config/settings.h"
#include "../boot2/debug.h"

typedef void      VOID;

typedef uint32_t  EFI_STATUS;

typedef uint8_t   EFI_BOOLEAN;

typedef int8_t    EFI_INT8;
typedef int16_t   EFI_INT16;
typedef int32_t   EFI_INT32;
typedef int64_t   EFI_INT64;

typedef uint8_t   EFI_UINT8;
typedef uint16_t  EFI_UINT16;
typedef uint32_t  EFI_UINT32;
typedef uint64_t  EFI_UINT64;

typedef uint32_t  EFI_UINTN;					// Natural size for firmware, not the kernel.

typedef int8_t    EFI_CHAR8;
typedef int16_t   EFI_CHAR16;
typedef int32_t   EFI_CHAR32;
typedef int64_t   EFI_CHAR64;

typedef uint32_t  EFI_PTR32;
typedef uint64_t  EFI_PTR64;

typedef uint32_t  EFI_HANDLE32;
typedef uint64_t  EFI_HANDLE64;


typedef struct EFI_GUID
{
	EFI_UINT32	Data1;
	EFI_UINT16	Data2;
	EFI_UINT16	Data3;
	EFI_UINT8	Data4[8];
} EFI_GUID;


#if EFI_64_BIT
	typedef uint64_t		EFI_UINT;
	typedef uint64_t		EFI_PTR;
	typedef uint64_t		EFI_HANDLE;
#else
	typedef uint32_t		EFI_UINT;
	typedef uint32_t		EFI_PTR;
	typedef uint32_t		EFI_HANDLE;
#endif


typedef struct
{
	//
	// HARDWARE_DEVICE_PATH		0x01
	// ACPI_DEVICE_PATH			0x02
	// MESSAGING_DEVICE_PATH	0x03
	// MEDIA_DEVICE_PATH		0x04
	// BBS_DEVICE_PATH			0x05
	// END_DEVICE_PATH_TYPE		0x7f
	//
	EFI_UINT8					Type;
	
	//
	// Depends On Type
	//
	// HW_PCI_DP				0x01  
	// HW_PCCARD_DP				0x02
	// HW_MEMMAP_DP				0x03
	// HW_VENDOR_DP				0x04
	// HW_CONTROLLER_DP			0x05
	//
	EFI_UINT8					SubType;
	
	//
	// Device Path Length
	//
	EFI_UINT8					Length[2];
} EFI_DEVICE_PATH_PROTOCOL;


#define HW_VENDOR_DP			0x04

typedef struct
{
	EFI_DEVICE_PATH_PROTOCOL	Header;
	
	EFI_GUID					Guid;
} VENDOR_DEVICE_PATH;


typedef struct
{
	EFI_DEVICE_PATH_PROTOCOL	Header;
	
	//
	// Device's PnP hardware ID stored in a numeric 32-bit
	// compressed EISA-type ID. This value must match the
	// corresponding _HID in the ACPI name space.
	//
	EFI_UINT32					HID;
	//
	// Unique ID that is required by ACPI if two devices have the
	// same _HID. This value must also match the corresponding
	// _UID/_HID pair in the ACPI name space. Only the 32-bit
	// numeric value type of _UID is supported. Thus, strings must
	// not be used for the _UID in the ACPI name space.
	//
	EFI_UINT32					UID;
} ACPI_HID_DEVICE_PATH;


typedef struct
{
	EFI_DEVICE_PATH_PROTOCOL	Header;

	///
	/// Describes the entry in a partition table, starting with entry 1.
	/// Partition number zero represents the entire device. Valid
	/// partition numbers for a MBR partition are [1, 4]. Valid
	/// partition numbers for a GPT partition are [1, NumberOfPartitionEntries].
	///
	EFI_UINT32					PartitionNumber;
	///
	/// Starting LBA of the partition on the hard drive.
	///
	EFI_UINT64					PartitionStart;
	///
	/// Size of the partition in units of Logical Blocks.
	///
	EFI_UINT64					PartitionSize;
	//
	// Signature unique to this partition:
	// If SignatureType is 0, this field has to be initialized with 16 zeros.
	// If SignatureType is 1, the MBR signature is stored in the first 4 bytes of this field.
	// The other 12 bytes are initialized with zeros.
	// If SignatureType is 2, this field contains a 16 byte signature.
	//
	EFI_UINT8					Signature[16];
	//
	// Partition Format: (Unused values reserved).
	// 0x01 - PC-AT compatible legacy MBR.
	// 0x02 - GUID Partition Table.
	//
	EFI_UINT8					MBRType;
	//
	// Type of Disk Signature: (Unused values reserved).
	// 0x00 - No Disk Signature.
	// 0x01 - 32-bit signature from address 0x1b8 of the type 0x01 MBR.
	// 0x02 - GUID signature.
	//
	EFI_UINT8					SignatureType;
} HARDDRIVE_DEVICE_PATH;


// Stuff from EDK2's EfiDevicePath.h

#define MEDIA_HARDDRIVE_DP				0x01
#define MEDIA_DEVICE_PATH				0x04

#define SIGNATURE_TYPE_MBR				0x01
#define SIGNATURE_TYPE_GUID				0x02

#define END_DEVICE_PATH_TYPE			0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE	0xff
#define EFI_DP_TYPE_MASK				0x7f

#define DevicePathType(a)				( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)			( (a)->SubType )
#define IsDevicePathEndType(a)			( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define DevicePathNodeLength(a)			( ((a)->Length[0]) | ((a)->Length[1] << 8) )
#define NextDevicePathNode(a)			( (EFI_DEVICE_PATH_PROTOCOL *) ( ((EFI_INT8 *) (a)) + DevicePathNodeLength(a)))

#endif /* !__LIBSAIO_EFI_ESSENTIALS_H */

