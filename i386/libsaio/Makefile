#
# File: RevoBoot/i386/libsaio/Makefile
#
# Updates:
#
#			- Major cleanup (Pike R. Alpha, October 2012).
#			- DMAKE_TARGET_MODEL added (Pike R. Alpha, October 2012).
#			- Static data selectors added (Pike R. Alpha, October 2012).
#			- STATIC_DATA_FILENAME added (Pike R> Alpha, October 2012).
#			- Output added for rm/ar/ranlib actions (Pike R> Alpha, November 2012).
#			- Enabled clang compilation (dgsga, PikerAlpha, November 2012. Credits to Evan Lojewski for original work).
#			- Output change and now using libtool instead of ar/ranlib (Pike R. Alpha, November 2012).
#			- SAIO_OBJS changed / base64.o added (Pike R. Alpha, November 2012).
#			- MAKE_TARGET_OS_VER added (Pike R. Alpha, June 2014).
#			- patcher.c added (Pike R. Alpha, August 2016).

include ../MakePaths.dir

UTILDIR = ../util
LIBSADIR = ../libsa

OPTIM = -Os -Oz
DEBUG = -DNOTHING

CFLAGS	= $(RC_CFLAGS) $(OPTIM) -arch i386 -g -Wmost \
		-D__ARCHITECTURE__=\"i386\" -DSAIO_INTERNAL_USER \
		-DRCZ_COMPRESSED_FILE_SUPPORT $(DEBUG) \
		-DREVOBOOT_VERSION_INFO=\"RevoBoot\ v$(PRODUCT_VERSION_NUMBER)\" \
		-DMAKE_TARGET_OS=$(PRODUCT_OS_TARGET) \
		-DMAKE_TARGET_OS_VER=$(PRODUCT_OS_TARGET_VERSION) \
		-DSETTINGS_FILE=SETTINGS/$(MAKE_TARGET_MODEL).h \
		-DSTATIC_DATA_FILENAME=$(MAKE_TARGET_MODEL).bin \
		-DACPI_DATA_FILE=../../config/$(MAKE_ACPI_DATA_FILE) \
		-DEFI_DATA_FILE=../config/$(MAKE_EFI_DATA_FILE) \
		-DSMBIOS_DATA_FILE=../config/$(MAKE_SMBIOS_DATA_FILE) \
		-fno-builtin -static $(OMIT_FRAME_POINTER_CFLAG) \
		-fno-stack-protector \
		-march=pentium4 -msse2 -msoft-float

INC = -I. -I$(SYMROOT) -I$(UTILDIR) -I$(LIBSADIR)

VPATH = $(OBJROOT):$(SYMROOT)

SAIO_OBJS =	table.o asm.o bios.o biosfn.o guid.o disk.o sys.o cache.o \
		bootstruct.o base64.o stringTable.o patcher.o load.o pci.o allocate.o \
		vbe.o hfs.o hfs_compare.o xml.o md5c.o device_tree.o cpu.o \
		platform.o acpi.o smbios.o efi.o console.o 

LIBS = libsaio.a

DIRS_NEEDED = $(OBJROOT) $(SYMROOT)

$(MAKEGOAL): $(DIRS_NEEDED) libsaio.h $(LIBS)

$(LIBS): $(SAIO_OBJS)
	@if [ -f $(SYMROOT)/$@ ]; then \
		echo "\t[RM] $@"; \
		rm -f $(SYMROOT)/$@; \
	fi;

	@echo "\t[LIBTOOL] $@"
	@libtool -o $(SYMROOT)/$@ $^

include ../MakeInc.dir
