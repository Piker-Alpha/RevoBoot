#!/bin/bash
#
# Installation script for ssdtPRGen.command
#
# Version 0.1 - Copyright (c) 2013 by Pike <PikeRAlpha@yahoo.com>
#
# Updates:
#			-
#
# Contributors:
#

#--------------------------------------------------------------------------------

if [ -f ~/ssdtPRGen.command ];
    then
        open ~/ssdtPRGen.command
    else
        #
        # Download script
        #
        curl -o ~/ssdtPRGen.command https://raw.github.com/Piker-Alpha/RevoBoot/clang/i386/libsaio/acpi/Tools/ssdtPRGen.sh

        #
        # Add execute rights
        #
        chmod +x ~/ssdtPRGen.command

        #
        # Maintain backward compatibility with older versions
        #
        ln -sf ~/ssdtPRGen.command ~/ssdtPRGen.sh

        #
        # Put a symbolic link to the script on the Desktop
        #
        ln -sf ~/ssdtPRGen.command ~/Desktop/ssdtPRGen.command
fi

exit 0
