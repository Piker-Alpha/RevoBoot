#
# File: RevoBoot/i386/libsa/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#


include ../MakePaths.dir

UTILDIR = ../util
LIBSAIODIR = ../libsaio

OPTIM = -Os -Oz
CFLAGS	= $(RC_CFLAGS) $(OPTIM) $(MORECPP) -arch i386 -g -Wmost -Werror \
		-fno-builtin -static $(OMIT_FRAME_POINTER_CFLAG) \
		-DSETTINGS_FILE=SETTINGS/$(MAKE_TARGET_MODEL).h \
		-mpreferred-stack-boundary=2 -fno-align-functions -fno-stack-protector \
		-march=pentium4 -msse2 -mfpmath=sse -msoft-float

INC = -I. -I$(SYMROOT) -I$(UTILDIR) -I$(LIBSAIODIR)

VPATH = $(OBJROOT):$(SYMROOT)

SA_OBJS = prf.o printf.o zalloc.o string.o strtol.o setjmp.o efi_tables.o

LIBS = libsa.a
DIRS_NEEDED = $(OBJROOT) $(SYMROOT)

$(MAKEGOAL): $(DIRS_NEEDED) $(LIBS)

libsa.a: $(SA_OBJS)
	rm -f $(SYMROOT)/$(@F)
	ar q $(SYMROOT)/$(@F) $^
	ranlib $(SYMROOT)/$(@F)

include ../MakeInc.dir
