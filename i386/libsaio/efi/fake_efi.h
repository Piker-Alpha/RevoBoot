/*
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
 * Portions of source code Copyright (c) 2007 by David F. Elliott,
 * additional changes by: Macerintel (2008), Master Chief (2009) and 
 * Rekursor in 2009. All rights reserved.
 *
 * EFI implementation for Revolution Copyright (c) 2010 by DHP.
 * All rights reserved.
 *
 * Updates:
 *		- Check malloc return (PikerAlpha, November 2012).
 *
 */

#include "bootstruct.h"		// For bootArgs.


//------------------------------------------------------------------------------

extern void setupACPI(void);
extern void setupSMBIOS(void);
extern bool setRootUUID(Node *chosenNode, char * rootUUID);

//------------------------------------------------------------------------------

static EFI_CHAR16 const FIRMWARE_VENDOR[] = { 'A', 'p', 'p', 'l', 'e', '\0' };
// Resulting in: "firmware-vendor" = <4100700070006c0065000000>

/*
 * We use the same value for everything, as we should, which means (currently)
 * 0x0001000A for EFI64 and 0x00010001 for EFI32. Just like on real Mac's.
 */

static EFI_UINT32 const FIRMWARE_REVISION = EFI_SYSTEM_TABLE_REVISION;


//==============================================================================
// Utility function to make a device tree string from an EFI_GUID

static inline char * mallocStringForGuid(EFI_GUID const *aGuid)
{
	char *string = NULL;

	convertEFIGUIDToString(aGuid, &string);

	if (string)
	{
		return string;
	}

	return NULL;
}

//==============================================================================
// Function to map a 32-bit address to a 64-bit address, or it simply returns 
// the given (32-bit) address (to support EFI 32-bit mode).

static EFI_UINT ptov64(uint32_t address)
{
	if (gPlatform.AddressWidth == 4)
	{
		return (uint32_t)address;
	}

	return ((uint64_t)address | 0xFFFFFF8000000000ULL);
}


//==============================================================================

extern EFI_STATUS addConfigurationTable(EFI_GUID const *pGuid, void * table, char const * tableAlias)
{
	EFI_UINTN numberOfTables = gPlatform.EFI.SystemTable->NumberOfTableEntries;
	
	_EFI_DEBUG_DUMP("In addConfigurationTable(%d)\n", numberOfTables);

	// We only do additions. No modifications and deletes like CoreInstallConfigurationTable does.
	if (numberOfTables >= EFI_MAX_CONFIG_TABLES)
	{
		stop("Unable to add table.\nIncrease EFI_MAX_CONFIG_TABLES in efi/efi.h\n");
	}
	
	if (table != NULL)
	{
		/* FIX ME
		EFI_CONFIGURATION_TABLE *cTable = (EFI_CONFIGURATION_TABLE *)((uint32_t)gPlatform.EFI.SystemTable->ConfigurationTable);
		cTable[numberOfTables].VendorGuid = (EFI_GUID *)pGuid;
		cTable[numberOfTables].VendorTable = (uint32_t)table;
		gPlatform.EFI.SystemTable->NumberOfTableEntries++; */

		Node *tableNode = DT__AddChild(gPlatform.EFI.Nodes.ConfigurationTable, mallocStringForGuid(pGuid));

		// Use the pointer to the GUID we just stuffed into the system table.
		DT__AddProperty(tableNode, "guid", sizeof(EFI_GUID), (void *)pGuid);
		
		// The "table" property is the 32/64-bit physical address of the table.
		DT__AddProperty(tableNode, "table", gPlatform.AddressWidth, table);

		// Assume the alias pointer is a global or static piece of data.
		if (tableAlias != NULL)
		{
			DT__AddProperty(tableNode, "alias", strlen(tableAlias) + 1, (char *)tableAlias);
		}
	}
	
	return EFI_SUCCESS;
}


//==============================================================================
// Allocate fake EFI system / runtime services table.

void setupEFITables(void)
{
	// return instruction.
	static uint8_t const VOIDRET_INSTRUCTIONS[] = { 0xc3 };

	// movl $0x80000003,%eax; ret
	// static uint8_t const UNSUPPORTEDRET_INSTRUCTIONS[] = { 0xb8, 0x03, 0x00, 0x00, 0x80, 0xc3 };

	// movabs $0x8000000000000003,%rax
	// ret
	static uint8_t const UNSUPPORTEDRET_INSTRUCTIONS[] = { 0x48, 0xb8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc3 };

	// Occupying a single 4 KB memory block (wired page) to prevent multiple smaller allocations.
	struct EFI_Container
	{
		EFI_SYSTEM_TABLE			EfiSystemTable;
		EFI_RUNTIME_SERVICES		EfiRuntimeServices;
		EFI_CONFIGURATION_TABLE		EfiConfigurationTable[EFI_MAX_CONFIG_TABLES];
		EFI_CHAR16					FirmwareVendor[sizeof(FIRMWARE_VENDOR) / sizeof(EFI_CHAR16)];
		uint8_t						Voidret_instructions[sizeof(VOIDRET_INSTRUCTIONS) / sizeof(uint8_t)];
		uint8_t						Unsupportedret_instructions[sizeof(UNSUPPORTEDRET_INSTRUCTIONS) / sizeof(uint8_t)];
	};

	struct EFI_Container * fakeEFI = (struct EFI_Container *)AllocateKernelMemory(sizeof(struct EFI_Container));

    // Zero out all the tables in case fields are added later.
	bzero(fakeEFI, sizeof(struct EFI_Container));

    /*--------------------------------------------------------------------------
     * Initialize some machine code that will return EFI_UNSUPPORTED for
     * functions returning int and simply return for void functions.
     */
    memcpy(fakeEFI->Voidret_instructions, VOIDRET_INSTRUCTIONS, sizeof(VOIDRET_INSTRUCTIONS));
    memcpy(fakeEFI->Unsupportedret_instructions, UNSUPPORTEDRET_INSTRUCTIONS, sizeof(UNSUPPORTEDRET_INSTRUCTIONS));

    //--------------------------------------------------------------------------
    EFI_SYSTEM_TABLE * efiSystemTable				= &fakeEFI->EfiSystemTable;

    efiSystemTable->Hdr.Signature					= EFI_SYSTEM_TABLE_SIGNATURE;
    efiSystemTable->Hdr.Revision					= EFI_SYSTEM_TABLE_REVISION;
    efiSystemTable->Hdr.HeaderSize					= sizeof(EFI_SYSTEM_TABLE);
    efiSystemTable->Hdr.CRC32						= 0;
    efiSystemTable->Hdr.Reserved					= 0;

	efiSystemTable->FirmwareVendor					= ptov64((EFI_PTR32) &fakeEFI->FirmwareVendor);

    memcpy(fakeEFI->FirmwareVendor, FIRMWARE_VENDOR, sizeof(FIRMWARE_VENDOR));

    efiSystemTable->FirmwareRevision				= FIRMWARE_REVISION;

    /* XXX: We may need to have basic implementations of ConIn/ConOut/StdErr */
    /* The EFI spec states that all handles are invalid after boot services have been
     * exited so we can probably get by with leaving the handles as zero. */
    efiSystemTable->ConsoleInHandle					= 0;
    efiSystemTable->ConIn							= 0;

    efiSystemTable->ConsoleOutHandle				= 0;
    efiSystemTable->ConOut							= 0;

    efiSystemTable->StandardErrorHandle				= 0;
    efiSystemTable->StdErr							= 0;

	efiSystemTable->RuntimeServices					= ptov64((EFI_PTR32) &fakeEFI->EfiRuntimeServices);

    /* According to the EFI spec, BootServices aren't valid after the
     * boot process is exited so we can probably do without it.
     * Apple didn't provide a definition for it in pexpert/i386/efi.h
     * so I'm guessing they don't use it.
     */
    efiSystemTable->BootServices					= 0;

    efiSystemTable->NumberOfTableEntries			= 0;
	efiSystemTable->ConfigurationTable				= ptov64((EFI_PTR32) fakeEFI->EfiConfigurationTable);

	// Fix checksum.
	efiSystemTable->Hdr.CRC32 = crc32(0L, efiSystemTable, efiSystemTable->Hdr.HeaderSize);

	// Used in finalizeEFITree() to update the checksum, after adding the ACPI/SMBIOS tables.
	gPlatform.EFI.SystemTable						= efiSystemTable;

    //--------------------------------------------------------------------------
    EFI_RUNTIME_SERVICES * efiRuntimeServices		= &fakeEFI->EfiRuntimeServices;

    efiRuntimeServices->Hdr.Signature				= EFI_RUNTIME_SERVICES_SIGNATURE;
    efiRuntimeServices->Hdr.Revision				= EFI_RUNTIME_SERVICES_REVISION;
    efiRuntimeServices->Hdr.HeaderSize				= sizeof(EFI_RUNTIME_SERVICES);
    efiRuntimeServices->Hdr.CRC32					= 0;
    efiRuntimeServices->Hdr.Reserved				= 0;

    /* There are a number of function pointers in the efiRuntimeServices table.
     * These are the Foundation (e.g. core) services and are expected to be present on
     * all EFI-compliant machines.  Some kernel extensions (notably AppleEFIRuntime)
     * will call these without checking to see if they are null.
     */
    void (* voidret_fp)() = (void *) fakeEFI->Voidret_instructions;
    void (* unsupportedret_fp)() = (void *) fakeEFI->Unsupportedret_instructions;

	// Be smart. Do <i>not</i> call the same function (ptov64) over and over again.
	EFI_UINT unsupportedReturnCall = ptov64((EFI_PTR32) voidret_fp);
	EFI_UINT unsupportedFunctionCall = ptov64((EFI_PTR32) unsupportedret_fp);

	efiRuntimeServices->GetTime						= unsupportedFunctionCall;
	efiRuntimeServices->SetTime						= unsupportedFunctionCall;
	efiRuntimeServices->GetWakeupTime				= unsupportedFunctionCall;
	efiRuntimeServices->SetWakeupTime				= unsupportedFunctionCall;
	efiRuntimeServices->SetVirtualAddressMap		= unsupportedFunctionCall;
	efiRuntimeServices->ConvertPointer				= unsupportedFunctionCall;
	efiRuntimeServices->GetVariable					= unsupportedFunctionCall;
	efiRuntimeServices->GetNextVariableName			= unsupportedFunctionCall;
	efiRuntimeServices->SetVariable					= unsupportedFunctionCall;
	efiRuntimeServices->GetNextHighMonotonicCount	= unsupportedFunctionCall;
	efiRuntimeServices->ResetSystem					= unsupportedReturnCall;

	// Fix checksum.
	efiRuntimeServices->Hdr.CRC32 = crc32(0L, efiRuntimeServices, efiRuntimeServices->Hdr.HeaderSize);

    /* The bootArgs structure as a whole is bzero'd so we don't need to fill in
     * things like efiRuntimeServices* and what not.
     *
     * In fact, the only code that seems to use that is the hibernate code so it
     * knows not to save the pages.  It even checks to make sure its nonzero.
     */	
    bootArgs->efiSystemTable = (uint32_t)efiSystemTable;

	// Note: Boots fine without this.
	DT__AddProperty(gPlatform.EFI.Nodes.RuntimeServices, "table", gPlatform.AddressWidth, &gPlatform.EFI.SystemTable->RuntimeServices);
}

