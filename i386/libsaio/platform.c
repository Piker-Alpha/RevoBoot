/*
 *
 * platform.c
 *
 * Updates:
 *
 *			- STATIC_SMBIOS_MODEL_ID renamed to SMB_PRODUCT_NAME (PikerAlpha, October 2012).
 *
 */

#include "bootstruct.h"
#include "cpu/cpuid.h"

PlatformInfo_t	gPlatform;	// Global platform structure with everything we need.


#if MUST_ENABLE_A20
//==============================================================================
// Private function. Called from enableA20 only.

static inline void flushKeyboardInputBuffer()
{
	#define PORT_B		0x64	// port B
	#define KB_INFULL	0x2		// input buffer full.

	unsigned char ret;

	// Apparently all flags on means that they're invalid and that the code
	// should stop trying to check them because they'll never change.
	do
	{
		ret = inb(PORT_B);
	} while ((ret != 0xff) && (ret & KB_INFULL));
}


//==============================================================================
// Enable A20 gate to be able to access memory above 1MB.

void enableA20()
{
	// keyboard controller (8042) I/O port addresses.
	#define PORT_A		0x60	// port A
	#define PORT_B		0x64	// port B
	
	// keyboard controller command.
	#define CMD_WOUT	0xd1	// Write controller's output port.
	
	// keyboard controller status flags.
	#define KB_INFULL	0x2		// input buffer full.
	#define KB_OUTFULL	0x1		// output buffer full.
	
	#define KB_A20		0x9f	// enable A20, enable output buffer full interrupt
	// enable data line disable clock line.
	
	// Make sure that the input buffer is empty.
	flushKeyboardInputBuffer();

	// Make sure that the output buffer is empty.
	if (inb(PORT_B) & KB_OUTFULL)
	{
		(void)inb(PORT_A);
	}

	// Make sure that the input buffer is empty.
	flushKeyboardInputBuffer();

	// Write output port.
	outb(PORT_B, CMD_WOUT);
	delay(100);

	// Wait until command is accepted.
	flushKeyboardInputBuffer();

	outb(PORT_A, KB_A20);
	delay(100);

	// Wait until done.
	flushKeyboardInputBuffer();
}
#endif // MUST_ENABLE_A20

//==============================================================================
// Public function. Called from initPlatform.
// Returns the CPU / platform type.

cpu_type_t getArchCPUType(void)
{
	uint32_t	cpuid_reg[4];
	do_cpuid(0, cpuid_reg);
	
	if (!memcmp(cpuid_reg + 1, "GenuntelineI", 12))
	{
		do_cpuid(0x80000001, cpuid_reg);
		
		if (cpuid_reg[3] & (1 << 29))
		{
			return CPU_TYPE_X86_64;
		}
	}
	
	return CPU_TYPE_I386;
}


#if ENABLE_HPET
//==============================================================================

void enableHPET(void)
{
	// HPTC—High Precision Timer Configuration Register (see Intel datasheet).
	unsigned int *hptc = (uint32_t *)0xFED1F404;

	// Get register value (the default value is usually 0x00000000).
	uint32_t reg_value = *hptc;

	// Select memory range 0xFED00000 – 0xFED003FF and enable it.
	*hptc = ((reg_value & ~3) | 0x80);
}
#endif // ENABLE_HPET


//==============================================================================
// Public function. Called from boot/common_boot only.

void initPlatform(int biosDevice)
{
	memset(&gPlatform, 0, sizeof(gPlatform));

	// Copied from cpu/dynamic_data.h to make printf work this early on.
#if DEBUG_CPU || DEBUG_PLATFORM
	extern void setVideoMode(int mode);
	setVideoMode(0); // Switch to VGA_TEXT_MODE
#endif

#if ENABLE_HPET
	enableHPET();
#endif

	gPlatform.RevoBootVersionInfo = strdup(REVOBOOT_VERSION_INFO);	// Example: "RevoBoot v1.0.04"

	_PLATFORM_DEBUG_DUMP("Booting with: %s\n", gPlatform.RevoBootVersionInfo);

#if AUTOMATIC_SSDT_PR_CREATION || DEBUG_TURBO_RATIOS
	uint8_t cpu = 0;
	uint8_t numberOfCores = STATIC_CPU_NumCores;

	// Zero out CPU core ratio limits.
	for (; cpu < numberOfCores; cpu++)
	{
		gPlatform.CPU.CoreTurboRatio[cpu] = 0; // Get updated later on in: i386/libsaio/Intel/cpu.c
	}
#endif

	// Jeroen: Initialized in cpu.c and used in ssdt_pr_generator.h
	gPlatform.CPU.NumberOfTurboRatios = 0;

	initCPUStruct();

	/*
	 * DHP: Booting with arch=i386 <i>and</i> setting this to CPU_TYPE_I386
	 * and setting the EFI_64_BIT directive in private_data to 0 allowed me 
	 * to boot in EFI32 mode. Even with my 64 bit configuration. Pretty sweet.
	 *
	 * Note to self: Get rid of gArchCPUType (global alarm) fast.
	 */

	gPlatform.ArchCPUType			= gArchCPUType = getArchCPUType();

	gPlatform.AddressWidth			= (gPlatform.ArchCPUType == CPU_TYPE_X86_64) ? 8 : 4;

	gPlatform.ACPI.Guid				= (EFI_GUID) EFI_ACPI_20_TABLE_GUID;

	gPlatform.SMBIOS.Guid			= (EFI_GUID) EFI_SMBIOS_TABLE_GUID;

#if INCLUDE_MPS_TABLE
	gPlatform.MPS.Guid				= (EFI_GUID) EFI_MPS_TABLE_GUID;
#endif // INCLUDE_MP_TABLE

	// Used in boot.c to verify the checksum (adler32) of pre-linked kernels.
	gPlatform.ModelID				= strdup(SMB_PRODUCT_NAME);

#if LOAD_MODEL_SPECIFIC_STATIC_DATA
	// Used in RevoBoot/i386/libsaio/ACPI/patcher.h, RevoBoot/i386/libsaio/efi.c
	// and RevoBoot/i386/libsaio/SMBIOS/static_data.h
	gPlatform.CommaLessModelID		= removeChar(strdup(gPlatform.ModelID), ',');
#endif

	// Determine system type based on product name. Used in
	// acpi/patcher.h to update FADT->Preferred_PM_Profile
	gPlatform.Type					= (strncmp(gPlatform.ModelID, "MacBook", 7) == 0) ? 2 : 1;

	// Are we supposted to have a Mobile CPU?
	if (gPlatform.Type == 2 && gPlatform.CPU.Mobile == false)
	{
		// Yes (based on the model identifier) but we either failed  
		// to detect a Mobile CPU, or we are using static CPU data.
		gPlatform.CPU.Mobile		= true;	// Will be initialized in cpu/cpu_dynamic.h (used in smbios/dynamic_data.h)
	}

#if (MAKE_TARGET_OS == LION)
	gPlatform.OSVersion				= strdup("10.7");
#elif (MAKE_TARGET_OS == MOUNTAIN_LION)
	gPlatform.OSVersion				= strdup("10.8");
#else // Snow Leopard
	gPlatform.OSVersion				= strdup("10.6");
#endif

	// _PLATFORM_DEBUG_DUMP("REVOBOOT_OS_TARGET: %d\n", REVOBOOT_OS_TARGET);

	gPlatform.OSType				= (int) MAKE_TARGET_OS;

	_PLATFORM_DEBUG_DUMP("gPlatform.OSType: %d\n", gPlatform.OSType);

	// Target OS setting from either make or config/settings.h
	// gPlatform.OSVersion[3]			= 0x34 + gPlatform.OSType;

	_PLATFORM_DEBUG_DUMP("gPlatform.OSVersion: %s\n", gPlatform.OSVersion);

	gPlatform.BIOSDevice			= (biosDevice & kBIOSDevMask);	// Device number masked with 0xFF.
	gPlatform.BootVolume			= NULL;	// Will be initialized in disk.c
	gPlatform.BootPartitionChain	= NULL;	// Will be initialized in sys.c
	gPlatform.RootVolume			= NULL;	// Will be initialized in disk.c (used in sys.c)

	gPlatform.RAM.SlotCount			= 0;	// Will be initialized further down (used in smbios/dynamic_data.h)

	gPlatform.KernelCachePath		= strdup(kKernelCachePath);	// Used in boot.c and driver.c

	_PLATFORM_DEBUG_DUMP("Kernel cache path: %s\n", gPlatform.KernelCachePath);

#if USE_STATIC_SMBIOS_DATA
	// We don't have to do anything when static SMBIOS data is used.
#elif OVERRIDE_DYNAMIC_MEMORY_DETECTION
	// Setup static STATIC_RAM_XXXX module info defined in config/settings.h
	const char * ramVendor[]		= STATIC_RAM_VENDORS;
	const char * ramPartNumber[]	= STATIC_RAM_PART_NUMBERS;
	const char * ramSerialNumber[]	= STATIC_RAM_SERIAL_NUMBERS;

#if DYNAMIC_RAM_OVERRIDE_SIZE
	int ramSize[]					= DYNAMIC_RAM_OVERRIDE_SIZES;
#endif

	int i = 0;

	// Loop through the static RAM vendors (might be different).
	for (; i < STATIC_RAM_SLOTS; i++)
	{
		gPlatform.RAM.SlotCount++;

		// We check for "N/A" so make sure you use that in config/settings.h
		if (strcmp(ramVendor[i], "N/A") != 0)
		{
			_PLATFORM_DEBUG_DUMP("Slot:%d, ", i); 

			gPlatform.RAM.MODULE[i].InUse			= true;
			gPlatform.RAM.MODULE[i].Type			= DYNAMIC_RAM_OVERRIDE_TYPE;
#if DYNAMIC_RAM_OVERRIDE_SIZE
			gPlatform.RAM.MODULE[i].Size			= ramSize[i];

			_PLATFORM_DEBUG_DUMP("Size:%d, ", gPlatform.RAM.MODULE[i].Size); 
#endif
			gPlatform.RAM.MODULE[i].Vendor			= ramVendor[i];
			gPlatform.RAM.MODULE[i].PartNumber		= ramPartNumber[i];
			gPlatform.RAM.MODULE[i].SerialNumber	= ramSerialNumber[i];

			_PLATFORM_DEBUG_DUMP("%s, %s, %s\n",
								 gPlatform.RAM.MODULE[i].Vendor,
								 gPlatform.RAM.MODULE[i].PartNumber,
								 gPlatform.RAM.MODULE[i].SerialNumber);
		}
		else
		{
			// Properly initialized for: smbios/dynamic_data.h which relies on it.
			gPlatform.RAM.MODULE[i].InUse			= false;
		}
	}

	_PLATFORM_DEBUG_DUMP("Static data for %d RAM BANKS used.\n", gPlatform.RAM.SlotCount);
#endif

	_PLATFORM_DEBUG_SLEEP(15);

	initKernelBootConfig();

#if (LOAD_MODEL_SPECIFIC_EFI_DATA)
	/*
	 * We need to call this much earlier in the boot process when static EFI data
	 * is read from: /Extra/EFI[MacModelNN.bin]. Otherwise LoadFile (load.c) fails.
	 */
	initPartitionChain();
#endif

	initEFITree();
}
