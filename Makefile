#
# File: RevoBoot/Makefile
#
# Updates:
#
#			- Major cleanup (Pike R. Alpha, October 2012).
#			- Output improvements (Pike R. Alpha, October 2012).
#			- Default build target is now Mountain Lion (Pike R. Alpha, October 2012).
#			- PRODUCT_MODEL_TARGET for target build model added (Pike R. Alpha, October 2012).
#			- Creates RevoBoot/config/SETTINGS when missing (Pike R. Alpha, October 2012).
#			- Copies settings-template.h to SETTINGS/ModelnameNN.h when missing (Pike R. Alpha, October 2012).
#			- Automatic ACPI/EFI/SMBIOS data selection (Pike R. Alpha, October 2012).
#			- Copies ACPI/EFI/SMBIOS/data-template.h for new conigurations (Pike R. Alpha, October 2012).
#			- Output added for cp/mkdir/rm actions (Pike R. Alpha, November 2012).
#			- New build target 'help' added (Pike R. Alpha, November 2012).
#			- Cleanups and output changed (Pike R. Alpha, November 2012).
#			- Yosemite support added (Pike R. Alpha, June 2014).
#			- Changed default from Mavericks to Yosemite (Pike R. Alpha, June 2014).
#			- El Capitan support added (Pike R. Alpha, June 2015).
#			- Sierra support added (Pike R. Alpha, June 2016).
#			- macOS 10.13 support added (Pike R. Alpha, March 2017).
#

#
# Include Apple makefile definitions.
#

export USE_APPLE_PB_SUPPORT = all

LIBDIR = libsa
INC = -I. -I$(LIBDIR)

PAX = /bin/pax

OBJROOT = `pwd`/obj
SYMROOT = `pwd`/sym

DEFAULT_MODEL=$(shell cat MODEL)

#
# Export version number (picked up by i386/libsaio/Makefile)
#

export PRODUCT_VERSION_NUMBER = `cat ../../VERSION`

EXCLUDE = --exclude=.DS_Store --exclude=sym --exclude=obj --exclude=*.sh

#
# Search paths.
#

VPATH = $(OBJROOT):$(SYMROOT)

OS_TYPE = "OS\ X"

#
# Check if OS build target is specified (example: make mountain-lion).
#

ifeq ($(MAKECMDGOALS),)
	#
	# No OS build target given. Build for CodeName (default).
	#
	MAKEGOAL = codename
	MAKE_TARGET_OS = 254;
	MAKE_TARGET_OS_VER = 10.13
        OS_TYPE = "macOS"
else
	#
	# Setting MAKE_TARGET_OS and MAKEGOAL based on OS build target.
	#
	ifeq ($(MAKECMDGOALS), codename)
		MAKEGOAL = codename
		MAKE_TARGET_OS = 254;
		MAKE_TARGET_OS_VER = 10.13
                OS_TYPE = "macOS"
	else ifeq ($(MAKECMDGOALS), sierra)
		MAKEGOAL = sierra
		MAKE_TARGET_OS = 126;
		MAKE_TARGET_OS_VER = 10.12
                OS_TYPE = "macOS"
	else ifeq ($(MAKECMDGOALS), el-capitan)
		MAKEGOAL = el-capitan
		MAKE_TARGET_OS = 62;
		MAKE_TARGET_OS_VER = 10.11
	else ifeq ($(MAKECMDGOALS), yosemite)
		MAKEGOAL = yosemite
		MAKE_TARGET_OS = 26;
		MAKE_TARGET_OS_VER = 10.10
	else ifeq ($(MAKECMDGOALS), mavericks)
		MAKEGOAL = mavericks
		MAKE_TARGET_OS = 10;
		MAKE_TARGET_OS_VER = 10.9
	else ifeq ($(MAKECMDGOALS), mountain-lion)
		MAKEGOAL = mountain-lion
		MAKE_TARGET_OS = 6;
		MAKE_TARGET_OS_VER = 10.8
	else ifeq ($(MAKECMDGOALS), lion)
		MAKEGOAL = lion
		MAKE_TARGET_OS = 2;
		MAKE_TARGET_OS_VER = 10.7
	else ifeq ($(MAKECMDGOALS), legacy)
		MAKEGOAL = legacy
		MAKE_TARGET_OS = 1;
		MAKE_TARGET_OS_VER = 10.6
	endif
endif

#
# Export our make goal i.e. Sierra, El Capitan, Yosemite, Mavericks, Mountain Lion, Lion or legacy (Snow Leopard or Leopard).
#

export MAKEGOAL

#
# Export OS build target (picked up by: i386/libsaio/Makefile).
#

export PRODUCT_OS_TARGET = `echo $(MAKE_TARGET_OS)`

#
# Export target OS version (picked up by: i386/libsaio/Makefile) for platform.c
#

export PRODUCT_OS_TARGET_VERSION = `echo \"$(MAKE_TARGET_OS_VER)\"`

#
# Check if a target model was specified (example: make MODEL=MacPro61).
#

ifdef MODEL
	#
	# MODEL=[MacModelNN] specified, export target model.
	#
	ifneq ($(MODEL),)
		export MAKE_TARGET_MODEL = $(MODEL)
		#
		# Include static ACPI/EFI/SMBIOS data file per model identifier.
		#
		DATA_FILE = $(MODEL)
	else
		#
		# No. Use Macmini62 as a fallback default.
		#
		MODEL = Macmini62
		export MAKE_TARGET_MODEL = Macmini62
		#
		# Include default/empty static data files (no model identifier specified).
		#
		DATA_FILE = data-template
	endif
else
	#
	# MODEL=[MacModelNN], check if DEFAULT_MODEL was set (first run only).
	#
	ifdef DEFAULT_MODEL
		#
		# Yes it is. Use Macmodel[nn] from RevoBoot/MODEL
		#
		MODEL = $(DEFAULT_MODEL)
		export MAKE_TARGET_MODEL = $(MODEL)
		#
		# Include static ACPI/EFI/SMBIOS data files per model identifier.
		#
		DATA_FILE = $(MODEL)
	else
		#
		# No. Use Macmini62 as a fallback default.
		#
		MODEL = Macmini62
		export MAKE_TARGET_MODEL = $(MODEL)
		#
		# Include default/empty static data file (no model identifier specified).
		#
		DATA_FILE = data-template
	endif
endif

#
# Export target filenames for static ACPI, EFI and SMBIOS data.
# 

export MAKE_ACPI_DATA_FILE = ACPI/$(DATA_FILE).h
export MAKE_EFI_DATA_FILE = EFI/$(DATA_FILE).h
export MAKE_SMBIOS_DATA_FILE = SMBIOS/$(DATA_FILE).h

#
# Our one and only build target directory.
#

ARCH_DIR=i386

CONFIG_DIR=$(ARCH_DIR)/config

SETTINGS_DIR=$(CONFIG_DIR)/SETTINGS
SETTINGS_FILE=$(SETTINGS_DIR)/$(MAKE_TARGET_MODEL).h

$(MAKEGOAL):
#
# autoclean
#
	@if [ -d "$(OBJROOT)" ]; then \
		echo "\t[RMDIR] $(OBJROOT)" > /dev/null; \
	fi;

	@if [ -d "$(SYMROOT)" ]; then \
		echo "\t[RMDIR] $(SYMROOT)" > /dev/null; \
	fi;

	@rm -rf sym obj dst out.log 
#
# normal make goal
#
	@printf "\nCompiling RevoBoot, setup for a $(MODEL) running $(OS_TYPE) $(MAKE_TARGET_OS_VER) ($@)\n" >&2;

	@if [ ! -f $(CONFIG_DIR)/$(MAKE_ACPI_DATA_FILE) ]; then \
		echo "\t[CP] $(CONFIG_DIR)/ACPI/data-template.h $(CONFIG_DIR)/$(MAKE_ACPI_DATA_FILE)"; \
		cp -n $(CONFIG_DIR)/ACPI/data-template.h $(CONFIG_DIR)/$(MAKE_ACPI_DATA_FILE); \
	fi;

	@if [ ! -f $(CONFIG_DIR)/$(MAKE_EFI_DATA_FILE) ]; then \
		echo "\t[CP] $(CONFIG_DIR)/EFI/data-template.h $(CONFIG_DIR)/$(MAKE_EFI_DATA_FILE)"; \
		cp -n $(CONFIG_DIR)/EFI/data-template.h $(CONFIG_DIR)/$(MAKE_EFI_DATA_FILE); \
	fi;

	@if [ ! -f $(CONFIG_DIR)/$(MAKE_SMBIOS_DATA_FILE) ]; then \
		echo "\t[CP] $(CONFIG_DIR)/SMBIOS/data-template.h $(CONFIG_DIR)/$(MAKE_SMBIOS_DATA_FILE)"; \
		cp -n $(CONFIG_DIR)/SMBIOS/data-template.h $(CONFIG_DIR)/$(MAKE_SMBIOS_DATA_FILE); \
	fi;

	@if [ ! -d $(SETTINGS_DIR) ]; then \
		echo "\t[MKDIR] $(SETTINGS_DIR)"; \
		/bin/mkdir -p $(SETTINGS_DIR); \
	fi;

	@if [ ! -f $(SETTINGS_FILE) ]; then \
		echo "\t[CP] $(CONFIG_DIR)/settings-template.h $(SETTINGS_FILE)"; \
		cp -n $(CONFIG_DIR)/settings-template.h $(SETTINGS_FILE); \
	fi;

	@echo "======================================================";
	@echo "Running: make MODEL=$(MODEL) $@";

	@(OBJROOT=$(OBJROOT)/$(ARCH_DIR); \
	SYMROOT=$(SYMROOT)/$(ARCH_DIR); \
	XCFLAGS="$(RC_CFLAGS)"; \
	cd $(ARCH_DIR); \
	${MAKE}	"OBJROOT=$$OBJROOT" "SYMROOT=$$SYMROOT" "RC_ARCHS=$(ARCH_DIR)" \
	"TARGET=$(ARCH_DIR)" "RC_CFLAGS=$$XCFLAGS" $@ )

clean:
	@if [ -d "$(OBJROOT)" ]; then \
		echo "\t[RMDIR] $(OBJROOT)" > /dev/null; \
	fi;

	@if [ -d "$(SYMROOT)" ]; then \
		echo "\t[RMDIR] $(SYMROOT)" > /dev/null; \
	fi;

	@rm -rf sym obj dst out.log

help:
	@echo
	@echo	'Build targets:'
	@echo	'		- Builds all targets [DEFAULT]'
	@echo
	@echo	'Cleaning targets:'
	@echo	' clean	- Removes generated files'

$(SYMROOT) $(OBJROOT):
	@/bin/mkdir -p $@
