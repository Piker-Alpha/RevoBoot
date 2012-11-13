#
# File: RevoBoot/i386/boot2/Makefile
#
# Updates:
#
#		- Support for self compiled libcc_kext.a added (PikerAlpha, October 2012).
#		- Major cleanup (PikerAlpha, October 2012).
#		- Fixed clang compilation (dgsga, November 2012. Credits to Evan Lojewski for original work).
#		- BOOT2ADDR moved to RevoBoot/i386/util/segsize.c (PikerAlpha, November 2012).
#		- Simplified calls to RevoBoot/i386/util/segsize (PikerAlpha, November 2012).
#		- Reformatted output, include directory dependency lifted (PikerAlpha, November 2012).
#		- Single pass linking and elimination of -Wl,-segaddr (PikerAlpha, November 2012).
#


include ../MakePaths.dir

OPTIM = -Os -Oz
CFLAGS	= $(RC_CFLAGS) $(OPTIM) $(MORECPP) -arch i386 -g -Wmost -Werror \
	-fno-builtin -DSAIO_INTERNAL_USER -static $(OMIT_FRAME_POINTER_CFLAG) \
	-DMAKE_TARGET_OS=$(PRODUCT_OS_TARGET) \
    	-DSETTINGS_FILE=SETTINGS/$(MAKE_TARGET_MODEL).h \
	-fno-stack-protector \
	-march=pentium4 -msse2 -msoft-float

LIBSADIR = ../libsa
LIBSAIODIR = ../libsaio
UTILDIR = ../util

INC = -I. -I.. -I$(SYMROOT) -I$(LIBSADIR) -I$(LIBSAIODIR) -I$(UTILDIR)

LIBS = -L$(SYMROOT) -lsaio -lsa
LIBDEP = $(SYMROOT)/libsaio.a $(SYMROOT)/libsa.a

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

boot: $(OBJS)

	@echo "\t[LD] boot.sys"
	@$(CC)	-nostdlib -arch i386 \
		-Wl,-preload \
		-Wl,-pie \
		-Wl,-segalign,20 \
		-Wl,-read_only_relocs,suppress \
		-lcc_kext \
		$(filter %.o,$^) $(LIBS) -o ${SYMROOT}/$@.sys

	@echo "\t[MACHOCONV] boot"
	@$(SYMROOT)/machOconv $(SYMROOT)/boot.sys $(SYMROOT)/boot

	@echo "============================================"
	@size $(SYMROOT)/boot.sys

	@( size=`ls -l $(SYMROOT)/boot | awk '{ print $$5}'` ; \
	if expr "$$size" ">" "$(MAXBOOTSIZE)" > /dev/null ;\
	then \
		echo "Boot ($$size) larger than $(MAXBOOTSIZE) bytes" ;\
		rm $(SYMROOT)/boot ;\
		exit 1;\
	else \
		echo "=========== boot is $$size bytes ============"; \
	fi)

include ../MakeInc.dir
