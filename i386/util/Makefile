#
#File: RevoBoot/i386/util/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#


include ../MakePaths.dir

VPATH = $(OBJROOT):$(SYMROOT)

OPTIM = -Os -Oz
CFLAGS = $(RC_CFLAGS) $(OPTIM) -Wmost -Werror -g

LDFLAGS =
DEFINES=

PROGRAMS = md machOconv

DIRS_NEEDED = $(OBJROOT) $(SYMROOT) $(LANGDIR)

$(MAKEGOAL): $(DIRS_NEEDED) $(PROGRAMS)

machOconv: machOconv.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEFINES) -o $(SYMROOT)/$(@F) machOconv.o
md:
	$(CC) -mdynamic-no-pic -Wall -dead_strip -arch i386 -mmacosx-version-min=10.5 md.c -o $(SYMROOT)/md

include ../MakeInc.dir
