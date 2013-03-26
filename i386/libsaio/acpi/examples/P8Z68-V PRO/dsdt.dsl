/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20110316-64 [Mar 16 2011]
 * Copyright (c) 2000 - 2011 Intel Corporation
 * 
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x00001EE2 (7906)
 *     Revision         0x02
 *     Checksum         0x7F
 *     OEM ID           "APPLE"
 *     OEM Table ID     "Macmini"
 *     OEM Revision     0x00050001 (327681)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20110316 (537985814)
 */

DefinitionBlock ("dsdt.aml", "DSDT", 2, "APPLE", "Macmini", 0x00050001)
{
    Name (HPTB, 0xFED00000)
    Name (SRCB, 0xFED1C000)
    Name (HPTC, 0xFED1F404)
    Name (MCHB, 0xFED10000)
    Name (EGPB, 0xFED19000)
    Name (PEBS, 0xF8000000)
    Name (PELN, 0x04000000)
    Name (VTBS, 0xFED90000)
    Name (VTLN, 0x4000)
    Name (LAPB, 0xFEE00000)
    Name (APCB, 0xFEC00000)
    Name (TCBR, 0xFED08000)
    Name (PMBS, 0x0400)
    Name (SMCR, 0x0430)
    Name (GPBS, 0x0500)
    Name (RCLN, 0x4000)
    Name (TCLT, 0x1000)
    Name (OPRE, 0xDCBB2E18)

    OperationRegion (GNVS, SystemMemory, OPRE, 0x0163)
    Field (GNVS, AnyAcc, Lock, Preserve)
    {
                Offset (0x0B), 
        P80D,   32,
                Offset (0x3C), 
        IGDS,   8,
                Offset (0xAA), 
        ASLB,   32,
                Offset (0xEF),
        L01C,   8,
                Offset (0x15F), 
        TBAB,   32, 
    }

    OperationRegion (PMIO, SystemIO, PMBS, 0x43)
    Field (PMIO, ByteAcc, NoLock, Preserve)
    {
                Offset (0x42), 
            ,   1, 
        GPEC,   1
    }

    OperationRegion (GPIO, SystemIO, GPBS, 0x10)
    Field (GPIO, ByteAcc, NoLock, Preserve)
    {
                Offset (0x0F), 
        GP24,   1, 
            ,   2, 
        GP27,   1
    }

    OperationRegion (DEB0, SystemIO, 0x80, One)
    Field (DEB0, ByteAcc, NoLock, Preserve)
    {
        DBG8,   8
    }

    OperationRegion (PRT0, SystemIO, 0x80, 0x04)
    Field (PRT0, DWordAcc, Lock, Preserve)
    {
        P80H,   32
    }

    Method (_PIC, 1, NotSerialized)
    {
    }

    Scope (_PR)
    {
        Processor (CPU0, 0x01, 0x00000410, 0x06) {}
        Processor (CPU1, 0x02, 0x00000410, 0x06) {}
        Processor (CPU2, 0x03, 0x00000410, 0x06) {}
        Processor (CPU3, 0x04, 0x00000410, 0x06) {}
    }

    Scope (_SB)
    {
        OperationRegion (IOB2, SystemIO, 0xB2, One)
        Field (IOB2, ByteAcc, NoLock, Preserve)
        {
            SMIC,   8
        }

        Device (PCI0)
        {
            Name (_ADR, Zero)
            Name (_UID, Zero)
            Name (_BBN, Zero)
            Name (_CID, EisaId ("PNP0A03"))
            Name (_HID, EisaId ("PNP0A08"))
            Name (_PRT, Package (0x24)
            {
                Package (0x04) { 0x001FFFFF, Zero, Zero, 0x15 },
                Package (0x04) { 0x001FFFFF,  One, Zero, 0x13 },
                Package (0x04) { 0x001FFFFF, 0x02, Zero, 0x12 },
                Package (0x04) { 0x001FFFFF, 0x03, Zero, 0x10 },
                Package (0x04) { 0x0014FFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x001DFFFF,  One, Zero, 0x13 },
                Package (0x04) { 0x001DFFFF, 0x02, Zero, 0x10 },
                Package (0x04) { 0x001DFFFF, 0x03, Zero, 0x12 },
                Package (0x04) { 0x001DFFFF, Zero, Zero, 0x17 },
                Package (0x04) { 0x001AFFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x001AFFFF,  One, Zero, 0x15 },
                Package (0x04) { 0x001AFFFF, 0x02, Zero, 0x12 },
                Package (0x04) { 0x001AFFFF, 0x03, Zero, 0x13 },
                Package (0x04) { 0x001BFFFF, Zero, Zero, 0x16 },
                Package (0x04) { 0x0016FFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x0016FFFF,  One, Zero, 0x13 },
                Package (0x04) { 0x0016FFFF, 0x02, Zero, 0x12 },
                Package (0x04) { 0x0016FFFF, 0x03, Zero, 0x11 },
                Package (0x04) { 0x001CFFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x001CFFFF,  One, Zero, 0x11 },
                Package (0x04) { 0x001CFFFF, 0x02, Zero, 0x12 },
                Package (0x04) { 0x001CFFFF, 0x03, Zero, 0x13 },
                Package (0x04) { 0x0001FFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x0001FFFF,  One, Zero, 0x11 },
                Package (0x04) { 0x0001FFFF, 0x02, Zero, 0x12 },
                Package (0x04) { 0x0001FFFF, 0x03, Zero, 0x13 },
                Package (0x04) { 0x0006FFFF, Zero, Zero, 0x13 },
                Package (0x04) { 0x0006FFFF,  One, Zero, 0x10 },
                Package (0x04) { 0x0006FFFF, 0x02, Zero, 0x11 },
                Package (0x04) { 0x0006FFFF, 0x03, Zero, 0x12 },
                Package (0x04) { 0x0004FFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x0004FFFF, One,  Zero, 0x11 },
                Package (0x04) { 0x0004FFFF, 0x02, Zero, 0x12 },
                Package (0x04) { 0x0004FFFF, 0x03, Zero, 0x13 },
                Package (0x04) { 0x0002FFFF, Zero, Zero, 0x10 },
                Package (0x04) { 0x0019FFFF, Zero, Zero, 0x14 }
            })
            OperationRegion (HBUS, PCI_Config, Zero, 0x0100)
            Field (HBUS, DWordAcc, NoLock, Preserve)
            {
                        Offset (0x40), 
                EPEN,   1, 
                    ,   11, 
                EPBR,   20, 
                        Offset (0x48), 
                MHEN,   1, 
                    ,   14, 
                MHBR,   17, 
                        Offset (0x50), 
                GCLK,   1, 
                        Offset (0x54), 
                D0EN,   1, 
                        Offset (0x60), 
                PXEN,   1, 
                PXSZ,   2, 
                    ,   23, 
                PXBR,   6, 
                        Offset (0x68), 
                DIEN,   1, 
                    ,   11, 
                DIBR,   20, 
                        Offset (0x70), 
                    ,   20, 
                MEBR,   12, 
                        Offset (0x80), 
                    ,   4, 
                PM0H,   2, 
                        Offset (0x81), 
                PM1L,   2, 
                    ,   2, 
                PM1H,   2, 
                        Offset (0x82), 
                PM2L,   2, 
                    ,   2, 
                PM2H,   2, 
                        Offset (0x83), 
                PM3L,   2, 
                    ,   2, 
                PM3H,   2, 
                        Offset (0x84), 
                PM4L,   2, 
                    ,   2, 
                PM4H,   2, 
                        Offset (0x85), 
                PM5L,   2, 
                    ,   2, 
                PM5H,   2, 
                        Offset (0x86), 
                PM6L,   2, 
                    ,   2, 
                PM6H,   2, 
                        Offset (0x87), 
                        Offset (0xA8), 
                    ,   20, 
                TUUD,   19, 
                        Offset (0xBC), 
                    ,   20, 
                TLUD,   12, 
                        Offset (0xC8), 
                    ,   7, 
                HTSE,   1
            }

            OperationRegion (MCHT, SystemMemory, 0xFED10000, 0x1100)
            Field (MCHT, ByteAcc, NoLock, Preserve)
            {
            }

            Name (BUF0, ResourceTemplate ()
            {
                WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
                    0x0000,             // Granularity
                    0x0000,             // Range Minimum
                    0x00FF,             // Range Maximum
                    0x0000,             // Translation Offset
                    0x0100,             // Length
                    ,, _Y00)
                DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                    0x00000000,         // Granularity
                    0x00000000,         // Range Minimum
                    0x00000CF7,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00000CF8,         // Length
                    ,, , TypeStatic)
                IO (Decode16,
                    0x0CF8,             // Range Minimum
                    0x0CF8,             // Range Maximum
                    0x01,               // Alignment
                    0x08,               // Length
                    )
                DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                    0x00000000,         // Granularity
                    0x00000D00,         // Range Minimum
                    0x0000FFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x0000F300,         // Length
                    ,, , TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000A0000,         // Range Minimum
                    0x000BFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00020000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000C0000,         // Range Minimum
                    0x000C3FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y01, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000C4000,         // Range Minimum
                    0x000C7FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y02, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000C8000,         // Range Minimum
                    0x000CBFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y03, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000CC000,         // Range Minimum
                    0x000CFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y04, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000D0000,         // Range Minimum
                    0x000D3FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y05, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000D4000,         // Range Minimum
                    0x000D7FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y06, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000D8000,         // Range Minimum
                    0x000DBFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y07, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000DC000,         // Range Minimum
                    0x000DFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y08, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000E0000,         // Range Minimum
                    0x000E3FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y09, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000E4000,         // Range Minimum
                    0x000E7FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y0A, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000E8000,         // Range Minimum
                    0x000EBFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y0B, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000EC000,         // Range Minimum
                    0x000EFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, _Y0C, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000F0000,         // Range Minimum
                    0x000FFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00010000,         // Length
                    ,, _Y0D, AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x00000000,         // Range Minimum
                    0xFEAFFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0xFEB00000,         // Length
                    ,, _Y0E, AddressRangeMemory, TypeStatic)
                QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x0000000000000000, // Granularity
                    0x0000000000010000, // Range Minimum
                    0x000000000001FFFF, // Range Maximum
                    0x0000000000000000, // Translation Offset
                    0x0000000000010000, // Length
                    ,, _Y0F, AddressRangeMemory, TypeStatic)
            })
            Method (_CRS, 0, Serialized)
            {
                CreateWordField (BUF0, ^_Y00._MAX, PBMX)
                Store (Subtract (ShiftRight (PELN, 0x14), 0x02), PBMX)
                CreateWordField (BUF0, ^_Y00._LEN, PBLN)
                Store (Subtract (ShiftRight (PELN, 0x14), One), PBLN)
                If (PM1L)
                {
                    CreateDWordField (BUF0, ^_Y01._LEN, C0LN)
                    Store (Zero, C0LN)
                }

                If (LEqual (PM1L, One))
                {
                    CreateBitField (BUF0, ^_Y01._RW, C0RW)
                    Store (Zero, C0RW)
                }

                If (PM1H)
                {
                    CreateDWordField (BUF0, ^_Y02._LEN, C4LN)
                    Store (Zero, C4LN)
                }

                If (LEqual (PM1H, One))
                {
                    CreateBitField (BUF0, ^_Y02._RW, C4RW)
                    Store (Zero, C4RW)
                }

                If (PM2L)
                {
                    CreateDWordField (BUF0, ^_Y03._LEN, C8LN)
                    Store (Zero, C8LN)
                }

                If (LEqual (PM2L, One))
                {
                    CreateBitField (BUF0, ^_Y03._RW, C8RW)
                    Store (Zero, C8RW)
                }

                If (PM2H)
                {
                    CreateDWordField (BUF0, ^_Y04._LEN, CCLN)
                    Store (Zero, CCLN)
                }

                If (LEqual (PM2H, One))
                {
                    CreateBitField (BUF0, ^_Y04._RW, CCRW)
                    Store (Zero, CCRW)
                }

                If (PM3L)
                {
                    CreateDWordField (BUF0, ^_Y05._LEN, D0LN)
                    Store (Zero, D0LN)
                }

                If (LEqual (PM3L, One))
                {
                    CreateBitField (BUF0, ^_Y05._RW, D0RW)
                    Store (Zero, D0RW)
                }

                If (PM3H)
                {
                    CreateDWordField (BUF0, ^_Y06._LEN, D4LN)
                    Store (Zero, D4LN)
                }

                If (LEqual (PM3H, One))
                {
                    CreateBitField (BUF0, ^_Y06._RW, D4RW)
                    Store (Zero, D4RW)
                }

                If (PM4L)
                {
                    CreateDWordField (BUF0, ^_Y07._LEN, D8LN)
                    Store (Zero, D8LN)
                }

                If (LEqual (PM4L, One))
                {
                    CreateBitField (BUF0, ^_Y07._RW, D8RW)
                    Store (Zero, D8RW)
                }

                If (PM4H)
                {
                    CreateDWordField (BUF0, ^_Y08._LEN, DCLN)
                    Store (Zero, DCLN)
                }

                If (LEqual (PM4H, One))
                {
                    CreateBitField (BUF0, ^_Y08._RW, DCRW)
                    Store (Zero, DCRW)
                }

                If (PM5L)
                {
                    CreateDWordField (BUF0, ^_Y09._LEN, E0LN)
                    Store (Zero, E0LN)
                }

                If (LEqual (PM5L, One))
                {
                    CreateBitField (BUF0, ^_Y09._RW, E0RW)
                    Store (Zero, E0RW)
                }

                If (PM5H)
                {
                    CreateDWordField (BUF0, ^_Y0A._LEN, E4LN)
                    Store (Zero, E4LN)
                }

                If (LEqual (PM5H, One))
                {
                    CreateBitField (BUF0, ^_Y0A._RW, E4RW)
                    Store (Zero, E4RW)
                }

                If (PM6L)
                {
                    CreateDWordField (BUF0, ^_Y0B._LEN, E8LN)
                    Store (Zero, E8LN)
                }

                If (LEqual (PM6L, One))
                {
                    CreateBitField (BUF0, ^_Y0B._RW, E8RW)
                    Store (Zero, E8RW)
                }

                If (PM6H)
                {
                    CreateDWordField (BUF0, ^_Y0C._LEN, ECLN)
                    Store (Zero, ECLN)
                }

                If (LEqual (PM6H, One))
                {
                    CreateBitField (BUF0, ^_Y0C._RW, ECRW)
                    Store (Zero, ECRW)
                }

                If (PM0H)
                {
                    CreateDWordField (BUF0, ^_Y0D._LEN, F0LN)
                    Store (Zero, F0LN)
                }

                If (LEqual (PM0H, One))
                {
                    CreateBitField (BUF0, ^_Y0D._RW, F0RW)
                    Store (Zero, F0RW)
                }

                CreateDWordField (BUF0, ^_Y0E._MIN, M1MN)
                CreateDWordField (BUF0, ^_Y0E._MAX, M1MX)
                CreateDWordField (BUF0, ^_Y0E._LEN, M1LN)
                ShiftLeft (TLUD, 0x14, M1MN)
                Add (Subtract (M1MX, M1MN), One, M1LN)
                CreateQWordField (BUF0, ^_Y0F._LEN, MSLN)
                Store (Zero, MSLN)

                Return (BUF0)
            }

            Device (PEG0)
            {
                Name (_ADR, 0x00010000)
                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x10 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x11 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x12 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x13 }
                })
                Device (PEGP)
                {
                    Name (_ADR, 0xFFFF)
                }
            }

            Device (PEG1)
            {
                Name (_ADR, 0x00010001)
                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x11 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x12 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x13 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x10 }
                })
            }

            Device (PEG2)
            {
                Name (_ADR, 0x00010002)
                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x12 },
                    Package (0x04) { 0xFFFF,  One, Zero, 0x13 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x10 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x11 }
                })
            }

            Device (IGPU)
            {
                Name (_ADR, 0x00020000)
                Device (^^MEM2)
                {
                    Name (_HID, EisaId ("PNP0C01"))
                    Name (_UID, 0x02)
                    Name (_CRS, ResourceTemplate ()
                    {
                        Memory32Fixed (ReadWrite, 0x20000000, 0x00200000, )
                        Memory32Fixed (ReadWrite, 0x40000000, 0x00200000, )
                    })
                    Method (_STA, 0, NotSerialized)
                    {
                        If (IGDS) // Uncore enabled?
                        {
                            Return (0x0F)
                        }

                        Return (Zero)
                    }
                }
            }

            Device (PEG3)
            {
                Name (_ADR, 0x00060000)
                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x13 },
                    Package (0x04) { 0xFFFF,  One, Zero, 0x10 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x11 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x12 }
                })
            }

            Device (GIGE)
            {
                Name (_ADR, 0x00190000)
                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
            }

            Device (RP01)
            {
                Name (_ADR, 0x001C0000)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x10 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x11 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x12 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x13 }
                })
            }

            Device (RP02)
            {
                Name (_ADR, 0x001C0001)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x11 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x12 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x13 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x10 }
                })
            }

            Device (RP03)
            {
                Name (_ADR, 0x001C0002)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x12 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x13 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x10 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x11 }
                })
            }

            Device (RP04)
            {
                Name (_ADR, 0x001C0003)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x13 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x10 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x11 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x12 }
                })
            }

            Device (RP05)
            {
                Name (_ADR, 0x001C0004)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x10 },
                    Package (0x04) { 0xFFFF,  One, Zero, 0x11 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x12 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x13}
				})
            }

            Device (RP06)
            {
                Name (_ADR, 0x001C0005)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x11 },
                    Package (0x04) { 0xFFFF,  One, Zero, 0x12 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x13 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x10 }
                })
            }

            Device (EHC2)
            {
                Name (_ADR, 0x001A0000)
                Name (_S3D, 0x02)
				Name (_S4D, 0x02)

                OperationRegion (PWKE, PCI_Config, 0x62, One)	// PWAKE_CAP—Port Wake Capability Register (datasheet 324645-006, page 652)
                Field (PWKE, ByteAcc, NoLock, Preserve)
                {
                     PWI,   1,									// Port Wake Implemented
                    PWUC,   7									// Port Wake Up Capability Mask
                }

                Method (_PSW, 1, NotSerialized)
                {
                    Multiply (0x7E, Arg0, PWUC)					// Set bit 0-8 based on Arg0 (0 disable- or 1 enable wake capabilities).
                }

                Device (HUBN)
                {
                    Name (_ADR, Zero)
                    Device (PR01)
                    {
                        Name (_ADR, One)
                        Name (_UPC, Package (0x04) { 0xFF, Zero, Zero, Zero })
                        Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0x30, 0x1C, Zero, Zero, Zero, Zero, Zero, Zero }})
                        Device (PR11)
                        {
                            Name (_ADR, One)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1C, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR12)
                        {
                            Name (_ADR, 0x02)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1D, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR13)
                        {
                            Name (_ADR, 0x03)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1D, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR14)
                        {
                            Name (_ADR, 0x04)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR15)
                        {
                            Name (_ADR, 0x05)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xB1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR16)
                        {
                            Name (_ADR, 0x06)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xB1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }
                    }
                }

                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
            }

            Device (HDEF)
            {
                Name (_ADR, 0x001B0000)
                Name (_PRW, Package (0x02) { 0x0D, 0x04 })
            }

            Device (RP07)
            {
                Name (_ADR, 0x001C0006)
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x12 },
                    Package (0x04) { 0xFFFF,  One, Zero, 0x13 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x10 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x11 }
                })
            }

            Device (RP08)
            {
                Name (_ADR, 0x001C0007)
                Name (_PRW, Package (0x02) { 0x09, 0x04 })
                Name (_PRT, Package (0x04)
                {
                    Package (0x04) { 0xFFFF, Zero, Zero, 0x13 }, 
                    Package (0x04) { 0xFFFF,  One, Zero, 0x10 },
                    Package (0x04) { 0xFFFF, 0x02, Zero, 0x11 },
                    Package (0x04) { 0xFFFF, 0x03, Zero, 0x12 }
                })
            }

            Device (EHC1)
            {
                Name (_ADR, 0x001D0000)
                Name (_S4D, 0x02)
                Name (_S3D, 0x02)

                Device (HUBN)
                {
                    Name (_ADR, Zero)
                    Device (PR01)
                    {
                        Name (_ADR, One)
                        Name (_UPC, Package (0x04) { 0xFF, Zero, Zero, Zero })
                        Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0x30, 0x1C, Zero, Zero, Zero, Zero, Zero, Zero }})
                        Device (PR11)
                        {
                            Name (_ADR, One)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1C, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR12)
                        {
                            Name (_ADR, 0x02)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1D, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR13)
                        {
                            Name (_ADR, 0x03)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1D, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR14)
                        {
                            Name (_ADR, 0x04)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xE1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR15)
                        {
                            Name (_ADR, 0x05)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xB1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR16)
                        {
                            Name (_ADR, 0x06)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xB1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR17)
                        {
                            Name (_ADR, 0x07)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xB1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }

                        Device (PR18)
                        {
                            Name (_ADR, 0x08)
                            Name (_UPC, Package (0x04) { 0xFF, 0xFF, Zero, Zero })
                            Name (_PLD, Package (One) { Buffer (0x10) { 0x81, Zero, Zero, Zero, Zero, Zero, Zero, Zero, 0xB1, 0x1E, Zero, Zero, Zero, Zero, Zero, Zero }})
                        }
                    }
                }
            }

            Device (P0P1)
            {
                Name (_ADR, 0x001E0000)
                Name (_PRW, Package (0x02) { 0x0B, 0x04 })
                Name (_PRT, Package (0x08)
                {
                    Package (0x04) { 0x0002FFFF, Zero, Zero, 0x12 }, 
                    Package (0x04) { 0x0002FFFF,  One, Zero, 0x13 },
                    Package (0x04) { 0x0002FFFF, 0x02, Zero, 0x11 },
                    Package (0x04) { 0x0002FFFF, 0x03, Zero, 0x10 },
                    Package (0x04) { 0x0003FFFF, Zero, Zero, 0x13 },
                    Package (0x04) { 0x0003FFFF,  One, Zero, 0x12 },
                    Package (0x04) { 0x0003FFFF, 0x02, Zero, 0x15 },
                    Package (0x04) { 0x0003FFFF, 0x03, Zero, 0x16 }
                })
            }

            Device (LPCB)
            {
                Name (_ADR, 0x001F0000)
                OperationRegion (LPC1, PCI_Config, 0xAE, One)
                Field (LPC1, AnyAcc, NoLock, Preserve)
                {
                    XUSB,   1
                }

                OperationRegion (LPC0, PCI_Config, 0xF0, 0xC0)
                Field (LPC0, AnyAcc, NoLock, Preserve)
                {
                    RAEN,   1, 
                        ,   13, 
                    RCBA,   18
                }

                OperationRegion (SMIE, SystemIO, PMBS, 0x02)	// PM1_STS—Power Management 1 Status Register ().
                Field (SMIE, ByteAcc, NoLock, Preserve)
                {
                        ,   10, 
                    RTCS,   1									// Bit 10 - RTC Status (see page 520).
                }

                OperationRegion (SLPR, SystemIO, SMCR, 0x08)
                Field (SLPR, ByteAcc, NoLock, Preserve)
                {
                        ,   4, 
                    SLPE,   1, 
                        ,   31, 
                    SLPX,   1
                }

                OperationRegion (GPBX, SystemIO, GPBS, 0x1C)
                Field (GPBX, ByteAcc, NoLock, Preserve)
                {
                            Offset (0x18), 
                        ,   27, 
                    PLED,   1
                }

                Method (SWAK, 1, NotSerialized)
                {
                    Store (Zero, SLPE)
                    If (LNot (RTCS))
					{
                        Notify (PWRB, 0x02)
                    }
                }

                Device (FWHD)
                {
                    Name (_HID, EisaId ("INT0800"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        Memory32Fixed (ReadOnly, 0xFF000000, 0x01000000, )
                    })
                }

                Device (HPET)
                {
                    Name (_HID, EisaId ("PNP0103"))
                    Name (_UID, Zero)
                    Name (_STA, 0x0F)
                    Name (_CRS, ResourceTemplate ()
                    {
                        Memory32Fixed (ReadWrite, 0xFED00000, 0x00000400, )
                    })
                }

                Device (IPIC)
                {
                    Name (_HID, EisaId ("PNP0000"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16, 0x0020, 0x0020, 0x01, 0x02, )
                        IO (Decode16, 0x0024, 0x0024, 0x01, 0x02, )
                        IO (Decode16, 0x0028, 0x0028, 0x01, 0x02, )
                        IO (Decode16, 0x002C, 0x002C, 0x01, 0x02, )
                        IO (Decode16, 0x0030, 0x0030, 0x01, 0x02, )
                        IO (Decode16, 0x0034, 0x0034, 0x01, 0x02, )
                        IO (Decode16, 0x0038, 0x0038, 0x01, 0x02, )
                        IO (Decode16, 0x003C, 0x003C, 0x01, 0x02, )
                        IO (Decode16, 0x00A0, 0x00A0, 0x01, 0x02, )
                        IO (Decode16, 0x00A4, 0x00A4, 0x01, 0x02, )
                        IO (Decode16, 0x00A8, 0x00A8, 0x01, 0x02, )
                        IO (Decode16, 0x00AC, 0x00AC, 0x01, 0x02, )
                        IO (Decode16, 0x00B0, 0x00B0, 0x01, 0x02, )
                        IO (Decode16, 0x00B4, 0x00B4, 0x01, 0x02, )
                        IO (Decode16, 0x00B8, 0x00B8, 0x01, 0x02, )
                        IO (Decode16, 0x00BC, 0x00BC, 0x01, 0x02, )
                        IO (Decode16, 0x04D0, 0x04D0, 0x01, 0x02, )
                        IRQNoFlags () {2}
                    })
                }

                Device (LDRC)
                {
                    Name (_HID, EisaId ("PNP0C02"))
                    Name (_UID, 0x02)
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16, 0x002E, 0x002E, 0x01, 0x02, )
                        IO (Decode16, 0x004E, 0x004E, 0x01, 0x02, )
                        IO (Decode16, 0x0061, 0x0061, 0x01, 0x01, )
                        IO (Decode16, 0x0063, 0x0063, 0x01, 0x01, )
                        IO (Decode16, 0x0065, 0x0065, 0x01, 0x01, )
                        IO (Decode16, 0x0067, 0x0067, 0x01, 0x01, )
                        IO (Decode16, 0x0070, 0x0070, 0x01, 0x01, )
                        IO (Decode16, 0x0080, 0x0080, 0x01, 0x01, )
                        IO (Decode16, 0x0092, 0x0092, 0x01, 0x01, )
                        IO (Decode16, 0x00B2, 0x00B2, 0x01, 0x02, )
                        IO (Decode16, 0x0680, 0x0680, 0x01, 0x20, )
                        IO (Decode16, 0x0200, 0x0200, 0x01, 0x10, )
                        IO (Decode16, 0xFFFF, 0xFFFF, 0x01, 0x01, )
                        IO (Decode16, 0xFFFF, 0xFFFF, 0x01, 0x01, )
                        IO (Decode16, 0x0400, 0x0400, 0x01, 0x54, )
                        IO (Decode16, 0x0458, 0x0458, 0x01, 0x28, )
                        IO (Decode16, 0x0500, 0x0500, 0x01, 0x80, )
                        IO (Decode16, 0x164E, 0x164E, 0x01, 0x02, )
                    })
                }

                Device (PDRC)
                {
                    Name (_HID, EisaId ("PNP0C02"))
                    Name (_UID, One)
                    Name (BUF0, ResourceTemplate ()
                    {
                        Memory32Fixed (ReadWrite, 0x00000000, 0x00004000, _Y10)
                        Memory32Fixed (ReadWrite, 0x00000000, 0x00001000, _Y11)
                        Memory32Fixed (ReadWrite, 0x00000000, 0x00008000, _Y12)
                        Memory32Fixed (ReadWrite, 0x00000000, 0x00001000, _Y13)
                        Memory32Fixed (ReadWrite, 0x00000000, 0x00001000, _Y14)
                        Memory32Fixed (ReadWrite, 0x00000000, 0x00000000, _Y15)

                        Memory32Fixed (ReadWrite, 0xFED20000, 0x00020000, )
                        Memory32Fixed (ReadOnly,  0xFED90000, 0x00004000, )
                        Memory32Fixed (ReadWrite, 0xFED45000, 0x0004B000, )
                        Memory32Fixed (ReadOnly,  0xFF000000, 0x01000000, )
                        Memory32Fixed (ReadOnly,  0xFEE00000, 0x00100000, )

                    })
                    Method (_CRS, 0, Serialized)
                    {
                        CreateDWordField (BUF0, ^_Y10._BAS, RBR0)
                        ShiftLeft (RCBA, 0x0E, RBR0)
                        CreateDWordField (BUF0, ^_Y11._BAS, TBR0)
                        Store (TBAB, TBR0)
                        CreateDWordField (BUF0, ^_Y11._LEN, TBLN)
                        If (LEqual (TBAB, Zero))
                        {
                            Store (Zero, TBLN)
                        }

                        CreateDWordField (BUF0, ^_Y12._BAS, MBR0)
                        ShiftLeft (MHBR, 0x0F, MBR0)
                        CreateDWordField (BUF0, ^_Y13._BAS, DBR0)
                        ShiftLeft (DIBR, 0x0C, DBR0)
                        CreateDWordField (BUF0, ^_Y14._BAS, EBR0)
                        ShiftLeft (EPBR, 0x0C, EBR0)
                        CreateDWordField (BUF0, ^_Y15._BAS, XBR0)
                        ShiftLeft (PXBR, 0x1A, XBR0)
                        CreateDWordField (BUF0, ^_Y15._LEN, XSZ0)
                        ShiftRight (0x10000000, PXSZ, XSZ0)
                        Return (BUF0)
                    }
                }

                Device (RTC)
                {
                    Name (_HID, EisaId ("PNP0B00"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16, 0x0070, 0x0070, 0x01, 0x08, )
                        IRQNoFlags () {8}
                    })
                }

                Device (TIMR)
                {
                    Name (_HID, EisaId ("PNP0100"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16, 0x0040, 0x0040, 0x01, 0x04, )
                        IO (Decode16, 0x0050, 0x0050, 0x10, 0x04, )
                        IRQNoFlags () {0}
                    })
                }

                Device (EC)
                {
                    Name (_HID, EisaId ("PNP0C09"))
                    Name (_GPE, 0x18)
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16, 0x0062, 0x0062, 0x00, 0x01, )
                        IO (Decode16, 0x0066, 0x0066, 0x00, 0x01, )
                    })
                }

                Device (MATH)
                {
                    Name (_HID, EisaId ("PNP0C04"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16, 0x00F0, 0x00F0, 0x00, 0x10, )
                        IRQNoFlags () {13}
                    })
                }
            }

            Device (SATA)
            {
                Name (_ADR, 0x001F0002)
            }

            Device (SBUS)
            {
                Name (_ADR, 0x001F0003)
                Device (BUS0)
                {
                    Name (_CID, "smbus")
                    Name (_ADR, Zero)
                    Device (DVL0)
                    {
                        Name (_ADR, 0x57)
                        Name (_CID, "diagsvault")
                    }
                }
            }
        }

        Device (PWRB)
        {
            Name (_HID, EisaId ("PNP0C0C"))
            Name (_UID, 0xAA)
            Name (_STA, 0x0B)
            Name (_PRW, Package (0x02) { 0x1D, 0x04 })
        }
    }

    Scope (_GPE)
    {
        Method (_L01, 0, NotSerialized)
        {
            Add (L01C, One, L01C)
            P8XH (Zero, One)
            P8XH (One, L01C)
        }

        Method (_L02, 0, NotSerialized)
        {
            Store (Zero, GPEC)
        }

        Method (_L09, 0, NotSerialized)
        {
            Notify (\_SB.PCI0.PEG0, 0x02)
            Notify (\_SB.PCI0.PEG0.PEGP, 0x02)
            Notify (\_SB.PCI0.PEG1, 0x02)
            Notify (\_SB.PCI0.PEG2, 0x02)
            Notify (\_SB.PCI0.PEG3, 0x02)
        }

        Method (_L0B, 0, NotSerialized)
        {
            Notify (\_SB.PCI0.P0P1, 0x02)
            Notify (\_SB.PWRB, 0x02)
        }

        Method (_L0D, 0, NotSerialized)
        {
            Notify (\_SB.PCI0.EHC1, 0x02)
            Notify (\_SB.PCI0.EHC2, 0x02)
            Notify (\_SB.PCI0.HDEF, 0x02)
            Notify (\_SB.PCI0.GIGE, 0x02)
        }

        Method (_L1D, 0, NotSerialized)
        {
            Notify (\_SB.PWRB, 0x02)
        }
    }

    Name (_S0, Package (0x03) { Zero, Zero, Zero })
    Name (_S3, Package (0x03) { 0x05, 0x05, Zero })
    Name (_S4, Package (0x03) { 0x06, 0x06, Zero })
    Name (_S5, Package (0x03) { 0x07, 0x07, Zero })

    Method (P8XH, 2, Serialized)
    {
        If (LEqual (Arg0, Zero))
        {
            Store (Or (And (P80D, 0xFFFFFF00), Arg1), P80D)
        }

        If (LEqual (Arg0, One))
        {
            Store (Or (And (P80D, 0xFFFF00FF), ShiftLeft (Arg1, 0x08)
                ), P80D)
        }

        If (LEqual (Arg0, 0x02))
        {
            Store (Or (And (P80D, 0xFF00FFFF), ShiftLeft (Arg1, 0x10)
                ), P80D)
        }

        If (LEqual (Arg0, 0x03))
        {
            Store (Or (And (P80D, 0x00FFFFFF), ShiftLeft (Arg1, 0x18)
                ), P80D)
        }

        Store (P80D, P80H)
    }

    Method (_PTS, 1, NotSerialized)
    {
        Store (Zero, P80D)
        P8XH (Zero, Arg0)
        If (Arg0)
        {
            Store (One, \_SB.PCI0.LPCB.SLPX)
            Store (One, \_SB.PCI0.LPCB.SLPE)
            If (LAnd (LGreater (Arg0, 0x03), LLess (Arg0, 0x06)))
            {
                Store (Arg0, \_SB.SMIC)
                Store (One, GP27)
            }
        }
    }

    Method (_WAK, 1, Serialized)
    {
        ShiftLeft (Arg0, 0x04, DBG8)
        \_SB.PCI0.LPCB.SWAK (Arg0)
        Store (Zero, \_SB.PCI0.LPCB.PLED)
        Return (Package (0x02)
        {
            Zero, 
            Zero
        })
    }
}
