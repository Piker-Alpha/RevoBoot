/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20130214-64 [Mar 24 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Disassembly of ssdt.aml, Mon Mar 25 08:07:55 2013
 *
 * Original Table Header:
 *     Signature        "SSDT"
 *     Length           0x000004FF (1279)
 *     Revision         0x01
 *     Checksum         0x72
 *     OEM ID           "APPLE "
 *     OEM Table ID     "general"
 *     OEM Revision     0x00001000 (4096)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20130214 (538116628)
 */
DefinitionBlock ("ssdt.aml", "SSDT", 1, "APPLE ", "general", 0x00001000)
{
    External (_SB_.PCI0, DeviceObj)
    External (_SB_.PCI0.EHC1, DeviceObj)
    External (_SB_.PCI0.EHC1.HUBN.PR01.PR14, DeviceObj)
    External (_SB_.PCI0.EHC1.HUBN.PR01.PR15, DeviceObj)
    External (_SB_.PCI0.EHC1.HUBN.PR01.PR16, DeviceObj)
    External (_SB_.PCI0.EHC1.HUBN.PR01.PR17, DeviceObj)
    External (_SB_.PCI0.EHC2, DeviceObj)
    External (_SB_.PCI0.EHC2.HUBN.PR01.PR12, DeviceObj)
    External (_SB_.PCI0.EHC2.HUBN.PR01.PR13, DeviceObj)
    External (_SB_.PCI0.LPCB.HPET, DeviceObj)
    External (_SB_.PCI0.RP02, DeviceObj)
    External (_SB_.PCI0.RP04, DeviceObj)
    External (_SB_.PCI0.RP05, DeviceObj)
    External (_SB_.PCI0.RP07, DeviceObj)
    External (HPTC, IntObj)
    External (SBV1, FieldUnitObj)
    External (SBV2, FieldUnitObj)

    Scope (\_SB.PCI0)
    {
        Method (EHCN, 2, NotSerialized)
        {
            Name (T_0, Zero)
            Store (ToInteger (Arg1), T_0)

            If (LEqual (T_0, Zero))
            {
                Return (Buffer (One)
                {
                    0x07
                })
            }
            ElseIf (LEqual (T_0, One))
            {
                If (LNotEqual (Arg0, 0xFF))
                {
                    Return (One)
                }
            }
            ElseIf (LEqual (T_0, 0x02))
            {
                Return (Arg0)
            }

            Return (Zero)
        }
    }

    Scope (\_SB.PCI0.EHC2)
    {
        Name (AAPL, Package (0x0B)
        {
            "AAPL,current-available", 
            0x0834, 
            "AAPL,current-extra", 
            0x0898, 
            "AAPL,current-extra-in-sleep", 
            0x0640, 
            "AAPL,max-port-current-in-sleep", 
            0x0834, 
            "AAPL,device-internal", 
            0x02, 
            Buffer (One) { 0x00 }
        })

        Method (_DSM, 4, NotSerialized)
        {
            If (LEqual (Arg2, Zero))
            {
                Return (Buffer (One) { 0x03 })
            }

            Return (RefOf (AAPL))
        }
    }

    Scope (\_SB.PCI0.EHC2.HUBN.PR01.PR12)
    {
        Method (_DSM, 4, Serialized)
        {
            Return (\_SB.PCI0.EHCN (SBV1, Arg2))
        }
    }

    Scope (\_SB.PCI0.EHC2.HUBN.PR01.PR13)
    {
        Method (_DSM, 4, Serialized)
        {
            Return (\_SB.PCI0.EHCN (SBV2, Arg2))
        }
    }

    Scope (\_SB.PCI0.RP02)
    {
        Device (XHC1)
        {
            Name (_ADR, Zero)
        }
    }

    Scope (\_SB.PCI0.RP04)
    {
        Device (JMB0)
        {
            Name (_ADR, Zero)
            OperationRegion (CF40, PCI_Config, 0x40, 0x04)
            Field (CF40, ByteAcc, NoLock, Preserve)
            {
                CHE0,   1, 
                MULT,   1, 
                    ,   1, 
                CAB0,   1, 
                CHE1,   1, 
                Offset (0x01), 
                AHEN,   1, 
                    ,   3, 
                PRT0,   1, 
                AHM0,   1, 
                PRT1,   1, 
                AHM1,   1, 
                CF42,   6, 
                SWAP,   1, 
                PATA,   1, 
                    ,   6, 
                WTEN,   1, 
                Offset (0x04)
            }
        }

        Device (JMB1)
        {
            Name (_ADR, One)
            OperationRegion (CF40, PCI_Config, 0x40, 0x04)
            Field (CF40, ByteAcc, NoLock, Preserve)
            {
                CHE0,   1, 
                MULT,   1, 
                    ,   1, 
                CAB0,   1, 
                CHE1,   1, 
                Offset (0x01), 
                AHEN,   1, 
                    ,   3, 
                PRT0,   1, 
                AHM0,   1, 
                PRT1,   1, 
                AHM1,   1, 
                CF42,   6, 
                SWAP,   1, 
                PATA,   1, 
                    ,   6, 
                WTEN,   1, 
                Offset (0x04)
            }
        }
    }

    Scope (\_SB.PCI0.RP05)
    {
        Device (XHC2)
        {
            Name (_ADR, Zero)
        }
    }

    Scope (\_SB.PCI0.RP07)
    {
        Device (FWBR)
        {
            Name (_ADR, Zero)
            Name (_PRW, Package (0x02) { 0x0B, 0x04 })
            Name (_PRT, Package (0x0C)
            {
                Package (0x04) { 0xFFFF,     Zero, Zero, 0x12 },
                Package (0x04) { 0xFFFF,      One, Zero, 0x13 },
                Package (0x04) { 0xFFFF,     0x02, Zero, 0x10 },
                Package (0x04) { 0xFFFF,     0x03, Zero, 0x11 },
                Package (0x04) { 0x0001FFFF, Zero, Zero, 0x13 },
                Package (0x04) { 0x0001FFFF,  One, Zero, 0x10 },
                Package (0x04) { 0x0001FFFF, 0x02, Zero, 0x11 },
                Package (0x04) { 0x0001FFFF, 0x03, Zero, 0x12 },
                Package (0x04) { 0x0002FFFF, Zero, Zero, 0x11 },
                Package (0x04) { 0x0002FFFF,  One, Zero, 0x12 },
                Package (0x04) { 0x0002FFFF, 0x02, Zero, 0x13 },
                Package (0x04) { 0x0002FFFF, 0x03, Zero, 0x10 }
            })

            Device (FRWR)
            {
                Name (_ADR, 0x00020000)
            }
        }
    }

    Scope (\_SB.PCI0.EHC1)
    {
        Method (_DSM, 4, NotSerialized)
        {
            If (LEqual (Arg2, Zero))
            {
                Return (Buffer (One) { 0x03 })
            }

            Return (RefOf (\_SB.PCI0.EHC2.AAPL))
        }
    }

    Scope (\_SB.PCI0.EHC1.HUBN.PR01.PR14)
    {
        Method (_DSM, 4, Serialized)
        {
            Return (\_SB.PCI0.EHCN (SBV1, Arg2))
        }
    }

    Scope (\_SB.PCI0.EHC1.HUBN.PR01.PR15)
    {
        Method (_DSM, 4, Serialized)
        {
            Return (\_SB.PCI0.EHCN (SBV2, Arg2))
        }
    }

    Scope (\_SB.PCI0.EHC1.HUBN.PR01.PR16)
    {
        Method (_DSM, 4, Serialized)
        {
            Return (\_SB.PCI0.EHCN (SBV1, Arg2))
        }
    }

    Scope (\_SB.PCI0.EHC1.HUBN.PR01.PR17)
    {
        Method (_DSM, 4, Serialized)
        {
            Return (\_SB.PCI0.EHCN (SBV2, Arg2))
        }
    }

    Scope (\_SB.PCI0.LPCB.HPET)
    {
        OperationRegion (RCRB, SystemMemory, HPTC, One)
        Field (RCRB, ByteAcc, Lock, Preserve)
        {
                ,   7, 
            HPAE,   1
        }

        Method (_INI, 0, NotSerialized)
        {
            Store (One, HPAE)
        }
    }
}

