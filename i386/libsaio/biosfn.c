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
 * Copyright 1993 NeXT Computer, Inc.
 * All rights reserved.
 */

/*  Copyright 2007 David Elliott
    2007-12-30 dfe
    - Enhanced code to normalize segment/offset to huge pointers so that any
      linear address within the first MB of memory can be passed to BIOS
      functions.  This allows some of the __DATA sections to span into the
      next segment and also allows stack variables to be used whereas the
      old code could only operate on static data in the first 64k.
      NOTE: Requires bios.s change to respect DS.
 */

#include "bootstruct.h"
#include "libsaio.h"

// Global private data storage file.
#include "../config/settings.h"

static biosBuf_t bb;


#if MUST_ENABLE_A20
//==============================================================================
// Called from boot() in boot.c

int fastEnableA20(void)
{
	bb.intno	= 0x15;
	bb.eax.rx	= 0x2401;
	bios(&bb);

	// If successful: CF clear, AH = 00h. On error: CF set, AH = status
	return bb.flags.cf ? bb.eax.r.h : 0;
}
#endif


//==============================================================================

int bgetc(void)
{
    /*  Poll for the next character.  Most real BIOS do not need this as the
        INT 16h,AH=0h function will block until one is received.
        Unfortunately, Apple's EFI CSM will never wake up.  This idea is lifted
        from the grub-a20.patch to GRUB's stage2/asm.S file.
     */
	while(!readKeyboardStatus());

	bb.intno	= 0x16;
	bb.eax.r.h	= 0x00;
	bios(&bb);

	return bb.eax.rr;
}


//==============================================================================
// Called from getAndProcessBootArguments() in options.c

int readKeyboardStatus(void)
{
	bb.intno = 0x16;
	bb.eax.r.h = 0x01;
	bios(&bb);

	if (bb.flags.zf)
	{
		return 0;
	}

	return bb.eax.rr;
}


//==============================================================================

unsigned int time18(void)
{
	union
	{
		struct
		{
			unsigned int low:16;
			unsigned int high:16;
		} s;

		unsigned int i;
	} time;
    
	bb.intno = 0x1a;
	bb.eax.r.h = 0x00;
	bios(&bb);
	time.s.low = bb.edx.rr;
	time.s.high = bb.ecx.rr;

	return time.i;
}


//==============================================================================
// Called from initKernelBootConfig() in bootstruct.c

unsigned long getMemoryMap(MemoryRange * rangeArray, unsigned long maxRangeCount, unsigned long * conMemSizePtr, unsigned long * extMemSizePtr)
{
	#define kMemoryMapSignature  'SMAP'
	#define kDescriptorSizeMin   20

	MemoryRange *        range = (MemoryRange *)BIOS_ADDR;
	unsigned long        count = 0;
	unsigned long long   conMemSize = 0;
	unsigned long long   extMemSize = 0;

    // Prepare for the INT15 E820h call. Each call returns a single
    // memory range. A continuation value is returned that must be
    // provided on a subsequent call to fetch the next range.
    //
    // Certain BIOSes (Award 6.00PG) expect the upper word in EAX
    // to be cleared on entry, otherwise only a single range will
    // be reported.
    //
    // Some BIOSes will simply ignore the value of ECX on entry.
    // Probably best to keep its value at 20 to avoid surprises.

    // printf("Get memory map 0x%x, %d\n", rangeArray);
	// getchar();
    if (maxRangeCount > (BIOS_LEN / sizeof(MemoryRange)))
	{
        maxRangeCount = (BIOS_LEN / sizeof(MemoryRange));
	}

    bb.ebx.rx = 0;  // Initial continuation value must be zero.

    while (count < maxRangeCount)
    {
        bb.intno  = 0x15;
        bb.eax.rx = 0xe820;
        bb.ecx.rx = kDescriptorSizeMin;
        bb.edx.rx = kMemoryMapSignature;
        bb.edi.rr = NORMALIZED_OFFSET(  (unsigned long) range);
        bb.es     = NORMALIZED_SEGMENT( (unsigned long) range);
        bios(&bb);

        // Check for errors.

        if (bb.flags.cf || bb.eax.rx != kMemoryMapSignature || bb.ecx.rx != kDescriptorSizeMin)
        {
            //printf("Got an error %x %x %x\n", bb.flags.cf,
            //       bb.eax.rx, bb.ecx.rx);
            break;
        }

        // Tally up the conventional/extended memory sizes.

        if (range->type == kMemoryRangeUsable || range->type == kMemoryRangeACPI || range->type == kMemoryRangeNVS)
        {
            // Tally the conventional memory ranges.
            if (range->base + range->length <= 0xa0000)
			{
                conMemSize += range->length;
			}

            // Record the top of extended memory.
            if (range->base >= EXTENDED_ADDR)
			{
                extMemSize += range->length;
			}
        }

        range++;
        count++;

        // Is this the last address range?

        if (bb.ebx.rx == 0)
		{
            //printf("last range\n");
            break;
        }
    }

    *conMemSizePtr = (conMemSize / 1024);  // size in KB
    *extMemSizePtr = (extMemSize / 1024);  // size in KB

    // Copy out data
    bcopy((char *)BIOS_ADDR, rangeArray, ((char *)range - (char *)BIOS_ADDR));

#if DEBUG
    {
        int i;
        printf("%d total ranges\n", count);

		getchar();

        for (i = 0, range = rangeArray; i<count; i++, range++)
        {
            printf("range: type %d, base 0x%x, length 0x%x\n", range->type, (unsigned int)range->base, (unsigned int)range->length);
            getchar();
        }
    }
#endif

    return count;
}


//==============================================================================
// Called from initKernelBootConfig() in bootstruct.c

unsigned long getExtendedMemorySize()
{
	// Get extended memory size for large configurations. Not used unless
	// the INT15, E820H call (Get System Address Map) failed.
	//
	// Input:
	//
	// AX   Function Code   E801h
	//
	// Outputs:
	//
	// CF   Carry Flag      Carry cleared indicates no error.
	// AX   Extended 1      Number of contiguous KB between 1 and 16 MB,
	//                      maximum 0x3C00 = 15 MB.
	// BX   Extended 2      Number of contiguous 64 KB blocks between
	//                      16 MB and 4 GB.
	// CX   Configured 1    Number of contiguous KB between 1 and 16 MB,
	//                      maximum 0x3C00 = 15 MB.
	// DX   Configured 2    Number of contiguous 64 KB blocks between
	//                      16 MB and 4 GB.

	bb.intno  = 0x15;
	bb.eax.rx = 0xe801;
	bios(&bb);

	// Return the size of memory above 1MB (extended memory) in kilobytes.

	if (bb.flags.cf == 0)
	{
		return (bb.ebx.rr * 64 + bb.eax.rr);
	}

	// Get Extended memory size. Called on last resort since the return
	// value is limited to 16-bits (a little less than 64MB max). May
	// not be supported by modern BIOSes.
	//
	// Input:
	//
	// AX   Function Code   88h
	//
	// Outputs:
	//
	// CF   Carry Flag      Carry cleared indicates no error.
	// AX   Memory Count    Number of contiguous KB above 1MB.

	bb.intno  = 0x15;
	bb.eax.rx = 0x88;
	bios(&bb);

	// Return the size of memory above 1MB (extended memory) in kilobytes.

	return bb.flags.cf ? 0 : bb.eax.rr;
}


//==============================================================================
// Called from initKernelBootConfig() in bootstruct.c

unsigned long getConventionalMemorySize()
{
	bb.intno = 0x12;
	bios(&bb);

	return bb.eax.rr;  // kilobytes
}


//==============================================================================
// Called from setVESATextMode() in graphics.c

void video_mode(int mode)
{
	bb.intno = 0x10;
	bb.eax.r.h = 0x00;
	bb.eax.r.l = mode;
	bios(&bb);
}


// ==============================================================================
/* Called from setVESATextMode() in graphics.c

unsigned long getResolutionFromEDID(void)
{
	UInt8 data[128];

	bb.intno	= 0x10;
	bb.eax.rr	= 0x4F15;
	bb.ebx.r.l	= 0x01;
	bb.edx.rr	= 0x01; // Target block.
	bb.es		= SEG(data);
	bb.edi.rr	= OFF(data);
	bios(&bb);
	
	if (bb.eax.r.h == 0)
	{
		return ( ( (data[56] | ((data[58] & 0xF0) << 4)) << 16) | 
				 ( (data[59] | ((data[61] & 0xF0 ) << 4)) ));
	}

	return 0;
} */


//==============================================================================

int biosread(int dev, int cyl, int head, int sec, int num)
{
	int i;

	bb.intno = 0x13;
	sec += 1;  // sector numbers start at 1.
    
	for (i = 0; ;)
	{
		bb.ecx.r.h = cyl;
		bb.ecx.r.l = ((cyl & 0x300) >> 2) | (sec & 0x3F);
		bb.edx.r.h = head;
		bb.edx.r.l = dev;
		bb.eax.r.l = num;
		bb.ebx.rr  = OFFSET(ptov(BIOS_ADDR));
		bb.es      = SEGMENT(ptov(BIOS_ADDR));

		bb.eax.r.h = 0x02;
		bios(&bb);

		// In case of a successful call, make sure we set AH (return code) to zero.
		if (bb.flags.cf == 0)
		{
			bb.eax.r.h = 0;
		}

		// Now we can really check for the return code (AH) value.
		if ((bb.eax.r.h == 0x00) || (i++ >= 5))
		{
			break;
		}

        // Reset disk subsystem and try again.
		bb.eax.r.h = 0x00;
		bios(&bb);
	}

	return bb.eax.r.h;
}


//==============================================================================

int ebiosread(int dev, unsigned long long sec, int count)
{
	int i;
    
	static struct
	{
		unsigned char  size;
		unsigned char  reserved;
		unsigned char  numblocks;
		unsigned char  reserved2;
		unsigned short bufferOffset;
		unsigned short bufferSegment;
		unsigned long  long startblock;
	} addrpacket __attribute__((aligned(16))) = {0};
	addrpacket.size = sizeof(addrpacket);

	for (i = 0; ;)
	{
		bb.intno   = 0x13;
		bb.eax.r.h = 0x42;
		bb.edx.r.l = dev;
		bb.esi.rr  = NORMALIZED_OFFSET((unsigned)&addrpacket);
		bb.ds      = NORMALIZED_SEGMENT((unsigned)&addrpacket);
		addrpacket.reserved = addrpacket.reserved2 = 0;
		addrpacket.numblocks     = count;
		addrpacket.bufferOffset  = OFFSET(ptov(BIOS_ADDR));
		addrpacket.bufferSegment = SEGMENT(ptov(BIOS_ADDR));
		addrpacket.startblock    = sec;
		bios(&bb);

		// In case of a successful call, make sure we set AH (return code) to zero.
		if (bb.flags.cf == 0)
		{
			bb.eax.r.h = 0;
		}
		
		// Now we can really check for the return code (AH) value.
		if ((bb.eax.r.h == 0x00) || (i++ >= 5))
		{
			break;
		}

        // Reset disk subsystem and try again.
		bb.eax.r.h = 0x00;
		bios(&bb);
	}

	return bb.eax.r.h;
}


//==============================================================================

void putc(int ch)
{
	bb.intno	= 0x10;
	bb.ebx.r.h	= 0x00;  /* background black */
	bb.ebx.r.l	= 0x0F;  /* foreground white */
	bb.eax.r.h	= 0x0e;
	bb.eax.r.l	= ch;
	bios(&bb);
}


//==============================================================================

void putca(int ch, int attr, int repeat)
{
	bb.intno   = 0x10;
	bb.ebx.r.h = 0x00;   /* page number */
	bb.ebx.r.l = attr;   /* attribute   */
	bb.eax.r.h = 0x9;
	bb.eax.r.l = ch;
	bb.ecx.rx  = repeat; /* repeat count */ 
	bios(&bb);
}


//==============================================================================
// Called from get_drive_info() below.
// Check to see if the passed-in drive is in El Torito no-emulation mode.

int is_no_emulation(int drive)
{
	struct packet
	{
		unsigned char packet_size;
		unsigned char media_type;
		unsigned char drive_num;
		unsigned char ctrlr_index;
		unsigned long lba;
		unsigned short device_spec;
		unsigned short buffer_segment;
		unsigned short load_segment;
		unsigned short sector_count;
		unsigned char cyl_count;
		unsigned char sec_count;
		unsigned char head_count;
		unsigned char reseved;
	} __attribute__((packed));
	static struct packet pkt;

	bzero(&pkt, sizeof(pkt));
	pkt.packet_size = 0x13;

	bb.intno   = 0x13;
	bb.eax.r.h = 0x4b;
	bb.eax.r.l = 0x01;     // subfunc: get info
	bb.edx.r.l = drive;
	bb.esi.rr = NORMALIZED_OFFSET((unsigned)&pkt);
	bb.ds     = NORMALIZED_SEGMENT((unsigned)&pkt);

	bios(&bb);

#if DEBUG
	printf("el_torito info drive %x\n", drive);
	printf("--> cf %x, eax %x\n", bb.flags.cf, bb.eax.rr);
	printf("pkt_size: %x\n", pkt.packet_size);
	printf("media_type: %x\n", pkt.media_type);
	printf("drive_num: %x\n", pkt.drive_num);
	printf("device_spec: %x\n", pkt.device_spec);
	printf("press a key->\n");
	getchar();
#endif

	/* Some BIOSes erroneously return cf = 1 */
	/* Just check to see if the drive number is the same. */
	if (pkt.drive_num == drive && (pkt.media_type & 0x0F) == 0)
	{
		return 1; // We are in no-emulation mode.
	}

	return 0;
}


//==============================================================================
// Called from getDriveInfo() in disk.c

int get_drive_info(int drive, struct driveInfo *dp)
{
    int ret = 0;

    boot_drive_info_t *di = &dp->di;

#if UNUSED
    if (maxhd == 0)
    {
        bb.intno = 0x13;
        bb.eax.r.h = 0x08;
        bb.edx.r.l = 0x80;
        bios(&bb);

        if (bb.flags.cf == 0)
		{
            maxhd = 0x7f + bb.edx.r.l;
		}
    };

    if (drive > maxhd)
	{
        return 0;
	}
#endif

    bzero(dp, sizeof(struct driveInfo));
    dp->biosdev = drive;

    /* Check for El Torito no-emulation mode. */
    dp->no_emulation = is_no_emulation(drive);

    /* Check drive for EBIOS support. */
    bb.intno = 0x13;
    bb.eax.r.h = 0x41;
    bb.edx.r.l = drive;
    bb.ebx.rr = 0x55aa;
    bios(&bb);

    if ((bb.ebx.rr == 0xaa55) && (bb.flags.cf == 0))
	{
        dp->uses_ebios = bb.ecx.r.l; // Get flags for supported operations.
	}

    if (dp->uses_ebios & (EBIOS_ENHANCED_DRIVE_INFO | EBIOS_LOCKING_ACCESS | EBIOS_FIXED_DISK_ACCESS))
    {
        // Get EBIOS drive info.
        static struct drive_params params;
        params.buf_size = sizeof(params);

        bb.intno	= 0x13;
        bb.eax.r.h	= 0x48;
        bb.edx.r.l	= drive;
        bb.esi.rr	= NORMALIZED_OFFSET((unsigned)&params);
        bb.ds		= NORMALIZED_SEGMENT((unsigned)&params);
        bios(&bb);

        if (bb.flags.cf != 0 /* || params.phys_sectors < 2097152 */)
        {
            dp->uses_ebios = 0;
            di->params.buf_size = 1;
        }
        else
        {
            bcopy(&params, &di->params, sizeof(params));

            if (drive >= BASE_HD_DRIVE && 
                (dp->uses_ebios & EBIOS_ENHANCED_DRIVE_INFO) &&
                di->params.buf_size >= 30 &&
                !(di->params.dpte_offset == 0xFFFF && di->params.dpte_segment == 0xFFFF))
            {
                void *ptr = (void *)(di->params.dpte_offset + ((unsigned int)di->params.dpte_segment << 4));
                bcopy(ptr, &di->dpte, sizeof(di->dpte));
            }
        }
    }

    if (dp->no_emulation)
    {
        /* Some BIOSes give us erroneous EBIOS support information.
         * Assume that if you're on a CD, then you can use
         * EBIOS disk calls.
         */
        dp->uses_ebios |= EBIOS_FIXED_DISK_ACCESS;
    }
#if DEBUG
    print_drive_info(di);
    printf("uses_ebios = 0x%x\n", dp->uses_ebios);
    printf("result %d\n", ret);
    printf("press a key->\n");
	getchar();
#endif

    if (ret == 0)
	{
        dp->valid = 1;
	}

    return ret;
}


//==============================================================================

void sleep(int n)
{
	if (n < 60)
	{
		unsigned int endtime = (time18() + (18*n));
		while (time18() < endtime);
	}
}


//==============================================================================

void delay(int ms)
{
    bb.intno	= 0x15;
    bb.eax.r.h	= 0x86;
    bb.ecx.rr	= ms >> 16;
    bb.edx.rr	= ms & 0xFFFF;
    bios(&bb);
}
