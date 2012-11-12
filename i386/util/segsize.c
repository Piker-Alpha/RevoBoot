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
 *			- Reformated and cleanups (PikerAlpha, November 2012)
  *			- Single pass runs for all target segment names (PikerAlpha, November 2012)
 *
 *
 * Note:	RevoBoot/i386/boot2/Makefile calls this tool to calculate segment sizes, example:
 *			-segaddr __INIT 20200 -segaddr __TEXT 20480 -segaddr __DATA 2C6E0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mach/mach.h>
#include <mach/mach_error.h>
#include <sys/file.h>
#include <mach-o/loader.h>
#include <libkern/OSByteOrder.h>
#include <unistd.h>

int infile;

struct mach_header	mh;

void * cmds;

static bool	swap_ends;

//==========================================================================

static unsigned long swap(unsigned long x)
{
	if (swap_ends)
	{
		return OSSwapInt32(x);
	}
	else
	{
		return x;
	}
}

//==========================================================================

int main(int argc, char *argv[])
{
	int nc, ncmds;
	char *cp;
	long boot2Address = 0x20200L;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./segsize [__INIT/__TEXT/__DATA]\n");
		exit(1);
	}
	else if (strcmp(argv[1], "__INIT") == 0)
	{
		printf("%lX\n", boot2Address);
		exit(0);
	}

	infile = open("../../sym/i386/boot.sys", O_RDONLY);

	if (infile < 0)
	{
		fprintf(stderr, "Error: boot.sys Not Found\n");
		exit(1);
	}

	nc = read(infile, &mh, sizeof (mh));

	if (nc < 0)
	{
		perror("read mach header");
		exit(1);
	}

	if (nc < (int)sizeof (mh))
	{
		fprintf(stderr, "read mach header: premature EOF %d\n", nc);
		exit(1);
	}

	if (mh.magic == MH_MAGIC)
	{
		swap_ends = false;
	}
	else if (mh.magic == MH_CIGAM)
	{
		swap_ends = true;
	}
	else
	{
		fprintf(stderr, "bad magic number %lx\n", (unsigned long)mh.magic);
		exit(1);
	}
	
	cmds = calloc(swap(mh.sizeofcmds), sizeof (char));

	if (cmds == 0)
	{
		fprintf(stderr, "alloc load commands: no memory\n");
		exit(1);
	}

	nc = read(infile, cmds, swap(mh.sizeofcmds));

	if (nc < 0)
	{
		perror("read load commands");
		exit(1);
	}

	if (nc < (int)swap(mh.sizeofcmds))
	{
		fprintf(stderr, "read load commands: premature EOF %d\n", nc);
		exit(1);
	}

	long text = 0L;

	#define lcp	((struct load_command *)cp)
	#define scp	((struct segment_command *)cp)

	for (ncmds = swap(mh.ncmds), cp = cmds; ncmds > 0; ncmds--)
	{
		switch(swap(lcp->cmd))
		{
			case LC_SEGMENT:
				if (strcmp(scp->segname, "__TEXT") == 0)
				{
					text = swap(scp->vmsize);
				}
				else if (strcmp(scp->segname, "__INIT") == 0)
				{
					if (strcmp(argv[1], "__TEXT") == 0)
					{
						printf("%lX\n", boot2Address + swap(scp->vmsize));
					}
					else // __DATA
					{
						printf("%lX\n", boot2Address + swap(scp->vmsize) + text);
					}
				}

				break;
		}

		cp += swap(lcp->cmdsize);
	}
	
	exit(0);
}
