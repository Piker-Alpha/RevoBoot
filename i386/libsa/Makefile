#
# File: RevoBoot/i386/libsa/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#			- Output added for rm/ar/ranlib actions (PikerAlpha, November 2012).
#			- Enabled clang compilation (dgsga, November 2012. Credits to Evan Lojewski for original work).
#			- Output change and now using libtool instead of ar/ranlib (PikerAlpha, November 2012).
#

include ../MakePaths.dir

UTILDIR = ../util
LIBSAIODIR = ../libsaio

OPTIM = -Os -Oz
CFLAGS	= $(RC_CFLAGS) $(OPTIM) -arch i386 -g -Wmost -Werror \
		-fno-builtin -static $(OMIT_FRAME_POINTER_CFLAG) \
		-DSETTINGS_FILE=SETTINGS/$(MAKE_TARGET_MODEL).h \
		-fno-stack-protector \
		-march=pentium4 -msse2 -msoft-float

INC = -I. -I$(SYMROOT) -I$(UTILDIR) -I$(LIBSAIODIR)

VPATH = $(OBJROOT):$(SYMROOT)

SA_OBJS = prf.o printf.o zalloc.o string.o strtol.o setjmp.o efi_tables.o

LIBS = libsa.a

DIRS_NEEDED = $(OBJROOT) $(SYMROOT)

$(MAKEGOAL): $(DIRS_NEEDED) $(LIBS)

$(LIBS): $(SA_OBJS)
	@if [ -f $(SYMROOT)/$@ ]; then \
		echo "\t[RM] $@"; \
		rm -f $(SYMROOT)/$@; \
	fi;

	@echo "\t[LIBTOOL] $@"
	@libtool -o $(SYMROOT)/$@ $^

include ../MakeInc.dir
	@echo "\t[RM] $(SYMROOT)/$@"
	@rm -f $(SYMROOT)/$@
	@echo "\t[AR] $@"
	@ar q $(SYMROOT)/$@ $^ &> /dev/null
	@echo "\t[RANLIB] $@"
	@ranlib $(SYMROOT)/$@

include ../MakeInc.dir
