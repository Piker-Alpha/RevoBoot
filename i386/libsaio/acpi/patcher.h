/*
 * Original source code (dsdt_patcher for Chameleon) by mackerintel (2008)
 * Overhaul by Master Chief in 2009.
 *
 * Updates:
 *
 *			- Refactorized for Revolution by DHP in 2010.
 *			- A complete new implementation written for RevoBoot by DHP in 2011.
 *			- Automatic SSDT_PR creation added by DHP in June 2011.
 *			- Call loadBinaryData from loadACPITable (PikerAlpha, October 2012).
 *			- Moved extern declarations to saio_internal.h (PikerAlpha, October 2012).
 *			- Now using gPlatform.CommaLessModelID instead of gPlatform.ModelID (PikerAlpha, October 2012).
 *			- Fall back to non-model specific file when model specific file is unavailable (PikerAlpha, October 2012).
 */


#if PATCH_ACPI_TABLE_DATA

#if AUTOMATIC_SSDT_PR_CREATION
	#include "ssdt_pr_generator.h"
#endif


#if VERIFY_OPREGION_GNVS_ADDRESS
//==============================================================================

unsigned int search64bitPattern(unsigned int aStartAddress, int aNumberOfBytes, uint64_t aSearchPattern)
{
	unsigned char * baseAddress = (unsigned char *) aStartAddress;
	unsigned char * endAddress = (baseAddress + aNumberOfBytes);

	for (; baseAddress <= endAddress; baseAddress++)
	{
		if (*(uint64_t *)baseAddress == aSearchPattern)
		{
			_ACPI_DEBUG_DUMP("GNVS Address Found @ 0x%x\n", baseAddress);

			return (unsigned int)baseAddress; // Found!
		}
	}

	return 0; // Not found!
}
#endif // VERIFY_OPREGION_GNVS_ADDRESS


#if (LOAD_EXTRA_ACPI_TABLES && (LOAD_DSDT_TABLE_FROM_EXTRA_ACPI || LOAD_SSDT_TABLE_FROM_EXTRA_ACPI))
//==============================================================================

int loadACPITable(int tableIndex)
{
	char dirSpec[48];
	long fileSize = 0;
	void * tableAddress = (void *)kLoadAddr;
	
	bzero(dirSpec, 48);
#if LOAD_MODEL_SPECIFIC_ACPI_DATA
	// Example: /Extra/ACPI/DSDT-MacBookPro101.aml
	//          0123456789 0123456789 0123456789 1
	sprintf(dirSpec, "/Extra/ACPI/%s-%s.aml", customTables[tableIndex].name, gPlatform.CommaLessModelID);

	/*
	 * loadBinaryData calls LoadFile (both in sys.c) to load table data into a
	 * load buffer at kLoadAddr (defined in memory.h) and copies it into a new
	 * allocated memory block (kLoadAddr gets overwritten by the next call).
	 */
	fileSize = loadBinaryData(dirSpec, &tableAddress);

	if (fileSize == -1)
	{
#endif
		// File: /Extra/ACPI/DSDT-MacBookPro101.aml not found. Try: /Extra/ACPI/dsdt.aml
		sprintf(dirSpec, "/Extra/ACPI/%s.aml", customTables[tableIndex].name);
		fileSize = loadBinaryData(dirSpec, &tableAddress);
#if LOAD_MODEL_SPECIFIC_ACPI_DATA
	}
#endif

	if (fileSize > 0)
	{
		_ACPI_DEBUG_DUMP("Loading: %s (%d bytes).\n", dirSpec, fileSize);
		_ACPI_DEBUG_SLEEP(1);

		// 'tableAddress' is copied into kernel memory later on (see setupACPI).
		customTables[tableIndex].table			= tableAddress;
		customTables[tableIndex].tableLength	= fileSize;

#if (DEBUG_ACPI && LOAD_MODEL_SPECIFIC_ACPI_DATA)
		// Update table name from DSDT.aml to DSDT-Macmini51.aml (DSDT example).
		sprintf(customTables[tableIndex].fileName, gPlatform.CommaLessModelID);
#endif

		return 0;
	}

	_ACPI_DEBUG_DUMP("Error: File %s not found.)\n", dirSpec);
	_ACPI_DEBUG_SLEEP(5);

	return -1;
}


//==============================================================================

void loadACPITables(void)
{
	// DHP: We might want to change this and walk through the /Extra/ACPI/ folder for target tabels.

#if LOAD_DSDT_TABLE_FROM_EXTRA_ACPI
	loadACPITable(DSDT);
#endif // LOAD_DSDT_TABLE_FROM_EXTRA_ACPI

#if LOAD_SSDT_TABLE_FROM_EXTRA_ACPI
	// loadACPITable(APIC); Table load example!
	loadACPITable(SSDT);
	loadACPITable(SSDT_PR);	// Overrides STATIC_SSDT_PR_TABLE_DATA / AUTOMATIC_SSDT_PR_CREATION when found!
	loadACPITable(SSDT_USB);
	loadACPITable(SSDT_GPU);
	loadACPITable(SSDT_SATA);
#endif	// LOAD_SSDT_TABLE_FROM_EXTRA_ACPI

}
#endif // LOAD_EXTRA_ACPI_TABLES && (LOAD_DSDT_TABLE_FROM_EXTRA_ACPI || LOAD_SSDT_TABLE_FROM_EXTRA_ACPI)



//==============================================================================

bool replaceTable(ENTRIES * xsdtEntries, int entryIndex, int tableIndex)
{
	// Get the target table type.
	int type = essentialTables[tableIndex].type;

	_ACPI_DEBUG_DUMP("Replacing table %s\n", customTables[type].name);
	_ACPI_DEBUG_DUMP("type: %d\n", type);

#if REPLACE_EXISTING_SSDT_TABLES
	int i = SSDT_GPU;

	// SSDT tables can be replaced with optionally added tables.
	if (type == SSDT && customTables[SSDT].tableAddress == 0)
	{
		// Walk through the optional SSDT tables to find a replacement table.
		for (; i < SSDT_USB; i++)
		{
			// Do we have one?
			if (customTables[i].tableAddress)
			{
				// Yes. Use the index as type (same values).
				type = i;
				break;
			}
		}
	}
#endif	// REPLACE_EXISTING_SSDT_TABLES

	// Check address to prevent a KP.
	if (customTables[type].tableAddress)
	{
		_ACPI_DEBUG_DUMP("Replaced table: %s with custom one.\n", customTables[type].name);

		xsdtEntries[entryIndex] = (uint32_t) customTables[type].tableAddress;

		customTables[type].table = NULL;

		return true;
	}

	return false;
}


#if OVERRIDE_ACPI_METHODS
//==============================================================================

void overrideACPIMethods(ACPI_FADT *patchedFADT)
{
	// Get a handle to the factory DSDT.
	ACPI_DSDT * factoryDSDT = (ACPI_DSDT *)patchedFADT->DSDT;

	// Allocate kernel memory for the 'to-be-patched' factory DSDT.
	ACPI_DSDT * patchedDSDT = (void *)AllocateKernelMemory(factoryDSDT->Length);

	// Copy factory DSDT into newly allocated memory space.
	memcpy((void *)patchedDSDT, (void *)factoryDSDT, factoryDSDT->Length);

	// Determine the search range (top to bottom).
	void *searchStart	= (void *)patchedDSDT + patchedDSDT->Length;
	void *searchEnd		= (void *)patchedDSDT;

	// Default number of Methods to search for.
	uint8_t targetMethods = 1;

	// Search for the target method(s).
	for (; searchStart > searchEnd; searchStart--)
	{
		uint32_t data = *(uint32_t *)searchStart;

#if OVERRIDE_ACPI_METHODS == 1
		if (data == _PTS_SIGNATURE)
#elif OVERRIDE_ACPI_METHODS == 2
		if (data == _WAK_SIGNATURE)
#elif OVERRIDE_ACPI_METHODS == 3
			targetMethods = 2;
		
		if (data == _PTS_SIGNATURE || data == _WAK_SIGNATURE)
#endif
		{
			// Change namespace from _PTS /_WAK to ZPTS / ZWAK (examples).
			*((uint32_t *)((uint32_t *)searchStart)) &= 0xFFFFFF5A;

			// Did we locate all targets yet?
			if (targetMethods-- == 0)
			{
				break; // Yes.
			}
		}
	}
	// Fix checksum.
	patchedDSDT->Checksum = 0;
	patchedDSDT->Checksum = checksum8(patchedDSDT, sizeof(patchedDSDT));

	// We're done. Using the patched factory DSDT now.
	patchedFADT->DSDT = patchedFADT->X_DSDT = (uint32_t)patchedDSDT;
}
#endif	// OVERRIDE_ACPI_METHODS


//==============================================================================

bool patchFACPTable(ENTRIES * xsdtEntries, int tableIndex, int dropOffset)
{
	_ACPI_DEBUG_DUMP("FACP table patching");
		
	ACPI_FADT *factoryFADT = (ACPI_FADT *)(uint32_t)xsdtEntries[tableIndex];
	ACPI_FADT *patchedFADT = (ACPI_FADT *)AllocateKernelMemory(244); // 0xF4
		
	// The table length should be 244, but may be shorter, or greater than the amount 
	// of allocated kernel memory and thus we check it here (better safe than sorry).
	int tableLength = (factoryFADT->Length < 244) ? factoryFADT->Length : 244;
		
	// Copy factory table into kernel memory as the 'to-be-patched' table replacement.
	memcpy(patchedFADT, factoryFADT, tableLength);
		
	// Update table length (factory table might be too short so fix it).
	patchedFADT->Length = 244;
		
	// Blatantly ignoring the original revision info (using the latest and greatest). 
	patchedFADT->Revision = 4;
		
	// Macro's for some Apple styling. 
	_ACPI_SET_APPLE_OEMID(patchedFADT);
	_ACPI_SET_APPLE_OEMTargetID(patchedFADT);
		
	// Update platform type (ignoring the original value here -= 32 bytes).
	patchedFADT->PM_Profile = gPlatform.Type;
		
	if (gPlatform.CPU.Vendor == 0x756E6547) // Intel only!
	{
		_ACPI_DEBUG_DUMP(", fixed reset GAS.\n");

		// Restart fix (by Duvel300) for ACPI 2.0 and greater.
		// Note: This patch is basically a port of Master Chief's OSXRestart.kext with one 
		//		 addition; The initialization of the reset GAS (when missing).
		patchedFADT->Flags				|= 0x400;
		patchedFADT->ResetSpaceID		= 0x01;
		patchedFADT->ResetBitWidth		= 0x08;
		patchedFADT->ResetBitOffset		= 0x00;
		patchedFADT->ResetAccessWidth	= 0x01;
		patchedFADT->ResetAddress		= 0x0cf9;
		patchedFADT->ResetValue			= 0x06;
	}
#if DEBUG_ACPI
	else
	{
		printf(".\n");	
	}
#endif	// DEBUG_ACPI

#if OVERRIDE_ACPI_METHODS
	overrideACPIMethods(patchedFADT);
#elif STATIC_DSDT_TABLE_INJECTION || (LOAD_EXTRA_ACPI_TABLES && LOAD_DSDT_TABLE_FROM_EXTRA_ACPI)
	patchedFADT->DSDT = (uint32_t)customTables[DSDT].tableAddress; // The original DSDT without DSDT table injection!

#if VERIFY_OPREGION_GNVS_ADDRESS
	#define OP_REGION_GNVS_ADDRESS_LE 0x0C0053564E47805B
	// First try to locate the OperationRegion (GNVS, SystemMemory, 0xNNNNNNNN, 0xNNNN) in the factory DSDT.
	unsigned int opRegFactoryDSDTAddress = search64bitPattern(factoryFADT->DSDT + sizeof(ACPI_DSDT), 2000, OP_REGION_GNVS_ADDRESS_LE);

	if (opRegFactoryDSDTAddress) // Found?
	{
		// Yes. Get the GNVS address.
		unsigned int factoryDSDT_GNVS_Address = (*(uint32_t *)(opRegFactoryDSDTAddress + 8));
#if (DEBUG_ACPI || DUMP_OPREGION_GNVS_ADDRESS)
		printf("GNVS address (0x%x) found @: 0x%x\n", factoryDSDT_GNVS_Address, opRegFactoryDSDTAddress);
#endif
		// Now try to locate the OperationRegion (GNVS, SystemMemory, 0xNNNNNNNN, 0xNNNN) in the patched DSDT.
		unsigned int opRegPatchedDSDTAddress = search64bitPattern(patchedFADT->DSDT + sizeof(ACPI_DSDT), 2000, OP_REGION_GNVS_ADDRESS_LE);

		if (opRegPatchedDSDTAddress) // Found?
		{
			// Yes. Get the GNVS address.
			unsigned int patchedDSDT_GNVS_Address = (*(uint32_t *)(opRegPatchedDSDTAddress + 8));
#if (DEBUG_ACPI || DUMP_OPREGION_GNVS_ADDRESS)
			printf("GNVS address (0x%x) found @: 0x%08x\n", patchedDSDT_GNVS_Address, opRegPatchedDSDTAddress);
#endif
			// Are both GNVS address values the same?
			if (patchedDSDT_GNVS_Address != factoryDSDT_GNVS_Address)
			{
				_ACPI_DEBUG_DUMP("Patching GNVS address ... ");
				// Copy the 4 address bytes from the factory DSDT into the patched DSDT.
				// Note: We do not copy the length (may be different for a patched DSDT).
				memcpy((void *)opRegPatchedDSDTAddress, (void *)opRegFactoryDSDTAddress, 4);

				_ACPI_DEBUG_DUMP("Done.\n");
			}
		}
#if (DEBUG_ACPI || DUMP_OPREGION_GNVS_ADDRESS)
		sleep(1);
#endif
	}
#endif // VERIFY_OPREGION_GNVS_ADDRESS
		
	_ACPI_DEBUG_DUMP("Replacing factory DSDT with ");

	if (customTables[DSDT].tableAddress)
	{
#if STATIC_DSDT_TABLE_INJECTION
		_ACPI_DEBUG_DUMP("static DSDT data");
#elif LOAD_MODEL_SPECIFIC_ACPI_DATA
		_ACPI_DEBUG_DUMP("%s", customTables[DSDT].fileName);
#endif	// STATIC_DSDT_TABLE_INJECTION
		_ACPI_DEBUG_DUMP(" @ 0x%x\n", customTables[DSDT].tableAddress);

		patchedFADT->X_DSDT = (uint32_t)customTables[DSDT].tableAddress;

		customTables[DSDT].table = NULL;
	}
#if DEBUG_ACPI
	else
	{
		_ACPI_DEBUG_DUMP("Failed to locate DSDT replacement!\n");
	}
#endif	// DEBUG_ACPI
	
#endif	// STATIC_DSDT_TABLE_INJECTION || (LOAD_EXTRA_ACPI_TABLES && LOAD_DSDT_TABLE_FROM_EXTRA_ACPI)

#if STATIC_FACS_TABLE_INJECTION
	// Replace the factory FACS table.
	_ACPI_DEBUG_DUMP("patchedFADT->FIRMWARE_CTRL: 0x%08x\n", patchedFADT->FIRMWARE_CTRL);

	/*
	 * factoryFADT->FIRMWARE_CTRL is usually non zero on systems with less than 4GB.
	 */
	if (factoryFADT->FIRMWARE_CTRL > 0)
	{
		// In which case we must use this value
		patchedFADT->FIRMWARE_CTRL = (uint32_t) customTables[FACS].tableAddress;
		// And we must zero out this field (conform the ACPI specification).
		patchedFADT->X_FIRMWARE_CTRL = (uint64_t) 0;
	}
	else
	{
		patchedFADT->FIRMWARE_CTRL = (uint32_t) 0;
		patchedFADT->X_FIRMWARE_CTRL = (uint64_t) customTables[FACS].tableAddress;
	}

	customTables[FACS].table = NULL;
#endif	// STATIC_FACS_TABLE_INJECTION
	patchedFADT->Checksum = 0;
	patchedFADT->Checksum = checksum8(patchedFADT, sizeof(ACPI_FADT));
		
	xsdtEntries[tableIndex - dropOffset] = (uint32_t)patchedFADT;

	return true;
}
#endif // PATCH_ACPI_TABLE_DATA


/*==============================================================================
 * Function setupACPI can simply obtain the ACPI base address - for people with 
 * the perfect BIOS on their mainboards - or do more serious work like patching, 
 * updating, replacing and/or injecting new tables.
 *
 * Note: Requires the PATCH_ACPI_TABLE_DATA directive in private_data.h to be 1.
 */

void setupACPI(void)
{
	_ACPI_DEBUG_DUMP("\nEntering setupACPI(%d)\n", PATCH_ACPI_TABLE_DATA);
	
	ACPI_RSDP * factoryRSDP = getACPIBaseAddress();

	_ACPI_DEBUG_DUMP("factoryRSDP: 0x%x\n", factoryRSDP);
	_ACPI_DEBUG_SLEEP(5);

	// _ACPI_DUMP_RSDP_TABLE(factoryRSDP, "Factory");

#if PATCH_ACPI_TABLE_DATA

	ACPI_XSDT * factoryXSDT = (ACPI_XSDT *) ACPI_RXSDT_ADDRESS;

	// _ACPI_DUMP_XSDT_TABLE(factoryXSDT, "Factory");

#if AUTOMATIC_SSDT_PR_CREATION
	generateSSDT_PR();
#endif	// AUTOMATIC_SSDT_PR_CREATION

#if LOAD_EXTRA_ACPI_TABLES
	loadACPITables();
#endif	// LOAD_EXTRA_ACPI_TABLES

	_ACPI_DEBUG_DUMP("\n");

#if DROP_SELECTED_SSDT_TABLE
	const char * oemTableIdTargets[] = OEM_TABLE_ID_TARGETS;
#endif

	int cti = 0; // CustomTableIndex

	for (; customTables[cti].table; cti++)
	{
		if (customTables[cti].tableLength)
		{
			_ACPI_DEBUG_DUMP("customTable[%2d] %9s length: %d\n", cti, customTables[cti].name, customTables[cti].tableLength);

			customTables[cti].tableAddress = (void *)AllocateKernelMemory(customTables[cti].tableLength);
			memcpy((void *)customTables[cti].tableAddress, (void *)customTables[cti].table, customTables[cti].tableLength);
			
			// Did we load this table from file?
			if (customTables[cti].loaded)
			{
				// Yes. Return previously allocated memory.
				free(customTables[cti].table);
			}
		}
		else
		{
			// _ACPI_DEBUG_DUMP("No data for: %s (cleared).\n", customTables[cti].name);

			customTables[cti].table = NULL;
		}
		
		// _ACPI_DEBUG_SLEEP(1);
	}

	/*
	 * Main loop with some basic validation checks.
	 *
	 * Note: 196 offers space for twenty 64-bit table addresses.
	 *       196 - 36 = 160 / 8 = 20 tables.
	 */

	if (factoryXSDT && factoryXSDT->Length < 196 && VALID_ADDRESS(factoryRSDP, factoryXSDT))
	{
		int i, dropOffset = 0;

		// Creates a copy of the RSDP aka our to-be-patched-table.
		ACPI_RSDP * patchedRSDP = (ACPI_RSDP *) AllocateKernelMemory(sizeof(ACPI_RSDP));
		memcpy(patchedRSDP, factoryRSDP, RSDP_LENGTH);

		// Keep address for efi.c
		gPlatform.ACPI.BaseAddress = (uint32_t)patchedRSDP;

		// Creates a copy of the XSDP aka our to-be-patched-table.
		ACPI_XSDT * patchedXSDT = (ACPI_XSDT *) AllocateKernelMemory(factoryXSDT->Length);
		memcpy(patchedXSDT, factoryXSDT, factoryXSDT->Length);

		// Pseudo code to fake Apple ID's.
		_ACPI_SET_APPLE_OEMID(patchedRSDP);
		_ACPI_SET_APPLE_OEMID(patchedXSDT);
		_ACPI_SET_APPLE_OEMTargetID(patchedXSDT);

		int entryCount = (patchedXSDT->Length - sizeof(ACPI_XSDT)) / ADDRESS_WIDTH;

		// ACPI 1.0 -> ACPI 2.0 (or initializes patchedRSDP->XsdtAddress).
		updateACPITableData(patchedRSDP, patchedXSDT, entryCount);

		_ACPI_DUMP_RSDP_TABLE(patchedRSDP, "Modified");
		_ACPI_DUMP_XSDT_TABLE(patchedXSDT, "Modified");

		// Gives us a 32/64-bit pointer to the table entries (depends on compiler directives).
		ENTRIES * xsdtEntries = (ENTRIES *) (patchedXSDT + 1);

		_ACPI_DEBUG_DUMP("\nWe have %d entries to work with\n", entryCount);

		// Main loop; walks through the XSDT entries.
		for (i = 0; i < entryCount; i++)
		{
			bool tableMatch = false;

			int idx = 0;

			// Get a pointer to the current table.
			void *table = (void *)((uint32_t)xsdtEntries[i]);

			_ACPI_DEBUG_DUMP_TABLENAME(table, &tableName, i);

			// Get table signature from table.
			uint32_t tableSignature = * (uint32_t *)table;

			// Secondary loop; sequencial search for potential table targets.
			for (idx = 0; essentialTables[idx].tableSignature; idx++)
			{
				// _ACPI_DEBUG_DUMP("idx: %d\n", idx);

				// Check the list with essential tables for a match.
				if (essentialTables[idx].tableSignature == tableSignature)
				{
					tableMatch = true;

					_ACPI_DEBUG_DUMP("(Essential table)\n");

					xsdtEntries[i - dropOffset] = xsdtEntries[i];						
					
					if (essentialTables[idx].action & kPatchTable)
					{
						// Does it have a table action assigned to it?
						if (essentialTables[idx].tableAction)
						{
							_ACPI_DEBUG_DUMP("Calling tableAction(kPatchTable)\n");
							
							// Yes. Call it and let it do its thing.
							essentialTables[idx].tableAction(xsdtEntries, i, dropOffset);
						}
					}
					else if (essentialTables[idx].action & kReplaceTable)
					{
						// Does it have a table action assigned to it?
						if (essentialTables[idx].tableAction)
						{
							int type = essentialTables[idx].type;

							// 
							if (customTables[type].table)
							{
								_ACPI_DEBUG_DUMP("Calling tableAction(kReplaceTable) for %s\n", customTables[type].name);
							
								// Yes. Call it and let it do its thing.
								essentialTables[idx].tableAction(xsdtEntries, (i - dropOffset), idx);
							}
						}
					}
					else if (essentialTables[idx].action & kDropTable)
					{
#if DROP_SELECTED_SSDT_TABLE
						short tid = 0;

						if (tableSignature == SSDT_TABLE_SIGNATURE)
						{
							ACPI_SSDT * currentTable = (ACPI_SSDT *)table;

							_ACPI_DEBUG_DUMP("Checking SSDT(%s)\n", currentTable->OEMTableId);
							
							do
							{
								if (strncmp(currentTable->OEMTableId, oemTableIdTargets[tid], strlen(currentTable->OEMTableId)) == 0)
								{
									_ACPI_DEBUG_DUMP("Dropping table: %s (on request)\n", tableName);

									dropOffset++;

									break;
								}

								tid++;
							} while (oemTableIdTargets[tid] != 0);
						}
						else
						{
#endif
							_ACPI_DEBUG_DUMP("Dropping table: %s (on request)\n", tableName);

							dropOffset++;
#if DROP_SELECTED_SSDT_TABLE
						}
#endif
					}
				}

				if (tableMatch)
				{
					break;
				}
			}

			if (!tableMatch)
			{
				_ACPI_DEBUG_DUMP("(Dropped. Unused in OS X)\n");

				dropOffset++;
			}
		}

		_ACPI_DEBUG_DUMP("Dropped table count: %d\n", dropOffset);

		// printf("size: %d\n", sizeof(customTables) / sizeof(ACPITable)); // 308

		i = (entryCount - dropOffset);
		int newTableEntries = 0;

		// Now wade through the custom table entries to see if they have been assigned already.
		for (cti = 0; cti < 14; cti++)
		{
			// We need an address so check it.
			if (customTables[cti].table)
			{
				// Do we have a previously dropped table entry available for use?
				if (dropOffset)
				{
					_ACPI_DEBUG_DUMP("Using void XSDT entry[%d] for table: %s.\n", dropOffset, customTables[cti].name);

					// Yes. Reassigning XSDT table entry.
					xsdtEntries[i++] = (uint32_t)customTables[cti].tableAddress;

					customTables[cti].table = NULL;

					// One free spot filled up.
					dropOffset--;
				}
				else // Adding new entries.
				{
					_ACPI_DEBUG_DUMP("Adding new XSDT entry for table: %s.\n", customTables[cti].name);

					// Expand entry table.
					xsdtEntries[i++] = (uint32_t)customTables[cti].tableAddress;

					newTableEntries++;

					// Adjust table length.
					patchedXSDT->Length += ADDRESS_WIDTH;
				}
			}
		}

		_ACPI_DEBUG_DUMP("patchedXSDT->Length (current): %d\n", patchedXSDT->Length);

		// Did we drop tables without using them for new tables?
		if (dropOffset)
		{
			// Yes, fix length.
			patchedXSDT->Length -= (ADDRESS_WIDTH * dropOffset);

			_ACPI_DEBUG_DUMP("patchedXSDT->Length (changed): %d/%d\n", patchedXSDT->Length, (patchedXSDT->Length / ADDRESS_WIDTH));
		}

		_ACPI_DEBUG_DUMP("\nRecalculating checksums / ");

		// Patch the checksum of the new XSDP table.
        patchedXSDT->Checksum = 0;
        patchedXSDT->Checksum = checksum8(patchedXSDT, patchedXSDT->Length);

		// Patch the checksum of the new RSDP table.
		patchedRSDP->Checksum = 0;
		patchedRSDP->Checksum = checksum8(patchedRSDP, 20);

		// Patch the (extended) checksum of the RSDP for table revision 1 and greater. 
		if (patchedRSDP->Revision)
		{
			patchedRSDP->ExtendedChecksum = 0;
			patchedRSDP->ExtendedChecksum = checksum8(patchedRSDP, patchedRSDP->Length);
		}
    }

#else // No patching done.

	// Init base address, pointing to newly allocated kernel memory,
	// used to initialize the "ACPI_20" efi->configuration-table.
	gPlatform.ACPI.BaseAddress = (uint32_t)factoryRSDP;

	_ACPI_DEBUG_DUMP("Factory ACPI tables untouched \n");

#endif // PATCH_ACPI_TABLE_DATA

	_ACPI_DEBUG_DUMP("About to exit setupACPI() ");

	_ACPI_DEBUG_SLEEP(20);

}
