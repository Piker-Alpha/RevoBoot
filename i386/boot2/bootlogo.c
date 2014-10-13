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
#include "appleClut8.h"

#define DEBUG 0

//==============================================================================

unsigned long lookUpCLUTIndex(unsigned char index)
{
	long colorIndex = (index * 3);
	long red   = appleClut8[ colorIndex   ];
	long green = appleClut8[ colorIndex++ ];
	long blue  = appleClut8[ colorIndex++ ];
	
	return (red << 16) | (green << 8) | blue;
}

//==============================================================================

void * stosl(void * dst, long val, long len)
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
	
	while (height--)
	{
		bcopy(&aBackGroundColor, vram, rem);
		stosl(vram + rem, aBackGroundColor, length);
		vram += VIDEO(rowBytes);
	}
}

//==============================================================================

void drawDataRectangle(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char * data)
{
	unsigned short drawWidth;
	
	long pixelBytes = VIDEO(depth) / 8;
	
	unsigned char * vram = (unsigned char *) VIDEO(baseAddr) + VIDEO(rowBytes) * y + pixelBytes * x;
	
	drawWidth = MIN(width, VIDEO(width) - x);
	height = MIN(height, VIDEO(height) - y);
	
	while (height--)
	{
		bcopy( data, vram, drawWidth * pixelBytes );
		vram += VIDEO(rowBytes);
		data += width * pixelBytes;
	}
}

#if (MAKE_TARGET_OS == YOSEMITE)

#include "picopng.h"

//==============================================================================

void showBootLogo(bool aBootRecoveryHDFlag)
{
#if DEBUG
	printf("aBootRecoveryHDFlag: %s\n", aBootRecoveryHDFlag ? "true" : "false");
	sleep(1);
#else
	setVideoMode(GRAPHICS_MODE);
#endif

	uint32_t backGroundColor = 0xbfbfbf;

	char filename[60] = "";
	char targetLogoName[30] = "appleLogo_apple";

	// bootArgs->flags |= kBootArgsFlagBlack is set by boot.efi (EFI var 'BlackMode')
	if (bootArgs->flags & kBootArgsFlagBlackTheme) // kBootArgsFlagBlack)
	{
		backGroundColor = 0x030000;
#if DEBUG
		printf("Black mode active!\n");
		sleep(1);
#endif
	}
	else
	{
		sprintf(targetLogoName, "%s%s", targetLogoName, "_gray");
#if DEBUG
		printf("Gray mode active!\n");
		sleep(1);
#endif
	}

	// bootArgs->flags |= kBootArgsFlagHiDPI is set by boot.efi (EFI var 'UIScale')
	sprintf(targetLogoName, "%s%s.png", targetLogoName, (bootArgs->flags & kBootArgsFlagHiDPI) ? "@2x" : "");
#if DEBUG
	printf("targetLogoName: %s\n", targetLogoName);
	sleep(1);
#endif
	setBackgroundColor(backGroundColor);
	
	void *imageLoadBuffer = (void *)kLoadAddr;
	//
	// Rock, Paper, Scissors?
	//
	sprintf(filename, "%s", (aBootRecoveryHDFlag) ? "/com.apple.Boot.P" : "", "/usr/standalone/i386/EfiLoginUI/appleLogo.efires");

	int EFIResourceFile = open(filename, 0);
	
	if (EFIResourceFile >= 0)
	{
		int filesize = file_size(EFIResourceFile);
		
		if (read(EFIResourceFile, (char *) kLoadAddr, filesize) == filesize)
		{
			EFIRES_HEADER * header = (EFIRES_HEADER *) imageLoadBuffer;
#if DEBUG
			printf("\nheader->revision..: %d\n", header->revision);
			printf("header->imageCount: %d\n", header->imageCount);
#endif
			int pos = sizeof(header);

			for (int index = 0; index < header->imageCount; index++)
			{
				EFIRES_IMAGE_HEADER * imageHeader = (EFIRES_IMAGE_HEADER *) (imageLoadBuffer + pos);
#if DEBUG
				printf("imageHeader->filename.: %s\n", imageHeader->filename);
				printf("imageHeader->offset...: %d\n", imageHeader->offset);
				printf("imageHeader->imageSize: %d\n", imageHeader->imageSize);
				sleep(2);
#endif
				if (strncmp((char *)imageHeader->filename, targetLogoName, strlen(targetLogoName)) == 0)
				{
					PNG_info_t *info = PNG_decode((imageLoadBuffer + imageHeader->offset), imageHeader->imageSize);
#if DEBUG
					printf("Apple logo image found!\n");
					printf("Image width...........: %d\n", info->width);
					printf("Image height..........: %d\n", info->height);
					sleep(3);
#endif
					uint8_t *bootImage = malloc((info->width * 4) * info->height);
					memcpy(bootImage, info->image->data, ((info->width * 4) * info->height));
	
#if DEBUG
					setVideoMode(GRAPHICS_MODE);
#endif
					uint16_t x = (VIDEO(width) - MIN(info->width, VIDEO(width)) ) / 2;
					uint16_t y = (VIDEO(height) - MIN(info->height, VIDEO(height)) ) / 2;
					blendImage(x, y, info->width, info->height, bootImage);
					png_alloc_free_all();
					free(bootImage);

					return;
				}
				else
				{
					pos += sizeof(EFIRES_IMAGE_HEADER);
				}
			}
		}

		close(EFIResourceFile);
	}
#if DEBUG
	else
	{
		setVideoMode(VGA_TEXT_MODE);
		error("showBootLogo(Error)");
	}
#endif

}

#else


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


/*==============================================================================

void drawDataRectangle(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char * data)
{
	unsigned short drawWidth;

	long pixelBytes = VIDEO(depth) / 8;

	unsigned char * vram = (unsigned char *) VIDEO(baseAddr) + VIDEO(rowBytes) * y + pixelBytes * x;
	
	drawWidth = MIN(width, VIDEO(width) - x);
	height = MIN(height, VIDEO(height) - y);

	while (height--)
	{
		bcopy( data, vram, drawWidth * pixelBytes );
		vram += VIDEO(rowBytes);
		data += width * pixelBytes;
	}
} */


//==============================================================================

char * decodeRLE(const void * rleData, int rleBlocks, int outBytes)
{
	char *out, *cp;

	struct RLEBlock
	{
		unsigned char count;
		unsigned char value;
	} * bp = (struct RLEBlock *) rleData;

	out = cp = (char *) malloc(outBytes);

	if (out == NULL)
	{
		return NULL;
	}
	
	while (rleBlocks--)
	{
		memset( cp, bp->value, bp->count );
		cp += bp->count;
		bp++;
	}

	return out;
}

//==============================================================================

void showBootLogo(bool aBootRecoveryHDFlag)
{
	uint8_t *bootImageData = NULL;
	uint8_t *appleBootLogo = (uint8_t *) decodeRLE(appleLogoRLE, 686, 16384); 

	setVideoMode(GRAPHICS_MODE);
	setBackgroundColor(0xbfbfbf);

	convertImage(APPLE_LOGO_WIDTH, APPLE_LOGO_HEIGHT, appleBootLogo, &bootImageData);

	drawDataRectangle(APPLE_LOGO_X, APPLE_LOGO_Y, APPLE_LOGO_WIDTH, APPLE_LOGO_HEIGHT, bootImageData);

	free(bootImageData);
	free(appleBootLogo); 
}

#endif
