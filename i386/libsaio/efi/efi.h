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

#ifndef _LIBSAIO_EFI_EFI_H
#define _LIBSAIO_EFI_EFI_H


// Set up space for up to 5 tables but we currently only add two.
#define EFI_MAX_CONFIG_TABLES			5

#if EFI_64_BIT
	// Mountain Lion
	//
	// movabs $0x8000000000000003,%rax
	// ret
	static uint8_t const UNSUPPORTEDRET_INSTRUCTIONS[] = { 0x48, 0xb8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc3 };
#else
	// Lion, Snow Leopard and Leopard
	//
	// movl $0x80000003,%eax
	// ret
	static uint8_t const UNSUPPORTEDRET_INSTRUCTIONS[] = { 0xb8, 0x03, 0x00, 0x00, 0x80, 0xc3 };
#endif

///
/// 32/64-bit native width with the highest bit set.
///
#if EFI_64_BIT
	#define EFI_MAX_BIT					0x8000000000000000ULL
#else
	#define EFI_MAX_BIT					0x80000000
#endif

///
/// Macro's to encode the status code.
///

// Set the upper bit to indicate EFI Error.
#define ENCODE_ERROR(_a)				(EFI_MAX_BIT | (_a))

#define EFIERR(_a)						ENCODE_ERROR(_a)

///
/// The operation completed successfully.
///
#define EFI_SUCCESS						0

///
/// The parameter was incorrect.
///
#define EFI_INVALID_PARAMETER			EFIERR (2)

///
/// The operation is not supported.
///
#define EFI_UNSUPPORTED					EFIERR (3)

// EFI Revision info.
//
#if EFI_64_BIT
	#define EFI_SPEC_MAJOR_REVISION		2
	#define EFI_SPEC_MINOR_REVISION		31
#else
	#define EFI_SPEC_MAJOR_REVISION		1
	#define EFI_SPEC_MINOR_REVISION		10
#endif

// EFI System Table.
//
#define EFI_SYSTEM_TABLE_SIGNATURE		0x5453595320494249ULL
#define EFI_SYSTEM_TABLE_REVISION		((EFI_SPEC_MAJOR_REVISION << 16) | (EFI_SPEC_MINOR_REVISION))

// EFI Runtime Services Table.
//
#define EFI_RUNTIME_SERVICES_SIGNATURE	0x56524553544e5552ULL
#define EFI_RUNTIME_SERVICES_REVISION	((EFI_SPEC_MAJOR_REVISION << 16) | (EFI_SPEC_MINOR_REVISION))


typedef struct
{
	EFI_UINT64				Signature;
	EFI_UINT32				Revision;
	EFI_UINT32				HeaderSize;
	EFI_UINT32				CRC32;
	EFI_UINT32				Reserved;
} __attribute__((aligned(8))) EFI_TABLE_HEADER;


typedef struct
{
	EFI_TABLE_HEADER		Hdr;

	// Time Services
	EFI_PTR					GetTime;
	EFI_PTR					SetTime;
	EFI_PTR					GetWakeupTime;
	EFI_PTR					SetWakeupTime;

	// Virtual Memory Services
	EFI_PTR					SetVirtualAddressMap;
	EFI_PTR					ConvertPointer;

	// Variable Services
	EFI_PTR					GetVariable;
	EFI_PTR					GetNextVariableName;
	EFI_PTR					SetVariable;

	// Miscellaneous Services
	EFI_PTR					GetNextHighMonotonicCount;
	EFI_PTR					ResetSystem;

	// UEFI 2.0 Capsule Services
	EFI_PTR					UpdateCapsule;
	EFI_PTR					QueryCapsuleCapabilities;
	
	// Miscellaneous UEFI 2.0 Service
	EFI_PTR					QueryVariableInfo;
} __attribute__((aligned(8))) EFI_RUNTIME_SERVICES;


typedef struct EFI_CONFIGURATION_TABLE
{
	EFI_GUID				VendorGuid;
	EFI_PTR					VendorTable;
#if EFI_64_BIT
} __attribute__((aligned(8))) EFI_CONFIGURATION_TABLE;
#else
} EFI_CONFIGURATION_TABLE;
#endif


typedef struct EFI_SYSTEM_TABLE
{
	EFI_TABLE_HEADER		Hdr;

	EFI_PTR					FirmwareVendor;
	EFI_UINT32				FirmwareRevision;

#if EFI_64_BIT
	EFI_UINT32				__pad;
#endif	

	EFI_HANDLE				ConsoleInHandle;
	EFI_PTR					ConIn;

	EFI_HANDLE				ConsoleOutHandle;
	EFI_PTR					ConOut;

	EFI_HANDLE				StandardErrorHandle;
	EFI_PTR					StdErr;

	EFI_PTR					RuntimeServices;
	EFI_PTR					BootServices;

	EFI_UINT				NumberOfTableEntries;
	EFI_PTR					ConfigurationTable;
} __attribute__((aligned(8))) EFI_SYSTEM_TABLE;

#endif /* _LIBSAIO_EFI_EFI_H */
