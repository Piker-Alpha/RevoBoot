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
 * Updates:
 *
 *  		- loadBinaryData(load.c) and toLowerCase(string.c) added (PikerAlpha, October 2012).
 *			- Tidied up (spaces -> tabs) (PikerAlpha, October 2012).
 *
 */

#ifndef __LIBSAIO_SAIO_INTERNAL_H
#define __LIBSAIO_SAIO_INTERNAL_H

#include "saio_types.h"
#include "efi/essentials.h"


/* asm.s */
extern void		real_to_prot(void);
extern void		prot_to_real(void);
extern void		halt(void);
extern void		startMachKernel(unsigned int address, void *arg);


/* bios.s */
extern void		bios(biosBuf_t *bb);


extern int		bgetc(void);
extern int		biosread(int dev, int cyl, int head, int sec, int num);
extern int		ebiosread(int dev, unsigned long long sec, int count);
extern int		get_drive_info(int drive, struct driveInfo *dp);
extern void		putc(int ch);
extern void		putca(int ch, int attr, int repeat);
extern int		getc(void);
extern int		readKeyboardStatus(void);
extern unsigned int	time18(void);

extern void		delay(int ms);
extern unsigned int	get_diskinfo(int dev);

extern int		memsize(int i);
extern void		video_mode(int mode);
extern void		setCursorPosition(int x, int y, int page);
extern void		setCursorType(int type);
extern void		getCursorPositionAndType(int *x, int *y, int *type);
extern void		scollPage(int x1, int y1, int x2, int y2, int attr, int rows, int dir);
extern void		clearScreenRows(int y1, int y2);
extern void		setActiveDisplayPage(int page);
extern unsigned long getMemoryMap(struct MemoryRange * rangeArray, unsigned long maxRangeCount, unsigned long * conMemSizePtr, unsigned long * extMemSizePtr);
extern unsigned long getExtendedMemorySize();
extern unsigned long getConventionalMemorySize();
extern void		sleep(int n);

/* efi.c */
extern void		initEFITree(void);
extern void		updateEFITree(char *rootUUID);
extern void		finalizeEFITree(uint32_t kernelAdler32);

/* bootstruct.c */
extern void		initKernelBootConfig(void);
extern void		finalizeKernelBootConfig(void);
extern void		moveKernelBootArgs(void);

/* cache.c */
extern void		CacheReset();
extern void		CacheInit(CICell ih, long blockSize);
extern long		CacheRead(CICell ih, char *buffer, long long offset, long length, long cache);

/* console.c */
extern bool		gVerboseMode;
extern bool		gErrors;
extern void		putchar(int ch);
extern int		getchar(void);
extern int		printf(const char *format, ...);
extern int		error(const char *format, ...);
extern int		verbose(const char *format, ...);
extern void		stop(const char *format, ...);


/* disk.c */
extern int		testBiosread(int biosdev, unsigned long long secno);
extern BVRef	diskScanBootVolumes(int biosdev, int *count);
extern BVRef	diskScanGPTBootVolumes(int biosdev, int *count);
extern void		diskSeek(BVRef bvr, long long position);
extern int		diskRead(BVRef bvr, long addr, long length);
extern bool		hasBootEFI(BVRef bvr);
extern void		initPartitionChain(void);

extern BVRef	getBVChainForBIOSDev(int biosdev);
extern BVRef	newFilteredBVChain(int minBIOSDev, int maxBIOSDev, unsigned int allowFlags, unsigned int denyFlags, int *count);
extern int		freeFilteredBVChain(const BVRef chain);
extern int		rawDiskRead(BVRef bvr, unsigned int secno, void *buffer, unsigned int len);
extern int		rawDiskWrite(BVRef bvr, unsigned int secno, void *buffer, unsigned int len);
extern int		readBootSector(int biosdev, unsigned int secno, void *buffer);
extern void		turnOffFloppy(void);
extern int		testFAT32EFIBootSector(int biosdev, unsigned int secno, void * buffer);


/* guid.c */
extern			void convertEFIGUIDToString(EFI_GUID const *aGuid, char **aUUIDString);
extern			bool isEFIGUIDNull(EFI_GUID const *aGuid);
extern			int compareEFIGUID(EFI_GUID const *pG1, EFI_GUID const *pG2);

#if USE_DEVICE_PATH
void *getUUIDFromDevicePath(EFI_DEVICE_PATH_PROTOCOL *devicePath);
#else
void *getUUIDFromDevicePath(EFI_GUID *aGUID);
#endif

extern			char * getStartupDiskUUID(char * aDataPtr);


/* hfs_compare.c */
extern int32_t	FastUnicodeCompare(u_int16_t *uniStr1, u_int32_t len1, u_int16_t *uniStr2, u_int32_t len2);
extern void		utf_encodestr(const u_int16_t * ucsp, int ucslen, u_int8_t * utf8p, u_int32_t bufsize);
extern void		utf_decodestr(const u_int8_t *utf8p, u_int16_t *ucsp, u_int16_t *ucslen, u_int32_t bufsize);


/* load.c */
extern bool		gLoadKernelDrivers;
extern long		ThinFatFile(void **binary, unsigned long *length);
extern long		DecodeMachO(void *binary, entry_t *rentry, char **raddr, int *rsize);
extern long		loadBinaryData(char *aFilePath, void **aMemoryAddress);


/* memory.c */
long			AllocateKernelMemory(long inSize);
long			AllocateMemoryRange(char * rangeName, long start, long length, long type);


/* platform.c */
extern void		enableA20(void);


/* stringTable.c */
extern int		base64Decode(char *input, unsigned char **decodedData);

extern bool		getValueForConfigTableKey(config_file_t *config, const char *key, const char **val, int *size);
extern char		* newStringForKey(char *key, config_file_t *configBuff);
extern bool		getValueForBootKey(const char *line, const char *match, const char **matchval, int *len);
extern bool		getValueForKey(const char *key, const char **val, int *size, config_file_t *configBuff);
extern bool		getBoolForKey(const char *key, bool *val, config_file_t *configBuff);
extern bool		getIntForKey(const char *key, int *val, config_file_t *configBuff);
extern bool		loadConfigFile(const char *configFile, config_file_t *configBuff);
extern int		loadSystemConfig(config_file_t *configBuff);
extern char		* getNextArg(char ** ptr, char * val);
extern long		ParseXMLFile(char * buffer, TagPtr * dict);


/* sys.c */
extern BVRef	getBootVolumeRef(const char * path, const char ** outPath);
extern long		LoadVolumeFile(BVRef bvr, const char *fileSpec);
extern long		LoadFile(const char *fileSpec);
extern long		ReadFileAtOffset(const char * fileSpec, void *buffer, uint64_t offset, uint64_t length);
extern long		LoadThinFatFile(const char *fileSpec, void **binary);
extern long		GetDirEntry(const char *dirSpec, long *dirIndex, const char **name, long *flags, long *time);
extern long		GetFileInfo(const char *dirSpec, const char *name,long *flags, long *time);
extern long		GetFileBlock(const char *fileSpec, unsigned long long *firstBlock);
extern long		GetFSUUID(char *spec, char *uuidStr);
extern long		CreateUUIDString(uint8_t uubytes[], int nbytes, char *uuidStr);
extern int		openmem(char *buf, int len);
extern int		open(const char *str, int flags);
extern int		close(int fdesc);
extern int		file_size(int fdesc);
extern int		read(int fdesc, char *buf, int count);
extern int		b_lseek(int fdesc, int addr, int ptr);
extern int		tell(int fdesc);
extern const char * systemConfigDir(void);
extern struct	dirstuff * opendir(const char *path);
extern struct	dirstuff * vol_opendir(BVRef bvr, const char *path);
extern int		closedir(struct dirstuff *dirp);
extern int		readdir(struct dirstuff *dirp, const char **name, long *flags, long *time);
extern int		readdir_ext(struct dirstuff * dirp, const char ** name, long * flags, long * time, FinderInfo *finderInfo, long *infoValid);
extern void		flushdev(void);
extern void		scanBootVolumes(int biosdev, int *count);

extern BVRef	getBootVolume(BVRef chain, int targetDevice);
extern BVRef	getTargetRootVolume(char *rootUUID);
extern BVRef	selectBootVolume(BVRef chain);

extern void		getBootVolumeDescription(BVRef bvr, char *str, long strMaxLen, bool verbose);


// Function pointer to be filled in if ramdisks are available
extern int		(*p_get_ramdisk_info)(int biosdev, struct driveInfo *dip);
extern int		(*p_ramdiskReadBytes)(int biosdev, unsigned int blkno, unsigned int byteoff, unsigned int byteCount, void * buffer);


/* string.h */
extern char		* toLowerCase(char *aSourceString);

#endif /* !__LIBSAIO_SAIO_INTERNAL_H */
