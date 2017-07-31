#!/bin/sh

#
# Bash script to install boot files.
#
#
# Version 1.2 - Copyright (c) 2013-2017 by Pike R. Alpha
#
# Updates:
#			- 1.1 Verbose output added.
#			- 1.2 Check files/run nasm for missing boot files.
#

pwd=$(pwd)

if [ ! -e i386/boot0/boot0 ];
  then
    cd i386/boot0
    echo "Running nasm for boot0 ..."
    nasm boot0.s -o boot0
    cd "${pwd}"
fi

if [ ! -e i386/boot0/boot1h ];
  then
    cd "i386/boot1"
    echo "Running nasm for boot1h ..."
    nasm boot1h.s -o boot1h
    cd "${pwd}"
fi

let index=0

if [[ -e "i386/boot0/boot0" && -e "i386/boot1/boot1h" ]];
  then
    #
    # Collect available volume names.
    #
    cd /Volumes/
    targetVolumes=(*)
    cd "${pwd}"

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
    read -p "Select a target volume for the boot files: " volumeNumber

    #
    # Path to target volume.
    #
    targetVolume="/Volumes/${targetVolumes[$volumeNumber]}"

    #
    # Get device identifier.
    #
    disk=$(diskutil info "${targetVolume}" | awk '$1$2$3 == "PartofWhole:" { print $4 }')

    sudo ./fdisk440 -f i386/boot0/boot0 -u -y "/dev/r${disk}"

    sudo dd if=i386/boot1/boot1h of="/dev/r${disk}s2"
fi
