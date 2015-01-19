/*
 * Copyright 2014 by Pike R. Alpha. All rights reserved.
 */

#define BIT31								0x80000000

#define PCI_BUS_NUMBER						0x0
#define XHCI_DEVICE_NUMBER					0x14
#define XHCI_FUNCTION_NUMBER				0x0
#define XHCI_ADDRESS						(BIT31 | (PCI_BUS_NUMBER << 16) | (XHCI_DEVICE_NUMBER << 11) | (XHCI_FUNCTION_NUMBER << 8))

#define PCI_ADDR_REG						0xcf8
#define PCI_DATA_REG						0xcfc

#define XHCI_BASE_ADDRESS_REGISTER_0		0x10
#define XHCI_BASE_ADDRESS_REGISTER_1		0x14

#define XHCI_BIOS_OWNED						0x1
#define XHCI_OS_OWNED						0x100

#define XHCI_LEGACY_CONTROL_OFFSET			0x4
#define XHCI_HCC_CAPABILITY_PARAMS_OFFSET	0x10

#define XHCI_LEGACY_DISABLE_SMI				0xE1FE0
#define XHCI_LEGACY_SMI_EVENTS				0xE0000000

#define	USB_LEGACY_SUPPORT_ID				0x1

/*------------------------------------------------------------------------------
 * Format of xHCI Extended Capability Pointer Register (see table 146).
 *------------------------------------------------------------------------------
 * Bit 31:16	Capability Specific – RO. The definition and attributes of these
 *				bits depends on the specific capability.
 *------------------------------------------------------------------------------
 * Bit 15:8		Next xHCI Extended Capability Pointer – RO. This field points to
 *				the xHCI MMIO space offset of the next xHCI extended capability
 *				pointer. A value of 00h indicates the end of the extended 
 *				capability list. A non-zero value in this register indicates a 
 *				relative offset, in Dwords, from this Dword to the beginning of 
 *				the next extended capability. For example, assuming an effective 
 *				address of this data structure is 350h and assuming a pointer 
 *				value of 068h, we can calculate the following effective address:
 *				350h + (068h << 2) -> 350h + 1A0h -> 4F0h
 *------------------------------------------------------------------------------
 * Bit 7:0		Capability ID – RO. This field identifies the xHCI Extended
 *				capability. Refer to table 146 in specification for a list of
 *				the valid xHCI extended capabilities.
 *------------------------------------------------------------------------------*/

typedef struct xHCI_ExtendedCapabilityPointer
{
	// USBLEGSUP - USB Legacy Support Capability Register
	uint8_t		ID;
	uint8_t		Next;
	uint16_t	Capabilities;
	// USBLEGCTLSTS - USB Legacy Support Control and Status Register
	uint32_t	Value;
} XHCI_EXTENDED_CAPABILITY_POINTER;


//==============================================================================

void disableLegacyXHCI(void)
{
	uint8_t timeout = 60;

	// Get 32-bit xHCI MMIO address (no 64-bit support for legacy boot loaders).
	outl(PCI_ADDR_REG, (XHCI_ADDRESS + XHCI_BASE_ADDRESS_REGISTER_0));
	uint32_t addressBAR0 = inl(PCI_DATA_REG); // Example: 0xd3c00004

	// Mask the lower bits to fix the MMIO BAR address (need 4KB page-alignment).
	addressBAR0 &= 0xFFFFFFF0; // Example: 0xd3c00004 ->  0xd3c00000

	// Read Host Controller Capability Parameters.
	uint32_t hccparams = *(uint32_t const volatile*) (addressBAR0 + XHCI_HCC_CAPABILITY_PARAMS_OFFSET);
	uint32_t extendedCapabilitiesPointer = (hccparams >> 16); // Example: 0x2000

	_BOOT_DEBUG_DUMP("hccparams: 0x%x\n", hccparams); //  Example: 0x200077c1
	_BOOT_DEBUG_DUMP("extendedCapabilitiesPointer: 0x%x\n", extendedCapabilitiesPointer);

	// Shift value (basically multiply it by 4).
	extendedCapabilitiesPointer = (extendedCapabilitiesPointer << 2); //  Example: (0x2000 << 2) = 0x8000
	XHCI_EXTENDED_CAPABILITY_POINTER * xHCI_ECP = (XHCI_EXTENDED_CAPABILITY_POINTER *) (addressBAR0 + extendedCapabilitiesPointer);

	while (xHCI_ECP->ID) // Main loop.
	{
		/*------------------------------------------------------------------------------
		 * Format of USB Legacy Support Extended Capabilities (see table 146).
		 * Note: Be aware that the bits here are shifted to the right (data >> 16).
		 *------------------------------------------------------------------------------
		 * Bit 15:9		Reserved.
		 *------------------------------------------------------------------------------
		 * Bit 8		HC OS Owned Semaphore – RW. Default = ‘0’. System software sets
		 *				this bit to request ownership of the xHCI. Ownership is obtained
		 *				when this bit reads as ‘1’ and the HC BIOS Owned Semaphore bit
		 *				reads as ‘0’.
		 *------------------------------------------------------------------------------
		 * Bit 7:1		Reserved.
		 *------------------------------------------------------------------------------
		 * Bit 0		HC BIOS Owned Semaphore – RW. Default = ‘0’. The BIOS sets this
		 *				bit to establish ownership of the xHC. System BIOS will set this
		 *				bit to a ‘0’ in response to a request for ownership of the xHCI
		 *				by system software.
		 *------------------------------------------------------------------------------*/

		_BOOT_DEBUG_DUMP("Capabilities: 0x%04x\n", xHCI_ECP->Capabilities);	// 0x0200, 0x0300, 0x0001, 0x0000, 0x0001
		_BOOT_DEBUG_DUMP("Next........: 0x%02x\n", xHCI_ECP->Next);			// 0x08,   0x08,   0x0c,   0xff,   0x00
		_BOOT_DEBUG_DUMP("ID..........: 0x%02x\n", xHCI_ECP->ID);			// 0x02,   0x02,   0xc1,   0xc0,   0x01

		if (xHCI_ECP->ID == USB_LEGACY_SUPPORT_ID)
		{
			_BOOT_DEBUG_DUMP ("XHCI legacy mode enabled in BIOS!\n");

			if (xHCI_ECP->Capabilities & XHCI_BIOS_OWNED)
			{
				_BOOT_DEBUG_DUMP ("XHCI is owned by BIOS!\n");

				while (timeout--)
				{
					// Signal the BIOS that the Bootloader/OS wants control.
					xHCI_ECP->Capabilities |= XHCI_OS_OWNED;
					delay(1);

					if ((xHCI_ECP->Capabilities & (XHCI_OS_OWNED | XHCI_BIOS_OWNED)) == XHCI_OS_OWNED) // Done?
					{
						_BOOT_DEBUG_DUMP("XHCI now owned by Bootloader/OS (attempts %d)!\n", (60 - timeout));
						break;
					}
				}
			}
			/*------------------------------------------------------------------------------
			 * Bit 31		SMI on BAR – RW1C. Default = ‘0’. This bit is set to ‘1’ whenever 
			 *				the Base Address Register (BAR) is written.
			 *------------------------------------------------------------------------------
			 * Bit 30		SMI on PCI Command – RW1C. Default = ‘0’. This bit is set to ‘1’
			 *				whenever the PCI Command Register is written.
			 *------------------------------------------------------------------------------
			 * Bit 29		SMI on OS Ownership Change – RW1C. Default = ‘0’. This bit is set
			 *				to ‘1’ whenever the HC OS Owned Semaphore bit in the USBLEGSUP 
			 *				register transitions from ‘1’ to a ‘0’ or ‘0’ to a ‘1’.
			 *------------------------------------------------------------------------------
			 * Bit 28:21	Reserved.
			 *------------------------------------------------------------------------------
			 * Bit 20		SMI on Host System Error – RO. Default = ‘0’. Shadow bit of Host 
			 *				System Error (HSE) bit in the USBSTS register refer to Section 
			 *				5.4.2 for definition and effects of the events associated with 
			 *				this bit being set to ‘1’. To clear this bit to a ‘0’, system 
			 *				software shall write a ‘1’ to the Host System Error (HSE) bit in 
			 *				the USBSTS register.
			 *------------------------------------------------------------------------------
			 * Bit 19:17	Reserved.
			 *------------------------------------------------------------------------------
			 * Bit 16		SMI on Event Interrupt – RO. Default = ‘0’. Shadow bit of Event 
			 *				Interrupt (EINT) bit in the USBSTS register. Refer to Section 
			 *				5.4.2 for definition. This bit follows the state the Event 
			 *				Interrupt (EINT) bit in the USBSTS register, e.g. it automatically 
			 *				clears when EINT clears or set when EINT is set.
			 *------------------------------------------------------------------------------
			 * Bit 15		SMI on BAR Enable – RW. Default = ‘0’. When this bit is ‘1’ and 
			 *				SMI on BAR is ‘1’, then the host controller will issue an SMI.
			 *------------------------------------------------------------------------------
			 * Bit 14		SMI on PCI Command Enable – RW. Default = ‘0’. When this bit is 
			 *				‘1’ and SMI on PCI Command is ‘1’, then the host controller will 
			 *				issue an SMI.
			 *------------------------------------------------------------------------------
			 * Bit 13		SMI on OS Ownership Enable – RW. Default = ‘0’. When this bit is 
			 *				a ‘1’ AND the OS Ownership Change bit is ‘1’, the host controller 
			 *				will issue an SMI.
			 *------------------------------------------------------------------------------
			 * Bit 12:5		Reserved.
			 *------------------------------------------------------------------------------
			 * Bit 4		SMI on Host System Error Enable – RW. Default = ‘0’. When this 
			 *				bit is a ‘1’, and the SMI on Host System Error bit (below) in 
			 *				this register is a ‘1’, the host controller will issue an SMI 
			 *				immediately.
			 *------------------------------------------------------------------------------
			 * Bit 3:1		Reserved.
			 *------------------------------------------------------------------------------
			 * Bit 0		USB SMI Enable – RW. Default = ‘0’. When this bit is a ‘1’, and
			 *				the SMI on Event Interrupt bit (below) in this register is a ‘1’,
			 *				the host controller will issue an SMI immediately.
			 *------------------------------------------------------------------------------*/

			_BOOT_DEBUG_DUMP("Before fix: 0x%x\n", xHCI_ECP->Value); // 0x00002000 (bit 13)

			xHCI_ECP->Value &= XHCI_LEGACY_DISABLE_SMI;
			xHCI_ECP->Value |= XHCI_LEGACY_SMI_EVENTS;

			_BOOT_DEBUG_DUMP("After fix: 0x%x\n", xHCI_ECP->Value);  // 0xe0000000 (bit 31:29)
			break;
		}
		else
		{
			// Get next xHCI Extended Capabilities Structure.
			extendedCapabilitiesPointer += (xHCI_ECP->Next << 2);
			xHCI_ECP = (XHCI_EXTENDED_CAPABILITY_POINTER *) (addressBAR0 + extendedCapabilitiesPointer);
		}
	};
	
	_BOOT_DEBUG_SLEEP(5);
}
