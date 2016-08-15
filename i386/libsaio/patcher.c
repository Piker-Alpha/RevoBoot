/*
 * Copyright (c) 2016 Pike R. Alpha. All rights reserved.
 *
 * Updates:
 *			- Moved function patchKernel from load.c to patcher.c (Pike R. Alpha, August 2016)
 *			- Cleanups/removed some of the old style patches (more to follow).
 *
 */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "platform.h"

#if (PATCH_KERNEL && ((MAKE_TARGET_OS & EL_CAPITAN) == EL_CAPITAN))

#define PATCH_KEXT_LOADING	1


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

	struct symtab_command * symtab = (struct symtab_command *)cmdBase;
	struct segment_command_64 * textSegment = (struct segment_command_64 *)textSegmentAddress;
#if PRELINKED_KERNEL_SUPPORT
	struct segment_command_64 * vldSegment = (struct segment_command_64 *)vldSegmentAddress;
#endif

	void * stringTable = (void *)(loadAddress + symtab->stroff);

	const uint16_t targetMSRs[] = { 0xE2, 0x01A0, /* 0x01FC, */ 0x01AA, 0x0620, /* 0x064C, */ 0x063A, 0x0642 };

	uint32_t pointer = (loadAddress + symtab->symoff + skippedSymbolCount);

	int64_t offset			= 0;

	uint64_t startAddress	= 0;
	uint64_t endAddress		= 0;
	//
	// Main while loop.
	//
	while (symbolNumber < symtab->nsyms)
	{
		struct nlist_64 * nl = (struct nlist_64 *)pointer;

#if PATCH_KEXT_LOADING || PATCH_CPUID_SET_INFO
        offset			= 0;
        startAddress	= 0;
        endAddress		= 0;

		if ((nl->n_sect == 1 /* __TEXT,__text */) && nl->n_value)
		{
			symbolName = (char *)stringTable + nl->n_un.n_strx;
#if PATCH_KEXT_LOADING
			if (strcmp(symbolName, "__ZN6OSKext14loadExecutableEv") == 0)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x300);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (; p <= (unsigned char *)endAddress; p++)
				{
					//
					// Search pattern: 0x48xx74db854c3789
					//
					if ((*(uint32_t *)p == 0x8548c389) && (*(uint16_t *)(p+4) == 0x74db) && (*(uint8_t *)(p+7) == 0x48))
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)
						
						*(uint64_t *)p = 0x4812ebdb8548c389;
						p = (unsigned char *)endAddress;
					}
				}
			}
#endif // #if PATCH_KEXT_LOADING

#if PATCH_CPUID_SET_INFO
	#if PATCH_KEXT_LOADING
			else
	#endif
			if (strcmp(symbolName, "_cpuid_set_info") == 0)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x2100);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (; p <= (unsigned char *)endAddress; p++)
				{
					// Broadwell E (0x4F)	-> Broadwell (0x47)		=> 0x4F-0x47 = 0x08	-> change 0xE9 into 0xE1
					// Haswell E (0x3F)		-> Haswell (0x3C)		=> 0x3F-0x3C = 0x03	-> change 0xE9 into 0xE6
					// Ivy Bridge E (0x3E)	-> Ivy Bridge (0x3A)	=> 0x3E-0x3A = 0x04	-> change 0xE9 into 0xE5

					//
					// TODO: Port the patch routine from Vector.
					//
					if (*(uint64_t *)p == 0xf883e9c083c4b60f) // Reversed 0f b6 c4 83 c0 e9 83 f8 (47) (8 bytes).
					{ //                        ^^                                       ^^
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						// 0xff - 0xe9 = 0x16 + 0x01 = 0x17 + (0x4f - 0x47 = 0x08) = 0x1f (0x4f - 0x1f = 0x38)
						*(uint64_t *)p = 0xf8839000000030b8; // Reversed b8 30 00 00 00 90 83 f8 (47) (8 bytes).
						p = (unsigned char *)endAddress;
					}
					else if (*(uint64_t *)p == 0xf883f1c083c4b60f) // Reversed 0f b6 c4 83 c0 f1 83 f8 (47) (8 bytes).
					{ //                               ^^                                  ^^
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)
						
						// 0xff - 0xf1 = 0x0e + 0x01 = 0x0f + (0x4f - 0x47 = 0x08) = 0x17 (0x4f - 0x17 = 0x38)
						*(uint64_t *)p = 0xf8839000000038b8; // Reversed b8 38 00 00 00 90 83 f8 (47) (8 bytes).
						p = (unsigned char *)endAddress;
					}
				}
			}
#endif
			else if (strcmp(symbolName, "_xcpm_bootstrap") == 0)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x100);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (; p <= (unsigned char *)endAddress; p++)
				{
					//
					// TODO: Port the patch routine from Vector.
					//
					if (*(uint64_t *)p == 0x1c7722fb83c4c383) // Reversed of HexEdit: 83 C3 C4 83 FB 22 77 1C
					{ //                              ˆˆ                                    ˆˆ
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						*(uint64_t *)p = 0x1c7722fb83bcc383; // Reversed of HexEdit: 83 C3 BC 83 FB 22 77 1C
						//                           ˆˆ                                    ˆˆ
					}
				}
			}

			else if (strcmp(symbolName, "_xcpm_idle") == 0) // 2 MSRs (0xE2, 0xE2)
			{
				offset = (nl->n_value - textSegment->vmaddr);
				startAddress = (uint64_t)(textSegment->vmaddr + offset);
				endAddress = (startAddress + 0x200);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)

				for (; p <= (unsigned char *)endAddress; p++)
				{
					if (*(uint64_t *)p == 0x300f000000e2b920)// (48 C1 EA) 20 B9 E2 00 00 00 0F 30 reversed
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						*(uint32_t *)(p + 4) = 0x90900000; // Reversed 00 00 90 90 (4 bytes).
					}
				}
			}
		}
#endif // #if PATCH_KEXT_LOADING || PATCH_CPUID_SET_INFO

#if PATCH_XCPM_SCOPE_MSRS
	#if PATCH_KEXT_LOADING || PATCH_CPUID_SET_INFO
		else
	#endif
		if (((nl->n_sect == 8 /* __DATA,__data */) && nl->n_value) && gPlatform.CPU.CstConfigMsrLocked)
		{
			UInt8 repeat = 0;

			symbolName = (char *)stringTable + nl->n_un.n_strx;

			if (strcmp(symbolName, "_xcpm_SMT_scope_msrs") == 0) // 11 MSRs (0xE2, 0x01A0, 0x01B0, 0x01B0, 0x01B0, 0x0609, 0x038D, 0x038F, 0x0187, 0x0188, 0x0189)
			{
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, startAddress)
				//
				// TODO: Port the patch routine from Vector.
				//
				//
				// Zero out MSR 0xE2 and MSR 0x01A0
				//
				for (repeat = 0; repeat < 8; repeat++)
				{
					DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

					*(uint64_t *)p = 0x0000000000000000ULL;
					p += 0x08;
				}
			}
			else if (strcmp(symbolName, "_xcpm_core_scope_msrs") == 0) // 2 MSRs (0xE2, 0xE2)
			{
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, startAddress)
				//
				// TODO: Port the patch routine from Vector.
				//
				DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)
				//
				// Zero out CPU bits of MSR 0xE2
				//
				*(uint32_t *)(p + 4) = 0x00000000UL;
				//
				// Skip to second MSR 0xE2
				//
				p += 0x30;
				//
				// Zero out CPU bits of MSR 0xE2
				//
				*(uint32_t *)(p + 4) = 0x00000000UL;
			}
			else if (strcmp(symbolName, "_xcpm_pkg_scope_msrs") == 0) // 7 MSRs (0x01A0, 0x01FC, 0x01AA, 0x0620, 0x064C, 0x063A, 0x0642)
			{
				//
				// 0x064C MSR_TURBO_ACTIVATION_RATIO (Ivy Bridge Haswell E)
				// 0x063A MSR_PP0_POLICY
				// 0x0642 MSR_PP1_POLICY (not supported for server platform)
				//
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, startAddress)
				//
				// TODO: Port the patch routine from Vector.
				//
				for (short target_msr = 0; target_msr < 7; target_msr++)
				{
					//
					// Secondary for-loop to find MSRs that we need to disable.
					//
					for (short msr_to_disable = 0; msr_to_disable < 6; msr_to_disable++)
					{
						//
						// Is this a MSR that we need to disable?
						//
						if (*(uint16_t *)p == targetMSRs[msr_to_disable])
						{
							//
							// Yes.
							//
							DEBUG_DISABLED_MSR(targetMSRs[msr_to_disable], 1)
							//
							// Zero out the 32-bit CPU-bits field.
							//
							*(uint32_t *)(p + 4) = 0x00000000UL;
							//
							// The MSR is now disabled. Break out of secondary for loop.
							//
							break;
						}
					}
					
					p += 0x30;
				}
			}
		}
#endif // #if PATCH_XCPM_SCOPE_MSRS

#if (PATCH_LOAD_EXTRA_KEXTS && PRELINKED_KERNEL_SUPPORT)
	#if (PATCH_KEXT_LOADING || PATCH_XCPM_SCOPE_MSRS)
		else
	#endif
		if ((nl->n_sect == 25 /* __KLD,__text */) && nl->n_value)
		{
			symbolName = (char *)stringTable + nl->n_un.n_strx;
			
			if (strcmp(symbolName, "__ZN12KLDBootstrap21readStartupExtensionsEv") == 0)
			{
				int64_t offset = (nl->n_value - textSegment->vmaddr);
				uint64_t startAddress = (uint64_t)(textSegment->vmaddr + offset);
				uint64_t endAddress = (startAddress + 0x3f);

				p = (unsigned char *)startAddress;

				DEBUG_SYMBOL_FOUND(symbolName, offset, textSegment->vmaddr, textSegment->fileoff, startAddress, endAddress)
				
				for (; p <= (unsigned char *)endAddress; p++)
				{
					if (*(uint64_t *)p == 0xe805eb00000025e8)
					{
						DEBUG_PATCH_STATUS(symbolName, ((uint64_t)p - startAddress), 1)

						*(uint64_t *)p = 0xe8909000000025e8;
						p = (unsigned char *)endAddress;
					}
				}
			}
		}
#endif // #if (PATCH_LOAD_EXTRA_KEXTS && PRELINKED_KERNEL_SUPPORT)

		symbolNumber++;
		pointer += listSize; // Point to next symbol.
	}

	return 0;
}
#endif
