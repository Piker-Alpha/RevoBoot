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
 * Copyright 1993 NeXT, Inc.
 * All rights reserved.
 */

#include "libsaio.h"
#include "vbe.h"

// Various inline routines for video I/O

static biosBuf_t bb;


//==============================================================================

int getVBEInfo(void * infoBlock)
{
    bb.intno  = 0x10;
    bb.eax.rr = funcGetControllerInfo;
    bb.es     = SEG( infoBlock );
    bb.edi.rr = OFF( infoBlock );
    bios(&bb);

    return(bb.eax.r.h);
}


//==============================================================================

int getVBEModeInfo(int mode, void * minfo_p)
{
    bb.intno  = 0x10;
    bb.eax.rr = funcGetModeInfo;
    bb.ecx.rr = mode;
    bb.es     = SEG(minfo_p);
    bb.edi.rr = OFF(minfo_p);
    bios(&bb);

    return(bb.eax.r.h);
}


//==============================================================================

int setVBEMode(unsigned short mode, const VBECRTCInfoBlock * timing)
{
    bb.intno  = 0x10;
    bb.eax.rr = funcSetMode;
    bb.ebx.rr = mode;

    if (timing) {
        bb.es     = SEG(timing);
        bb.edi.rr = OFF(timing);
    }

    bios(&bb);

    return(bb.eax.r.h);
}


//==============================================================================

int setVBEPalette(void *palette)
{
    bb.intno = 0x10;
    bb.eax.rr = funcGetSetPaletteData;
    bb.ebx.r.l = subfuncSet;
    bb.ecx.rr = 256;
    bb.edx.rr = 0;
    bb.es = SEG(palette);
    bb.edi.rr = OFF(palette);
    bios(&bb);

    return(bb.eax.r.h);
}


#if (USE_STATIC_DISPLAY_RESOLUTION == 0)
//==============================================================================
// Called from initGraphicsMode() in graphics.c

unsigned long getResolutionFromEDID(void)
{
	UInt8 data[128];
	UInt8 targetBlock = 0;
	const UInt8 header[] = { 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00	};

	bzero(data, 128);

	do
	{
		bb.intno	= 0x10;
		bb.eax.rr	= 0x4F15;
		bb.ebx.r.l	= 0x01;
		bb.edx.rr	= targetBlock++;
		bb.es		= SEG((void *)data);
		bb.edi.rr	= OFF((void *)data);
		bios(&bb);

		// BIOS / display supports Display Data Channel (EDID) reading?
		if ( ((bb.eax.rr & 0xff00) == 0) && ((bb.eax.rr & 0xff) == 0x4f) )
		{
			// Yes, supported. Check EDID header against known headers.
			if (memcmp(data, header, sizeof(header)) != 0)
			{
#if DEBUG_BOOT_GRAPHICS
				printf("targetBlock: %d\n", targetBlock);
#endif
				continue;
			}

#if DEBUG_BOOT_GRAPHICS
			short r = 0;

			for (short i = 0; i < 128; i++)
			{
				printf(" %02x", data[i]);

				r++;

				if (r == 16)
				{
					r = 0;
					printf("\n");
				}

				sleep(1);

				if (data[126] == 0)
				{
					targetBlock = 0;
				}
			}
#endif
			return (((data[56] | ((data[58] & 0xF0) << 4)) << 16) | (data[59] | ((data[61] & 0xF0) << 4)));
		}
		else
		{
#if DEBUG_BOOT_GRAPHICS
			printf("Error: Unable to get EDID (unsupported in BIOS/display)!\n");
#endif
			targetBlock = 0;
		}
	} while (targetBlock);

	return 0;
}
#endif
