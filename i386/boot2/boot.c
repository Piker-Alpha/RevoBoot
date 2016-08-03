/*
 * Copyright (c) 1999-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 2.0 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 * INTEL CORPORATION PROPRIETARY INFORMATION
 *
 * This software is supplied under the terms of a license  agreement or
 * nondisclosure agreement with Intel Corporation and may not be copied
 * nor disclosed except in accordance with the terms of that agreement.
 *
 * Copyright 1988, 1989 by Intel Corporation
 *
 * Copyright 1993 NeXT Computer, Inc. All rights reserved.
 *
 * Completely reworked by Sam Streeper (sam_s@NeXT.com)
 * Reworked again by Curtis Galloway (galloway@NeXT.com)
 *
 * Updates:
 *			- Refactorized by DHP in 2010 and 2011.
 *			- Optionally include Recovery HD support code (PikerAlpha, November 2012).
 *			- Fixed clang compilation (PikerAlpha, November 2012).
 *			- Unused sysConfigValid removed and white space fix (PikerAlpha, November 2012).
 *			- Fixed boot failure for InstallESD/BaseSystem.dmg/patched kernelcache (PikerAlpha, April 2013).
 *			- Renamed LION_INSTALL_SUPPORT to INSTALL_ESD_SUPPORT (PikerAlpha, April 2013).
 *
 */

#include "boot.h"
#include "bootstruct.h"
#include "sl.h"
#include "libsa.h"

#if DISABLE_LEGACY_XHCI
	#include "pci.h"
	#include "xhci.h"
#endif

#if PATCH_APIC_RET
	#include "backup/apic.h"
#endif

//==============================================================================
// Local adler32 function.

unsigned long Adler32(unsigned char *buf, long len)
{
	#define BASE 65521L // largest prime smaller than 65536
	#define NMAX 5000
	// NMAX (was 5521) the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1
	
	#define DO1(buf, i)  {s1 += buf[i]; s2 += s1;}
	#define DO2(buf, i)  DO1(buf, i); DO1(buf, i + 1);
	#define DO4(buf, i)  DO2(buf, i); DO2(buf, i + 2);
	#define DO8(buf, i)  DO4(buf, i); DO4(buf, i + 4);
	#define DO16(buf)   DO8(buf, 0); DO8(buf, 8);

	int k;

	unsigned long s1 = 1;	// adler & 0xffff;
	unsigned long s2 = 0;	// (adler >> 16) & 0xffff;
	unsigned long result;

	
	while (len > 0)
	{
		k = len < NMAX ? len : NMAX;
		len -= k;

		while (k >= 16)
		{
			DO16(buf);
			buf += 16;
			k -= 16;
		}

		if (k != 0)
		{
			do
			{
				s1 += *buf++;
				s2 += s1;
			} while (--k);
		}

		s1 %= BASE;
		s2 %= BASE;
	}

	result = (s2 << 16) | s1;

	return OSSwapHostToBigInt32(result);
}


//==============================================================================

static void zeroBSS()
{
	extern int  _DATA_bss__start	__asm("section$start$__DATA$__bss");
	extern int  _DATA_bss__end		__asm("section$end$__DATA$__bss");
	extern int  _DATA_common__start	__asm("section$start$__DATA$__common");
	extern int  _DATA_common__end	__asm("section$end$__DATA$__common");

	bzero(&_DATA_bss__start, (&_DATA_bss__end - &_DATA_bss__start));
	bzero(&_DATA_common__start, (&_DATA_common__end - &_DATA_common__start));
}

/*
 * The SAFE_MALLOC related code (adding 768 bytes) should only be used for 
 * debugging purposes – I have never seen this memory allocation error!
 */

#if SAFE_MALLOC
static void mallocError(char *addr, size_t size, const char *file, int line)
{
	stop("\nMemory allocation error! Addr=0x%x, Size=0x%x, File=%s, Line=%d\n", (unsigned)addr, (unsigned)size, file, line);
}
#else
static void mallocError(char *addr, size_t size)
{
	printf("\nMemory allocation error (0x%x, 0x%x)\n", (unsigned)addr, (unsigned)size);
	asm volatile ("hlt");
}
#endif


//==============================================================================
// Entrypoint from real-mode.

void boot(int biosdev)
{
	zeroBSS();
	mallocInit(0, 0, 0, mallocError);

#if MUST_ENABLE_A20
	// Enable A20 gate before accessing memory above 1 MB.
	if (fastEnableA20() != 0)
	{
		enableA20(); // Fast enable failed. Try legacy method.
	}
#endif

	bool	haveCABootPlist	= false;
	bool	quietBootMode	= true;

	void *fileLoadBuffer = (void *)kLoadAddr;

	char bootFile[256];
	char rootUUID[37];

	char * kernelFlags = NULL;

	const char * val;

	int length	= 0;
	int kernelFlagsLength = 0;

	bootFile[0] = '\0';
	rootUUID[0] = '\0';

#if PRELINKED_KERNEL_SUPPORT
	bool	mayUseKernelCache	= false;
	bool	flushCaches			= false;
	bool	kernelSpecified	= false;
#endif

	long flags, cachetime;

	initPlatform(biosdev);

#if DEBUG_BOOT
	/*
	 * In DEBUG mode we don't switch to graphics mode and do not show the Apple boot logo.
	 */
	printf("\nModel: %s\n", gPlatform.ModelID);

	#if ((MAKE_TARGET_OS & LION) != LION)
		printf("\nArchCPUType (CPU): %s\n", (gPlatform.ArchCPUType == CPU_TYPE_X86_64) ? "x86_64" : "i386");
		sleep(3); // Silent sleep.
	#endif
#endif

#if (DEBUG_STATE_ENABLED == 0)
	showBootLogo();
#endif

#if (LOAD_MODEL_SPECIFIC_EFI_DATA == 0 && BLACKMODE == 0)
	/*
	 * We can only make this call here when static EFI is included from:
	 * RevoBoot/i386/config/EFI/[MacModelNN.h] Not when the data is read from:
	 * /Extra/EFI/ because then RevoBoot/i386/libsaio/platform.c makes the call.
	 *
 	 * We can also <em>not</em> call it here if BLACKMODE is enabled, because
	 * then it fails to load: /usr/standalone/i386/EfiLoginUI/appleLogo.efires
 	 */
	initPartitionChain();
#endif

#if STARTUP_DISK_SUPPORT
	// Booting from a Recovery HD ignores the Startup Disk setting (as it should).
	if (gPlatform.BootRecoveryHD == false)
	{
		/*
		 * sudo nano /etc/rc.shutdown.local
		 * #!/bin/sh
		 * /usr/sbin/nvram -x -p > /Extra/NVRAM/nvramStorage.plist
		 */
		config_file_t	nvramStorage;
		const char * path = "/Extra/NVRAM/nvramStorage.plist";
	
		if (loadConfigFile(path, &nvramStorage) == EFI_SUCCESS)
		{
			_BOOT_DEBUG_DUMP("nvramStorage.plist found\n");

			if (getValueForConfigTableKey(&nvramStorage, "efi-boot-device-data", &val, &length))
			{
				_BOOT_DEBUG_DUMP("Key 'efi-boot-device-data' found %d\n", length);

				char * uuid = getStartupDiskUUID((char *)val);

				if (uuid)
				{
					_BOOT_DEBUG_DUMP("GUID: %s\n", uuid);
					_BOOT_DEBUG_SLEEP(1);

					strlcpy(rootUUID, uuid, 37);
				}
			}
		}
	}
	else
	{
		_BOOT_DEBUG_DUMP("Warning: unable to locate nvramStorage.plist\n");
	}
#endif // #if STARTUP_DISK_SUPPORT

	if (loadCABootPlist() == EFI_SUCCESS)
	{
		_BOOT_DEBUG_DUMP("com.apple.Boot.plist located.\n");

		// Load successful. Change state accordantly.
		haveCABootPlist = true;	// Checked <i>before</i> calling key functions.

		// Check the value of <key>Kernel Flags</key> for stuff we are interested in.
		// Note: We need to know about: arch= and the boot flags: -s, -v, -f and -x

		if (getValueForKey(kKernelFlagsKey, &val, &kernelFlagsLength, &bootInfo->bootConfig))
		{
			// "Kernel Flags" key found. Check length to see if we have anything to work with.
			if (kernelFlagsLength)
			{
				kernelFlagsLength++;

				// Yes. Allocate memory for it and copy the kernel flags into it.
				kernelFlags = malloc(kernelFlagsLength);
				strlcpy(kernelFlags, val, kernelFlagsLength);

				// Is 'arch=<i386/x86_64>' specified as kernel flag?
				if (getValueForBootKey(kernelFlags, "arch", &val, &length)) //  && len >= 4)
				{
					gPlatform.ArchCPUType = (strncmp(val, "x86_64", 6) == 0) ? CPU_TYPE_X86_64 : CPU_TYPE_I386;

					_BOOT_DEBUG_DUMP("ArchCPUType (c.a.B.plist): %s\n",  (gPlatform.ArchCPUType == CPU_TYPE_X86_64) ? "x86_64" : "i386");
				}
				
				// Check for -v (verbose) and -s (single user mode) flags.
				gVerboseMode =	getValueForBootKey(kernelFlags, kVerboseModeFlag, &val, &length) || 
								getValueForBootKey(kernelFlags, kSingleUserModeFlag, &val, &length);
				
				if (gVerboseMode)
				{
					_BOOT_DEBUG_DUMP("Notice: -s (single user mode) and/or -v (verbose mode) specified!\n");
#if (DEBUG_BOOT == false)
					setVideoMode(VGA_TEXT_MODE);
#endif
				}

				// Check for -x (safe) flag.
				if (getValueForBootKey(kernelFlags, kSafeModeFlag, &val, &length))
				{
					gPlatform.BootMode = kBootModeSafe;
				}

				// Check for -f (flush cache) flag.
				if (getValueForBootKey(kernelFlags, kIgnoreCachesFlag, &val, &length))
				{
					_BOOT_DEBUG_DUMP("Notice: -f (flush cache) specified!\n");
#if PRELINKED_KERNEL_SUPPORT
					flushCaches = true;
#endif
				}

				// Is rootUUID still empty and 'boot-uuid=<value>' specified as kernel flag?
				if (rootUUID[0] == '\0' && (getValueForBootKey(kernelFlags, kBootUUIDKey, &val, &length) && length == 36))
				{
					_BOOT_DEBUG_DUMP("Target boot-uuid=<%s>\n", val);

					// Yes. Copy its value into rootUUID.
					strlcpy(rootUUID, val, 37);
				}
#if INSTALL_ESD_SUPPORT
				/*
				 * boot-arg scheme:
				 *
				 * container-dmg: optional DMG that contains the root-dmg.
				 * root-dmg: the DMG that will be the root filesystem.
				 */
				if (getValueForBootKey(kernelFlags, "container-dmg", &val, &length) &&
					getValueForBootKey(kernelFlags, "root-dmg", &val, &length))
				{
					_BOOT_DEBUG_DUMP("Target container-dmg/root-dmg=%s\n", val);

					gPlatform.BootVolume->flags |= kBVFlagInstallVolume;
				}
				else
				{
					gPlatform.BootVolume->flags = ~kBVFlagInstallVolume;
				}
#endif
			}
		}
		// Check for Root UUID (required for Fusion Drives).
		if (rootUUID[0] == '\0' && (getValueForKey(kHelperRootUUIDKey, &val, &length, &bootInfo->bootConfig) && length == 36))
		{
			_BOOT_DEBUG_DUMP("Target boot-uuid=<%s>\n", val);
			
			// Yes. Copy its value into rootUUID.
			strlcpy(rootUUID, val, 37);
		}

		/* Enable touching of a single BIOS device by setting 'Scan Single Drive' to yes.
		if (getBoolForKey(kScanSingleDriveKey, &gScanSingleDrive, &bootInfo->bootConfig) && gScanSingleDrive)
		{
			gScanSingleDrive = true;
		} */
	}
	else
	{
		_BOOT_DEBUG_DUMP("No com.apple.Boot.plist found.\n");
		_BOOT_DEBUG_SLEEP(5);
	}

	// Was a target drive (per UUID) specified in com.apple.Boot.plist?
	if (rootUUID[0] == '\0')
	{
		_BOOT_DEBUG_DUMP("No NVRAM-Startup Disk / rd=uuid bootuuid= in com.apple.Boot.plist\n");

		// No, so are we booting from a System Volume?
		if (gPlatform.BootVolume->flags & kBVFlagSystemVolume)
		{
			_BOOT_DEBUG_DUMP("Booting from a System Volume, getting UUID.\n");

			// Yes, then let's get the UUID.
			if (HFSGetUUID(gPlatform.BootVolume, rootUUID) == EFI_SUCCESS)
			{
				_BOOT_DEBUG_DUMP("Success [%s]\n", rootUUID);
			}
		}
		else if (gPlatform.BootVolume->flags & kBVFlagInstallVolume)
		{
			_BOOT_DEBUG_DUMP("Booting from a disk image in the installation directory\n");

			if (HFSGetUUID(gPlatform.BootVolume, rootUUID) == EFI_SUCCESS)
			{
				_BOOT_DEBUG_DUMP("Success [%s]\n", rootUUID);
			}
		}
		else // Booting from USB-stick or SDboot media
		{
			_BOOT_DEBUG_DUMP("Booting from a Non System Volume, getting UUID.\n");

			// Get target System Volume and UUID in one go.
			BVRef rootVolume = getTargetRootVolume(rootUUID);

			if (rootVolume)
			{
				_BOOT_DEBUG_DUMP("Success [%s]\n", rootUUID);

				gPlatform.RootVolume = rootVolume;
			}
		}

		// This should never happen, but just to be sure.
		if (rootUUID[0] == '\0')
		{
			_BOOT_DEBUG_DUMP("Failed to get UUID for System Volume.\n");

			if (!gVerboseMode)
			{
				// Force verbose mode when we didn't find a UUID, so 
				// that people see what is going on in times of trouble.
				gVerboseMode = true;
			}
		}
	}

	/*
	 * At this stage we know exactly what boot mode we're in, and which disk to boot from
	 * any of which may or may not have been set/changed (in com.apple.Boot.plist) into a 
	 * non-default system setting and thus is this the place to update our EFI tree.
	 */

	updateEFITree(rootUUID);

	if (haveCABootPlist) // Check boolean before doing more time consuming tasks.
	{
#if PRELINKED_KERNEL_SUPPORT
		/*
		 * We cannot use the kernelcache from the Yosemite installer, not yet,
		 * and thus we load: /System/Library/Caches/Startup/kernelcache instead
		 */
#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
		// Installation directory located?
		if (flushCaches == false) //  && (gPlatform.BootVolume->flags != kBVFlagInstallVolume))
		{
#endif // #if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE)
			_BOOT_DEBUG_DUMP("Checking Kernel Cache key in com.apple.Boot.plist\n");

			if (getValueForKey(kKernelCacheKey, &val, &length, &bootInfo->bootConfig))
			{
				_BOOT_DEBUG_DUMP("Kernel Cache key located in com.apple.Boot.plist\n");
				_BOOT_DEBUG_DUMP("length: %d, val: %s\n", length, val);
#if RECOVERY_HD_SUPPORT
				// XXX: Required for booting from the Recovery HD.
#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
				// FIXME: This static check sucks!
				if (strncmp(val, "\\com.apple.recovery.boot\\prelinkedkernel", length) == 0)
				{
					val = "/com.apple.recovery.boot/prelinkedkernel";
				}
#else
				if (strncmp(val, "\\com.apple.recovery.boot\\kernelcache", length) == 0)
				{
					val = "/com.apple.recovery.boot/kernelcache";
				}
#endif // #if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
#endif // #if RECOVERY_HD_SUPPORT
				if (length && GetFileInfo(NULL, val, &flags, &cachetime) == 0)
				{
					_BOOT_DEBUG_DUMP("Kernel Cache set to: %s\n", val);

					// File located. Init kernelCacheFile so that we can use it as boot file.
					gPlatform.KernelCachePath = strdup(val);
				
					// Set flag to inform the load process to skip parts of the code.
					gPlatform.KernelCacheSpecified = true;
				}
			}
#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
		}
		else
		{
			if (getValueForKey(kKernelNameKey, &val, &length, &bootInfo->bootConfig))
			{
				_BOOT_DEBUG_DUMP("Kernel key located in com.apple.Boot.plist\n");
				_BOOT_DEBUG_DUMP("length: %d, val: %s\n", length, val);
				strcpy(bootFile, val);
				kernelSpecified = true;
			}
		}
#endif // #if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE)

#else // #if PRELINKED_KERNEL_SUPPORT
	#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
		sprintf(bootFile, "/System/Library/Kernels/%s", bootInfo->bootFile);
	#else
		// Set to mach_kernel for Mavericks and earlier versions of OS X.
		sprintf(bootFile, "/%s", bootInfo->bootFile);
	#endif
#endif // #if PRELINKED_KERNEL_SUPPORT
		
		if (getBoolForKey(kQuietBootKey, &quietBootMode, &bootInfo->bootConfig) && !quietBootMode)
		{
			gPlatform.BootMode = kBootModeNormal; // Reversed from: gPlatform.BootMode |= kBootModeQuiet;
		}
	}

	// Parse args, load and start kernel.
	while (1)
	{
		// Initialize globals.
		gErrors			= 0;

		int retStatus	= -1;

		uint32_t adler32 = 0;

		getAndProcessBootArguments(kernelFlags);

		/* Initialize bootFile (defaults to: mach_kernel).
		strcpy(bootFile, bootInfo->bootFile);
		_BOOT_DEBUG_DUMP("bootFile: %s\n", bootFile);
		_BOOT_DEBUG_DUMP("bootInfo->bootFile: %s\n", bootInfo->bootFile);
		_BOOT_DEBUG_SLEEP(5); */

#if PRELINKED_KERNEL_SUPPORT
		_BOOT_DEBUG_DUMP("gPlatform.BootMode = %d\n", gPlatform.BootMode);

		// Preliminary checks to prevent us from doing useless things.
		mayUseKernelCache = ((flushCaches == false) && ((gPlatform.BootMode & kBootModeSafe) == 0));

		_BOOT_DEBUG_DUMP("mayUseKernelCache = %s\n", mayUseKernelCache ? "true" : "false");

		/* 
		 * A prelinkedkernel or kernelcache requires you to have all essential kexts for your
		 * configuration, including FakeSMC.kext in: /System/Library/Extensions/ 
		 * Not in /Extra/Extensions/ because this directory will be ignored, completely when a 
		 * prelinkedkernel or kernelcache is used!
		 *
		 * Note: Not following this word of advise will render your system incapable of booting!
		 */
		
		if (mayUseKernelCache == false)
		{
			_BOOT_DEBUG_DUMP("Warning: kernelcache will be ignored!\n");

			// True when 'Kernel Cache' is set in com.apple.Boot.plist
			if (gPlatform.KernelCacheSpecified == true)
			{
				sprintf(bootFile, "%s", bootInfo->bootFile);
			}
#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
			else
			{
				if (!kernelSpecified)
				{
					sprintf(bootFile, "/System/Library/Kernels/%s", bootInfo->bootFile);
				}
			}
#endif
		}
		else
		{
			// True when 'Kernel Cache' is set in com.apple.Boot.plist
			if (gPlatform.KernelCacheSpecified == true)
			{
				_BOOT_DEBUG_DUMP("kernelcache path: %s\n", gPlatform.KernelCachePath);

				/*
				 * Starting with Lion, we can take a shortcut by simply pointing 
				 * the 'bootFile' to the kernel cache and we are done.
				 */
				sprintf(bootFile, "%s", gPlatform.KernelCachePath);
			}
			else // Try to find a prelinkedkernel/kernelcache
			{
				char * preLinkedKernelPath = malloc(128);

				if (gPlatform.HelperPath) // com.apple.boot.[RPS]
				{
					sprintf(preLinkedKernelPath, "%s%s", gPlatform.HelperPath, gPlatform.KernelCachePath);
				}
				else
				{
					sprintf(preLinkedKernelPath, "%s", gPlatform.KernelCachePath);
				}

				// Check kernelcache directory
				if (GetFileInfo(NULL, preLinkedKernelPath, &flags, &cachetime) == 0)
				{
					static char adler32Key[PLATFORM_NAME_LEN + ROOT_PATH_LEN];
				
					_BOOT_DEBUG_DUMP("Checking for prelinkedkernel...\n");
				
					// Zero out platform info (name and kernel root path).
					bzero(adler32Key, sizeof(adler32Key));
				
					// Construct key for the pre-linked kernel checksum (generated by adler32).
					sprintf(adler32Key, gPlatform.ModelID);
					sprintf(adler32Key + PLATFORM_NAME_LEN, "%s", BOOT_DEVICE_PATH);
					sprintf(adler32Key + (PLATFORM_NAME_LEN + 38), "%s", bootInfo->bootFile);
				
					adler32 = Adler32((unsigned char *)adler32Key, sizeof(adler32Key));
				
					_BOOT_DEBUG_DUMP("adler32: %08X\n", adler32);

#if ((MAKE_TARGET_OS & LION) == LION) // Sierra, El Capitan, Yosemite, Mavericks and Mountain Lion also have bit 1 set (like Lion).

					_BOOT_DEBUG_DUMP("Checking for kernelcache...\n");

					// if (GetFileInfo(gPlatform.KernelCachePath, (char *)kKernelCache, &flags, &cachetime) == 0)
					if (GetFileInfo(preLinkedKernelPath, (char *)kKernelCache, &flags, &cachetime) == 0)
					{
						sprintf(bootFile, "%s/%s", preLinkedKernelPath, kKernelCache);

						_BOOT_DEBUG_DUMP("Kernelcache located.\n");
					}
					else
					{
						mayUseKernelCache = false;
						_BOOT_DEBUG_DUMP("Failed to locate the kernelcache!\n");
					}
				}
				else
				{
					mayUseKernelCache = false;
					_BOOT_DEBUG_DUMP("Failed to locate the kernelcache directory!\n");
				}
				
				if (mayUseKernelCache == false)
				{
					_BOOT_DEBUG_DUMP("No kernelcache found, will load: %s!\n", bootInfo->bootFile);

#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
					sprintf(bootFile, "/System/Library/Kernels/%s", bootInfo->bootFile);
#else
					// Set to mach_kernel for Mavericks and earlier versions of OS X.
					sprintf(bootFile, "/%s", bootInfo->bootFile);
#endif
				}

				free(preLinkedKernelPath);
			}
		}
#else // Not for Mavericks/Mountain Lion/Lion, go easy with the Snow Leopard.

				/* static char preLinkedKernelPath[128];
				static char adler32Key[PLATFORM_NAME_LEN + ROOT_PATH_LEN];

				unsigned long adler32 = 0;

				preLinkedKernelPath[0] = '\0';

				_BOOT_DEBUG_DUMP("Checking for pre-linked kernel...\n");

				// Zero out platform info (name and kernel root path).
				bzero(adler32Key, sizeof(adler32Key));
				
				// Construct key for the pre-linked kernel checksum (generated by adler32). 
				sprintf(adler32Key, gPlatform.ModelID);
				sprintf(adler32Key + PLATFORM_NAME_LEN, "%s", BOOT_DEVICE_PATH);
				sprintf(adler32Key + (PLATFORM_NAME_LEN + 38), "%s", bootInfo->bootFile);
				
				adler32 = Adler32((unsigned char *)adler32Key, sizeof(adler32Key));
				
				_BOOT_DEBUG_DUMP("adler32: %08X\n", adler32); */
				
				// Create path to pre-linked kernel.
				sprintf(preLinkedKernelPath, "%s/%s_%s.%08lX", gPlatform.KernelCachePath, kKernelCache, 
						((gPlatform.ArchCPUType == CPU_TYPE_X86_64) ? "x86_64" : "i386"), adler32);

				// Check if this file exists.
				if ((GetFileInfo(NULL, preLinkedKernelPath, &flags, &cachetime) == 0) && ((flags & kFileTypeMask) == kFileTypeFlat))
				{
					_BOOT_DEBUG_DUMP("Pre-linked kernel cache located!\nLoading pre-linked kernel: %s\n", preLinkedKernelPath);
					
					// Returns -1 on error, or the actual filesize.
					if (LoadFile((const char *)preLinkedKernelPath))
					{
						retStatus = 1;
						fileLoadBuffer = (void *)kLoadAddr;
						bootFile[0] = 0;
					}

					_BOOT_DEBUG_ELSE_DUMP("Failed to load the pre-linked kernel. Will load: %s!\n", bootInfo->bootFile);
				}

				_BOOT_DEBUG_ELSE_DUMP("Failed to locate the pre-linked kernel!\n");
			}

			_BOOT_DEBUG_ELSE_DUMP("Failed to locate the cache directory!\n");
		}
#endif // #if ((MAKE_TARGET_OS & LION) == LION)

#endif // PRELINKED_KERNEL_SUPPORT

		/*
		 * The 'bootFile' normally points to (mach_)kernel but will be empty when
		 * a prelinkedkernel was processed, or when prelinkedkernel support is
		 * disabled in the settings file, which is why we check the length here.
		 */

		if (strlen(bootFile) == 0)
		{
#if ((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) // Yosemite, El Capitan and Sierra.
			sprintf(bootFile, "/System/Library/Kernels/%s", bootInfo->bootFile);
#else
			// Set to mach_kernel for Mavericks and earlier versions of OS X.
			sprintf(bootFile, "/%s", bootInfo->bootFile);
#endif
			if (GetFileInfo(NULL, bootFile, &flags, &cachetime))
			{
				stop("ERROR: %s not found!\n", bootFile);
			}
		}

		_BOOT_DEBUG_DUMP("About to load: %s\n", bootFile);

		retStatus = LoadThinFatFile(bootFile, &fileLoadBuffer);

#if SUPPORT_32BIT_MODE
		if (retStatus <= 0 && gPlatform.ArchCPUType == CPU_TYPE_X86_64)
		{
			_BOOT_DEBUG_DUMP("Load failed for arch=x86_64, trying arch=i386 now.\n");

			gPlatform.ArchCPUType = CPU_TYPE_I386;

			retStatus = LoadThinFatFile(bootFile, &fileLoadBuffer);
		}
#endif // SUPPORT_32BIT_MODE

		_BOOT_DEBUG_DUMP("LoadStatus(%d): %s\n", retStatus, bootFile);

		/*
		 * Time to fire up the kernel - previously known as execKernel()
		 * Note: retStatus should now be anything but <= 0
		 */

		if (retStatus)
		{
			_BOOT_DEBUG_SLEEP(5);

			_BOOT_DEBUG_DUMP("execKernel-0\n");
			
			entry_t kernelEntry;
			bootArgs->kaddr = bootArgs->ksize = 0;
			
			_BOOT_DEBUG_DUMP("execKernel-1\n");
			
			if (decodeKernel(fileLoadBuffer, &kernelEntry, (char **) &bootArgs->kaddr, (int *)&bootArgs->ksize) != 0)
			{
				stop("DecodeKernel() failed!");
			}
			
			_BOOT_DEBUG_DUMP("execKernel-2 address: 0x%x\n", kernelEntry);
			
			// Allocate and copy boot args.
			moveKernelBootArgs();
			
			_BOOT_DEBUG_DUMP("execKernel-3\n");
			
			// Do we need to load kernel MKexts?
			// Skipped when a pre-linked kernel / kernelcache is being used.
			if (gLoadKernelDrivers)
			{
				_BOOT_DEBUG_DUMP("Calling loadDrivers()\n");

				// Yes. Load boot drivers from root path.
				loadDrivers("/");
			}
			
			_BOOT_DEBUG_DUMP("execKernel-4\n");
			
			finalizeEFITree(adler32); // rootUUID);
			
			_BOOT_DEBUG_DUMP("execKernel-5\n");
			
#if DEBUG_BOOT
			if (gErrors)
			{
				printf("Errors encountered while starting up the computer.\n");
				printf("Pausing %d seconds...\n", kBootErrorTimeout);
				sleep(kBootErrorTimeout);
			}
#endif
			_BOOT_DEBUG_DUMP("execKernel-6\n");
			
			finalizeKernelBootConfig();
			
			_BOOT_DEBUG_DUMP("execKernel-7 / gVerboseMode is %s\n", gVerboseMode ? "true" : "false");

#if DISABLE_LEGACY_XHCI
			disableLegacyXHCI();
#endif

#if PATCH_APIC_RET
			patchApicRedirectionTables();
#endif

			// Did we switch to graphics mode yet (think verbose mode)?
			if (gVerboseMode || bootArgs->Video.v_display != GRAPHICS_MODE)
			{
				// Switch to graphics mode and show the (white) Apple logo on a black/gray background.
				showBootLogo();
				
				_BOOT_DEBUG_SLEEP(5);
			}

			startMachKernel(kernelEntry, bootArgs); // asm.s
		}

		_BOOT_DEBUG_ELSE_DUMP("Can't find: %s\n", bootFile);

	} /* while(1) */
}
