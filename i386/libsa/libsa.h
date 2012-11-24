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
 *			- Use size_t instead of int when required (PikerAlpha, November 2012)
 *
 */

#ifndef __BOOT_LIBSA_H
#define __BOOT_LIBSA_H

/* Exported API for standalone library */

#include <mach-o/loader.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#include "../config/settings.h"


/*
 * boot.c
 */
extern int fastEnableA20(void);


/*
 * crc32.c
 */
uint32_t crc32(uint32_t crc, const void *buf, size_t size);


/*
 * getsegbyname.c
 */
extern struct segment_command * getsegbynamefromheader(struct mach_header * mhp, char * segname);


/*
 * prf.c
 */
extern void prf(const char * fmt, va_list ap, void (*putfn_p)(), void * putfn_arg);


/*
 * printf.c
 */
extern int sprintf(char *s, const char * format, ...);
extern int slvprintf(char * buffer, int len, const char * fmt, va_list arg);


/*
 * string.c
 */
#ifndef bcopy
	extern void   bcopy(const void * src, void * dst, size_t len);
#endif

#ifndef bzero
	extern void   bzero(void * dst, size_t len);
#endif

extern char * strcpy(char * s1, const char * s2);
extern char * strncpy(char * s1, const char * s2, size_t n);

extern char * strstr(const char *in, const char *str);
extern char * strcat(char * s1, const char * s2);
extern char * strncat(char * s1, const char * s2, size_t n);
extern char * strdup(const char *s1);

extern void * memset(void * dst, int c, size_t n);
extern void * memcpy(void * dst, const void * src, size_t len);

extern int		strcmp(const char * s1, const char * s2);
extern int		strncmp(const char * s1, const char * s2, size_t n);
extern int		atoi(const char * str);
extern int		ptol(const char * str);

extern int	memcmp(const void * p1, const void * p2, size_t len);

extern size_t	strlcpy(char * s1, const char * s2, size_t n);
extern size_t	strlen(const char * str);

#if STRNCASECMP
	extern int    strncasecmp(const char * s1, const char * s2, size_t n);
#endif

extern uint8_t checksum8( void * start, unsigned int length);
char * removeChar(char *aSourceString, char aTargetChar);


/*
 * strtol.c
 */
extern long strtol(const char * nptr, char ** endptr, int base);
extern unsigned long strtoul(const char * nptr, char ** endptr, int base);
extern unsigned long long strtouq(const char *nptr, char ** endptr, int base);


/*
 * zalloc.c
 */

#if SAFE_MALLOC
	#define malloc(size) safeMalloc(size, __FILE__, __LINE__)

	extern void   mallocInit(char * start, int size, int nodes, void (*malloc_error)(char *, size_t, const char *, int));
	extern void * safeMalloc(size_t size, const char *file, int line);
#else
	extern void   mallocInit(char * start, int size, int nodes, void (*malloc_error)(char *, size_t));
	extern void * malloc(size_t size);
#endif

extern void   free(void * start);
extern void * realloc(void * ptr, size_t size);

#endif /* !__BOOT_LIBSA_H */
