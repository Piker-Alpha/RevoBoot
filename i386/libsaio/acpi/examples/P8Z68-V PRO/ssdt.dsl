/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20110316-64 [Mar 16 2011]
 * Copyright (c) 2000 - 2011 Intel Corporation
 * 
 * Disassembly of /ssdt.aml, Mon Jan 21 08:31:48 2013
 *
 * Original Table Header:
 *     Signature        "SSDT"
 *     Length           0x0000031A (794)
 *     Revision         0x01
 *     Checksum         0x77
 *     OEM ID           "APPLE "
 *     OEM Table ID     "general"
 *     OEM Revision     0x00001000 (4096)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20110316 (537985814)
 */

DefinitionBlock ("ssdt.aml", "SSDT", 1, "APPLE ", "general", 0x00001000)
{
    External (HPTC, IntObj)
    External (SBV1, IntObj)
    External (SBV2, IntObj)

    External (\_SB_.PCI0, DeviceObj)
    External (\_SB_.PCI0.RP02, DeviceObj)
    External (\_SB_.PCI0.RP04, DeviceObj)
    External (\_SB_.PCI0.RP05, DeviceObj)
    External (\_SB_.PCI0.RP07, DeviceObj)

    External (\_SB_.PCI0.EHC1, DeviceObj)
    External (\_SB_.PCI0.EHC1.HUBN, DeviceObj)
    External (\_SB_.PCI0.EHC1.HUBN.PR01, DeviceObj)
    External (\_SB_.PCI0.EHC1.HUBN.PR01.PR14, DeviceObj)
    External (\_SB_.PCI0.EHC1.HUBN.PR01.PR15, DeviceObj)
    External (\_SB_.PCI0.EHC1.HUBN.PR01.PR16, DeviceObj)
    External (\_SB_.PCI0.EHC1.HUBN.PR01.PR17, DeviceObj)

    External (\_SB_.PCI0.EHC2, DeviceObj)
    External (\_SB_.PCI0.EHC2.HUBN, DeviceObj)
    External (\_SB_.PCI0.EHC2.HUBN.PR01, DeviceObj)
    External (\_SB_.PCI0.EHC2.HUBN.PR01.PR12, DeviceObj)
    External (\_SB_.PCI0.EHC2.HUBN.PR01.PR13, DeviceObj)

    External (\_SB_.PCI0.LPCB, DeviceObj)
    External (\_SB_.PCI0.LPCB.HPET, DeviceObj)

    Scope (\)
    {
        Scope (_SB)
        {
            Scope (PCI0)
            {
                Scope (EHC2)
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

                    Scope (HUBN)
                    {
                        Scope (PR01)
                        {
                            Scope (PR12)
                            {
                                Alias (SBV1, SDGV)

                                Method (_DSM, 4, Serialized)
                                {
                                    Name (T_0, Zero)
                                    Store (ToInteger (Arg2), T_0)

                                    If (LEqual (T_0, Zero))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    ElseIf (LEqual (T_0, One))
                                    {
                                        If (LNotEqual (SDGV, 0xFF))
                                        {
                                            Return (One)
                                        }
                                    }
                                    ElseIf (LEqual (T_0, 0x02))
                                    {
                                        Return (SDGV)
                                    }

                                    Return (Zero)
                                }
                            }

                            Scope (PR13)
                            {
                                Alias (SBV2, SDGV)

                                Method (_DSM, 4, Serialized)
                                {
                                    Return (^^PR12._DSM (Arg0, Arg1, Arg2, Arg3))
                                }
                            }
                        }
                    }
                }

                Scope (RP02)
                {
                    Device (XHC1)
                    {
                        Name (_ADR, Zero)
                    }
                }

                Scope (RP04)
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

                Scope (RP05)
                {
                    Device (XHC2)
                    {
                        Name (_ADR, Zero)
                    }
                }

                Scope (RP07)
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

                Scope (EHC1)
                {
                    Method (_DSM, 4, NotSerialized)
                    {
                        If (LEqual (Arg2, Zero))
                        {
                           Return (Buffer (One) { 0x03 })
                        }

                        Return (RefOf (^^EHC2.AAPL))
                    }

                    Scope (HUBN)
                    {
                        Scope (PR01)
                        {
                            Scope (PR14)
                            {
                                Alias (SBV1, SDGV)

                                Method (_DSM, 4, Serialized)
                                {
                                    Return (\_SB.PCI0.EHC2.HUBN.PR01.PR12._DSM (Arg0, Arg1, Arg2, Arg3))
                                }
                            }

                            Scope (PR15)
                            {
                                Alias (SBV2, SDGV)

                                Method (_DSM, 4, Serialized)
                                {
                                    Return (\_SB.PCI0.EHC2.HUBN.PR01.PR12._DSM (Arg0, Arg1, Arg2, Arg3))
                                }
                            }

                            Scope (PR16)
                            {
                                Alias (SBV1, SDGV)

                                Method (_DSM, 4, Serialized)
                                {
                                    Return (\_SB.PCI0.EHC2.HUBN.PR01.PR12._DSM (Arg0, Arg1, Arg2, Arg3))
                                }
                            }

                            Scope (PR17)
                            {
                                Alias (SBV2, SDGV)

                                Method (_DSM, 4, Serialized)
                                {
                                    Return (\_SB.PCI0.EHC2.HUBN.PR01.PR12._DSM (Arg0, Arg1, Arg2, Arg3))
                                }
                            }
                        }
                    }
                }

                Scope (LPCB)
                {
                    Scope (HPET)
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
            }
        }
    }
}

