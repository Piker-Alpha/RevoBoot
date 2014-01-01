/*
 * Copyright (c) 2012-2013 Pike R. Alpha. All rights reserved.
 *
 * Original idea and initial development of MSRDumper.kext (c) 2011 by RevoGirl.
 *
 * Thanks to George for his help and continuation of Sam's work, but it is
 * time for us to push the envelope and add some really interesting stuff.
 *
 */

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOTimerEventSource.h>

#include <i386/cpuid.h>
#include <i386/proc_reg.h>

#include "../../../essentials.h"

#define super IOService

#define REPORT_MSRS			1
#define REPORT_GPU_STATS	1
#define REPORT_C_STATES		1

#define NB_BUS	0x00
#define NB_DEV	0x00
#define NB_FUN	0x00

#define DEVEN	(0x54)
#define DEVEN_D2EN_MASK	(0x10)

#define NB_PCICFG_SPACE_INDEX_REG	0xcf8
#define NB_PCICFG_SPACE_DATA_REG	0xcfc

#define BIT31						0x80000000

#define PCIEX_BASE_ADDRESS			0xF8000000
#define NB_MCH_BASE_ADDRESS			0xFED10000	// (G)MCH Memory Mapped Register Range Base Address (D0:F0:Rx48).

#define READ_PCI8(Bx, Dx, Fx, Rx)	ReadPci8(Bx, Dx, Fx, Rx)
#define READ_PCI8_NB(Rx)			READ_PCI8(NB_BUS, NB_DEV, NB_FUN, Rx)
#define MMIO_READ8(Address)			(*(volatile UInt8  *)(Address))

#define IGPU_RATIO_TO_FREQUENCY(ratio)	((ratio * 100) / 2)

#define NB_PCI_CFG_ADDRESS(bus, dev, func, reg) \
(UInt64) ((((UInt8)(bus) << 24) + ((UInt8)(dev) << 16) + \
((UInt8)(func) << 8) + ((UInt8)(reg))) & 0xffffffff)

#define NB_PCIE_CFG_ADDRESS(bus, dev, func, reg) \
((UInt32)(PCIEX_BASE_ADDRESS + ((UInt8)(bus) << 20) + \
((UInt8)(dev) << 15) + ((UInt8)(func) << 12) + (reg)))

static __inline__ unsigned char inb(UInt16 port)
{
	UInt8 value;
	__asm__ volatile("inb %w1, %b0" : "=a" (value) : "Nd" (port));
	return (value);
}

static __inline__ void outl(UInt16 port, UInt32 value)
{
	__asm__ volatile("outl %0, %w1" : : "a" (value), "Nd" (port));
}

UInt8 ReadPci8(UInt8 Bus, UInt8 Dev, UInt8 Fun, UInt16 Reg)
{
	if (Reg >= 0x100)
	{
		// return MMIO_READ8(NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg));
		return MMIO_READ8((UInt64)NB_PCIE_CFG_ADDRESS(Bus, Dev, Fun, Reg));
	}
	else
	{
		outl(NB_PCICFG_SPACE_INDEX_REG, BIT31 | (Bus << 16) | (Dev << 11) | (Fun << 8) | (Reg & 0xfc));
		return inb(NB_PCICFG_SPACE_DATA_REG | (UInt8)(Reg & 3));
    }
}

extern "C" void mp_rendezvous_no_intrs(void (*action_func)(void *), void * arg);
extern "C" int cpu_number(void);

class AppleIntelCPUPowerManagementInfo : public IOService
{
	OSDeclareDefaultStructors (AppleIntelCPUPowerManagementInfo);
	
private:
	IOSimpleLock		*simpleLock;
	IOWorkLoop			*workLoop;
	IOTimerEventSource	*timerEventSource;
	
#if REPORT_GPU_STATS
	IOMemoryDescriptor	*memDescriptor;
	IOMemoryMap			*memoryMap;
#endif
	
	IOReturn result		= kIOReturnSuccess;
	
	virtual IOReturn loopTimerEvent(void);
	
	void reportMSRs(UInt8 aCPUModel);
	
	bool loopLock = false;		// TODO: Use Info.plist
	bool dumpCStates = true;	// TODO: Use Info.plist
	bool igpuEnabled = true;	// TODO: Use Info.plist
	
	UInt16 Interval	= 50;
	
	UInt64	gCoreMultipliers		= 0ULL;
	UInt64	gTriggeredPStates		= 0ULL;
	
	UInt64	gIGPUMultipliers		= 0ULL;
	UInt64	gTriggeredIGPUPStates	= 0ULL;
	
public:
	virtual IOService *	probe(IOService * provider, SInt32 * score);
	virtual bool start(IOService * provider);
	virtual void stop(IOService * provider);
	virtual void free(void);
	
	UInt8	gMinRatio	= 0;
	UInt8	gClockRatio	= 0;
	UInt8	gMaxRatio	= 0;
};

OSDefineMetaClassAndStructors(AppleIntelCPUPowerManagementInfo, IOService)

UInt8	gCPUModel	= 0x2A;
UInt8	gCoreStates	= 0ULL;

#if REPORT_C_STATES
bool	gCheckC3	= true;
bool	gCheckC6	= true;
bool	gCheckC7	= false;

UInt32	gC3Cores	= 0;
UInt32	gC6Cores	= 0;
UInt32	gC7Cores	= 0;

UInt32	gTriggeredC3Cores	= 0;
UInt32	gTriggeredC6Cores	= 0;
UInt32	gTriggeredC7Cores	= 0;
#endif

UInt64	gCoreMultipliers = 0ULL;

#if REPORT_GPU_STATS
UInt8	* gMchbar	= NULL;
#endif