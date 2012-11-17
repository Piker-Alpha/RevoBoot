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
 *
 * Copyright 1994 NeXT Computer, Inc. All rights reserved.
 *
 * Updates:
 *			- Unused sysConfigValid removed (PikerAlpha, November 2012).
 *
 */

#ifndef __BOOT2_BOOT_H
#define __BOOT2_BOOT_H

#include "platform.h"

#define STATE_SUCCESS	0	// Move this to a more appropriate header file.

#if USE_STATIC_DISPLAY_RESOLUTION
	#define DEFAULT_SCREEN_WIDTH	STATIC_SCREEN_WIDTH
	#define DEFAULT_SCREEN_HEIGHT	STATIC_SCREEN_HEIGHT
#else
	#define DEFAULT_SCREEN_WIDTH	1600
	#define DEFAULT_SCREEN_HEIGHT	1200
#endif

#define APPLE_LOGO_WIDTH  128
#define APPLE_LOGO_HEIGHT 128

/*
 * Used in showBootLogo. Now using the VIDEO() macro instead of the static 
 * values. This way the logo should be properly positioned. With or without 
 * specifying a "Graphics Mode" in com.apple.Boot.plist And no matter what 
 * values you've set in RevoBoot/i386/config/settings.h Should all be fine now.
 */

#define APPLE_LOGO_X    ((VIDEO(width) - APPLE_LOGO_WIDTH) / 2)
#define APPLE_LOGO_Y    ((VIDEO(height) - APPLE_LOGO_HEIGHT) / 2)

/*
 * How long to wait (in seconds) to load the kernel after displaying the "boot:" prompt.
 */

#define kBootErrorTimeout 5

/*
 * Keys used in system Boot.plist
 */

#define kGraphicsModeKey    "Graphics Mode"
#define kTextModeKey        "Text Mode"
#define kQuietBootKey       "Quiet Boot"
#define kKernelFlagsKey     "Kernel Flags"
#define kMKextCacheKey      "MKext Cache"
#define kKernelNameKey      "Kernel"
#define kKernelCacheKey     "Kernel Cache"
#define kBootDeviceKey      "Boot Device"
#define kTimeoutKey         "Timeout"
#define kRootDeviceKey      "rd"
#define kBootUUIDKey        "boot-uuid"
#define kHelperRootUUIDKey  "Root UUID"
#define kPlatformKey        "platform"
#define kACPIKey            "acpi"
#define kScanSingleDriveKey "Scan Single Drive"
#define kInsantMenuKey      "Instant Menu"
#define kDefaultKernel      "mach_kernel"
#define kWaitForKeypressKey "Wait"

/*
 * Flags to the booter or kernel
 *
 */

#define kVerboseModeFlag		"-v"
#define kSafeModeFlag			"-x"
#define kIgnoreCachesFlag		"-f"	// Formerly kOldSafeModeFlag
#define kIgnoreBootFileFlag		"-F"
#define kSingleUserModeFlag		"-s"

/*
 * Booter behavior control
 */

#define kBootTimeout         -1

// A global set by boot() to record the device that the booter was loaded from.

extern long gBootMode;
extern char bootPrompt[];

// Kernel Boot Modes
enum
{
	kBootModeNormal = 0,
	kBootModeSafe   = 1,
	kBootModeSecure = 2,
	kBootModeQuiet  = 4
};

/* 
 * Note well that we take an easier approice, and this should not be 
 * confused with /chosen/boot-file-path because this is what we want.
 */
#define BOOT_DEVICE_PATH "\\System\\Library\\CoreServices\\boot.efi"

// Taken from kextcache_main.h - kernel cache (Adler32) related.

#define PLATFORM_NAME_LEN 64
#define ROOT_PATH_LEN 256

/*
 * bootlogo.c
 */

extern void showBootLogo();

/*
 * fake_efi.c
 */

extern void finalizeEFITree();

/*
 * graphics.c
 */

extern void setVideoMode(int mode);
extern  bool inGraphicsMode(void);

/*
 * hfs.c
 */

extern long HFSGetUUID(CICell ih, char *uuidStr);

/*
 * drivers.c
 */

#if RAMDISK_SUPPORT
	extern void drawPreview(void *src, uint8_t * saveunder);
#endif

extern long loadDrivers(char * dirSpec);
extern long decodeKernel(void *binary, entry_t *rentry, char **raddr, int *rsize);

typedef long (*FileLoadDrivers_t)(char *dirSpec, long plugin);

/*!
    Hookable function pointer called during the driver loading phase that
    allows other code to cause additional drivers to be loaded.
 */

extern long (*LoadExtraDrivers_p)(FileLoadDrivers_t FileLoadDrivers_p);

/*
 * lzss.c
 */

extern int decompressLZSS(u_int8_t *dst, u_int8_t *src, u_int32_t srclen);

/*
 * options.c
 */

extern void getAndProcessBootArguments(char *configKernelFlags);

/*
 * resume.c
 */

#if HIBERNATE_SUPPORT
	void HibernateBoot(char *boot_device);
#endif

// Taken from: kextcache_main.h

struct compressed_kernel_header
{
	u_int32_t	signature;
	u_int32_t	compressType;						// compress_type;
	u_int32_t	adler32;
	u_int32_t	uncompressedSize;					// uncompressed_size;
	u_int32_t	compressedSize;						// compressed_size;
	u_int32_t	reserved[11];
	char		platformName[PLATFORM_NAME_LEN];	// platform_name[64];
	char		rootPath[ROOT_PATH_LEN];			// root_path[256];
	// char		data[0];
	u_int8_t data[0];
};

typedef struct compressed_kernel_header compressed_kernel_header;

/*
 * bmdecompress.c ???
 */

void * DecompressData(void *srcbase, int *dw, int *dh, int *bytesPerPixel);

#endif /* !__BOOT2_BOOT_H */
