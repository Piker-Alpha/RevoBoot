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
 * EFI implementation for Revolution Copyright (c) 2010 by DHP. All rights reserved.
 *
 * Updates:
 *
 *			- STATIC_MODEL_NAME moved over from settings.h (PikerAlpha, October 2012).
 *			- STATIC_MODEL_NAME renamed to EFI_MODEL_NAME (PikerAlpha, October 2012).
 *			- Now no longer includes platform.h (PikerAlpha, October 2012).
 *			- Data selector moved over from RevoBoot/i386/config/data.h (PikerAlpha, October 2012).
 *			- Get static EFI data (optional) from /Extra/EFI/[MacModelNN].bin (PikerAlpha, October 2012).
 *			- STATIC_SYSTEM_SERIAL_NUMBER renamed to EFI_SYSTEM_SERIAL_NUMBER (PikerAlpha, October 2012).
 *			- Check return of malloc call (PikerAlpha, November 2012).
 *			- Sam's workaround for iMessage breakage added (PikerAlpha, January 2013).
 *
 */

#include "efi/fake_efi.h"


/* #if LOAD_MODEL_SPECIFIC_EFI_DATA
//==============================================================================

void useStaticEFIProperties(Node * aEFINode)
{
	// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
	#include STRING(EFI_DATA_FILE)
	
	static EFI_UINT8 const EFI_DEVICE_PROPERTIES[] =
	{
		// Replaced with data from: RevoBoot/i386/config/EFI/[data-template/MacModelNN].h
		STATIC_EFI_DEVICE_PROPERTIES
	};
	
	DT__AddProperty(aEFINode, "device-properties", sizeof(EFI_DEVICE_PROPERTIES), (EFI_CHAR8*) &EFI_DEVICE_PROPERTIES);
	
	// _EFI_DEBUG_DUMP("Using statically linked EFI device-properties\n");
}
#endif */

//==============================================================================
// Called from RevoBoot/i386/libsaio/platform.c

void initEFITree(void)
{
	_EFI_DEBUG_DUMP("Entering initEFITree(%x)\n", gPlatform.ACPI.Guid.Data1);

	static char ACPI[] = "ACPI";

	// The information from RevoBoot/i386/libsaio/SMBIOS/model_data.h is used here.
	static EFI_CHAR16 const MODEL_NAME[]			= EFI_MODEL_NAME;
	static EFI_CHAR16 const SYSTEM_SERIAL_NUMBER[]	= EFI_SYSTEM_SERIAL_NUMBER;

	DT__Initialize(); // Add and initialize gPlatform.DT.RootNode

	/*
	 * The root node is available until the call to DT__Finalize, or the first call 
	 * to DT__AddChild with NULL as first argument. Which we don't do and thus we 
	 * can use it in the meantime, instead of defining a local / global variable.
	 */

	DT__AddProperty(gPlatform.DT.RootNode, "model", 5, ACPI);
	DT__AddProperty(gPlatform.DT.RootNode, "compatible", 5, ACPI);
	
	Node * efiNode = DT__AddChild(gPlatform.DT.RootNode, "efi");

	DT__AddProperty(efiNode, "firmware-abi", 6, (gPlatform.ArchCPUType == CPU_TYPE_X86_64) ? "EFI64" : "EFI32");
	DT__AddProperty(efiNode, "firmware-revision", sizeof(FIRMWARE_REVISION), (EFI_UINT32*) &FIRMWARE_REVISION);
	DT__AddProperty(efiNode, "firmware-vendor", sizeof(FIRMWARE_VENDOR), (EFI_CHAR16*) FIRMWARE_VENDOR);

	// Initialize a global var, used by function setupEFITables later on, to
	// add the address to the boot arguments (done to speed up the process).
	gPlatform.EFI.Nodes.RuntimeServices = DT__AddChild(efiNode, "runtime-services");

	// Initialize a global var, used by function addConfigurationTable later on, 
	// to add the SMBIOS and ACPI tables (done to speed up the process).
	gPlatform.EFI.Nodes.ConfigurationTable = DT__AddChild(efiNode, "configuration-table");

	Node * platformNode = DT__AddChild(efiNode, "platform");

	gPlatform.EFI.Nodes.Platform = platformNode;

	// Satisfying AppleACPIPlatform.kext
	static EFI_UINT8 const DEVICE_PATHS_SUPPORTED[] = { 0x01, 0x00, 0x00, 0x00 };

	DT__AddProperty(platformNode, "DevicePathsSupported", sizeof(DEVICE_PATHS_SUPPORTED), (EFI_UINT8*) &DEVICE_PATHS_SUPPORTED);

	// The use of sizeof() here is mandatory (to prevent breakage).
	DT__AddProperty(platformNode, "Model", sizeof(MODEL_NAME), (EFI_CHAR16*) MODEL_NAME);
	DT__AddProperty(platformNode, "SystemSerialNumber", sizeof(SYSTEM_SERIAL_NUMBER), (EFI_CHAR16*) SYSTEM_SERIAL_NUMBER);

	if (gPlatform.CPU.FSBFrequency)
	{
		_EFI_DEBUG_DUMP("Adding FSBFrequency property (%dMHz)\n", (gPlatform.CPU.FSBFrequency / 1000));
		DT__AddProperty(platformNode, "FSBFrequency", sizeof(uint64_t), &gPlatform.CPU.FSBFrequency);
	}

	Node * chosenNode = DT__AddChild(gPlatform.DT.RootNode, "chosen");

	if (chosenNode == 0)
	{
		stop("Couldn't create /chosen node"); // Mimics boot.efi
	}

	gPlatform.EFI.Nodes.MemoryMap = DT__AddChild(chosenNode, "memory-map");

	// Adding the root path for kextcache.
	DT__AddProperty(chosenNode, "boot-device-path", 38, "\\System\\Library\\CoreServices\\boot.efi");

	/* static EFI_UINT8 const BOOT_DEVICE_PATH[] =
	{
		0x02, 0x01, 0x0C, 0x00, 0xD0, 0x41, 0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00,
		0x02, 0x1F, 0x03, 0x12, 0x0A, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x2A, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x28, 0x40, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x0B, 0x63, 0x34,
		0x00, 0x00, 0x00, 0x00, 0x65, 0x8C, 0x53, 0x3F, 0x1B, 0xCA, 0x83, 0x38, 0xA9, 0xD0, 0xF0, 0x46,
		0x19, 0x14, 0x8E, 0x31, 0x02, 0x02, 0x7F, 0xFF, 0x04, 0x00
	};

	DT__AddProperty(chosenNode, "boot-device-path", sizeof(BOOT_DEVICE_PATH), &BOOT_DEVICE_PATH); */

	// Adding the default kernel name (mach_kernel) for kextcache.
	DT__AddProperty(chosenNode, "boot-file", sizeof(bootInfo->bootFile), bootInfo->bootFile);

#if APPLE_STYLE_EFI

	static EFI_UINT8 const BOOT_FILE_PATH[] =
	{
		0x04, 0x04, 0x50, 0x00, 0x5c, 0x00, 0x53, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74, 0x00, 0x65, 0x00, 
		0x6d, 0x00, 0x5c, 0x00, 0x4c, 0x00, 0x69, 0x00, 0x62, 0x00, 0x72, 0x00, 0x61, 0x00, 0x72, 0x00,
		0x79, 0x00, 0x5c, 0x00, 0x43, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x65, 0x00, 0x53, 0x00, 0x65, 0x00,
		0x72, 0x00, 0x76, 0x00, 0x69, 0x00, 0x63, 0x00, 0x65, 0x00, 0x73, 0x00, 0x5c, 0x00, 0x62, 0x00, 
		0x6f, 0x00, 0x6f, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x66, 0x00, 0x69, 0x00, 0x00, 0x00, 
		0x7f, 0xff, 0x04, 0x00
	};

	DT__AddProperty(chosenNode, "boot-file-path", sizeof(BOOT_FILE_PATH), (EFI_UINT8*) &BOOT_FILE_PATH);

	static EFI_UINT8 const BOOT_ARGS[] = { 0x00 };

	DT__AddProperty(chosenNode, "boot-args", sizeof(BOOT_ARGS), (EFI_UINT8*) &BOOT_ARGS);

	/* Adding kIOHibernateMachineSignatureKey (IOHibernatePrivate.h).
	 *
	 * This 'Hardware Signature' (offset 8 in the FACS table) is calculated by the BIOS on a best effort 
	 * basis to indicate the base hardware configuration of the system such that different base hardware 
	 * configurations  can have different hardware signature values. OSPM uses this information in waking 
	 * from an S4 state, by comparing the current hardware signature to the signature values saved in the 
	 * non-volatile sleep image. If the values are not the same, OSPM assumes that the saved non-volatile 
	 * image is from a different hardware configuration and cannot be restored.
	 */
	
	static EFI_UINT8 const MACHINE_SIGNATURE[] = { 0x00, 0x00, 0x00, 0x00 };

	DT__AddProperty(chosenNode, "machine-signature", sizeof(MACHINE_SIGNATURE), (EFI_UINT8*) &MACHINE_SIGNATURE);

#if ((MAKE_TARGET_OS & LION) == LION)

	// Used by boot.efi - cosmetic only node/properties on hacks.
	Node * kernelCompatNode = DT__AddChild(efiNode, "kernel-compatibility");

	static EFI_UINT8 const COMPAT_MODE[] = { 0x01, 0x00, 0x00, 0x00 };

	DT__AddProperty(kernelCompatNode, "i386", sizeof(COMPAT_MODE), (EFI_UINT8*) &COMPAT_MODE);
	DT__AddProperty(kernelCompatNode, "x86_64", sizeof(COMPAT_MODE), (EFI_UINT8*) &COMPAT_MODE);
#endif

	// Adding the options node breaks AppleEFINVRAM (missing hardware UUID).
	// Node *optionsNode = DT__AddChild(gPlatform.DT.RootNode, "options");
	// DT__AddProperty(optionsNode, "EFICapsuleResult", 4, "STAR"); // 53 54 41 52

#endif

	gPlatform.EFI.Nodes.Chosen = chosenNode;

#if INJECT_EFI_DEVICE_PROPERTIES
	_EFI_DEBUG_DUMP("Injecting static EFI device-properties\n");

	#if LOAD_MODEL_SPECIFIC_EFI_DATA
		char dirSpec[32] = "";
		sprintf(dirSpec, "/Extra/EFI/%s.bin", gPlatform.CommaLessModelID);

		_EFI_DEBUG_DUMP("Loading: %s\n", dirSpec);

		void * staticEFIData = (void *)kLoadAddr;

		long fileSize = loadBinaryData(dirSpec, &staticEFIData);

		if (fileSize > 0)
		{
			DT__AddProperty(efiNode, "device-properties", fileSize, (EFI_CHAR8*) staticEFIData);
		}
		else // No model specific data found. Use static EFI data from RevoBoot/i386/config/EFI
		{
			// useStaticEFIProperties(efiNode);
			// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
			#include STRING(EFI_DATA_FILE)
			
			static EFI_UINT8 const EFI_DEVICE_PROPERTIES[] =
			{
				// Replaced with data from: RevoBoot/i386/config/EFI/[data-template/MacModelNN].h
				STATIC_EFI_DEVICE_PROPERTIES
			};
			
			DT__AddProperty(efiNode, "device-properties", sizeof(EFI_DEVICE_PROPERTIES), (EFI_CHAR8*) &EFI_DEVICE_PROPERTIES);
		}
	#else
		// The STRING (macro) is defined in RevoBoot/i386/config/settings.h
		#include STRING(EFI_DATA_FILE)
	
		static EFI_UINT8 const EFI_DEVICE_PROPERTIES[] =
		{
			// Replaced with data from: RevoBoot/i386/config/EFI/[data-template/MacModelNN].h
			STATIC_EFI_DEVICE_PROPERTIES
		};
	
		DT__AddProperty(efiNode, "device-properties", sizeof(EFI_DEVICE_PROPERTIES), (EFI_CHAR8*) &EFI_DEVICE_PROPERTIES);
	#endif
#endif

	_EFI_DEBUG_DUMP("Exiting initEFITree()\n");
	_EFI_DEBUG_SLEEP(5);
}


#ifndef SMB_STATIC_SYSTEM_UUID
/*==============================================================================

static EFI_CHAR8 * getSmbiosUUID()
{
	bool error = TRUE;

	UInt8 *p = (UInt8 *)gPlatform.UUID;

	for (int i = 0; i < 16; i++)
	{
		if (p[i] != 0x00 || p[i] != 0xff)
		{
			error = FALSE;
		}
	}

	if (error)
	{
		printf("No proper UUID found in the System Information Table\n");
		return NULL;
	}

	return (EFI_CHAR8 *)gPlatform.UUID;
}
 */
#endif


//==============================================================================
// Stage two EFI initialization (after getting data from com.apple.Boot.plist).

void updateEFITree(char *rootUUID)
{
	_EFI_DEBUG_DUMP("In updateEFITree(%s)\n", rootUUID);

	// Only accept a UUID with the correct length.
	if (strlen(rootUUID) == 36)
	{
		_EFI_DEBUG_DUMP("Initializing property boot-uuid (%s)\n", rootUUID);
		
		DT__AddProperty(gPlatform.EFI.Nodes.Chosen, "boot-uuid", 37, rootUUID);
	}

	/* 
	 * Check the architectures' target (boot) mode against the chosen setting of  
	 * EFI_64_BIT, which may not fit well and throw the dreadful
	 * "tsc_init: EFI not supported" (due to a mismatch of the chosen/supported 
	 * boot/EFI mode) or KP with a page fault after booting with EFI_64_BIT set 
	 * to 0 on a 64-bit platform (can be done - read my comment in platform.c).
	 */

	if (bootArgs->efiMode != ((EFI_64_BIT) ? 64 : 32))
	{
		stop("EFI_64_BIT setting (%d) error detected (%d)!\n", EFI_64_BIT, bootArgs->efiMode);
	}

	_EFI_DEBUG_SLEEP(5);
}


#if INCLUDE_MPS_TABLE
//==============================================================================

bool initMultiProcessorTableAdress(void)
{
	// Is the base address initialized already?
	if (gPlatform.MPS.BaseAddress != 0)
	{
		// Yes (true for dynamic SMBIOS gathering only).
		return true;
	}
	else
	{
		// The MP table is usually located after the factory SMBIOS table (aka
		// (a dynamic run). Not when you use static SMBIOS data, which is when 
		// we have to search the whole area – hence the use of directives here.
#if USE_STATIC_SMBIOS_DATA
		void *baseAddress = (void *)0x000F0000;
#else
		void *baseAddress = &gPlatform.SMBIOS.BaseAddress;
#endif
	
		for(; baseAddress <= (void *)0x000FFFFF; baseAddress += 16)
		{
			// Do we have a Multi Processor signature match?
			if (*(uint32_t *)baseAddress == 0x5f504d5f) // _MP_ signature.
			{
				// Yes, set address and return true.
				gPlatform.MPS.BaseAddress = (uint32_t)baseAddress;
			
				return true;
			}
		}
	}

	// No _MP_ signature found.
	return false;
}
#endif // #if INCLUDE_MP_TABLE


//==============================================================================
// Called from execKernel() in boot.c

void finalizeEFITree(EFI_UINT32 kernelAdler32)
{
	_EFI_DEBUG_DUMP("done).Calling setupEFITables(");

	setupEFITables();
	
	DT__AddProperty(gPlatform.EFI.Nodes.Chosen, "boot-kernelcache-adler32", sizeof(EFI_UINT32), (EFI_UINT32*)kernelAdler32);

	setupSMBIOS();

	_EFI_DEBUG_DUMP("done).\nAdding EFI configuration table for SMBIOS(");

	addConfigurationTable(&gPlatform.SMBIOS.Guid, &gPlatform.SMBIOS.BaseAddress, NULL);

#ifdef SMB_STATIC_SYSTEM_UUID
	// Static UUID from: RevoBoot/i386/config/SETTINGS/MacModelNN.h
	static EFI_CHAR8 const SYSTEM_ID[] = SMB_STATIC_SYSTEM_UUID;
	
	DT__AddProperty(gPlatform.EFI.Nodes.Platform, "system-id", 16, (EFI_CHAR8 *) &SYSTEM_ID);
#else
	// DT__AddProperty(gPlatform.EFI.Nodes.Platform, "system-id", 16, getSmbiosUUID());
	DT__AddProperty(gPlatform.EFI.Nodes.Platform, "system-id", 16, (EFI_CHAR8 *)gPlatform.UUID);
#endif
	
	//
	// Start of experimental code
	//
	
	Node *revoEFINode = DT__AddChild(gPlatform.DT.RootNode, "RevoEFI");
	
#ifdef STATIC_NVRAM_ROM
	static EFI_UINT8 const NVRAM_ROM_DATA[] = STATIC_NVRAM_ROM;
#else
#ifdef SMB_STATIC_SYSTEM_UIID
	static EFI_UINT8 const NVRAM_ROM_DATA[] = SMB_STATIC_SYSTEM_UUID;
#else
	static EFI_UINT8 const NVRAM_ROM_DATA[] = gPlatform.UUID;
#endif
#endif
	
	DT__AddProperty(revoEFINode, "NVRAM:ROM", sizeof(NVRAM_ROM_DATA), (EFI_UINT8 *) &NVRAM_ROM_DATA);
	
	static EFI_UINT8 const NVRAM_MLB_DATA[] = STATIC_NVRAM_MLB;
	DT__AddProperty(revoEFINode, "NVRAM:MLB", sizeof(NVRAM_MLB_DATA), (EFI_UINT8 *) &NVRAM_MLB_DATA);

	//
	// End of experimental code
	//

#if INCLUDE_MPS_TABLE
	// This BIOS includes a MP table?
	if (initMultiProcessorTableAdress())
	{
		// The EFI specification dictates that the MP table must be reallocated 
		// when is it not in the right spot. We don't bother about this rule 
		// simply because we're not - pretending to be - EFI compliant.
		addConfigurationTable(&gPlatform.MPS.Guid, &gPlatform.MPS.BaseAddress, NULL);
	}
#endif

	_EFI_DEBUG_DUMP("done)\nCalling setupACPI(");

	// DHP: Pfff. Setting DEBUG to 1 in acpi_patcher.c breaks our layout!
	setupACPI();

	_EFI_DEBUG_DUMP("done).\nAdding EFI configuration table for ACPI(");

	addConfigurationTable(&gPlatform.ACPI.Guid, &gPlatform.ACPI.BaseAddress, "ACPI_20");

	_EFI_DEBUG_DUMP("done).\nFixing checksum... ");

	// Now fixup the CRC32 and we're done here.
	gPlatform.EFI.SystemTable->Hdr.CRC32 = 0;
	gPlatform.EFI.SystemTable->Hdr.CRC32 = crc32(0L, gPlatform.EFI.SystemTable, 
												 gPlatform.EFI.SystemTable->Hdr.HeaderSize);

	_EFI_DEBUG_DUMP("(done).\n");
	_EFI_DEBUG_SLEEP(10);
}
