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
 *
 * Sam's simple memory allocator.
 *
 */

#include "libsa.h"
#include "memory.h"

// #define SAFE_MALLOC		1

#define ZDEBUG			0

#if ZDEBUG
	int zout;
#endif

typedef struct {
	char * start;
	size_t size;
} zmem;

static zmem * zalloced;
static zmem * zavailable;
static short  availableNodes, allocedNodes, totalNodes;
static char * zalloc_base;
static char * zalloc_end;

#if SAFE_MALLOC
	static void		(*zerror)(char *, size_t, const char *, int);
#else
	static void		(*zerror)(char *, size_t);
#endif

static void   zallocate(char * start,int size);
static void   zinsert(zmem * zp, int ndx);
static void   zdelete(zmem * zp, int ndx);
static void   zcoalesce(void);

#if ZDEBUG
	size_t zalloced_size;
#endif

#define ZALLOC_NODES	32767 /* was 16384 */

#if SAFE_MALLOC
	static void mallocError(char *addr, size_t size, const char *file, int line)
#else
	static void mallocError(char *addr, size_t size)
#endif
{
#ifdef i386
    asm volatile ("hlt");
#endif
}

// define the block of memory that the allocator will use
#if SAFE_MALLOC
	void mallocInit(char * start, int size, int nodes, void (*malloc_err_fn)(char *, size_t, const char *, int))
#else
	void mallocInit(char * start, int size, int nodes, void (*malloc_err_fn)(char *, size_t))
#endif
{
	zalloc_base         = start ? start : (char *)ZALLOC_ADDR;
	totalNodes          = nodes ? nodes : ZALLOC_NODES;
	zalloced            = (zmem *) zalloc_base;
	zavailable          = (zmem *) zalloc_base + sizeof(zmem) * totalNodes;
	zavailable[0].start = (char *)zavailable + sizeof(zmem) * totalNodes;

	if (size == 0)
	{
		size = ZALLOC_LEN;
	}

	zavailable[0].size  = size - (zavailable[0].start - zalloc_base);
    zalloc_end          = zalloc_base + size;
	availableNodes      = 1;
	allocedNodes        = 0;
    zerror              = malloc_err_fn ? malloc_err_fn : mallocError;
}

#define BEST_FIT 1

#if SAFE_MALLOC
	void * safeMalloc(size_t size, const char *file, int line)
#else
	void * malloc(size_t size)
#endif
{
	int    i;
#if BEST_FIT
    int    bestFit;
    size_t smallestSize;
#endif
	char * ret = 0;

	if ( !zalloc_base )
	{
		// this used to follow the bss but some bios' corrupted it...
		mallocInit((char *)ZALLOC_ADDR, ZALLOC_LEN, ZALLOC_NODES, mallocError);
	}

	size = ((size + 0xf) & ~0xf);

    if (size == 0 && zerror)
#if SAFE_MALLOC
        (*zerror)((char *)0xdeadbeef, 0, file, line);
#else
        (*zerror)((char *)0xdeadbeef, 0);
#endif

#if BEST_FIT
    smallestSize = 0;
    bestFit = -1;
#endif
 
	for (i = 0; i < availableNodes; i++)
	{
		/*
		 * Find node with equal size, or if not found, then smallest node that fits.
		 */
		if (zavailable[i].size == size)
		{
			zallocate(ret = zavailable[i].start, size);
			zdelete(zavailable, i); availableNodes--;
			goto done;
		}
#if BEST_FIT
        else if ((zavailable[i].size > size) && ((smallestSize == 0) || (zavailable[i].size < smallestSize)))
        {
                bestFit = i;
                smallestSize = zavailable[i].size;
        }
#else
		else if (zavailable[i].size > size)
		{
			zallocate(ret = zavailable[i].start, size);
			zavailable[i].start += size;
			zavailable[i].size  -= size;
			goto done;
		}
#endif
    }
#if BEST_FIT
    if (bestFit != -1)
    {
        zallocate(ret = zavailable[bestFit].start, size);
        zavailable[bestFit].start += size;
        zavailable[bestFit].size  -= size;
    }
#endif

done:
	if ((ret == 0) || (ret + size >= zalloc_end))
    {
		if (zerror)
#if SAFE_MALLOC
            (*zerror)(ret, size, file, line);
#else
            (*zerror)(ret, size);
#endif
    }

	if (ret != 0)
		bzero(ret, size);

#if ZDEBUG
    zalloced_size += size;
#endif
	return (void *) ret;
}

void free(void * pointer)
{
    unsigned long rp;
	int i, found = 0;
    size_t tsize = 0;
	char * start = pointer;

#if i386    
    // Get return address of our caller,
    // in case we have to report an error below.
    asm volatile ("movl %%esp, %%eax\n\t"
                  "subl $4, %%eax\n\t"
                  "movl 0(%%eax), %%eax" : "=a" (rp));
#else
	rp = 0;
#endif

	if (!start)
	{
        return;
	}

	for (i = 0; i < allocedNodes; i++)
	{
		if (zalloced[i].start == start)
		{
			tsize = zalloced[i].size;
#if ZDEBUG
			zout -= tsize;
			printf("    zz out %d\n", zout);
#endif
			zdelete(zalloced, i); allocedNodes--;
			found = 1;
#if ZDEBUG
            memset(pointer, 0x5A, tsize);
#endif
			break;
		}
	}

	if (!found)
    {
        if (zerror)
#if SAFE_MALLOC
            (*zerror)(pointer, rp, "free", 0);
#else
            (*zerror)(pointer, rp);
#endif
        else
           return;
    }
#if ZDEBUG
        zalloced_size -= tsize;
#endif

	for (i = 0; i < availableNodes; i++)
	{
		if ((start + tsize) == zavailable[i].start)  // merge it in
		{
			zavailable[i].start = start;
			zavailable[i].size += tsize;
			zcoalesce();
			return;
		}

		if ((i > 0) && (zavailable[i-1].start + zavailable[i-1].size == start))
		{
			zavailable[i-1].size += tsize;
			zcoalesce();
			return;
		}

		if ((start + tsize) < zavailable[i].start)
		{
            if (++availableNodes > totalNodes)
            {
                if (zerror)
#if SAFE_MALLOC
                    (*zerror)((char *)0xf000f000, 0, "free", 0);
#else
                    (*zerror)((char *)0xf000f000, 0);
#endif
            }
			zinsert(zavailable, i); 
			zavailable[i].start = start;
			zavailable[i].size = tsize;
			return;
		}
	}

    if (++availableNodes > totalNodes)
    {
        if (zerror)
#if SAFE_MALLOC
            (*zerror)((char *)0xf000f000, 1, "free", 0);
#else
            (*zerror)((char *)0xf000f000, 1);
#endif
    }

	zavailable[i].start = start;
	zavailable[i].size  = tsize;
	zcoalesce();

	return;
}

static void zallocate(char * start,int size)
{

#if ZDEBUG
	zout += size;
	printf("    alloc %d, total 0x%x\n", size, zout);
#endif

	zalloced[allocedNodes].start = start;
	zalloced[allocedNodes].size  = size;

	if (++allocedNodes > totalNodes)
    {
        if (zerror)
#if SAFE_MALLOC
            (*zerror)((char *)0xf000f000, 2, "zallocate", 0);
#else
            (*zerror)((char *)0xf000f000, 2);
#endif
    };
}

static void zinsert(zmem * zp, int ndx)
{
	int i;
	zmem *z1, *z2;

	i  = totalNodes-2;
	z1 = zp + i;
	z2 = z1 + 1;

	for (; i >= ndx; i--, z1--, z2--)
	{
        *z2 = *z1;
	}
}

static void zdelete(zmem * zp, int ndx)
{
	int i;
	zmem *z1, *z2;

	z1 = zp + ndx;
	z2 = z1 + 1;

	for (i = ndx; i < totalNodes - 1; i++, z1++, z2++)
	{
        *z1 = *z2;
	}
}

static void zcoalesce(void)
{
	int i;

	for (i = 0; i < availableNodes-1; i++)
	{
		if ( zavailable[i].start + zavailable[i].size == zavailable[i + 1].start )
		{
			zavailable[i].size += zavailable[i + 1].size;
			zdelete(zavailable, i + 1); availableNodes--;
			return;
		}
	}	
}

/* This is the simplest way possible.  Should fix this. */
void * realloc(void * start, size_t newsize)
{
#if SAFE_MALLOC
    void * newstart = safeMalloc(newsize, __FILE__, __LINE__);
#else
    void * newstart = malloc(newsize);
#endif
    bcopy(start, newstart, newsize);
    free(start);
    return newstart;
}
