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

extern "C" void mp_rendezvous_no_intrs(void (*action_func)(void *), void * arg);
extern "C" int cpu_number(void);

class AppleIntelCPUPowerManagementInfo : public IOService
{
	OSDeclareDefaultStructors (AppleIntelCPUPowerManagementInfo);

private:
	IOSimpleLock		*simpleLock;
	IOWorkLoop			*workLoop;
	IOTimerEventSource	*timerEventSource;

	virtual IOReturn loopTimerEvent(void);

	void reportMSRs(uint8_t aModel);

	bool loopLock = false;

	UInt16 Interval	= 50;

public:
	virtual IOService *	probe(IOService * provider, SInt32 * score);
	virtual bool start(IOService * provider);
	virtual void stop(IOService * provider);
	virtual void free(void);
};

OSDefineMetaClassAndStructors(AppleIntelCPUPowerManagementInfo, IOService)

UInt64	gCoreMultipliers;
UInt64	gTriggeredPStates;

UInt8	gMinRatio	= 0;
UInt8	gClockRatio	= 0;
UInt8	gMaxRatio	= 0;

UInt8	gCPUModel	= 0x2A;