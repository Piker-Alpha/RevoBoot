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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mach/mach.h>
#include <mach/mach_error.h>
#include <sys/file.h>
#include <mach-o/loader.h>
#include <libkern/OSByteOrder.h>
#include <unistd.h>

int	infile;

struct mach_header	mh;
void *		cmds;

static bool	swap_ends;

static unsigned long swap(
						  unsigned long x
						  )
{
    if (swap_ends)
		return OSSwapInt32(x);
    else
		return x;
}

int
main(int argc, char *argv[])
{
    int			nc, ncmds;
    char *		cp;
    
    if (argc == 3) {
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			goto usage;
    }
    else {
	usage:
    	fprintf(stderr, "usage: segsize segment\n");
		exit(1);
    }
    
    nc = read(infile, &mh, sizeof (mh));
    if (nc < 0) {
		perror("read mach header");
		exit(1);
    }
    if (nc < (int)sizeof (mh)) {
		fprintf(stderr, "read mach header: premature EOF %d\n", nc);
		exit(1);
    }
    if (mh.magic == MH_MAGIC)
		swap_ends = false;
    else if (mh.magic == MH_CIGAM)
		swap_ends = true;
    else {
    	fprintf(stderr, "bad magic number %lx\n", (unsigned long)mh.magic);
		exit(1);
    }
	
    cmds = calloc(swap(mh.sizeofcmds), sizeof (char));
    if (cmds == 0) {
		fprintf(stderr, "alloc load commands: no memory\n");
		exit(1);
    }
    nc = read(infile, cmds, swap(mh.sizeofcmds));
    if (nc < 0) {
		perror("read load commands");
		exit(1);
    }
    if (nc < (int)swap(mh.sizeofcmds)) {
		fprintf(stderr, "read load commands: premature EOF %d\n", nc);
		exit(1);
    }
	
    for (	ncmds = swap(mh.ncmds), cp = cmds;
		 ncmds > 0; ncmds--) {
//	    bool	isDATA;
//	    unsigned	vmsize;
		
#define lcp	((struct load_command *)cp)    
		switch(swap(lcp->cmd)) {
				
			case LC_SEGMENT:
#define scp	((struct segment_command *)cp)
				if(strcmp(scp->segname, argv[2]) == 0)
				{
					printf("%ld\n", swap(scp->vmsize));
#if 0
				if (isDATA)
					vmsize = swap(scp->filesize);
				else
					vmsize = swap(scp->vmsize);
#endif
				}
				break;
		}
		
		cp += swap(lcp->cmdsize);
    }
	
    exit(0);
}
