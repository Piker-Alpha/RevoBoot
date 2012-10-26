#
# File: RevoBoot/i386/boot2/Makefile
#
# Updates:
#
#			- Support for self compiled libcc_kext.a added (PikerAlpha, October 2012).
#			- Major cleanup (PikerAlpha, October 2012).
#


include ../MakePaths.dir

OPTIM = -Os -Oz
CFLAGS	= $(RC_CFLAGS) $(OPTIM) $(MORECPP) -arch i386 -g -Wmost -Werror \
	-fno-builtin -DSAIO_INTERNAL_USER -static $(OMIT_FRAME_POINTER_CFLAG) \
	-DMAKE_TARGET_OS=$(PRODUCT_OS_TARGET) \
    -DSETTINGS_FILE=SETTINGS/$(MAKE_TARGET_MODEL).h \
	-mpreferred-stack-boundary=2 -fno-align-functions -fno-stack-protector \
	-march=pentium4 -msse2 -mfpmath=sse -msoft-float

LIBSADIR = ../libsa
LIBSAIODIR = ../libsaio
UTILDIR = ../util

INC = -I. -I.. -I$(SYMROOT) -I$(LIBSADIR) -I$(LIBSAIODIR) -I$(UTILDIR)

LIBS = -L$(SYMROOT) -lsaio -lsa
LIBDEP = $(SYMROOT)/libsaio.a $(SYMROOT)/libsa.a

#
# build_gcc no longer builds libgcc.a and libcc_kext.a with 'all' target  
# and thus we have to provide it, or people will have to build gcc.
#

LIBCC= $(UTILDIR)/libcc_kext.a

#
# Check ../util/ for a self compiled copy of libcc_kext.a
#

ifeq ($(wildcard $(LIBCC)),)
  #
  # Not found: Use Xcode supplied file.
  #
  LIBCC= `find /usr/llvm-gcc-*/lib/gcc/*/*/ -name \libcc_kext.a`
endif

VPATH = $(OBJROOT):$(SYMROOT)

#
# The order of object filenames below is important;
#	

OBJS = boot2.o boot.o bootlogo.o graphics.o drivers.o options.o lzss.o

DIRS_NEEDED = $(OBJROOT) $(SYMROOT)
BOOT2ADDR = 20200

#
# Set maximum size of the booter to 128KB (should be more than sufficient).
#
MAXBOOTSIZE = 131072

$(MAKEGOAL): $(DIRS_NEEDED) boot

boot: machOconv $(OBJS) $(LIBDEP)
	$(UTILDIR)/ld_classic -static -preload -segaddr __INIT $(BOOT2ADDR) \
	    -arch i386 -segalign 20 \
		-o $(SYMROOT)/boot.sys $(filter %.o,$^) $(LIBS) $(LIBCC)
	machOconv $(SYMROOT)/boot.sys $(SYMROOT)/boot
	size $(SYMROOT)/boot.sys
	ls -l $(SYMROOT)/boot
	@( size=`ls -l $(SYMROOT)/boot | awk '{ print $$5}'` ; \
	  if expr "$$size" ">" "$(MAXBOOTSIZE)" > /dev/null ; \
	  then \
	    echo "Error: Booter executable larger than $(MAXBOOTSIZE) bytes" ; \
	    rm $(SYMROOT)/boot ; \
	    exit 1 ; \
	  fi)

include ../MakeInc.dir
