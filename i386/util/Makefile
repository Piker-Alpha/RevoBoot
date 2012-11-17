#
#File: RevoBoot/i386/util/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#			- Fixed clang compilation (dgsga, November 2012. Credits to Evan Lojewski for original work).
#			- Output improved (PikerAlpha, October 2012).
#			- Now using my bash script instead of segsize.c (PikerAlpha, November 2012).
#

include ../MakePaths.dir

VPATH = $(OBJROOT):$(SYMROOT)

OPTIM = -Os -Oz
CFLAGS = $(RC_CFLAGS) $(OPTIM) -Wmost -Werror -g

LDFLAGS =
DEFINES=

PROGRAMS = machOconv
OBJS = machOconv.o

DIRS_NEEDED = $(OBJROOT) $(SYMROOT)

$(MAKEGOAL): $(DIRS_NEEDED) $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	@echo "\t[CC] $(@F)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DEFINES) -o $(SYMROOT)/$(@F) $(OBJROOT)/$(@F).o

include ../MakeInc.dir
