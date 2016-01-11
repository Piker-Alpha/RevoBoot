/*
 *
 * Name			: smbiosXtract
 * Version		: 0.0.1
 * Type			: Command line tool
 * Copyright	: Pike R. Alpha (c) 2016
 * Description	: SMBIOS extractor for use with: dmidecode --from-file SMBIOS.bin
 *
 * Usage		: sudo ./smbiosXtract
 *
 * Compile with	: cc smbiosXtract.c -o smbiosXtract -Wall -framework IOKit -framework CoreFoundation
 *
 * Updates		: None so far.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>

#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>

#include "../smbios.h"

//==============================================================================

uint8_t checksum8(const uint8_t *cp, uint8_t length)
{
	uint8_t sum = 0;
	uint8_t i = 0;
	
	for (; i < length; i++)
	{
		sum += *cp++;
	}
	
	return sum;
}

//==============================================================================

int main(void)
{
	char dirspec[128];
	int filedesc = 0;

	mach_port_t		masterPort;
    io_service_t	service = MACH_PORT_NULL;
	CFDataRef		dataRef;

	UInt8 entryPointLength = 0;
	UInt16 tableLength = 0;
	UInt32 bytesWritten = 0;

	IOMasterPort(MACH_PORT_NULL, &masterPort);

	//==================================================================================

	service = IOServiceGetMatchingService(masterPort, IOServiceMatching("AppleSMBIOS"));

    if (service)
	{
		dataRef = (CFDataRef) IORegistryEntryCreateCFProperty(service, CFSTR("SMBIOS-EPS"), kCFAllocatorDefault, kNilOptions);

		if (dataRef)
		{
			struct SMBEntryPoint * eps = (struct SMBEntryPoint *) CFDataGetBytePtr(dataRef);
			entryPointLength = eps->entryPointLength;
			tableLength = eps->dmi.tableLength;

			// Point table address to data.
			eps->dmi.tableAddress = 0x20;

			// Zero out checksums.
			eps->checksum = 0;
			eps->dmi.checksum = 0;

			// Recalculate checksums.
			eps->dmi.checksum = (256 - checksum8(CFDataGetBytePtr(dataRef) + 0x10, 0x0f));
			eps->checksum = (256 - checksum8(CFDataGetBytePtr(dataRef), 0x1f));

			sprintf (dirspec, "SMBIOS.bin");
			filedesc = open(dirspec, O_WRONLY|O_CREAT|O_TRUNC, 0644);
			
			if (filedesc == -1)
			{
				printf("Error: Unable to open SMBIOS.bin!\n");
				close (filedesc);
				CFRelease(dataRef);
			}
			else
			{
				bytesWritten = write(filedesc, (char *)CFDataGetBytePtr(dataRef), (entryPointLength + 1));
				close (filedesc);
				CFRelease(dataRef);
				dataRef = (CFDataRef) IORegistryEntryCreateCFProperty(service, CFSTR("SMBIOS"), kCFAllocatorDefault, kNilOptions);

				if (dataRef)
				{
					filedesc = open(dirspec, O_WRONLY|O_APPEND, 0644);
					bytesWritten += write(filedesc, (char *)CFDataGetBytePtr(dataRef), tableLength);
					printf("%d bytes written to SMBIOS.bin for use with: dmidecode --from-dump SMBIOS.bin\n", bytesWritten);
					close (filedesc);
					CFRelease(dataRef);
				}
			}
		}

		IOObjectRelease(service);
    }

	exit(0);
}
