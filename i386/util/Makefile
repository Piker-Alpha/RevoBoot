#
#File: RevoBoot/i386/util/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#			- Fixed clang compilation (dgsga, November 2012. Credits to Evan Lojewski for original work).
#


include ../MakePaths.dir

VPATH = $(OBJROOT):$(SYMROOT)

OPTIM = -Os -Oz
CFLAGS = $(RC_CFLAGS) $(OPTIM) -Wmost -Werror -g

LDFLAGS =
DEFINES=

PROGRAMS = machOconv segsize
OBJS = machOconv.o segsize.o

DIRS_NEEDED = $(OBJROOT) $(SYMROOT) $(LANGDIR)

$(MAKEGOAL): $(DIRS_NEEDED) $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	@echo "\t[CC] $(@F)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DEFINES) -o $(SYMROOT)/$(@F) $(OBJROOT)/$(@F).o

include ../MakeInc.dir
