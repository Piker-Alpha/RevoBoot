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
 * Portions of source code Copyright (c) 2008 by Macerintel, additional 
 * changes by: Master Chief (2009) and Rekursor in 2009. All rights reserved.
 *
 * EFI implementation for Revolution Copyright (c) 2010 by DHP.
 * All rights reserved.
 *
 * Updates:
 *
 *			- Moved #include to end of file, eliminating need of extern in patcher.h (PikerAlpha, October 2012).
 */


#include "platform.h"

#include "acpi/essentials.h"				// Depends on ACPI_10_SUPPORT.
#include "acpi/debug.h"						// Depends on the DEBUG directive.


//==========================================================================

void updateACPITableData(struct acpi_2_rsdp * rsdp, struct acpi_2_xsdt * xsdt, int entryCount)
{
#if ACPI_10_SUPPORT

	_ACPI_DEBUG_DUMP("\nPatching RSDP and RSDT tables... ");

	// Update revision info (fake ACPI 2.0).
	rsdp->Revision = 1;
	
	// Update pointers.
	rsdp->RsdtAddress = (uint32_t) xsdt;
	rsdp->XsdtAddress = rsdp->RsdtAddress;
	
	// Expand length (32-bit -> 64-bit addresses).
	rsdp->Length = sizeof(struct acpi_2_xsdt) + (entryCount * 8);
	
	// Set initial checksum (will be corrected at the end of this run).
	rsdp->Checksum = 0;
	rsdp->ExtendedChecksum = 0;
	
	// Change RSDT signature into XSDT.
	xsdt->Signature[0] = 'X';

#else
	_ACPI_DEBUG_DUMP("\nUpdating XSDT address... ");

	rsdp->XsdtAddress = (uint32_t) xsdt;

#endif // ACPI_10_SUPPORT

	_ACPI_DEBUG_DUMP("(done).\n");
}


#if APPLE_STYLE_ACPI
	//------------------------- Used in acpi/patcher.h -------------------------
	#define _ACPI_SET(target, str, len) strncpy(target, str, len)
	#define _ACPI_SET_APPLE_OEMID(target) _ACPI_SET((target)->OEMID, "Apple ", 6)
	#define _ACPI_SET_APPLE_OEMTargetID(target) _ACPI_SET((target)->OEMTableID, gPlatform.CommaLessModelID, 8)
	//--------------------------------------------------------------------------
#else
	//--------------------------- Void replacements ----------------------------
	#define _ACPI_SET(target, str, len)
	#define _ACPI_SET_APPLE_OEMID(target)
	#define _ACPI_SET_APPLE_OEMTargetID(target)
	//--------------------------------------------------------------------------
#endif


//==============================================================================
// Original version written by macerintel (?). Rewrite by Master Chief in 2009.

struct acpi_2_rsdp * getACPIBaseAddress()
{
	_ACPI_DEBUG_DUMP("getACPIBaseAddress(");

#if USE_STATIC_ACPI_BASE_ADDRESS
	_ACPI_DEBUG_DUMP("0x%08x)\n", STATIC_ACPI_BASE_ADDRESS);
	_ACPI_DEBUG_SLEEP(5);

	return (void *)STATIC_ACPI_BASE_ADDRESS;
#else
	void *baseAddress = (void *)0x000E0000;
	
	for (; baseAddress <= (void *)0x000FFFFF; baseAddress += 16)
	{
		if (*(uint64_t *)baseAddress == ACPI_SIGNATURE_UINT64_LE)
		{
			if (checksum8(baseAddress, 20) == 0)
			{
				uint8_t revision = ((struct acpi_2_rsdp*)baseAddress)->Revision;
				
				if (revision == 0 || 
					(revision > 0 && checksum8(baseAddress, sizeof(struct acpi_2_rsdp)) == 0))
				{
					_ACPI_DEBUG_DUMP("0x%08x)\n", baseAddress);

					return baseAddress;
				}
			}
		}
	}

	_ACPI_DEBUG_DUMP("NULL)\n");

	return NULL;
#endif
}

#include "acpi/patcher.h" // Macro's in this include file must be live now.
