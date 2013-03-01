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

void AppleIntelCPUPowerManagementInfo::reportMSRs(uint8_t aModel)
{
	IOLog("MSR_CORE_THREAD_COUNT......(0x35)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CORE_THREAD_COUNT));

	IOLog("MSR_PLATFORM_INFO..........(0xCE)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PLATFORM_INFO));

	IOLog("MSR_PMG_CST_CONFIG_CONTROL.(0xE2)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PMG_CST_CONFIG_CONTROL));
	IOLog("MSR_PMG_IO_CAPTURE_BASE....(0xE4)  : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PMG_IO_CAPTURE_BASE));
	IOLog("IA32_MPERF.................(0xE7)  : 0x%llX\n", (unsigned long long)rdmsr64(IA32_MPERF));
	IOLog("IA32_APERF.................(0xE8)  : 0x%llX\n", (unsigned long long)rdmsr64(IA32_APERF));

	IOLog("MSR_IA32_PERF_STATUS.......(0x198) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_IA32_PERF_STATUS));
	IOLog("MSR_IA32_PERF_CONTROL......(0x199) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_IA32_PERF_CONTROL));
	IOLog("IA32_CLOCK_MODULATION......(0x19A) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_CLOCK_MODULATION));
	IOLog("IA32_THERM_STATUS..........(0x19C) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_THERM_STATUS));

	IOLog("IA32_MISC_ENABLES..........(0x1A0) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_MISC_ENABLES));
	IOLog("MSR_MISC_PWR_MGMT..........(0x1AA) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_MISC_PWR_MGMT));
	IOLog("MSR_TURBO_RATIO_LIMIT......(0x1AD) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_TURBO_RATIO_LIMIT));

	IOLog("IA32_ENERGY_PERF_BIAS......(0x1B0) : 0x%llX\n", (unsigned long long)rdmsr64(IA32_ENERGY_PERF_BIAS));

	IOLog("MSR_POWER_CTL..............(0x1FC) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_POWER_CTL));

	IOLog("rdmsr64....................(0x602) : 0x%llX\n", (unsigned long long)rdmsr64(0x602));
	IOLog("MSR_RAPL_POWER_UNIT........(0x606) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_RAPL_POWER_UNIT));
	IOLog("MSR_PKG_POWER_LIMIT........(0x610) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_POWER_LIMIT));
	IOLog("MSR_PKG_ENERGY_STATUS......(0x611) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PKG_ENERGY_STATUS));

	IOLog("MSR_PP0_POWER_LIMIT........(0x638) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_POWER_LIMIT));
	IOLog("MSR_PP0_ENERGY_STATUS......(0x639) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_ENERGY_STATUS));
	IOLog("MSR_PP0_POLICY.............(0x63a) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP0_POLICY));

	if ((aModel == CPU_MODEL_SB_CORE) || aModel == (CPU_MODEL_IB_CORE))
	{
		IOLog("MSR_PP1_POWER_LIMIT........(0x640) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_POWER_LIMIT));
		IOLog("MSR_PP1_ENERGY_STATUS......(0x641) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_ENERGY_STATUS));
		IOLog("MSR_PP1_POLICY.............(0x642) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_PP1_POLICY));
	}

	if ((aModel == CPU_MODEL_IB_CORE) || (aModel == CPU_MODEL_IB_CORE_EX))
	{
		IOLog("MSR_CONFIG_TDP_NOMINAL.....(0x648) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_NOMINAL));
		IOLog("MSR_CONFIG_TDP_LEVEL1......(0x649) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_LEVEL1));
		IOLog("MSR_CONFIG_TDP_LEVEL2......(0x64a) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_LEVEL2));
		IOLog("MSR_CONFIG_TDP_CONTROL.....(0x64b) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_CONFIG_TDP_CONTROL));
		IOLog("MSR_TURBO_ACTIVATION_RATIO.(0x64c) : 0x%llX\n", (unsigned long long)rdmsr64(MSR_TURBO_ACTIVATION_RATIO));
	}
}

//==============================================================================

IOReturn AppleIntelCPUPowerManagementInfo::getMultiplier(void)
{
	timerEventSource->setTimeoutTicks(gInterval);
	gCoreMultipliers |= (1ULL << (rdmsr64(MSR_IA32_PERF_STS) >> 8));

	if (!loopLock)
	{
		loopLock = true;

		if (gCoreMultipliers != gTriggeredPStates)
		{
			gTriggeredPStates = gCoreMultipliers;
			IOLog("AICPUPMI: P-States [ ");

			for (int currentBit = gMinRatio; currentBit <= gMaxRatio; currentBit++)
			{
				UInt64 value = (1ULL << currentBit);
				
				if ((gTriggeredPStates & value) == value)
				{
					IOLog("%d ", currentBit);
				}
			}

			IOLog("]\n");
		}

		loopLock = false;

		return kIOReturnSuccess;
	}

	return kIOReturnTimeout;
}

//==============================================================================

bool AppleIntelCPUPowerManagementInfo::start(IOService *provider)
{
	if (IOService::start(provider))
	{
		timerEventSource = IOTimerEventSource::timerEventSource(this, OSMemberFunctionCast(IOTimerEventSource::Action, this, &AppleIntelCPUPowerManagementInfo::getMultiplier));
		workLoop = getWorkLoop();

		if (timerEventSource && workLoop && (kIOReturnSuccess == workLoop->addEventSource(timerEventSource)))
		{
			this->registerService(0);

			uint32_t cpuid_reg[4];
			do_cpuid(0x00000001, cpuid_reg);

			uint8_t cpuModel = bitfield32(cpuid_reg[eax], 7,  4) + (bitfield32(cpuid_reg[eax], 19, 16) << 4);
			reportMSRs(cpuModel);

			UInt64 msr = rdmsr64(MSR_PLATFORM_INFO);
			gMinRatio = (UInt8)((msr >> 40) & 0xff);
			IOLog("Low Frequency Mode : %d00 MHz\n", gMinRatio);
 
			gClockRatio = (UInt8)((msr >> 8) & 0xff);
			IOLog("Clock Speed        : %d00 MHz\n", gClockRatio);

			if (turboEnabled)
			{
				msr = rdmsr64(MSR_TURBO_RATIO_LIMIT);
				gMaxRatio = (UInt8)(msr & 0xff);
				IOLog("Max Turbo Frequency: %d00 MHz\n", gMaxRatio);
			}
			else
			{
				gMaxRatio = gClockRatio;
				IOLog("Max Frequency      : %d00 MHz\n", gMaxRatio);
			}

			timerEventSource->enable();
			timerEventSource->setTimeoutMS(500);

			return true;
		}
	}

	return false;
}

//==============================================================================

void AppleIntelCPUPowerManagementInfo::stop(IOService *provider)
{
	if (timerEventSource)
	{
		timerEventSource->disable();
		timerEventSource->cancelTimeout();

		if (workLoop)
		{
			workLoop->removeEventSource(timerEventSource);
			workLoop->release();
			workLoop = NULL;
		}

		timerEventSource->release();
		timerEventSource = NULL;
	}

	super::stop(provider);
}

//==============================================================================

void AppleIntelCPUPowerManagementInfo::free()
{
	if (timerEventSource)
	{
		timerEventSource->cancelTimeout();
		
		if (workLoop)
		{
			workLoop->removeEventSource(timerEventSource);
			workLoop->release();
			workLoop = NULL;
		}
		
		timerEventSource->release();
		timerEventSource = NULL;
	}

	super::free();
}
