/*
 * Copyright (c) 1999-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999-2004 Apple Computer, Inc.  All Rights
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

#include "boot.h"
#include "bootstruct.h"

extern BVRef    bvChain;

static char gBootArgs[BOOT_STRING_LEN];
static char * gBootArgsPtr = gBootArgs;
static char * gBootArgsEnd = gBootArgs + BOOT_STRING_LEN - 1;


//==============================================================================

static void skipblanks(const char ** cpp)
{
	while (**(cpp) == ' ' || **(cpp) == '\t' ) ++(*cpp);
}


//==============================================================================

bool copyArgument(const char *argName, const char *val, int cnt, char **argP, int *cntRemainingP)
{
	int argLen = argName ? strlen(argName) : 0;
	int len = argLen + cnt + 1;  // + 1 to account for space.

	if (len > *cntRemainingP)
	{
		// error("Warning: boot arguments too long, truncating\n");
		return false;
	}

	if (argName)
	{
		strncpy(*argP, argName, argLen);
		*argP += argLen;
		*argP[0] = '=';
		(*argP)++;
		len++; // +1 to account for '='
	}

	strncpy(*argP, val, cnt);
	*argP += cnt;
	*argP[0] = ' ';
	(*argP)++;
	*cntRemainingP -= len;

	return true;
}


//==============================================================================
// Copyright (c) 2010 by DHP.  All rights reserved.

void getAndProcessBootArguments(char * configKernelFlags)
{
	bool truncated = false;

	const char * cp			= gBootArgs;

	char * argP				= bootArgs->CommandLine;

	int key;
	int pressedKey			= 0;
	int cntRemaining		= BOOT_STRING_LEN - 2; // (1024 -2)
	int kernelFlagsLength	= strlen(configKernelFlags);

	int index = 1;
	int bootModes[6]			= { -1, kBootModeNormal, kBootModeNormal, -1, kBootModeSafe, kBootModeNormal };
	const char * bootFlags[6]	= { "", kVerboseModeFlag, kSingleUserModeFlag, "", kSafeModeFlag, kIgnoreCachesFlag };

	bzero(gBootArgs, sizeof(gBootArgs));
	skipblanks(&cp);

    while (readKeyboardStatus())
    {
        key = (bgetc() & 0xff);

		switch (key |= 0x20)
		{
			case 'v': // Verbose booting.
				printf("V\n");
				pressedKey |= 1;
				break;

			case 's': // Single user mode.
				printf("S\n");
				pressedKey |= 2;
				break;

			case 'x': // Safe mode.
				printf("X\n");
				pressedKey |= 4;
				break;

			case 'f': // Skip MKext.
				printf("F\n");
				pressedKey |= 8;
				break;
		}
    }

	if ((pressedKey & 1) || (pressedKey & 2))
	{
		// Mandatory mode change before entering single user mode,
		// which is optional for normal and safe booting modes.
		gVerboseMode = true; // ((pressedKey & 1) || (pressedKey & 2));
	}

    for (index = 1; index < 6; index++)
	{
		int currentMode = bootModes[index];
		// printf("currentMode: %d\n", currentMode);
		// sleep(2);

		if (currentMode >= 0 && (pressedKey & index) == index)
		{
			// printf("And action...\n");
			if (gBootArgsPtr + 3 < gBootArgsEnd)
			{
				gPlatform.BootMode = currentMode;
				copyArgument(0, bootFlags[index], 3, &argP, &cntRemaining);
			}

			pressedKey -= index;
		}
    }

	// Reworked copy from processBootOptions() which is no more.
	if (kernelFlagsLength)
	{
		if (kernelFlagsLength > cntRemaining)
		{
			truncated = true;
			kernelFlagsLength = cntRemaining;
		}

		// Store kernel flags.
		strncpy(argP, configKernelFlags, kernelFlagsLength);
		argP[kernelFlagsLength++] = ' ';
		cntRemaining -= kernelFlagsLength;
	}

	int bootArgsLength = strlen(cp);
    
	if (bootArgsLength > cntRemaining)
	{
		truncated = true;
		bootArgsLength = cntRemaining;
	}
    
	if (truncated)
	{
		error("Warning: boot arguments too long, truncating\n");
	}

	// Store boot args.
	strncpy(&argP[kernelFlagsLength], cp, bootArgsLength);
	argP[kernelFlagsLength + bootArgsLength] = '\0';

	if (configKernelFlags)
	{
		// Free the earlier allocated (in boot.c) / passed on Kernel Flags.
		free(configKernelFlags);
	}
}
