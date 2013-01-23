#!/bin/sh
#
# Script (ssdtPRGen.sh) to create ssdt-pr.dsl for Apple Power Management Support.
#
# Version 0.9 - Copyright (c) 2012 by RevoGirl <RevoGirl@rocketmail.com>
#

# set -x # Used for tracing errors (can be put anywhere in the script).

#================================= GLOBAL VARS ==================================

ssdtPR=/tmp/ssdt-pr.dsl

ssdtID=ssdt-pr

#
# Lowest possible idle frequency (800 for mobile processors).
#

baseFrequency=1500

#CPU='i5-2410M','i5-2510E','i5-2515E','i5-2520M','i5-2537M','i5-2540M','i5-2557M',\
#'i5-3210M','i5-3317U','i5-3320M','i5-3360M','i5-3427U','i5-3610ME'

#TDP=		35,35,35,35,17,35,17,35,17,35,35,17,25

#CLOCKSPEED=	23,25,25,25,14,26,17,25,17,26,28,18,27

#MAXTURBO=	29,31,31,32,23,33,27,31,26,33,35,28,33

#THREADS=	04,04,04,04,04,04,04,04,04,04,04,04,04


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
	echo '    Scope (_PR.CPU0)'                                             >> $ssdtPR
	echo '    {'                                                            >> $ssdtPR

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

   printf "        Name (APSS, Package (0x%02X" $2                          >> $ssdtPR

	echo ')'                                                                >> $ssdtPR
	echo '        {'                                                        >> $ssdtPR
}


#--------------------------------------------------------------------------------

function _printPackages()
{
	let tdp=($1*1000)
	let maxNonTurboFrequency=$2
	let frequency=$3
	let max_ratio=($frequency/100)

	while [ $frequency -gt $baseFrequency ]; do
		echo ''                                                             >> $ssdtPR
		echo '            Package (0x06)'                                   >> $ssdtPR
		echo '            {'                                                >> $ssdtPR

		printf "                0x%04X" $frequency                          >> $ssdtPR

		echo ','                                                            >> $ssdtPR

		let ratio=$frequency/100
        
        if [ $frequency -lt $maxNonTurboFrequency ];
            then
                power=$(echo "scale=6;m=((1.1-(($max_ratio-$ratio)*0.00625))/1.1);(($ratio/$max_ratio)*(m*m)*$tdp);" | bc | sed -e 's/.[0-9A-F]*$//')
            else
                power=$tdp
        fi

		printf "                0x%08X" $power                              >> $ssdtPR

		echo ','                                                            >> $ssdtPR

		echo '                0x0A,'                                        >> $ssdtPR
		echo '                0x0A,'                                        >> $ssdtPR
 
		printf "                0x%02X" $ratio                              >> $ssdtPR

		echo '00,'                                                          >> $ssdtPR

		printf "                0x%02X" $ratio                              >> $ssdtPR

		echo '00'                                                           >> $ssdtPR

		let frequency-=100

		if [ $frequency -eq $baseFrequency ];
			then
				echo '            }'                                        >> $ssdtPR
			else
				echo '            },'                                       >> $ssdtPR
		fi
	done

	echo '        })'                                                       >> $ssdtPR
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
	echo '    }'                                                            >> $ssdtPR
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
	_printScopeStart $turboStates $packageLength
	_printPackages $tdp $frequency $maxTurboFrequency
	_printCSTScope
	_printCPUScopes $logicalCPUs
}


#==================================== START =====================================
 
#
# Check number of arguments.
#

if [ $# -eq 2 ];
    then
        main $1 $2
    else
        echo "Usage: $0 TDP MaxTurboFrequency"
        exit 1
fi

#================================================================================

exit 0
