#!/bin/sh

#
# Bash script executed from: RevoBoot/i386/boot2/Makefile
#
#
# Version 1.1 - Copyright (c) 2013-2017 by Pike R. Alpha
#
# Updates:
#		- v1.1 Improved output (Pike R. Alpha, June 2017).	
#

let index=0

#
# Collect available volume name.
#
targetVolumes=($(ls /Volumes | sort))

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
        echo "Done!"
    fi 
fi
