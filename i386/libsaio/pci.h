/*
 *
 * Copyright 2008 by Islam M. Ahmed Zaid. All rights reserved.
 *
 * Refactoring for Revolution done by DHP in 2011.
 *
 */

#define READ_BYTE	1
#define READ_WORD	2
#define READ_LONG	4

#define PCI_ADDR_REG	0xcf8
#define PCI_DATA_REG	0xcfc

#define PCIADDR(bus, dev, func)		(1 << 31) | (bus << 16) | (dev << 11) | (func << 8)

uint32_t pciConfigRead( uint8_t readType, uint32_t pciAddress, uint8_t pciRegister);

//==============================================================================
// Note: Currently only called from: i386/libsaio/cpu/dynamic_data.h

static inline uint8_t pciConfigRead8(uint32_t pciAddress, uint8_t pciRegister)
{
	return (uint8_t)pciConfigRead(READ_BYTE, pciAddress, pciRegister);
}

//==============================================================================
// Note: Currently only called from: i386/libsaio/cpu/dynamic_data.h


static inline uint16_t pciConfigRead16(uint32_t pciAddress, uint8_t pciRegister)
{
	return (uint16_t)pciConfigRead(READ_WORD, pciAddress, pciRegister);
}

//==============================================================================
// Note: Currently only called from: i386/libsaio/cpu/dynamic_data.h

static inline uint32_t pciConfigRead32(uint32_t pciAddress, uint8_t pciRegister)
{
	return (uint32_t)pciConfigRead(READ_LONG, pciAddress, pciRegister);
}
