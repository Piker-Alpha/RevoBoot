#!/bin/sh
#
# Script (ssdtPRGen.sh) to create ssdt-pr.dsl for Apple Power Management Support.
#
# Version 0.9 - Copyright (c) 2012 by RevoGirl <RevoGirl@rocketmail.com>
# Version 1.3 - Copyright (c) 2013 by Pike <PikeRAlpha@yahoo.com>
#
# Updates:
#			- Added support for Ivybridge (Pike, January, 2013)
#			- Filename error fixed (Pike, January, 2013)
#			- Namespace error fixed in _printScopeStart (Pike, January, 2013)
#			- Model and board-id checks added (Pike, January, 2013)
#			- SMBIOS cpu-type check added (Pike, January, 2013)
#

# set -x # Used for tracing errors (can be put anywhere in the script).

#================================= GLOBAL VARS ==================================

ssdtPR=/tmp/ssdt-pr.dsl

ssdtID=ssdt_pr

#
# Lowest possible idle frequency minus 100.
#

baseFrequency=1500

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
		echo '    External (\_PR_.CPU'$currentCPU', DeviceObj)'             >> $ssdtPR
		let currentCPU+=1
	done

	echo ''                                                                 >> $ssdtPR
}


#--------------------------------------------------------------------------------

function _printProcessorDefinitions()
{
	currentCPU=0;

	while [ $currentCPU -lt $1 ]; do
		echo '    External (\_PR_.CPU'$currentCPU', DeviceObj)'             >> $ssdtPR
		let currentCPU+=1
	done

	echo ''                                                                 >> $ssdtPR
}

#--------------------------------------------------------------------------------

function _printScopeStart()
{
	echo '    Scope (\_PR.CPU0)'                                            >> $ssdtPR
	echo '    {'                                                            >> $ssdtPR

	let packageLength=$2

	#
	# Do we need to create additional (Low Frequency) P-States for Ivybridge?
	#

	if [ $3 -eq 1 ];
		then
			let lowestFrequency=($baseFrequency+100)
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
	let tdp=($1*1000)
	let maxNonTurboFrequency=$2
	let frequency=$3
	let min_ratio=($baseFrequency/100)
	let max_ratio=($frequency/100)
	let lowFrequencyPStates=$4
	let lowestFrequency=$baseFrequency

	#
	# Do we need to create additional (Low Frequency) P-States for Ivybridge?
	#

	if [ $lowFrequencyPStates -eq 1 ]
		then
			let lowestFrequency=(800-100)
	fi

	while [ $frequency -gt $lowestFrequency ]; do
		echo '            Package (0x06)'                                   >> $ssdtPR
		echo '            {'                                                >> $ssdtPR

		printf "                0x%04X" $frequency                          >> $ssdtPR

		echo ','                                                            >> $ssdtPR

		let ratio=$frequency/100

		if [ $ratio -gt $min_ratio ]
			then
				if [ $frequency -lt $maxNonTurboFrequency ];
					then
						power=$(echo "scale=6;m=((1.1-(($max_ratio-$ratio)*0.00625))/1.1);(($ratio/$max_ratio)*(m*m)*$tdp);" | bc | sed -e 's/.[0-9A-F]*$//')
					else
						power=$tdp
				fi

				printf "                0x%08X" $power                      >> $ssdtPR
				echo ','                                                    >> $ssdtPR
			else
				echo '                Zero,'                                 >> $ssdtPR
		fi

		echo '                0x0A,'                                        >> $ssdtPR
		echo '                0x0A,'                                        >> $ssdtPR
 
		printf "                0x%02X" $ratio                              >> $ssdtPR

		echo '00,'                                                          >> $ssdtPR

		printf "                0x%02X" $ratio                              >> $ssdtPR

		echo '00'                                                           >> $ssdtPR

		let frequency-=100

		if [ $frequency -eq $lowestFrequency ];
			then
				echo '            }'                                        >> $ssdtPR
			else
				echo '            },'                                       >> $ssdtPR
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
	echo ''                                                                 >> $ssdtPR
	echo '        Method (ACST, 0, NotSerialized)'                          >> $ssdtPR
	echo '        {'                                                        >> $ssdtPR
	echo '            Return (Package (0x06)'                               >> $ssdtPR
	echo '            {'                                                    >> $ssdtPR
	echo '                One,'                                             >> $ssdtPR
	echo '                0x04,'                                            >> $ssdtPR
	echo '                Package (0x04)'                                   >> $ssdtPR
	echo '                {'                                                >> $ssdtPR
	echo '                    ResourceTemplate ()'                          >> $ssdtPR
	echo '                    {'                                            >> $ssdtPR
	echo '                        Register (FFixedHW,'                      >> $ssdtPR
	echo '                            0x01,               // Bit Width'		>> $ssdtPR
	echo '                            0x02,               // Bit Offset'	>> $ssdtPR
	echo '                            0x0000000000000000, // Address'		>> $ssdtPR
	echo '                            0x01,               // Access Size'	>> $ssdtPR
	echo '                            )'                                    >> $ssdtPR
	echo '                    },'                                           >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                    One,'                                         >> $ssdtPR
	echo '                    0x03,'                                        >> $ssdtPR
	echo '                    0x03E8'                                       >> $ssdtPR
	echo '                },'                                               >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                Package (0x04)'                                   >> $ssdtPR
	echo '                {'                                                >> $ssdtPR
	echo '                    ResourceTemplate ()'                          >> $ssdtPR
	echo '                    {'                                            >> $ssdtPR
	echo '                        Register (FFixedHW,'                      >> $ssdtPR
	echo '                            0x01,               // Bit Width'		>> $ssdtPR
	echo '                            0x02,               // Bit Offset'	>> $ssdtPR
	echo '                            0x0000000000000010, // Address'		>> $ssdtPR
	echo '                            0x03,               // Access Size'	>> $ssdtPR
	echo '                            )'                                    >> $ssdtPR
	echo '                    },'                                           >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                    0x03,'                                        >> $ssdtPR
	echo '                    0xCD,'                                        >> $ssdtPR
	echo '                    0x01F4'                                       >> $ssdtPR
	echo '                },'                                               >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                Package (0x04)'                                   >> $ssdtPR
	echo '                {'                                                >> $ssdtPR
	echo '                    ResourceTemplate ()'                          >> $ssdtPR
	echo '                    {'                                            >> $ssdtPR
	echo '                        Register (FFixedHW,'                      >> $ssdtPR
	echo '                            0x01,               // Bit Width'		>> $ssdtPR
	echo '                            0x02,               // Bit Offset'	>> $ssdtPR
	echo '                            0x0000000000000020, // Address'		>> $ssdtPR
	echo '                            0x03,               // Access Size'	>> $ssdtPR
	echo '                            )'                                    >> $ssdtPR
	echo '                    },'                                           >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                    0x06,'                                        >> $ssdtPR
	echo '                    0xF5,'                                        >> $ssdtPR
	echo '                    0x015E'                                       >> $ssdtPR
	echo '                },'                                               >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                Package (0x04)'                                   >> $ssdtPR
	echo '                {'                                                >> $ssdtPR
	echo '                    ResourceTemplate ()'                          >> $ssdtPR
	echo '                    {'                                            >> $ssdtPR
	echo '                        Register (FFixedHW,'                      >> $ssdtPR
	echo '                            0x01,               // Bit Width'		>> $ssdtPR
	echo '                            0x02,               // Bit Offset'	>> $ssdtPR
	echo '                            0x0000000000000030, // Address'		>> $ssdtPR
	echo '                            0x03,               // Access Size'	>> $ssdtPR
	echo '                            )'                                    >> $ssdtPR
	echo '                    },'                                           >> $ssdtPR
	echo ''                                                                 >> $ssdtPR
	echo '                    0x07,'                                        >> $ssdtPR
	echo '                    0xF5,'                                        >> $ssdtPR
	echo '                    0xC8'                                         >> $ssdtPR
	echo '                }'                                                >> $ssdtPR
	echo '            })'                                                   >> $ssdtPR
	echo '        }'                                                        >> $ssdtPR

	#
	# We don't want a closing bracket here when we add methods for Ivybridge.
	#

	if [ $lowFrequencyPStates -eq 0 ]
		then
			echo '    }'                                                    >> $ssdtPR
	fi
}


#--------------------------------------------------------------------------------

function _printCPUScopes()
{
	currentCPU=1;

	while [ $currentCPU -lt $1 ]; do
		echo ''                                                             >> $ssdtPR
		echo '    Scope (\_PR.CPU'$currentCPU')'                            >> $ssdtPR
		echo '    {'                                                        >> $ssdtPR
		echo '        Method (APSS, 0, NotSerialized)'                      >> $ssdtPR
		echo '        {'                                                    >> $ssdtPR
		echo '            Return (\_PR.CPU0.APSS)'                          >> $ssdtPR
		echo '        }'                                                    >> $ssdtPR
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
	echo `ioreg -p IODeviceTree -d 2 -k compatible | grep compatible | sed -e 's/ *"*=*<*>*//g' -e 's/compatible*//'`
}

#--------------------------------------------------------------------------------

function _getBoardID()
{
	#
	# Grab 'board-id' property from ioreg (stripped with sed / RegEX magic).
	#
	echo `ioreg -p IODeviceTree -d 2 -k board-id | grep board-id | sed -e 's/ *"*=*<*>*//g' -e 's/board-id*//'`
}

#--------------------------------------------------------------------------------

function _getCPUtype()
{
	#
	# Grab 'cpu-type' property from ioreg (stripped with sed / RegEX magic).
	#
	local grepStr=`ioreg -p IODeviceTree -n CPU0@0 -k cpu-type | grep cpu-type | sed -e 's/.*[<]//' -e 's/0\{0\}>$//'`
	#
	# Swap bytes with help of ${str:pos:num}
	#
	echo ${grepStr:2:2}${grepStr:0:2}
}

#--------------------------------------------------------------------------------

function _getSandyMacModelByBoardID()
{
	local boardID=$(_getBoardID)
	local macModelIdentifier=""

	case $boardID in
		Mac-942B59F58194171B)
			local macModelIdentifier="iMac12,1"
			;;

		Mac-942B5BF58194151B)
			local macModelIdentifier="iMac12,2"
			;;

		Mac-8ED6AF5B48C039E1)
			local macModelIdentifier="Macmini5,1"
			;;

		Mac-4BC72D62AD45599E)
			local macModelIdentifier="Macmini5,2"
			;;

		Mac-7BA5B2794B2CDB12)
			local macModelIdentifier="Macmini5,3"
			;;

		Mac-94245B3640C91C81)
			local macModelIdentifier="MacBookPro8,1"
			;;

		Mac-94245A3940C91C80)
			local macModelIdentifier="MacBookPro8,2"
			;;

		Mac-942459F5819B171B)
			local macModelIdentifier="MacBookPro8,3"
			;;

		Mac-C08A6BB70A942AC2)
			local macModelIdentifier="MacBookAir4,1"
			;;

		Mac-742912EFDBEE19B3)
			local macModelIdentifier="MacBookAir4,2"
			;;
	esac

	echo $macModelIdentifier
}

#--------------------------------------------------------------------------------

function _getIvyMacModelByBoardID()
{
  local boardID=$(_getBoardID)
  local macModelIdentifier=""

  case $boardID in
	Mac-00BE6ED71E35EB86)
		local macModelIdentifier="iMac13,1"
		;;

	Mac-FC02E91DDD3FA6A4)
		local macModelIdentifier="iMac13,2"
		;;

	Mac-031AEE4D24BFF0B15819B171B)
		local macModelIdentifier="Macmini6,1"
		;;

	Mac-F65AE981FFA204ED)
		local macModelIdentifier="Macmini6,2"
		;;

	Mac-4B7AC7E43945597E)
		local macModelIdentifier="MacBookPro9,1"
		;;

	Mac-6F01561E16C75D06)
		local macModelIdentifier="MacBookPro9,2"
		;;

	Mac-C3EC7CD22292981F)
		local macModelIdentifier="MacBookPro10,1"
		;;

	Mac-AFD8A9D944EA4843)
		local macModelIdentifier="MacBookPro10,2"
		;;

	Mac-66F35F19FE2A0D05)
		local macModelIdentifier="MacBookAir5,1"
		;;

	Mac-2E6FAB96566FE58C)
		local macModelIdentifier="MacBookAir5,2"
		;;
  esac

  echo $macModelIdentifier
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
    #
    # Command line arguments.
    #

    let tdp=$1
    let maxTurboFrequency=$2
	# let lowFrequencyPStates=$3

    #
    # Do not change anything below this line!
    #

	#let logicalCPUs=$(echo `sysctl hw.logicalcpu` | sed -e 's/^hw.logicalcpu: //')
    let logicalCPUs=$(echo `sysctl machdep.cpu.thread_count` | sed -e 's/^machdep.cpu.thread_count: //')

	let frequency=$(echo `sysctl hw.cpufrequency` | sed -e 's/^hw.cpufrequency: //')
    let frequency=($frequency / 1000000)

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

    let packageLength=$(echo "(($maxTurboFrequency - $baseFrequency) / 100)" | bc)

    _printHeader
	_printExternals $logicalCPUs
	_printScopeStart $turboStates $packageLength $3
	_printPackages $tdp $frequency $maxTurboFrequency $3
	_printCSTScope

	local modelID=$(_getModelName)
	local usedBoardID=$(_getBoardID)

	if [ $3 -eq 1 ]
		then
			local typeCPU=$(_getCPUtype)
			local targetModelID=$(_getIvyMacModelByBoardID)

			_printIvybridgeMethods $usedBoardID $targetModelID
			_printCPUScopes $logicalCPUs

			if [ "$targetModelID" == "" ]
				then
					echo "Warning: Used board-id [$usedBoardID] is not supported by Ivybridge PM"
				else
					if [ "$targetModelID" != "$modelID" ]
						then
							echo "Error: board-id [$usedBoardID] and model [$modelID] mismatch"
					fi
			fi

			if [ "${typeCPU}:2:2" != "04" ]
				then
					echo "Warning: cpu-type may be set improperly (0x$typeCPU instead of 0x${typeCPU:0:2}04)"
			fi
		else
			local targetModelID=$(_getSandyMacModelByBoardID)

			_printCPUScopes $logicalCPUs

			if [ "$targetModelID" == "" ]
				then
					echo "Warning: Used board-id [$usedBoardID] is not supported by Sandybridge PM"
				else
					if [ "$targetModelID" != "$modelID" ]
						then
							echo "Error: board-id [$usedBoardID] and model [$modelID] mismatch"
					fi
			fi

			if [ "${typeCPU}:2:2" != "02" ]
				then
					echo "Warning: cpu-type may be set improperly (0x$typeCPU instead of 0x${typeCPU:0:2}02)"
			fi

	fi
}


#==================================== START =====================================
 
#
# Check number of arguments.
#

if [ $# -eq 3 ];
    then
        main $1 $2 $3
    else
        echo "Usage: $0 TDP MaxTurboFrequency (0 for SandyBridge / 1 for IvyBridge)"
        exit 1
fi

#================================================================================

exit 0
