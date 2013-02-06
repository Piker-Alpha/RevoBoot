#!/bin/bash
#
# Script (ssdtPRGen.sh) to create ssdt-pr.dsl for Apple Power Management Support.
#
# Version 0.9 - Copyright (c) 2012 by RevoGirl <RevoGirl@rocketmail.com>
# Version 2.1 - Copyright (c) 2013 by Pike <PikeRAlpha@yahoo.com>
#
# Updates:
#			- Added support for Ivybridge (Pike, January, 2013)
#			- Filename error fixed (Pike, January, 2013)
#			- Namespace error fixed in _printScopeStart (Pike, January, 2013)
#			- Model and board-id checks added (Pike, January, 2013)
#			- SMBIOS cpu-type check added (Pike, January, 2013)
#			- Copy/paste error fixed (Pike, January, 2013)
#			- Method ACST added to CPU scopes for IB CPUPM (Pike, January, 2013)
#			- Method ACST corrected for latest version of iasl (Dave, January, 2013)
#			- Changed path/filename to ~/Desktop/SSDT_PR.dsl (Dave, January, 2013)
#			- P-States are now one-liners instead of blocks (Pike, January, 2013)
#			- Support for flexible ProcessorNames added (Pike, Februari, 2013)
#			- Better feedback and Debug() injection added (Pike, Februari, 2013)
#			- Automatic processor type detection (Pike, Februari, 2013)
#			- TDP and processor type are now optional arguments (Pike, Februari, 2013)
#			- system-type check (used by X86PlatformPlugin) added (Pike, Februari, 2013)
#			- ACST injection for all logical processors (Pike, Februari, 2013)
#			- ACST hintcode error fixed (Pike, Februari, 2013)
#
# Contributors:
#			- Thanks to Dave and toleda for their help (bug fixes and other improvements).
#

# set -x # Used for tracing errors (can be used anywhere in the script).

#================================= GLOBAL VARS ==================================

scriptVersion=2.0

#
# Path and filename setup.
#

path=~/Desktop
ssdtID=SSDT_PR
ssdtPR=${path}/${ssdtID}.dsl

#
# Lowest possible idle frequency (user configurable).
#

baseFrequency=1600

#
# Here are the other global variables defined.
#

systemType=0

gACST_CPU0=13
gACST_CPU1=7

macModelIdentifier=""

#
# Change this label to "P00" when your tables use P00n instead of CPUn.
#

gProcLabel="CPU"

IVY_BRIDGE=4
SANDY_BRIDGE=2

#--------------------------------------------------------------------------------

function _printHeader()
{
	echo '/*'                                                               >  $ssdtPR
	echo ' * Intel ACPI Component Architecture'                             >> $ssdtPR
	echo ' * AML Disassembler version 20120620-64 [Jun 20 2012]'            >> $ssdtPR
	echo ' * Copyright (c) 2000 - 2012 Intel Corporation'                   >> $ssdtPR
	echo ' * '                                                              >> $ssdtPR
	echo ' * Original Table Header:'                                        >> $ssdtPR
	echo ' *     Signature        "SSDT"'                                   >> $ssdtPR
	echo ' *     Length           0x0000036A (874)'                         >> $ssdtPR
	echo ' *     Revision         0x01'                                     >> $ssdtPR
	echo ' *     Checksum         0x98'                                     >> $ssdtPR
	echo ' *     OEM ID           "APPLE "'                                 >> $ssdtPR
	echo ' *     OEM Table ID     "CpuPm"'                                  >> $ssdtPR
	echo ' *     OEM Revision     0x00001000 (4096)'                        >> $ssdtPR
	echo ' *     Compiler ID      "INTL"'                                   >> $ssdtPR
	echo ' *     Compiler Version 0x20120620 (537985814)'                   >> $ssdtPR
	echo ' */'                                                              >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo 'DefinitionBlock ("'$ssdtID'.aml", "SSDT", 1, "APPLE ", "CpuPm", 0x00001000)'>> $ssdtPR
	echo '{'                                                                >> $ssdtPR
}


#--------------------------------------------------------------------------------

function _printExternals()
{
	currentCPU=0;

	while [ $currentCPU -lt $1 ]; do
		echo '    External (\_PR_.'$gProcLabel$currentCPU', DeviceObj)'     >> $ssdtPR
		let currentCPU+=1
	done

	echo ''                                                                 >> $ssdtPR
}


#--------------------------------------------------------------------------------

function _printDebugInfo()
{
	echo '    Store ("ssdtPRGen.sh version '$scriptVersion'", Debug)'       >> $ssdtPR
	echo '    Store ("baseFrequency    : '$baseFrequency'", Debug)'         >> $ssdtPR
	echo '    Store ("frequency        : '$frequency'", Debug)'             >> $ssdtPR
	echo '    Store ("logicalCPUs      : '$logicalCPUs'", Debug)'           >> $ssdtPR
	echo '    Store ("tdp              : '$tdp'", Debug)'                   >> $ssdtPR
	echo '    Store ("packageLength    : '$packageLength'", Debug)'         >> $ssdtPR
	echo '    Store ("turboStates      : '$turboStates'", Debug)'           >> $ssdtPR
	echo '    Store ("maxTurboFrequency: '$maxTurboFrequency'", Debug)'     >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
}

#--------------------------------------------------------------------------------

function _printProcessorDefinitions()
{
	currentCPU=0;

	while [ $currentCPU -lt $1 ]; do
		echo '    External (\_PR_.'$gProcLabel$currentCPU', DeviceObj)'     >> $ssdtPR
		let currentCPU+=1
	done

	echo ''                                                                 >> $ssdtPR
}

#--------------------------------------------------------------------------------

function _printScopeStart()
{
	echo '    Scope (\_PR.'$gProcLabel'0)'                                  >> $ssdtPR
	echo '    {'                                                            >> $ssdtPR

	let packageLength=$2

	#
	# Do we need to create additional (Low Frequency) P-States?
	#

	if [ $bridgeType -eq $IVY_BRIDGE ];
		then
			let lowestFrequency=$baseFrequency
			let lowFrequencyPStates=($lowestFrequency/100)-8
			let packageLength=($2+$lowFrequencyPStates)

			printf "        Name (APLF, 0x%02x" $lowFrequencyPStates        >> $ssdtPR
			echo ')'                                                        >> $ssdtPR
	fi

	#
	# Check number of Turbo states (for IASL optimization).
	#

	if [ $1 -eq 0 ];
		then
			echo '        Name (APSN, Zero)'                                >> $ssdtPR
		else
			printf "        Name (APSN, 0x%02X" $1                          >> $ssdtPR
			echo ')'                                                        >> $ssdtPR
	fi

	printf "        Name (APSS, Package (0x%02X" $packageLength             >> $ssdtPR

	echo ')'                                                                >> $ssdtPR
	echo '        {'                                                        >> $ssdtPR
}


#--------------------------------------------------------------------------------

function _printPackages()
{
	local frequency=$3
	local maxNonTurboFrequency=$2
	local lowestFrequency=$baseFrequency

	let maxTDP=($1*1000)
	let min_ratio=($baseFrequency/100)
	let max_ratio=($frequency/100)

	#
	# Do we need to create additional (Low Frequency) P-States for Ivybridge?
	#

	if [ $bridgeType -eq $IVY_BRIDGE ]
		then
			let lowestFrequency=800
	fi

	while [ $frequency -ge $lowestFrequency ];
		do
		printf "            Package (0x06) { 0x%04X, " $frequency           >> $ssdtPR

		let ratio=$frequency/100

		if [ $ratio -ge $min_ratio ]
			then
				if [ $frequency -lt $maxNonTurboFrequency ];
					then
						power=$(echo "scale=6;m=((1.1-(($max_ratio-$ratio)*0.00625))/1.1);(($ratio/$max_ratio)*(m*m)*$maxTDP);" | bc | sed -e 's/.[0-9A-F]*$//')
					else
						power=$maxTDP
				fi

				printf "0x%08X, " $power                                    >> $ssdtPR
			else
				printf '      Zero, '                                       >> $ssdtPR
		fi

		printf "0x0A, 0x0A, 0x%02X00, 0x%02X00 }" $ratio $ratio             >> $ssdtPR

		let frequency-=100

		if [ $frequency -ge $lowestFrequency ];
			then
				echo ','                                                    >> $ssdtPR
			else
				echo ''                                                     >> $ssdtPR
			fi
	done

		echo '        })'                                                   >> $ssdtPR
}


#--------------------------------------------------------------------------------

function _printIvybridgeMethods()
{
	echo ''                                                                 >> $ssdtPR
	echo '        Method (MCDP, 2, NotSerialized)'                          >> $ssdtPR
	echo '        {'                                                        >> $ssdtPR
	echo '            If (LEqual (Arg0, Zero))'                             >> $ssdtPR
	echo '            {'                                                    >> $ssdtPR
	echo '                Store (Buffer (One)'                              >> $ssdtPR
	echo '                {'                                                >> $ssdtPR
	echo '                    0x03'                                         >> $ssdtPR
	echo '                }, Arg1)'                                         >> $ssdtPR
	echo '            }'                                                    >> $ssdtPR
	echo '        }'                                                        >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '        Method (_DSM, 4, NotSerialized)'                          >> $ssdtPR
	echo '        {'                                                        >> $ssdtPR
	echo '            Store (Package (0x02)'                                >> $ssdtPR
	echo '            {'                                                    >> $ssdtPR
	echo '                "plugin-type",'                                   >> $ssdtPR
	echo '                One'                                              >> $ssdtPR
	echo '            }, Local0)'                                           >> $ssdtPR
	echo '            MCDP (Arg2, RefOf (Local0))'                          >> $ssdtPR
	echo '            Return (Local0)'                                      >> $ssdtPR
	echo '        }'                                                        >> $ssdtPR
	echo '    }'                                                            >> $ssdtPR
}

#--------------------------------------------------------------------------------

function _printCSTScope()
{
    let C1=0
    let C2=0
    let C3=0
    let C6=0
    let C7=0
    local pkgLength=2
    local numberOfCStates=0

    echo ''                                                                         >> $ssdtPR
    echo '        Method (ACST, 0, NotSerialized)'                                  >> $ssdtPR
    echo '        {'                                                                >> $ssdtPR

    #
    # Are we injecting C-States for CPU1?
    #
    if [ $1 -eq 1 ];
        then
            # Yes (also used by CPU2, CPU3 and greater).
            let targetCStates=$gACST_CPU1
            latency_C1=0x03E8
            latency_C2=0x94
            latency_C3=0xA9
            echo '            Store ("CPU1 C-States    : '$gACST_CPU1'", Debug)'    >> $ssdtPR

        else
			# No (only used by CPU0).
            let targetCStates=$gACST_CPU0
            latency_C1=Zero
            latency_C3=0xCD
            latency_C6=0xF5
            latency_C7=0xF5
            echo '            Store ("CPU0 C-States    : '$gACST_CPU0'", Debug)'    >> $ssdtPR
    fi

    #
    # Checks to determine which C-State(s) we should inject.
    #
    if (($targetCStates & 1)); then
        let C1=1
        let numberOfCStates+=1
        let pkgLength+=1
    fi

    if (($targetCStates & 2)); then
        let C2=1
        let numberOfCStates+=1
        let pkgLength+=1
    fi

    if (($targetCStates & 4)); then
        let C3=1
        let numberOfCStates+=1
        let pkgLength+=1
    fi

    if (($targetCStates & 8)); then
        let C6=1
        let numberOfCStates+=1
        let pkgLength+=1
    fi

    if (($targetCStates & 16)); then
        let C7=1
        let numberOfCStates+=1
        let pkgLength+=1
    fi

    let hintCode=0x00

    echo ''                                                                         >> $ssdtPR
  printf "            Return (Package (0x%02x)\n" $pkgLength                        >> $ssdtPR
    echo '            {'                                                            >> $ssdtPR
    echo '                One,'                                                     >> $ssdtPR
  printf "                0x%02x,\n" $numberOfCStates                               >> $ssdtPR
    echo '                Package (0x04)'                                           >> $ssdtPR
    echo '                {'                                                        >> $ssdtPR
    echo '                    ResourceTemplate ()'                                  >> $ssdtPR
    echo '                    {'                                                    >> $ssdtPR
    echo '                        Register (FFixedHW,'                              >> $ssdtPR
    echo '                            0x01,               // Bit Width'             >> $ssdtPR
    echo '                            0x02,               // Bit Offset'            >> $ssdtPR
  printf "                            0x%016x, // Address\n" $hintCode              >> $ssdtPR
    echo '                            0x01,               // Access Size'           >> $ssdtPR
    echo '                            )'                                            >> $ssdtPR
    echo '                    },'                                                   >> $ssdtPR
    echo '                    One,'                                                 >> $ssdtPR
    echo '                    '$latency_C1','                                       >> $ssdtPR
    echo '                    0x03E8'                                               >> $ssdtPR

    if (($C2)); then
        let hintCode+=0x10
        echo '                },'                                                   >> $ssdtPR
        echo ''                                                                     >> $ssdtPR
        echo '                Package (0x04)'                                       >> $ssdtPR
        echo '                {'                                                    >> $ssdtPR
        echo '                    ResourceTemplate ()'                              >> $ssdtPR
        echo '                    {'                                                >> $ssdtPR
        echo '                        Register (FFixedHW,'                          >> $ssdtPR
        echo '                            0x01,               // Bit Width'         >> $ssdtPR
        echo '                            0x02,               // Bit Offset'        >> $ssdtPR
      printf "                            0x%016x, // Address\n" $hintCode          >> $ssdtPR
        echo '                            0x03,               // Access Size'       >> $ssdtPR
        echo '                            )'                                        >> $ssdtPR
        echo '                    },'                                               >> $ssdtPR
        echo '                    0x02,'                                            >> $ssdtPR
        echo '                    '$latency_C2','                                   >> $ssdtPR
        echo '                    0x01F4'                                           >> $ssdtPR
    fi

    if (($C3)); then
        let hintCode+=0x10
        echo '                },'                                                   >> $ssdtPR
        echo ''                                                                     >> $ssdtPR
        echo '                Package (0x04)'                                       >> $ssdtPR
        echo '                {'                                                    >> $ssdtPR
        echo '                    ResourceTemplate ()'                              >> $ssdtPR
        echo '                    {'                                                >> $ssdtPR
        echo '                        Register (FFixedHW,'                          >> $ssdtPR
        echo '                            0x01,               // Bit Width'         >> $ssdtPR
        echo '                            0x02,               // Bit Offset'        >> $ssdtPR
      printf "                            0x%016x, // Address\n" $hintCode          >> $ssdtPR
        echo '                            0x03,               // Access Size'       >> $ssdtPR
        echo '                            )'                                        >> $ssdtPR
        echo '                    },'                                               >> $ssdtPR
        echo '                    0x03,'                                            >> $ssdtPR
        echo '                    '$latency_C3','                                   >> $ssdtPR
        echo '                    0x01F4'                                           >> $ssdtPR
    fi

    if (($C6)); then
        let hintCode+=0x10
        echo '                },'                                                   >> $ssdtPR
        echo ''                                                                     >> $ssdtPR
        echo '                Package (0x04)'                                       >> $ssdtPR
        echo '                {'                                                    >> $ssdtPR
        echo '                    ResourceTemplate ()'                              >> $ssdtPR
        echo '                    {'                                                >> $ssdtPR
        echo '                        Register (FFixedHW,'                          >> $ssdtPR
        echo '                            0x01,               // Bit Width'         >> $ssdtPR
        echo '                            0x02,               // Bit Offset'        >> $ssdtPR
      printf "                            0x%016x, // Address\n" $hintCode          >> $ssdtPR
        echo '                            0x03,               // Access Size'       >> $ssdtPR
        echo '                            )'                                        >> $ssdtPR
        echo '                    },'                                               >> $ssdtPR
        echo '                    0x06,'                                            >> $ssdtPR
        echo '                    '$latency_C6','                                   >> $ssdtPR
        echo '                    0x015E'                                           >> $ssdtPR
    fi

	if (($C7)); then
        #
        # If $hintCode is already 0x30 then use 0x31 otherwise 0x30
        #
        if [ $hintCode -eq 48 ];
            then
                let hintCode+=0x01
            else
                let hintCode+=0x10
        fi
        echo '                },'                                                   >> $ssdtPR
        echo ''                                                                     >> $ssdtPR
        echo '                Package (0x04)'                                       >> $ssdtPR
        echo '                {'                                                    >> $ssdtPR
        echo '                    ResourceTemplate ()'                              >> $ssdtPR
        echo '                    {'                                                >> $ssdtPR
        echo '                        Register (FFixedHW,'                          >> $ssdtPR
        echo '                            0x01,               // Bit Width'         >> $ssdtPR
        echo '                            0x02,               // Bit Offset'        >> $ssdtPR
      printf "                            0x%016x, // Address\n" $hintCode          >> $ssdtPR
        echo '                            0x03,               // Access Size'       >> $ssdtPR
        echo '                            )'                                        >> $ssdtPR
        echo '                    },'                                               >> $ssdtPR
        echo '                    0x07,'                                            >> $ssdtPR
        echo '                    '$latency_C7','                                   >> $ssdtPR
        echo '                    0xC8'                                             >> $ssdtPR
    fi

    echo '                }'                                                        >> $ssdtPR
    echo '            })'                                                           >> $ssdtPR
    echo '        }'                                                                >> $ssdtPR

    if [ $1 -eq 1 ];
        then
            gACST_CPU1=$numberOfCStates
        else
			gACST_CPU0=$numberOfCStates
    fi

    #
    # We don't want a closing bracket here when we add methods for Ivy Bridge.
    #

    if [ $bridgeType -eq $SANDY_BRIDGE ]; then
        echo '    }'                                                                >> $ssdtPR
    fi
}

#--------------------------------------------------------------------------------

function _printCPUScopes()
{
	currentCPU=1;

	while [ $currentCPU -lt $1 ]; do
		echo ''                                                             >> $ssdtPR
		echo '    Scope (\_PR.'$gProcLabel$currentCPU')'                    >> $ssdtPR
		echo '    {'                                                        >> $ssdtPR
		echo '        Method (APSS, 0, NotSerialized) { Return (\_PR.'$gProcLabel'0.APSS) }' >> $ssdtPR

		#
		# IB CPUPM tries to parse/execute Method ACST (see debug data) and thus we add
		# this method, conditionally, since SB CPUPM doesn't seem to care about it.
		#
		if [ $bridgeType -eq $IVY_BRIDGE ]
			then
				if [ $currentCPU -eq 1 ];
					then
						_printCSTScope 1
					else
						echo '        Method (ACST, 0, NotSerialized) { Return (\_PR.'$gProcLabel'1.ACST ()) }' >> $ssdtPR
				fi
		fi

		echo '    }'                                                        >> $ssdtPR
		let currentCPU+=1
	done

	echo '}'                                                                >> $ssdtPR
}

#--------------------------------------------------------------------------------

function _getModelName()
{
	#
	# Grab 'compatible' property from ioreg (stripped with sed / RegEX magic).
	#
	echo `ioreg -p IODeviceTree -d 2 -k compatible | grep compatible | sed -e 's/ *["=<>]//g' -e 's/compatible//'`
}

#--------------------------------------------------------------------------------

function _getBoardID()
{
	#
	# Grab 'board-id' property from ioreg (stripped with sed / RegEX magic).
	#
	boardID=`ioreg -p IODeviceTree -d 2 -k board-id | grep board-id | sed -e 's/ *["=<>]//g' -e 's/board-id//'`
}

#--------------------------------------------------------------------------------

function _getCPUtype()
{
	#
	# Grab 'cpu-type' property from ioreg (stripped with sed / RegEX magic).
	#
	local grepStr=`ioreg -p IODeviceTree -n CPU0@0 -k cpu-type | grep cpu-type | sed -e 's/ *[-|="<a-z>]//g'`
	#
	# Swap bytes with help of ${str:pos:num}
	#
	echo ${grepStr:2:2}${grepStr:0:2}
}

#--------------------------------------------------------------------------------

function _getCPUModel()
{
	#
	# Returns the hexadecimal value of machdep.cpu.model
	#
	echo 0x$(echo "obase=16; `sysctl machdep.cpu.model | sed -e 's/^machdep.cpu.model: //'`" | bc)
}

#--------------------------------------------------------------------------------

function _getSystemType()
{
	#
	# Grab 'system-type' property from ioreg (stripped with sed / RegEX magic).
	#
	echo `ioreg -p IODeviceTree -d 2 -k system-type | grep system-type | sed -e 's/ *[-="<0a-z>]//g'`
}

#--------------------------------------------------------------------------------

function _checkSMCKeys()
{
	#
	# TODO: Check SMC keys to see if they are there and properly initialized!
	#
	# Note: Do <i>not</i> dump SMC keys with HWSensors/iStat or other SMC plug-ins installed!
	#
	local filename="/System/Library/Extensions/FakeSMC.kext/Contents/Info.plist"
	local data=`grep -so '<key>[a-zA-Z]*</key>' $filename | sed -e 's/<key>//' -e 's/<\/key>//g'`

	local status=`echo $data | grep -oe 'DPLM'`

	if [ $status == 'XPLM' ]; then
		# DPLM  [{lim]  (bytes 00 00 00 00 00)
		echo "SMC key 'DPLM' found (OK)"
	fi
set -x
	local status=`echo $data | grep -oe 'MSAL'`

	if [ $status == 'MSAL' ]; then
		# MSAL  [hex_]  (bytes 4b)
		echo "SMC key 'MSAL' found (OK)"
	fi
}

#--------------------------------------------------------------------------------

function _initSandyBridgeSetup()
{
	case $boardID in
		Mac-942B59F58194171B)
			systemType=1
			macModelIdentifier="iMac12,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-942B5BF58194151B)
			systemType=1
			macModelIdentifier="iMac12,2"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-8ED6AF5B48C039E1)
			systemType=1
			macModelIdentifier="Macmini5,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-4BC72D62AD45599E)
			systemType=1
			macModelIdentifier="Macmini5,2"
			gACST_CPU0=13   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-7BA5B2794B2CDB12)
			systemType=1
			macModelIdentifier="Macmini5,3"
			gACST_CPU0=13   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-94245B3640C91C81)
			systemType=2
			macModelIdentifier="MacBookPro8,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-94245A3940C91C80)
			systemType=2
			macModelIdentifier="MacBookPro8,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-942459F5819B171B)
			systemType=2
			macModelIdentifier="MacBookPro8,3"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-C08A6BB70A942AC2)
			systemType=2
			macModelIdentifier="MacBookAir4,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-742912EFDBEE19B3)
			systemType=2
			macModelIdentifier="MacBookAir4,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;
	esac
}

#--------------------------------------------------------------------------------

function _initIvyBridgeSetup()
{
	case $boardID in
		Mac-00BE6ED71E35EB86)
			systemType=1
			macModelIdentifier="iMac13,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-FC02E91DDD3FA6A4)
			systemType=1
			macModelIdentifier="iMac13,2"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-031AEE4D24BFF0B1)
			systemType=1
			macModelIdentifier="Macmini6,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-F65AE981FFA204ED)
			systemType=1
			macModelIdentifier="Macmini6,2"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-4B7AC7E43945597E)
			systemType=2
			macModelIdentifier="MacBookPro9,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-6F01561E16C75D06)
			systemType=2
			macModelIdentifier="MacBookPro9,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-C3EC7CD22292981F)
			systemType=2
			macModelIdentifier="MacBookPro10,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-AFD8A9D944EA4843)
			systemType=2
			macModelIdentifier="MacBookPro10,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-66F35F19FE2A0D05)
			systemType=2
			macModelIdentifier="MacBookAir5,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-2E6FAB96566FE58C)
			systemType=2
			macModelIdentifier="MacBookAir5,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;
	esac
}

#--------------------------------------------------------------------------------
#
# Only administrators (root) are allowed to run this script.
#
#--------------------------------------------------------------------------------

function _isRoot()
{
  if [ $(id -u) != 0 ]; then
      echo "This script must be run as root" 1>&2
      exit 1
  fi

  echo 1
}


#--------------------------------------------------------------------------------

function main()
{
	echo ''

	#
	# Get CPU type and model.
	#

	local model=$(_getCPUModel)

	case $model in
		0x2A)
			echo "Sandy Bridge Core processor detected"
			let tdp=95
			let bridgeType=2
			;;

		0x2D)
			echo "Sandy Bridge Core processor detected"
			let tdp=95
			let bridgeType=2
			;;

		0x3A)
			echo "Ivy Bridge Core processor detected"
			let tdp=77
			let bridgeType=4
			;;

		0x3B)
			echo "Ivy Bridge Core processor detected"
			let tdp=77
			let bridgeType=4
			;;
	esac

    #
    # Command line arguments.
    #

	let maxTurboFrequency=$1

	if [ $# -eq 2 ];
		then
			let tdp=$2
			echo "Max TDP override, now using: $tdp Watt"
		else
			echo "Using the default max TDP of: $tdp Watt"
	fi

	if [ $# -eq 3 ];
		then
			if [ $3 -eq 0 ];
				then
					let bridgeType=2
					echo "CPU type override, now using: Sandy Bridge"
				else
					let bridgeType=4
					echo "CPU type override, now using: Ivy Bridge"
			fi
	fi

    #
    # Do not change anything below this line!
    #

	#let logicalCPUs=$(echo `sysctl hw.logicalcpu` | sed -e 's/^hw.logicalcpu: //')
    local logicalCPUs=$(echo `sysctl machdep.cpu.thread_count` | sed -e 's/^machdep.cpu.thread_count: //')
	let frequency=$(echo `sysctl hw.cpufrequency` | sed -e 's/^hw.cpufrequency: //')
    let frequency=($frequency / 1000000)

	echo "$logicalCPUs logical CPU's detected with a Core Frequency of $frequency MHz"

	#
    # Get number of Turbo states.
    #

    let turboStates=$(echo "(($maxTurboFrequency - $frequency) / 100)" | bc)

    #
    # Check number of Turbo states.
    #

    if [ $turboStates -lt 0 ];
        then
            let turboStates=0
    fi

	echo "Number of Turbo States: $turboStates ($frequency-$maxTurboFrequency MHz)"

    local packageLength=$(echo "((($maxTurboFrequency - $baseFrequency)+100) / 100)" | bc)

	echo "Number of P-States: $packageLength ($baseFrequency-$maxTurboFrequency)"

    _printHeader
	_printExternals $logicalCPUs
	_printDebugInfo $logicalCPUs $tdp $packageLength $turboStates $maxTurboFrequency
	_printScopeStart $turboStates $packageLength
	_printPackages $tdp $frequency $maxTurboFrequency

	_getBoardID

	local modelID=$(_getModelName)
	local typeCPU=$(_getCPUtype)
	local currentSystemType=$(_getSystemType)

	if [ $bridgeType -eq $IVY_BRIDGE ];
		then
			local cpuTypeString="04"
			local bridgeTypeString="Ivy Bridge"

			_initIvyBridgeSetup
			_printCSTScope 0
			_printIvybridgeMethods
			_printCPUScopes $logicalCPUs
		else
			local cpuTypeString="02"
			local bridgeTypeString="Sandy Bridge"

			_initSandyBridgeSetup
			_printCSTScope 0
			_printCPUScopes $logicalCPUs
	fi

	printf "Number of C-States for "$gProcLabel"0: $gACST_CPU0\n"
	printf "Number of C-States for "$gProcLabel"1: $gACST_CPU1\n"

	if [ ${typeCPU:2:2} -ne $cpuTypeString ]; then
		echo "Warning: cpu-type may be set improperly (0x$typeCPU instead of 0x${typeCPU:0:2}$cpuTypeString)"
	fi

	if [ $systemType -eq 0 ];
		then
			echo "Warning: Used board-id [$boardID] is not supported by $bridgeTypeString PM"
		else
			if [ "$macModelIdentifier" != "$modelID" ]; then
				echo "Error: board-id [$boardID] and model [$modelID] mismatch"
			fi

			if [ $currentSystemType -ne $systemType ]; then
				echo "Warning: system-type may be set improperly ($currentSystemType instead of $systemType)"
		fi
	fi
}


#==================================== START =====================================
 
#
# Check number of arguments.
#

if [ $# -gt 0 ];
    then
        main $1 $2 $3
        open $ssdtPR
    else
        echo "Usage: $0 MaxTurboFrequency [TDP (Watts) CPU (0=SandyBridge, 1=IvyBridge)]"
        exit 1
fi

#================================================================================

exit 0
