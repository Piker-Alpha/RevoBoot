/*
 * Name			: extractACPITables.c
 * Version		: 0.1
 * Type			: Command line tool
 * Copyright	: Pike R. Alpha (c) September 2014
 * Description	: ACPI table extractor.
 *
 * Usage		: ./extractACPITables	(writes table data to: /tmp/XXXX.aml)
 *
 * Compile with	: cc -O2 extractACPITables.c -o extractACPITables -Wall -framework IOKit -framework CoreFoundation
 *
 * Updates:
 *			v0.1	initial version.
 *			v0.2	renamed from acpiTableExtract.c to extractAcpiTables.c
 */

#include <stdio.h>

#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>

//==============================================================================

int main(int argc, char * argv[])
{
	char dirspec[32];
	int filedesc, status = 0;

	io_service_t	service;
	CFDictionaryRef	tableDictionary;

	//==================================================================================

	if ((service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("AppleACPIPlatformExpert"))))
	{
		if ((tableDictionary = (CFDictionaryRef) IORegistryEntryCreateCFProperty(service, CFSTR("ACPI Tables"), kCFAllocatorDefault, kNilOptions)))
		{
			CFIndex tableCount = CFDictionaryGetCount(tableDictionary);

			CFStringRef	tableNames[tableCount];
			CFDataRef	tableData[tableCount];

			CFDictionaryGetKeysAndValues(tableDictionary, (const void **)&tableNames, (const void **)&tableData);

			for (CFIndex i = 0; i < tableCount; i++)
			{
				UInt8 * buffer = (UInt8 *) CFDataGetBytePtr(tableData[i]);
				UInt32 numBytes = (UInt32) CFDataGetLength(tableData[i]);
				
				sprintf(dirspec, "/tmp/%s.aml", CFStringGetCStringPtr(tableNames[i], kCFStringEncodingMacRoman));

				if ((filedesc = open(dirspec, O_WRONLY|O_CREAT|O_TRUNC, 0644)) != -1)
				{
					write(filedesc, buffer, numBytes);
					close(filedesc);
				}
				else
				{
					status = -3;
				}
			}

			CFRelease(tableDictionary);
		}
		else
		{
			status = -2;
		}

		IOObjectRelease(service);

		exit(status);	//  0 = success.
						// -2 = tableDictionary is NULL.
						// -3 = one or more writes failed.
    }

	exit(-1); // error (service is NULL).
}
