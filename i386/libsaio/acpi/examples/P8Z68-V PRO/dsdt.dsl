/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20110316-64 [Mar 16 2011]
 * Copyright (c) 2000 - 2011 Intel Corporation
 * 
 * Disassembly of dsdt-factory-32mb-igpu.aml, Wed Mar 20 12:38:18 2013
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x0000BAFE (47870)
 *     Revision         0x02
 *     Checksum         0x72
 *     OEM ID           "ALASKA"
 *     OEM Table ID     "A M I"
 *     OEM Revision     0x00000015 (21)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20051117 (537202967)
 */

DefinitionBlock ("dsdt-factory-32mb-igpu.aml", "DSDT", 2, "ALASKA", "A M I", 0x00000015)
{
    External (TNOT, MethodObj)    // 0 Arguments
    External (PDC7)
    External (PDC6)
    External (PDC5)
    External (PDC4)
    External (PDC3)
    External (PDC2)
    External (PDC1)
    External (PDC0)
    External (CFGD)
    External (HNOT, MethodObj)    // 1 Arguments
    External (SNXD)
    External (HWID, IntObj)
    External (IDAB, MethodObj)    // 0 Arguments
    External (HDOS, MethodObj)    // 0 Arguments
    External (ECST, MethodObj)    // 1 Arguments
    External (\_PR_.APSV)
    External (\_PR_.AAC0)
    External (\_PR_.ACRT)
    External (\_PR_.CPU0._PPC)
    External (\_SB_.PCI0.IEIT.EITV, MethodObj)    // 0 Arguments

    Name (SP1O, 0x2E)
    Name (IO1B, Zero)
    Name (IO1L, Zero)
    Name (IO2B, Zero)
    Name (IO2L, Zero)
    Name (IO3B, 0x0290)
    Name (IO3L, 0x10)
    Name (IOES, Zero)
    Name (WKTP, Zero)
    Name (SPIO, 0x2E)
    Name (IOHW, 0x0290)
    Name (IOSB, Zero)
    Name (IOSL, 0x10)
    Name (IOHB, 0x0290)
    Name (IOHL, 0x10)
    Name (SMBS, 0x0580)
    Name (SMBL, 0x20)
    Name (PMBS, 0x0400)
    Name (PMLN, 0x80)
    Name (GPBS, 0x0500)
    Name (GPLN, 0x80)
    Name (SMIP, 0xB2)
    Name (APCB, 0xFEC00000)
    Name (APCL, 0x1000)
    Name (SMCR, 0x0430)
    Name (HPTB, 0xFED00000)
    Name (HPTC, 0xFED1F404)
    Name (FLSZ, 0x00800000)
    Name (SRCB, 0xFED1C000)
    Name (RCLN, 0x4000)
    Name (TCBR, 0xFED08000)
    Name (TCLT, 0x1000)
    Name (PEBS, 0xF8000000)
    Name (PELN, 0x04000000)
    Name (LAPB, 0xFEE00000)
    Name (EGPB, 0xFED19000)
    Name (MCHB, 0xFED10000)
    Name (VTBS, 0xFED90000)
    Name (VTLN, 0x4000)
    Name (ACPH, 0xDE)
    Name (ASSB, Zero)
    Name (AOTB, Zero)
    Name (AAXB, Zero)
    Name (PEHP, One)
    Name (SHPC, Zero)
    Name (PEPM, One)
    Name (PEER, One)
    Name (PECS, One)
    Name (ITKE, Zero)
    Name (MBEC, 0xFFFF)
    Name (AMWV, 0x09)
    Name (FMBL, One)
    Name (FDTP, 0x02)
    Name (FUPS, 0x03)
    Name (FUWS, 0x04)
    Name (BSH, Zero)
    Name (BEL, One)
    Name (BEH, 0x02)
    Name (BRH, 0x03)
    Name (BTF, 0x04)
    Name (BHC, 0x05)
    Name (BYB, 0x06)
    Name (BPH, 0x07)
    Name (BSHS, 0x08)
    Name (BELC, 0x09)
    Name (BRHP, 0x0A)
    Name (BTFC, 0x0B)
    Name (BEHP, 0x0C)
    Name (BPHS, 0x0D)
    Name (BELP, 0x0E)
    Name (BTL, 0x10)
    Name (BTFP, 0x11)
    Name (BSR, 0x14)
    Name (BOF, 0x20)
    Name (BEF, 0x21)
    Name (BLLE, 0x22)
    Name (BLLC, 0x23)
    Name (BLCA, 0x24)
    Name (BLLS, 0x25)
    Name (BLLP, 0x26)
    Name (BLLD, 0x27)
    Name (BHBE, 0x30)
    Name (BHBC, 0x31)
    Name (BHBN, 0x32)
    Name (BHBM, 0x33)
    Name (TRTP, One)
    Name (WDTE, One)
    Name (TRTD, 0x02)
    Name (TRTI, 0x03)
    Name (GCDD, One)
    Name (DSTA, 0x0A)
    Name (DSLO, 0x0C)
    Name (DSLC, 0x0E)
    Name (PITS, 0x10)
    Name (SBCS, 0x12)
    Name (SALS, 0x13)
    Name (LSSS, 0x2A)
    Name (SOOT, 0x35)
    Name (PDBR, 0x4D)
    Name (SS1, One)
    Name (SS2, Zero)
    Name (SS3, One)
    Name (SS4, One)
    Name (IOST, 0x0000)
    Name (TOPM, 0x00000000)
    Name (ROMS, 0xFFE00000)
    Name (VGAF, One)
    OperationRegion (GNVS, SystemMemory, 0xDCBB2E18, 0x01CB)
    Field (GNVS, AnyAcc, Lock, Preserve)
    {
        OSYS,   16, 
        SMIF,   8, 
        PRM0,   8, 
        PRM1,   8, 
        SCIF,   8, 
        PRM2,   8, 
        PRM3,   8, 
        LCKF,   8, 
        PRM4,   8, 
        PRM5,   8, 
        P80D,   32, 
        LIDS,   8, 
        PWRS,   8, 
        DBGS,   8, 
        THOF,   8, 
        ACT1,   8, 
        ACTT,   8, 
        PSVT,   8, 
        TC1V,   8, 
        TC2V,   8, 
        TSPV,   8, 
        CRTT,   8, 
        DTSE,   8, 
        DTS1,   8, 
        DTS2,   8, 
        DTSF,   8, 
                Offset (0x25), 
        REVN,   8, 
        RES3,   8, 
                Offset (0x28), 
        APIC,   8, 
        TCNT,   8, 
        PCP0,   8, 
        PCP1,   8, 
        PPCM,   8, 
        PPMF,   32, 
        C67L,   8, 
        NATP,   8, 
        CMAP,   8, 
        CMBP,   8, 
        LPTP,   8, 
        FDCP,   8, 
        CMCP,   8, 
        CIRP,   8, 
        SMSC,   8, 
        W381,   8, 
        SMC1,   8, 
        IGDS,   8, 
        TLST,   8, 
        CADL,   8, 
        PADL,   8, 
        CSTE,   16, 
        NSTE,   16, 
        SSTE,   16, 
        NDID,   8, 
        DID1,   32, 
        DID2,   32, 
        DID3,   32, 
        DID4,   32, 
        DID5,   32, 
        KSV0,   32, 
        KSV1,   8, 
                Offset (0x67), 
        BLCS,   8, 
        BRTL,   8, 
        ALSE,   8, 
        ALAF,   8, 
        LLOW,   8, 
        LHIH,   8, 
                Offset (0x6E), 
        EMAE,   8, 
        EMAP,   16, 
        EMAL,   16, 
                Offset (0x74), 
        MEFE,   8, 
        DSTS,   8, 
                Offset (0x78), 
        TPMP,   8, 
        TPME,   8, 
        MORD,   8, 
        TCGP,   8, 
        PPRP,   32, 
        PPRQ,   8, 
        LPPR,   8, 
        GTF0,   56, 
        GTF2,   56, 
        IDEM,   8, 
        GTF1,   56, 
        BID,    8, 
        PLID,   8, 
                Offset (0xAA), 
        ASLB,   32, 
        IBTT,   8, 
        IPAT,   8, 
        ITVF,   8, 
        ITVM,   8, 
        IPSC,   8, 
        IBLC,   8, 
        IBIA,   8, 
        ISSC,   8, 
        I409,   8, 
        I509,   8, 
        I609,   8, 
        I709,   8, 
        IPCF,   8, 
        IDMS,   8, 
        IF1E,   8, 
        HVCO,   8, 
        NXD1,   32, 
        NXD2,   32, 
        NXD3,   32, 
        NXD4,   32, 
        NXD5,   32, 
        NXD6,   32, 
        NXD7,   32, 
        NXD8,   32, 
        GSMI,   8, 
        PAVP,   8, 
                Offset (0xE1), 
        OSCC,   8, 
        NEXP,   8, 
        SBV1,   8, 
        SBV2,   8, 
                Offset (0xEB), 
        DSEN,   8, 
        ECON,   8, 
        GPIC,   8, 
        CTYP,   8, 
        L01C,   8, 
        VFN0,   8, 
        VFN1,   8, 
        VFN2,   8, 
        VFN3,   8, 
        VFN4,   8, 
                Offset (0x100), 
        NVGA,   32, 
        NVHA,   32, 
        AMDA,   32, 
        DID6,   32, 
        DID7,   32, 
        DID8,   32, 
        EBAS,   32, 
        CPSP,   32, 
        EECP,   32, 
        EVCP,   32, 
        XBAS,   32, 
        OBS1,   32, 
        OBS2,   32, 
        OBS3,   32, 
        OBS4,   32, 
        OBS5,   32, 
        OBS6,   32, 
        OBS7,   32, 
        OBS8,   32, 
                Offset (0x157), 
        ATMC,   8, 
        PTMC,   8, 
        ATRA,   8, 
        PTRA,   8, 
        PNHM,   32, 
        TBAB,   32, 
        TBAH,   32, 
        RTIP,   8, 
        TSOD,   8, 
        ATPC,   8, 
        PTPC,   8, 
        PFLV,   8, 
        BREV,   8, 
        SGMD,   8, 
        SGFL,   8, 
        PWOK,   8, 
        HLRS,   8, 
        DSEL,   8, 
        ESEL,   8, 
        PSEL,   8, 
        PWEN,   8, 
        PRST,   8, 
        MXD1,   32, 
        MXD2,   32, 
        MXD3,   32, 
        MXD4,   32, 
        MXD5,   32, 
        MXD6,   32, 
        MXD7,   32, 
        MXD8,   32, 
        GBAS,   16, 
        SGGP,   8, 
        PXFX,   8, 
        PXDY,   8, 
        PXFD,   8, 
                Offset (0x19D), 
        ALFP,   8, 
        IMON,   8, 
        PDTS,   8, 
        PKGA,   8, 
        PAMT,   8, 
        AC0F,   8, 
        AC1F,   8, 
        DTS3,   8, 
        DTS4,   8, 
                Offset (0x1B2), 
        XHCI,   8, 
        XHPM,   8, 
                Offset (0x1B7), 
        XTUB,   32, 
        XTUS,   32, 
        XMPB,   32, 
                Offset (0x1C4), 
        LPMV,   8, 
        AOAC,   8, 
        SLDR,   32, 
        E4GM,   8
    }

    Scope (_SB)
    {
        Name (PR00, Package (0x24)
        {
            Package (0x04)
            {
                0x001FFFFF, 
                Zero, 
                LNKF, 
                Zero
            }, 

            Package (0x04)
            {
                0x001FFFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x001FFFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x001FFFFF, 
                0x03, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0014FFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                0x02, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                0x03, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                Zero, 
                LNKH, 
                Zero
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                One, 
                LNKF, 
                Zero
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                0x03, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x001BFFFF, 
                Zero, 
                LNKG, 
                Zero
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                0x03, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                One, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                0x03, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                One, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x03, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                Zero, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                One, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                0x02, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                0x03, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                One, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                0x03, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0019FFFF, 
                Zero, 
                LNKE, 
                Zero
            }
        })
        Name (AR00, Package (0x24)
        {
            Package (0x04)
            {
                0x001FFFFF, 
                Zero, 
                Zero, 
                0x15
            }, 

            Package (0x04)
            {
                0x001FFFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x001FFFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x001FFFFF, 
                0x03, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0014FFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                0x02, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                0x03, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x001DFFFF, 
                Zero, 
                Zero, 
                0x17
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                One, 
                Zero, 
                0x15
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x001AFFFF, 
                0x03, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x001BFFFF, 
                Zero, 
                Zero, 
                0x16
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0016FFFF, 
                0x03, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                One, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x001CFFFF, 
                0x03, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                One, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x03, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                Zero, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                One, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                0x02, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0006FFFF, 
                0x03, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                One, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0004FFFF, 
                0x03, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0019FFFF, 
                Zero, 
                Zero, 
                0x14
            }
        })
        Name (PR04, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKD, 
                Zero
            }
        })
        Name (AR04, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x13
            }
        })
        Name (PR05, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKA, 
                Zero
            }
        })
        Name (AR05, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x10
            }
        })
        Name (PR06, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKB, 
                Zero
            }
        })
        Name (AR06, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x11
            }
        })
        Name (PR07, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKC, 
                Zero
            }
        })
        Name (AR07, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x12
            }
        })
        Name (PR08, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKD, 
                Zero
            }
        })
        Name (AR08, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x13
            }
        })
        Name (PR09, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKA, 
                Zero
            }
        })
        Name (AR09, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x10
            }
        })
        Name (PR0E, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKB, 
                Zero
            }
        })
        Name (AR0E, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x11
            }
        })
        Name (PR0F, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKC, 
                Zero
            }
        })
        Name (AR0F, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x12
            }
        })
        Name (PR01, Package (0x08)
        {
            Package (0x04)
            {
                0x0002FFFF, 
                Zero, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x02, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x03, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                Zero, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                One, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                0x02, 
                LNKF, 
                Zero
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                0x03, 
                LNKG, 
                Zero
            }
        })
        Name (AR01, Package (0x08)
        {
            Package (0x04)
            {
                0x0002FFFF, 
                Zero, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x02, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x03, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                Zero, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                One, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                0x02, 
                Zero, 
                0x15
            }, 

            Package (0x04)
            {
                0x0003FFFF, 
                0x03, 
                Zero, 
                0x16
            }
        })
        Name (PR02, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKD, 
                Zero
            }
        })
        Name (AR02, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x13
            }
        })
        Name (PR0A, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKA, 
                Zero
            }
        })
        Name (AR0A, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x10
            }
        })
        Name (PR0B, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKB, 
                Zero
            }
        })
        Name (AR0B, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x11
            }
        })
        Name (PR0C, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKC, 
                Zero
            }
        })
        Name (AR0C, Package (0x04)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x12
            }
        })
        Name (PR31, Package (0x0C)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                Zero, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                One, 
                LNKA, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x02, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x03, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                Zero, 
                LNKB, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                One, 
                LNKC, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x02, 
                LNKD, 
                Zero
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x03, 
                LNKA, 
                Zero
            }
        })
        Name (AR31, Package (0x0C)
        {
            Package (0x04)
            {
                0xFFFF, 
                Zero, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0xFFFF, 
                One, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x02, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0xFFFF, 
                0x03, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                Zero, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                One, 
                Zero, 
                0x10
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x02, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0001FFFF, 
                0x03, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                Zero, 
                Zero, 
                0x11
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                One, 
                Zero, 
                0x12
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x02, 
                Zero, 
                0x13
            }, 

            Package (0x04)
            {
                0x0002FFFF, 
                0x03, 
                Zero, 
                0x10
            }
        })
        Name (PRSA, ResourceTemplate ()
        {
            IRQ (Level, ActiveLow, Shared, )
                {3,4,5,6,10,11,12,14,15}
        })
        Alias (PRSA, PRSB)
        Alias (PRSA, PRSC)
        Alias (PRSA, PRSD)
        Alias (PRSA, PRSE)
        Alias (PRSA, PRSF)
        Alias (PRSA, PRSG)
        Alias (PRSA, PRSH)
        Device (PCI0)
        {
            Name (_HID, EisaId ("PNP0A08"))
            Name (_CID, EisaId ("PNP0A03"))
            Name (_ADR, Zero)
            Method (^BN00, 0, NotSerialized)
            {
                Return (Zero)
            }

            Method (_BBN, 0, NotSerialized)
            {
                Return (BN00 ())
            }

            Name (_UID, Zero)
            Method (_PRT, 0, NotSerialized)
            {
                If (PICM)
                {
                    Return (AR00 ())
                }

                Return (PR00 ())
            }

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
                    ,, )
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
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000C4000,         // Range Minimum
                    0x000C7FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000C8000,         // Range Minimum
                    0x000CBFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000CC000,         // Range Minimum
                    0x000CFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000D0000,         // Range Minimum
                    0x000D3FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000D4000,         // Range Minimum
                    0x000D7FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000D8000,         // Range Minimum
                    0x000DBFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000DC000,         // Range Minimum
                    0x000DFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000E0000,         // Range Minimum
                    0x000E3FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000E4000,         // Range Minimum
                    0x000E7FFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000E8000,         // Range Minimum
                    0x000EBFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000EC000,         // Range Minimum
                    0x000EFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00004000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x000F0000,         // Range Minimum
                    0x000FFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0x00010000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x00000000,         // Granularity
                    0x00000000,         // Range Minimum
                    0xFEAFFFFF,         // Range Maximum
                    0x00000000,         // Translation Offset
                    0xFEB00000,         // Length
                    ,, , AddressRangeMemory, TypeStatic)
                QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                    0x0000000000000000, // Granularity
                    0x0000000000010000, // Range Minimum
                    0x000000000001FFFF, // Range Maximum
                    0x0000000000000000, // Translation Offset
                    0x0000000000010000, // Length
                    ,, , AddressRangeMemory, TypeStatic)
            })
            Method (_CRS, 0, Serialized)
            {
                CreateWordField (BUF0, 0x0A, PBMX)
                Store (Subtract (ShiftRight (PELN, 0x14), 0x02), PBMX)
                CreateWordField (BUF0, 0x0E, PBLN)
                Store (Subtract (ShiftRight (PELN, 0x14), One), PBLN)
                If (PM1L)
                {
                    CreateDWordField (BUF0, 0x7C, C0LN)
                    Store (Zero, C0LN)
                }

                If (LEqual (PM1L, One))
                {
                    CreateBitField (BUF0, 0x0358, C0RW)
                    Store (Zero, C0RW)
                }

                If (PM1H)
                {
                    CreateDWordField (BUF0, 0x96, C4LN)
                    Store (Zero, C4LN)
                }

                If (LEqual (PM1H, One))
                {
                    CreateBitField (BUF0, 0x0428, C4RW)
                    Store (Zero, C4RW)
                }

                If (PM2L)
                {
                    CreateDWordField (BUF0, 0xB0, C8LN)
                    Store (Zero, C8LN)
                }

                If (LEqual (PM2L, One))
                {
                    CreateBitField (BUF0, 0x04F8, C8RW)
                    Store (Zero, C8RW)
                }

                If (PM2H)
                {
                    CreateDWordField (BUF0, 0xCA, CCLN)
                    Store (Zero, CCLN)
                }

                If (LEqual (PM2H, One))
                {
                    CreateBitField (BUF0, 0x05C8, CCRW)
                    Store (Zero, CCRW)
                }

                If (PM3L)
                {
                    CreateDWordField (BUF0, 0xE4, D0LN)
                    Store (Zero, D0LN)
                }

                If (LEqual (PM3L, One))
                {
                    CreateBitField (BUF0, 0x0698, D0RW)
                    Store (Zero, D0RW)
                }

                If (PM3H)
                {
                    CreateDWordField (BUF0, 0xFE, D4LN)
                    Store (Zero, D4LN)
                }

                If (LEqual (PM3H, One))
                {
                    CreateBitField (BUF0, 0x0768, D4RW)
                    Store (Zero, D4RW)
                }

                If (PM4L)
                {
                    CreateDWordField (BUF0, 0x0118, D8LN)
                    Store (Zero, D8LN)
                }

                If (LEqual (PM4L, One))
                {
                    CreateBitField (BUF0, 0x0838, D8RW)
                    Store (Zero, D8RW)
                }

                If (PM4H)
                {
                    CreateDWordField (BUF0, 0x0132, DCLN)
                    Store (Zero, DCLN)
                }

                If (LEqual (PM4H, One))
                {
                    CreateBitField (BUF0, 0x0908, DCRW)
                    Store (Zero, DCRW)
                }

                If (PM5L)
                {
                    CreateDWordField (BUF0, 0x014C, E0LN)
                    Store (Zero, E0LN)
                }

                If (LEqual (PM5L, One))
                {
                    CreateBitField (BUF0, 0x09D8, E0RW)
                    Store (Zero, E0RW)
                }

                If (PM5H)
                {
                    CreateDWordField (BUF0, 0x0166, E4LN)
                    Store (Zero, E4LN)
                }

                If (LEqual (PM5H, One))
                {
                    CreateBitField (BUF0, 0x0AA8, E4RW)
                    Store (Zero, E4RW)
                }

                If (PM6L)
                {
                    CreateDWordField (BUF0, 0x0180, E8LN)
                    Store (Zero, E8LN)
                }

                If (LEqual (PM6L, One))
                {
                    CreateBitField (BUF0, 0x0B78, E8RW)
                    Store (Zero, E8RW)
                }

                If (PM6H)
                {
                    CreateDWordField (BUF0, 0x019A, ECLN)
                    Store (Zero, ECLN)
                }

                If (LEqual (PM6H, One))
                {
                    CreateBitField (BUF0, 0x0C48, ECRW)
                    Store (Zero, ECRW)
                }

                If (PM0H)
                {
                    CreateDWordField (BUF0, 0x01B4, F0LN)
                    Store (Zero, F0LN)
                }

                If (LEqual (PM0H, One))
                {
                    CreateBitField (BUF0, 0x0D18, F0RW)
                    Store (Zero, F0RW)
                }

                CreateDWordField (BUF0, 0x01C2, M1MN)
                CreateDWordField (BUF0, 0x01C6, M1MX)
                CreateDWordField (BUF0, 0x01CE, M1LN)
                ShiftLeft (TLUD, 0x14, M1MN)
                Add (Subtract (M1MX, M1MN), One, M1LN)
                If (LLessEqual (OSYS, 0x07D3))
                {
                    CreateDWordField (BUF0, 0x01F8, MSLN)
                    Store (Zero, MSLN)
                }
                Else
                {
                    If (E4GM)
                    {
                        CreateQWordField (BUF0, 0x01F8, M2LN)
                        CreateQWordField (BUF0, 0x01E0, M2MN)
                        CreateQWordField (BUF0, 0x01E8, M2MX)
                        If (LGreaterEqual (TUUD, 0x1000))
                        {
                            ShiftLeft (TUUD, 0x14, M2MN)
                            Store (Subtract (0x0000001000000000, ShiftLeft (TUUD, 0x14)), M2LN)
                        }
                        Else
                        {
                            Store (0x0000000100000000, M2MN)
                            Store (0x0000000F00000000, M2LN)
                        }

                        Subtract (Add (M2MN, M2LN), One, M2MX)
                    }
                    Else
                    {
                        CreateDWordField (BUF0, 0x01F8, M4LN)
                        Store (Zero, M4LN)
                    }
                }

                Return (BUF0)
            }

            Name (GUID, Buffer (0x10)
            {
                /* 0000 */    0x5B, 0x4D, 0xDB, 0x33, 0xF7, 0x1F, 0x1C, 0x40, 
                /* 0008 */    0x96, 0x57, 0x74, 0x41, 0xC0, 0x3D, 0xD7, 0x66
            })
            Name (SUPP, Zero)
            Name (CTRL, Zero)
            Name (XCNT, Zero)
            Method (_OSC, 4, Serialized)
            {
                Store (Arg3, Local0)
                CreateDWordField (Local0, Zero, CDW1)
                CreateDWordField (Local0, 0x04, CDW2)
                CreateDWordField (Local0, 0x08, CDW3)
                If (^XHC.CUID (Arg0))
                {
                    Return (^XHC.POSC (Arg1, Arg2, Arg3))
                }
                Else
                {
                    If (_OSI ("Windows 2012"))
                    {
                        If (LEqual (XCNT, Zero))
                        {
                            ^XHC.XSEL ()
                            Increment (XCNT)
                        }
                    }
                }

                If (LAnd (LEqual (Arg0, GUID), NEXP))
                {
                    Store (CDW2, SUPP)
                    Store (CDW3, CTRL)
                    If (Not (And (CDW1, One)))
                    {
                        If (And (CTRL, One))
                        {
                            NHPG ()
                        }

                        If (And (CTRL, 0x04))
                        {
                            NPME ()
                        }
                    }

                    If (LNotEqual (Arg1, One))
                    {
                        Or (CDW1, 0x08, CDW1)
                    }

                    If (LNotEqual (CDW3, CTRL))
                    {
                        Or (CDW1, 0x10, CDW1)
                    }

                    Store (CTRL, CDW3)
                    Store (CTRL, OSCC)
                    Return (Local0)
                }
                Else
                {
                    Or (CDW1, 0x04, CDW1)
                    Return (Local0)
                }
            }

            Scope (\_SB.PCI0)
            {
                Method (AR00, 0, NotSerialized)
                {
                    Return (^^AR00)
                }

                Method (PR00, 0, NotSerialized)
                {
                    Return (^^PR00)
                }

                Method (AR01, 0, NotSerialized)
                {
                    Return (^^AR01)
                }

                Method (PR01, 0, NotSerialized)
                {
                    Return (^^PR01)
                }

                Method (AR02, 0, NotSerialized)
                {
                    Return (^^AR02)
                }

                Method (PR02, 0, NotSerialized)
                {
                    Return (^^PR02)
                }

                Method (AR04, 0, NotSerialized)
                {
                    Return (^^AR04)
                }

                Method (PR04, 0, NotSerialized)
                {
                    Return (^^PR04)
                }

                Method (AR05, 0, NotSerialized)
                {
                    Return (^^AR05)
                }

                Method (PR05, 0, NotSerialized)
                {
                    Return (^^PR05)
                }

                Method (AR06, 0, NotSerialized)
                {
                    Return (^^AR06)
                }

                Method (PR06, 0, NotSerialized)
                {
                    Return (^^PR06)
                }

                Method (AR07, 0, NotSerialized)
                {
                    Return (^^AR07)
                }

                Method (PR07, 0, NotSerialized)
                {
                    Return (^^PR07)
                }

                Method (AR08, 0, NotSerialized)
                {
                    Return (^^AR08)
                }

                Method (PR08, 0, NotSerialized)
                {
                    Return (^^PR08)
                }

                Method (AR09, 0, NotSerialized)
                {
                    Return (^^AR09)
                }

                Method (PR09, 0, NotSerialized)
                {
                    Return (^^PR09)
                }

                Method (AR0E, 0, NotSerialized)
                {
                    Return (^^AR0E)
                }

                Method (PR0E, 0, NotSerialized)
                {
                    Return (^^PR0E)
                }

                Method (AR0F, 0, NotSerialized)
                {
                    Return (^^AR0F)
                }

                Method (PR0F, 0, NotSerialized)
                {
                    Return (^^PR0F)
                }

                Method (AR0A, 0, NotSerialized)
                {
                    Return (^^AR0A)
                }

                Method (PR0A, 0, NotSerialized)
                {
                    Return (^^PR0A)
                }

                Method (AR0B, 0, NotSerialized)
                {
                    Return (^^AR0B)
                }

                Method (PR0B, 0, NotSerialized)
                {
                    Return (^^PR0B)
                }

                Method (AR0C, 0, NotSerialized)
                {
                    Return (^^AR0C)
                }

                Method (PR0C, 0, NotSerialized)
                {
                    Return (^^PR0C)
                }
            }

            Device (TPMX)
            {
                Name (_HID, EisaId ("PNP0C01"))
                Name (_UID, One)
                Name (CRS, ResourceTemplate ()
                {
                    Memory32Fixed (ReadOnly,
                        0xFED40000,         // Address Base
                        0x00005000,         // Address Length
                        )
                })
                Method (_CRS, 0, NotSerialized)
                {
                    If (TPMF)
                    {
                        Return (Zero)
                    }

                    Return (CRS)
                }
            }

            Device (LPCB)
            {
                Name (_ADR, 0x001F0000)
                Scope (\_SB)
                {
                    OperationRegion (PCI0.LPCB.LPC1, PCI_Config, 0x40, 0xC0)
                    Field (PCI0.LPCB.LPC1, AnyAcc, NoLock, Preserve)
                    {
                                Offset (0x20), 
                        PARC,   8, 
                        PBRC,   8, 
                        PCRC,   8, 
                        PDRC,   8, 
                                Offset (0x28), 
                        PERC,   8, 
                        PFRC,   8, 
                        PGRC,   8, 
                        PHRC,   8, 
                                Offset (0x6C), 
                                Offset (0x6D), 
                                Offset (0x6E), 
                        XUSB,   1
                    }

                    Device (LNKA)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, One)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PARC, 0x80, PARC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSA)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLA, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLA, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PARC, 0x0F), IRQ0)
                            Return (RTLA)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PARC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PARC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKB)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x02)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PBRC, 0x80, PBRC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSB)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLB, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLB, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PBRC, 0x0F), IRQ0)
                            Return (RTLB)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PBRC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PBRC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKC)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x03)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PCRC, 0x80, PCRC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSC)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLC, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLC, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PCRC, 0x0F), IRQ0)
                            Return (RTLC)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PCRC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PCRC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKD)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x04)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PDRC, 0x80, PDRC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSD)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLD, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLD, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PDRC, 0x0F), IRQ0)
                            Return (RTLD)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PDRC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PDRC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKE)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x05)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PERC, 0x80, PERC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSE)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLE, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLE, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PERC, 0x0F), IRQ0)
                            Return (RTLE)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PERC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PERC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKF)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x06)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PFRC, 0x80, PFRC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSF)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLF, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLF, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PFRC, 0x0F), IRQ0)
                            Return (RTLF)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PFRC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PFRC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKG)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x07)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PGRC, 0x80, PGRC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSG)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLG, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLG, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PGRC, 0x0F), IRQ0)
                            Return (RTLG)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PGRC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PGRC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }

                    Device (LNKH)
                    {
                        Name (_HID, EisaId ("PNP0C0F"))
                        Name (_UID, 0x08)
                        Method (_DIS, 0, Serialized)
                        {
                            Or (PHRC, 0x80, PHRC)
                        }

                        Method (_PRS, 0, Serialized)
                        {
                            Return (PRSH)
                        }

                        Method (_CRS, 0, Serialized)
                        {
                            Name (RTLH, ResourceTemplate ()
                            {
                                IRQ (Level, ActiveLow, Shared, )
                                    {}
                            })
                            CreateWordField (RTLH, One, IRQ0)
                            Store (Zero, IRQ0)
                            ShiftLeft (One, And (PHRC, 0x0F), IRQ0)
                            Return (RTLH)
                        }

                        Method (_SRS, 1, Serialized)
                        {
                            CreateWordField (Arg0, One, IRQ0)
                            FindSetRightBit (IRQ0, Local0)
                            Decrement (Local0)
                            Store (Local0, PHRC)
                        }

                        Method (_STA, 0, Serialized)
                        {
                            If (And (PHRC, 0x80))
                            {
                                Return (0x09)
                            }
                            Else
                            {
                                Return (0x0B)
                            }
                        }
                    }
                }

                OperationRegion (LPC0, PCI_Config, 0x40, 0xC0)
                Field (LPC0, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x40), 
                    IOD0,   8, 
                    IOD1,   8, 
                            Offset (0xB0), 
                    RAEN,   1, 
                        ,   13, 
                    RCBA,   18
                }

                Device (DMAC)
                {
                    Name (_HID, EisaId ("PNP0200"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x20,               // Length
                            )
                        IO (Decode16,
                            0x0081,             // Range Minimum
                            0x0081,             // Range Maximum
                            0x01,               // Alignment
                            0x11,               // Length
                            )
                        IO (Decode16,
                            0x0093,             // Range Minimum
                            0x0093,             // Range Maximum
                            0x01,               // Alignment
                            0x0D,               // Length
                            )
                        IO (Decode16,
                            0x00C0,             // Range Minimum
                            0x00C0,             // Range Maximum
                            0x01,               // Alignment
                            0x20,               // Length
                            )
                        DMA (Compatibility, NotBusMaster, Transfer8_16, )
                            {4}
                    })
                }

                Device (FWHD)
                {
                    Name (_HID, EisaId ("INT0800"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        Memory32Fixed (ReadOnly,
                            0xFF000000,         // Address Base
                            0x01000000,         // Address Length
                            )
                    })
                }

                Device (HPET)
                {
                    Name (_HID, EisaId ("PNP0103"))
                    Name (_UID, Zero)
                    Name (BUF0, ResourceTemplate ()
                    {
                        Memory32Fixed (ReadWrite,
                            0xFED00000,         // Address Base
                            0x00000400,         // Address Length
                            )
                    })
                    Method (_STA, 0, NotSerialized)
                    {
                        If (LGreaterEqual (OSYS, 0x07D1))
                        {
                            If (HPAE)
                            {
                                Return (0x0F)
                            }
                        }
                        Else
                        {
                            If (HPAE)
                            {
                                Return (0x0B)
                            }
                        }

                        Return (Zero)
                    }

                    Method (_CRS, 0, Serialized)
                    {
                        If (HPAE)
                        {
                            CreateDWordField (BUF0, 0x04, HPT0)
                            If (LEqual (HPAS, One))
                            {
                                Store (0xFED01000, HPT0)
                            }

                            If (LEqual (HPAS, 0x02))
                            {
                                Store (0xFED02000, HPT0)
                            }

                            If (LEqual (HPAS, 0x03))
                            {
                                Store (0xFED03000, HPT0)
                            }
                        }

                        Return (BUF0)
                    }
                }

                Device (IPIC)
                {
                    Name (_HID, EisaId ("PNP0000"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0020,             // Range Minimum
                            0x0020,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0024,             // Range Minimum
                            0x0024,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0028,             // Range Minimum
                            0x0028,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x002C,             // Range Minimum
                            0x002C,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0030,             // Range Minimum
                            0x0030,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0034,             // Range Minimum
                            0x0034,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0038,             // Range Minimum
                            0x0038,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x003C,             // Range Minimum
                            0x003C,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00A0,             // Range Minimum
                            0x00A0,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00A4,             // Range Minimum
                            0x00A4,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00A8,             // Range Minimum
                            0x00A8,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00AC,             // Range Minimum
                            0x00AC,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00B0,             // Range Minimum
                            0x00B0,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00B4,             // Range Minimum
                            0x00B4,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00B8,             // Range Minimum
                            0x00B8,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x00BC,             // Range Minimum
                            0x00BC,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x04D0,             // Range Minimum
                            0x04D0,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IRQNoFlags ()
                            {2}
                    })
                }

                Device (LDRC)
                {
                    Name (_HID, EisaId ("PNP0C02"))
                    Name (_UID, 0x02)
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x002E,             // Range Minimum
                            0x002E,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x004E,             // Range Minimum
                            0x004E,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0061,             // Range Minimum
                            0x0061,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0063,             // Range Minimum
                            0x0063,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0065,             // Range Minimum
                            0x0065,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0067,             // Range Minimum
                            0x0067,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0070,             // Range Minimum
                            0x0070,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0080,             // Range Minimum
                            0x0080,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0092,             // Range Minimum
                            0x0092,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x00B2,             // Range Minimum
                            0x00B2,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0680,             // Range Minimum
                            0x0680,             // Range Maximum
                            0x01,               // Alignment
                            0x20,               // Length
                            )
                        IO (Decode16,
                            0x0200,             // Range Minimum
                            0x0200,             // Range Maximum
                            0x01,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0xFFFF,             // Range Minimum
                            0xFFFF,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0xFFFF,             // Range Minimum
                            0xFFFF,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0400,             // Range Minimum
                            0x0400,             // Range Maximum
                            0x01,               // Alignment
                            0x54,               // Length
                            )
                        IO (Decode16,
                            0x0458,             // Range Minimum
                            0x0458,             // Range Maximum
                            0x01,               // Alignment
                            0x28,               // Length
                            )
                        IO (Decode16,
                            0x0500,             // Range Minimum
                            0x0500,             // Range Maximum
                            0x01,               // Alignment
                            0x80,               // Length
                            )
                        IO (Decode16,
                            0x164E,             // Range Minimum
                            0x164E,             // Range Maximum
                            0x01,               // Alignment
                            0x02,               // Length
                            )
                    })
                }

                Device (RTC)
                {
                    Name (_HID, EisaId ("PNP0B00"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0070,             // Range Minimum
                            0x0070,             // Range Maximum
                            0x01,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {8}
                    })
                }

                Device (TIMR)
                {
                    Name (_HID, EisaId ("PNP0100"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0040,             // Range Minimum
                            0x0040,             // Range Maximum
                            0x01,               // Alignment
                            0x04,               // Length
                            )
                        IO (Decode16,
                            0x0050,             // Range Minimum
                            0x0050,             // Range Maximum
                            0x10,               // Alignment
                            0x04,               // Length
                            )
                        IRQNoFlags ()
                            {0}
                    })
                }

                Device (CWDT)
                {
                    Name (_HID, EisaId ("INT3F0D"))
                    Name (_CID, EisaId ("PNP0C02"))
                    Name (BUF0, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0454,             // Range Minimum
                            0x0454,             // Range Maximum
                            0x04,               // Alignment
                            0x04,               // Length
                            )
                    })
                    Method (_STA, 0, Serialized)
                    {
                        If (LEqual (WDTE, One))
                        {
                            Return (0x0F)
                        }
                        Else
                        {
                            Return (Zero)
                        }
                    }

                    Method (_CRS, 0, Serialized)
                    {
                        Return (BUF0)
                    }
                }

                Device (EC0)
                {
                    Name (_HID, EisaId ("PNP0C09"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0062,             // Range Minimum
                            0x0062,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0066,             // Range Minimum
                            0x0066,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                    })
                    CreateWordField (_CRS, 0x02, DPRT)
                    CreateWordField (_CRS, 0x0A, CPRT)
                    Name (_GPE, 0x18)
                    Name (REGC, Zero)
                    Method (_Q80, 0, NotSerialized)
                    {
                        \AMW0.AMWN (0x05)
                    }

                    Method (_Q81, 0, NotSerialized)
                    {
                        \AMW0.AMWN (0x00010005)
                    }

                    Method (_Q82, 0, NotSerialized)
                    {
                        \AMW0.AMWN (0x00020005)
                    }

                    Method (_Q83, 0, NotSerialized)
                    {
                        \AMW0.AMWN (0x00030005)
                    }
                }

                Device (SIO1)
                {
                    Name (_HID, EisaId ("PNP0C02"))
                    Name (_UID, 0x0111)
                    Name (CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            )
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            )
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            )
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            )
                    })
                    Method (_CRS, 0, NotSerialized)
                    {
                        If (LAnd (LLess (SP1O, 0x03F0), LGreater (SP1O, 0xF0)))
                        {
                            CreateWordField (CRS, 0x02, GPI0)
                            CreateWordField (CRS, 0x04, GPI1)
                            CreateByteField (CRS, 0x07, GPIL)
                            Store (SP1O, GPI0)
                            Store (SP1O, GPI1)
                            Store (0x02, GPIL)
                        }

                        If (IO1B)
                        {
                            CreateWordField (CRS, 0x0A, GP10)
                            CreateWordField (CRS, 0x0C, GP11)
                            CreateByteField (CRS, 0x0F, GPL1)
                            Store (IO1B, GP10)
                            Store (IO1B, GP11)
                            Store (IO1L, GPL1)
                        }

                        If (IO3B)
                        {
                            CreateWordField (CRS, 0x12, GP20)
                            CreateWordField (CRS, 0x14, GP21)
                            CreateByteField (CRS, 0x17, GPL2)
                            Store (IO3B, GP20)
                            Store (IO3B, GP21)
                            Store (IO3L, GPL2)
                        }

                        If (IO2B)
                        {
                            CreateWordField (CRS, 0x1A, GP30)
                            CreateWordField (CRS, 0x1C, GP31)
                            CreateByteField (CRS, 0x1F, GPL3)
                            Store (IO2B, GP30)
                            Store (IO2B, GP31)
                            Store (IO2L, GPL3)
                        }

                        Return (CRS)
                    }

                    Name (DCAT, Package (0x15)
                    {
                        0x02, 
                        0x03, 
                        One, 
                        Zero, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0x05, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0x05, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0x06, 
                        0xFF, 
                        0xFF
                    })
                    Mutex (MUT0, 0x00)
                    Method (ENFG, 1, NotSerialized)
                    {
                        Acquire (MUT0, 0x0FFF)
                        Store (0x87, INDX)
                        Store (0x87, INDX)
                        Store (Arg0, LDN)
                    }

                    Method (EXFG, 0, NotSerialized)
                    {
                        Store (0xAA, INDX)
                        Release (MUT0)
                    }

                    Method (LPTM, 1, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        And (OPT0, 0x02, Local0)
                        EXFG ()
                        Return (Local0)
                    }

                    Method (UHID, 1, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        And (OPT0, 0x38, Local0)
                        EXFG ()
                        If (Local0)
                        {
                            Return (0x1005D041)
                        }
                        Else
                        {
                            Return (0x0105D041)
                        }
                    }

                    OperationRegion (IOID, SystemIO, SP1O, 0x02)
                    Field (IOID, ByteAcc, NoLock, Preserve)
                    {
                        INDX,   8, 
                        DATA,   8
                    }

                    IndexField (INDX, DATA, ByteAcc, NoLock, Preserve)
                    {
                                Offset (0x07), 
                        LDN,    8, 
                                Offset (0x21), 
                        SCF1,   8, 
                        SCF2,   8, 
                        SCF3,   8, 
                        SCF4,   8, 
                        SCF5,   8, 
                        SCF6,   8, 
                                Offset (0x29), 
                        CKCF,   8, 
                                Offset (0x30), 
                        ACTR,   8, 
                                Offset (0x60), 
                        IOAH,   8, 
                        IOAL,   8, 
                        IOH2,   8, 
                        IOL2,   8, 
                                Offset (0x70), 
                        INTR,   8, 
                                Offset (0x74), 
                        DMCH,   8, 
                                Offset (0xE0), 
                        RGE0,   8, 
                        RGE1,   8, 
                        RGE2,   8, 
                        RGE3,   8, 
                        RGE4,   8, 
                        RGE5,   8, 
                        RGE6,   8, 
                        RGE7,   8, 
                        RGE8,   8, 
                        RGE9,   8, 
                                Offset (0xF0), 
                        OPT0,   8, 
                        OPT1,   8, 
                        OPT2,   8, 
                        OPT3,   8, 
                        OPT4,   8, 
                        OPT5,   8, 
                        OPT6,   8, 
                        OPT7,   8, 
                        OPT8,   8, 
                        OPT9,   8
                    }

                    Method (CGLD, 1, NotSerialized)
                    {
                        Return (DerefOf (Index (DCAT, Arg0)))
                    }

                    Method (DSTA, 1, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        Store (ACTR, Local0)
                        EXFG ()
                        If (LEqual (Local0, 0xFF))
                        {
                            Return (Zero)
                        }

                        And (Local0, One, Local0)
                        If (LGreaterEqual (Arg0, 0x10))
                        {
                            Or (IOES, ShiftLeft (Local0, And (Arg0, 0x0F)), IOES)
                        }
                        Else
                        {
                            Or (IOST, ShiftLeft (Local0, Arg0), IOST)
                        }

                        If (Local0)
                        {
                            Return (0x0F)
                        }
                        Else
                        {
                            If (LGreaterEqual (Arg0, 0x10))
                            {
                                Store (IOES, Local0)
                            }
                            Else
                            {
                                Store (IOST, Local0)
                            }

                            And (Arg0, 0x0F, Local1)
                            If (And (ShiftLeft (One, Local1), Local0))
                            {
                                Return (0x0D)
                            }
                            Else
                            {
                                Return (Zero)
                            }
                        }
                    }

                    Method (DCNT, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        If (LAnd (LLess (DMCH, 0x04), LNotEqual (And (DMCH, 0x03, 
                            Local1), Zero)))
                        {
                            RDMA (Arg0, Arg1, Increment (Local1))
                        }

                        Store (Arg1, ACTR)
                        ShiftLeft (IOAH, 0x08, Local1)
                        Or (IOAL, Local1, Local1)
                        RRIO (Arg0, Arg1, Local1, 0x08)
                        EXFG ()
                    }

                    Name (CRS1, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            )
                        IRQNoFlags ()
                            {}
                        DMA (Compatibility, NotBusMaster, Transfer8, )
                            {}
                    })
                    CreateWordField (CRS1, 0x09, IRQM)
                    CreateByteField (CRS1, 0x0C, DMAM)
                    CreateWordField (CRS1, 0x02, IO11)
                    CreateWordField (CRS1, 0x04, IO12)
                    CreateByteField (CRS1, 0x07, LEN1)
                    Name (CRS2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            )
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            )
                        IRQNoFlags ()
                            {}
                        DMA (Compatibility, NotBusMaster, Transfer8, )
                            {2}
                    })
                    CreateWordField (CRS2, 0x11, IRQE)
                    CreateByteField (CRS2, 0x14, DMAE)
                    CreateWordField (CRS2, 0x02, IO21)
                    CreateWordField (CRS2, 0x04, IO22)
                    CreateByteField (CRS2, 0x07, LEN2)
                    CreateWordField (CRS2, 0x0A, IO31)
                    CreateWordField (CRS2, 0x0C, IO32)
                    CreateByteField (CRS2, 0x0F, LEN3)
                    Name (CRS4, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            )
                        IRQ (Edge, ActiveLow, Shared, )
                            {}
                    })
                    CreateWordField (CRS4, 0x09, IRQL)
                    CreateWordField (CRS4, 0x02, IOHL)
                    CreateWordField (CRS4, 0x04, IORL)
                    CreateByteField (CRS4, 0x06, ALMN)
                    CreateByteField (CRS4, 0x07, LENG)
                    Method (DCRS, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        ShiftLeft (IOAH, 0x08, IO11)
                        Or (IOAL, IO11, IO11)
                        Store (IO11, IO12)
                        Store (0x08, LEN1)
                        If (INTR)
                        {
                            ShiftLeft (One, INTR, IRQM)
                        }
                        Else
                        {
                            Store (Zero, IRQM)
                        }

                        If (LOr (LGreater (DMCH, 0x03), LEqual (Arg1, Zero)))
                        {
                            Store (Zero, DMAM)
                        }
                        Else
                        {
                            And (DMCH, 0x03, Local1)
                            ShiftLeft (One, Local1, DMAM)
                        }

                        EXFG ()
                        Return (CRS1)
                    }

                    Method (DCR2, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        ShiftLeft (IOAH, 0x08, IO21)
                        Or (IOAL, IO21, IO21)
                        Store (IO21, IO22)
                        Store (0x08, LEN2)
                        ShiftLeft (IOH2, 0x08, IO31)
                        Or (IOL2, IO31, IO31)
                        Store (IO21, IO32)
                        Store (0x08, LEN3)
                        If (INTR)
                        {
                            ShiftLeft (One, INTR, IRQE)
                        }
                        Else
                        {
                            Store (Zero, IRQE)
                        }

                        If (LOr (LGreater (DMCH, 0x03), LEqual (Arg1, Zero)))
                        {
                            Store (Zero, DMAE)
                        }
                        Else
                        {
                            And (DMCH, 0x03, Local1)
                            ShiftLeft (One, Local1, DMAE)
                        }

                        EXFG ()
                        Return (CRS2)
                    }

                    Method (DCR4, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        ShiftLeft (IOAH, 0x08, IOHL)
                        Or (IOAL, IOHL, IOHL)
                        Store (IOHL, IORL)
                        Store (0x08, LENG)
                        If (INTR)
                        {
                            And (INTR, 0x0F, INTR)
                            ShiftLeft (One, INTR, IRQL)
                        }
                        Else
                        {
                            Store (Zero, IRQL)
                        }

                        EXFG ()
                        Return (CRS4)
                    }

                    Method (DSRS, 2, NotSerialized)
                    {
                        If (LEqual (Arg1, 0x02))
                        {
                            If (LPTM (CGLD (Arg1)))
                            {
                                DSR2 (Arg0, Arg1)
                            }
                        }
                        Else
                        {
                            CreateWordField (Arg0, 0x09, IRQM)
                            CreateByteField (Arg0, 0x0C, DMAM)
                            CreateWordField (Arg0, 0x02, IO11)
                            ENFG (CGLD (Arg1))
                            ShiftLeft (IOAH, 0x08, Local1)
                            Or (IOAL, Local1, Local1)
                            RRIO (Arg1, Zero, Local1, 0x08)
                            RRIO (Arg1, One, IO11, 0x08)
                            And (IO11, 0xFF, IOAL)
                            ShiftRight (IO11, 0x08, IOAH)
                            If (IRQM)
                            {
                                FindSetRightBit (IRQM, Local0)
                                Subtract (Local0, One, INTR)
                            }
                            Else
                            {
                                Store (Zero, INTR)
                            }

                            If (DMAM)
                            {
                                FindSetRightBit (DMAM, Local0)
                                Subtract (Local0, One, DMCH)
                            }
                            Else
                            {
                                Store (0x04, DMCH)
                            }

                            EXFG ()
                            DCNT (Arg1, One)
                            Store (Arg1, Local2)
                            If (LGreater (Local2, Zero))
                            {
                                Subtract (Local2, One, Local2)
                            }
                        }
                    }

                    Method (DSR2, 2, NotSerialized)
                    {
                        CreateWordField (Arg0, 0x11, IRQT)
                        CreateByteField (Arg0, 0x14, DMAT)
                        CreateWordField (Arg0, 0x02, IOT1)
                        CreateWordField (Arg0, 0x0A, IOT2)
                        ENFG (CGLD (Arg1))
                        And (IOT1, 0xFF, IOAL)
                        ShiftRight (IOT1, 0x08, IOAH)
                        And (IOT2, 0xFF, IOL2)
                        ShiftRight (IOT2, 0x08, IOH2)
                        If (IRQT)
                        {
                            FindSetRightBit (IRQT, Local0)
                            Subtract (Local0, One, INTR)
                        }
                        Else
                        {
                            Store (Zero, INTR)
                        }

                        If (DMAT)
                        {
                            FindSetRightBit (DMAT, Local0)
                            Subtract (Local0, One, DMCH)
                        }
                        Else
                        {
                            Store (0x04, DMCH)
                        }

                        EXFG ()
                        DCNT (Arg1, One)
                        Store (Arg1, Local2)
                        If (LGreater (Local2, Zero))
                        {
                            Subtract (Local2, One, Local2)
                        }
                    }

                    Method (DSR4, 2, NotSerialized)
                    {
                        CreateWordField (Arg0, 0x02, IOHL)
                        CreateWordField (Arg0, 0x09, IRQL)
                        ENFG (CGLD (Arg1))
                        And (IOHL, 0xFF, IOAL)
                        ShiftRight (IOHL, 0x08, IOAH)
                        If (IRQL)
                        {
                            FindSetRightBit (IRQL, Local0)
                            Subtract (Local0, One, INTR)
                        }
                        Else
                        {
                            Store (Zero, INTR)
                        }

                        EXFG ()
                        DCNT (Arg1, One)
                        Store (Arg1, Local2)
                        If (LGreater (Local2, Zero))
                        {
                            Subtract (Local2, One, Local2)
                        }
                    }
                }

                Name (PMFG, Zero)
                Method (SIOS, 1, NotSerialized)
                {
                    Store ("SIOS", Debug)
                    If (LEqual (One, Arg0))
                    {
                        ^SIO1.ENFG (0x0A)
                        And (^SIO1.RGE0, 0x9F, ^SIO1.RGE0)
                        If (KBFG)
                        {
                            Or (^SIO1.OPT6, 0x10, ^SIO1.OPT6)
                        }
                        Else
                        {
                            And (^SIO1.OPT6, 0xEF, ^SIO1.OPT6)
                        }

                        If (MSFG)
                        {
                            Or (^SIO1.OPT6, 0x20, ^SIO1.OPT6)
                        }
                        Else
                        {
                            And (^SIO1.OPT6, 0xDF, ^SIO1.OPT6)
                        }

                        Store (0xFF, ^SIO1.OPT3)
                        Store (0xFF, ^SIO1.OPT4)
                        Or (One, ^SIO1.OPT2, ^SIO1.OPT2)
                        ^SIO1.EXFG ()
                        Return (Zero)
                    }

                    If (LNotEqual (0x05, Arg0))
                    {
                        ^SIO1.ENFG (0x0A)
                        Store (0xFF, ^SIO1.OPT3)
                        Store (0xFF, ^SIO1.OPT4)
                        Store (^SIO1.RGE3, Local0)
                        If (KBFG)
                        {
                            Or (^SIO1.RGE0, 0x41, ^SIO1.RGE0)
                        }
                        Else
                        {
                            And (^SIO1.RGE0, 0xBF, ^SIO1.RGE0)
                        }

                        If (MSFG)
                        {
                            Or (^SIO1.RGE0, 0x22, ^SIO1.RGE0)
                            And (^SIO1.RGE0, 0xFD, ^SIO1.RGE0)
                            Or (^SIO1.RGE6, 0x80, ^SIO1.RGE6)
                        }
                        Else
                        {
                            And (^SIO1.RGE0, 0xDF, ^SIO1.RGE0)
                        }

                        And (0xFE, ^SIO1.OPT2, ^SIO1.OPT2)
                        ^SIO1.EXFG ()
                    }
                }

                Method (SIOW, 1, NotSerialized)
                {
                    Store ("SIOW", Debug)
                    ^SIO1.ENFG (0x0A)
                    Store (^SIO1.OPT3, PMFG)
                    Store (0xFF, ^SIO1.OPT3)
                    And (^SIO1.OPT0, 0xE7, ^SIO1.OPT0)
                    And (0xFE, ^SIO1.OPT2, ^SIO1.OPT2)
                    ^SIO1.EXFG ()
                }

                OperationRegion (RX80, PCI_Config, Zero, 0xFF)
                Field (RX80, ByteAcc, NoLock, Preserve)
                {
                            Offset (0x80), 
                    LPCD,   16, 
                    LPCE,   16
                }

                Name (DBPT, Package (0x04)
                {
                    Package (0x08)
                    {
                        0x03F8, 
                        0x02F8, 
                        0x0220, 
                        0x0228, 
                        0x0238, 
                        0x02E8, 
                        0x0338, 
                        0x03E8
                    }, 

                    Package (0x08)
                    {
                        0x03F8, 
                        0x02F8, 
                        0x0220, 
                        0x0228, 
                        0x0238, 
                        0x02E8, 
                        0x0338, 
                        0x03E8
                    }, 

                    Package (0x03)
                    {
                        0x0378, 
                        0x0278, 
                        0x03BC
                    }, 

                    Package (0x02)
                    {
                        0x03F0, 
                        0x0370
                    }
                })
                Name (DDLT, Package (0x04)
                {
                    Package (0x02)
                    {
                        Zero, 
                        0xFFF8
                    }, 

                    Package (0x02)
                    {
                        0x04, 
                        0xFF8F
                    }, 

                    Package (0x02)
                    {
                        0x08, 
                        0xFCFF
                    }, 

                    Package (0x02)
                    {
                        0x0C, 
                        0xEFFF
                    }
                })
                Method (RRIO, 4, NotSerialized)
                {
                    If (LAnd (LLessEqual (Arg0, 0x03), LGreaterEqual (Arg0, Zero)))
                    {
                        Store (Match (DerefOf (Index (DBPT, Arg0)), MEQ, Arg2, MTR, 
                            Zero, Zero), Local0)
                        If (LNotEqual (Local0, Ones))
                        {
                            Store (DerefOf (Index (DerefOf (Index (DDLT, Arg0)), Zero)), 
                                Local1)
                            Store (DerefOf (Index (DerefOf (Index (DDLT, Arg0)), One)), 
                                Local2)
                            ShiftLeft (Local0, Local1, Local0)
                            And (LPCD, Local2, LPCD)
                            Or (LPCD, Local0, LPCD)
                            WX82 (Arg0, Arg1)
                        }
                    }

                    If (LEqual (Arg0, 0x08))
                    {
                        If (LEqual (Arg2, 0x0200))
                        {
                            WX82 (0x08, Arg0)
                        }
                        Else
                        {
                            If (LEqual (Arg2, 0x0208))
                            {
                                WX82 (0x09, Arg0)
                            }
                        }
                    }

                    If (LAnd (LLessEqual (Arg0, 0x0D), LGreaterEqual (Arg0, 0x0A)))
                    {
                        WX82 (Arg0, Arg1)
                    }
                }

                Method (WX82, 2, NotSerialized)
                {
                    ShiftLeft (One, Arg0, Local0)
                    If (Arg1)
                    {
                        Or (LPCE, Local0, LPCE)
                    }
                    Else
                    {
                        Not (Local0, Local0)
                        And (LPCE, Local0, LPCE)
                    }
                }

                Method (RDMA, 3, NotSerialized)
                {
                }

                Device (RMSC)
                {
                    Name (_HID, EisaId ("PNP0C02"))
                    Name (_UID, 0x10)
                    Name (CRS1, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0010,             // Range Minimum
                            0x0010,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x0022,             // Range Minimum
                            0x0022,             // Range Maximum
                            0x00,               // Alignment
                            0x1E,               // Length
                            )
                        IO (Decode16,
                            0x0044,             // Range Minimum
                            0x0044,             // Range Maximum
                            0x00,               // Alignment
                            0x1C,               // Length
                            )
                        IO (Decode16,
                            0x0062,             // Range Minimum
                            0x0062,             // Range Maximum
                            0x00,               // Alignment
                            0x02,               // Length
                            )
                        IO (Decode16,
                            0x0065,             // Range Minimum
                            0x0065,             // Range Maximum
                            0x00,               // Alignment
                            0x0B,               // Length
                            )
                        IO (Decode16,
                            0x0072,             // Range Minimum
                            0x0072,             // Range Maximum
                            0x00,               // Alignment
                            0x0E,               // Length
                            )
                        IO (Decode16,
                            0x0080,             // Range Minimum
                            0x0080,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0084,             // Range Minimum
                            0x0084,             // Range Maximum
                            0x00,               // Alignment
                            0x03,               // Length
                            )
                        IO (Decode16,
                            0x0088,             // Range Minimum
                            0x0088,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x008C,             // Range Minimum
                            0x008C,             // Range Maximum
                            0x00,               // Alignment
                            0x03,               // Length
                            )
                        IO (Decode16,
                            0x0090,             // Range Minimum
                            0x0090,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x00A2,             // Range Minimum
                            0x00A2,             // Range Maximum
                            0x00,               // Alignment
                            0x1E,               // Length
                            )
                        IO (Decode16,
                            0x00E0,             // Range Minimum
                            0x00E0,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x04D0,             // Range Minimum
                            0x04D0,             // Range Maximum
                            0x00,               // Alignment
                            0x02,               // Length
                            )
                    })
                    Name (CRS2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0010,             // Range Minimum
                            0x0010,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x0022,             // Range Minimum
                            0x0022,             // Range Maximum
                            0x00,               // Alignment
                            0x1E,               // Length
                            )
                        IO (Decode16,
                            0x0044,             // Range Minimum
                            0x0044,             // Range Maximum
                            0x00,               // Alignment
                            0x1C,               // Length
                            )
                        IO (Decode16,
                            0x0072,             // Range Minimum
                            0x0072,             // Range Maximum
                            0x00,               // Alignment
                            0x0E,               // Length
                            )
                        IO (Decode16,
                            0x0080,             // Range Minimum
                            0x0080,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0084,             // Range Minimum
                            0x0084,             // Range Maximum
                            0x00,               // Alignment
                            0x03,               // Length
                            )
                        IO (Decode16,
                            0x0088,             // Range Minimum
                            0x0088,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x008C,             // Range Minimum
                            0x008C,             // Range Maximum
                            0x00,               // Alignment
                            0x03,               // Length
                            )
                        IO (Decode16,
                            0x0090,             // Range Minimum
                            0x0090,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x00A2,             // Range Minimum
                            0x00A2,             // Range Maximum
                            0x00,               // Alignment
                            0x1E,               // Length
                            )
                        IO (Decode16,
                            0x00E0,             // Range Minimum
                            0x00E0,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IO (Decode16,
                            0x04D0,             // Range Minimum
                            0x04D0,             // Range Maximum
                            0x00,               // Alignment
                            0x02,               // Length
                            )
                    })
                    Method (_CRS, 0, NotSerialized)
                    {
                        If (And (MBEC, 0xFFFF))
                        {
                            Return (CRS1)
                        }
                        Else
                        {
                            Return (CRS2)
                        }
                    }
                }

                Device (COPR)
                {
                    Name (_HID, EisaId ("PNP0C04"))
                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x00F0,             // Range Minimum
                            0x00F0,             // Range Maximum
                            0x00,               // Alignment
                            0x10,               // Length
                            )
                        IRQNoFlags ()
                            {13}
                    })
                }

                Device (PS2K)
                {
                    Name (_HID, EisaId ("PNP0303"))
                    Name (_CID, EisaId ("PNP030B"))
                    Method (_STA, 0, NotSerialized)
                    {
                        If (And (IOST, 0x0400))
                        {
                            Return (0x0F)
                        }
                        Else
                        {
                            Return (Zero)
                        }
                    }

                    Name (_CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0060,             // Range Minimum
                            0x0060,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0064,             // Range Minimum
                            0x0064,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IRQNoFlags ()
                            {1}
                    })
                    Name (_PRS, ResourceTemplate ()
                    {
                        StartDependentFn (0x00, 0x00)
                        {
                            FixedIO (
                                0x0060,             // Address
                                0x01,               // Length
                                )
                            FixedIO (
                                0x0064,             // Address
                                0x01,               // Length
                                )
                            IRQNoFlags ()
                                {1}
                        }
                        EndDependentFn ()
                    })
                    Method (_PSW, 1, NotSerialized)
                    {
                        Store (Arg0, KBFG)
                    }
                }

                Scope (\)
                {
                    Name (KBFG, One)
                }

                Method (PS2K._PRW, 0, NotSerialized)
                {
                    Return (GPRW (0x1D, 0x04))
                }

                Device (PS2M)
                {
                    Name (_HID, EisaId ("PNP0F03"))
                    Name (_CID, EisaId ("PNP0F13"))
                    Method (_STA, 0, NotSerialized)
                    {
                        If (And (IOST, 0x4000))
                        {
                            Return (0x0F)
                        }
                        Else
                        {
                            Return (Zero)
                        }
                    }

                    Name (CRS1, ResourceTemplate ()
                    {
                        IRQNoFlags ()
                            {12}
                    })
                    Name (CRS2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0060,             // Range Minimum
                            0x0060,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0064,             // Range Minimum
                            0x0064,             // Range Maximum
                            0x00,               // Alignment
                            0x01,               // Length
                            )
                        IRQNoFlags ()
                            {12}
                    })
                    Method (_CRS, 0, NotSerialized)
                    {
                        If (And (IOST, 0x0400))
                        {
                            Return (CRS1)
                        }
                        Else
                        {
                            Return (CRS2)
                        }
                    }

                    Name (_PRS, ResourceTemplate ()
                    {
                        StartDependentFn (0x00, 0x00)
                        {
                            IRQNoFlags ()
                                {12}
                        }
                        EndDependentFn ()
                    })
                    Method (_PSW, 1, NotSerialized)
                    {
                        Store (Arg0, MSFG)
                    }
                }

                Scope (\)
                {
                    Name (MSFG, One)
                }

                Method (PS2M._PRW, 0, NotSerialized)
                {
                    Return (GPRW (0x1D, 0x04))
                }

                Scope (^^PCI0)
                {
                    Name (SLIC, Buffer (0x9E)
                    {
                        "374937846529Genuine NVIDIA Certified SLI Ready Motherboard for ASUS P8Z68-V PRO    56e7-Copyright 2010 NVIDIA Corporation All Rights Reserved-458103946203(R)"
                    })
                    Device (WMI1)
                    {
                        Name (_HID, "pnp0c14")
                        Name (_UID, "MXM2")
                        Name (_WDG, Buffer (0x14)
                        {
                            /* 0000 */    0x3C, 0x5C, 0xCB, 0xF6, 0xAE, 0x9C, 0xBD, 0x4E, 
                            /* 0008 */    0xB5, 0x77, 0x93, 0x1E, 0xA3, 0x2A, 0x2C, 0xC0, 
                            /* 0010 */    0x4D, 0x58, 0x01, 0x02
                        })
                        Method (WMMX, 3, NotSerialized)
                        {
                            CreateDWordField (Arg2, Zero, FUNC)
                            If (LEqual (FUNC, 0x41494C53))
                            {
                                Return (SLIC)
                            }

                            Return (Zero)
                        }
                    }
                }

                Scope (\_SB)
                {
                    Name (LUCD, Buffer (0x7D)
                    {
                        /* 0000 */    0x4C, 0x75, 0x63, 0x69, 0x64, 0x4C, 0x6F, 0x67, 
                        /* 0008 */    0x69, 0x78, 0x00, 0x68, 0x00, 0x01, 0x00, 0x01, 
                        /* 0010 */    0x00, 0x00, 0x00, 0x1A, 0x8D, 0x65, 0x61, 0x30, 
                        /* 0018 */    0x62, 0x64, 0x64, 0x30, 0x63, 0x34, 0x30, 0x66, 
                        /* 0020 */    0x35, 0x32, 0x33, 0x36, 0x66, 0x66, 0x65, 0x65, 
                        /* 0028 */    0x31, 0x30, 0x66, 0x63, 0x35, 0x37, 0x32, 0x34, 
                        /* 0030 */    0x65, 0x38, 0x31, 0x36, 0x36, 0x37, 0x38, 0x65, 
                        /* 0038 */    0x64, 0x35, 0x39, 0x34, 0x65, 0x64, 0x65, 0x65, 
                        /* 0040 */    0x65, 0x37, 0x61, 0x35, 0x32, 0x38, 0x64, 0x32, 
                        /* 0048 */    0x64, 0x31, 0x65, 0x36, 0x36, 0x32, 0x37, 0x61, 
                        /* 0050 */    0x65, 0x65, 0x64, 0x32, 0x63, 0x30, 0x30, 0x30, 
                        /* 0058 */    0x30, 0x32, 0x35, 0x36, 0x39, 0x63, 0x65, 0x64, 
                        /* 0060 */    0x31, 0x36, 0x35, 0x31, 0x36, 0x33, 0x65, 0x35, 
                        /* 0068 */    0x31, 0x65, 0x30, 0x36, 0x65, 0x30, 0x31, 0x64, 
                        /* 0070 */    0x63, 0x34, 0x34, 0x63, 0x33, 0x35, 0x66, 0x65, 
                        /* 0078 */    0x61, 0x33, 0x65, 0x61, 0x66
                    })
                }
            }

            Device (P0P1)
            {
                Name (_ADR, 0x001E0000)
                Method (_PRW, 0, NotSerialized)
                {
                    Return (GPRW (0x0B, 0x04))
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR01 ())
                    }

                    Return (PR01 ())
                }
            }

            Device (USB1)
            {
                Name (_ADR, 0x001D0001)
            }

            Device (USB2)
            {
                Name (_ADR, 0x001D0002)
            }

            Device (USB3)
            {
                Name (_ADR, 0x001D0003)
            }

            Device (USB4)
            {
                Name (_ADR, 0x001D0004)
            }

            Device (USB5)
            {
                Name (_ADR, 0x001A0001)
            }

            Device (USB6)
            {
                Name (_ADR, 0x001A0002)
            }

            Device (USB7)
            {
                Name (_ADR, 0x001A0003)
            }

            Device (RP01)
            {
                Name (_ADR, 0x001C0000)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR04 ())
                    }

                    Return (PR04 ())
                }
            }

            Device (RP02)
            {
                Name (_ADR, 0x001C0001)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR05 ())
                    }

                    Return (PR05 ())
                }
            }

            Device (RP03)
            {
                Name (_ADR, 0x001C0002)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR06 ())
                    }

                    Return (PR06 ())
                }
            }

            Device (RP04)
            {
                Name (_ADR, 0x001C0003)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR07 ())
                    }

                    Return (PR07 ())
                }

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

                    Name (PIOT, Package (0x05)
                    {
                        0x0258, 
                        0x0186, 
                        0x014A, 
                        0xB4, 
                        0x78
                    })
                    Name (UDMA, Package (0x07)
                    {
                        0x78, 
                        0x50, 
                        0x3C, 
                        0x28, 
                        0x1E, 
                        0x14, 
                        0x0F
                    })
                    Name (MDMA, Package (0x03)
                    {
                        0x01E0, 
                        0x96, 
                        0x78
                    })
                    Name (IDEB, Buffer (0x14) {})
                    CreateDWordField (IDEB, Zero, GTM0)
                    CreateDWordField (IDEB, 0x04, GTM1)
                    CreateDWordField (IDEB, 0x08, GTM2)
                    CreateDWordField (IDEB, 0x0C, GTM3)
                    CreateDWordField (IDEB, 0x10, GTM4)
                    Name (PIO0, 0x04)
                    Name (DMA0, 0x06)
                    Name (MDA0, 0x02)
                    Name (PIO1, 0x04)
                    Name (DMA1, 0x06)
                    Name (MDA1, 0x02)
                    Name (PIO2, 0x04)
                    Name (DMA2, 0x06)
                    Name (MDA2, 0x02)
                    Name (PIO3, 0x04)
                    Name (DMA3, 0x06)
                    Name (MDA3, 0x02)
                    Name (FLGP, 0x1F)
                    Name (FLGS, 0x1F)
                    Device (IDE0)
                    {
                        Name (_ADR, Zero)
                        Method (_GTM, 0, NotSerialized)
                        {
                            Store (DerefOf (Index (PIOT, PIO0)), Local0)
                            Store (DerefOf (Index (PIOT, PIO1)), Local2)
                            Store (0x1A, Local4)
                            If (LAnd (FLGP, One))
                            {
                                If (LNot (MULT))
                                {
                                    If (LAnd (CAB0, SWAP))
                                    {
                                        Store (0x02, DMA0)
                                    }
                                }

                                Store (DerefOf (Index (UDMA, DMA0)), Local1)
                                Or (Local4, One, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA0)), Local1)
                            }

                            If (LAnd (FLGP, 0x04))
                            {
                                If (LAnd (CAB0, SWAP))
                                {
                                    Store (0x02, DMA1)
                                }

                                Store (DerefOf (Index (UDMA, DMA1)), Local3)
                                Or (Local4, 0x04, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA1)), Local3)
                            }

                            Store (Local0, GTM0)
                            Store (Local1, GTM1)
                            Store (Local2, GTM2)
                            Store (Local3, GTM3)
                            Store (Local4, GTM4)
                            Return (IDEB)
                        }

                        Method (_STM, 3, NotSerialized)
                        {
                            Store (Arg0, IDEB)
                            Store (GTM0, Local0)
                            Store (GTM1, Local1)
                            Store (GTM2, Local2)
                            Store (GTM3, Local3)
                            Store (GTM4, Local4)
                            Store (Local4, FLGP)
                            If (LAnd (LNotEqual (Local0, 0xFFFFFFFF), LNotEqual (Local0, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local0, MTR, Zero, Zero), PIO0)
                            }

                            If (LAnd (LNotEqual (Local1, 0xFFFFFFFF), LNotEqual (Local1, Zero)))
                            {
                                If (LAnd (FLGP, One))
                                {
                                    Store (Match (UDMA, MEQ, Local1, MTR, Zero, Zero), DMA0)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local1, MTR, Zero, Zero), MDA0)
                                }
                            }

                            If (LAnd (LNotEqual (Local2, 0xFFFFFFFF), LNotEqual (Local2, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local2, MTR, Zero, Zero), PIO1)
                            }

                            If (LAnd (LNotEqual (Local3, 0xFFFFFFFF), LNotEqual (Local3, Zero)))
                            {
                                If (LAnd (FLGP, 0x04))
                                {
                                    Store (Match (UDMA, MEQ, Local3, MTR, Zero, Zero), DMA1)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local3, MTR, Zero, Zero), MDA1)
                                }
                            }
                        }

                        Device (DRV0)
                        {
                            Name (_ADR, Zero)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO0, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGP, One))
                                {
                                    Store (DMA0, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA0, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }

                        Device (DRV1)
                        {
                            Name (_ADR, One)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO1, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGP, 0x04))
                                {
                                    Store (DMA1, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA1, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }
                    }

                    Device (IDE1)
                    {
                        Name (_ADR, One)
                        Method (_GTM, 0, NotSerialized)
                        {
                            Store (DerefOf (Index (PIOT, PIO2)), Local0)
                            Store (DerefOf (Index (PIOT, PIO3)), Local2)
                            Store (0x1A, Local4)
                            If (LAnd (FLGS, One))
                            {
                                If (LNot (MULT))
                                {
                                    If (LAnd (CAB0, LNot (SWAP)))
                                    {
                                        Store (0x02, DMA2)
                                    }
                                }

                                Store (DerefOf (Index (UDMA, DMA2)), Local1)
                                Or (Local4, One, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA2)), Local1)
                            }

                            If (LAnd (FLGS, 0x04))
                            {
                                If (LAnd (CAB0, LNot (SWAP)))
                                {
                                    Store (0x02, DMA3)
                                }

                                Store (DerefOf (Index (UDMA, DMA3)), Local3)
                                Or (Local4, 0x04, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA3)), Local3)
                            }

                            Store (Local0, GTM0)
                            Store (Local1, GTM1)
                            Store (Local2, GTM2)
                            Store (Local3, GTM3)
                            Store (Local4, GTM4)
                            Return (IDEB)
                        }

                        Method (_STM, 3, NotSerialized)
                        {
                            Store (Arg0, IDEB)
                            Store (GTM0, Local0)
                            Store (GTM1, Local1)
                            Store (GTM2, Local2)
                            Store (GTM3, Local3)
                            Store (GTM4, Local4)
                            Store (Local4, FLGS)
                            If (LAnd (LNotEqual (Local0, 0xFFFFFFFF), LNotEqual (Local0, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local0, MTR, Zero, Zero), PIO2)
                            }

                            If (LAnd (LNotEqual (Local1, 0xFFFFFFFF), LNotEqual (Local1, Zero)))
                            {
                                If (LAnd (FLGS, One))
                                {
                                    Store (Match (UDMA, MEQ, Local1, MTR, Zero, Zero), DMA2)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local1, MTR, Zero, Zero), MDA2)
                                }
                            }

                            If (LAnd (LNotEqual (Local2, 0xFFFFFFFF), LNotEqual (Local2, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local2, MTR, Zero, Zero), PIO3)
                            }

                            If (LAnd (LNotEqual (Local3, 0xFFFFFFFF), LNotEqual (Local3, Zero)))
                            {
                                If (LAnd (FLGS, 0x04))
                                {
                                    Store (Match (UDMA, MEQ, Local3, MTR, Zero, Zero), DMA3)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local3, MTR, Zero, Zero), MDA3)
                                }
                            }
                        }

                        Device (DRV0)
                        {
                            Name (_ADR, Zero)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO2, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGS, One))
                                {
                                    Store (DMA2, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA2, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }

                        Device (DRV1)
                        {
                            Name (_ADR, One)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO3, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGS, 0x04))
                                {
                                    Store (DMA3, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA3, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }
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

                    Name (PIOT, Package (0x05)
                    {
                        0x0258, 
                        0x0186, 
                        0x014A, 
                        0xB4, 
                        0x78
                    })
                    Name (UDMA, Package (0x07)
                    {
                        0x78, 
                        0x50, 
                        0x3C, 
                        0x28, 
                        0x1E, 
                        0x14, 
                        0x0F
                    })
                    Name (MDMA, Package (0x03)
                    {
                        0x01E0, 
                        0x96, 
                        0x78
                    })
                    Name (IDEB, Buffer (0x14) {})
                    CreateDWordField (IDEB, Zero, GTM0)
                    CreateDWordField (IDEB, 0x04, GTM1)
                    CreateDWordField (IDEB, 0x08, GTM2)
                    CreateDWordField (IDEB, 0x0C, GTM3)
                    CreateDWordField (IDEB, 0x10, GTM4)
                    Name (PIO0, 0x04)
                    Name (DMA0, 0x06)
                    Name (MDA0, 0x02)
                    Name (PIO1, 0x04)
                    Name (DMA1, 0x06)
                    Name (MDA1, 0x02)
                    Name (PIO2, 0x04)
                    Name (DMA2, 0x06)
                    Name (MDA2, 0x02)
                    Name (PIO3, 0x04)
                    Name (DMA3, 0x06)
                    Name (MDA3, 0x02)
                    Name (FLGP, 0x1F)
                    Name (FLGS, 0x1F)
                    Device (IDE0)
                    {
                        Name (_ADR, Zero)
                        Method (_GTM, 0, NotSerialized)
                        {
                            Store (DerefOf (Index (PIOT, PIO0)), Local0)
                            Store (DerefOf (Index (PIOT, PIO1)), Local2)
                            Store (0x1A, Local4)
                            If (LAnd (FLGP, One))
                            {
                                If (LAnd (CAB0, SWAP))
                                {
                                    Store (0x02, DMA0)
                                }

                                Store (DerefOf (Index (UDMA, DMA0)), Local1)
                                Or (Local4, One, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA0)), Local1)
                            }

                            If (LAnd (FLGP, 0x04))
                            {
                                If (LAnd (CAB0, SWAP))
                                {
                                    Store (0x02, DMA1)
                                }

                                Store (DerefOf (Index (UDMA, DMA1)), Local3)
                                Or (Local4, 0x04, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA1)), Local3)
                            }

                            Store (Local0, GTM0)
                            Store (Local1, GTM1)
                            Store (Local2, GTM2)
                            Store (Local3, GTM3)
                            Store (Local4, GTM4)
                            Return (IDEB)
                        }

                        Method (_STM, 3, NotSerialized)
                        {
                            Store (Arg0, IDEB)
                            Store (GTM0, Local0)
                            Store (GTM1, Local1)
                            Store (GTM2, Local2)
                            Store (GTM3, Local3)
                            Store (GTM4, Local4)
                            Store (Local4, FLGP)
                            If (LAnd (LNotEqual (Local0, 0xFFFFFFFF), LNotEqual (Local0, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local0, MTR, Zero, Zero), PIO0)
                            }

                            If (LAnd (LNotEqual (Local1, 0xFFFFFFFF), LNotEqual (Local1, Zero)))
                            {
                                If (LAnd (FLGP, One))
                                {
                                    Store (Match (UDMA, MEQ, Local1, MTR, Zero, Zero), DMA0)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local1, MTR, Zero, Zero), MDA0)
                                }
                            }

                            If (LAnd (LNotEqual (Local2, 0xFFFFFFFF), LNotEqual (Local2, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local2, MTR, Zero, Zero), PIO1)
                            }

                            If (LAnd (LNotEqual (Local3, 0xFFFFFFFF), LNotEqual (Local3, Zero)))
                            {
                                If (LAnd (FLGP, 0x04))
                                {
                                    Store (Match (UDMA, MEQ, Local3, MTR, Zero, Zero), DMA1)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local3, MTR, Zero, Zero), MDA1)
                                }
                            }
                        }

                        Device (DRV0)
                        {
                            Name (_ADR, Zero)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO0, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGP, One))
                                {
                                    Store (DMA0, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA0, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }

                        Device (DRV1)
                        {
                            Name (_ADR, One)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO1, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGP, 0x04))
                                {
                                    Store (DMA1, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA1, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }
                    }

                    Device (IDE1)
                    {
                        Name (_ADR, One)
                        Method (_GTM, 0, NotSerialized)
                        {
                            Store (DerefOf (Index (PIOT, PIO2)), Local0)
                            Store (DerefOf (Index (PIOT, PIO3)), Local2)
                            Store (0x1A, Local4)
                            If (LAnd (FLGS, One))
                            {
                                If (LAnd (CAB0, LNot (SWAP)))
                                {
                                    Store (0x02, DMA2)
                                }

                                Store (DerefOf (Index (UDMA, DMA2)), Local1)
                                Or (Local4, One, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA2)), Local1)
                            }

                            If (LAnd (FLGS, 0x04))
                            {
                                If (LAnd (CAB0, LNot (SWAP)))
                                {
                                    Store (0x02, DMA3)
                                }

                                Store (DerefOf (Index (UDMA, DMA3)), Local3)
                                Or (Local4, 0x04, Local4)
                            }
                            Else
                            {
                                Store (DerefOf (Index (MDMA, MDA3)), Local3)
                            }

                            Store (Local0, GTM0)
                            Store (Local1, GTM1)
                            Store (Local2, GTM2)
                            Store (Local3, GTM3)
                            Store (Local4, GTM4)
                            Return (IDEB)
                        }

                        Method (_STM, 3, NotSerialized)
                        {
                            Store (Arg0, IDEB)
                            Store (GTM0, Local0)
                            Store (GTM1, Local1)
                            Store (GTM2, Local2)
                            Store (GTM3, Local3)
                            Store (GTM4, Local4)
                            Store (Local4, FLGS)
                            If (LAnd (LNotEqual (Local0, 0xFFFFFFFF), LNotEqual (Local0, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local0, MTR, Zero, Zero), PIO2)
                            }

                            If (LAnd (LNotEqual (Local1, 0xFFFFFFFF), LNotEqual (Local1, Zero)))
                            {
                                If (LAnd (FLGS, One))
                                {
                                    Store (Match (UDMA, MEQ, Local1, MTR, Zero, Zero), DMA2)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local1, MTR, Zero, Zero), MDA2)
                                }
                            }

                            If (LAnd (LNotEqual (Local2, 0xFFFFFFFF), LNotEqual (Local2, Zero)))
                            {
                                Store (Match (PIOT, MEQ, Local2, MTR, Zero, Zero), PIO3)
                            }

                            If (LAnd (LNotEqual (Local3, 0xFFFFFFFF), LNotEqual (Local3, Zero)))
                            {
                                If (LAnd (FLGS, 0x04))
                                {
                                    Store (Match (UDMA, MEQ, Local3, MTR, Zero, Zero), DMA3)
                                }
                                Else
                                {
                                    Store (Match (MDMA, MEQ, Local3, MTR, Zero, Zero), MDA3)
                                }
                            }
                        }

                        Device (DRV0)
                        {
                            Name (_ADR, Zero)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO2, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGS, One))
                                {
                                    Store (DMA2, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA2, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }

                        Device (DRV1)
                        {
                            Name (_ADR, One)
                            Method (_GTF, 0, NotSerialized)
                            {
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local0)
                                Store (Buffer (0x07)
                                    {
                                        0x03, 0x00, 0x00, 0x00, 0x00, 0xB0, 0xEF
                                    }, Local1)
                                CreateByteField (Local0, One, PIOM)
                                CreateByteField (Local1, One, DMAM)
                                Store (PIO3, PIOM)
                                Or (PIOM, 0x08, PIOM)
                                If (LAnd (FLGS, 0x04))
                                {
                                    Store (DMA3, DMAM)
                                    Or (DMAM, 0x40, DMAM)
                                }
                                Else
                                {
                                    Store (MDA3, DMAM)
                                    Or (DMAM, 0x20, DMAM)
                                }

                                Concatenate (Local0, Local1, Local2)
                                Return (Local2)
                            }
                        }
                    }
                }
            }

            Device (RP05)
            {
                Name (_ADR, 0x001C0004)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR08 ())
                    }

                    Return (PR08 ())
                }
            }

            Device (RP06)
            {
                Name (_ADR, 0x001C0005)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR09 ())
                    }

                    Return (PR09 ())
                }
            }

            Device (RP08)
            {
                Name (_ADR, 0x001C0007)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Name (_PRW, Package (0x02)
                    {
                        0x09, 
                        0x04
                    })
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR0F ())
                    }

                    Return (PR0F ())
                }
            }

            Device (PEG0)
            {
                Name (_ADR, 0x00010000)
                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR02 ())
                    }

                    Return (PR02 ())
                }

                Device (PEGP)
                {
                    Name (_ADR, 0xFFFF)
                }
            }

            Device (PEG1)
            {
                Name (_ADR, 0x00010001)
                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR0A ())
                    }

                    Return (PR0A ())
                }
            }

            Device (PEG2)
            {
                Name (_ADR, 0x00010002)
                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR0B ())
                    }

                    Return (PR0B ())
                }
            }

            Device (PEG3)
            {
                Name (_ADR, 0x00060000)
                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR0C ())
                    }

                    Return (PR0C ())
                }
            }

            Device (B0D4)
            {
                Name (_ADR, 0x00040000)
            }

            Device (EUSB)
            {
                Name (_ADR, 0x001D0000)
                Name (_S4D, 0x02)
                Name (_S3D, 0x02)
                Name (_S2D, 0x02)
                Name (_S1D, 0x02)
                Device (HUBN)
                {
                    Name (_ADR, Zero)
                    Device (PR10)
                    {
                        Name (_ADR, One)
                        Name (_UPC, Package (0x04)
                        {
                            0xFF, 
                            Zero, 
                            Zero, 
                            Zero
                        })
                        Name (_PLD, Buffer (0x10)
                        {
                            /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                            /* 0008 */    0x30, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                        })
                        Device (PR30)
                        {
                            Name (_ADR, One)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xE1, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR31)
                        {
                            Name (_ADR, 0x02)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xE1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR32)
                        {
                            Name (_ADR, 0x03)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xE1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR33)
                        {
                            Name (_ADR, 0x04)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xE1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR34)
                        {
                            Name (_ADR, 0x05)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR35)
                        {
                            Name (_ADR, 0x06)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR36)
                        {
                            Name (_ADR, 0x07)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xB0, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }

                        Device (PR37)
                        {
                            Name (_ADR, 0x08)
                            Name (_UPC, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Name (_PLD, Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            })
                        }
                    }
                }
            }

            Device (RP07)
            {
                Name (_ADR, 0x001C0006)
                OperationRegion (PXCS, PCI_Config, 0x40, 0xC0)
                Field (PXCS, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x10), 
                    L0SE,   1, 
                            Offset (0x11), 
                            Offset (0x12), 
                        ,   13, 
                    LASX,   1, 
                            Offset (0x1A), 
                    ABPX,   1, 
                        ,   2, 
                    PDCX,   1, 
                        ,   2, 
                    PDSX,   1, 
                            Offset (0x1B), 
                            Offset (0x20), 
                            Offset (0x22), 
                    PSPX,   1, 
                            Offset (0x98), 
                        ,   30, 
                    HPEX,   1, 
                    PMEX,   1
                }

                Field (PXCS, AnyAcc, NoLock, WriteAsZeros)
                {
                            Offset (0x9C), 
                        ,   30, 
                    HPSX,   1, 
                    PMSX,   1
                }

                Method (HPME, 0, Serialized)
                {
                    If (PMSX)
                    {
                        Store (0xC8, Local0)
                        While (Local0)
                        {
                            Store (One, PMSX)
                            If (PMSX)
                            {
                                Decrement (Local0)
                            }
                            Else
                            {
                                Store (Zero, Local0)
                            }
                        }

                        Notify (PXSX, 0x02)
                    }
                }

                Method (_PRT, 0, NotSerialized)
                {
                    If (PICM)
                    {
                        Return (AR0E ())
                    }

                    Return (PR0E ())
                }

                Device (PXSX)
                {
                    Name (_ADR, Zero)
                    Method (_PRW, 0, NotSerialized)
                    {
                        Return (GPRW (0x0B, 0x04))
                    }

                    Method (_PRT, 0, NotSerialized)
                    {
                        If (PICM)
                        {
                            Return (AR31)
                        }

                        Return (PR31)
                    }
                }
            }
        }

        Scope (\_GPE)
        {
            Method (_L1D, 0, NotSerialized)
            {
                \_SB.PCI0.LPCB.SIOH ()
                Notify (\_SB.PWRB, 0x02)
            }

            Method (_L0B, 0, NotSerialized)
            {
                Notify (\_SB.PCI0.P0P1, 0x02)
                Notify (\_SB.PCI0.RP07.PXSX, 0x02)
                Notify (\_SB.PWRB, 0x02)
            }
        }

        Device (PWRB)
        {
            Name (_HID, EisaId ("PNP0C0C"))
            Name (_UID, 0xAA)
            Name (_STA, 0x0B)
            Method (_PRW, 0, NotSerialized)
            {
                Return (GPRW (0x1D, 0x04))
            }
        }
    }

    Scope (\)
    {
        OperationRegion (IO_T, SystemIO, 0x0200, 0x10)
        Field (IO_T, ByteAcc, NoLock, Preserve)
        {
            TRPI,   16, 
                    Offset (0x04), 
                    Offset (0x06), 
                    Offset (0x08), 
            TRP0,   8, 
                    Offset (0x0A), 
                    Offset (0x0B), 
                    Offset (0x0C), 
                    Offset (0x0D), 
                    Offset (0x0E), 
                    Offset (0x0F), 
                    Offset (0x10)
        }

        OperationRegion (IO_D, SystemIO, 0x0810, 0x04)
        Field (IO_D, ByteAcc, NoLock, Preserve)
        {
            TRPD,   8
        }

        OperationRegion (IO_H, SystemIO, 0x1000, 0x04)
        Field (IO_H, ByteAcc, NoLock, Preserve)
        {
            TRPH,   8
        }

        OperationRegion (PMIO, SystemIO, PMBS, 0x80)
        Field (PMIO, ByteAcc, NoLock, Preserve)
        {
                    Offset (0x28), 
                    Offset (0x2A), 
                ,   3, 
            GPE3,   1, 
                    Offset (0x3C), 
                ,   1, 
            UPRW,   1, 
                    Offset (0x42), 
                ,   1, 
            GPEC,   1
        }

        Field (PMIO, ByteAcc, NoLock, WriteAsZeros)
        {
                    Offset (0x20), 
                    Offset (0x22), 
                ,   3, 
            GPS3,   1, 
                    Offset (0x64), 
                ,   9, 
            SCIS,   1, 
                    Offset (0x66)
        }

        OperationRegion (GPIO, SystemIO, GPBS, 0x64)
        Field (GPIO, ByteAcc, NoLock, Preserve)
        {
            GU00,   8, 
            GU01,   8, 
            GU02,   8, 
            GU03,   8, 
            GIO0,   8, 
            GIO1,   8, 
            GIO2,   8, 
            GIO3,   8, 
                    Offset (0x0C), 
            GL00,   8, 
            GL01,   8, 
            GL02,   8, 
            GP24,   1, 
                ,   2, 
            GP27,   1, 
            GP28,   1, 
                    Offset (0x10), 
                    Offset (0x18), 
            GB00,   8, 
            GB01,   8, 
            GB02,   8, 
            GB03,   8, 
                    Offset (0x2C), 
            GIV0,   8, 
            GIV1,   8, 
            GIV2,   8, 
            GIV3,   8, 
            GU04,   8, 
            GU05,   8, 
            GU06,   8, 
            GU07,   8, 
            GIO4,   8, 
            GIO5,   8, 
            GIO6,   8, 
            GIO7,   8, 
            GL04,   8, 
            GL05,   8, 
            GL06,   8, 
            GL07,   8, 
                    Offset (0x40), 
            GU08,   8, 
            GU09,   8, 
            GU0A,   8, 
            GU0B,   8, 
            GIO8,   8, 
            GIO9,   8, 
            GIOA,   8, 
            GIOB,   8, 
            GL08,   8, 
            GL09,   8, 
            GL0A,   8, 
            GL0B,   8
        }

        OperationRegion (RCRB, SystemMemory, SRCB, 0x4000)
        Field (RCRB, DWordAcc, Lock, Preserve)
        {
                    Offset (0x1000), 
                    Offset (0x3000), 
                    Offset (0x3404), 
            HPAS,   2, 
                ,   5, 
            HPAE,   1, 
                    Offset (0x3418), 
                ,   1, 
                ,   1, 
            SATD,   1, 
            SMBD,   1, 
            HDAD,   1, 
                    Offset (0x341A), 
            RP1D,   1, 
            RP2D,   1, 
            RP3D,   1, 
            RP4D,   1, 
            RP5D,   1, 
            RP6D,   1, 
            RP7D,   1, 
            RP8D,   1, 
                    Offset (0x359C), 
            UP0D,   1, 
            UP1D,   1, 
            UP2D,   1, 
            UP3D,   1, 
            UP4D,   1, 
            UP5D,   1, 
            UP6D,   1, 
            UP7D,   1, 
            UP8D,   1, 
            UP9D,   1, 
            UPAD,   1, 
            UPBD,   1, 
            UPCD,   1, 
            UPDD,   1, 
                ,   1, 
                    Offset (0x359E)
        }
    }

    Scope (_SB.PCI0)
    {
        Device (GLAN)
        {
            Name (_ADR, 0x00190000)
            Method (_PRW, 0, NotSerialized)
            {
                Return (GPRW (0x0D, 0x04))
            }
        }

        Device (EHC1)
        {
            Name (_ADR, 0x001D0000)
            OperationRegion (PWKE, PCI_Config, 0x62, 0x04)
            Field (PWKE, DWordAcc, NoLock, Preserve)
            {
                    ,   1, 
                PWUC,   8
            }

            Method (_PSW, 1, NotSerialized)
            {
                If (Arg0)
                {
                    Store (Ones, PWUC)
                }
                Else
                {
                    Store (Zero, PWUC)
                }
            }

            Method (_S3D, 0, NotSerialized)
            {
                Return (0x02)
            }

            Method (_S4D, 0, NotSerialized)
            {
                Return (0x02)
            }

            Device (HUBN)
            {
                Name (_ADR, Zero)
                Device (PR01)
                {
                    Name (_ADR, One)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCA, Package (0x04)
                        {
                            0xFF, 
                            Zero, 
                            Zero, 
                            Zero
                        })
                        Return (UPCA)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x30, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        Return (PLDP)
                    }

                    Device (PR11)
                    {
                        Name (_ADR, One)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }

                    Device (PR12)
                    {
                        Name (_ADR, 0x02)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }

                    Device (PR13)
                    {
                        Name (_ADR, 0x03)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }

                    Device (PR14)
                    {
                        Name (_ADR, 0x04)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }

                        Alias (SBV1, SDGV)
                        Method (_DSM, 4, Serialized)
                        {
                            If (LEqual (Arg0, Buffer (0x10)
                                    {
                                        /* 0000 */    0x8F, 0x70, 0xFC, 0xA5, 0x75, 0x87, 0xA6, 0x4B, 
                                        /* 0008 */    0xBD, 0x0C, 0xBA, 0x90, 0xA1, 0xEC, 0x72, 0xF8
                                    }))
                            {
                                Name (_T_0, Zero)
                                Store (ToInteger (Arg2), _T_0)
                                If (LEqual (_T_0, Zero))
                                {
                                    If (LEqual (Arg1, One))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    Else
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x00
                                        })
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, One))
                                    {
                                        If (LEqual (SDGV, 0xFF))
                                        {
                                            Return (Zero)
                                        }
                                        Else
                                        {
                                            Return (One)
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x02))
                                        {
                                            Return (SDGV)
                                        }
                                    }
                                }
                            }

                            Return (Zero)
                        }
                    }

                    Device (PR15)
                    {
                        Name (_ADR, 0x05)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }

                        Alias (SBV2, SDGV)
                        Method (_DSM, 4, Serialized)
                        {
                            If (LEqual (Arg0, Buffer (0x10)
                                    {
                                        /* 0000 */    0x8F, 0x70, 0xFC, 0xA5, 0x75, 0x87, 0xA6, 0x4B, 
                                        /* 0008 */    0xBD, 0x0C, 0xBA, 0x90, 0xA1, 0xEC, 0x72, 0xF8
                                    }))
                            {
                                Name (_T_0, Zero)
                                Store (ToInteger (Arg2), _T_0)
                                If (LEqual (_T_0, Zero))
                                {
                                    If (LEqual (Arg1, One))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    Else
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x00
                                        })
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, One))
                                    {
                                        If (LEqual (SDGV, 0xFF))
                                        {
                                            Return (Zero)
                                        }
                                        Else
                                        {
                                            Return (One)
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x02))
                                        {
                                            Return (SDGV)
                                        }
                                    }
                                }
                            }

                            Return (Zero)
                        }
                    }

                    Device (PR16)
                    {
                        Name (_ADR, 0x06)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }

                        Alias (SBV1, SDGV)
                        Method (_DSM, 4, Serialized)
                        {
                            If (LEqual (Arg0, Buffer (0x10)
                                    {
                                        /* 0000 */    0x8F, 0x70, 0xFC, 0xA5, 0x75, 0x87, 0xA6, 0x4B, 
                                        /* 0008 */    0xBD, 0x0C, 0xBA, 0x90, 0xA1, 0xEC, 0x72, 0xF8
                                    }))
                            {
                                Name (_T_0, Zero)
                                Store (ToInteger (Arg2), _T_0)
                                If (LEqual (_T_0, Zero))
                                {
                                    If (LEqual (Arg1, One))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    Else
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x00
                                        })
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, One))
                                    {
                                        If (LEqual (SDGV, 0xFF))
                                        {
                                            Return (Zero)
                                        }
                                        Else
                                        {
                                            Return (One)
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x02))
                                        {
                                            Return (SDGV)
                                        }
                                    }
                                }
                            }

                            Return (Zero)
                        }
                    }

                    Device (PR17)
                    {
                        Name (_ADR, 0x07)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }

                        Alias (SBV2, SDGV)
                        Method (_DSM, 4, Serialized)
                        {
                            If (LEqual (Arg0, Buffer (0x10)
                                    {
                                        /* 0000 */    0x8F, 0x70, 0xFC, 0xA5, 0x75, 0x87, 0xA6, 0x4B, 
                                        /* 0008 */    0xBD, 0x0C, 0xBA, 0x90, 0xA1, 0xEC, 0x72, 0xF8
                                    }))
                            {
                                Name (_T_0, Zero)
                                Store (ToInteger (Arg2), _T_0)
                                If (LEqual (_T_0, Zero))
                                {
                                    If (LEqual (Arg1, One))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    Else
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x00
                                        })
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, One))
                                    {
                                        If (LEqual (SDGV, 0xFF))
                                        {
                                            Return (Zero)
                                        }
                                        Else
                                        {
                                            Return (One)
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x02))
                                        {
                                            Return (SDGV)
                                        }
                                    }
                                }
                            }

                            Return (Zero)
                        }
                    }

                    Device (PR18)
                    {
                        Name (_ADR, 0x08)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }
                }
            }

            Method (_PRW, 0, NotSerialized)
            {
                Return (GPRW (0x0D, 0x04))
            }
        }

        Device (EHC2)
        {
            Name (_ADR, 0x001A0000)
            OperationRegion (PWKE, PCI_Config, 0x62, 0x04)
            Field (PWKE, DWordAcc, NoLock, Preserve)
            {
                    ,   1, 
                PWUC,   6
            }

            Method (_PSW, 1, NotSerialized)
            {
                If (Arg0)
                {
                    Store (Ones, PWUC)
                }
                Else
                {
                    Store (Zero, PWUC)
                }
            }

            Method (_S3D, 0, NotSerialized)
            {
                Return (0x02)
            }

            Method (_S4D, 0, NotSerialized)
            {
                Return (0x02)
            }

            Device (HUBN)
            {
                Name (_ADR, Zero)
                Device (PR01)
                {
                    Name (_ADR, One)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCA, Package (0x04)
                        {
                            0xFF, 
                            Zero, 
                            Zero, 
                            Zero
                        })
                        Return (UPCA)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x30, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        Return (PLDP)
                    }

                    Device (PR11)
                    {
                        Name (_ADR, One)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }

                    Device (PR12)
                    {
                        Name (_ADR, 0x02)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }

                        Alias (SBV1, SDGV)
                        Method (_DSM, 4, Serialized)
                        {
                            If (LEqual (Arg0, Buffer (0x10)
                                    {
                                        /* 0000 */    0x8F, 0x70, 0xFC, 0xA5, 0x75, 0x87, 0xA6, 0x4B, 
                                        /* 0008 */    0xBD, 0x0C, 0xBA, 0x90, 0xA1, 0xEC, 0x72, 0xF8
                                    }))
                            {
                                Name (_T_0, Zero)
                                Store (ToInteger (Arg2), _T_0)
                                If (LEqual (_T_0, Zero))
                                {
                                    If (LEqual (Arg1, One))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    Else
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x00
                                        })
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, One))
                                    {
                                        If (LEqual (SDGV, 0xFF))
                                        {
                                            Return (Zero)
                                        }
                                        Else
                                        {
                                            Return (One)
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x02))
                                        {
                                            Return (SDGV)
                                        }
                                    }
                                }
                            }

                            Return (Zero)
                        }
                    }

                    Device (PR13)
                    {
                        Name (_ADR, 0x03)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }

                        Alias (SBV2, SDGV)
                        Method (_DSM, 4, Serialized)
                        {
                            If (LEqual (Arg0, Buffer (0x10)
                                    {
                                        /* 0000 */    0x8F, 0x70, 0xFC, 0xA5, 0x75, 0x87, 0xA6, 0x4B, 
                                        /* 0008 */    0xBD, 0x0C, 0xBA, 0x90, 0xA1, 0xEC, 0x72, 0xF8
                                    }))
                            {
                                Name (_T_0, Zero)
                                Store (ToInteger (Arg2), _T_0)
                                If (LEqual (_T_0, Zero))
                                {
                                    If (LEqual (Arg1, One))
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x07
                                        })
                                    }
                                    Else
                                    {
                                        Return (Buffer (One)
                                        {
                                            0x00
                                        })
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, One))
                                    {
                                        If (LEqual (SDGV, 0xFF))
                                        {
                                            Return (Zero)
                                        }
                                        Else
                                        {
                                            Return (One)
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x02))
                                        {
                                            Return (SDGV)
                                        }
                                    }
                                }
                            }

                            Return (Zero)
                        }
                    }

                    Device (PR14)
                    {
                        Name (_ADR, 0x04)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xE1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }

                    Device (PR15)
                    {
                        Name (_ADR, 0x05)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }

                    Device (PR16)
                    {
                        Name (_ADR, 0x06)
                        Method (_UPC, 0, Serialized)
                        {
                            Name (UPCP, Package (0x04)
                            {
                                0xFF, 
                                0xFF, 
                                Zero, 
                                Zero
                            })
                            Return (UPCP)
                        }

                        Method (_PLD, 0, Serialized)
                        {
                            Name (PLDP, Package (0x01)
                            {
                                Buffer (0x10)
                                {
                                    /* 0000 */    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                    /* 0008 */    0xB1, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                }
                            })
                            Return (PLDP)
                        }
                    }
                }
            }

            Method (_PRW, 0, NotSerialized)
            {
                Return (GPRW (0x0D, 0x04))
            }
        }

        Device (XHC)
        {
            Name (_ADR, 0x00140000)
            OperationRegion (XPRT, PCI_Config, 0xD0, 0x10)
            Field (XPRT, DWordAcc, NoLock, Preserve)
            {
                PR2,    32, 
                PR2M,   32, 
                PR3,    32, 
                PR3M,   32
            }

            Method (CUID, 1, Serialized)
            {
                If (LEqual (Arg0, Buffer (0x10)
                        {
                            /* 0000 */    0xA9, 0x12, 0x95, 0x7C, 0x05, 0x17, 0xB4, 0x4C, 
                            /* 0008 */    0xAF, 0x7D, 0x50, 0x6A, 0x24, 0x23, 0xAB, 0x71
                        }))
                {
                    Return (One)
                }

                Return (Zero)
            }

            Method (POSC, 3, Serialized)
            {
                CreateDWordField (Arg2, Zero, CDW1)
                If (LNotEqual (Arg1, One))
                {
                    Or (CDW1, 0x08, CDW1)
                }

                If (LEqual (XHCI, Zero))
                {
                    Or (CDW1, 0x02, CDW1)
                }

                If (LNot (And (CDW1, One)))
                {
                    XSEL ()
                }

                Return (Arg2)
            }

            Method (XSEL, 0, Serialized)
            {
                If (LOr (LEqual (XHCI, 0x02), LEqual (XHCI, 0x03)))
                {
                    Store (Zero, Local0)
                    And (PR3, 0xFFFFFFF0, Local0)
                    Or (Local0, XHPM, Local0)
                    And (Local0, PR3M, PR3)
                    Store (Zero, Local0)
                    And (PR2, 0xFFFFFFF0, Local0)
                    Or (Local0, XHPM, Local0)
                    And (Local0, PR2M, PR2)
                    Store (One, XUSB)
                }
            }

            Method (_S3D, 0, NotSerialized)
            {
                Return (0x02)
            }

            Method (_S4D, 0, NotSerialized)
            {
                Return (0x02)
            }

            Device (RHUB)
            {
                Name (_ADR, Zero)
                Device (HSP1)
                {
                    Name (_ADR, One)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR2, One)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR2, One)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (HSP2)
                {
                    Name (_ADR, 0x02)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR2, 0x02)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR2, 0x02)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (HSP3)
                {
                    Name (_ADR, 0x03)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR2, 0x04)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR2, 0x04)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (HSP4)
                {
                    Name (_ADR, 0x04)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR2, 0x08)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR2, 0x08)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (SSP1)
                {
                    Name (_ADR, 0x05)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR3, One)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR3, One)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (SSP2)
                {
                    Name (_ADR, 0x06)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR3, 0x02)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR3, 0x02)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (SSP3)
                {
                    Name (_ADR, 0x07)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR3, 0x04)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR3, 0x04)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }

                Device (SSP4)
                {
                    Name (_ADR, 0x08)
                    Method (_UPC, 0, Serialized)
                    {
                        Name (UPCP, Package (0x04)
                        {
                            0xFF, 
                            0x03, 
                            Zero, 
                            Zero
                        })
                        If (LNot (And (PR3, 0x08)))
                        {
                            Store (Zero, Index (UPCP, Zero))
                        }

                        Return (UPCP)
                    }

                    Method (_PLD, 0, Serialized)
                    {
                        Name (PLDP, Package (0x01)
                        {
                            Buffer (0x10)
                            {
                                /* 0000 */    0x01, 0xC6, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                /* 0008 */    0x69, 0x0C, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
                            }
                        })
                        CreateBitField (DerefOf (Index (PLDP, Zero)), 0x40, VIS)
                        If (LNot (And (PR3, 0x08)))
                        {
                            And (VIS, Zero, VIS)
                        }

                        Return (PLDP)
                    }
                }
            }

            Method (_PRW, 0, NotSerialized)
            {
                Return (GPRW (0x0D, 0x04))
            }
        }

        Device (HDEF)
        {
            Name (_ADR, 0x001B0000)
            OperationRegion (HDAR, PCI_Config, 0x4C, 0x10)
            Field (HDAR, WordAcc, NoLock, Preserve)
            {
                DCKA,   1, 
                        Offset (0x01), 
                DCKM,   1, 
                    ,   6, 
                DCKS,   1, 
                        Offset (0x08), 
                    ,   15, 
                PMES,   1
            }

            Method (_PRW, 0, NotSerialized)
            {
                Return (GPRW (0x0D, 0x04))
            }
        }

        Device (SAT0)
        {
            Name (_ADR, 0x001F0002)
        }

        Device (SAT1)
        {
            Name (_ADR, 0x001F0005)
        }

        Device (SBUS)
        {
            Name (_ADR, 0x001F0003)
            OperationRegion (SMBP, PCI_Config, 0x40, 0xC0)
            Field (SMBP, DWordAcc, NoLock, Preserve)
            {
                    ,   2, 
                I2CE,   1
            }

            OperationRegion (SMPB, PCI_Config, 0x20, 0x04)
            Field (SMPB, DWordAcc, NoLock, Preserve)
            {
                    ,   5, 
                SBAR,   11
            }

            OperationRegion (SMBI, SystemIO, ShiftLeft (SBAR, 0x05), 0x10)
            Field (SMBI, ByteAcc, NoLock, Preserve)
            {
                HSTS,   8, 
                        Offset (0x02), 
                HCON,   8, 
                HCOM,   8, 
                TXSA,   8, 
                DAT0,   8, 
                DAT1,   8, 
                HBDR,   8, 
                PECR,   8, 
                RXSA,   8, 
                SDAT,   16
            }

            Method (SSXB, 2, Serialized)
            {
                If (STRT ())
                {
                    Return (Zero)
                }

                Store (Zero, I2CE)
                Store (0xBF, HSTS)
                Store (Arg0, TXSA)
                Store (Arg1, HCOM)
                Store (0x48, HCON)
                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (One)
                }

                Return (Zero)
            }

            Method (SRXB, 1, Serialized)
            {
                If (STRT ())
                {
                    Return (0xFFFF)
                }

                Store (Zero, I2CE)
                Store (0xBF, HSTS)
                Store (Or (Arg0, One), TXSA)
                Store (0x44, HCON)
                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (DAT0)
                }

                Return (0xFFFF)
            }

            Method (SWRB, 3, Serialized)
            {
                If (STRT ())
                {
                    Return (Zero)
                }

                Store (Zero, I2CE)
                Store (0xBF, HSTS)
                Store (Arg0, TXSA)
                Store (Arg1, HCOM)
                Store (Arg2, DAT0)
                Store (0x48, HCON)
                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (One)
                }

                Return (Zero)
            }

            Method (SRDB, 2, Serialized)
            {
                If (STRT ())
                {
                    Return (0xFFFF)
                }

                Store (Zero, I2CE)
                Store (0xBF, HSTS)
                Store (Or (Arg0, One), TXSA)
                Store (Arg1, HCOM)
                Store (0x48, HCON)
                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (DAT0)
                }

                Return (0xFFFF)
            }

            Method (SWRW, 3, Serialized)
            {
                If (STRT ())
                {
                    Return (Zero)
                }

                Store (Zero, I2CE)
                Store (0xBF, HSTS)
                Store (Arg0, TXSA)
                Store (Arg1, HCOM)
                And (Arg2, 0xFF, DAT1)
                And (ShiftRight (Arg2, 0x08), 0xFF, DAT0)
                Store (0x4C, HCON)
                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (One)
                }

                Return (Zero)
            }

            Method (SRDW, 2, Serialized)
            {
                If (STRT ())
                {
                    Return (0xFFFF)
                }

                Store (Zero, I2CE)
                Store (0xBF, HSTS)
                Store (Or (Arg0, One), TXSA)
                Store (Arg1, HCOM)
                Store (0x4C, HCON)
                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (Or (ShiftLeft (DAT0, 0x08), DAT1))
                }

                Return (0xFFFFFFFF)
            }

            Method (SBLW, 4, Serialized)
            {
                If (STRT ())
                {
                    Return (Zero)
                }

                Store (Arg3, I2CE)
                Store (0xBF, HSTS)
                Store (Arg0, TXSA)
                Store (Arg1, HCOM)
                Store (SizeOf (Arg2), DAT0)
                Store (Zero, Local1)
                Store (DerefOf (Index (Arg2, Zero)), HBDR)
                Store (0x54, HCON)
                While (LGreater (SizeOf (Arg2), Local1))
                {
                    Store (0x0FA0, Local0)
                    While (LAnd (LNot (And (HSTS, 0x80)), Local0))
                    {
                        Decrement (Local0)
                        Stall (0x32)
                    }

                    If (LNot (Local0))
                    {
                        KILL ()
                        Return (Zero)
                    }

                    Store (0x80, HSTS)
                    Increment (Local1)
                    If (LGreater (SizeOf (Arg2), Local1))
                    {
                        Store (DerefOf (Index (Arg2, Local1)), HBDR)
                    }
                }

                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (One)
                }

                Return (Zero)
            }

            Method (SBLR, 3, Serialized)
            {
                Name (TBUF, Buffer (0x0100) {})
                If (STRT ())
                {
                    Return (Zero)
                }

                Store (Arg2, I2CE)
                Store (0xBF, HSTS)
                Store (Or (Arg0, One), TXSA)
                Store (Arg1, HCOM)
                Store (0x54, HCON)
                Store (0x0FA0, Local0)
                While (LAnd (LNot (And (HSTS, 0x80)), Local0))
                {
                    Decrement (Local0)
                    Stall (0x32)
                }

                If (LNot (Local0))
                {
                    KILL ()
                    Return (Zero)
                }

                Store (DAT0, Index (TBUF, Zero))
                Store (0x80, HSTS)
                Store (One, Local1)
                While (LLess (Local1, DerefOf (Index (TBUF, Zero))))
                {
                    Store (0x0FA0, Local0)
                    While (LAnd (LNot (And (HSTS, 0x80)), Local0))
                    {
                        Decrement (Local0)
                        Stall (0x32)
                    }

                    If (LNot (Local0))
                    {
                        KILL ()
                        Return (Zero)
                    }

                    Store (HBDR, Index (TBUF, Local1))
                    Store (0x80, HSTS)
                    Increment (Local1)
                }

                If (COMP ())
                {
                    Or (HSTS, 0xFF, HSTS)
                    Return (TBUF)
                }

                Return (Zero)
            }

            Method (STRT, 0, Serialized)
            {
                Store (0xC8, Local0)
                While (Local0)
                {
                    If (And (HSTS, 0x40))
                    {
                        Decrement (Local0)
                        Sleep (One)
                        If (LEqual (Local0, Zero))
                        {
                            Return (One)
                        }
                    }
                    Else
                    {
                        Store (Zero, Local0)
                    }
                }

                Store (0x0FA0, Local0)
                While (Local0)
                {
                    If (And (HSTS, One))
                    {
                        Decrement (Local0)
                        Stall (0x32)
                        If (LEqual (Local0, Zero))
                        {
                            KILL ()
                        }
                    }
                    Else
                    {
                        Return (Zero)
                    }
                }

                Return (One)
            }

            Method (COMP, 0, Serialized)
            {
                Store (0x0FA0, Local0)
                While (Local0)
                {
                    If (And (HSTS, 0x02))
                    {
                        Return (One)
                    }
                    Else
                    {
                        Decrement (Local0)
                        Stall (0x32)
                        If (LEqual (Local0, Zero))
                        {
                            KILL ()
                        }
                    }
                }

                Return (Zero)
            }

            Method (KILL, 0, Serialized)
            {
                Or (HCON, 0x02, HCON)
                Or (HSTS, 0xFF, HSTS)
            }
        }
    }

    Scope (_SB.PCI0.LPCB)
    {
        OperationRegion (CPSB, SystemMemory, 0xDCBC5F98, 0x10)
        Field (CPSB, AnyAcc, NoLock, Preserve)
        {
            RTCX,   1, 
            SBB0,   7, 
            SBB1,   8, 
            SBB2,   8, 
            SBB3,   8, 
            SBB4,   8, 
            SBB5,   8, 
            SBB6,   8, 
            SBB7,   8, 
            SBB8,   8, 
            SBB9,   8, 
            SBBA,   8, 
            SBBB,   8, 
            SBBC,   8, 
            SBBD,   8, 
            SBBE,   8, 
            SBBF,   8
        }

        Method (SPTS, 1, NotSerialized)
        {
            Store (One, SLPX)
            Store (One, SLPE)
        }

        Method (SWAK, 1, NotSerialized)
        {
            Store (Zero, SLPE)
            If (RTCX) {}
            Else
            {
                Notify (PWRB, 0x02)
            }
        }

        OperationRegion (SMIE, SystemIO, PMBS, 0x04)
        Field (SMIE, ByteAcc, NoLock, Preserve)
        {
                ,   10, 
            RTCS,   1, 
                ,   3, 
            PEXS,   1, 
            WAKS,   1, 
                    Offset (0x03), 
            PWBT,   1, 
                    Offset (0x04)
        }

        OperationRegion (SLPR, SystemIO, SMCR, 0x08)
        Field (SLPR, ByteAcc, NoLock, Preserve)
        {
                ,   4, 
            SLPE,   1, 
                ,   31, 
            SLPX,   1, 
                    Offset (0x08)
        }
    }

    Scope (_SB.PCI0.RP01)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP02)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP03)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP04)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP05)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP06)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP07)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.RP08)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    OperationRegion (_SB.PCI0.LPCB.LPCR, PCI_Config, 0x80, 0x04)
    Field (\_SB.PCI0.LPCB.LPCR, ByteAcc, NoLock, Preserve)
    {
        CADR,   3, 
            ,   1, 
        CBDR,   3, 
                Offset (0x01), 
        LTDR,   2, 
            ,   2, 
        FDDR,   1, 
                Offset (0x02), 
        CALE,   1, 
        CBLE,   1, 
        LTLE,   1, 
        FDLE,   1, 
                Offset (0x03), 
        GLLE,   1, 
        GHLE,   1, 
        KCLE,   1, 
        MCLE,   1, 
        C1LE,   1, 
        C2LE,   1, 
                Offset (0x04)
    }

    Method (UXDV, 1, NotSerialized)
    {
        Store (0xFF, Local0)
        Name (_T_0, Zero)
        Store (Add (Arg0, Zero), _T_0)
        If (LEqual (_T_0, 0x03F8))
        {
            Store (Zero, Local0)
        }
        Else
        {
            If (LEqual (_T_0, 0x02F8))
            {
                Store (One, Local0)
            }
            Else
            {
                If (LEqual (_T_0, 0x0220))
                {
                    Store (0x02, Local0)
                }
                Else
                {
                    If (LEqual (_T_0, 0x0228))
                    {
                        Store (0x03, Local0)
                    }
                    Else
                    {
                        If (LEqual (_T_0, 0x0238))
                        {
                            Store (0x04, Local0)
                        }
                        Else
                        {
                            If (LEqual (_T_0, 0x02E8))
                            {
                                Store (0x05, Local0)
                            }
                            Else
                            {
                                If (LEqual (_T_0, 0x0338))
                                {
                                    Store (0x06, Local0)
                                }
                                Else
                                {
                                    If (LEqual (_T_0, 0x03E8))
                                    {
                                        Store (0x07, Local0)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Return (Local0)
    }

    Method (RRIO, 4, NotSerialized)
    {
        Name (_T_0, Zero)
        Store (Add (Arg0, Zero), _T_0)
        If (LEqual (_T_0, Zero))
        {
            Store (Zero, CALE)
            Store (UXDV (Arg2), Local0)
            If (LNotEqual (Local0, 0xFF))
            {
                Store (Local0, CADR)
            }

            If (Arg1)
            {
                Store (One, CALE)
            }
        }
        Else
        {
            If (LEqual (_T_0, One))
            {
                Store (Zero, CBLE)
                Store (UXDV (Arg2), Local0)
                If (LNotEqual (Local0, 0xFF))
                {
                    Store (Local0, CBDR)
                }

                If (Arg1)
                {
                    Store (One, CBLE)
                }
            }
            Else
            {
                If (LEqual (_T_0, 0x02))
                {
                    Store (Zero, LTLE)
                    If (LEqual (Arg2, 0x0378))
                    {
                        Store (Zero, LTDR)
                    }

                    If (LEqual (Arg2, 0x0278))
                    {
                        Store (One, LTDR)
                    }

                    If (LEqual (Arg2, 0x03BC))
                    {
                        Store (0x02, LTDR)
                    }

                    If (Arg1)
                    {
                        Store (One, LTLE)
                    }
                }
                Else
                {
                    If (LEqual (_T_0, 0x03))
                    {
                        Store (Zero, FDLE)
                        If (LEqual (Arg2, 0x03F0))
                        {
                            Store (Zero, FDDR)
                        }

                        If (LEqual (Arg2, 0x0370))
                        {
                            Store (One, FDDR)
                        }

                        If (Arg1)
                        {
                            Store (One, FDLE)
                        }
                    }
                    Else
                    {
                        If (LEqual (_T_0, 0x08))
                        {
                            If (LEqual (Arg2, 0x0200))
                            {
                                If (Arg1)
                                {
                                    Store (One, GLLE)
                                }
                                Else
                                {
                                    Store (Zero, GLLE)
                                }
                            }

                            If (LEqual (Arg2, 0x0208))
                            {
                                If (Arg1)
                                {
                                    Store (One, GHLE)
                                }
                                Else
                                {
                                    Store (Zero, GHLE)
                                }
                            }
                        }
                        Else
                        {
                            If (LEqual (_T_0, 0x09))
                            {
                                If (LEqual (Arg2, 0x0200))
                                {
                                    If (Arg1)
                                    {
                                        Store (One, GLLE)
                                    }
                                    Else
                                    {
                                        Store (Zero, GLLE)
                                    }
                                }

                                If (LEqual (Arg2, 0x0208))
                                {
                                    If (Arg1)
                                    {
                                        Store (One, GHLE)
                                    }
                                    Else
                                    {
                                        Store (Zero, GHLE)
                                    }
                                }
                            }
                            Else
                            {
                                If (LEqual (_T_0, 0x0A))
                                {
                                    If (LOr (LEqual (Arg2, 0x60), LEqual (Arg2, 0x64)))
                                    {
                                        If (Arg1)
                                        {
                                            Store (One, KCLE)
                                        }
                                        Else
                                        {
                                            Store (Zero, KCLE)
                                        }
                                    }
                                }
                                Else
                                {
                                    If (LEqual (_T_0, 0x0B))
                                    {
                                        If (LOr (LEqual (Arg2, 0x62), LEqual (Arg2, 0x66)))
                                        {
                                            If (Arg1)
                                            {
                                                Store (One, MCLE)
                                            }
                                            Else
                                            {
                                                Store (Zero, MCLE)
                                            }
                                        }
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x0C))
                                        {
                                            If (LEqual (Arg2, 0x2E))
                                            {
                                                If (Arg1)
                                                {
                                                    Store (One, C1LE)
                                                }
                                                Else
                                                {
                                                    Store (Zero, C1LE)
                                                }
                                            }

                                            If (LEqual (Arg2, 0x4E))
                                            {
                                                If (Arg1)
                                                {
                                                    Store (One, C2LE)
                                                }
                                                Else
                                                {
                                                    Store (Zero, C2LE)
                                                }
                                            }
                                        }
                                        Else
                                        {
                                            If (LEqual (_T_0, 0x0D))
                                            {
                                                If (LEqual (Arg2, 0x2E))
                                                {
                                                    If (Arg1)
                                                    {
                                                        Store (One, C1LE)
                                                    }
                                                    Else
                                                    {
                                                        Store (Zero, C1LE)
                                                    }
                                                }

                                                If (LEqual (Arg2, 0x4E))
                                                {
                                                    If (Arg1)
                                                    {
                                                        Store (One, C2LE)
                                                    }
                                                    Else
                                                    {
                                                        Store (Zero, C2LE)
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Method (RDMA, 3, NotSerialized)
    {
    }

    Scope (_SB.PCI0)
    {
        Method (NPTS, 1, NotSerialized)
        {
        }

        Method (NWAK, 1, NotSerialized)
        {
        }
    }

    Scope (_SB.PCI0.PEG0)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.PEG0.PEGP)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.PEG1)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.PEG2)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0.PEG3)
    {
        Method (_PRW, 0, NotSerialized)
        {
            Return (GPRW (0x09, 0x04))
        }
    }

    Scope (_SB.PCI0)
    {
        Device (GFX0)
        {
            Name (_ADR, 0x00020000)
            Method (PCPC, 0, NotSerialized)
            {
                If (ECON)
                {
                    Store (0x02, ^^LPCB.H_EC.SLPC)
                }

                ECST (0x6F)
            }

            Method (PAPR, 0, NotSerialized)
            {
                If (ECON)
                {
                    Return (Divide (^^LPCB.H_EC.MCAP, 0x64, ))
                }
                Else
                {
                    Return (Zero)
                }
            }

            Method (_DOS, 1, NotSerialized)
            {
                Store (And (Arg0, 0x07), DSEN)
                If (LEqual (And (Arg0, 0x03), Zero))
                {
                    If (CondRefOf (HDOS))
                    {
                        HDOS ()
                    }
                }
            }

            Method (_DOD, 0, NotSerialized)
            {
                If (CondRefOf (IDAB))
                {
                    IDAB ()
                }
                Else
                {
                    Store (Zero, NDID)
                    If (LNotEqual (DIDL, Zero))
                    {
                        Store (SDDL (DIDL), DID1)
                    }

                    If (LNotEqual (DDL2, Zero))
                    {
                        Store (SDDL (DDL2), DID2)
                    }

                    If (LNotEqual (DDL3, Zero))
                    {
                        Store (SDDL (DDL3), DID3)
                    }

                    If (LNotEqual (DDL4, Zero))
                    {
                        Store (SDDL (DDL4), DID4)
                    }

                    If (LNotEqual (DDL5, Zero))
                    {
                        Store (SDDL (DDL5), DID5)
                    }

                    If (LNotEqual (DDL6, Zero))
                    {
                        Store (SDDL (DDL6), DID6)
                    }

                    If (LNotEqual (DDL7, Zero))
                    {
                        Store (SDDL (DDL7), DID7)
                    }

                    If (LNotEqual (DDL8, Zero))
                    {
                        Store (SDDL (DDL8), DID8)
                    }
                }

                If (LEqual (NDID, One))
                {
                    Name (TMP1, Package (0x01)
                    {
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP1, Zero))
                    Return (TMP1)
                }

                If (LEqual (NDID, 0x02))
                {
                    Name (TMP2, Package (0x02)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP2, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP2, One))
                    Return (TMP2)
                }

                If (LEqual (NDID, 0x03))
                {
                    Name (TMP3, Package (0x03)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP3, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP3, One))
                    Store (Or (0x00010000, DID3), Index (TMP3, 0x02))
                    Return (TMP3)
                }

                If (LEqual (NDID, 0x04))
                {
                    Name (TMP4, Package (0x04)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP4, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP4, One))
                    Store (Or (0x00010000, DID3), Index (TMP4, 0x02))
                    Store (Or (0x00010000, DID4), Index (TMP4, 0x03))
                    Return (TMP4)
                }

                If (LEqual (NDID, 0x05))
                {
                    Name (TMP5, Package (0x05)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP5, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP5, One))
                    Store (Or (0x00010000, DID3), Index (TMP5, 0x02))
                    Store (Or (0x00010000, DID4), Index (TMP5, 0x03))
                    Store (Or (0x00010000, DID5), Index (TMP5, 0x04))
                    Return (TMP5)
                }

                If (LEqual (NDID, 0x06))
                {
                    Name (TMP6, Package (0x06)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP6, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP6, One))
                    Store (Or (0x00010000, DID3), Index (TMP6, 0x02))
                    Store (Or (0x00010000, DID4), Index (TMP6, 0x03))
                    Store (Or (0x00010000, DID5), Index (TMP6, 0x04))
                    Store (Or (0x00010000, DID6), Index (TMP6, 0x05))
                    Return (TMP6)
                }

                If (LEqual (NDID, 0x07))
                {
                    Name (TMP7, Package (0x07)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP7, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP7, One))
                    Store (Or (0x00010000, DID3), Index (TMP7, 0x02))
                    Store (Or (0x00010000, DID4), Index (TMP7, 0x03))
                    Store (Or (0x00010000, DID5), Index (TMP7, 0x04))
                    Store (Or (0x00010000, DID6), Index (TMP7, 0x05))
                    Store (Or (0x00010000, DID7), Index (TMP7, 0x06))
                    Return (TMP7)
                }

                If (LEqual (NDID, 0x08))
                {
                    Name (TMP8, Package (0x08)
                    {
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF, 
                        0xFFFFFFFF
                    })
                    Store (Or (0x00010000, DID1), Index (TMP8, Zero))
                    Store (Or (0x00010000, DID2), Index (TMP8, One))
                    Store (Or (0x00010000, DID3), Index (TMP8, 0x02))
                    Store (Or (0x00010000, DID4), Index (TMP8, 0x03))
                    Store (Or (0x00010000, DID5), Index (TMP8, 0x04))
                    Store (Or (0x00010000, DID6), Index (TMP8, 0x05))
                    Store (Or (0x00010000, DID7), Index (TMP8, 0x06))
                    Store (Or (0x00010000, DID8), Index (TMP8, 0x07))
                    Return (TMP8)
                }

                If (LEqual (NDID, 0x09))
                {
                    If (CondRefOf (HWID))
                    {
                        Return (HWID)
                    }
                }

                Return (Package (0x01)
                {
                    0x0400
                })
            }

            Device (DD01)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID1, Zero))
                    {
                        Return (One)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID1))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    Return (CDDS (DID1))
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD1)
                    }

                    Return (NDDS (DID1))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Device (DD02)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID2, Zero))
                    {
                        Return (0x02)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID2))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (LIDS, Zero))
                    {
                        Return (Zero)
                    }

                    Return (CDDS (DID2))
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD2)
                    }

                    Return (NDDS (DID2))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }

                Method (_BCL, 0, NotSerialized)
                {
                    Return (Package (0x17)
                    {
                        0x50, 
                        0x32, 
                        Zero, 
                        0x05, 
                        0x0A, 
                        0x0F, 
                        0x14, 
                        0x19, 
                        0x1E, 
                        0x23, 
                        0x28, 
                        0x2D, 
                        0x32, 
                        0x37, 
                        0x3C, 
                        0x41, 
                        0x46, 
                        0x4B, 
                        0x50, 
                        0x55, 
                        0x5A, 
                        0x5F, 
                        0x64
                    })
                }

                Method (_BCM, 1, NotSerialized)
                {
                    If (LAnd (LGreaterEqual (Arg0, Zero), LLessEqual (Arg0, 0x64)))
                    {
                        AINT (One, Arg0)
                        Store (Arg0, BRTL)
                    }
                }

                Method (_BQC, 0, NotSerialized)
                {
                    Return (BRTL)
                }
            }

            Device (DD03)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID3, Zero))
                    {
                        Return (0x03)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID3))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (DID3, Zero))
                    {
                        Return (0x0B)
                    }
                    Else
                    {
                        Return (CDDS (DID3))
                    }
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD3)
                    }

                    Return (NDDS (DID3))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Device (DD04)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID4, Zero))
                    {
                        Return (0x04)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID4))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (DID4, Zero))
                    {
                        Return (0x0B)
                    }
                    Else
                    {
                        Return (CDDS (DID4))
                    }
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD4)
                    }

                    Return (NDDS (DID4))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Device (DD05)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID5, Zero))
                    {
                        Return (0x05)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID5))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (DID5, Zero))
                    {
                        Return (0x0B)
                    }
                    Else
                    {
                        Return (CDDS (DID5))
                    }
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD5)
                    }

                    Return (NDDS (DID5))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Device (DD06)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID6, Zero))
                    {
                        Return (0x06)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID6))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (DID6, Zero))
                    {
                        Return (0x0B)
                    }
                    Else
                    {
                        Return (CDDS (DID6))
                    }
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD6)
                    }

                    Return (NDDS (DID6))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Device (DD07)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID7, Zero))
                    {
                        Return (0x07)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID7))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (DID7, Zero))
                    {
                        Return (0x0B)
                    }
                    Else
                    {
                        Return (CDDS (DID7))
                    }
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD7)
                    }

                    Return (NDDS (DID7))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Device (DD08)
            {
                Method (_ADR, 0, Serialized)
                {
                    If (LEqual (DID8, Zero))
                    {
                        Return (0x08)
                    }
                    Else
                    {
                        Return (And (0xFFFF, DID8))
                    }
                }

                Method (_DCS, 0, NotSerialized)
                {
                    If (LEqual (DID8, Zero))
                    {
                        Return (0x0B)
                    }
                    Else
                    {
                        Return (CDDS (DID8))
                    }
                }

                Method (_DGS, 0, NotSerialized)
                {
                    If (LAnd (LEqual (And (SGMD, 0x7F), One), CondRefOf (SNXD
                        )))
                    {
                        Return (NXD8)
                    }

                    Return (NDDS (DID8))
                }

                Method (_DSS, 1, NotSerialized)
                {
                    If (LEqual (And (Arg0, 0xC0000000), 0xC0000000))
                    {
                        Store (NSTE, CSTE)
                    }
                }
            }

            Method (SDDL, 1, NotSerialized)
            {
                Increment (NDID)
                Store (And (Arg0, 0x0F0F), Local0)
                Or (0x80000000, Local0, Local1)
                If (LEqual (DIDL, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL2, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL3, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL4, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL5, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL6, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL7, Local0))
                {
                    Return (Local1)
                }

                If (LEqual (DDL8, Local0))
                {
                    Return (Local1)
                }

                Return (Zero)
            }

            Method (CDDS, 1, NotSerialized)
            {
                Store (And (Arg0, 0x0F0F), Local0)
                If (LEqual (Zero, Local0))
                {
                    Return (0x1D)
                }

                If (LEqual (CADL, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL2, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL3, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL4, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL5, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL6, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL7, Local0))
                {
                    Return (0x1F)
                }

                If (LEqual (CAL8, Local0))
                {
                    Return (0x1F)
                }

                Return (0x1D)
            }

            Method (NDDS, 1, NotSerialized)
            {
                Store (And (Arg0, 0x0F0F), Local0)
                If (LEqual (Zero, Local0))
                {
                    Return (Zero)
                }

                If (LEqual (NADL, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL2, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL3, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL4, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL5, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL6, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL7, Local0))
                {
                    Return (One)
                }

                If (LEqual (NDL8, Local0))
                {
                    Return (One)
                }

                Return (Zero)
            }

            Scope (^^PCI0)
            {
                OperationRegion (MCHP, PCI_Config, 0x40, 0xC0)
                Field (MCHP, AnyAcc, NoLock, Preserve)
                {
                            Offset (0x60), 
                    TASM,   10, 
                            Offset (0x62)
                }
            }

            OperationRegion (IGDP, PCI_Config, 0x40, 0xC0)
            Field (IGDP, AnyAcc, NoLock, Preserve)
            {
                        Offset (0x12), 
                    ,   1, 
                GIVD,   1, 
                    ,   2, 
                GUMA,   3, 
                        Offset (0x14), 
                    ,   4, 
                GMFN,   1, 
                        Offset (0x18), 
                        Offset (0xA4), 
                ASLE,   8, 
                        Offset (0xA8), 
                GSSE,   1, 
                GSSB,   14, 
                GSES,   1, 
                        Offset (0xB0), 
                    ,   12, 
                CDVL,   1, 
                        Offset (0xB2), 
                        Offset (0xB5), 
                LBPC,   8, 
                        Offset (0xBC), 
                ASLS,   32
            }

            OperationRegion (IGDM, SystemMemory, ASLB, 0x2000)
            Field (IGDM, AnyAcc, NoLock, Preserve)
            {
                SIGN,   128, 
                SIZE,   32, 
                OVER,   32, 
                SVER,   256, 
                VVER,   128, 
                GVER,   128, 
                MBOX,   32, 
                DMOD,   32, 
                        Offset (0x100), 
                DRDY,   32, 
                CSTS,   32, 
                CEVT,   32, 
                        Offset (0x120), 
                DIDL,   32, 
                DDL2,   32, 
                DDL3,   32, 
                DDL4,   32, 
                DDL5,   32, 
                DDL6,   32, 
                DDL7,   32, 
                DDL8,   32, 
                CPDL,   32, 
                CPL2,   32, 
                CPL3,   32, 
                CPL4,   32, 
                CPL5,   32, 
                CPL6,   32, 
                CPL7,   32, 
                CPL8,   32, 
                CADL,   32, 
                CAL2,   32, 
                CAL3,   32, 
                CAL4,   32, 
                CAL5,   32, 
                CAL6,   32, 
                CAL7,   32, 
                CAL8,   32, 
                NADL,   32, 
                NDL2,   32, 
                NDL3,   32, 
                NDL4,   32, 
                NDL5,   32, 
                NDL6,   32, 
                NDL7,   32, 
                NDL8,   32, 
                ASLP,   32, 
                TIDX,   32, 
                CHPD,   32, 
                CLID,   32, 
                CDCK,   32, 
                SXSW,   32, 
                EVTS,   32, 
                CNOT,   32, 
                NRDY,   32, 
                        Offset (0x200), 
                SCIE,   1, 
                GEFC,   4, 
                GXFC,   3, 
                GESF,   8, 
                        Offset (0x204), 
                PARM,   32, 
                DSLP,   32, 
                        Offset (0x300), 
                ARDY,   32, 
                ASLC,   32, 
                TCHE,   32, 
                ALSI,   32, 
                BCLP,   32, 
                PFIT,   32, 
                CBLV,   32, 
                BCLM,   320, 
                CPFM,   32, 
                EPFM,   32, 
                PLUT,   592, 
                PFMB,   32, 
                CCDV,   32, 
                PCFT,   32, 
                        Offset (0x400), 
                GVD1,   49152, 
                PHED,   32, 
                BDDC,   2048
            }

            Name (DBTB, Package (0x15)
            {
                Zero, 
                0x07, 
                0x38, 
                0x01C0, 
                0x0E00, 
                0x3F, 
                0x01C7, 
                0x0E07, 
                0x01F8, 
                0x0E38, 
                0x0FC0, 
                Zero, 
                Zero, 
                Zero, 
                Zero, 
                Zero, 
                0x7000, 
                0x7007, 
                0x7038, 
                0x71C0, 
                0x7E00
            })
            Name (CDCT, Package (0x05)
            {
                Package (0x02)
                {
                    0xE4, 
                    0x0140
                }, 

                Package (0x02)
                {
                    0xDE, 
                    0x014D
                }, 

                Package (0x02)
                {
                    0xDE, 
                    0x014D
                }, 

                Package (0x02)
                {
                    Zero, 
                    Zero
                }, 

                Package (0x02)
                {
                    0xDE, 
                    0x014D
                }
            })
            Name (SUCC, One)
            Name (NVLD, 0x02)
            Name (CRIT, 0x04)
            Name (NCRT, 0x06)
            Method (GSCI, 0, Serialized)
            {
                Method (GBDA, 0, Serialized)
                {
                    If (LEqual (GESF, Zero))
                    {
                        Store (0x0679, PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, One))
                    {
                        Store (0x0240, PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x04))
                    {
                        And (PARM, 0xEFFF0000, PARM)
                        And (PARM, ShiftLeft (DerefOf (Index (DBTB, IBTT)), 0x10), 
                            PARM)
                        Or (IBTT, PARM, PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x05))
                    {
                        Store (IPSC, PARM)
                        Or (PARM, ShiftLeft (IPAT, 0x08), PARM)
                        Add (PARM, 0x0100, PARM)
                        Or (PARM, ShiftLeft (LIDS, 0x10), PARM)
                        Add (PARM, 0x00010000, PARM)
                        Or (PARM, ShiftLeft (IBIA, 0x14), PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x06))
                    {
                        Store (ITVF, PARM)
                        Or (PARM, ShiftLeft (ITVM, 0x04), PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x07))
                    {
                        Store (GIVD, PARM)
                        XOr (PARM, One, PARM)
                        Or (PARM, ShiftLeft (GMFN, One), PARM)
                        Or (PARM, 0x1800, PARM)
                        Or (PARM, ShiftLeft (IDMS, 0x11), PARM)
                        Or (ShiftLeft (DerefOf (Index (DerefOf (Index (CDCT, HVCO)), CDVL
                            )), 0x15), PARM, PARM)
                        Store (One, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x0A))
                    {
                        Store (Zero, PARM)
                        If (ISSC)
                        {
                            Or (PARM, 0x03, PARM)
                        }

                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x0B))
                    {
                        Store (KSV0, PARM)
                        Store (KSV1, GESF)
                        Return (SUCC)
                    }

                    Store (Zero, GESF)
                    Return (CRIT)
                }

                Method (SBCB, 0, Serialized)
                {
                    If (LEqual (GESF, Zero))
                    {
                        Store (Zero, PARM)
                        Store (0x000F87FD, PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, One))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x03))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x04))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x05))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x06))
                    {
                        Store (And (PARM, 0x0F), ITVF)
                        Store (ShiftRight (And (PARM, 0xF0), 0x04), ITVM)
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x07))
                    {
                        If (LEqual (PARM, Zero))
                        {
                            Store (CLID, Local0)
                            If (And (0x80000000, Local0))
                            {
                                And (CLID, 0x0F, CLID)
                                GLID (CLID)
                            }
                        }

                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x08))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x09))
                    {
                        And (PARM, 0xFF, IBTT)
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x0A))
                    {
                        And (PARM, 0xFF, IPSC)
                        If (And (ShiftRight (PARM, 0x08), 0xFF))
                        {
                            And (ShiftRight (PARM, 0x08), 0xFF, IPAT)
                            Decrement (IPAT)
                        }

                        And (ShiftRight (PARM, 0x14), 0x07, IBIA)
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x0B))
                    {
                        And (ShiftRight (PARM, One), One, IF1E)
                        If (And (PARM, 0x0001E000))
                        {
                            And (ShiftRight (PARM, 0x0D), 0x0F, IDMS)
                        }
                        Else
                        {
                            And (ShiftRight (PARM, 0x11), 0x0F, IDMS)
                        }

                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x10))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x11))
                    {
                        Store (ShiftLeft (LIDS, 0x08), PARM)
                        Add (PARM, 0x0100, PARM)
                        Store (Zero, GESF)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x12))
                    {
                        If (And (PARM, One))
                        {
                            If (LEqual (ShiftRight (PARM, One), One))
                            {
                                Store (One, ISSC)
                            }
                            Else
                            {
                                Store (Zero, GESF)
                                Return (CRIT)
                            }
                        }
                        Else
                        {
                            Store (Zero, ISSC)
                        }

                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x13))
                    {
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    If (LEqual (GESF, 0x14))
                    {
                        And (PARM, 0x0F, PAVP)
                        Store (Zero, GESF)
                        Store (Zero, PARM)
                        Return (SUCC)
                    }

                    Store (Zero, GESF)
                    Return (SUCC)
                }

                If (LEqual (GEFC, 0x04))
                {
                    Store (GBDA (), GXFC)
                }

                If (LEqual (GEFC, 0x06))
                {
                    Store (SBCB (), GXFC)
                }

                Store (Zero, GEFC)
                Store (One, SCIS)
                Store (Zero, GSSE)
                Store (Zero, SCIE)
                Return (Zero)
            }

            Method (PDRD, 0, NotSerialized)
            {
                If (LNot (DRDY))
                {
                    Sleep (ASLP)
                }

                Return (LNot (DRDY))
            }

            Method (PSTS, 0, NotSerialized)
            {
                If (LGreater (CSTS, 0x02))
                {
                    Sleep (ASLP)
                }

                Return (LEqual (CSTS, 0x03))
            }

            Method (GNOT, 2, NotSerialized)
            {
                If (PDRD ())
                {
                    Return (One)
                }

                Store (Arg0, CEVT)
                Store (0x03, CSTS)
                If (LAnd (LEqual (CHPD, Zero), LEqual (Arg1, Zero)))
                {
                    If (LOr (LGreater (OSYS, 0x07D0), LLess (OSYS, 0x07D6)))
                    {
                        Notify (PCI0, Arg1)
                    }
                    Else
                    {
                        Notify (GFX0, Arg1)
                    }
                }

                If (CondRefOf (HNOT))
                {
                    HNOT (Arg0)
                }
                Else
                {
                    Notify (GFX0, 0x80)
                }

                Return (Zero)
            }

            Method (GHDS, 1, NotSerialized)
            {
                Store (Arg0, TIDX)
                Return (GNOT (One, Zero))
            }

            Method (GLID, 1, NotSerialized)
            {
                If (LEqual (Arg0, One))
                {
                    Store (0x03, CLID)
                }
                Else
                {
                    Store (Arg0, CLID)
                }

                Return (GNOT (0x02, Zero))
            }

            Method (GDCK, 1, NotSerialized)
            {
                Store (Arg0, CDCK)
                Return (GNOT (0x04, Zero))
            }

            Method (PARD, 0, NotSerialized)
            {
                If (LNot (ARDY))
                {
                    Sleep (ASLP)
                }

                Return (LNot (ARDY))
            }

            Method (AINT, 2, NotSerialized)
            {
                If (LNot (And (TCHE, ShiftLeft (One, Arg0))))
                {
                    Return (One)
                }

                If (PARD ())
                {
                    Return (One)
                }

                If (LEqual (Arg0, 0x02))
                {
                    If (CPFM)
                    {
                        And (CPFM, 0x0F, Local0)
                        And (EPFM, 0x0F, Local1)
                        If (LEqual (Local0, One))
                        {
                            If (And (Local1, 0x06))
                            {
                                Store (0x06, PFIT)
                            }
                            Else
                            {
                                If (And (Local1, 0x08))
                                {
                                    Store (0x08, PFIT)
                                }
                                Else
                                {
                                    Store (One, PFIT)
                                }
                            }
                        }

                        If (LEqual (Local0, 0x06))
                        {
                            If (And (Local1, 0x08))
                            {
                                Store (0x08, PFIT)
                            }
                            Else
                            {
                                If (And (Local1, One))
                                {
                                    Store (One, PFIT)
                                }
                                Else
                                {
                                    Store (0x06, PFIT)
                                }
                            }
                        }

                        If (LEqual (Local0, 0x08))
                        {
                            If (And (Local1, One))
                            {
                                Store (One, PFIT)
                            }
                            Else
                            {
                                If (And (Local1, 0x06))
                                {
                                    Store (0x06, PFIT)
                                }
                                Else
                                {
                                    Store (0x08, PFIT)
                                }
                            }
                        }
                    }
                    Else
                    {
                        XOr (PFIT, 0x07, PFIT)
                    }

                    Or (PFIT, 0x80000000, PFIT)
                    Store (0x04, ASLC)
                }
                Else
                {
                    If (LEqual (Arg0, One))
                    {
                        Store (Divide (Multiply (Arg1, 0xFF), 0x64, ), BCLP)
                        Or (BCLP, 0x80000000, BCLP)
                        Store (0x02, ASLC)
                    }
                    Else
                    {
                        If (LEqual (Arg0, Zero))
                        {
                            Store (Arg1, ALSI)
                            Store (One, ASLC)
                        }
                        Else
                        {
                            Return (One)
                        }
                    }
                }

                Store (One, ASLE)
                Return (Zero)
            }

            Method (SCIP, 0, NotSerialized)
            {
                If (LNotEqual (OVER, Zero))
                {
                    Return (LNot (GSMI))
                }

                Return (Zero)
            }

            Device (^^MEM2)
            {
                Name (_HID, EisaId ("PNP0C01"))
                Name (_UID, 0x02)
                Name (CRS1, ResourceTemplate ()
                {
                    Memory32Fixed (ReadWrite,
                        0x20000000,         // Address Base
                        0x00200000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0x40000000,         // Address Base
                        0x00200000,         // Address Length
                        )
                })
                Name (CRS2, ResourceTemplate ()
                {
                    Memory32Fixed (ReadWrite,
                        0x20000000,         // Address Base
                        0x00200000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0x40004000,         // Address Base
                        0x00001000,         // Address Length
                        )
                })
                Method (_STA, 0, NotSerialized)
                {
                    If (IGDS)
                    {
                        Return (0x0F)
                    }

                    Return (Zero)
                }

                Method (_CRS, 0, NotSerialized)
                {
                    If (LOr (LEqual (And (PNHM, 0x0FFF0FF0), 0x000206A0), LEqual (And (
                        PNHM, 0x0FFF0FFF), 0x000306A0)))
                    {
                        Return (CRS1)
                    }

                    Return (CRS2)
                }
            }
        }
    }

    Scope (_PR)
    {
        Processor (CPU0, 0x01, 0x00000410, 0x06) {}
        Processor (CPU1, 0x02, 0x00000410, 0x06) {}
        Processor (CPU2, 0x03, 0x00000410, 0x06) {}
        Processor (CPU3, 0x04, 0x00000410, 0x06) {}
        Processor (CPU4, 0x05, 0x00000410, 0x06) {}
        Processor (CPU5, 0x06, 0x00000410, 0x06) {}
        Processor (CPU6, 0x07, 0x00000410, 0x06) {}
        Processor (CPU7, 0x08, 0x00000410, 0x06) {}
    }

    Mutex (MUTX, 0x00)
    OperationRegion (DEB0, SystemIO, 0x80, One)
    Field (DEB0, ByteAcc, NoLock, Preserve)
    {
        DBG8,   8
    }

    OperationRegion (DEB1, SystemIO, 0x90, 0x02)
    Field (DEB1, WordAcc, NoLock, Preserve)
    {
        DBG9,   16
    }

    OperationRegion (PRT0, SystemIO, 0x80, 0x04)
    Field (PRT0, DWordAcc, Lock, Preserve)
    {
        P80H,   32
    }

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

    OperationRegion (SPRT, SystemIO, 0xB2, 0x02)
    Field (SPRT, ByteAcc, Lock, Preserve)
    {
        SSMP,   8
    }

    Method (_PIC, 1, NotSerialized)
    {
        Store (Arg0, GPIC)
        Store (Arg0, PICM)
    }

    Method (_PTS, 1, NotSerialized)
    {
        Store (Zero, P80D)
        P8XH (Zero, Arg0)
        PTS (Arg0)
        If (LEqual (Arg0, 0x03))
        {
            If (LAnd (DTSE, LGreater (TCNT, One)))
            {
                TRAP (TRTD, 0x1E)
            }
        }

        If (LOr (LOr (LEqual (Arg0, 0x03), LEqual (Arg0, 0x04)), LEqual (
            Arg0, 0x05)))
        {
            If (LEqual (PFLV, FDTP))
            {
                Store (One, GP27)
            }
        }
    }

    Method (_WAK, 1, Serialized)
    {
        ShiftLeft (Arg0, 0x04, DBG8)
        WAK (Arg0)
        If (NEXP)
        {
            If (And (OSCC, 0x02))
            {
                \_SB.PCI0.NHPG ()
            }

            If (And (OSCC, 0x04))
            {
                \_SB.PCI0.NPME ()
            }
        }

        If (LEqual (Arg0, 0x03))
        {
            If (LEqual (Zero, ACTT))
            {
                If (LEqual (ECON, One))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.CFAN)
                }
            }
        }

        If (LOr (LEqual (Arg0, 0x03), LEqual (Arg0, 0x04)))
        {
            If (LAnd (DTSE, LGreater (TCNT, One)))
            {
                TRAP (TRTD, 0x14)
            }

            If (LEqual (OSYS, 0x07D2))
            {
                If (And (CFGD, One))
                {
                    If (LGreater (\_PR.CPU0._PPC, Zero))
                    {
                        Subtract (\_PR.CPU0._PPC, One, \_PR.CPU0._PPC)
                        PNOT ()
                        Add (\_PR.CPU0._PPC, One, \_PR.CPU0._PPC)
                        PNOT ()
                    }
                    Else
                    {
                        Add (\_PR.CPU0._PPC, One, \_PR.CPU0._PPC)
                        PNOT ()
                        Subtract (\_PR.CPU0._PPC, One, \_PR.CPU0._PPC)
                        PNOT ()
                    }
                }
            }

            If (LEqual (ECON, One))
            {
                If (LNotEqual (LIDS, \_SB.PCI0.LPCB.H_EC.LSTE))
                {
                    Store (\_SB.PCI0.LPCB.H_EC.LSTE, LIDS)
                    If (IGDS)
                    {
                        If (\_SB.PCI0.GFX0.GLID (LIDS))
                        {
                            Or (0x80000000, \_SB.PCI0.GFX0.CLID, \_SB.PCI0.GFX0.CLID)
                        }
                    }

                    Notify (\_SB.LID0, 0x80)
                }

                If (LNotEqual (\_SB.PCI0.LPCB.H_EC.DOCK, DSTS))
                {
                    Store (\_SB.PCI0.LPCB.H_EC.DOCK, DSTS)
                    If (LAnd (\_SB.PCI0.HDEF.DCKS, One))
                    {
                        Store (DSTS, \_SB.PCI0.HDEF.DCKA)
                    }

                    If (LEqual (DSTS, One))
                    {
                        If (LEqual (Arg0, 0x03))
                        {
                            Sleep (0x03E8)
                            Store (PDBR, SSMP)
                            Sleep (0x03E8)
                        }

                        Notify (\_SB.PCI0.DOCK, Zero)
                    }
                    Else
                    {
                        Notify (\_SB.PCI0.DOCK, One)
                    }
                }

                If (LEqual (BNUM, Zero))
                {
                    If (LNotEqual (\_SB.PCI0.LPCB.H_EC.VPWR, PWRS))
                    {
                        Store (\_SB.PCI0.LPCB.H_EC.VPWR, PWRS)
                        PNOT ()
                    }
                }
                Else
                {
                    If (LNotEqual (\_SB.PCI0.LPCB.H_EC.RPWR, PWRS))
                    {
                        Store (\_SB.PCI0.LPCB.H_EC.RPWR, PWRS)
                        PNOT ()
                    }
                }
            }

            If (LEqual (RP1D, Zero))
            {
                Notify (\_SB.PCI0.RP01, Zero)
            }

            If (LEqual (RP2D, Zero))
            {
                Notify (\_SB.PCI0.RP02, Zero)
            }

            If (LEqual (RP3D, Zero))
            {
                Notify (\_SB.PCI0.RP03, Zero)
            }

            If (LEqual (RP4D, Zero))
            {
                Notify (\_SB.PCI0.RP04, Zero)
            }

            If (LEqual (RP5D, Zero))
            {
                Notify (\_SB.PCI0.RP05, Zero)
            }

            If (LEqual (RP6D, Zero))
            {
                Notify (\_SB.PCI0.RP06, Zero)
            }

            If (LEqual (RP7D, Zero))
            {
                If (LEqual (DSTS, Zero))
                {
                    Notify (\_SB.PCI0.RP07, Zero)
                }
            }

            If (LEqual (RP8D, Zero))
            {
                If (LEqual (DSTS, Zero))
                {
                    Notify (\_SB.PCI0.RP08, Zero)
                }
            }
        }

        Return (Package (0x02)
        {
            Zero, 
            Zero
        })
    }

    Method (GETB, 3, Serialized)
    {
        Multiply (Arg0, 0x08, Local0)
        Multiply (Arg1, 0x08, Local1)
        CreateField (Arg2, Local0, Local1, TBF3)
        Return (TBF3)
    }

    Method (PNOT, 0, Serialized)
    {
        If (LGreater (TCNT, One))
        {
            If (And (PDC0, 0x08))
            {
                Notify (\_PR.CPU0, 0x80)
                If (And (PDC0, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU0, 0x81)
                }
            }

            If (And (PDC1, 0x08))
            {
                Notify (\_PR.CPU1, 0x80)
                If (And (PDC1, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU1, 0x81)
                }
            }

            If (And (PDC2, 0x08))
            {
                Notify (\_PR.CPU2, 0x80)
                If (And (PDC2, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU2, 0x81)
                }
            }

            If (And (PDC3, 0x08))
            {
                Notify (\_PR.CPU3, 0x80)
                If (And (PDC3, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU3, 0x81)
                }
            }

            If (And (PDC4, 0x08))
            {
                Notify (\_PR.CPU4, 0x80)
                If (And (PDC4, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU4, 0x81)
                }
            }

            If (And (PDC5, 0x08))
            {
                Notify (\_PR.CPU5, 0x80)
                If (And (PDC5, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU5, 0x81)
                }
            }

            If (And (PDC6, 0x08))
            {
                Notify (\_PR.CPU6, 0x80)
                If (And (PDC6, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU6, 0x81)
                }
            }

            If (And (PDC7, 0x08))
            {
                Notify (\_PR.CPU7, 0x80)
                If (And (PDC7, 0x10))
                {
                    Sleep (0x64)
                    Notify (\_PR.CPU7, 0x81)
                }
            }
        }
        Else
        {
            Notify (\_PR.CPU0, 0x80)
            Sleep (0x64)
            Notify (\_PR.CPU0, 0x81)
        }

        If (LEqual (ECON, One))
        {
            Store (\_SB.PCI0.LPCB.H_EC.B1CC, B1SC)
            Store (\_SB.PCI0.LPCB.H_EC.B1ST, B1SS)
            Store (\_SB.PCI0.LPCB.H_EC.B2CC, B2SC)
            Store (\_SB.PCI0.LPCB.H_EC.B2ST, B2SS)
            If (LGreaterEqual (OSYS, 0x07D6))
            {
                Notify (\_SB.PCI0.LPCB.H_EC.BAT0, 0x81)
                Notify (\_SB.PCI0.LPCB.H_EC.BAT1, 0x81)
                Notify (\_SB.PCI0.LPCB.H_EC.BAT2, 0x81)
            }
            Else
            {
                Notify (\_SB.PCI0.LPCB.H_EC.BAT0, 0x80)
                Notify (\_SB.PCI0.LPCB.H_EC.BAT1, 0x80)
                Notify (\_SB.PCI0.LPCB.H_EC.BAT2, 0x80)
            }
        }
    }

    Method (TRAP, 2, Serialized)
    {
        Store (Arg1, SMIF)
        If (LEqual (Arg0, TRTP))
        {
            Store (Zero, TRP0)
        }

        If (LEqual (Arg0, TRTD))
        {
            Store (Arg1, DTSF)
            Store (Zero, TRPD)
            Return (DTSF)
        }

        If (LEqual (Arg0, TRTI))
        {
            Store (Zero, TRPH)
        }

        Return (SMIF)
    }

    Scope (_SB.PCI0)
    {
        Method (_INI, 0, NotSerialized)
        {
            Store (0x07D0, OSYS)
            If (CondRefOf (_OSI, Local0))
            {
                If (_OSI ("Windows 2001"))
                {
                    Store (0x07D1, OSYS)
                }

                If (_OSI ("Windows 2001 SP1"))
                {
                    Store (0x07D1, OSYS)
                }

                If (_OSI ("Windows 2001 SP2"))
                {
                    Store (0x07D2, OSYS)
                }

                If (_OSI ("Windows 2001.1"))
                {
                    Store (0x07D3, OSYS)
                }

                If (_OSI ("Windows 2006"))
                {
                    Store (0x07D6, OSYS)
                }

                If (_OSI ("Windows 2009"))
                {
                    Store (0x07D9, OSYS)
                }
            }
        }

        Method (NHPG, 0, Serialized)
        {
            Store (Zero, ^RP01.HPEX)
            Store (Zero, ^RP02.HPEX)
            Store (Zero, ^RP03.HPEX)
            Store (Zero, ^RP04.HPEX)
            Store (One, ^RP01.HPSX)
            Store (One, ^RP02.HPSX)
            Store (One, ^RP03.HPSX)
            Store (One, ^RP04.HPSX)
        }

        Method (NPME, 0, Serialized)
        {
            Store (Zero, ^RP01.PMEX)
            Store (Zero, ^RP02.PMEX)
            Store (Zero, ^RP03.PMEX)
            Store (Zero, ^RP04.PMEX)
            Store (Zero, ^RP05.PMEX)
            Store (Zero, ^RP06.PMEX)
            Store (Zero, ^RP07.PMEX)
            Store (Zero, ^RP08.PMEX)
            Store (One, ^RP01.PMSX)
            Store (One, ^RP02.PMSX)
            Store (One, ^RP03.PMSX)
            Store (One, ^RP04.PMSX)
            Store (One, ^RP05.PMSX)
            Store (One, ^RP06.PMSX)
            Store (One, ^RP07.PMSX)
            Store (One, ^RP08.PMSX)
        }
    }

    Scope (\)
    {
        Name (PICM, Zero)
        Name (PRWP, Package (0x02)
        {
            Zero, 
            Zero
        })
        Method (GPRW, 2, NotSerialized)
        {
            Store (Arg0, Index (PRWP, Zero))
            Store (ShiftLeft (SS1, One), Local0)
            Or (Local0, ShiftLeft (SS2, 0x02), Local0)
            Or (Local0, ShiftLeft (SS3, 0x03), Local0)
            Or (Local0, ShiftLeft (SS4, 0x04), Local0)
            If (And (ShiftLeft (One, Arg1), Local0))
            {
                Store (Arg1, Index (PRWP, One))
            }
            Else
            {
                ShiftRight (Local0, One, Local0)
                FindSetLeftBit (Local0, Index (PRWP, One))
            }

            Return (PRWP)
        }
    }

    Scope (_SB.PCI0)
    {
        Device (PDRC)
        {
            Name (_HID, EisaId ("PNP0C02"))
            Name (_UID, One)
            Name (BUF0, ResourceTemplate ()
            {
                Memory32Fixed (ReadWrite,
                    0x00000000,         // Address Base
                    0x00004000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0x00000000,         // Address Base
                    0x00008000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0x00000000,         // Address Base
                    0x00001000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0x00000000,         // Address Base
                    0x00001000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0x00000000,         // Address Base
                    0x00000000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0xFED20000,         // Address Base
                    0x00020000,         // Address Length
                    )
                Memory32Fixed (ReadOnly,
                    0xFED90000,         // Address Base
                    0x00004000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0xFED45000,         // Address Base
                    0x0004B000,         // Address Length
                    )
                Memory32Fixed (ReadOnly,
                    0xFF000000,         // Address Base
                    0x01000000,         // Address Length
                    )
                Memory32Fixed (ReadOnly,
                    0xFEE00000,         // Address Base
                    0x00100000,         // Address Length
                    )
                Memory32Fixed (ReadWrite,
                    0x00000000,         // Address Base
                    0x00001000,         // Address Length
                    )
            })
            Method (_CRS, 0, Serialized)
            {
                CreateDWordField (BUF0, 0x04, RBR0)
                ShiftLeft (^^LPCB.RCBA, 0x0E, RBR0)
                CreateDWordField (BUF0, 0x7C, TBR0)
                Store (TBAB, TBR0)
                CreateDWordField (BUF0, 0x80, TBLN)
                If (LEqual (TBAB, Zero))
                {
                    Store (Zero, TBLN)
                }

                CreateDWordField (BUF0, 0x10, MBR0)
                ShiftLeft (MHBR, 0x0F, MBR0)
                CreateDWordField (BUF0, 0x1C, DBR0)
                ShiftLeft (DIBR, 0x0C, DBR0)
                CreateDWordField (BUF0, 0x28, EBR0)
                ShiftLeft (EPBR, 0x0C, EBR0)
                CreateDWordField (BUF0, 0x34, XBR0)
                ShiftLeft (PXBR, 0x1A, XBR0)
                CreateDWordField (BUF0, 0x38, XSZ0)
                ShiftRight (0x10000000, PXSZ, XSZ0)
                Return (BUF0)
            }
        }
    }

    Method (BRTN, 1, Serialized)
    {
        If (LEqual (And (DID1, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD01, Arg0)
        }

        If (LEqual (And (DID2, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD02, Arg0)
        }

        If (LEqual (And (DID3, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD03, Arg0)
        }

        If (LEqual (And (DID4, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD04, Arg0)
        }

        If (LEqual (And (DID5, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD05, Arg0)
        }

        If (LEqual (And (DID6, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD06, Arg0)
        }

        If (LEqual (And (DID7, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD07, Arg0)
        }

        If (LEqual (And (DID8, 0x0F00), 0x0400))
        {
            Notify (\_SB.PCI0.GFX0.DD08, Arg0)
        }
    }

    Scope (_GPE)
    {
        Method (_L09, 0, NotSerialized)
        {
            If (LEqual (RP1D, Zero))
            {
                \_SB.PCI0.RP01.HPME ()
                Notify (\_SB.PCI0.RP01, 0x02)
            }

            If (LEqual (RP2D, Zero))
            {
                \_SB.PCI0.RP02.HPME ()
                Notify (\_SB.PCI0.RP02, 0x02)
            }

            If (LEqual (RP3D, Zero))
            {
                \_SB.PCI0.RP03.HPME ()
                Notify (\_SB.PCI0.RP03, 0x02)
            }

            If (LEqual (RP4D, Zero))
            {
                \_SB.PCI0.RP04.HPME ()
                Notify (\_SB.PCI0.RP04, 0x02)
            }

            If (LEqual (RP5D, Zero))
            {
                \_SB.PCI0.RP05.HPME ()
                Notify (\_SB.PCI0.RP05, 0x02)
            }

            If (LEqual (RP6D, Zero))
            {
                \_SB.PCI0.RP06.HPME ()
                Notify (\_SB.PCI0.RP06, 0x02)
            }

            If (LEqual (RP7D, Zero))
            {
                \_SB.PCI0.RP07.HPME ()
                Notify (\_SB.PCI0.RP07, 0x02)
            }

            If (LEqual (RP8D, Zero))
            {
                \_SB.PCI0.RP08.HPME ()
                Notify (\_SB.PCI0.RP08, 0x02)
            }

            Notify (\_SB.PCI0.PEG0, 0x02)
            Notify (\_SB.PCI0.PEG0.PEGP, 0x02)
            Notify (\_SB.PCI0.PEG1, 0x02)
            Notify (\_SB.PCI0.PEG2, 0x02)
            Notify (\_SB.PCI0.PEG3, 0x02)
        }

        Method (_L0D, 0, NotSerialized)
        {
            Notify (\_SB.PCI0.EHC1, 0x02)
            Notify (\_SB.PCI0.EHC2, 0x02)
            Notify (\_SB.PCI0.HDEF, 0x02)
            Notify (\_SB.PCI0.GLAN, 0x02)
        }

        Method (_L01, 0, NotSerialized)
        {
            Add (L01C, One, L01C)
            P8XH (Zero, One)
            P8XH (One, L01C)
            If (LAnd (LEqual (RP1D, Zero), \_SB.PCI0.RP01.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP01.PDCX)
                {
                    Store (One, \_SB.PCI0.RP01.PDCX)
                    Store (One, \_SB.PCI0.RP01.HPSX)
                    If (LNot (\_SB.PCI0.RP01.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP01.L0SE)
                    }

                    Notify (\_SB.PCI0.RP01, Zero)
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP01.HPSX)
                }
            }

            If (LAnd (LEqual (RP2D, Zero), \_SB.PCI0.RP02.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP02.PDCX)
                {
                    Store (One, \_SB.PCI0.RP02.PDCX)
                    Store (One, \_SB.PCI0.RP02.HPSX)
                    If (LNot (\_SB.PCI0.RP02.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP02.L0SE)
                    }

                    Notify (\_SB.PCI0.RP02, Zero)
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP02.HPSX)
                }
            }

            If (LAnd (LEqual (RP3D, Zero), \_SB.PCI0.RP03.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP03.PDCX)
                {
                    Store (One, \_SB.PCI0.RP03.PDCX)
                    Store (One, \_SB.PCI0.RP03.HPSX)
                    If (LNot (\_SB.PCI0.RP03.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP03.L0SE)
                    }

                    Notify (\_SB.PCI0.RP03, Zero)
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP03.HPSX)
                }
            }

            If (LAnd (LEqual (RP4D, Zero), \_SB.PCI0.RP04.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP04.PDCX)
                {
                    Store (One, \_SB.PCI0.RP04.PDCX)
                    Store (One, \_SB.PCI0.RP04.HPSX)
                    If (LNot (\_SB.PCI0.RP04.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP04.L0SE)
                    }

                    Notify (\_SB.PCI0.RP04, Zero)
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP04.HPSX)
                }
            }

            If (LAnd (LEqual (RP5D, Zero), \_SB.PCI0.RP05.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP05.PDCX)
                {
                    Store (One, \_SB.PCI0.RP05.PDCX)
                    Store (One, \_SB.PCI0.RP05.HPSX)
                    If (LNot (\_SB.PCI0.RP05.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP05.L0SE)
                    }

                    Notify (\_SB.PCI0.RP05, Zero)
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP05.HPSX)
                }
            }

            If (LAnd (LEqual (RP6D, Zero), \_SB.PCI0.RP06.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP06.PDCX)
                {
                    Store (One, \_SB.PCI0.RP06.PDCX)
                    Store (One, \_SB.PCI0.RP06.HPSX)
                    If (LNot (\_SB.PCI0.RP06.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP06.L0SE)
                    }

                    Notify (\_SB.PCI0.RP06, Zero)
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP06.HPSX)
                }
            }

            If (LAnd (LEqual (RP7D, Zero), \_SB.PCI0.RP07.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP07.PDCX)
                {
                    Store (One, \_SB.PCI0.RP07.PDCX)
                    Store (One, \_SB.PCI0.RP07.HPSX)
                    If (LNot (\_SB.PCI0.RP07.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP07.L0SE)
                    }

                    If (ECON)
                    {
                        If (LEqual (\_SB.PCI0.LPCB.H_EC.DOCK, Zero))
                        {
                            Notify (\_SB.PCI0.RP07, Zero)
                        }
                    }
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP07.HPSX)
                }
            }

            If (LAnd (LEqual (RP8D, Zero), \_SB.PCI0.RP08.HPSX))
            {
                Sleep (0x64)
                If (\_SB.PCI0.RP08.PDCX)
                {
                    Store (One, \_SB.PCI0.RP08.PDCX)
                    Store (One, \_SB.PCI0.RP08.HPSX)
                    If (LNot (\_SB.PCI0.RP08.PDSX))
                    {
                        Store (Zero, \_SB.PCI0.RP08.L0SE)
                    }

                    If (ECON)
                    {
                        If (LEqual (\_SB.PCI0.LPCB.H_EC.DOCK, Zero))
                        {
                            Notify (\_SB.PCI0.RP08, Zero)
                        }
                    }
                }
                Else
                {
                    Store (One, \_SB.PCI0.RP08.HPSX)
                }
            }
        }

        Method (_L02, 0, NotSerialized)
        {
            Store (Zero, GPEC)
            If (CondRefOf (\_SB.PCI0.IEIT.EITV))
            {
                \_SB.PCI0.IEIT.EITV ()
            }

            Notify (\_TZ.TZ00, 0x80)
            Notify (\_TZ.TZ01, 0x80)
            If (CondRefOf (TNOT))
            {
                TNOT ()
            }
        }

        Method (_L06, 0, NotSerialized)
        {
            If (LAnd (\_SB.PCI0.GFX0.GSSE, LNot (GSMI)))
            {
                \_SB.PCI0.GFX0.GSCI ()
            }
        }

        Method (_L07, 0, NotSerialized)
        {
            Store (0x20, \_SB.PCI0.SBUS.HSTS)
        }
    }

    Scope (_TZ)
    {
        Name (ETMD, One)
        Name (THLD, 0x78)
        PowerResource (FN00, 0x00, 0x0000)
        {
            Method (_STA, 0, Serialized)
            {
                Return (VFN0)
            }

            Method (_ON, 0, Serialized)
            {
                Store (One, VFN0)
                If (LAnd (ECON, ETMD))
                {
                    Store (AC0F, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }

            Method (_OFF, 0, Serialized)
            {
                Store (Zero, VFN0)
                If (LAnd (ECON, ETMD))
                {
                    If (LEqual (VFN1, Zero))
                    {
                        Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    }
                    Else
                    {
                        Store (AC1F, \_SB.PCI0.LPCB.H_EC.PENV)
                    }

                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }
        }

        Device (FAN0)
        {
            Name (_HID, EisaId ("PNP0C0B"))
            Name (_UID, Zero)
            Name (_PR0, Package (0x01)
            {
                FN00
            })
        }

        PowerResource (FN01, 0x00, 0x0000)
        {
            Method (_STA, 0, Serialized)
            {
                Return (VFN1)
            }

            Method (_ON, 0, Serialized)
            {
                Store (One, VFN1)
                If (LAnd (ECON, ETMD))
                {
                    Store (AC1F, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }

            Method (_OFF, 0, Serialized)
            {
                Store (Zero, VFN1)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }
        }

        Device (FAN1)
        {
            Name (_HID, EisaId ("PNP0C0B"))
            Name (_UID, One)
            Name (_PR0, Package (0x01)
            {
                FN01
            })
        }

        PowerResource (FN02, 0x00, 0x0000)
        {
            Method (_STA, 0, Serialized)
            {
                Return (VFN2)
            }

            Method (_ON, 0, Serialized)
            {
                Store (One, VFN2)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }

            Method (_OFF, 0, Serialized)
            {
                Store (Zero, VFN2)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }
        }

        Device (FAN2)
        {
            Name (_HID, EisaId ("PNP0C0B"))
            Name (_UID, 0x02)
            Name (_PR0, Package (0x01)
            {
                FN02
            })
        }

        PowerResource (FN03, 0x00, 0x0000)
        {
            Method (_STA, 0, Serialized)
            {
                Return (VFN3)
            }

            Method (_ON, 0, Serialized)
            {
                Store (One, VFN3)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }

            Method (_OFF, 0, Serialized)
            {
                Store (Zero, VFN3)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }
        }

        Device (FAN3)
        {
            Name (_HID, EisaId ("PNP0C0B"))
            Name (_UID, 0x03)
            Name (_PR0, Package (0x01)
            {
                FN03
            })
        }

        PowerResource (FN04, 0x00, 0x0000)
        {
            Method (_STA, 0, Serialized)
            {
                Return (VFN4)
            }

            Method (_ON, 0, Serialized)
            {
                Store (One, VFN4)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }

            Method (_OFF, 0, Serialized)
            {
                Store (Zero, VFN4)
                If (LAnd (ECON, ETMD))
                {
                    Store (Zero, \_SB.PCI0.LPCB.H_EC.PENV)
                    \_SB.PCI0.LPCB.H_EC.ECMD (0x1A)
                }
            }
        }

        Device (FAN4)
        {
            Name (_HID, EisaId ("PNP0C0B"))
            Name (_UID, 0x04)
            Name (_PR0, Package (0x01)
            {
                FN04
            })
        }

        ThermalZone (TZ00)
        {
            Name (PTMP, 0x0BB8)
            Method (_SCP, 1, Serialized)
            {
                Store (Arg0, CTYP)
            }

            Method (_CRT, 0, Serialized)
            {
                If (CondRefOf (\_PR.ACRT))
                {
                    If (LNotEqual (\_PR.ACRT, Zero))
                    {
                        Return (Add (0x0AAC, Multiply (\_PR.ACRT, 0x0A)))
                    }
                }

                Return (Add (0x0AAC, Multiply (CRTT, 0x0A)))
            }

            Method (_AC0, 0, Serialized)
            {
                If (CondRefOf (\_PR.AAC0))
                {
                    If (LNotEqual (\_PR.AAC0, Zero))
                    {
                        Return (Add (0x0AAC, Multiply (\_PR.AAC0, 0x0A)))
                    }
                }

                Return (Add (0x0AAC, Multiply (ACTT, 0x0A)))
            }

            Method (_AC1, 0, Serialized)
            {
                Return (Add (0x0AAC, Multiply (ACT1, 0x0A)))
            }

            Method (_AC2, 0, Serialized)
            {
                Return (0x0AAC)
            }

            Method (_AC3, 0, Serialized)
            {
                Return (0x0AAC)
            }

            Method (_AC4, 0, Serialized)
            {
                Return (0x0AAC)
            }

            Name (_AL0, Package (0x01)
            {
                FAN0
            })
            Name (_AL1, Package (0x01)
            {
                FAN1
            })
            Name (_AL2, Package (0x01)
            {
                FAN2
            })
            Name (_AL3, Package (0x01)
            {
                FAN3
            })
            Name (_AL4, Package (0x01)
            {
                FAN4
            })
            Method (_TMP, 0, Serialized)
            {
                If (LNot (ETMD))
                {
                    Return (0x0BB8)
                }

                If (LEqual (DTSE, 0x03))
                {
                    Return (Add (0x0B10, Multiply (CRTT, 0x0A)))
                }

                If (LEqual (DTSE, One))
                {
                    If (LEqual (PKGA, One))
                    {
                        Store (PDTS, Local0)
                        Return (Add (0x0AAC, Multiply (Local0, 0x0A)))
                    }

                    Store (DTS1, Local0)
                    If (LGreater (DTS2, Local0))
                    {
                        Store (DTS2, Local0)
                    }

                    If (LGreater (DTS3, Local0))
                    {
                        Store (DTS3, Local0)
                    }

                    If (LGreater (DTS4, Local0))
                    {
                        Store (DTS4, Local0)
                    }

                    Return (Add (0x0AAC, Multiply (Local0, 0x0A)))
                }

                If (ECON)
                {
                    Store (\_SB.PCI0.LPCB.H_EC.PLMX, Local0)
                    Add (0x0AAC, Multiply (Local0, 0x0A), Local0)
                    Store (Local0, PTMP)
                    Return (Local0)
                }

                Return (0x0BC2)
            }
        }

        ThermalZone (TZ01)
        {
            Name (PTMP, 0x0BB8)
            Method (_SCP, 1, Serialized)
            {
                Store (Arg0, CTYP)
            }

            Method (_CRT, 0, Serialized)
            {
                If (CondRefOf (\_PR.ACRT))
                {
                    If (LNotEqual (\_PR.ACRT, Zero))
                    {
                        Return (Add (0x0AAC, Multiply (\_PR.ACRT, 0x0A)))
                    }
                }

                Return (Add (0x0AAC, Multiply (CRTT, 0x0A)))
            }

            Method (_TMP, 0, Serialized)
            {
                If (LNot (ETMD))
                {
                    Return (0x0BCC)
                }

                If (LEqual (DTSE, 0x03))
                {
                    Return (Add (0x0B10, Multiply (CRTT, 0x0A)))
                }

                If (LEqual (DTSE, One))
                {
                    If (LEqual (PKGA, One))
                    {
                        Store (PDTS, Local0)
                        Return (Add (0x0AAC, Multiply (Local0, 0x0A)))
                    }

                    Store (DTS1, Local0)
                    If (LGreater (DTS2, Local0))
                    {
                        Store (DTS2, Local0)
                    }

                    If (LGreater (DTS3, Local0))
                    {
                        Store (DTS3, Local0)
                    }

                    If (LGreater (DTS4, Local0))
                    {
                        Store (DTS4, Local0)
                    }

                    Return (Add (0x0AAC, Multiply (Local0, 0x0A)))
                }

                If (ECON)
                {
                    Store (\_SB.PCI0.LPCB.H_EC.PECH, Local0)
                    Multiply (Local0, 0x0A, Local0)
                    Store (\_SB.PCI0.LPCB.H_EC.PECL, Local1)
                    ShiftRight (Local1, 0x02, Local1)
                    Store (Divide (Multiply (Local1, 0x0A), 0x40, ), Local1)
                    Add (Local0, Local1, Local0)
                    Add (0x0AAC, Local0, Local0)
                    Store (Local0, PTMP)
                    Return (Local0)
                }

                Return (0x0BD6)
            }

            Method (_PSL, 0, Serialized)
            {
                If (LEqual (TCNT, 0x08))
                {
                    Return (Package (0x08)
                    {
                        \_PR.CPU0, 
                        \_PR.CPU1, 
                        \_PR.CPU2, 
                        \_PR.CPU3, 
                        \_PR.CPU4, 
                        \_PR.CPU5, 
                        \_PR.CPU6, 
                        \_PR.CPU7
                    })
                }

                If (LEqual (TCNT, 0x04))
                {
                    Return (Package (0x04)
                    {
                        \_PR.CPU0, 
                        \_PR.CPU1, 
                        \_PR.CPU2, 
                        \_PR.CPU3
                    })
                }

                If (LEqual (TCNT, 0x02))
                {
                    Return (Package (0x02)
                    {
                        \_PR.CPU0, 
                        \_PR.CPU1
                    })
                }

                Return (Package (0x01)
                {
                    \_PR.CPU0
                })
            }

            Method (_PSV, 0, Serialized)
            {
                If (CondRefOf (\_PR.APSV))
                {
                    If (LNotEqual (\_PR.APSV, Zero))
                    {
                        Return (Add (0x0AAC, Multiply (\_PR.APSV, 0x0A)))
                    }
                }

                Return (Add (0x0AAC, Multiply (PSVT, 0x0A)))
            }

            Method (_TC1, 0, Serialized)
            {
                Return (TC1V)
            }

            Method (_TC2, 0, Serialized)
            {
                Return (TC2V)
            }

            Method (_TSP, 0, Serialized)
            {
                Return (TSPV)
            }
        }
    }

    Scope (_SB.PCI0.LPCB)
    {
        Method (SIOH, 0, NotSerialized)
        {
            If (And (PMFG, 0x10))
            {
                Notify (PS2K, 0x02)
            }

            If (And (PMFG, 0x20))
            {
                Notify (PS2M, 0x02)
            }
        }
    }

    Name (TPMF, Zero)
    Scope (\)
    {
        Device (AMW0)
        {
            Name (_HID, EisaId ("PNP0C14"))
            Name (_UID, "ASUSWMI")
            Name (_WDG, Buffer (0x50)
            {
                /* 0000 */    0xD0, 0x5E, 0x84, 0x97, 0x6D, 0x4E, 0xDE, 0x11, 
                /* 0008 */    0x8A, 0x39, 0x08, 0x00, 0x20, 0x0C, 0x9A, 0x66, 
                /* 0010 */    0x42, 0x43, 0x01, 0x02, 0xA0, 0x47, 0x67, 0x46, 
                /* 0018 */    0xEC, 0x70, 0xDE, 0x11, 0x8A, 0x39, 0x08, 0x00, 
                /* 0020 */    0x20, 0x0C, 0x9A, 0x66, 0x42, 0x44, 0x01, 0x02, 
                /* 0028 */    0x72, 0x0F, 0xBC, 0xAB, 0xA1, 0x8E, 0xD1, 0x11, 
                /* 0030 */    0x00, 0xA0, 0xC9, 0x06, 0x29, 0x10, 0x00, 0x00, 
                /* 0038 */    0xD2, 0x00, 0x01, 0x08, 0x21, 0x12, 0x90, 0x05, 
                /* 0040 */    0x66, 0xD5, 0xD1, 0x11, 0xB2, 0xF0, 0x00, 0xA0, 
                /* 0048 */    0xC9, 0x06, 0x29, 0x10, 0x4D, 0x4F, 0x01, 0x00
            })
            Name (CCAC, Zero)
            Name (ECD2, Zero)
            Name (EID2, Zero)
            Method (WED2, 1, NotSerialized)
            {
                Store (Arg0, ECD2)
            }

            Method (WMBC, 3, NotSerialized)
            {
                Store (One, Local0)
                Name (_T_0, Zero)
                Store (Arg1, _T_0)
                If (LEqual (_T_0, 0x43455053))
                {
                    Return (SPEC (Arg2))
                }
                Else
                {
                    If (LEqual (_T_0, 0x50564544))
                    {
                        Return (DEVP (Arg2))
                    }
                    Else
                    {
                        If (LEqual (_T_0, 0x50534453))
                        {
                            Return (SDSP (Arg2))
                        }
                        Else
                        {
                            If (LEqual (_T_0, 0x50534447))
                            {
                                Return (GDSP (Arg2))
                            }
                            Else
                            {
                                If (LEqual (_T_0, 0x53564544))
                                {
                                    Return (DEVS (Arg2))
                                }
                                Else
                                {
                                    If (LEqual (_T_0, 0x53544344))
                                    {
                                        Return (DSTS (Arg2))
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x44495047))
                                        {
                                            Return (GPID ())
                                        }
                                        Else
                                        {
                                            If (LEqual (_T_0, 0x5446424B))
                                            {
                                                Return (KBFT (Arg2))
                                            }
                                            Else
                                            {
                                                If (LEqual (_T_0, 0x59454B48))
                                                {
                                                    Return (HKEY ())
                                                }
                                                Else
                                                {
                                                    Return (Zero)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Return (Local0)
            }

            Method (RSMB, 1, Serialized)
            {
                Return (Zero)
            }

            Method (WSMB, 1, Serialized)
            {
                Return (Zero)
            }

            Method (RSMW, 1, Serialized)
            {
                Return (Zero)
            }

            Method (WSMW, 1, Serialized)
            {
                Return (Zero)
            }

            Method (RSMK, 1, Serialized)
            {
                Return (Zero)
            }

            Method (WSMK, 1, Serialized)
            {
                Return (Zero)
            }

            Method (WMBD, 3, NotSerialized)
            {
                Store (One, Local0)
                Name (_T_0, Zero)
                Store (Arg1, _T_0)
                If (LEqual (_T_0, 0x424D5352))
                {
                    Return (RSMB (Arg2))
                }
                Else
                {
                    If (LEqual (_T_0, 0x424D5357))
                    {
                        Return (WSMB (Arg2))
                    }
                    Else
                    {
                        If (LEqual (_T_0, 0x574D5352))
                        {
                            Return (RSMW (Arg2))
                        }
                        Else
                        {
                            If (LEqual (_T_0, 0x574D5357))
                            {
                                Return (WSMW (Arg2))
                            }
                            Else
                            {
                                If (LEqual (_T_0, 0x4B4D5352))
                                {
                                    Return (RSMK (Arg2))
                                }
                                Else
                                {
                                    If (LEqual (_T_0, 0x4B4D5357))
                                    {
                                        Return (WSMK (Arg2))
                                    }
                                    Else
                                    {
                                        Return (Zero)
                                    }
                                }
                            }
                        }
                    }
                }

                Return (Local0)
            }

            Method (_WED, 1, NotSerialized)
            {
                If (LEqual (Arg0, 0xD2))
                {
                    Return (EID2)
                }

                Return (Zero)
            }

            Method (AMWR, 1, Serialized)
            {
                Store (Zero, Local1)
                If (ECD2)
                {
                    Store (Arg0, EID2)
                    Notify (AMW0, 0xD2)
                    Store (One, Local1)
                }
                Else
                {
                }

                Return (Local1)
            }

            Method (AMWN, 1, Serialized)
            {
                Store (AMWR (Arg0), Local0)
                Return (Local0)
            }

            Name (WQMO, Buffer (0x09A6)
            {
                /* 0000 */    0x46, 0x4F, 0x4D, 0x42, 0x01, 0x00, 0x00, 0x00, 
                /* 0008 */    0x96, 0x09, 0x00, 0x00, 0x42, 0x38, 0x00, 0x00, 
                /* 0010 */    0x44, 0x53, 0x00, 0x01, 0x1A, 0x7D, 0xDA, 0x54, 
                /* 0018 */    0xA8, 0xD1, 0x9A, 0x00, 0x01, 0x06, 0x18, 0x42, 
                /* 0020 */    0x10, 0x07, 0x10, 0x4A, 0x29, 0x86, 0x42, 0x04, 
                /* 0028 */    0x0A, 0x0D, 0xA1, 0x38, 0x0A, 0x60, 0x30, 0x12, 
                /* 0030 */    0x20, 0x24, 0x07, 0x42, 0x2E, 0x98, 0x98, 0x00, 
                /* 0038 */    0x11, 0x10, 0xF2, 0x2A, 0xC0, 0xA6, 0x00, 0x93, 
                /* 0040 */    0x20, 0xEA, 0xDF, 0x1F, 0xA2, 0x24, 0x38, 0x94, 
                /* 0048 */    0x10, 0x08, 0x49, 0x14, 0x60, 0x5E, 0x80, 0x6E, 
                /* 0050 */    0x01, 0x86, 0x05, 0xD8, 0x16, 0x60, 0x5A, 0x80, 
                /* 0058 */    0x63, 0x48, 0x2A, 0x0D, 0x9C, 0x12, 0x58, 0x0A, 
                /* 0060 */    0x84, 0x84, 0x0A, 0x50, 0x2E, 0xC0, 0xB7, 0x00, 
                /* 0068 */    0xED, 0x88, 0x92, 0x2C, 0xC0, 0x32, 0x8C, 0x08, 
                /* 0070 */    0x3C, 0x8A, 0xC8, 0x46, 0xE3, 0x04, 0x65, 0x43, 
                /* 0078 */    0xA3, 0x64, 0x40, 0xC8, 0xB3, 0x00, 0xEB, 0xC0, 
                /* 0080 */    0x84, 0xC0, 0xEE, 0x05, 0x98, 0x13, 0xE0, 0x4D, 
                /* 0088 */    0x80, 0xB8, 0x61, 0x68, 0x85, 0x07, 0x10, 0xAA, 
                /* 0090 */    0x30, 0x01, 0xB6, 0x60, 0x84, 0x52, 0x1B, 0x8C, 
                /* 0098 */    0x50, 0x1A, 0x43, 0xD0, 0x30, 0x8C, 0x12, 0xF1, 
                /* 00A0 */    0x90, 0x3A, 0x83, 0x15, 0x4A, 0xC4, 0x30, 0x21, 
                /* 00A8 */    0x22, 0x54, 0x86, 0x41, 0x86, 0x15, 0x2A, 0x5A, 
                /* 00B0 */    0xDC, 0x08, 0xED, 0x0F, 0x82, 0x44, 0x5B, 0xB1, 
                /* 00B8 */    0x86, 0xEA, 0x48, 0xA3, 0x41, 0x0D, 0x2F, 0xC1, 
                /* 00C0 */    0xE1, 0x7A, 0xA8, 0xE7, 0xD8, 0xB9, 0x00, 0xE9, 
                /* 00C8 */    0xC0, 0x02, 0x09, 0x7E, 0x16, 0x75, 0x8E, 0x93, 
                /* 00D0 */    0x80, 0x24, 0x30, 0xD6, 0xF1, 0xB3, 0x81, 0xE3, 
                /* 00D8 */    0x5D, 0x03, 0x6A, 0xC6, 0xC7, 0xCB, 0x04, 0xC1, 
                /* 00E0 */    0xA1, 0x86, 0xE8, 0x81, 0x86, 0x3B, 0x81, 0x43, 
                /* 00E8 */    0x64, 0x80, 0x9E, 0xD3, 0xD1, 0x60, 0x0E, 0x00, 
                /* 00F0 */    0x76, 0x38, 0x19, 0xDD, 0x03, 0x4A, 0x15, 0x60, 
                /* 00F8 */    0x76, 0xCC, 0xB2, 0x08, 0xA4, 0xF1, 0x18, 0xFA, 
                /* 0100 */    0x74, 0xCF, 0xE7, 0x84, 0x13, 0x58, 0xFE, 0x20, 
                /* 0108 */    0x50, 0x23, 0x33, 0xB4, 0x0D, 0x4E, 0x4B, 0x98, 
                /* 0110 */    0x21, 0x0F, 0xFF, 0xB0, 0x98, 0x58, 0x08, 0x7D, 
                /* 0118 */    0x10, 0x3C, 0x1E, 0x78, 0xFF, 0xFF, 0xF1, 0x80, 
                /* 0120 */    0x47, 0xF1, 0x99, 0x40, 0x08, 0xAF, 0x04, 0xB1, 
                /* 0128 */    0x3D, 0xA0, 0xE7, 0x04, 0x03, 0x63, 0x07, 0x64, 
                /* 0130 */    0xBF, 0x02, 0x10, 0x82, 0x97, 0x39, 0x22, 0x39, 
                /* 0138 */    0x45, 0xD0, 0x98, 0x8C, 0xD1, 0x2A, 0x84, 0x86, 
                /* 0140 */    0x10, 0xDA, 0x10, 0x67, 0x17, 0xFF, 0xE0, 0x0D, 
                /* 0148 */    0x73, 0xEE, 0x26, 0x28, 0x72, 0x04, 0xA8, 0xCF, 
                /* 0150 */    0x84, 0x47, 0xC0, 0x8F, 0x01, 0xD1, 0x43, 0x9F, 
                /* 0158 */    0x4D, 0xF4, 0xE3, 0x89, 0x72, 0x12, 0x07, 0xE4, 
                /* 0160 */    0x33, 0x83, 0x11, 0x82, 0x97, 0x7B, 0x48, 0x20, 
                /* 0168 */    0x9A, 0xE7, 0xA0, 0x13, 0xC3, 0x39, 0x1D, 0x02, 
                /* 0170 */    0x53, 0xA3, 0x05, 0xA2, 0x09, 0x10, 0x45, 0x59, 
                /* 0178 */    0xAA, 0x6C, 0x2C, 0xD5, 0x83, 0xA0, 0x82, 0x80, 
                /* 0180 */    0x34, 0x77, 0x43, 0x9C, 0xB4, 0x91, 0x03, 0xC7, 
                /* 0188 */    0xA8, 0x7E, 0xD8, 0x54, 0x04, 0x9C, 0x0E, 0x1B, 
                /* 0190 */    0x1E, 0xB7, 0xE3, 0x93, 0x28, 0xFA, 0x80, 0x28, 
                /* 0198 */    0x9C, 0xC3, 0x9E, 0x39, 0x28, 0x88, 0x01, 0x9D, 
                /* 01A0 */    0x04, 0x42, 0x4E, 0x8E, 0x02, 0xA8, 0xBD, 0x68, 
                /* 01A8 */    0x58, 0x1A, 0xD7, 0xA9, 0xBD, 0x09, 0x78, 0x5A, 
                /* 01B0 */    0x8F, 0x05, 0x87, 0x71, 0x5C, 0x67, 0x6D, 0xD1, 
                /* 01B8 */    0x37, 0x06, 0x3A, 0x1F, 0xDF, 0x05, 0xB8, 0x06, 
                /* 01C0 */    0x08, 0xCD, 0xC8, 0xF0, 0x56, 0x03, 0x48, 0xC1, 
                /* 01C8 */    0xF8, 0x49, 0xE0, 0x11, 0xC0, 0x04, 0xD6, 0x75, 
                /* 01D0 */    0x20, 0x80, 0x7E, 0xD9, 0xF0, 0xF0, 0x7D, 0xC2, 
                /* 01D8 */    0x78, 0xBC, 0x48, 0x50, 0xDF, 0x7D, 0x00, 0x14, 
                /* 01E0 */    0x40, 0x3E, 0x00, 0x58, 0xE9, 0x1D, 0x80, 0x8E, 
                /* 01E8 */    0x21, 0x44, 0x98, 0x68, 0x46, 0xE7, 0x12, 0x56, 
                /* 01F0 */    0xAA, 0xFF, 0xFF, 0x68, 0xF9, 0x41, 0xC5, 0xA3, 
                /* 01F8 */    0x35, 0x88, 0x47, 0xEB, 0x40, 0xA3, 0x45, 0x1F, 
                /* 0200 */    0x33, 0xAC, 0x70, 0x54, 0xF2, 0x39, 0x01, 0x0D, 
                /* 0208 */    0x17, 0x06, 0x41, 0xE1, 0x07, 0x0E, 0x68, 0x80, 
                /* 0210 */    0xA7, 0xF7, 0x66, 0xE0, 0x99, 0x18, 0xCE, 0xF3, 
                /* 0218 */    0xE5, 0x70, 0x9E, 0x2F, 0x1F, 0x8E, 0x0F, 0x14, 
                /* 0220 */    0xF0, 0x07, 0x8C, 0x25, 0x28, 0x70, 0xC2, 0x20, 
                /* 0228 */    0x87, 0xC7, 0x08, 0x1E, 0x2C, 0x95, 0x35, 0x2E, 
                /* 0230 */    0xD4, 0xFD, 0xC0, 0x27, 0x1A, 0x86, 0x7D, 0xA8, 
                /* 0238 */    0x47, 0xF3, 0x96, 0x70, 0x86, 0x6F, 0x13, 0x07, 
                /* 0240 */    0xF5, 0xEE, 0x61, 0xA7, 0x42, 0x2D, 0x3A, 0x84, 
                /* 0248 */    0xF5, 0x48, 0x39, 0xAC, 0xD1, 0xC2, 0x1E, 0xF0, 
                /* 0250 */    0x73, 0x87, 0xEF, 0x19, 0xFC, 0x4A, 0xE3, 0x63, 
                /* 0258 */    0x08, 0x5D, 0x85, 0x4E, 0x15, 0x5C, 0x14, 0x84, 
                /* 0260 */    0xE2, 0xAD, 0x45, 0xC3, 0x3F, 0x0B, 0x8F, 0xEB, 
                /* 0268 */    0x15, 0xC3, 0x57, 0x80, 0x87, 0x13, 0x9F, 0x01, 
                /* 0270 */    0xE2, 0x07, 0x3A, 0x82, 0x17, 0x11, 0x9F, 0x7D, 
                /* 0278 */    0x7C, 0x79, 0xF1, 0x21, 0x83, 0x9D, 0x2C, 0x78, 
                /* 0280 */    0x08, 0x0A, 0xC5, 0x38, 0x1C, 0xA0, 0x84, 0xC3, 
                /* 0288 */    0x08, 0xCE, 0x20, 0x1E, 0x9E, 0x83, 0x1C, 0x0E, 
                /* 0290 */    0xD0, 0xE7, 0x20, 0x0F, 0x84, 0x0D, 0xC2, 0x20, 
                /* 0298 */    0xE7, 0xF1, 0xF2, 0xC3, 0x2E, 0x16, 0xF8, 0xFF, 
                /* 02A0 */    0xFF, 0xC5, 0x02, 0x78, 0xA5, 0x19, 0x14, 0x5A, 
                /* 02A8 */    0xCF, 0xA0, 0x20, 0x60, 0x3C, 0x3F, 0x78, 0xBC, 
                /* 02B0 */    0x9E, 0xAD, 0xA7, 0x05, 0xDE, 0x11, 0xFB, 0xFC, 
                /* 02B8 */    0x01, 0x9C, 0xC3, 0x1F, 0x5E, 0x50, 0x71, 0x87, 
                /* 02C0 */    0x44, 0x41, 0x7C, 0x36, 0x70, 0x94, 0xF1, 0xA2, 
                /* 02C8 */    0x67, 0xE2, 0xC3, 0x90, 0x8F, 0x0B, 0x4F, 0x37, 
                /* 02D0 */    0x98, 0xC3, 0x07, 0xB8, 0x47, 0xE2, 0xC3, 0x07, 
                /* 02D8 */    0xF0, 0xF8, 0xFF, 0x1F, 0x3E, 0x80, 0x9F, 0x44, 
                /* 02E0 */    0x8B, 0x5A, 0x85, 0x1E, 0x3E, 0xC0, 0x15, 0xE4, 
                /* 02E8 */    0x84, 0x84, 0x96, 0x73, 0xF8, 0x40, 0x4E, 0x24, 
                /* 02F0 */    0x4C, 0x74, 0x9F, 0x91, 0x5E, 0x3C, 0x2C, 0xE1, 
                /* 02F8 */    0xE0, 0x81, 0x0A, 0x4F, 0xA2, 0xF8, 0xA7, 0x02, 
                /* 0300 */    0x54, 0xE0, 0x53, 0x01, 0x05, 0x31, 0xA0, 0x0F, 
                /* 0308 */    0x15, 0x70, 0x66, 0xF0, 0xEC, 0x85, 0x99, 0x07, 
                /* 0310 */    0x8C, 0x33, 0x12, 0x60, 0xEB, 0x50, 0x01, 0xDE, 
                /* 0318 */    0xFF, 0xFF, 0xA1, 0x02, 0x38, 0x1C, 0x90, 0x00, 
                /* 0320 */    0x59, 0x12, 0x2F, 0x48, 0x0F, 0x15, 0xE0, 0x3A, 
                /* 0328 */    0x70, 0xFA, 0x50, 0xC1, 0x0F, 0x9A, 0x16, 0x05, 
                /* 0330 */    0xA4, 0x23, 0x9E, 0x0F, 0x15, 0x30, 0x2E, 0x42, 
                /* 0338 */    0x86, 0x7F, 0xAD, 0x3B, 0x96, 0xE7, 0x30, 0x72, 
                /* 0340 */    0xAE, 0x40, 0xC7, 0x3E, 0x18, 0xA0, 0x82, 0x8E, 
                /* 0348 */    0x9E, 0x82, 0x18, 0xD0, 0x29, 0x0E, 0x06, 0x68, 
                /* 0350 */    0x1D, 0xE7, 0x0A, 0xD4, 0x31, 0x0E, 0xF8, 0xFD, 
                /* 0358 */    0xFF, 0xCF, 0x14, 0xC0, 0x49, 0xC4, 0xD1, 0x0A, 
                /* 0360 */    0x35, 0x5C, 0x8F, 0xD5, 0x20, 0x1E, 0xAB, 0x8F, 
                /* 0368 */    0xA1, 0x1E, 0x2B, 0xEE, 0x1B, 0xE0, 0x23, 0x00, 
                /* 0370 */    0xFE, 0xE8, 0x84, 0x03, 0x7B, 0xAE, 0x00, 0x4C, 
                /* 0378 */    0x7B, 0x3C, 0x57, 0x80, 0x4E, 0xDA, 0xD9, 0x07, 
                /* 0380 */    0x1D, 0x70, 0xAD, 0x3A, 0x89, 0xE1, 0xCF, 0x71, 
                /* 0388 */    0x8C, 0x60, 0xA8, 0xC3, 0x1B, 0x85, 0x70, 0x1C, 
                /* 0390 */    0x0A, 0x85, 0x39, 0x19, 0xD0, 0xFF, 0xFF, 0x11, 
                /* 0398 */    0x96, 0xC0, 0x51, 0x10, 0x0F, 0xCD, 0x61, 0xCE, 
                /* 03A0 */    0x70, 0xA0, 0x39, 0x16, 0xC0, 0xBB, 0x55, 0xB0, 
                /* 03A8 */    0x63, 0x01, 0x6C, 0x02, 0x1F, 0x0B, 0xC0, 0x17, 
                /* 03B0 */    0x67, 0x58, 0xE8, 0xD1, 0xFA, 0xFE, 0x87, 0xBB, 
                /* 03B8 */    0x3F, 0x44, 0x79, 0x29, 0xF6, 0x21, 0x07, 0xEE, 
                /* 03C0 */    0xB8, 0xC0, 0x71, 0x7A, 0x00, 0x5C, 0x1D, 0xC4, 
                /* 03C8 */    0xE4, 0xF4, 0xF4, 0x00, 0xAE, 0x24, 0xA7, 0x07, 
                /* 03D0 */    0xD4, 0x80, 0xFD, 0xFF, 0xD7, 0x03, 0xA4, 0x73, 
                /* 03D8 */    0x02, 0xF6, 0xA2, 0xCD, 0x20, 0x4E, 0xF4, 0x79, 
                /* 03E0 */    0xC4, 0x0A, 0x8E, 0x38, 0xA8, 0xEC, 0x24, 0x4A, 
                /* 03E8 */    0x7E, 0xC4, 0x41, 0x65, 0x1D, 0x3B, 0x05, 0x31, 
                /* 03F0 */    0xA0, 0x4F, 0x94, 0x80, 0x8F, 0x3B, 0x0E, 0xB0, 
                /* 03F8 */    0xD8, 0xA8, 0x27, 0xCB, 0x23, 0x4F, 0x96, 0x82, 
                /* 0400 */    0x78, 0xB2, 0xBE, 0x54, 0x00, 0x87, 0x1B, 0x0E, 
                /* 0408 */    0xB0, 0xFF, 0xFF, 0x5F, 0x2A, 0x80, 0x92, 0x43, 
                /* 0410 */    0xA9, 0x97, 0x0A, 0x90, 0xC9, 0xBB, 0xE1, 0xA0, 
                /* 0418 */    0x43, 0xAE, 0x55, 0xF7, 0x3A, 0x76, 0x6C, 0xF5, 
                /* 0420 */    0xB8, 0x7D, 0x93, 0xC6, 0x04, 0xBB, 0xE1, 0xA0, 
                /* 0428 */    0x22, 0x51, 0x28, 0xD0, 0xB9, 0x00, 0x15, 0x01, 
                /* 0430 */    0x8E, 0x82, 0x78, 0x68, 0x3E, 0x17, 0x58, 0xC9, 
                /* 0438 */    0xB9, 0x00, 0xED, 0xFD, 0x42, 0x41, 0x06, 0xE7, 
                /* 0440 */    0x7B, 0x81, 0x61, 0x8A, 0x1F, 0x8A, 0xEE, 0x3D, 
                /* 0448 */    0x3E, 0x17, 0x80, 0xFB, 0x8A, 0x03, 0x2E, 0x63, 
                /* 0450 */    0x02, 0xB4, 0x41, 0x92, 0x7B, 0xB8, 0xC7, 0x85, 
                /* 0458 */    0x1B, 0x87, 0x47, 0x75, 0x4C, 0x31, 0x9F, 0xE3, 
                /* 0460 */    0x82, 0x3C, 0xC7, 0x79, 0x5E, 0xB8, 0xF3, 0x03, 
                /* 0468 */    0x70, 0xFB, 0xFF, 0x0F, 0x0C, 0xD6, 0x85, 0x0B, 
                /* 0470 */    0x88, 0x0B, 0x35, 0x29, 0xF1, 0xFC, 0x00, 0xAE, 
                /* 0478 */    0x5B, 0xB7, 0xEF, 0x85, 0x38, 0x29, 0x77, 0x57, 
                /* 0480 */    0x14, 0xC6, 0x2B, 0x49, 0x0C, 0xDF, 0x53, 0x8D, 
                /* 0488 */    0x6D, 0x98, 0x03, 0x38, 0x15, 0xE3, 0x24, 0x18, 
                /* 0490 */    0xFC, 0xEC, 0x40, 0xC7, 0xE5, 0xC8, 0x24, 0xBA, 
                /* 0498 */    0xED, 0xFB, 0x08, 0xC1, 0x63, 0x8E, 0x9E, 0x82, 
                /* 04A0 */    0x18, 0xD0, 0x19, 0x4E, 0x2A, 0x68, 0x15, 0x20, 
                /* 04A8 */    0x9A, 0x02, 0xE6, 0xE6, 0x0A, 0xF8, 0xFB, 0xFF, 
                /* 04B0 */    0xDF, 0x5C, 0x01, 0x56, 0xB8, 0x54, 0xA8, 0x51, 
                /* 04B8 */    0xEA, 0x91, 0x02, 0x5C, 0x77, 0x40, 0xDF, 0xC2, 
                /* 04C0 */    0x70, 0x92, 0x80, 0x74, 0x65, 0x3D, 0x8D, 0x07, 
                /* 04C8 */    0x00, 0x5F, 0x29, 0x60, 0x5C, 0x3C, 0xD9, 0x11, 
                /* 04D0 */    0x87, 0xDF, 0xAE, 0x7D, 0x2C, 0x00, 0xE6, 0xFF, 
                /* 04D8 */    0xFF, 0x2B, 0x21, 0x58, 0x8F, 0x05, 0xC0, 0x5B, 
                /* 04E0 */    0xA4, 0x4B, 0x8B, 0x66, 0x8F, 0x05, 0xE0, 0x12, 
                /* 04E8 */    0xBF, 0x0A, 0x7A, 0x50, 0xB1, 0x5C, 0x18, 0x94, 
                /* 04F0 */    0x84, 0xB1, 0x43, 0x19, 0xCD, 0xC1, 0x1C, 0x43, 
                /* 04F8 */    0x70, 0x76, 0x86, 0x31, 0x1C, 0x1F, 0xA8, 0xA7, 
                /* 0500 */    0xFE, 0x58, 0x7B, 0x1A, 0xAF, 0x68, 0xBE, 0xE2, 
                /* 0508 */    0xF9, 0x3E, 0x4A, 0x87, 0x88, 0xBA, 0xEA, 0x79, 
                /* 0510 */    0xAC, 0x6F, 0x05, 0xA7, 0xF6, 0xAC, 0xE7, 0x6B, 
                /* 0518 */    0x8B, 0x61, 0x12, 0x78, 0x88, 0x0C, 0x8D, 0x13, 
                /* 0520 */    0xBC, 0x23, 0x19, 0x9A, 0xCB, 0x80, 0xD0, 0x5D, 
                /* 0528 */    0xE9, 0x35, 0xC0, 0x73, 0x33, 0x41, 0xF7, 0x43, 
                /* 0530 */    0x97, 0x42, 0x04, 0x9D, 0x00, 0xDE, 0x09, 0x6A, 
                /* 0538 */    0x14, 0xE0, 0xED, 0x2A, 0x20, 0x5B, 0x02, 0xC4, 
                /* 0540 */    0x8D, 0x5E, 0x58, 0x6F, 0x45, 0x51, 0x42, 0x44, 
                /* 0548 */    0x08, 0x1A, 0xC5, 0x78, 0x11, 0x42, 0x85, 0x88, 
                /* 0550 */    0x12, 0xB5, 0x39, 0x10, 0x5D, 0x8E, 0xA2, 0x06, 
                /* 0558 */    0x89, 0x16, 0xCC, 0x08, 0xCC, 0xFE, 0x20, 0x88, 
                /* 0560 */    0xF4, 0x67, 0x80, 0x2E, 0x33, 0xBE, 0x0C, 0x7B, 
                /* 0568 */    0x34, 0xFC, 0x2C, 0xC5, 0x87, 0x7A, 0x8E, 0x8F, 
                /* 0570 */    0x8A, 0xEC, 0xFF, 0x0F, 0xF2, 0x5A, 0x68, 0x9D, 
                /* 0578 */    0xE3, 0x24, 0x87, 0x1C, 0x83, 0xEB, 0x0C, 0x01, 
                /* 0580 */    0xCD, 0x35, 0xA0, 0x8E, 0xFD, 0x1E, 0xAF, 0xBF, 
                /* 0588 */    0x1A, 0x86, 0xE3, 0x43, 0xF4, 0xA1, 0xC2, 0x13, 
                /* 0590 */    0x38, 0x44, 0x06, 0xE8, 0x43, 0x04, 0xFC, 0xF1, 
                /* 0598 */    0x18, 0xFA, 0x29, 0xC2, 0x13, 0x7E, 0xA1, 0x25, 
                /* 05A0 */    0x83, 0x40, 0x9D, 0x34, 0xF8, 0x48, 0x5F, 0xB8, 
                /* 05A8 */    0xD9, 0xED, 0xC3, 0x04, 0x16, 0x7B, 0x76, 0xA0, 
                /* 05B0 */    0xE3, 0x01, 0xBF, 0xE2, 0x33, 0x81, 0xAE, 0x71, 
                /* 05B8 */    0xC6, 0xF6, 0xC9, 0xC8, 0x11, 0x0E, 0x22, 0x50, 
                /* 05C0 */    0x40, 0x9F, 0x4D, 0xF8, 0xCD, 0x83, 0x1D, 0x2D, 
                /* 05C8 */    0xB8, 0xA8, 0xA3, 0x05, 0xEA, 0xB4, 0xE0, 0x83, 
                /* 05D0 */    0x02, 0x43, 0x7C, 0xF8, 0x34, 0xC4, 0x93, 0x05, 
                /* 05D8 */    0x3B, 0xEA, 0x80, 0x53, 0xDE, 0x21, 0x04, 0x14, 
                /* 05E0 */    0x20, 0x3E, 0x59, 0xB0, 0x79, 0x61, 0x08, 0x2C, 
                /* 05E8 */    0x12, 0x1E, 0x75, 0xE8, 0x30, 0x3C, 0x3F, 0x25, 
                /* 05F0 */    0x3C, 0x8E, 0x30, 0xEC, 0x37, 0x12, 0x4F, 0xE1, 
                /* 05F8 */    0x70, 0x7C, 0xA4, 0x30, 0x42, 0xF0, 0x72, 0x4F, 
                /* 0600 */    0x16, 0xE4, 0x62, 0x73, 0x74, 0xFF, 0xFF, 0x27, 
                /* 0608 */    0x18, 0xCC, 0x50, 0x3D, 0x04, 0x7E, 0x5E, 0xF0, 
                /* 0610 */    0x10, 0xF8, 0x00, 0x5A, 0x9D, 0x1D, 0x39, 0x9F, 
                /* 0618 */    0x9C, 0x13, 0x6E, 0xBC, 0x7C, 0x4C, 0xD8, 0x01, 
                /* 0620 */    0xF0, 0xE0, 0x4B, 0xF2, 0x59, 0x84, 0xC6, 0x58, 
                /* 0628 */    0xBE, 0x8F, 0x23, 0x80, 0x9C, 0x49, 0x3C, 0x81, 
                /* 0630 */    0x44, 0x78, 0x19, 0x09, 0x12, 0xE2, 0x58, 0x5E, 
                /* 0638 */    0x43, 0x0C, 0x12, 0xE3, 0xED, 0xC8, 0xC7, 0x11, 
                /* 0640 */    0x0E, 0xF3, 0x4C, 0x62, 0xB8, 0x87, 0x83, 0x57, 
                /* 0648 */    0x91, 0x17, 0x12, 0xC3, 0x3C, 0x8A, 0xF8, 0x7C, 
                /* 0650 */    0x10, 0xC3, 0x98, 0xA1, 0xA2, 0x9D, 0x80, 0x8F, 
                /* 0658 */    0x23, 0xEC, 0x58, 0xE9, 0xA1, 0xFA, 0x38, 0x02, 
                /* 0660 */    0x58, 0xFA, 0xFF, 0x1F, 0x47, 0x80, 0xF9, 0x11, 
                /* 0668 */    0x01, 0x77, 0xDA, 0x80, 0x7B, 0x9F, 0x08, 0xF1, 
                /* 0670 */    0xA4, 0xF1, 0x92, 0xF0, 0xAC, 0x01, 0x5C, 0x84, 
                /* 0678 */    0x6A, 0x39, 0xF7, 0xB0, 0x34, 0x8F, 0x01, 0x1D, 
                /* 0680 */    0xCF, 0x38, 0x87, 0x35, 0x01, 0x69, 0x98, 0xFC, 
                /* 0688 */    0xCA, 0xED, 0x73, 0xC1, 0xD9, 0x3D, 0x72, 0x1B, 
                /* 0690 */    0x26, 0xC8, 0x13, 0xC1, 0x6B, 0x94, 0xC1, 0x05, 
                /* 0698 */    0xA9, 0xF3, 0x23, 0x4F, 0x4F, 0x21, 0xDD, 0x27, 
                /* 06A0 */    0x5A, 0x94, 0xD2, 0x63, 0x1A, 0x05, 0xF1, 0x19, 
                /* 06A8 */    0xC1, 0x21, 0xCE, 0x31, 0xE8, 0xE1, 0x7B, 0x0E, 
                /* 06B0 */    0x67, 0x74, 0x20, 0xEF, 0x01, 0xEC, 0xFE, 0x08, 
                /* 06B8 */    0x3C, 0x4F, 0x3A, 0x78, 0x74, 0xDF, 0x14, 0xCE, 
                /* 06C0 */    0xF3, 0x4C, 0xFF, 0xFF, 0x47, 0x04, 0xDE, 0x99, 
                /* 06C8 */    0xFA, 0x82, 0x09, 0x9C, 0x43, 0xDC, 0x05, 0x50, 
                /* 06D0 */    0xB2, 0xEF, 0x02, 0x14, 0xC4, 0x13, 0xF3, 0xD5, 
                /* 06D8 */    0x0F, 0x0E, 0xFE, 0xAB, 0x1F, 0x30, 0xB9, 0x2C, 
                /* 06E0 */    0xF8, 0x9A, 0x04, 0xBE, 0x53, 0x3F, 0xFE, 0xC2, 
                /* 06E8 */    0xE0, 0xDB, 0xC0, 0xC3, 0x13, 0x1B, 0x14, 0xF8, 
                /* 06F0 */    0xA1, 0x7C, 0x3D, 0x04, 0xFF, 0xFF, 0xFF, 0x7A, 
                /* 06F8 */    0x08, 0x3C, 0x95, 0x3A, 0xB5, 0xA9, 0xF0, 0x7A, 
                /* 0700 */    0x08, 0xAE, 0x28, 0xD7, 0x12, 0xD4, 0xAD, 0xC9, 
                /* 0708 */    0x82, 0x80, 0x74, 0x3F, 0x7F, 0xBE, 0x31, 0xA6, 
                /* 0710 */    0xCF, 0x25, 0xF0, 0xEE, 0xA0, 0x5A, 0x95, 0xEE, 
                /* 0718 */    0x25, 0x3C, 0x38, 0x85, 0xA2, 0x1F, 0x1E, 0x50, 
                /* 0720 */    0x61, 0x0F, 0x0F, 0x14, 0xC4, 0x17, 0x23, 0xDF, 
                /* 0728 */    0x4B, 0x00, 0x0E, 0xFC, 0xFF, 0x47, 0xC4, 0x6F, 
                /* 0730 */    0xDA, 0x70, 0x8E, 0x16, 0x98, 0x19, 0x81, 0xF5, 
                /* 0738 */    0x44, 0xE0, 0x9B, 0x36, 0xE0, 0xE8, 0xE4, 0x02, 
                /* 0740 */    0x5C, 0x4E, 0x25, 0x80, 0x2B, 0xAF, 0xA7, 0x12, 
                /* 0748 */    0xFD, 0xFF, 0x4F, 0x25, 0xE0, 0xBA, 0x7B, 0x81, 
                /* 0750 */    0xE9, 0x6A, 0x72, 0x26, 0xD1, 0x82, 0xFB, 0xEE, 
                /* 0758 */    0x05, 0xF0, 0xF3, 0xFF, 0x7F, 0xF7, 0x02, 0x88, 
                /* 0760 */    0xE9, 0xF5, 0xEE, 0x05, 0xBC, 0xCE, 0x25, 0x98, 
                /* 0768 */    0xBB, 0x97, 0xFF, 0xFF, 0x77, 0x2F, 0x80, 0xFF, 
                /* 0770 */    0xFF, 0xFF, 0xBB, 0x17, 0x40, 0x96, 0x53, 0x09, 
                /* 0778 */    0xC8, 0xB2, 0x9D, 0x4A, 0xD0, 0x0A, 0xCF, 0xD1, 
                /* 0780 */    0x50, 0x27, 0x70, 0x28, 0x4F, 0x18, 0xAF, 0xEA, 
                /* 0788 */    0x09, 0xAC, 0xE7, 0xF2, 0x85, 0x52, 0x02, 0xA3, 
                /* 0790 */    0xCB, 0x17, 0xB0, 0xFB, 0xFF, 0x5F, 0xBE, 0x00, 
                /* 0798 */    0x3E, 0x04, 0xBA, 0x0B, 0xA0, 0x22, 0xDC, 0x05, 
                /* 07A0 */    0x28, 0x88, 0x2F, 0x5F, 0x80, 0x97, 0x50, 0x10, 
                /* 07A8 */    0x32, 0x72, 0x93, 0xA0, 0x97, 0x2F, 0x38, 0x17, 
                /* 07B0 */    0x07, 0xDF, 0x8F, 0x3C, 0x28, 0x78, 0xFF, 0xFF, 
                /* 07B8 */    0x41, 0xC1, 0x19, 0xCC, 0x79, 0x17, 0x7B, 0x52, 
                /* 07C0 */    0xA4, 0xD7, 0x13, 0xB8, 0x77, 0x0E, 0x8F, 0x0D, 
                /* 07C8 */    0x1C, 0xE2, 0xAE, 0x60, 0xC0, 0xDE, 0xE5, 0xED, 
                /* 07D0 */    0x04, 0x5C, 0xDA, 0xD6, 0xAE, 0xDB, 0x09, 0x2E, 
                /* 07D8 */    0xE1, 0x71, 0x1A, 0xF2, 0xF1, 0x04, 0x93, 0xE7, 
                /* 07E0 */    0x76, 0x82, 0x4A, 0x02, 0xA3, 0x2C, 0x24, 0x3A, 
                /* 07E8 */    0x42, 0x70, 0xF5, 0x37, 0x31, 0x0A, 0x62, 0x0B, 
                /* 07F0 */    0xB7, 0x13, 0x40, 0xC7, 0xFF, 0xFF, 0x76, 0x02, 
                /* 07F8 */    0xFC, 0xC7, 0x0C, 0x67, 0x44, 0xEF, 0x15, 0x86, 
                /* 0800 */    0xF4, 0x19, 0x0C, 0x98, 0x06, 0x3A, 0x82, 0xA0, 
                /* 0808 */    0x2F, 0x69, 0xD8, 0x04, 0x37, 0x10, 0x3A, 0x23, 
                /* 0810 */    0x78, 0x17, 0x10, 0xB8, 0x13, 0x83, 0x75, 0x00, 
                /* 0818 */    0x01, 0xDF, 0x59, 0x0D, 0x78, 0xFD, 0xFF, 0xCF, 
                /* 0820 */    0x6A, 0xC0, 0xF4, 0x00, 0xE0, 0xB3, 0x1A, 0xA0, 
                /* 0828 */    0xEA, 0xF6, 0x02, 0x32, 0x85, 0x36, 0x7D, 0x6A, 
                /* 0830 */    0x34, 0x6A, 0xD5, 0xA0, 0x4C, 0x8D, 0x32, 0x0D, 
                /* 0838 */    0x6A, 0xF5, 0xA9, 0xD4, 0x98, 0x31, 0xBB, 0x60, 
                /* 0840 */    0x8A, 0x71, 0x7B, 0xA2, 0x22, 0x96, 0x23, 0x10, 
                /* 0848 */    0xEB, 0xA6, 0x90, 0x91, 0xCB, 0x86, 0x41, 0x04, 
                /* 0850 */    0x64, 0xD9, 0x8B, 0x16, 0x10, 0x01, 0x11, 0x90, 
                /* 0858 */    0x85, 0xBC, 0x1B, 0x04, 0x64, 0x55, 0x20, 0x02, 
                /* 0860 */    0x72, 0x2A, 0x20, 0x1A, 0x11, 0x88, 0xC6, 0xF1, 
                /* 0868 */    0x00, 0xC4, 0xC2, 0x81, 0x08, 0xC8, 0xEA, 0x4C, 
                /* 0870 */    0x00, 0x31, 0xA9, 0x20, 0xBA, 0x43, 0x90, 0xCF, 
                /* 0878 */    0x85, 0x80, 0x2C, 0x12, 0x44, 0x40, 0xCE, 0xB8, 
                /* 0880 */    0x3E, 0x01, 0x39, 0x30, 0x88, 0x80, 0x1C, 0xF2, 
                /* 0888 */    0x1B, 0x22, 0x20, 0x47, 0x06, 0x11, 0x90, 0x05, 
                /* 0890 */    0xEB, 0x00, 0xF2, 0xFF, 0x9F, 0xA0, 0x7C, 0x10, 
                /* 0898 */    0x01, 0x39, 0x3E, 0x10, 0x15, 0xE3, 0xE3, 0xAE, 
                /* 08A0 */    0x45, 0x1F, 0x03, 0x02, 0x72, 0x2E, 0x10, 0x01, 
                /* 08A8 */    0x39, 0x07, 0x8D, 0x80, 0x9C, 0x8A, 0x42, 0x40, 
                /* 08B0 */    0x56, 0xF5, 0x76, 0x10, 0x90, 0x35, 0x82, 0x08, 
                /* 08B8 */    0xC8, 0x29, 0x81, 0x68, 0x66, 0x20, 0x2A, 0xD8, 
                /* 08C0 */    0x0A, 0x10, 0x53, 0x0F, 0x22, 0x20, 0x2B, 0xD5, 
                /* 08C8 */    0x02, 0xC4, 0x74, 0x83, 0x08, 0xC8, 0xA9, 0xBD, 
                /* 08D0 */    0x00, 0x31, 0x0D, 0xEF, 0x00, 0x01, 0x59, 0xEB, 
                /* 08D8 */    0xD3, 0x43, 0x20, 0x4E, 0x0A, 0x42, 0xB5, 0xBA, 
                /* 08E0 */    0x01, 0x61, 0x39, 0xED, 0x80, 0x30, 0x95, 0x7A, 
                /* 08E8 */    0x40, 0x58, 0x1E, 0x3F, 0x43, 0xA6, 0x20, 0x02, 
                /* 08F0 */    0xB2, 0xA2, 0x97, 0x88, 0x80, 0x2C, 0x0F, 0x44, 
                /* 08F8 */    0x40, 0x96, 0x62, 0x08, 0x88, 0x09, 0x03, 0x11, 
                /* 0900 */    0x90, 0x23, 0x01, 0xD1, 0x80, 0x40, 0x54, 0x9E, 
                /* 0908 */    0x23, 0x20, 0xA6, 0x15, 0x44, 0x40, 0x0E, 0x08, 
                /* 0910 */    0x44, 0xD3, 0x02, 0x51, 0x8D, 0xBF, 0x25, 0x01, 
                /* 0918 */    0x59, 0x30, 0x88, 0x80, 0x2C, 0xCE, 0xD2, 0x51, 
                /* 0920 */    0x80, 0x82, 0x08, 0xC8, 0x31, 0x35, 0x0D, 0x95, 
                /* 0928 */    0x82, 0x08, 0xC8, 0x42, 0x3D, 0x01, 0x31, 0xD5, 
                /* 0930 */    0x20, 0x02, 0xB2, 0x42, 0x51, 0x40, 0x4C, 0x2F, 
                /* 0938 */    0x88, 0x06, 0x49, 0x80, 0x68, 0x6E, 0x20, 0xAA, 
                /* 0940 */    0x5A, 0x15, 0x10, 0x8B, 0x00, 0x22, 0x20, 0xE7, 
                /* 0948 */    0x06, 0xA2, 0x22, 0x5C, 0x01, 0x31, 0xE9, 0x20, 
                /* 0950 */    0x02, 0x72, 0x0E, 0x20, 0xAA, 0xF9, 0x49, 0x21, 
                /* 0958 */    0x20, 0x27, 0x00, 0x11, 0x90, 0xF3, 0xDB, 0x3A, 
                /* 0960 */    0x1A, 0xD0, 0x87, 0x8E, 0x80, 0x9C, 0x00, 0x44, 
                /* 0968 */    0x40, 0x8E, 0x03, 0x44, 0xA5, 0xFB, 0x02, 0x62, 
                /* 0970 */    0x41, 0x40, 0x04, 0x64, 0x41, 0xAF, 0x11, 0x0D, 
                /* 0978 */    0x9C, 0x80, 0x08, 0xC8, 0xD1, 0x8C, 0x01, 0xB1, 
                /* 0980 */    0x9C, 0x20, 0x02, 0xFA, 0xFF, 0x1F, 0xA8, 0xBE, 
                /* 0988 */    0x22, 0x02, 0xB2, 0x52, 0x10, 0x0D, 0x9A, 0x00, 
                /* 0990 */    0xD1, 0xB4, 0x40, 0x54, 0xF1, 0x9B, 0xE4, 0xD1, 
                /* 0998 */    0x81, 0x81, 0xE8, 0x88, 0x40, 0xA4, 0x1D, 0x11, 
                /* 09A0 */    0x28, 0x88, 0x80, 0xFC, 0xFF, 0x07
            })
            Method (SPEC, 1, Serialized)
            {
                Return (AMWV)
            }

            Method (DEVP, 1, Serialized)
            {
                CreateDWordField (Arg0, Zero, DVID)
                CreateDWordField (Arg0, 0x04, PARA)
                If (LEqual (PARA, One))
                {
                    Name (_T_0, Zero)
                    Store (DVID, _T_0)
                    If (LEqual (_T_0, 0x00010011))
                    {
                        Or (\_SB.DSAF, One, \_SB.DSAF)
                    }
                    Else
                    {
                        If (LEqual (_T_0, 0x00010013))
                        {
                            Or (\_SB.DSAF, 0x02, \_SB.DSAF)
                        }
                        Else
                        {
                            If (LEqual (_T_0, 0x00010023))
                            {
                                Or (\_SB.DSAF, 0x04, \_SB.DSAF)
                            }
                            Else
                            {
                                If (LEqual (_T_0, 0x00060013))
                                {
                                    Or (\_SB.DSAF, 0x08, \_SB.DSAF)
                                }
                                Else
                                {
                                    If (LEqual (_T_0, 0x00060015))
                                    {
                                        Or (\_SB.DSAF, 0x10, \_SB.DSAF)
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_0, 0x00010015))
                                        {
                                            Or (\_SB.DSAF, 0x20, \_SB.DSAF)
                                        }
                                        Else
                                        {
                                            If (LEqual (_T_0, 0x00090011))
                                            {
                                                Or (\_SB.DSAF, 0x40, \_SB.DSAF)
                                            }
                                            Else
                                            {
                                                If (LEqual (_T_0, 0x00070011))
                                                {
                                                    Or (\_SB.DSAF, 0x80, \_SB.DSAF)
                                                }
                                                Else
                                                {
                                                    If (LEqual (_T_0, 0x00080013))
                                                    {
                                                        Or (\_SB.DSAF, 0x0100, \_SB.DSAF)
                                                    }
                                                    Else
                                                    {
                                                        If (LEqual (_T_0, 0x00010019))
                                                        {
                                                            Or (\_SB.DSAF, 0x0200, \_SB.DSAF)
                                                        }
                                                        Else
                                                        {
                                                            If (LEqual (_T_0, 0x00010017))
                                                            {
                                                                Or (\_SB.DSAF, 0x0400, \_SB.DSAF)
                                                            }
                                                            Else
                                                            {
                                                                If (LEqual (_T_0, 0x00050011))
                                                                {
                                                                    Or (\_SB.DSAF, 0x0800, \_SB.DSAF)
                                                                }
                                                                Else
                                                                {
                                                                    If (LEqual (_T_0, 0x00050012))
                                                                    {
                                                                        Or (\_SB.DSAF, 0x1000, \_SB.DSAF)
                                                                    }
                                                                    Else
                                                                    {
                                                                        If (LEqual (_T_0, 0x00060017))
                                                                        {
                                                                            Or (\_SB.DSAF, 0x2000, \_SB.DSAF)
                                                                        }
                                                                        Else
                                                                        {
                                                                            If (LEqual (_T_0, 0x00080021))
                                                                            {
                                                                                Or (\_SB.DSAF, 0x4000, \_SB.DSAF)
                                                                            }
                                                                            Else
                                                                            {
                                                                                If (LEqual (_T_0, 0x00100011))
                                                                                {
                                                                                    Or (\_SB.DSAF, 0x8000, \_SB.DSAF)
                                                                                }
                                                                                Else
                                                                                {
                                                                                    If (LEqual (_T_0, 0x00050001))
                                                                                    {
                                                                                        Or (\_SB.DSAF, 0x00010000, \_SB.DSAF)
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If (LEqual (_T_0, 0x00120000))
                                                                                        {
                                                                                            Or (\_SB.DSAF, 0x00020000, \_SB.DSAF)
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If (LEqual (_T_0, 0x00120021))
                                                                                            {
                                                                                                Or (\_SB.DSAF, 0x00040000, \_SB.DSAF)
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If (LEqual (_T_0, 0x00120011))
                                                                                                {
                                                                                                    Or (\_SB.DSAF, 0x00080000, \_SB.DSAF)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    Return (Zero)
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Else
                {
                    If (LEqual (PARA, Zero))
                    {
                        Name (_T_1, Zero)
                        Store (DVID, _T_1)
                        If (LEqual (_T_1, 0x00010011))
                        {
                            And (\_SB.DSAF, 0xFFFFFFFFFFFFFFFE, \_SB.DSAF)
                        }
                        Else
                        {
                            If (LEqual (_T_1, 0x00010013))
                            {
                                And (\_SB.DSAF, 0xFFFFFFFFFFFFFFFD, \_SB.DSAF)
                            }
                            Else
                            {
                                If (LEqual (_T_1, 0x00010023))
                                {
                                    And (\_SB.DSAF, 0xFFFFFFFFFFFFFFFB, \_SB.DSAF)
                                }
                                Else
                                {
                                    If (LEqual (_T_1, 0x00060013))
                                    {
                                        And (\_SB.DSAF, 0xFFFFFFFFFFFFFFF7, \_SB.DSAF)
                                    }
                                    Else
                                    {
                                        If (LEqual (_T_1, 0x00060015))
                                        {
                                            And (\_SB.DSAF, 0xFFFFFFFFFFFFFFEF, \_SB.DSAF)
                                        }
                                        Else
                                        {
                                            If (LEqual (_T_1, 0x00010015))
                                            {
                                                And (\_SB.DSAF, 0xFFFFFFFFFFFFFFDF, \_SB.DSAF)
                                            }
                                            Else
                                            {
                                                If (LEqual (_T_1, 0x00090011))
                                                {
                                                    And (\_SB.DSAF, 0xFFFFFFFFFFFFFFBF, \_SB.DSAF)
                                                }
                                                Else
                                                {
                                                    If (LEqual (_T_1, 0x00070011))
                                                    {
                                                        And (\_SB.DSAF, 0xFFFFFFFFFFFFFF7F, \_SB.DSAF)
                                                    }
                                                    Else
                                                    {
                                                        If (LEqual (_T_1, 0x00080013))
                                                        {
                                                            And (\_SB.DSAF, 0xFFFFFFFFFFFFFEFF, \_SB.DSAF)
                                                        }
                                                        Else
                                                        {
                                                            If (LEqual (_T_1, 0x00010019))
                                                            {
                                                                And (\_SB.DSAF, 0xFFFFFFFFFFFFFDFF, \_SB.DSAF)
                                                            }
                                                            Else
                                                            {
                                                                If (LEqual (_T_1, 0x00010017))
                                                                {
                                                                    And (\_SB.DSAF, 0xFFFFFFFFFFFFFBFF, \_SB.DSAF)
                                                                }
                                                                Else
                                                                {
                                                                    If (LEqual (_T_1, 0x00050011))
                                                                    {
                                                                        And (\_SB.DSAF, 0xFFFFFFFFFFFFF7FF, \_SB.DSAF)
                                                                    }
                                                                    Else
                                                                    {
                                                                        If (LEqual (_T_1, 0x00050012))
                                                                        {
                                                                            And (\_SB.DSAF, 0xFFFFFFFFFFFFEFFF, \_SB.DSAF)
                                                                        }
                                                                        Else
                                                                        {
                                                                            If (LEqual (_T_1, 0x00060017))
                                                                            {
                                                                                And (\_SB.DSAF, 0xFFFFFFFFFFFFDFFF, \_SB.DSAF)
                                                                            }
                                                                            Else
                                                                            {
                                                                                If (LEqual (_T_1, 0x00080021))
                                                                                {
                                                                                    And (\_SB.DSAF, 0xFFFFFFFFFFFFBFFF, \_SB.DSAF)
                                                                                }
                                                                                Else
                                                                                {
                                                                                    If (LEqual (_T_1, 0x00100011))
                                                                                    {
                                                                                        And (\_SB.DSAF, 0xFFFFFFFFFFFF7FFF, \_SB.DSAF)
                                                                                    }
                                                                                    Else
                                                                                    {
                                                                                        If (LEqual (_T_1, 0x00050001))
                                                                                        {
                                                                                            And (\_SB.DSAF, 0xFFFFFFFFFFFEFFFF, \_SB.DSAF)
                                                                                        }
                                                                                        Else
                                                                                        {
                                                                                            If (LEqual (_T_1, 0x00120000))
                                                                                            {
                                                                                                And (\_SB.DSAF, 0xFFFFFFFFFFFDFFFF, \_SB.DSAF)
                                                                                            }
                                                                                            Else
                                                                                            {
                                                                                                If (LEqual (_T_1, 0x00120021))
                                                                                                {
                                                                                                    And (\_SB.DSAF, 0xFFFFFFFFFFFBFFFF, \_SB.DSAF)
                                                                                                }
                                                                                                Else
                                                                                                {
                                                                                                    If (LEqual (_T_1, 0x00120011))
                                                                                                    {
                                                                                                        And (\_SB.DSAF, 0xFFFFFFFFFFF7FFFF, \_SB.DSAF)
                                                                                                    }
                                                                                                    Else
                                                                                                    {
                                                                                                        Return (Zero)
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                Return (One)
            }

            Method (SDSP, 1, Serialized)
            {
                CreateDWordField (Arg0, Zero, ACTN)
                Return (Zero)
            }

            Method (GDSP, 1, Serialized)
            {
                CreateDWordField (Arg0, Zero, ACTN)
                Return (Zero)
            }

            Method (DEVS, 1, Serialized)
            {
                CreateDWordField (Arg0, Zero, DVID)
                CreateDWordField (Arg0, 0x04, CPAR)
                Name (_T_0, Zero)
                Store (DVID, _T_0)
                If (LEqual (_T_0, Zero))
                {
                    Return (Zero)
                }
                Else
                {
                    Return (Zero)
                }
            }

            Method (DSTS, 1, Serialized)
            {
                CreateDWordField (Arg0, Zero, DVID)
                Name (_T_0, Zero)
                Store (DVID, _T_0)
                If (LEqual (_T_0, 0xA0000000))
                {
                    Store (One, Local0)
                }
                Else
                {
                    If (LEqual (_T_0, Zero))
                    {
                        Return (Zero)
                    }
                    Else
                    {
                        Store (Zero, Local0)
                    }
                }

                And (Local0, 0x0007FFFF, Local0)
                Return (Local0)
            }

            Method (GPID, 0, Serialized)
            {
                Return (Zero)
            }

            Method (KBFT, 1, Serialized)
            {
                Return (Zero)
            }

            Method (HKEY, 0, Serialized)
            {
                Return (Zero)
            }

            Method (CFVS, 1, Serialized)
            {
            }

            Method (CFVG, 0, Serialized)
            {
            }
        }
    }

    Scope (_SB)
    {
        Name (RAMB, 0xDCB94018)
        OperationRegion (\RAMW, SystemMemory, RAMB, 0x00010000)
        Field (RAMW, ByteAcc, NoLock, Preserve)
        {
            DSAF,   256, 
            PAR0,   32, 
            PAR1,   32, 
            PAR2,   32, 
            PINX,   32, 
            PADD,   2048
        }

        Mutex (MPAR, 0x00)
        Name (ARBF, Buffer (0x10) {})
        CreateDWordField (ARBF, Zero, REAX)
        CreateDWordField (ARBF, 0x04, REBX)
        CreateDWordField (ARBF, 0x08, RECX)
        CreateDWordField (ARBF, 0x0C, REDX)
        OperationRegion (IOB2, SystemIO, SMIP, 0x02)
        Field (IOB2, ByteAcc, NoLock, Preserve)
        {
            SMIC,   8, 
            SMIS,   8
        }

        Method (ISMI, 1, Serialized)
        {
            Store (Arg0, SMIC)
        }

        Method (GMSR, 1, Serialized)
        {
            If (LEqual (Acquire (MPAR, 0xFFFF), Zero))
            {
                Store (0x80000000, PINX)
                Store (Arg0, PAR0)
                ISMI (0x90)
                Store (Arg0, RECX)
                Store (PAR1, REAX)
                Store (PAR2, REDX)
                Release (MPAR)
                Return (ARBF)
            }

            Return (Ones)
        }

        Method (SMSR, 1, Serialized)
        {
            If (LEqual (Acquire (MPAR, 0xFFFF), Zero))
            {
                CreateDWordField (Arg0, Zero, AEAX)
                CreateDWordField (Arg0, 0x04, AEBX)
                CreateDWordField (Arg0, 0x08, AECX)
                CreateDWordField (Arg0, 0x0C, AEDX)
                Store (0x80000001, PINX)
                Store (AECX, PAR0)
                Store (AEAX, PAR1)
                Store (AEDX, PAR2)
                ISMI (0x90)
                Release (MPAR)
            }

            Return (Ones)
        }

        Method (PRID, 1, Serialized)
        {
            If (LEqual (Acquire (MPAR, 0xFFFF), Zero))
            {
                Store (0x80000002, PINX)
                Store (Arg0, PAR0)
                ISMI (0x90)
                Store (PAR1, REAX)
                Store (PAR2, REDX)
                Release (MPAR)
                Return (ARBF)
            }

            Return (Ones)
        }

        Method (GPRE, 1, Serialized)
        {
            Store (Arg0, PAR0)
            Store (0x80000005, PINX)
            ISMI (0x90)
            Return (PAR0)
        }

        Method (GNVS, 1, Serialized)
        {
            Store (Arg0, PAR0)
            Store (0x80000003, PINX)
            ISMI (0x90)
            Return (PAR1)
        }

        Method (SNVS, 2, Serialized)
        {
            Store (Arg0, PAR0)
            Store (Arg1, PAR1)
            Store (0x80000004, PINX)
            ISMI (0x90)
        }

        Method (SARM, 1, Serialized)
        {
            If (LAnd (LGreater (Arg0, 0x03), LLess (Arg0, 0x06)))
            {
                ISMI (0x92)
            }
        }

        Method (GAMM, 0, Serialized)
        {
            ISMI (0x91)
        }

        Method (SAMM, 0, Serialized)
        {
            ISMI (0x92)
        }
    }

    Scope (_SB.PCI0.LPCB)
    {
        Method (S1RS, 1, NotSerialized)
        {
            Store (Zero, PLED)
        }

        OperationRegion (GPBX, SystemIO, GPBS, GPLN)
        Field (GPBX, ByteAcc, NoLock, Preserve)
        {
                    Offset (0x18), 
                ,   27, 
            PLED,   1
        }
    }

    Scope (_SB.PCI0.LPCB)
    {
        Device (H_EC)
        {
            Name (_HID, EisaId ("PNP0C09"))
            Name (_UID, One)
            Method (_STA, 0, NotSerialized)
            {
                Store (0x03, ^^^GFX0.CLID)
                Return (Zero)
            }

            Name (B1CC, Zero)
            Name (B1ST, Zero)
            Name (B2CC, Zero)
            Name (B2ST, Zero)
            Name (CFAN, Zero)
            Name (CMDR, Zero)
            Name (DOCK, Zero)
            Name (EJET, Zero)
            Name (MCAP, Zero)
            Name (PLMX, Zero)
            Name (PECH, Zero)
            Name (PECL, Zero)
            Name (PENV, Zero)
            Name (PINV, Zero)
            Name (PPSH, Zero)
            Name (PPSL, Zero)
            Name (PSTP, Zero)
            Name (RPWR, Zero)
            Name (LSTE, Zero)
            Name (SLPC, Zero)
            Name (VPWR, Zero)
            Method (ECMD, 1, Serialized)
            {
                If (ECON)
                {
                    While (CMDR)
                    {
                        Stall (0x14)
                    }

                    Store (Arg0, CMDR)
                }
            }

            Device (BAT0)
            {
                Name (_HID, EisaId ("PNP0C0A"))
                Name (_UID, Zero)
                Method (_STA, 0, NotSerialized)
                {
                    Return (Zero)
                }
            }

            Scope (\)
            {
                Field (GNVS, AnyAcc, Lock, Preserve)
                {
                            Offset (0x1E), 
                    BNUM,   8, 
                            Offset (0x20), 
                    B1SC,   8, 
                            Offset (0x23), 
                    B1SS,   8
                }
            }

            Device (BAT1)
            {
                Name (_HID, EisaId ("PNP0C0A"))
                Name (_UID, One)
                Method (_STA, 0, NotSerialized)
                {
                    Return (Zero)
                }
            }

            Scope (\)
            {
                Field (GNVS, AnyAcc, Lock, Preserve)
                {
                            Offset (0x21), 
                    B2SC,   8, 
                            Offset (0x24), 
                    B2SS,   8
                }
            }

            Device (BAT2)
            {
                Name (_HID, EisaId ("PNP0C0A"))
                Name (_UID, 0x02)
                Method (_STA, 0, NotSerialized)
                {
                    Return (Zero)
                }
            }
        }
    }

    Device (_SB.PCI0.DOCK)
    {
        Name (_HID, "ABCDEFGH")
        Name (_CID, EisaId ("PNP0C15"))
        Name (_UID, 0x02)
        Method (_STA, 0, NotSerialized)
        {
            Return (Zero)
        }
    }

    Scope (_SB)
    {
        Device (LID0)
        {
            Name (_HID, EisaId ("PNP0C0D"))
            Method (_STA, 0, NotSerialized)
            {
                Return (Zero)
            }
        }
    }

    Name (_S0, Package (0x04)
    {
        Zero, 
        Zero, 
        Zero, 
        Zero
    })
    If (SS1)
    {
        Name (_S1, Package (0x04)
        {
            One, 
            Zero, 
            Zero, 
            Zero
        })
    }

    If (SS3)
    {
        Name (_S3, Package (0x04)
        {
            0x05, 
            Zero, 
            Zero, 
            Zero
        })
    }

    If (SS4)
    {
        Name (_S4, Package (0x04)
        {
            0x06, 
            Zero, 
            Zero, 
            Zero
        })
    }

    Name (_S5, Package (0x04)
    {
        0x07, 
        Zero, 
        Zero, 
        Zero
    })
    Method (PTS, 1, NotSerialized)
    {
        If (Arg0)
        {
            \_SB.PCI0.LPCB.SPTS (Arg0)
            \_SB.PCI0.NPTS (Arg0)
            \_SB.SARM (Arg0)
            \_SB.PCI0.LPCB.SIOS (Arg0)
        }
    }

    Method (WAK, 1, NotSerialized)
    {
        \_SB.PCI0.LPCB.SWAK (Arg0)
        \_SB.PCI0.NWAK (Arg0)
        \_SB.PCI0.LPCB.S1RS (Arg0)
        \_SB.PCI0.LPCB.SIOW (Arg0)
    }
}

