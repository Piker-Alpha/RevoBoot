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
/* Useful types. */

#ifndef __LIBSAIO_SAIO_TYPES_H
#define __LIBSAIO_SAIO_TYPES_H

#include <sys/reboot.h>
#include <sys/types.h>
#include "bios.h"

#include <IOKit/IOTypes.h>
// #include <pexpert/i386/boot.h>


typedef unsigned long entry_t;

typedef struct
{
	unsigned int sectors:8;
	unsigned int heads:8;
	unsigned int cylinders:16;
} compact_diskinfo_t;


struct driveParameters
{
	int cylinders;
	int sectors;
	int heads;
	int totalDrives;
};


typedef struct Tag
{
	long       type;
	char       *string;
	struct Tag *tag;
	struct Tag *tagNext;
} Tag, *TagPtr;


typedef struct
{
	char	plist[4096];	// buffer for plist
	TagPtr	dictionary;		// buffer for XML dictionary
	bool  canOverride;		// flag to mark a dictionary can be overriden
} config_file_t;


typedef struct boot_drive_info
{
	struct drive_params
	{
		unsigned short buf_size;
		unsigned short info_flags;
		unsigned long  phys_cyls;
		unsigned long  phys_heads;
		unsigned long  phys_spt;
		unsigned long long phys_sectors;
		unsigned short phys_nbps;
		unsigned short dpte_offset;
		unsigned short dpte_segment;
		unsigned short key;
		unsigned char  path_len;
		unsigned char  reserved1;
		unsigned short reserved2;
		unsigned char  bus_type[4];
		unsigned char  interface_type[8];
		unsigned char  interface_path[8];
		unsigned char  dev_path[8];
		unsigned char  reserved3;
		unsigned char  checksum;
	} params __attribute__((packed));

	struct drive_dpte
	{
		unsigned short io_port_base;
		unsigned short control_port_base;
		unsigned char  head_flags;
		unsigned char  vendor_info;
		unsigned char  irq         : 4;
		unsigned char  irq_unused  : 4;
		unsigned char  block_count;
		unsigned char  dma_channel : 4;
		unsigned char  dma_type    : 4;
		unsigned char  pio_type    : 4;
		unsigned char  pio_unused  : 4;
		unsigned short option_flags;
		unsigned short reserved;
		unsigned char  revision;
		unsigned char  checksum;
    } dpte __attribute__((packed));
} __attribute__((packed)) boot_drive_info_t;


struct driveInfo
{
	boot_drive_info_t di;

	int uses_ebios;
	int no_emulation;
	int biosdev;
	int valid;
};


typedef struct FinderInfo
{
	unsigned char data[16];
} FinderInfo;


struct         BootVolume;
typedef struct BootVolume * BVRef;
typedef struct BootVolume * CICell;

typedef long (*FSInit)(CICell ih);
typedef long (*FSLoadFile)(CICell ih, char * filePath);
typedef long (*FSReadFile)(CICell ih, char *filePath, void *base, uint64_t offset, uint64_t length);
typedef long (*FSGetFileBlock)(CICell ih, char *filePath, unsigned long long *firstBlock);
typedef long (*FSGetDirEntry)(CICell ih, char * dirPath, long * dirIndex,
                              char ** name, long * flags, long * time,
                              FinderInfo * finderInfo, long * infoValid);
typedef long (* FSGetUUID)(CICell ih, char *uuidStr);
typedef void (*BVGetDescription)(CICell ih, char * str, long strMaxLen);
// Can be just pointed to free or a special free function
typedef void (*BVFree)(CICell ih);

struct iob
{
	char *         i_buf;           /* file load address */
	unsigned int   i_flgs;          /* see F_* below */
	unsigned int   i_offset;        /* seek byte offset in file */
	int            i_filesize;      /* size of file */
};

#define F_READ     0x1              /* file opened for reading */
#define F_WRITE    0x2              /* file opened for writing */
#define F_ALLOC    0x4              /* buffer allocated */
#define F_FILE     0x8              /* file instead of device */
#define F_NBSF     0x10             /* no bad sector forwarding */
#define F_SSI      0x40             /* set skip sector inhibit */
#define F_MEM      0x80             /* memory instead of file or device */

struct dirstuff
{
	char *         dir_path;        /* directory path */
	long           dir_index;       /* directory entry index */
	BVRef          dir_bvr;         /* volume reference */
};

#define BVSTRLEN 32

struct BootVolume
{
	BVRef            next;            /* list linkage pointer */
	int              biosdev;         /* BIOS device number */
	int              type;            /* device type (floppy, hd, network) */
	unsigned int     flags;           /* attribute flags */
	BVGetDescription description;     /* BVGetDescription function */
	int              part_no;         /* partition number (1 based) */
	unsigned int     part_boff;       /* partition block offset */
	unsigned int     part_type;       /* partition type */
	unsigned int     fs_boff;         /* 1st block # of next read */
	unsigned int     fs_byteoff;      /* Byte offset for read within block */
	FSLoadFile       fs_loadfile;     /* FSLoadFile function */
	FSReadFile       fs_readfile;     /* FSReadFile function */
	FSGetDirEntry    fs_getdirentry;  /* FSGetDirEntry function */
	FSGetFileBlock   fs_getfileblock; /* FSGetFileBlock function */
	FSGetUUID        fs_getuuid;      /* FSGetUUID function */
	unsigned int     bps;             /* bytes per sector for this device */
	char             name[BVSTRLEN];  /* (name of partition) */
	char             type_name[BVSTRLEN]; /* (type of partition, eg. Apple_HFS) */
	BVFree           bv_free;         /* BVFree function */
	uint32_t         modTime;
	char			 label[BVSTRLEN]; /* partition volume label */
	char			 altlabel[BVSTRLEN]; /* partition volume label */
	bool             filtered;        /* newFilteredBVChain() will set to TRUE */
	bool             visible;         /* will shown in the device list */
};

enum
{
	kBVFlagZero				= 0x00,
	kBVFlagPrimary			= 0x01,
	kBVFlagNativeBoot		= 0x02,
	kBVFlagForeignBoot		= 0x04,
	kBVFlagBootable			= 0x08,
	kBVFlagEFISystem		= 0x10,
	kBVFlagBooter			= 0x20,
	kBVFlagSystemVolume		= 0x40,
	kBVFlagInstallVolume    = 0x80
};

enum
{
	kBIOSDevTypeFloppy    = 0x00,
	kBIOSDevTypeHardDrive = 0x80,
	kBIOSDevTypeNetwork   = 0xE0,
	kBIOSDevUnitMask      = 0x0F,
	kBIOSDevTypeMask      = 0xF0,
	kBIOSDevMask          = 0xFF
};

enum
{
	kPartitionTypeHFS	  = 0xAF,
	kPartitionTypeHPFS    = 0x07,
	kPartitionTypeFAT16   = 0x06,
	kPartitionTypeFAT32   = 0x0c,
	kPartitionTypeEXT3    = 0x83,
};

#define BIOS_DEV_UNIT(bvr)  ((bvr)->biosdev - (bvr)->type)

// KernBootStruct device types.

enum
{
	DEV_SD = 0,
	DEV_HD = 1,
	DEV_FD = 2,
	DEV_EN = 3
};

#ifndef max
	#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

// Copied from: xnu/osfmk/cpuid.c
#ifndef min
	#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#define	round2(x, m)	(((x) + (m / 2)) & ~(m - 1))
#define roundup2(x, m)  (((x) + m - 1) & ~(m - 1))

#define MAKEKERNDEV(t, u, p)  MAKEBOOTDEV(t, 0, 0, u, p)


enum
{
	kCursorTypeHidden    = 0x0100,
	kCursorTypeUnderline = 0x0607
};

#endif /* !__LIBSAIO_SAIO_TYPES_H */
