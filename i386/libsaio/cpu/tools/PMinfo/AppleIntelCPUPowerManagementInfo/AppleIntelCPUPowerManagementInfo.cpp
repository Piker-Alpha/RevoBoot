/*
 * Copyright (c) 2012-2013 Pike R. Alpha. All rights reserved.
 *
 * Original idea and initial development of MSRDumper.kext (c) 2011 by RevoGirl.
 *
 * Thanks to George for his help and continuation of Sam's work, but it is
 * time for us to push the envelope and add some really interesting stuff.
 *
 */

#include "AppleIntelCPUPowerManagementInfo.h"


//==============================================================================

void AppleIntelCPUPowerManagementInfo::reportMSRs(void)
{
	IOLog("MSR_CORE_THREAD_COUNT......(0x35)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CORE_THREAD_COUNT));

	IOLog("MSR_PLATFORM_INFO..........(0xCE)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PLATFORM_INFO));

	IOLog("MSR_PMG_CST_CONFIG_CONTROL.(0xE2)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PMG_CST_CONFIG_CONTROL));
	IOLog("MSR_PMG_IO_CAPTURE_BASE....(0xE4)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PMG_IO_CAPTURE_BASE));
	IOLog("IA32_MPERF.................(0xE7)  : 0x%llX\n", (unsigned long long)rdmsr64(IA32_MPERF));
	IOLog("IA32_APERF.................(0xE8)  : 0x%llX\n", (unsigned long long)rdmsr64(IA32_APERF));

	IOLog("MSR_FLEX_RATIO.............(0x194) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_FLEX_RATIO));
	IOLog("MSR_IA32_PERF_STATUS.......(0x198) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_IA32_PERF_STATUS));
	IOLog("MSR_IA32_PERF_CONTROL......(0x199) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_IA32_PERF_CONTROL));
	IOLog("IA32_CLOCK_MODULATION......(0x19A) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_CLOCK_MODULATION));
	IOLog("IA32_THERM_STATUS..........(0x19C) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_THERM_STATUS));

	IOLog("IA32_MISC_ENABLES..........(0x1A0) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_MISC_ENABLES));
	IOLog("MSR_MISC_PWR_MGMT..........(0x1AA) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_MISC_PWR_MGMT));
	IOLog("MSR_TURBO_RATIO_LIMIT......(0x1AD) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_TURBO_RATIO_LIMIT));

	IOLog("IA32_ENERGY_PERF_BIAS......(0x1B0) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_ENERGY_PERF_BIAS));

	IOLog("MSR_POWER_CTL..............(0x1FC) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_POWER_CTL));

	IOLog("MSR_RAPL_POWER_UNIT........(0x606) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_RAPL_POWER_UNIT));
	IOLog("MSR_PKG_POWER_LIMIT........(0x610) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_POWER_LIMIT));
	IOLog("MSR_PKG_ENERGY_STATUS......(0x611) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_ENERGY_STATUS));

	IOLog("MSR_PKGC3_IRTL.............(0x60a) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKGC3_IRTL));
	IOLog("MSR_PKGC6_IRTL.............(0x60b) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKGC6_IRTL));
	IOLog("MSR_PKGC7_IRTL.............(0x60c) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKGC7_IRTL));

	IOLog("MSR_PP0_CURRENT_CONFIG.....(0x601) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_CURRENT_CONFIG));
	IOLog("MSR_PP0_POWER_LIMIT........(0x638) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_POWER_LIMIT));
	IOLog("MSR_PP0_ENERGY_STATUS......(0x639) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_ENERGY_STATUS));
	IOLog("MSR_PP0_POLICY.............(0x63a) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_POLICY));

	/* IOLog("MSR_PP1_CURRENT_CONFIG.....(0x602) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_CURRENT_CONFIG));
	IOLog("MSR_PP1_POWER_LIMIT........(0x640) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_POWER_LIMIT));
	IOLog("MSR_PP1_ENERGY_STATUS......(0x641) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_ENERGY_STATUS));
	IOLog("MSR_PP1_POLICY.............(0x642) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_POLICY)); */

	IOLog("MSR_CONFIG_TDP_NOMINAL.....(0x648) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_NOMINAL));
	IOLog("MSR_CONFIG_TDP_LEVEL1......(0x649) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_LEVEL1));
	IOLog("MSR_CONFIG_TDP_LEVEL2......(0x64a) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_LEVEL2));
	IOLog("MSR_CONFIG_TDP_CONTROL.....(0x64b) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_CONTROL));
	IOLog("MSR_TURBO_ACTIVATION_RATIO.(0x64c) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_TURBO_ACTIVATION_RATIO));

	IOLog("MSR_PKG_C2_RESIDENCY.......(0x60d) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C2_RESIDENCY));
	IOLog("MSR_PKG_C3_RESIDENCY.......(0x3f8) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C3_RESIDENCY));
	IOLog("MSR_PKG_C6_RESIDENCY.......(0x3f9) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C6_RESIDENCY));
	IOLog("MSR_PKG_C7_RESIDENCY.......(0x3fa) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
	
	if (gCPUModel == CPU_MODEL_HASWELL_ULT)
	{
		IOLog("MSR_PKG_C8_RESIDENCY.......(0x630) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
		IOLog("MSR_PKG_C9_RESIDENCY.......(0x631) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
		IOLog("MSR_PKG_C10_RESIDENCY......(0x632) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
		
		IOLog("MSR_PKG_C8_LATENCY.........(0x633) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
		IOLog("MSR_PKG_C9_LATENCY.........(0x634) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
		IOLog("MSR_PKG_C10_LATENCY........(0x635) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_C7_RESIDENCY));
	}
}

//==============================================================================

inline void getCStates(void *arg)
{
	UInt8 logicalCoreNumber = cpu_number();

	if ((gCoreStates & logicalCoreNumber) == 0)
	{
		gCoreStates |= (1ULL << logicalCoreNumber);
		IOLog("Core (logical): %d\n", logicalCoreNumber);
		IOLog("MSR_CORE_C3_RESIDENCY......(0x3fc) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CORE_C3_RESIDENCY));
		IOLog("MSR_CORE_C6_RESIDENCY......(0x3fd) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CORE_C6_RESIDENCY));

		if ((gCPUModel == CPU_MODEL_SB_CORE) || (gCPUModel == CPU_MODEL_SB_JAKETOWN))
		{
			IOLog("MSR_CORE_C7_RESIDENCY......(0x3fe) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CORE_C7_RESIDENCY));
		}
	}
}

//==============================================================================

IOReturn AppleIntelCPUPowerManagementInfo::loopTimerEvent(void)
{
	UInt8 currentMultiplier = (rdmsr64(MSR_IA32_PERF_STS) >> 8);
	gCoreMultipliers |= (1ULL << currentMultiplier);

#if REPORT_GPU_STATS
	UInt8 currentIgpuMultiplier = 0;

	if (igpuEnabled)
	{
		currentIgpuMultiplier = (UInt8)gMchbar[1];
		gIGPUMultipliers |= (1ULL << currentIgpuMultiplier);
	}
#endif

	timerEventSource->setTimeoutTicks(Interval);

	if (loopLock)
	{
		return kIOReturnTimeout;
	}
	
	loopLock = true;

	if (dumpCStates)
	{
		UInt32 magic = 0;
		IOSimpleLockLock(simpleLock);
		mp_rendezvous_no_intrs(getCStates, (void *)&magic);
		IOSimpleLockUnlock(simpleLock);
	}

#if REPORT_GPU_STATS
	if ((gCoreMultipliers != gTriggeredPStates) || (gIGPUMultipliers != gTriggeredIGPUPStates))
#else
	if (gCoreMultipliers != gTriggeredPStates)
#endif
	{
		int currentBit = 0;
		UInt64 value = 0ULL;

		gTriggeredPStates = gCoreMultipliers;
		IOLog("AICPUPMI: CPU P-States [ ");

		for (currentBit = gMinRatio; currentBit <= gMaxRatio; currentBit++)
		{
			value = (1ULL << currentBit);
			
			if ((gTriggeredPStates & value) == value)
			{
				if (currentBit == currentMultiplier)
				{
					IOLog("(%d) ", currentBit);
				}
				else
				{
					IOLog("%d ", currentBit);
				}
			}
		}

#if REPORT_GPU_STATS
		if (igpuEnabled)
		{
			gTriggeredIGPUPStates = gIGPUMultipliers;
			IOLog("] iGPU P-States [ ");
			
			for (currentBit = 1; currentBit <= 32; currentBit++)
			{
				value = (1ULL << currentBit);
				
				if ((gTriggeredIGPUPStates & value) == value)
				{
					if (currentBit == currentIgpuMultiplier)
					{
						IOLog("(%d) ", currentBit);
					}
					else
					{
						IOLog("%d ", currentBit);
					}
				}
			}
		}
#endif
		IOLog("]\n");
	}

	loopLock = false;

	return kIOReturnSuccess;
}

//==============================================================================

IOService* AppleIntelCPUPowerManagementInfo::probe(IOService *provider, SInt32 *score)
{
	IOService *ret = super::probe(provider, score);
	
	if (ret != this)
	{
		return 0;
	}
	
	return ret;
}

//==============================================================================

bool AppleIntelCPUPowerManagementInfo::start(IOService *provider)
{
	if (IOService::start(provider))
	{
		simpleLock = IOSimpleLockAlloc();

		if (simpleLock)
		{
			timerEventSource = IOTimerEventSource::timerEventSource(this, OSMemberFunctionCast(IOTimerEventSource::Action, this, &AppleIntelCPUPowerManagementInfo::loopTimerEvent));
			workLoop = getWorkLoop();

			if (timerEventSource && workLoop && (kIOReturnSuccess == workLoop->addEventSource(timerEventSource)))
			{
				this->registerService(0);

				UInt64  msr = rdmsr64(MSR_IA32_PERF_STS);
				gCoreMultipliers |= (1ULL << (msr >> 8));

				wrmsr64(IA32_ENERGY_PERF_BIAS, 15);
				
				uint32_t cpuid_reg[4];
				do_cpuid(0x00000001, cpuid_reg);

				gCPUModel = bitfield32(cpuid_reg[eax], 7,  4) + (bitfield32(cpuid_reg[eax], 19, 16) << 4);

				// MWAIT information
				do_cpuid(0x00000005, cpuid_reg);
				uint32_t supportedMwaitCStates = bitfield32(cpuid_reg[edx], 31,  0);

				IOLog("AICPUPMI: MWAIT C-States     : %d\n", supportedMwaitCStates);

#if REPORT_MSRS
				reportMSRs();
#endif
				msr = rdmsr64(MSR_PLATFORM_INFO);
				gMinRatio = (UInt8)((msr >> 40) & 0xff);
				IOLog("AICPUPMI: Low Frequency Mode : %d00 MHz\n", gMinRatio);
 
				gClockRatio = (UInt8)((msr >> 8) & 0xff);
				IOLog("AICPUPMI: Clock Speed        : %d00 MHz\n", gClockRatio);

				if (!((rdmsr64(IA32_MISC_ENABLES) >> 32) & 0x40))	// Turbo Mode Enabled?
				{
					msr = rdmsr64(MSR_TURBO_RATIO_LIMIT);
					gMaxRatio = (UInt8)(msr & 0xff);
					IOLog("AICPUPMI: Max Turbo Frequency: %d00 MHz\n", gMaxRatio);
				}
				else
				{
					gMaxRatio = gClockRatio;
					IOLog("AICPUPMI: Max Frequency      : %d00 MHz\n", gMaxRatio);
				}

#if REPORT_GPU_STATS
				if ((READ_PCI8_NB(DEVEN) & DEVEN_D2EN_MASK))
				{
					IOPhysicalAddress address = (IOPhysicalAddress)(0xFED10000 + 0x5948);
					memDescriptor = IOMemoryDescriptor::withPhysicalAddress(address, 0x53, kIODirectionInOut);
				
					if (memDescriptor != NULL)
					{
						if ((result = memDescriptor->prepare()) == kIOReturnSuccess)
						{
							memoryMap = memDescriptor->map();
						
							if (memoryMap != NULL)
							{
								igpuEnabled = true; // IGPU Enabled and Visible
								gMchbar = (UInt8 *)memoryMap->getVirtualAddress();
								
								// Current RP-state, when the graphics engine is in RC6, this reflects the last used ratio.
								IOLog("AICPUPMI: IGPU Current Freq..: %4d MHz\n", IGPU_RATIO_TO_FREQUENCY((UInt8)gMchbar[0x01])); // RP_STATE_RAT IO
								// Maximum RPN base frequency capability for the Integrated GFX Engine (GT).
								IOLog("AICPUPMI: IGPU Max Frequency.: %4d MHz\n", IGPU_RATIO_TO_FREQUENCY((UInt8)gMchbar[0x52])); // RPN_CAP
								// Maximum RP1 base frequency capability for the Integrated GFX Engine (GT).
								IOLog("AICPUPMI: IGPU Max Frequency.: %4d MHz\n", IGPU_RATIO_TO_FREQUENCY((UInt8)gMchbar[0x51])); // RP1_CAP
								// Maximum RP0 base frequency capability for the Integrated GFX Engine (GT).
								IOLog("AICPUPMI: IGPU Max Turbo Freq: %4d MHz\n", IGPU_RATIO_TO_FREQUENCY((UInt8)gMchbar[0x50])); // RP0_CAP
								// Maximum base frequency limit for the Integrated GFX Engine (GT) allowed during run-time.
								IOLog("AICPUPMI: IGPU Maximum limit.: %4d MHz\n", IGPU_RATIO_TO_FREQUENCY((UInt8)gMchbar[0x4C])); // RPSTT_LIM
								//
								// Example-1: 17 (multiplier) * 50 (frequency in MHz) =  850 MHz
								// Example-2: 22 (multiplier) * 50 (frequency in MHz) = 1100 MHz
								// 6 P-States: 850, 900, 950, 1000, 1050 and 1100 MHz
								//
							}
							else
							{
								IOLog("AICPUPMI: Error: memoryMap == NULL\n");
							}
						}
						else
						{
							IOLog("AICPUPMI: Error: memDescriptor->prepare() failed!\n");
						}
					}
					else
					{
						IOLog("AICPUPMI: Error: memDescriptor == NULL\n");
					}
				}
#endif
				timerEventSource->setTimeoutMS(1000);

				return true;
			}
		}
	}

	return false;
}

//==============================================================================

void AppleIntelCPUPowerManagementInfo::stop(IOService *provider)
{
	if (simpleLock)
	{
		IOSimpleLockFree(simpleLock);
	}

	if (timerEventSource)
	{
		if (workLoop)
		{
			timerEventSource->cancelTimeout();
			workLoop->removeEventSource(timerEventSource);
		}

		timerEventSource->release();
		timerEventSource = NULL;
	}

	super::stop(provider);
}

//==============================================================================

void AppleIntelCPUPowerManagementInfo::free()
{
#if REPORT_GPU_STATS
	if (igpuEnabled)
	{
		if (memoryMap)
		{
			memoryMap->release();
			memoryMap = NULL;
		}

		if (memDescriptor)
		{
			memDescriptor->release();
			memDescriptor = NULL;
		}
	}
#endif

	super::free();
}
