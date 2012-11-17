#
# File: RevoBoot/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#			- Output improvements (PikerAlpha, October 2012).
#			- Default build target is now Mountain Lion (PikerAlpha, October 2012).
#			- PRODUCT_MODEL_TARGET for target build model added (PikerAlpha, October 2012).
#			- Creates RevoBoot/config/SETTINGS when missing (PikerAlpha, October 2012).
#			- Copies settings-template.h to SETTINGS/ModelnameNN.h when missing (PikerAlpha, October 2012).
#			- Automatic ACPI/EFI/SMBIOS data selection (PikerAlpha, October 2012).
#			- Copies ACPI/EFI/SMBIOS/data-template.h for new conigurations (PikerAlpha, October 2012).
#			- Output added for cp/mkdir/rm actions (PikerAlpha, November 2012).
#			- New build target 'help' added (PikerAlpha, November 2012).
#			- Cleanups and output changed (PikerAlpha, November 2012).
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

#
# Export version number (picked up by i386/libsaio/Makefile)
#

export PRODUCT_VERSION_NUMBER = `cat ../../VERSION`

EXCLUDE = --exclude=.DS_Store --exclude=sym --exclude=obj --exclude=*.sh

#
# Search paths.
#

VPATH = $(OBJROOT):$(SYMROOT)

#
# Check if OS build target is specified (example: make mountain-lion).
#

ifeq ($(MAKECMDGOALS),)
	#
	# No OS build target given. Build for Mountain Lion (default).
	#
	MAKE_TARGET_OS = 6;
	MAKEGOAL = mountain-lion
else
	#
	# Setting MAKE_TARGET_OS and MAKEGOAL based on OS build target.
	#
	ifeq ($(MAKECMDGOALS), mountain-lion)
		MAKE_TARGET_OS = 6;
		MAKEGOAL = mountain-lion
	else
		ifeq ($(MAKECMDGOALS), lion)
			MAKE_TARGET_OS = 2;
			MAKEGOAL = lion
		else ifeq ($(MAKECMDGOALS), legacy)
			MAKE_TARGET_OS = 1;
			MAKEGOAL = legacy
		endif
	endif
endif

#
# Export our make goal i.e. mountain-lion, lion or legacy (snow-leopard or leopard).
#

export MAKEGOAL

#
# Export OS build target (picked up by: i386/libsaio/Makefile).
#

export PRODUCT_OS_TARGET = `echo $(MAKE_TARGET_OS)`

#
# Check if a target model was specified (example: make MODEL=16 mountain-lion).
#

ifdef MODEL
	#
	# MODEL=[MacModelNN] specified, export target model as PRODUCT_MODEL_TARGET.
	#
	ifneq ($(MODEL),)
		export MAKE_TARGET_MODEL = $(MODEL)
		#
		# Include static ACPI/EFI/SMBIOS data file per model identifier.
		#
		DATA_FILE = $(MODEL)
	else
		export MAKE_TARGET_MODEL = default
		#
		# Include default/empty static data file (no model identifier specified).
		#
		DATA_FILE = data-template
	endif
else
	#
	# Include default settings template (no model identifier specified).
	#
	export MAKE_TARGET_MODEL = default
	#
	# Include default/empty static data file (no model identifier specified).
	#
	DATA_FILE = data-template
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
