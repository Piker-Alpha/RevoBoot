/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
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
 * load.c - Functions for decoding a Mach-o Kernel.
 *
 * Copyright (c) 1998-2003 Apple Computer, Inc.
 *
 * Updates:
 *			- White space changes (Pike R. Alpha, November 2012)
 *			- Mountain Lion kernel patch for iMessage implemented (Pike R. Alpha, January 2013)
 *			- Patch for __ZN6OSKext14loadExecutableEv added (Pike R. Alpha, 2015)
 *			- Patch for __ZN12KLDBootstrap21readStartupExtensionsEv added.
 *			- Use Lower Camel Case for function names (Pike R. Alpha, July 2016)
 *			- Add _cpuid_set_info/_xcpm_bootstrap/_xcpm_idle to patches.
 *			- Dump global gBinaryAddress and use loadAddress argument.
 *			- New and improved patching routines (getting ready for smarter patching).
 *			- Renamed patchLoadExecutable to patchKernel (Pike R. Alpha, August 2016)
 *			- New and improved debug output (see also boot2/debug.h)
 *			- Made some preparations to move patchKernel() to patcher.c
 *			- Moved function patchKernel to patcher.c
 *
 */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach/machine/thread_status.h>

#include <sl.h>
#include "platform.h"

/***
 * Backward compatibility fix for the SDK 10.7 version of loader.h
 */

#ifndef LC_MAIN
	#define LC_MAIN (0x28|LC_REQ_DYLD) /* replacement for LC_UNIXTHREAD */
#endif

// Load MKext(s) or separate kexts (default behaviour / behavior).
bool gLoadKernelDrivers = true;

static long initKernelVersionInfo(unsigned long loadAddress, unsigned long cmdbase, long listSize, unsigned int textSegmentAddress);
static long decodeSegment(unsigned long loadAddress, long cmdBase, unsigned int*load_addr, unsigned int *load_size);
static long decodeUnixThread(long cmdBase, unsigned int *entry);

#define ADD_SYMTAB	1

#if ADD_SYMTAB
	static long decodeSymbolTable(unsigned long loadAddress, long cmdBase);
#endif


//==============================================================================
// Public function.

long thinFatFile(void **binary, unsigned long *length)
{
	unsigned long nfat, swapped, size = 0;
	struct fat_header *fhp = (struct fat_header *)*binary;
	struct fat_arch   *fap = (struct fat_arch *)((unsigned long)*binary + sizeof(struct fat_header));
	cpu_type_t fapcputype;
	uint32_t fapoffset;
	uint32_t fapsize;	

	if (fhp->magic == FAT_MAGIC)
	{
		nfat = fhp->nfat_arch;
		swapped = 0;
	}
	else if (fhp->magic == FAT_CIGAM)
	{
		nfat = OSSwapInt32(fhp->nfat_arch);
		swapped = 1;
	}
	else
	{
		return -1;
	}

	for (; nfat > 0; nfat--, fap++)
	{
		if (swapped)
		{
			fapcputype = OSSwapInt32(fap->cputype);
			fapoffset = OSSwapInt32(fap->offset);
			fapsize = OSSwapInt32(fap->size);
		}
		else
		{
			fapcputype = fap->cputype;
			fapoffset = fap->offset;
			fapsize = fap->size;
		}

		if (fapcputype == gPlatform.ArchCPUType)
		{
			*binary = (void *) ((unsigned long)*binary + fapoffset);
			size = fapsize;
			break;
		}
	}

	if (length != 0)
	{
		*length = size;
	}

	return 0;
}


//==============================================================================
// Called from decodeKernel() in drivers.c

long decodeMachO(void *fileLoadBuffer, entry_t *rentry, char **raddr, int *rsize)
{
	long ret						= -1;
	long sectionNumber				= 0;

	unsigned int vmaddr				= ~0;
	unsigned int vmend				= 0;
	unsigned int entry				= 0;
	unsigned int load_addr			= 0;
	unsigned int load_size			= 0;
	unsigned int textSegmentAddress	= 0;
	unsigned int vldSegmentAddress	= 0;

	unsigned long ncmds				= 0;
	unsigned long cmdBase			= 0;
	unsigned long cmd				= 0;
	unsigned long cmdsize			= 0;
	unsigned long cmdstart			= 0;
	unsigned long cnt				= 0;
	unsigned long listSize			= 0;

	unsigned long loadAddress = (unsigned long)fileLoadBuffer;

	if (gPlatform.ArchCPUType == CPU_TYPE_X86_64)
	{
		struct mach_header_64 * machHeader = (struct mach_header_64 *)(loadAddress);

		if (machHeader->magic != MH_MAGIC_64)
		{
			error("Mach-O file(X86_64) has a bad magic number!\n");
			return -1;
		}

		listSize = sizeof(struct nlist_64);
		cmdstart = loadAddress + sizeof(struct mach_header_64);
#if DEBUG
		printf("In decodeMachO()\n");
		printf("magic:      %x\n", (unsigned)machHeader->magic);
		printf("cputype:    %x\n", (unsigned)machHeader->cputype);
		printf("cpusubtype: %x\n", (unsigned)machHeader->cpusubtype);
		printf("filetype:   %x\n", (unsigned)machHeader->filetype);
		printf("ncmds:      %x\n", (unsigned)machHeader->ncmds);
		printf("sizeofcmds: %x\n", (unsigned)machHeader->sizeofcmds);
		printf("flags:      %x\n", (unsigned)machHeader->flags);
		sleep(5);
#endif
		ncmds = machHeader->ncmds;
	}
#if ((MAKE_TARGET_OS & SNOW_LEOPARD) == SNOW_LEOPARD)
	else // if (gPlatform.ArchCPUType == CPU_TYPE_I386)
	{
		struct mach_header * machHeader = (struct mach_header *)(loadAddress);

		if (machHeader->magic != MH_MAGIC)
		{
			error("Mach-O file(i386) has a bad magic number!\n");
			return -1;
		}

		listSize = sizeof(struct nlist);
		cmdstart = loadAddress + sizeof(struct mach_header);
#if DEBUG
		printf("In decodeMachO()\n");
		printf("magic:      %x\n", (unsigned)machHeader->magic);
		printf("cputype:    %x\n", (unsigned)machHeader->cputype);
		printf("cpusubtype: %x\n", (unsigned)machHeader->cpusubtype);
		printf("filetype:   %x\n", (unsigned)machHeader->filetype);
		printf("ncmds:      %x\n", (unsigned)machHeader->ncmds);
		printf("sizeofcmds: %x\n", (unsigned)machHeader->sizeofcmds);
		printf("flags:      %x\n", (unsigned)machHeader->flags);
		sleep(5);
#endif
		ncmds = machHeader->ncmds;
	}
#endif

	cmdBase = cmdstart;

	for (cnt = 0; cnt < ncmds; cnt++)
	{
		cmd = ((long *)cmdBase)[0];
		cmdsize = ((long *)cmdBase)[1];

		switch (cmd)
		{
			case LC_SEGMENT:
			case LC_SEGMENT_64:
				sectionNumber = decodeSegment(loadAddress, cmdBase, &load_addr, &load_size);

				if (sectionNumber == 1) // __TEXT,__text
				{
					textSegmentAddress = cmdBase;
					ret = 0;
				}
				else if (sectionNumber == 25) // __KLD,__text
				{
					vldSegmentAddress = cmdBase;
					ret = 0;
				}

				if (load_size != 0 && load_addr >= KERNEL_ADDR)
				{
					vmaddr = min(vmaddr, load_addr);
					vmend = max(vmend, load_addr + load_size);
				}

				break;

			case LC_SYMTAB:
				initKernelVersionInfo(loadAddress, cmdBase, listSize, textSegmentAddress);
#if (PATCH_KERNEL && ((MAKE_TARGET_OS & EL_CAPITAN) == EL_CAPITAN))
				patchKernel(loadAddress, cmdBase, listSize, textSegmentAddress, vldSegmentAddress);
#endif
				break;

			case LC_MAIN:	/* Mountain Lion's replacement for LC_UNIXTHREAD */
			case LC_UNIXTHREAD:
				ret = decodeUnixThread(cmdBase, &entry);
				break;

			default:
#if NOTDEF
				printf("Ignoring cmd type %d.\n", (unsigned)cmd);
#endif
				break;
		}

		if (ret != 0)
		{
			return -1;
		}

		cmdBase += cmdsize;
	}

	*rentry = (entry_t)( (unsigned long) entry & 0x3fffffff );
	*rsize = vmend - vmaddr;
	*raddr = (char *)vmaddr;

#if ADD_SYMTAB
	cmdBase = cmdstart;

	for (cnt = 0; cnt < ncmds; cnt++)
	{
		cmd = ((long *)cmdBase)[0];
		cmdsize = ((long *)cmdBase)[1];
		
		if (cmd == LC_SYMTAB)
		{
			if (decodeSymbolTable(loadAddress, cmdBase) != 0)
			{
				return -1;
			}
		}

		cmdBase += cmdsize;
	}
#endif
	return ret;
}


//==============================================================================
// Private function. Called from decodeMachO()

static long initKernelVersionInfo(unsigned long loadAddress, unsigned long cmdBase, long listSize, unsigned int textSegmentVMAddress)
{
	struct symtab_command * symtab = (struct symtab_command *)cmdBase;

	/*
	 * Reverse search is quicker for symbols at the end of the symbol table (example with 20496 symbols):
	 *
	 * _version_revision	is symbol 18865 – first target symbol, iterated symbols: 1631
	 * _version_minor		is symbol 18863 – second target symbol, iterated symbols: 1633
	 * _version_major		is symbol 18862 – last target symbol, iterated symbols: 1634
	 *
	 * versus:
	 *
	 * _version_major		is symbol 18862 – first target symbol, iterated symbols: 18862
	 * _version_minor		is symbol 18863 – ssecond target symbol, iterated symbols: 18863
	 * _version_revision	is symbol 18865 – last target symbol, iterated symbols: 18865
	 */

	const char * targetSymbols[] = { "_version_revision", "_version_minor", "_version_major" };

	char * symbolName = NULL;
	char * loadBuffer = (char *)loadAddress;

	void * stringTable = (void *)(loadAddress + symtab->stroff);

	short index								= 0;

	long symbolOffset						= 0;
	long symbolLength						= 0;
	long symbolNumber						= symtab->nsyms;

	uint32_t pointer = loadAddress + symtab->symoff + ((symtab->nsyms - 1) * listSize);

#if ((MAKE_TARGET_OS & SNOW_LEOPARD) == SNOW_LEOPARD)
	if (gPlatform.ArchCPUType == CPU_TYPE_X86_64)
	{
#endif
		struct nlist_64 * nl = (struct nlist_64 *)pointer;
	
		while (symbolNumber > 0)
		{
			nl = (struct nlist_64 *)pointer;
			
			if ((nl->n_sect == 2 /* __TEXT,__const */) && nl->n_value)
			{
				symbolName = (char *)stringTable + nl->n_un.n_strx;
				symbolLength = strlen(symbolName);
				symbolOffset = (nl->n_value - textSegmentVMAddress);
				
				if (symbolLength && (strcmp(symbolName, targetSymbols[index]) == 0))
				{
					switch(index)
					{
						case 0:
							gPlatform.KERNEL.versionRevision = (uint8_t)loadBuffer[symbolOffset];
							index++;
							break;
							
						case 1:
							gPlatform.KERNEL.versionMinor = (uint8_t)loadBuffer[symbolOffset];
							index++;
							break;
							
						case 2:
							gPlatform.KERNEL.versionMajor = (uint8_t)loadBuffer[symbolOffset];
							symbolNumber = 0;
							break;
					}
				}
			}
			
			symbolNumber--;
			pointer -= listSize;
		}
#if ((MAKE_TARGET_OS & SNOW_LEOPARD) == SNOW_LEOPARD)
	}
	else // 32-bit compatibility code.
	{
		struct nlist * nl = (struct nlist *)pointer;
		
		while (symbolNumber > 0)
		{
			nl = (struct nlist *)pointer;
			
			if ((nl->n_sect == 2 /* __TEXT,__const */) && nl->n_value)
			{
				symbolName = (char *)stringTable + nl->n_un.n_strx;
				symbolLength = strlen(symbolName);
				symbolOffset = (nl->n_value - textSegmentVMAddress);
				
				if (symbolLength && (strcmp(symbolName, targetSymbols[index]) == 0))
				{
					switch(index)
					{
						case 0:
							gPlatform.KERNEL.versionRevision = (uint8_t)loadBuffer[symbolOffset];
							index++;
							break;
							
						case 1:
							gPlatform.KERNEL.versionMinor = (uint8_t)loadBuffer[symbolOffset];
							index++;
							break;
							
						case 2:
							gPlatform.KERNEL.versionMajor = (uint8_t)loadBuffer[symbolOffset];
							symbolNumber = 0;
							break;
					}
				}
			}
			
			symbolNumber--;
			pointer -= listSize;
		}
	}
#endif

#if DEBUG
	printf("gPlatform.KERNEL.versionMmR: %d.%d.%d\n", gPlatform.KERNEL.versionMajor, gPlatform.KERNEL.versionMinor, gPlatform.KERNEL.versionRevision);
	sleep(5);
#endif

	return 0;
}

//==============================================================================
// Private function. Called from decodeMachO()
// Refactoring and segment name fix for OS X 10.6+ by DHP in 2010.

static long decodeSegment(unsigned long loadAddress, long cmdBase, unsigned int *load_addr, unsigned int *load_size)
{
	char *segmentName	= NULL;

	long retValue		= 0;
	long vmsize			= 0;
	long filesize		= 0;

	unsigned long vmaddr		= 0;
	unsigned long fileAddress	= 0;

	if (((long *)cmdBase)[0] == LC_SEGMENT_64)
	{
		struct segment_command_64 *segCmd = (struct segment_command_64 *)cmdBase;
		vmaddr			= (segCmd->vmaddr & 0x3fffffff);
		vmsize			= segCmd->vmsize;
		fileAddress		= (loadAddress + segCmd->fileoff);
		filesize		= segCmd->filesize;
		segmentName		= segCmd->segname;
	}
	else
	{
		struct segment_command *segCmd = (struct segment_command *)cmdBase;
		vmaddr			= (segCmd->vmaddr & 0x3fffffff);
		vmsize			= segCmd->vmsize;
		fileAddress		= (loadAddress + segCmd->fileoff);
		filesize		= segCmd->filesize;
		segmentName		= segCmd->segname;
	}
	
	// Pre-flight checks.
	if (vmsize && filesize)
	{
		if (! ((vmaddr >= KERNEL_ADDR && (vmaddr + vmsize) <= (KERNEL_ADDR + KERNEL_LEN)) ||
			   (vmaddr >= HIB_ADDR && (vmaddr + vmsize) <= (HIB_ADDR + HIB_LEN))))
		{
			stop("Kernel overflows available space");
		}

		/*
		 * Check for pre-linked kernel segment names, to block our (M)Kext(s) from
		 * getting loaded. Note that 10.6+ uses new / different segment names i.e. 
		 * __PRELINK_TEXT, __PRELINK_STATE, __PRELINK_INFO versus __PRELINK in 10.5
		 */

		if (gLoadKernelDrivers && strncmp(segmentName, "__PRELINK", 9) == 0)
		{
#if DEBUG
			printf("Setting: gLoadKernelDrivers to false.\n");
			printf("Sleeping for 5 seconds...\n");
			sleep(5);
#endif
			gLoadKernelDrivers = false;
		}
		else if (strncmp(segmentName, "__TEXT", 6) == 0)
		{
			retValue = 1;
		}
		else if (strncmp(segmentName, "__KLD", 5) == 0)
		{
			retValue = 25;
		}

		// Copy from file load area.
		if (filesize > 0)
		{
			bcopy((char *)fileAddress, (char *)vmaddr, vmsize > filesize ? filesize : vmsize);
		}

		// Zero space at the end of the segment.
		if (vmsize > filesize)
		{
			bzero((char *)(vmaddr + filesize), vmsize - filesize);
		}

		*load_addr = vmaddr;
		*load_size = vmsize;
	}
	else // Error condition. Zero out.
	{
		*load_addr = ~0;
		*load_size = 0;			
	}

	return retValue;
}


//==============================================================================
// Private function. Called from decodeMachO()

static long decodeUnixThread(long cmdBase, unsigned int *entry)
{
	switch (gPlatform.ArchCPUType)
	{
		case CPU_TYPE_I386:
		{
			i386_thread_state_t *i386ThreadState;
			i386ThreadState = (i386_thread_state_t *) (cmdBase + sizeof(struct thread_command) + 8);

		#if defined(__DARWIN_UNIX03) && __DARWIN_UNIX03
			*entry = i386ThreadState->__eip;
		#else
			*entry = i386ThreadState->eip;
		#endif
			return 0;
		}
			
		case CPU_TYPE_X86_64:
		{
			x86_thread_state64_t *x86_64ThreadState;
			x86_64ThreadState = (x86_thread_state64_t *) (cmdBase + sizeof(struct thread_command) + 8);
			
		#if defined(__DARWIN_UNIX03) && __DARWIN_UNIX03
			*entry = x86_64ThreadState->__rip;
		#else
			*entry = x86_64ThreadState->rip;
		#endif
			return 0;
		}
			
		default:
			error("Unknown CPU type\n");
			return -1;
	}
}

#if ADD_SYMTAB
//==============================================================================
// Private function. Called from decodeMachO()

static long decodeSymbolTable(unsigned long loadAddress, long cmdBase)
{
	long tmpAddr, symsSize, totalSize;
	long gSymbolTableAddr;
	long gSymbolTableSize;
	
	struct symtab_command *symTab, *symTableSave;

	symTab = (struct symtab_command *)cmdBase;

#if DEBUG
	printf("symoff: %x, nsyms: %x, stroff: %x, strsize: %x\n", symTab->symoff, symTab->nsyms, symTab->stroff, symTab->strsize);
	getchar();
#endif

	symsSize = symTab->stroff - symTab->symoff;
	totalSize = symsSize + symTab->strsize;

	gSymbolTableSize = totalSize + sizeof(struct symtab_command);
	gSymbolTableAddr = AllocateKernelMemory(gSymbolTableSize);
	// Add the SymTab to the memory-map.
	AllocateMemoryRange("Kernel-__SYMTAB", gSymbolTableAddr, gSymbolTableSize);

	symTableSave = (struct symtab_command *)gSymbolTableAddr;
	tmpAddr = gSymbolTableAddr + sizeof(struct symtab_command);

	symTableSave->symoff = tmpAddr;
	symTableSave->nsyms = symTab->nsyms;
	symTableSave->stroff = tmpAddr + symsSize;
	symTableSave->strsize = symTab->strsize;
	
	bcopy((char *)(loadAddress + symTab->symoff), (char *)tmpAddr, totalSize);

	return 0;
}
#endif

//==============================================================================
// Public function (RevoBoot v1.5.30 and greater). Called from our ACPI patcher
// which looks in /Extra/ACPI/ for [TableName].aml but it is also used in two
// other places, being libsaio/efi.c and libsaio/SMBIOS/static_data.h This to
// get static (binary) data from /Extra/[EFI/SMBIOS]/[FileName].bin

long loadBinaryData(char *aFilePath, void **aMemoryAddress)
{
	long fileSize = LoadFile(aFilePath);

	if (fileSize > 0)
	{
		*aMemoryAddress = (void *)malloc(fileSize);
		
		if (aMemoryAddress)
		{
			memcpy(*aMemoryAddress, (void *)kLoadAddr, fileSize);

			return fileSize;
		}
	}

	return 0;
}
