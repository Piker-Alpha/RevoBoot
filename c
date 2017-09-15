#!/bin/sh

#
# Bash script executed from: RevoBoot/i386/boot2/Makefile
#
#
# Version 1.3 - Copyright (c) 2013-2017 by Pike R. Alpha
#
# Updates:
#          - v1.1 Improved output (Pike R. Alpha, June 2017).
#          - v1.2 Fix typo (Pike R. Alpha, June 2017).
#          -      Now also asks if you want to reboot.
#          - v1.3 Improved volume name support. Thanks to 'M':
#          -      https://pikeralpha.wordpress.com/2017/06/22/script-to-upgrade-macos-high-sierra-dp1-to-dp2/#comment-10216

let index=0

#
# Get currect working directory.
#
workingDirectory=$(pwd)

#
# Change additional shell optional behavior (expand unmatched names to a null string).
#
shopt -s nullglob

#
# Change to Volumes folder.
#
cd /Volumes

#
# Collect available volume names.
#
targetVolumes=(*)

echo "\nAvailable target volumes:\n"

for volume in "${targetVolumes[@]}"
do
    echo "[$index] $volume"
    let index++
done

echo ""

#
# Ask to select a target volume.
#
read -p "Select a target volume for the boot file: " volumeNumber

#
# Verify selection.
#
if [ $volumeNumber -gt $index ];
  then
    printf "\nError: Invalid Option ($volumeNumber)!\nAborting ...\n"
    exit 0
  else
    cd "${workingDirectory}"
    echo "Copying RevoBoot/sym/i386/boot to: /Volumes/${targetVolumes[$volumeNumber]}/"
    sudo cp ../../sym/i386/boot "/Volumes/${targetVolumes[$volumeNumber]}/"
    #
    # Compare files.
    #
    cmp -s ../../sym/i386/boot /Volumes/${targetVolumes[$volumeNumber]}/boot
    #
    # Check status (zero is ok).
    #
    if [[ $? -ne 0 ]];
      then
        echo "Error: Copying boot file failed!"
      else
        echo ""
        read -p "Do you want to reboot now (y/n) ?" shouldReboot

        if [ $shouldReboot == "y" ];
          then
            sudo reboot now
          else
            echo "Done!"
        fi
    fi 
fi
