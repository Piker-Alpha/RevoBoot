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
 *          INTEL CORPORATION PROPRIETARY INFORMATION
 *
 *  This software is supplied under the terms of a license  agreement or 
 *  nondisclosure agreement with Intel Corporation and may not be copied 
 *  nor disclosed except in accordance with the terms of that agreement.
 *
 *  Copyright 1988, 1989 Intel Corporation
 */

/*
 * Copyright 1993 NeXT Computer, Inc.
 * All rights reserved.
 */

/*  Copyright 2007 VMware Inc.
    "Preboot" ramdisk support added by David Elliott
    GPT support added by David Elliott.  Based on IOGUIDPartitionScheme.cpp.
 */

/*
 * Updates:
 *		- Cleanups and refactoring by DHP in 2010 and 2011.
 *		- Renamed LION_RECOVERY_SUPPORT to CORE_STARAGE_SUPPORT (PikerAlpha, November 2012).
 *		- Renamed LION_FILEVAULT_SUPPORT to CORE_STARAGE_SUPPORT (PikerAlpha, November 2012).
 *		- Renamed encryptedBootPartition to coreStoragePartition (PikerAlpha, November 2012).
 */


#include "bootstruct.h"
#include "fdisk.h"
#include "hfs.h"

#include <limits.h>


#define DPISTRLEN	32 // Defined in: IOKit/storage/IOApplePartitionScheme.h

#include <IOKit/storage/IOGUIDPartitionScheme.h>

typedef struct gpt_hdr gpt_hdr;
typedef struct gpt_ent gpt_ent;

#include "efi_tables.h"


#define BPS				512		// sector size of the device.
#define PROBEFS_SIZE	BPS * 4	// buffer size for filesystem probe.
// #define CD_BPS		2048	// CD-ROM block size.
#define N_CACHE_SECS	(BIOS_LEN / BPS)	// Must be a multiple of 4 for CD-ROMs.

// IORound and IOTrunc convenience functions, in the spirit of vm's round_page() and trunc_page().
#define IORound(value, multiple) ((((value) + (multiple) - 1) / (multiple)) * (multiple))
#define IOTrunc(value, multiple) (((value) / (multiple)) * (multiple));

// trackbuf points to the start of the track cache. Biosread() 
// will store the sectors read from disk to this memory area.
static char * const trackbuf = (char *) ptov(BIOS_ADDR);

// biosbuf points to a sector within the track cache, and is updated by Biosread().
static char * biosbuf;

// Map a disk drive to bootable volumes contained within.
struct DiskBVMap
{
    int					biosdev;	// BIOS device number (unique).
    BVRef				bvr;		// Chain of boot volumes on the disk.
    int					bvrcnt;		// Number of boot volumes.
    struct DiskBVMap *	next;		// Linkage to next mapping.
};

static struct DiskBVMap * gDiskBVMap  = NULL;
static struct disk_blk0 * gBootSector = NULL;

#if RAMDISK_SUPPORT
	// Function pointers to be filled in when a ramdisk is available:
	int (*p_ramdiskReadBytes)(int biosdev, unsigned int blkno, unsigned int byteoff, unsigned int byteCount, void * buffer) = NULL;
	int (*p_get_ramdisk_info)(int biosdev, struct driveInfo *dip) = NULL;
#endif


/* 
 * Apple specific partition types.
 * 
 * Note: The first three dash-delimited fields of a GUID are stored in little 
 * endian (the least significant byte first), the last two fields (inside {}) 
 * are not.
 */

// Apple_HFS
EFI_GUID const GPT_HFS_GUID					= { 0x48465300, 0x0000, 0x11AA, { 0xAA, 0x11, 0x00, 0x30, 0x65, 0x43, 0xEC, 0xAC } };

#if CORE_STORAGE_SUPPORT || APPLE_RAID_SUPPORT
	// Apple_Boot (RAID helper partition and the 650 MB 'Recovery HD' partition).
	EFI_GUID const GPT_BOOT_GUID			= { 0x426F6F74, 0x0000, 0x11AA, { 0xAA, 0x11, 0x00, 0x30, 0x65, 0x43, 0xEC, 0xAC } };
#endif

#if APPLE_RAID_SUPPORT
	EFI_GUID const GPT_RAID_GUID			= { 0x52414944, 0x0000, 0x11AA, { 0xAA, 0x11, 0x00, 0x30, 0x65, 0x43, 0xEC, 0xAC } };

	EFI_GUID const GPT_RAID_OFFLINE_GUID	= { 0x52414944, 0x5f4f, 0x11AA, { 0xAA, 0x11, 0x00, 0x30, 0x65, 0x43, 0xEC, 0xAC } };
#endif

/*
 * The EFI system partition (ESP) is a special (200 MB) partition from which 
 * boot.efi can load EFI (boot-time) device drivers. The EFI firmware fully 
 * supports the ESP, although Apple does not currently use it for anything. They
 * simply create it on disks greater than 2 GB to make things easier in case 
 * they need to load ESP-based drivers from it.
 */

#if EFI_SYSTEM_PARTITION_SUPPORT
    EFI_GUID const GPT_EFISYS_GUID			= { 0xC12A7328, 0xF81F, 0x11D2, { 0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B } };
#endif

#if CORE_STORAGE_SUPPORT
	// Apple_CoreStorage (FileVault 2 and Fusion Drive)
	EFI_GUID const GPT_CORESTORAGE_GUID		= { 0x53746F72, 0x6167, 0x11AA, { 0xAA, 0x11, 0x00, 0x30, 0x65, 0x43, 0xEC, 0xAC } };
#endif


//==============================================================================

static int getDriveInfo(int biosdev, struct driveInfo *dip)
{
	static struct driveInfo cached_di;
	int cc;

	// Real BIOS devices are 8-bit, so anything above that is for internal use.
	// Don't cache ramdisk drive info since it doesn't require several BIOS
	// calls and is thus not worth it.
	if (biosdev >= 0x100)
	{
#if RAMDISK_SUPPORT
		if (p_get_ramdisk_info != NULL)
		{
			cc = (*p_get_ramdisk_info)(biosdev, dip);
		}
		else
		{
			cc = -1;
		}
#else
		cc = -1;
#endif
		if (cc < 0)
		{
			dip->valid = 0;
			return -1;
		}
		else
		{
			return 0;
		}
	}

	if (!cached_di.valid || biosdev != cached_di.biosdev)
	{
		cc = get_drive_info(biosdev, &cached_di);

		if (cc < 0)
		{
			cached_di.valid = 0;
			_DISK_DEBUG_DUMP(("get_drive_info returned error\n"));
			return (-1); // BIOS call error
		}
	}

	bcopy(&cached_di, dip, sizeof(cached_di));

	return 0;
}


//==============================================================================
// Maps (E)BIOS return codes to message strings.

struct NamedValue
{
	unsigned char value;
	const char *  name;
};


//==============================================================================

static const char * getNameForValue(const struct NamedValue * nameTable, unsigned char value)
{
	const struct NamedValue * np;

	for ( np = nameTable; np->value; np++)
	{
		if (np->value == value)
		{
			return np->name;
		}
	}

	return NULL;
}

#define ECC_CORRECTED_ERR 0x11

static const struct NamedValue bios_errors[] = 
{
	{ 0x10, "Media error"					},
	{ 0x11, "Corrected ECC error"			},
	{ 0x20, "Controller or device error"	},
	{ 0x40, "Seek failed"					},
	{ 0x80, "Device timeout"				},
	{ 0xAA, "Drive not ready"				},
	{ 0x00, 0								}
};


static bool cache_valid = false;


//==============================================================================

static const char * bios_error(int errnum)
{
	static char  errorstr[] = "Error 0x00";
	const char * errname;

	errname = getNameForValue(bios_errors, errnum);

	if (errname)
	{
		return errname;
	}

	sprintf(errorstr, "Error 0x%02x", errnum);
	return errorstr; // No string, print error code only
}


//==============================================================================
// Use BIOS INT13 calls to read the sector specified. This function will also
// perform read-ahead to cache a few subsequent sector to the sector cache.
// 
// Returns 0 on success, or an error code from INT13/F2 or INT13/F42 BIOS call.

static int Biosread(int biosdev, unsigned long long secno)
{
	static int xbiosdev;
	static unsigned int xsec, xnsecs;
	struct driveInfo di;

	int  rc = -1;
	int  tries = 0;
	int bps, divisor;

	if (getDriveInfo(biosdev, &di) < 0)
	{
		return -1;
	}

	// Is biosdev in El Torito no emulation mode (think bootable CD's here)?
	if (di.no_emulation)
	{
		bps = 2048; // Yes. Assume 2K block size since the BIOS may lie about the geometry.
	}
	else
	{
		bps = di.di.params.phys_nbps;

		if (bps == 0)
		{
			return -1;
		}
	}

	divisor = bps / BPS;

	// _DISK_DEBUG_DUMP("Biosread dev %x sec %d bps %d\n", biosdev, secno, bps);

	// Use ebiosread() when supported, otherwise revert to biosread().

	if ((biosdev >= kBIOSDevTypeHardDrive) && (di.uses_ebios & EBIOS_FIXED_DISK_ACCESS))
	{
		if (cache_valid && (biosdev == xbiosdev) && (secno >= xsec) && ((unsigned int)secno < (xsec + xnsecs)))
		{
			biosbuf = trackbuf + (BPS * (secno - xsec));
			return 0;
		}

		xnsecs = N_CACHE_SECS;
		xsec = (secno / divisor) * divisor;
		cache_valid = false;

		while ((rc = ebiosread(biosdev, secno / divisor, xnsecs / divisor)) && (++tries < 5))
		{
			if (rc == ECC_CORRECTED_ERR)
			{
				rc = 0; // Ignore corrected ECC errors.
				break;
			}

			error("  EBIOS read error: %s\n", bios_error(rc), rc);
			error("    Block 0x%x Sectors %d\n", secno, xnsecs);
			_DISK_DEBUG_SLEEP(1);
		}
	}
#if LEGACY_BIOS_READ_SUPPORT
	else
	{
		static int xcyl, xhead;
		/* spc = spt * heads */
		int spc = (di.di.params.phys_spt * di.di.params.phys_heads);
		int cyl  = secno / spc;
		int head = (secno % spc) / di.di.params.phys_spt;
		int sec  = secno % di.di.params.phys_spt;

		if (cache_valid && (biosdev == xbiosdev) && (cyl == xcyl) &&
			(head == xhead) && ((unsigned int)sec >= xsec) &&
			((unsigned int)sec < (xsec + xnsecs)))
		{
			// this sector is in trackbuf cache.
			biosbuf = trackbuf + (BPS * (sec - xsec));
			return 0;
		}

		// Cache up to a track worth of sectors, but do not cross a track boundary.
		xcyl   = cyl;
		xhead  = head;
		xsec   = sec;
		xnsecs = ((unsigned int)(sec + N_CACHE_SECS) > di.di.params.phys_spt) ? (di.di.params.phys_spt - sec) : N_CACHE_SECS;

		cache_valid = false;

		while ((rc = biosread(biosdev, cyl, head, sec, xnsecs)) && (++tries < 5))
		{
			if (rc == ECC_CORRECTED_ERR)
			{
				rc = 0; // Ignore corrected ECC errors.
				break;
			}

			error("  BIOS read error: %s\n", bios_error(rc), rc);
			error("  Block %d, Cyl %d Head %d Sector %d\n", secno, cyl, head, sec);
			_DISK_DEBUG_SLEEP(1);
		}
	}
#endif // LEGACY_BIOS_READ_SUPPORT

	if (rc == 0) // BIOS reported success, mark sector cache as valid.
	{
		cache_valid = true;
	}

	biosbuf  = trackbuf + (secno % divisor) * BPS;
	xbiosdev = biosdev;

	return rc;
}


//==============================================================================

int testBiosread(int biosdev, unsigned long long secno)
{
	return Biosread(biosdev, secno);
}


//==============================================================================

static int readBytes(int biosdev, unsigned long long blkno, unsigned int byteoff, unsigned int byteCount, void * buffer)
{
#if RAMDISK_SUPPORT
	// ramdisks require completely different code for reading.
	if (p_ramdiskReadBytes != NULL && biosdev >= 0x100)
	{
		return (*p_ramdiskReadBytes)(biosdev, blkno, byteoff, byteCount, buffer);
	}
#endif

	char * cbuf = (char *) buffer;
	int error;
	int copy_len;

	// _DISK_DEBUG_DUMP("%s: dev %x block %x [%d] -> 0x%x...", __FUNCTION__, biosdev, blkno, byteCount, (unsigned)cbuf);

	for (; byteCount; cbuf += copy_len, blkno++)
	{
		error = Biosread(biosdev, blkno);

		if (error)
		{
			_DISK_DEBUG_DUMP(("error\n"));

			return (-1);
		}

		copy_len = ((byteCount + byteoff) > BPS) ? (BPS - byteoff) : byteCount;
		bcopy( biosbuf + byteoff, cbuf, copy_len );
		byteCount -= copy_len;
		byteoff = 0;
	}

	// _DISK_DEBUG_DUMP(("done\n"));

	return 0;    
}


//==============================================================================

static BVRef initNewBVRef(int biosdev, int partno, unsigned int blkoff)
{
	BVRef bvr = (BVRef) malloc(sizeof(*bvr));
	
	if (bvr)
	{
		bzero(bvr, sizeof(*bvr));
		
		bvr->biosdev			= biosdev;
		bvr->part_no			= partno;
		bvr->part_boff			= blkoff;
		bvr->type				= kBIOSDevTypeHardDrive;
		
		bvr->fs_loadfile		= HFSLoadFile;
		bvr->fs_readfile		= HFSReadFile;
		bvr->fs_getdirentry		= HFSGetDirEntry;
		bvr->fs_getfileblock	= HFSGetFileBlock;
		bvr->fs_getuuid			= HFSGetUUID;
		bvr->description		= HFSGetDescription;
		bvr->bv_free			= HFSFree;
		
		return bvr;
	}
	
	return NULL;
}


//==============================================================================

static BVRef probeBVRef(BVRef bvr, unsigned int bvrFlags)
{
	bvr->flags |= kBVFlagNativeBoot;	// 0x02
		
	if (readBootSector(bvr->biosdev, bvr->part_boff, (void *)0x7e00) == 0)
	{
		bvr->flags |= kBVFlagBootable;	// 0x08
	}
	
	bvr->flags |= bvrFlags;
	
    return bvr;
}


//==============================================================================

static BVRef newGPTBVRef(int biosdev, int partno, unsigned int blkoff, const gpt_ent * part, unsigned int bvrFlags)
{
	BVRef bvr = initNewBVRef(biosdev, partno, blkoff);
	
	if (bvr)
	{
		strlcpy(bvr->type_name, "GPT HFS+", DPISTRLEN);
		
		return probeBVRef(bvr, bvrFlags);
	}
	
	return NULL;
}


//==============================================================================

static bool isPartitionUsed(gpt_ent * partition)
{
	return efi_guid_is_null((EFI_GUID const*)partition->ent_type) ? false : true;
}


//==============================================================================

BVRef diskScanGPTBootVolumes(int biosdev, int * countPtr)
{
	_DISK_DEBUG_DUMP("In diskScanGPTBootVolumes(%d)\n", biosdev);

	void *buffer = malloc(BPS);

	if (readBytes(biosdev, 1, 0, BPS, buffer) == 0)
	{
		int gptID = 1;

		gpt_ent * gptMap = 0;
		gpt_hdr * headerMap = buffer;

		// Partition header signature present?
		if (memcmp(headerMap->hdr_sig, GPT_HDR_SIG, strlen(GPT_HDR_SIG)) == 0)
		{
			UInt32 headerSize = OSSwapLittleToHostInt32(headerMap->hdr_size);

			// Valid partition header size?
			if (headerSize >= offsetof(gpt_hdr, padding))
			{
				// No header size overrun (limiting to 512 bytes)?
				if (headerSize <= BPS)
				{
					UInt32 headerCheck = OSSwapLittleToHostInt32(headerMap->hdr_crc_self);

					headerMap->hdr_crc_self = 0;

					// Valid partition header checksum?		
					if (crc32(0, headerMap, headerSize) == headerCheck)
					{
						UInt64	gptBlock = OSSwapLittleToHostInt64(headerMap->hdr_lba_table);
						UInt32	gptCount = OSSwapLittleToHostInt32(headerMap->hdr_entries);
						UInt32	gptSize  = OSSwapLittleToHostInt32(headerMap->hdr_entsz);

						free(buffer);

						if (gptSize >= sizeof(gpt_ent))
						{
							UInt32 bufferSize = IORound(gptCount * gptSize, BPS);

							buffer = malloc(bufferSize); // Allocate a buffer.

							if (readBytes(biosdev, gptBlock, 0, bufferSize, buffer) == 0)
							{
								// Allocate a new map for this device and insert it into the chain.
								struct DiskBVMap *map = malloc(sizeof(*map));

								map->biosdev	= biosdev;
								map->bvr		= NULL;
								map->bvrcnt		= 0;
								map->next		= gDiskBVMap;
								gDiskBVMap		= map;

#if CORE_STORAGE_SUPPORT
								bool coreStoragePartition = false;
#endif

								for (; gptID <= gptCount; gptID++)
								{
									gptMap = (gpt_ent *) (buffer + ((gptID - 1) * gptSize));

									if (isPartitionUsed(gptMap))
									{
										BVRef bvr = NULL;
										int bvrFlags = -1;
#if DEBUG_DISK
										char stringuuid[100];
										efi_guid_unparse_upper((EFI_GUID*)gptMap->ent_type, stringuuid);
										printf("Reading GPT partition %d, type %s\n", gptID, stringuuid);
										sleep(1);
#endif

#if EFI_SYSTEM_PARTITION_SUPPORT		// First check for the EFI partition.
										if (efi_guid_compare(&GPT_EFISYS_GUID, (EFI_GUID const *)gptMap->ent_type) == 0)
										{
											_DISK_DEBUG_DUMP("Matched: EFI GUID, probing for HFS format...\n");
											
											//-------------- START -------------
											// Allocate buffer for 4 sectors.
											void * probeBuffer = malloc(2048);
											
											bool probeOK = false;
											
											// Read the first 4 sectors.
											if (readBytes(biosdev, gptMap->ent_lba_start, 0, 2048, (void *)probeBuffer) == 0)
											{
												//  Probing (returns true for HFS partitions).
												probeOK = HFSProbe(probeBuffer);
												
												_DISK_DEBUG_DUMP("HFSProbe status: Is %s a HFS partition.\n", probeOK ? "" : "not");
												
											}
											
											free(probeBuffer);
											
											// Veto non-HFS partitions to be invalid.
											if (!probeOK)
											{
												continue;
											}
											
											//-------------- END ---------------
											
											bvrFlags = kBVFlagEFISystem;
										}
										else
#endif

#if CORE_STORAGE_SUPPORT				// Is this a CoreStorage partition?
										if (efi_guid_compare(&GPT_CORESTORAGE_GUID, (EFI_GUID const *)gptMap->ent_type) == 0)
										{
											_DISK_DEBUG_DUMP("Matched: CoreStorage GUID\n");

											coreStoragePartition = true;
											
											continue; // Start searching for the Recovery HD/Boot OS X partition.
										}
										else if (!coreStoragePartition && 
#else
										// Check for HFS+ partitions.
										if (
#endif
										!gPlatform.BootRecoveryHD && (efi_guid_compare(&GPT_HFS_GUID, (EFI_GUID const *)gptMap->ent_type) == 0))
										{
											_DISK_DEBUG_DUMP("Matched: HFS+ GUID\n");

											bvrFlags = kBVFlagZero;
										}
#if APPLE_RAID_SUPPORT
										else if (efi_guid_compare(&GPT_RAID_GUID, (EFI_GUID const *)gptMap->ent_type) == 0)
										{
											_DISK_DEBUG_DUMP("Skipping: GPT_RAID_GUID\n");
													 
											continue;
										}
#endif

#if CORE_STORAGE_SUPPORT || APPLE_RAID_SUPPORT
										else if (efi_guid_compare(&GPT_BOOT_GUID, (EFI_GUID const *)gptMap->ent_type) == 0)
										{
											_DISK_DEBUG_DUMP("Matched: GPT_BOOT_GUID\n");
											
											bvrFlags = kBVFlagBooter;
										}
#endif
										// Only true when we found a usable partition.
										if (bvrFlags >= 0)
										{
											bvr = newGPTBVRef(biosdev, gptID, gptMap->ent_lba_start, gptMap, bvrFlags);

											if (bvr)
											{
												bvr->part_type = FDISK_HFS;
												bvr->next = map->bvr;
												map->bvr = bvr;
												++map->bvrcnt;

												// Don't waste time checking for boot.efi on ESP partitions.
												if ((bvrFlags & kBVFlagEFISystem) == 0)
												{
													// Flag System Volumes with kBVFlagSystemVolume.
													hasBootEFI(bvr);
												}

												// True on the initial run only.
												if (gPlatform.BootVolume == NULL)
												{
													// Initialize with the first bootable volume.
													gPlatform.BootVolume = gPlatform.RootVolume = bvr;

													_DISK_DEBUG_DUMP("Init B/RootVolume - partition: %d, flags: %d, gptID: %d\n", bvr->part_no, bvr->flags, gptID);
												}

												// Bail out after finding the first System Volume.
												if (bvr->flags & kBVFlagSystemVolume)
												{
													_DISK_DEBUG_DUMP("Partition %d is a System Volume\n", gptID);

													break;
												}
											}
										}
									}
								}

								free(buffer);
								*countPtr = map->bvrcnt;

								_DISK_DEBUG_DUMP("map->bvrcnt: %d\n", map->bvrcnt);
								_DISK_DEBUG_SLEEP(5);

								return map->bvr;
							}
						}
					}
				}
			}
		}
	}
	_DISK_DEBUG_ELSE_DUMP("Failed to read boot sector from BIOS device %02xh\n", biosdev);

	free(buffer);
	*countPtr = 0;

	_DISK_DEBUG_SLEEP(5);

	return NULL;
}


//==============================================================================

bool hasBootEFI(BVRef bvr)
{
	char dirSpec[40];

	long  flags, time;

	sprintf(dirSpec, "hd(%d,%d)/System/Library/CoreServices/", BIOS_DEV_UNIT(bvr), bvr->part_no);

	_DISK_DEBUG_DUMP("In hasBootEFI(%d,%d)\n", BIOS_DEV_UNIT(bvr), bvr->part_no);

	if (GetFileInfo(dirSpec, "boot.efi", &flags, &time) == 0)
	{
		_DISK_DEBUG_DUMP("boot.efi found on bvr->part_no: %d\n", bvr->part_no);
		_DISK_DEBUG_SLEEP(5);

		bvr->flags |= kBVFlagSystemVolume;

		return true;
	}

	return false;
}


//==============================================================================

BVRef diskScanBootVolumes(int biosdev, int * countPtr)
{
	BVRef bvr = NULL;
	int count = 0;
	struct DiskBVMap *map = gDiskBVMap;

	// Find an existing (cached) mapping for this device.

	for (; map; map = map->next)
	{
		if (biosdev == map->biosdev)
		{
			count = map->bvrcnt;
			break;
		}
	}

	if (map == NULL)
	{
		bvr = diskScanGPTBootVolumes(biosdev, &count);
	}
	else
	{
		bvr = map->bvr;
	}

	if (countPtr)
	{
		*countPtr += count;
	}

	return bvr;
}


//==============================================================================

BVRef getBVChainForBIOSDev(int biosdev)
{
	BVRef chain = NULL;
	struct DiskBVMap * map = gDiskBVMap;

	for (; map; map = map->next)
	{
		if (map->biosdev == biosdev)
		{
			chain = map->bvr;
			break;
		}
	}

	return chain;
}


//==============================================================================

int readBootSector(int biosdev, unsigned int secno, void * buffer)
{
	int error;
	struct disk_blk0 * bootSector = (struct disk_blk0 *) buffer;

	if (bootSector == NULL)
	{
		if (gBootSector == NULL)
		{
			gBootSector = (struct disk_blk0 *) malloc(sizeof(*gBootSector));

			if (gBootSector == NULL)
			{
				return -1;
			}
		}

		bootSector = gBootSector;
	}

	error = readBytes(biosdev, secno, 0, BPS, bootSector);

	if (error || bootSector->signature != DISK_SIGNATURE)
	{
		return -1;
	}

	return 0;
}


//==============================================================================
// Handle seek request from filesystem modules.

void diskSeek(BVRef bvr, long long position)
{
	bvr->fs_boff = position / BPS;
	bvr->fs_byteoff = position % BPS;
}


//==============================================================================
// Handle read request from filesystem modules.

int diskRead(BVRef bvr, long addr, long length)
{
	return readBytes(bvr->biosdev, bvr->fs_boff + bvr->part_boff, bvr->fs_byteoff, length, (void *) addr);
}
