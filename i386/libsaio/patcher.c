/*
 * Copyright (c) 2016 Pike R. Alpha. All rights reserved.
 *
 * Updates:
 *			- Moved function patchKernel from load.c to patcher.c (Pike R. Alpha, August 2016)
 *			- Cleanups/removed some of the old style patches (more to follow).
 *			- Function disableMSRs added.
 *			- Patch bit mask added to speedup the main while loop.
 *			- Reducing the number of compiler derectives (make it much easier to handle).
 *			- Latest source code from Vector implemented.
 *			- Checks added to catch errors in config.h (think MacPro61.h etc).
 *
 */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "platform.h"

#if (PATCH_KERNEL && ((MAKE_TARGET_OS & EL_CAPITAN) == EL_CAPITAN))
//==============================================================================
// Called from patchKernel()

void disableMSRs(unsigned char * aPointer, uint8_t aNumberOfTargetMSRs)
{
	//
	// Array with target MSRs that we need to disable.
	//
	const uint16_t targetMSRs[] = { 0xE2, 0x01A0, /* 0x01FC, */ 0x01AA, 0x0620, /* 0x064C, */ 0x063A, 0x0642 };
	//
	// Main for-loop.
	//
	for (char x = 0; x < aNumberOfTargetMSRs; x++)
	{
		//
		// Secondary for-loop to find MSRs that we need to disable.
		//
		for (uint8_t y = 0; y < (sizeof(targetMSRs) / sizeof(short)); y++)
		{
			//
			// Target MSR?
			//
			if (*(uint16_t *)aPointer == targetMSRs[y])
			{
				//
				// Yes.
				//
				DEBUG_DISABLED_MSR(targetMSRs[y], 1)
				//
				// Zero out the 32-bit CPU-bits field.
				//
				*(uint32_t *)(aPointer + 4) = 0x00000000UL;
				//
				// Done (MSR is disabled).
				//
				break;
			}
		}
		
		aPointer += 0x30;
	}
}

			 
//==============================================================================
// Called from decodeMachO()

long patchKernel(unsigned long loadAddress, unsigned long cmdBase, long listSize, unsigned long textSegmentAddress, unsigned long vldSegmentAddress)
{
#if DEBUG_KERNEL_PATCHER
	printf("patchKernel() called\n");
	sleep(1);
#endif

	char * symbolName = NULL;
	unsigned char * p = NULL;
	//
	// Option to skip first nth symbols (speeds up the search process).
	//
	int skippedSymbolCount	= 0; // (3000 * listSize);

	long symbolNumber		= 0;

	uint32_t targetSections	= 9;
	uint32_t targetPatches	= 1;

	struct symtab_command * symtab = (struct symtab_command *)cmdBase;
	struct segment_command_64 * textSegment = (struct segment_command_64 *)textSegmentAddress;
#if PRELINKED_KERNEL_SUPPORT
	struct segment_command_64 * vldSegment = (struct segment_command_64 *)vldSegmentAddress;
	
	targetSections |= 25;
#endif

	void * stringTable = (void *)(loadAddress + symtab->stroff);

	uint32_t pointer = (loadAddress + symtab->symoff + skippedSymbolCount);
	
	int64_t offset			= 0;

	uint64_t startAddress	= 0;
	uint64_t endAddress		= 0;

	uint8_t cpuid_set_info_ModelCorrection = 0;
	uint8_t xcpm_bootstrap_ModelCorrection = 0;

#if (PATCH_CPUID_SET_INFO == 0)
	switch (gPlatform.CPU.Model)
	{
		case CPU_MODEL_BROADWELL_E:
			targetPatches					+= 2;
			cpuid_set_info_ModelCorrection	= -8;
			break;
	}
#else
	targetPatches							+= 2;
	cpuid_set_info_ModelCorrection			= PATCH_CPUID_SET_INFO;
#endif
	
#if (PATCH_XCPM_BOOTSTRAP == 0)
	switch (gPlatform.CPU.Model)
	{
		case CPU_MODEL_IB_CORE:
			targetPatches					+= 4;
			xcpm_bootstrap_ModelCorrection	= -1;
			break;

		case CPU_MODEL_IB_CORE_EX:
			targetPatches					+= 4;
			xcpm_bootstrap_ModelCorrection	= -2;
			break;
			
		case CPU_MODEL_HASWELL_E:
			targetPatches					+= 4;
			xcpm_bootstrap_ModelCorrection	= -3;
			break;
			
		case CPU_MODEL_BROADWELL_E:
			targetPatches					+= 4;
			xcpm_bootstrap_ModelCorrection	= -8;
			break;
	}
#else
	targetPatches							+= 4;
	xcpm_bootstrap_ModelCorrection			= PATCH_XCPM_BOOTSTRAP;
#endif
	//
	// Is MSR(0xE2) locked (bit-15 set)?
	//
	if (gPlatform.CPU.CstConfigMsrLocked)
	{
		//
		// Yes. Enable patches: _xcpm_idle(8), _xcpm_SMT_scope_msrs(16), _xcpm_core_scope_msrs(32), _xcpm_pkg_scope_msrs(64)
		//
		targetPatches += 120;
	}
	//
	// Main while loop.
	//
	while ((symbolNumber < symtab->nsyms) && targetSections)
	{
		struct nlist_64 * nl = (struct nlist_64 *)pointer;

        offset			= 0;
        startAddress	= 0;
        endAddress		= 0;

		if (nl->n_sect == 1 && nl->n_value && (targetSections & nl->n_sect)) // __TEXT,__text
		{
			symbolName = (char *)stringTable + nl->n_un.n_strx;

			if ((targetPatches & 1) && strcmp(symbolName, "__ZN6OSKext14loadExecutableEv") == 0)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x300);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (p = (unsigned char *)startAddress; p <= (unsigned char *)endAddress; p++)
				{
					//
					// Search pattern: 89 C3 48 85 DB 74 71 48 (in HexEdit)
					//
					if ((*(uint32_t *)p == 0x8548c389) && (*(uint16_t *)(p + 4) == 0x74db) && (*(uint8_t *)(p + 7) == 0x48))
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)
						
						*(uint64_t *)p = 0x4812ebdb8548c389;
						//                   ^^^^
						//
						// Done. Disable this patch.
						//
						p = (unsigned char *)endAddress;
						targetPatches =~ 1;
					}
				}
			}
			else if ((targetPatches & 2) && strcmp(symbolName, "_cpuid_set_info") == 0)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x2100);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (p = (unsigned char *)startAddress; p <= (unsigned char *)endAddress; p++)
				{
					//
					// Search pattern: 0F B6 C4 83 C0 E9 83 F8 (in HexEdit).
					//
					if ((*(uint32_t *)p == 0x83c4b60f) && (*(uint8_t *)(p + 4) == 0xc0) && (*(uint16_t *)(p + 6) == 0xf883))
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						// *(uint8_t *)(p + 5) = (*(uint8_t *)(p + 5) + PATCH_CPUID_SET_INFO);
						*(uint8_t *)(p + 5) = (*(uint8_t *)(p + 5) + cpuid_set_info_ModelCorrection);
						//
						// Done. Disable this patch.
						//
						p = (unsigned char *)endAddress;
						targetPatches =~ 2;
					}
				}
			}
			else if ((targetPatches & 4) && strcmp(symbolName, "_xcpm_bootstrap") == 0)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x100);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (p = (unsigned char *)startAddress; p <= (unsigned char *)endAddress; p++)
				{
					//
					// Search pattern: 83 C3 xx 83 FB 22 77 1C (in HexEdit).
					//
					if ((*(uint16_t *)p == 0xc383) && (*(uint32_t *)(p + 3) == 0x7722fb83) && (*(uint8_t *)(p + 7) == 0x1C))
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						// *(uint8_t *)(p + 2) = (*(uint8_t *)(p + 2) + PATCH_XCPM_BOOTSTRAP);
						*(uint8_t *)(p + 2) = (*(uint8_t *)(p + 2) + xcpm_bootstrap_ModelCorrection);
						//
						// Done. Disable this patch.
						//
						p = (unsigned char *)endAddress;
						targetPatches =~ 4;
					}
				}
			}
			else if ((targetPatches & 8) && strcmp(symbolName, "_xcpm_idle") == 0) // 2 MSRs (0xE2, 0xE2)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x200);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (p = (unsigned char *)startAddress; p <= (unsigned char *)endAddress; p++)
				{
					if (*(uint64_t *)p == 0x300f000000e2b920)// (48 C1 EA) 20 B9 E2 00 00 00 0F 30 reversed
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						*(uint32_t *)(p + 4) = 0x90900000; // Reversed 00 00 90 90 (4 bytes).
						//
						// Done. Disable this patch.
						//
						p = (unsigned char *)endAddress;
						targetPatches =~ 8;
					}
				}
			}
			//
			// Are we done patching for this section?
			//
			if (targetPatches == 0)
			{
				//
				// Yes. Disable this section.
				//
				targetSections =~ nl->n_sect;
			}
		}
		else if (nl->n_sect == 8 && nl->n_value && (targetSections & nl->n_sect)) // __DATA,__data
		{
			symbolName = (char *)stringTable + nl->n_un.n_strx;

			if ((targetPatches & 16) && strcmp(symbolName, "_xcpm_SMT_scope_msrs") == 0)
			{
				//
				// 11 MSRs (0xE2, 0x01A0, 0x01B0, 0x01B0, 0x01B0, 0x0609, 0x038D, 0x038F, 0x0187, 0x0188, 0x0189)
				//
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, startAddress)
				//
				// Disable MSR's from config.h
				//
				disableMSRs((unsigned char *)startAddress, 11);
				//
				// Done. Disable this patch.
				//
				targetPatches =~ 16;
			}
			else if ((targetPatches & 32) && strcmp(symbolName, "_xcpm_core_scope_msrs") == 0)
			{
				//
				// 2 MSRs (0xE2, 0xE2)
				//
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, startAddress)
				//
				// Disable MSR's from config.h
				//
				disableMSRs((unsigned char *)startAddress, 2);
				//
				// Done. Disable this patch.
				//
				targetPatches =~ 32;
			}
			else if ((targetPatches & 64) && strcmp(symbolName, "_xcpm_pkg_scope_msrs") == 0)
			{
				//
				// 7 MSRs (0x01A0, 0x01FC, 0x01AA, 0x0620, 0x064C, 0x063A, 0x0642)
				//
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, startAddress)
				//
				// Disable MSR's from config.h
				//
				disableMSRs((unsigned char *)startAddress, 7);
				//
				// Done. Disable this patch.
				//
				targetPatches =~ 64;

			}
			//
			// Are we done patching for this section?
			//
			if ((targetPatches & 112) == 0)
			{
				//
				// Yes. Disable this section.
				//
				targetSections =~ nl->n_sect;
			}
		}
#if PRELINKED_KERNEL_SUPPORT
		else if (nl->n_sect == 25 && nl->n_value && (targetSections & nl->n_sect)) // __KLD,__text
		{
			symbolName = (char *)stringTable + nl->n_un.n_strx;
			
			if ((targetPatches & 128) && strcmp(symbolName, "__ZN12KLDBootstrap21readStartupExtensionsEv") == 0)
			{
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);
				uint64_t endAddress = (startAddress + 0x3f);

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)
				
				for (p = (unsigned char *)startAddress; p <= (unsigned char *)endAddress; p++)
				{
					if (*(uint64_t *)p == 0xe805eb00000025e8) // E8 25 00 00 00 EB 05 E8 (in HexEdit)
					{ //                      ^^^^
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						*(uint64_t *)p = 0xe8909000000025e8; // E8 25 00 00 00 90 90 E8 (in HexEdit)
						//                   ^^^^
						//
						// Disable this section.
						//
						p = (unsigned char *)endAddress;
						targetPatches =~ 128;
						targetSections =~ nl->n_sect;
					}
				}
			}
		}
#endif // #if PRELINKED_KERNEL_SUPPORT

		symbolNumber++;
		pointer += listSize; // Point to next symbol.
	}

	return 0;
}
#endif
