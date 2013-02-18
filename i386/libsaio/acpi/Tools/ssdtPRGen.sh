#!/bin/bash
#
# Script (ssdtPRGen.sh) to create ssdt-pr.dsl for Apple Power Management Support.
#
# Version 0.9 - Copyright (c) 2012 by RevoGirl <RevoGirl@rocketmail.com>
# Version 4.2 - Copyright (c) 2013 by Pike <PikeRAlpha@yahoo.com>
#
# Updates:
#			- Added support for Ivybridge (Pike, January 2013)
#			- Filename error fixed (Pike, January 2013)
#			- Namespace error fixed in _printScopeStart (Pike, January 2013)
#			- Model and board-id checks added (Pike, January 2013)
#			- SMBIOS cpu-type check added (Pike, January 2013)
#			- Copy/paste error fixed (Pike, January 2013)
#			- Method ACST added to CPU scopes for IB CPUPM (Pike, January 2013)
#			- Method ACST corrected for latest version of iasl (Dave, January 2013)
#			- Changed path/filename to ~/Desktop/SSDT_PR.dsl (Dave, January 2013)
#			- P-States are now one-liners instead of blocks (Pike, January 2013)
#			- Support for flexible ProcessorNames added (Pike, Februari 2013)
#			- Better feedback and Debug() injection added (Pike, Februari 2013)
#			- Automatic processor type detection (Pike, Februari 2013)
#			- TDP and processor type are now optional arguments (Pike, Februari 2013)
#			- system-type check (used by X86PlatformPlugin) added (Pike, Februari 2013)
#			- ACST injection for all logical processors (Pike, Februari 2013)
#			- Introducing a stand-alone version of method _DSM (Pike, Februari 2013)
#			- Fix incorrect turbo range (Pike, Februari 2013)
#			- Restore IFS before return (Pike, Februari 2013)
#			- Better/more complete feedback added (Jeroen, Februari 2013)
#			- Processor data for desktop/mobile and server CPU's added (Jeroen, Februari 2013)
#			- Improved power calculation, matching Apple's new algorithm (Pike, Februari 2013)
#			- Fix iMac13,N latency and power values for C3 (Jeroen/Pike, Februari 2013)
#			- IASL failed to launch when path included spaces (Pike, Februari 2013)
#			- Typo in cpu-type check fixed (Jeroen, Februari 2013)
#			- Error in CPU data (i5-3317U) fixed (Pike, Februari 2013)
#			- Setting added for the target path/filename (Jeroen, Februari 2013)
#			- Initial implementation of auto-copy (Jeroen, Februari 2013)
#			- Additional checks added for cpu data/turbo modes (Jeroen, Februari 2013)
#			- Undo filename change done by Jeroen (Pike, Februari 2013)
#			- Improved/faster search algorithm to locate iasl (Jeroen, Februari 2013)
#			- Bug fix, automatic revision update and better feedback (Pike, Februari 2013)
#			- Turned auto copy on (Jeroen, Februari 2013)
#			- Download IASL if it isn't there where we expect it (Pike, Februari 2013)
#			- A sweet dreams update for Pike who wants better feedback (Jeroen, Februari 2013)
#			- First set of Haswell processors added (Pike/Jeroen, Februari 2013)
#			- More rigid testing for user errors (Pike/Jeroen, Februari 2013)
#			- Getting ready for new Haswell setups (Pike/Jeroen, Februari 2013)
#
# Contributors:
#			- Thanks to Dave, toleda and Francis for their help (bug fixes and other improvements).
#			- Many thanks to Jeroen for the CPU data, cleanups and renaming stuff.
#

# set -x # Used for tracing errors (can be used anywhere in the script).

#================================= GLOBAL VARS ==================================

#
# Change this to 0 when your CPU isn't stuck in Low Frequency Mode!
#
let gIvyWorkAround=1

#
# Asks for your confirmation to copy SSDT_PR.aml to /Extra/SSDT.aml (example)
#
let gAutoCopy=1

#
# This is the target location that SSDT.aml will be copied to.
#
# Note: Do no change this - will be updated automatically for Clover/RevoBoot!
#
gDestinationPath="/Extra/"

#
# This is the filename used for the copy process
#
gDestinationFile="SSDT.aml"

#
# A value of 1 will make this script call iasl (compiles SSDT_PR.dsl)
#
# Note: Will be set to 0 when we failed to locate a copy of iasl!
#
let gCallIasl=1

#
# A value of 1 will make this script open SSDT_PR.dsl in the editor of your choice. 
#
let gCallOpen=0

#
# Change this to 0 to stop it from injecting debug data.
#
let gDebug=1

#
# Lowest possible idle frequency (user configurable). Also known as Low Frequency Mode.
#
let gBaseFrequency=1600

#
# Change this label to "P00" when your DSDT uses 'P00n' instead of 'CPUn'.
#
gProcLabel="CPU"

#
# Other global variables.
#

gScriptVersion=4.2

gRevision='0x0000'${gScriptVersion:0:1}${gScriptVersion:2:1}'00'

#
# Path and filename setup.
#

gPath=~/Desktop
gSsdtID=SSDT_PR
gSsdtPR=${gPath}/${gSsdtID}.dsl

gSandyCPU=1
gDesktopCPU=2
gMobileCPU=3
let gServerCPU=4
let gHaswellCPU=5

let gSystemType=0

let gACST_CPU0=13
let gACST_CPU1=7

gMacModelIdentifier=""

let HASWELL=8
let IVY_BRIDGE=4
let SANDY_BRIDGE=2

let gTypeCPU=0
gProcessorData="Unknown CPU"
gProcessorNumber=""

#
# Maximum Turbo Clock Speed (user configurable)
#
let gMaxOCFrequency=5000

let MAX_TURBO_FREQUENCY_ERROR=2
let MAX_TDP_ERROR=3
let TARGET_CPU_ERROR=4
let PROCESSOR_NUMBER_ERROR=5

#
# Processor Number, Max TDP, Low Frequency Mode, Clock Speed, Max Turbo Frequency, Cores, Threads
#

gSandyBridgeCPUList=(
i5-2500K,95,1600,3300,3700,4,4
i7-2600K,95,1600,3400,3800,4,8
i7-2700K,95,1600,3500,3900,4,8
# E3-1200 Xeon Processor Series
E3-1290,95,0,3600,4000,4,8
E3-1280,95,0,3500,3900,4,8
E3-1275,95,0,3400,3800,4,8
E3-1270,80,0,3400,3800,4,8
E3-1260L,45,0,2400,3300,4,8
E3-1245,95,0,3300,3700,4,8
E3-1240,80,0,3300,3700,4,8
E3-1235,95,0,3200,3600,4,8
E3-1230,80,0,3200,3600,4,8
E3-1225,95,0,3100,3400,4,4
E3-1220L,20,0,2200,3400,2,4
E3-1220,80,0,3100,3400,4,4
)

#
# Processor Number, Max TDP, Low Frequency Mode, Clock Speed, Max Turbo Frequency, Cores, Threads
#

gServerIvyBridgeCPUList=(
# E3-1200 Xeon Processor Series
'E3-1290 V2',87,0,3700,4100,4,8
'E3-1285 V2',65,0,3600,4000,
'E3-1285L V2',0,0,3200,3900,
'E3-1280 V2',69,0,3600,4000,4,8
'E3-1275 V2',77,0,3500,3900,4,8
'E3-1270 V2',69,0,3500,3900,4,8
'E3-1265L V2',45,0,2500,3500,4,8
'E3-1245 V2',77,0,3400,3800,4,8
'E3-1240 V2',69,0,3400,3800,4,8
'E3-1230 V2',69,0,3300,3700,4,8
'E3-1225 V2',77,0,3200,3600,4,4
'E3-1220 V2',69,0,3100,3500,4,4
'E3-1220L V2',17,0,2300,3500,2,4
)

gDesktopIvyBridgeCPUList=(
# i7-3700 Desktop Processor Series
i7-3770T,45,1600,2500,3700,4,8
i7-3770S,65,1600,3100,3900,4,8
i7-3770K,77,1600,3500,3900,4,8
i7-3770,77,1600,3400,3900,4,8
# i5-3500 Desktop Processor Series
i5-3570T,45,1600,2300,3300,4,4
i5-3570K,77,1600,3400,3800,4,4
i5-3570S,65,1600,3100,3800,4,4
i5-3570,77,1600,3400,3800,4,4
i5-3550S,65,1600,3000,3700,4,4
i5-3550,77,1600,3300,3700,4,4
# i5-3400 Desktop Processor Series
i5-3475S,65,1600,2900,3600,4,4
i5-3470S,65,1600,2900,3600,4,4
i5-3470,77,1600,3200,3600,4,4
i5-3470T,35,1600,2900,3600,2,4
i5-3450S,65,1600,2800,3500,4,4
i5-3450,77,1600,3100,3500,4,4
# i5-3300 Desktop Processor Series
i5-3350P,69,1600,3100,3300,4,4
i5-3330S,65,1600,2700,3200,4,4
i5-3333S,65,1600,2700,3200,4,4
i5-3330S,65,1600,3700,3200,4,4
i5-3330,77,1600,3000,3200,4,4
# i3-3200 Desktop Processor Series
i3-3240,55,1600,3400,0,2,4
i3-3240T,35,1600,2900,0,2,4
i3-3225,55,1600,3300,0,2,4
i3-3220,55,1600,3300,0,2,4
i3-3220T,35,1600,2800,0,2,4
i3-3210,55,1600,3200,0,2,4
)

gMobileIvyBridgeCPUList=(
# i7-3800 Mobile Processor Series
i7-3840QM,45,1200,2800,3800,4,8
i7-3820QM,45,1200,2700,3700,4,8
# i7-3700 Mobile Processor Series
i7-3740QM,45,1200,2700,3700,4,8
i7-3720QM,45,1200,2600,3600,4,8
# i7-3600 Mobile Processor Series
i7-3689Y,13,0,1500,2600,2,4
i7-3687U,17,800,2100,3300,2,4
i7-3667U,17,800,2000,3200,2,4
i7-3635QM,45,0,2400,3400,4,8
i7-3620QM,35,0,2200,3200,4,8
i7-3632QM,35,0,2200,3200,4,8
i7-3630QM,45,0,2400,3400,4,8
i7-3615QM,45,0,2300,3300,4,8
i7-3615QE,45,0,2300,3300,4,8
i7-3612QM,35,0,2100,3100,4,8
i7-3612QE,35,0,2100,3100,4,8
i7-3610QM,45,0,2300,3300,4,8
i7-3610QE,45,0,2300,3300,4,8
# i7-3500 Mobile Processor Series
i7-3555LE,25,0,2500,3200,2,4
i7-3540M,35,1200,3000,3700,2,4
i7-3537U,17,800,2000,3100,2,4
i7-3520M,35,1200,2900,3600,2,4
i7-3517UE,17,0,1700,2800,2,4
i7-3517U,17,0,1900,3000,2,4
# i5-3600 Mobile Processor Series
i5-3610ME,35,0,2700,3300,2,4
# i5-3400 Mobile Processor Series
i5-3439Y,13,0,1500,2300,2,4
i5-3437U,17,800,1900,2900,2,4
i5-3427U,17,800,1800,2800,2,4
# i5-3300 Mobile Processor Series
i5-3380M,35,1200,2900,3600,2,4
i5-3360M,35,1200,2800,3500,2,4
i5-3340M,35,1200,2700,3400,2,4
i5-3339Y,13,0,1500,2000,2,4
i5-3337U,17,0,1800,2700,2,4
i5-3320M,35,1200,2600,3300,2,4
i5-3317U,17,0,1700,2600,2,4
# i5-3200 Mobile Processor Series
i5-3230M,35,1200,2600,3200,2,4
i5-3210M,35,1200,2500,3100,2,4
# i3-3200 Mobile Processor Series
i3-3239Y,13,0,1400,0,2,4
i3-3227U,17,800,1900,0,2,4
i3-3217UE,17,0,1600,0,2,4
i3-3217U,17,0,1800,0,2,4
# i3-3100 Mobile Processor Series
i3-3130M,35,1200,2600,0,2,4
i3-3120ME,35,0,2400,0,2,4
i3-3120M,35,0,2500,0,2,4
i3-3110M,35,0,2400,0,2,4
)

#
# New Haswell processors with HD-4600 graphics
#

gDesktopHaswellCPUList=(
# Socket 1150 (Standard Power)
i7-4770K,84,00,3500,3900,4,8
i7-4770,84,0,3400,3900,4,8
i5-4670K,84,0,3400,3800,4,4
i5-4670,84,0,3400,3800,4,4
i5-4570,84,0,3200,3600,4,4
i5-4430,84,0,3000,3200,4,4
# Socket 1150 (Low Power)
i7-4770S,65,0,3100,3900,4,8
i7-4770T,45,0,2500,3700,4,8
i7-4765T,35,0,2000,3000,4,8
i5-4670S,65,0,3100,3800,4,4
i5-4670T,45,0,2300,3300,4,4
i5-4570S,65,0,2900,3600,4,4
i5-4570T,35,0,2900,3600,2,4
i5-4430S,65,0,2700,3200,4,4
)

#--------------------------------------------------------------------------------

function _printHeader()
{
    echo '/*'                                                                             >  $gSsdtPR
    echo ' * Intel ACPI Component Architecture'                                           >> $gSsdtPR
    echo ' * AML Disassembler version 20130210-00 [Feb 10 2013]'                          >> $gSsdtPR
    echo ' * Copyright (c) 2000 - 2013 Intel Corporation'                                 >> $gSsdtPR
    echo ' * '                                                                            >> $gSsdtPR
    echo ' * Original Table Header:'                                                      >> $gSsdtPR
    echo ' *     Signature        "SSDT"'                                                 >> $gSsdtPR
    echo ' *     Length           0x0000036A (874)'                                       >> $gSsdtPR
    echo ' *     Revision         0x01'                                                   >> $gSsdtPR
    echo ' *     Checksum         0x00'                                                   >> $gSsdtPR
    echo ' *     OEM ID           "APPLE "'                                               >> $gSsdtPR
    echo ' *     OEM Table ID     "CpuPm"'                                                >> $gSsdtPR
  printf ' *     OEM Revision     '$gRevision' (%d)\n' $gRevision                         >> $gSsdtPR
    echo ' *     Compiler ID      "INTL"'                                                 >> $gSsdtPR
    echo ' *     Compiler Version 0x20130210 (538116624)'                                 >> $gSsdtPR
    echo ' */'                                                                            >> $gSsdtPR
    echo ''                                                                               >> $gSsdtPR
    echo 'DefinitionBlock ("'$gSsdtID'.aml", "SSDT", 1, "APPLE ", "CpuPm", '$gRevision')' >> $gSsdtPR
    echo '{'                                                                              >> $gSsdtPR
}


#--------------------------------------------------------------------------------

function _printExternals()
{
    currentCPU=0;

    while [ $currentCPU -lt $1 ]; do
        echo '    External (\_PR_.'$gProcLabel$currentCPU', DeviceObj)'                 >> $gSsdtPR
        let currentCPU+=1
    done

    echo ''                                                                             >> $gSsdtPR
}


#--------------------------------------------------------------------------------

function _printDebugInfo()
{
    if ((gDebug)); then
        echo '    Store ("ssdtPRGen.sh v'$gScriptVersion'", Debug)'                     >> $gSsdtPR
        echo '    Store ("baseFrequency    : '$gBaseFrequency'", Debug)'                >> $gSsdtPR
        echo '    Store ("frequency        : '$frequency'", Debug)'                     >> $gSsdtPR
        echo '    Store ("logicalCPUs      : '$logicalCPUs'", Debug)'                   >> $gSsdtPR
        echo '    Store ("tdp              : '$gTdp'", Debug)'                          >> $gSsdtPR
        echo '    Store ("packageLength    : '$packageLength'", Debug)'                 >> $gSsdtPR
        echo '    Store ("turboStates      : '$turboStates'", Debug)'                   >> $gSsdtPR
        echo '    Store ("maxTurboFrequency: '$maxTurboFrequency'", Debug)'             >> $gSsdtPR
        echo ''                                                                         >> $gSsdtPR
    fi
}

#--------------------------------------------------------------------------------

function _printProcessorDefinitions()
{
    let currentCPU=0;

    while [ $currentCPU -lt $1 ]; do
        echo '    External (\_PR_.'$gProcLabel$currentCPU', DeviceObj)'                 >> $gSsdtPR
        let currentCPU+=1
    done

    echo ''                                                                             >> $gSsdtPR
}

#--------------------------------------------------------------------------------

function _printScopeStart()
{
    let turboStates=$1
    let packageLength=$2

    # TODO: Remove this when CPUPM for IB works properly!
    let useWorkArounds=0

    echo '    Scope (\_PR.'$gProcLabel'0)'                                              >> $gSsdtPR
    echo '    {'                                                                        >> $gSsdtPR

    #
    # Do we need to create additional (Low Frequency) P-States?
    #

    if [ $gBridgeType -eq $IVY_BRIDGE ];
        then
            let lowFrequencyPStates=($gBaseFrequency/100)-8
            let packageLength=($2+$lowFrequencyPStates)

            printf "        Name (APLF, 0x%02x" $lowFrequencyPStates                    >> $gSsdtPR
            echo ')'                                                                    >> $gSsdtPR

            # TODO: Remove this when CPUPM for IB works properly!
            if ((gIvyWorkAround)); then
                let useWorkArounds=1
            fi
    fi

    #
    # Check number of Turbo states (for IASL optimization).
    #

    if [ $turboStates -eq 0 ];
        then
            # TODO: Remove this when CPUPM for IB works properly!
            if (($useWorkArounds));
                then
                    echo '        Name (APSN, One)'                                     >> $gSsdtPR
                else
                    echo '        Name (APSN, Zero)'                                    >> $gSsdtPR
            fi
        else
          # TODO: Remove this when CPUPM for IB works properly!
          if ((useWorkArounds)); then
              let turboStates+=1
          fi

          printf "        Name (APSN, 0x%02X)\n" $turboStates                           >> $gSsdtPR
    fi

    # TODO: Remove this when CPUPM for IB works properly!
    if (($useWorkArounds)); then
        let packageLength+=1
    fi

  printf "        Name (APSS, Package (0x%02X)\n" $packageLength                        >> $gSsdtPR
    echo '        {'                                                                    >> $gSsdtPR

    # TODO: Remove this when CPUPM for IB works properly!
    if (($useWorkArounds)); then
        let extraF=($maxTurboFrequency+1)
        let maxTDP=($gTdp*1000)
        let extraR=($maxTurboFrequency/100)+1
        echo '            /* Workaround for Ivy Bridge PM bug */'                       >> $gSsdtPR
      printf "            Package (0x06) { 0x%04X, 0x%06X, 0x0A, 0x0A, 0x%02X00, 0x%02X00 },\n" $extraF $maxTDP $extraR $extraR >> $gSsdtPR
    fi
}


#--------------------------------------------------------------------------------

function _printPackages()
{
    let maxTDP=($1*1000)
    local maxNonTurboFrequency=$2
    local frequency=$3

    let minRatio=($gBaseFrequency/100)
    let p1Ratio=($maxNonTurboFrequency/100)
    let ratio=($frequency/100)
    let powerRatio=($p1Ratio-1)

    #
    # Do we need to create additional (Low Frequency) P-States for Ivy bridge?
    #
    if [ $gBridgeType -eq $IVY_BRIDGE ]; then
        let minRatio=8
    fi

    if (($turboStates)); then
        echo '            /* High Frequency Modes (turbo) */'                           >> $gSsdtPR
    fi

    while [ $ratio -ge $minRatio ];
        do
            if [ $frequency -eq $gBaseFrequency ];
                then
                    echo '            /* Low Frequency Mode */'                         >> $gSsdtPR
            fi

            if [ $frequency -eq $maxNonTurboFrequency ];
                then
                    echo '            /* High Frequency Modes (non-turbo) */'           >> $gSsdtPR
            fi

            printf "            Package (0x06) { 0x%04X, " $frequency                   >> $gSsdtPR

            if [ $frequency -lt $maxNonTurboFrequency ];
                then
                    power=$(echo "scale=6;m=((1.1-(($p1Ratio-$powerRatio)*0.00625))/1.1);(($powerRatio/$p1Ratio)*(m*m)*$maxTDP);" | bc | sed -e 's/.[0-9A-F]*$//')
                    let powerRatio-=1
                else
                    power=$maxTDP
            fi

            if [ $frequency -ge $gBaseFrequency ];
                then
                    printf "0x%06X, " $power                                            >> $gSsdtPR
                else
                    printf '    Zero, '                                                 >> $gSsdtPR
            fi

            printf "0x0A, 0x0A, 0x%02X00, 0x%02X00 }" $ratio $ratio                     >> $gSsdtPR

            let ratio-=1
            let frequency-=100

            if [ $ratio -ge $minRatio ];
                then
                    echo ','                                                            >> $gSsdtPR
                else
                    echo ''                                                             >> $gSsdtPR
            fi

        done

    echo '        })'                                                                   >> $gSsdtPR
    echo ''                                                                             >> $gSsdtPR
}


#--------------------------------------------------------------------------------

function _printMethodDSM()
{
    #
    # New stand-alone version of Method _DSM - Copyright (c) 2009 by Master Chief
    #
    echo ''                                                                             >> $gSsdtPR
    echo '        Method (_DSM, 4, NotSerialized)'                                      >> $gSsdtPR
    echo '        {'                                                                    >> $gSsdtPR
    echo '            If (LEqual (Arg2, Zero))'                                         >> $gSsdtPR
    echo '            {'                                                                >> $gSsdtPR
    echo '                Return (Buffer (One)'                                         >> $gSsdtPR
    echo '                {'                                                            >> $gSsdtPR
    echo '                    0x03'                                                     >> $gSsdtPR
    echo '                })'                                                           >> $gSsdtPR
    echo '            }'                                                                >> $gSsdtPR
    echo ''                                                                             >> $gSsdtPR
    #
    # This property is required to get X86Platform[Plugin/Shim].kext loaded.
    #
    echo '            Return (Package (0x02)'                                           >> $gSsdtPR
    echo '            {'                                                                >> $gSsdtPR
    echo '                "plugin-type",'                                               >> $gSsdtPR
    echo '                One'                                                          >> $gSsdtPR
    echo '            })'                                                               >> $gSsdtPR
    echo '        }'                                                                    >> $gSsdtPR
    echo '    }'                                                                        >> $gSsdtPR
}

#--------------------------------------------------------------------------------

function _printScopeACST()
{
    let C1=0
    let C2=0
    let C3=0
    let C6=0
    let C7=0
    local pkgLength=2
    local numberOfCStates=0

#   echo ''                                                                             >> $gSsdtPR
    echo '        Method (ACST, 0, NotSerialized)'                                      >> $gSsdtPR
    echo '        {'                                                                    >> $gSsdtPR

    #
    # Are we injecting C-States for CPU1?
    #
    if [ $1 -eq 1 ];
        then
            # Yes (also used by CPU2, CPU3 and greater).
            let targetCStates=$gACST_CPU1
            latency_C1=0x03E8
            latency_C2=0x94
            latency_C3=0xC6

            if ((gDebug)); then
                echo '            Store ("CPU1 C-States    : '$targetCStates'", Debug)' >> $gSsdtPR
                echo ''                                                                 >> $gSsdtPR
            fi
        else
            #
            # C-States override for Mobile processors (CPU0 only)
            #
            if (($gTypeCPU == $gMobileCPU));
                then
                    echo 'Adjusting C-States for detected (mobile) processor'
                    gACST_CPU0=29
            fi

            let targetCStates=$gACST_CPU0
            latency_C1=Zero
            latency_C3=0xCD
            latency_C6=0xF5
            latency_C7=0xF5

            if ((gDebug)); then
                echo '            Store ("CPU0 C-States    : '$targetCStates'", Debug)' >> $gSsdtPR
                echo ''                                                                 >> $gSsdtPR
            fi
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

    echo '            /* Low Power Modes for '$gProcLabel$1' */'                        >> $gSsdtPR
  printf "            Return (Package (0x%02x)\n" $pkgLength                            >> $gSsdtPR
    echo '            {'                                                                >> $gSsdtPR
    echo '                One,'                                                         >> $gSsdtPR
  printf "                0x%02x,\n" $numberOfCStates                                   >> $gSsdtPR
    echo '                Package (0x04)'                                               >> $gSsdtPR
    echo '                {'                                                            >> $gSsdtPR
    echo '                    ResourceTemplate ()'                                      >> $gSsdtPR
    echo '                    {'                                                        >> $gSsdtPR
    echo '                        Register (FFixedHW,'                                  >> $gSsdtPR
    echo '                            0x01,               // Bit Width'                 >> $gSsdtPR
    echo '                            0x02,               // Bit Offset'                >> $gSsdtPR
  printf "                            0x%016x, // Address\n" $hintCode                  >> $gSsdtPR
    echo '                            0x01,               // Access Size'               >> $gSsdtPR
    echo '                            )'                                                >> $gSsdtPR
    echo '                    },'                                                       >> $gSsdtPR
    echo '                    One,'                                                     >> $gSsdtPR
    echo '                    '$latency_C1','                                           >> $gSsdtPR
    echo '                    0x03E8'                                                   >> $gSsdtPR

    if (($C2)); then
        let hintCode+=0x10
        echo '                },'                                                       >> $gSsdtPR
        echo ''                                                                         >> $gSsdtPR
        echo '                Package (0x04)'                                           >> $gSsdtPR
        echo '                {'                                                        >> $gSsdtPR
        echo '                    ResourceTemplate ()'                                  >> $gSsdtPR
        echo '                    {'                                                    >> $gSsdtPR
        echo '                        Register (FFixedHW,'                              >> $gSsdtPR
        echo '                            0x01,               // Bit Width'             >> $gSsdtPR
        echo '                            0x02,               // Bit Offset'            >> $gSsdtPR
      printf "                            0x%016x, // Address\n" $hintCode              >> $gSsdtPR
        echo '                            0x03,               // Access Size'           >> $gSsdtPR
        echo '                            )'                                            >> $gSsdtPR
        echo '                    },'                                                   >> $gSsdtPR
        echo '                    0x02,'                                                >> $gSsdtPR
        echo '                    '$latency_C2','                                       >> $gSsdtPR
        echo '                    0x01F4'                                               >> $gSsdtPR
    fi

    if (($C3)); then
        let hintCode+=0x10
        local power_C3=0x01F4
        #
        # Is this for CPU1?
        #
        if (($1)); then
            if [[ ${modelID:0:7} == "iMac13," ]];
                then
                    local power_C3=0x15E
                    latency_C3=0xA9
                else
                    local power_C3=0xC8
                    let hintCode+=0x10
            fi
        fi

        echo '                },'                                                       >> $gSsdtPR
        echo ''                                                                         >> $gSsdtPR
        echo '                Package (0x04)'                                           >> $gSsdtPR
        echo '                {'                                                        >> $gSsdtPR
        echo '                    ResourceTemplate ()'                                  >> $gSsdtPR
        echo '                    {'                                                    >> $gSsdtPR
        echo '                        Register (FFixedHW,'                              >> $gSsdtPR
        echo '                            0x01,               // Bit Width'             >> $gSsdtPR
        echo '                            0x02,               // Bit Offset'            >> $gSsdtPR
      printf "                            0x%016x, // Address\n" $hintCode              >> $gSsdtPR
        echo '                            0x03,               // Access Size'           >> $gSsdtPR
        echo '                            )'                                            >> $gSsdtPR
        echo '                    },'                                                   >> $gSsdtPR
        echo '                    0x03,'                                                >> $gSsdtPR
        echo '                    '$latency_C3','                                       >> $gSsdtPR
        echo '                    '$power_C3                                            >> $gSsdtPR
    fi

    if (($C6)); then
        let hintCode+=0x10
        echo '                },'                                                       >> $gSsdtPR
        echo ''                                                                         >> $gSsdtPR
        echo '                Package (0x04)'                                           >> $gSsdtPR
        echo '                {'                                                        >> $gSsdtPR
        echo '                    ResourceTemplate ()'                                  >> $gSsdtPR
        echo '                    {'                                                    >> $gSsdtPR
        echo '                        Register (FFixedHW,'                              >> $gSsdtPR
        echo '                            0x01,               // Bit Width'             >> $gSsdtPR
        echo '                            0x02,               // Bit Offset'            >> $gSsdtPR
      printf "                            0x%016x, // Address\n" $hintCode              >> $gSsdtPR
        echo '                            0x03,               // Access Size'           >> $gSsdtPR
        echo '                            )'                                            >> $gSsdtPR
        echo '                    },'                                                   >> $gSsdtPR
        echo '                    0x06,'                                                >> $gSsdtPR
        echo '                    '$latency_C6','                                       >> $gSsdtPR
        echo '                    0x015E'                                               >> $gSsdtPR
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
        echo '                },'                                                       >> $gSsdtPR
        echo ''                                                                         >> $gSsdtPR
        echo '                Package (0x04)'                                           >> $gSsdtPR
        echo '                {'                                                        >> $gSsdtPR
        echo '                    ResourceTemplate ()'                                  >> $gSsdtPR
        echo '                    {'                                                    >> $gSsdtPR
        echo '                        Register (FFixedHW,'                              >> $gSsdtPR
        echo '                            0x01,               // Bit Width'             >> $gSsdtPR
        echo '                            0x02,               // Bit Offset'            >> $gSsdtPR
      printf "                            0x%016x, // Address\n" $hintCode              >> $gSsdtPR
        echo '                            0x03,               // Access Size'           >> $gSsdtPR
        echo '                            )'                                            >> $gSsdtPR
        echo '                    },'                                                   >> $gSsdtPR
        echo '                    0x07,'                                                >> $gSsdtPR
        echo '                    '$latency_C7','                                       >> $gSsdtPR
        echo '                    0xC8'                                                 >> $gSsdtPR
    fi

    echo '                }'                                                            >> $gSsdtPR
    echo '            })'                                                               >> $gSsdtPR
    echo '        }'                                                                    >> $gSsdtPR

    #
    # We don't need a closing bracket here when we add method _DSM for Ivy Bridge.
    #

    if [ $gBridgeType -eq $SANDY_BRIDGE ]; then
        echo '    }'                                                                    >> $gSsdtPR
	fi
}


#--------------------------------------------------------------------------------

function _printScopeCPUn()
{
    let currentCPU=1;

    while [ $currentCPU -lt $1 ]; do
        echo ''                                                                         >> $gSsdtPR
        echo '    Scope (\_PR.'$gProcLabel$currentCPU')'                                >> $gSsdtPR
        echo '    {'                                                                    >> $gSsdtPR
        echo '        Method (APSS, 0, NotSerialized) { Return (\_PR.'$gProcLabel'0.APSS) }' >> $gSsdtPR

        #
        # IB CPUPM tries to parse/execute CPUn.ACST (see debug data) and thus we add
        # this method, conditionally, since SB CPUPM doesn't seem to care about it.
        #
        if [ $gBridgeType -ge $IVY_BRIDGE ]; then
            if [ $currentCPU -eq 1 ];
                then
                    _printScopeACST 1
                else
                    echo '        Method (ACST, 0, NotSerialized) { Return (\_PR.'$gProcLabel'1.ACST ()) }' >> $gSsdtPR
            fi
        fi

        echo '    }'                                                                    >> $gSsdtPR
        let currentCPU+=1
    done

    echo '}'                                                                            >> $gSsdtPR
}

#--------------------------------------------------------------------------------

function _getModelName()
{
    #
    # Grab 'compatible' property from ioreg (stripped with sed / RegEX magic).
    #
    echo `ioreg -p IODeviceTree -d 2 -k compatible | grep compatible | sed -e 's/ *["=<>]//g' -e 's/compatible//'`
#   echo "iMac13,2"
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
    # Note: This property is checked (cmpb $0x02) in X86PlatformPlugin::configResourceCallback
    #
    echo `ioreg -p IODeviceTree -d 2 -k system-type | grep system-type | sed -e 's/ *[-="<0a-z>]//g'`
}

#--------------------------------------------------------------------------------

function _findIasl()
{
    if ((gCallIasl)); then
        #
        # First we do a quick lookup of iasl (should be there after the first run)
        #
        if [ ! -f /usr/local/bin/iasl ]; then
            echo -e
            echo 'IASL not found. Downloading iasl...'
            sudo curl -o /usr/local/bin/iasl https://raw.github.com/Piker-Alpha/RevoBoot/clang/i386/libsaio/acpi/Tools/iasl
            sudo chmod +x /usr/local/bin/iasl
            echo 'Done.'
        fi

        iasl=/usr/local/bin/iasl
    fi
}

#--------------------------------------------------------------------------------

function _setDestinationPath
{
    #
    # Checking for RevoBoot
    #
    if [ -d /Extra/ACPI ]; then
        gDestinationPath="/Extra/ACPI/"
    fi

    #
    # Checking for Clover
    #
    if [ -d /EFI/ACPI/patched ]; then
        gDestinationPath="/EFI/ACPI/patched/"
    fi
}

#--------------------------------------------------------------------------------

function _getCPUNumberFromBrandString
{
    #
    # Get CPU brandstring
    #
    local brandString=$(echo `sysctl machdep.cpu.brand_string` | sed -e 's/machdep.cpu.brand_string: //')
    #
    # Save default (0) delimiter
    #
    local ifs=$IFS
    #
    # Change delimiter to a space character
    #
    IFS=" "
    #
    # Split brandstring into array (data)
    #
    local data=($brandString)
#   local data=("Intel(R)" "Xeon(R)" "CPU" "E3-1220" "V2" "@" "2.5GHz")
#   local data=("Intel(R)" "Xeon(R)" "CPU" "E3-1220" "@" "2.5GHz")
    #
    # Example from a MacBookPro10,2
    #
    # echo "${data[0]}" # Intel(R)
    # echo "${data[1]}" # Core(TM)
    # echo "${data[2]}" # i5-3210M
    # echo "${data[3]}" # CPU
    # echo "${data[4]}" # @
    # echo "${data[5]}" # 2.50GHz
    #
    # or: "Intel(R) Xeon(R) CPU E3-1230 V2 @ 3.30GHz"
    #
    # echo "${data[0]}" # Intel(R)
    # echo "${data[1]}" # Xeon(R)
    # echo "${data[2]}" # CPU
    # echo "${data[3]}" # E3-12XX
    # echo "${data[4]}" # V2
    # echo "${data[5]}" # @
    # echo "${data[6]}" # 3.30GHz

    #
    # Restore the default delimiter
    #
    IFS=$ifs

    let length=${#data[@]}

    if ((length > 6)); then
        echo 'Warning: Unexpected brandstring > "'${data[@]}'"'
    fi

    if [[ ${data[1]} == "Xeon(R)" && ${data[4]} == "V2" ]];
        then
            gProcessorNumber="${data[3]} ${data[4]}"
        else
            gProcessorNumber="${data[2]}"
    fi

#   echo $gProcessorNumber
}

#--------------------------------------------------------------------------------

function _getCPUDataByProcessorNumber
{
    #
    # Local function definition
    #
    function __searchList()
    {
        local ifs=$IFS
        local targetCPUList=("${!1}")

        for cpuData in "${targetCPUList[@]}"
        do
            IFS=","
            data=($cpuData)

            if [[ ${data[0]} == $gProcessorNumber ]]; then
                gProcessorData="$cpuData"
                let gTypeCPU=$2
                IFS=$ifs
                return
            fi
        done

        IFS=$ifs
    }

    #
    # Local function callers (passing array and cpu type)
    #
    __searchList gDesktopIvyBridgeCPUList[@] $gDesktopCPU

    if (!(($gTypeCPU))); then
        __searchList gMobileIvyBridgeCPUList[@] $gMobileCPU
    fi

    if (!(($gTypeCPU))); then
        __searchList "gServerIvyBridgeCPUList[@]" $gServerCPU
    fi

    if (!(($gTypeCPU))); then
        __searchList "gSandyBridgeCPUList[@]" $gSandyCPU
    fi

    if (!(($gTypeCPU))); then
        __searchList "gDesktopHaswellCPUList[@]" $gHaswellCPU
    fi
}

#--------------------------------------------------------------------------------

function _showLowPowerStates()
{
    #
    # Local function definition
    #
    function __print()
    {
        local mask=1
        local cStates=$1

        printf "Injected C-States for ${gProcLabel}${2} ("

        for state in C1 C2 C3 C6 C7
        do
            if (($cStates & $mask)); then
               if (($mask > 1)); then
                   printf ","
               fi

               printf "$state"
            fi

            let mask=$(($mask << 1))
        done

        echo ')'
    }

    #
    # Local function callers
    #
    __print $gACST_CPU0 0

    if [ $gBridgeType -ge $IVY_BRIDGE ]; then
        __print $gACST_CPU1 1
    fi
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

    if [ $status == 'DPLM' ]; then
        # DPLM  [{lim]  (bytes 00 00 00 00 00)
        # CPU, Idle, IGPU, EGPU and Memory P-State limits
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
			gSystemType=1
			gMacModelIdentifier="iMac12,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-942B5BF58194151B)
			gSystemType=1
			gMacModelIdentifier="iMac12,2"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-8ED6AF5B48C039E1)
			gSystemType=1
			gMacModelIdentifier="Macmini5,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-4BC72D62AD45599E)
			gSystemType=1
			gMacModelIdentifier="Macmini5,2"
			gACST_CPU0=13   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-7BA5B2794B2CDB12)
			gSystemType=1
			gMacModelIdentifier="Macmini5,3"
			gACST_CPU0=13   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-94245B3640C91C81)
			gSystemType=2
			gMacModelIdentifier="MacBookPro8,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-94245A3940C91C80)
			gSystemType=2
			gMacModelIdentifier="MacBookPro8,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-942459F5819B171B)
			gSystemType=2
			gMacModelIdentifier="MacBookPro8,3"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-C08A6BB70A942AC2)
			gSystemType=2
			gMacModelIdentifier="MacBookAir4,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-742912EFDBEE19B3)
			gSystemType=2
			gMacModelIdentifier="MacBookAir4,2"
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
			gSystemType=1
			gMacModelIdentifier="iMac13,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-FC02E91DDD3FA6A4)
			gSystemType=1
			gMacModelIdentifier="iMac13,2"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-031AEE4D24BFF0B1)
			gSystemType=1
			gMacModelIdentifier="Macmini6,1"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-F65AE981FFA204ED)
			gSystemType=1
			gMacModelIdentifier="Macmini6,2"
			gACST_CPU0=13   # C1, C3 and C6
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-4B7AC7E43945597E)
			gSystemType=2
			gMacModelIdentifier="MacBookPro9,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-6F01561E16C75D06)
			gSystemType=2
			gMacModelIdentifier="MacBookPro9,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-C3EC7CD22292981F)
			gSystemType=2
			gMacModelIdentifier="MacBookPro10,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-AFD8A9D944EA4843)
			gSystemType=2
			gMacModelIdentifier="MacBookPro10,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-66F35F19FE2A0D05)
			gSystemType=2
			gMacModelIdentifier="MacBookAir5,1"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;

		Mac-2E6FAB96566FE58C)
			gSystemType=2
			gMacModelIdentifier="MacBookAir5,2"
			gACST_CPU0=29   # C1, C3, C6 and C7
			gACST_CPU1=7    # C1, C2 and C3
			;;
	esac
}

#--------------------------------------------------------------------------------

function _exitWithError()
{
    case "$1" in
        2) echo -e "\nError: 'MaxTurboFrequency' must be in the range of $frequency-gMaxOCFrequency... exiting\n" 1>&2
           exit 2
           ;;
        3) echo -e "\nError: 'TDP' must be in the range of 10-150 Watts... exiting\n" 1>&2
           exit 3
           ;;
        4) echo -e "\nError: 'BridgeType' must be 0, 1 or 2... exiting\n" 1>&2
           exit 4
           ;;
        5) echo -e "\nError: Unknown processor number... exiting\n" 1>&2
           exit 5
           ;;
        *) exit 1
           ;;
    esac
}

#--------------------------------------------------------------------------------

function main()
{
    printf "\nsdtPRGen.sh v$gScriptVersion Copyright (c) 2013 by Pike R. Alpha\n"
    echo   '----------------------------------------------------------------'

    let modelSpecified=0
    let maxTurboFrequency=0

    #
    # Get installed CPU model, set bridge type and default TDP.
    #
    local model=$(_getCPUModel)

    _getCPUNumberFromBrandString

    if [[ $# -eq 1 ]]; then
        if [[ $1 != "" ]]; then
            # Ivy Bridge checks
            if [[ ${1:0:4} == "i3-3" || ${1:0:4} == "i5-3" || ${1:0:4} == "i7-3" || ${1:2:2} == "E3" ]]; then
                let model=0x3A
                let modelSpecified=1
                gProcessorNumber=$1
            fi
            # Haswell checks
            if [[ ${1:0:4} == "i3-4" || ${1:0:4} == "i5-4" || ${1:0:4} == "i7-4" || ${1:2:2} == "E4" ]]; then
                let model=0x4A
                let modelSpecified=1
                gProcessorNumber=$1
            fi
        fi
    fi

    if (($model==0x2A || $model==0x2D)); then
        let gTdp=95
        let gBridgeType=2
        local bridgeTypeString="Sandy Bridge"

        _getCPUDataByProcessorNumber
    fi

    if (($model==0x3A || $model==0x3B)); then
        let gTdp=77
        let gBridgeType=4
        local bridgeTypeString="Ivy Bridge"

        _getCPUDataByProcessorNumber
    fi

    if (($model==0x4A || $model==0x4B)); then
        let gTdp=84
        let gBridgeType=8
        local bridgeTypeString="Haswell"

        _getCPUDataByProcessorNumber
    fi

    _getBoardID

    local modelID=$(_getModelName)
    local cpu_type=$(_getCPUtype)
    local currentSystemType=$(_getSystemType)

    echo "Generating SSDT.dsl for a $modelID [$boardID]"
    echo "$bridgeTypeString Core $gProcessorNumber processor [0x$cpu_type] setup"

    #
    # gTypeCPU is greater than 0 when the processor is found in one of the CPU lists
    #
    if (($gTypeCPU));
        then
            local ifs=$IFS
            IFS=","
            local cpuData=($gProcessorData)
            let gTdp=${cpuData[1]}
            let lfm=${cpuData[2]}
            let frequency=${cpuData[3]}
            let maxTurboFrequency=${cpuData[4]}

            if [ $maxTurboFrequency == 0 ]; then
                let maxTurboFrequency=$frequency
            fi

            let logicalCPUs=${cpuData[6]}
            IFS=$ifs

            echo 'With a maximum TDP of '$gTdp' Watt, as specified by Intel'

            #
            # Check Low Frequency Mode (may be 0 aka still unknown)
            #
            if (($lfm == 0)); then
                echo 'Warning: Low Frequency Mode is 0 (unknown)'

                if (($gTypeCPU == gMobileCPU));
                    then
                        echo 'Now using 1200 MHz for Mobile processor'
                        let gBaseFrequency=1200
                    else
                        echo 'Now using 1600 MHz for Server/Desktop processors'
                        let gBaseFrequency=1600
                fi
            fi
        else
            let logicalCPUs=$(echo `sysctl machdep.cpu.thread_count` | sed -e 's/^machdep.cpu.thread_count: //')
            let frequency=$(echo `sysctl hw.cpufrequency` | sed -e 's/^hw.cpufrequency: //')
            let frequency=($frequency / 1000000)
    fi

    if (!(($modelSpecified))); then
        #
        # One arguments given (should be a number)
        #
        if [[ $# -ge 1 && "$1" =~ ^[0-9]+$ ]];
            then
                if [[ $1 -lt $frequency || $1 -gt $gMaxOCFrequency ]];
                    then
                        _exitWithError $MAX_TURBO_FREQUENCY_ERROR
                    else
                        let maxTurboFrequency=$1
                fi
            else
                _exitWithError $MAX_TURBO_FREQUENCY_ERROR
        fi

        if [[ $# -ge 2 && "$2" =~ ^[0-9]+$ ]];
            then
                if [[ $2 -lt 10 || -gt 150 ]];
                    then
                        _exitWithError $MAX_TDP_ERROR
                    else
                        let gTdp=$2
                        echo "Override value: Max TDP, now using: $gTdp Watt!"
                fi
            else
                _exitWithError $MAX_TDP_ERROR
        fi

        if [[ $# -eq 3 && "$3" =~ ^[0-9]+$ ]];
            then
                case "$3" in
                    0) let gBridgeType=2
                       echo "Override value: CPU type, now using: Sandy Bridge!"
                       ;;
                    1) let gBridgeType=4
                       echo "Override value: CPU type, now using: Ivy Bridge!"
                       ;;
                    2) let gBridgeType=8
                       echo "Override value: CPU type, now using: Haswell!"
                       ;;
                    *) _exitWithError $TARGET_CPU_ERROR
                       ;;
                esac
            else
                _exitWithError $TARGET_CPU_ERROR
        fi
    fi

    echo "Number logical CPU's: $logicalCPUs (Core Frequency: $frequency MHz)"

    #
    # Check maxTurboFrequency
    #
    if [ $maxTurboFrequency == 0 ]; then
        _exitWithError $PROCESSOR_NUMBER_ERROR
    fi

	#
    # Get number of Turbo states.
    #
    let turboStates=$(echo "(($maxTurboFrequency - $frequency) / 100)" | bc)

    #
    # Check number of Turbo states.
    #
    if [ $turboStates -lt 0 ]; then
        let turboStates=0
    fi

    #
    # Report number of Turbo States
    #
    if [ $turboStates -gt 0 ];
        then
            let minTurboFrequency=($frequency+100)
            echo "Number of Turbo States: $turboStates ($minTurboFrequency-$maxTurboFrequency MHz)"

        else
            echo "Number of Turbo States: 0"
    fi

    local packageLength=$(echo "((($maxTurboFrequency - $gBaseFrequency)+100) / 100)" | bc)

    echo "Number of P-States: $packageLength ($gBaseFrequency-$maxTurboFrequency MHz)"

    _printHeader
    _printExternals $logicalCPUs
    _printDebugInfo $logicalCPUs $gTdp $packageLength $turboStates $maxTurboFrequency
    _printScopeStart $turboStates $packageLength
    _printPackages $gTdp $frequency $maxTurboFrequency

    if [ $gBridgeType -eq $SANDY_BRIDGE ];
        then
            local cpuTypeString="06"

            _initSandyBridgeSetup

            _printScopeACST 0
            _printScopeCPUn $logicalCPUs
        else
            local cpuTypeString="07"

            _initIvyBridgeSetup

            _printScopeACST 0
            _printMethodDSM
            _printScopeCPUn $logicalCPUs
    fi

    _showLowPowerStates

    #
    # Some IB CPUPM specific configuration checks
    #
    if [ $gBridgeType -eq $IVY_BRIDGE ];
        then
            if [ ${cpu_type:0:2} -ne $cpuTypeString ]; then
                echo "Warning: 'cpu-type' may be set improperly (0x$cpu_type instead of 0x$cpuTypeString${cpu_type:2:2})"
            fi

            if [ $gSystemType -eq 0 ];
                then
                    echo "Warning: 'board-id' [$boardID] is not supported by $bridgeTypeString PM"
                else
                    if [ "$gMacModelIdentifier" != "$modelID" ]; then
                        echo "Error: board-id [$boardID] and model [$modelID] mismatch"
                    fi

                    if [ $currentSystemType -ne $gSystemType ]; then
                        echo "Warning: 'system-type' may be set improperly ($currentSystemType instead of $gSystemType)"
                    fi
            fi
    fi
}

#==================================== START =====================================

clear

main "$1" $2 $3

_findIasl

if ((gCallIasl)); then
    #
    # Compile SSDT.dsl
    #
    "$iasl" $gSsdtPR

    #
    # Copy SSDT_PR.aml to /Extra/SSDT.aml (example)
    #
    if (($gAutoCopy)); then
        if [ -f ${gPath}/${gSsdtID}.aml ]; then
            echo -e
            read -p "Do you want to copy ${gPath}/${gSsdtID}.aml to ${gDestinationPath}${gDestinationFile}? (y/n)?" choice
            case "$choice" in
                y|Y ) _setDestinationPath
                      sudo cp ${gPath}/${gSsdtID}.aml ${gDestinationPath}${gDestinationFile};;
            esac
        fi
    fi

fi

if ((gCallOpen)); then
    open $gSsdtPR
fi

exit 0
#================================================================================
