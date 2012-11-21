#
# File: RevoBoot/i386/Makefile
#
# Updates:
#
#			- Major cleanup (PikerAlpha, October 2012).
#			- Output improvements (PikerAlpha, October 2012).
#			- PRODUCT_MODEL_TARGET renamed to MAKE_TARGET_MODEL (PikerAlpha, November 2012).
#			- Cleanup and output changed (PikerAlpha, October 2012).
#

#
# These paths are only valid in subdirectories of this directory.
#

OBJROOT=../i386/obj/i386
SYMROOT=../i386/sym/i386

# VPATH = $(OBJROOT):$(SYMROOT)

#
# The build order here is important.
#

SUBDIRS = util libsa libsaio boot2


$(MAKEGOAL):
	@for i in $(SUBDIRS); \
	do \
		echo ================= RevoBoot/i386/$$i =================; \
		( cd $$i; ${MAKE} \
			"OBJROOT=$(OBJROOT)/$$i" \
		  	"SYMROOT=$(SYMROOT)" \
			"RC_ARCHS=$(RC_ARCHS)" \
			"RC_CFLAGS=$(RC_CFLAGS)" $@ \
		) || exit $$?; \
	done
