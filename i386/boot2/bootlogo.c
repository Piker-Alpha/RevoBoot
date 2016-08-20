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
 * Copyright 1993 NeXT, Inc. All rights reserved.
 *
 * Refactorizing done by DHP in 2011.
 */

#include "boot.h"
#include "bootlogo.h"
#include "bootstruct.h"

#define DEBUG 0

//==============================================================================

unsigned long lookUpCLUTIndex(unsigned char index)
{
	long colorIndex = (index * 3);
#if (((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) && (BLACKMODE == 1)) // Yosemite, El Capitan and Sierra.
	long red   = AppleLogoBlackClut[ colorIndex   ];
	long green = AppleLogoBlackClut[ colorIndex++ ];
	long blue  = AppleLogoBlackClut[ colorIndex++ ];
#else
	long red   = AppleLogoClut[ colorIndex   ];
	long green = AppleLogoClut[ colorIndex++ ];
	long blue  = AppleLogoClut[ colorIndex++ ];
#endif
	
	return (red << 16) | (green << 8) | blue;
}

//==============================================================================

void * stosl(void *dst, long val, long len)
{
	asm volatile ("rep; stosl"
				  : "=c" (len), "=D" (dst)
				  : "0" (len), "1" (dst), "a" (val)
				  : "memory" );
	
	return dst;
}

//==============================================================================

void setBackgroundColor(uint32_t aBackGroundColor)
{
	long pixelBytes = VIDEO(depth) / 8;
	
	char * vram = (char *) VIDEO(baseAddr) + VIDEO(rowBytes) + pixelBytes;
	
	int width = VIDEO(width);
	int height = VIDEO(height);
	
	int rem = (pixelBytes * width) % 4;
	int length = pixelBytes * width / 4;

	bcopy(&aBackGroundColor, vram, rem);

	while (height--)
	{
		stosl(vram + rem, aBackGroundColor, length);
		vram += VIDEO(rowBytes);
	}
}

//==============================================================================

void drawDataRectangle(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char *data)
{
	long pixelBytes = VIDEO(depth) / 8;
	
	char * vram = (char *) VIDEO(baseAddr) + VIDEO(rowBytes) * y + pixelBytes * x;
	
	height = MIN(height, VIDEO(height) - y);

	if (data)
	{
		while (height--)
		{
			bcopy(data, vram, (width * pixelBytes));
			vram += VIDEO(rowBytes);
			data += (width * pixelBytes);
		}
	}
}

//==============================================================================

int convertImage(unsigned short width, unsigned short height, const unsigned char *imageData, unsigned char **newImageData)
{
	int index = 0;
	int size = (width * height); // 16384
	int depth = VIDEO(depth);

	unsigned char *img = 0;
	unsigned long *img32;

	switch (depth)
	{
		case 32:
			img32 = malloc(size * 4);

			if (!img32)
			{		
				break;
			}

			for (; index < size; index++)
			{
				img32[index] = lookUpCLUTIndex(imageData[index]);
			}

			img = (unsigned char *)img32;
			break;
	}

	*newImageData = img;

	return 0;
}


//==============================================================================

void showBootLogo()
{
	setVideoMode(GRAPHICS_MODE);

#if (((MAKE_TARGET_OS & YOSEMITE) == YOSEMITE) && (BLACKMODE == 1)) // Yosemite, El Capitan and Sierra.
	setBackgroundColor(0x030000);
	uint32_t compressedSize = sizeof(AppleLogoBlackPacked);
	void *logoData = (void *)AppleLogoBlackPacked;
#else
	setBackgroundColor(0xbfbfbf);
	uint32_t compressedSize = sizeof(AppleLogoPacked);
	void *logoData = (void *)AppleLogoPacked;
#endif

	int logoSize = (APPLE_LOGO_WIDTH * APPLE_LOGO_HEIGHT);
	void * decompressedData = malloc(logoSize);

	if (decompressedData)
	{
		if (lzvn_decode(decompressedData, logoSize, logoData, compressedSize) == logoSize)
		{
			 uint8_t *bootImageData = NULL;
			 convertImage(APPLE_LOGO_WIDTH, APPLE_LOGO_HEIGHT, decompressedData, &bootImageData);
			 drawDataRectangle(APPLE_LOGO_X, APPLE_LOGO_Y, APPLE_LOGO_WIDTH, APPLE_LOGO_HEIGHT, bootImageData);
		}

		free(decompressedData);
	}
}
