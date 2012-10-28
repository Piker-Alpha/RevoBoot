#
# File: RevoBoot/i386/libsaio/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#			- DMAKE_TARGET_MODEL added (PikerAlpha, October 2012).
#			- Static data selectors added (PikerAlpha, October 2012).
#


include ../MakePaths.dir

UTILDIR = ../util
LIBSADIR = ../libsa

OPTIM = -Os -Oz
DEBUG = -DNOTHING

CFLAGS	= $(RC_CFLAGS) $(OPTIM) $(MORECPP) -arch i386 -g -Wmost \
    -D__ARCHITECTURE__=\"i386\" -DSAIO_INTERNAL_USER \
    -DRCZ_COMPRESSED_FILE_SUPPORT $(DEBUG) \
    -DREVOBOOT_VERSION_INFO=\"RevoBoot\ v$(PRODUCT_VERSION_NUMBER)\" \
    -DMAKE_TARGET_OS=$(PRODUCT_OS_TARGET) \
    -DSETTINGS_FILE=SETTINGS/$(MAKE_TARGET_MODEL).h \
    -DACPI_DATA_FILE=../../config/$(MAKE_ACPI_DATA_FILE) \
    -DEFI_DATA_FILE=../config/$(MAKE_EFI_DATA_FILE) \
    -DSMBIOS_DATA_FILE=../../config/$(MAKE_SMBIOS_DATA_FILE) \
    -fno-builtin -static $(OMIT_FRAME_POINTER_CFLAG) \
    -mpreferred-stack-boundary=2 -fno-align-functions -fno-stack-protector \
    -march=pentium4 -msse2 -mfpmath=sse -msoft-float

INC = -I. -I$(SYMROOT) -I$(UTILDIR) -I$(LIBSADIR)

VPATH = $(OBJROOT):$(SYMROOT)

SAIO_OBJS = table.o asm.o bios.o biosfn.o \
	disk.o sys.o cache.o bootstruct.o \
	stringTable.o load.o pci.o allocate.o \
	vbe.o hfs.o hfs_compare.o \
	xml.o md5c.o device_tree.o \
	cpu.o platform.o acpi.o \
	smbios.o efi.o

SAIO_EXTERN_OBJS = console.o

LIBS = libsaio.a
DIRS_NEEDED = $(OBJROOT) $(SYMROOT)

$(MAKEGOAL): $(DIRS_NEEDED) libsaio.h $(LIBS)

libsaio.a: $(SAIO_EXTERN_OBJS) $(SAIO_OBJS)
	rm -f $(SYMROOT)/$(@F)
	ar q $(SYMROOT)/$(@F) $^
	ranlib $(SYMROOT)/$(@F)

include ../MakeInc.dir
