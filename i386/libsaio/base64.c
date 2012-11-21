/*
 *
 * Name			: guidTest.c
 * Version		: 0.3
 * Type			: Command line test tool
 * Copyright	: Sam aka RevoGirl (c) 18 March 2011
 *
 * Compile with	: cc base64.c -o base64 -Wall -framework IOKit -framework CoreFoundation
 *
 * See also		: http://www.projectosx.com/forum/index.php?showtopic=2008&st=120&p=13378&#entry13378
 *
 * Updates		- guidTest.c included as RevoBootr/i386/libsaio/base64.c (PikerAlpha, November 2012)
 *				- DEBUG renamed to DEBUG_BASE64_DECODE (PikerAlpha, November 2012)
 *				- STAND_ALONE check added (PikerAlpha, November 2012)
 *				- Workaround for "___bzero" undefined error in RevoBoot (PikerAlpha, November 2012)
 *				- base64Charset moved to function decodeQuantum (PikerAlpha, November 2012)
 *
 */

#ifdef REVOBOOT_VERSION_INFO
	#define STAND_ALONE	0
#else
	#define STAND_ALONE	1
#endif

#if STAND_ALONE
	#include <IOKit/IOKitLib.h>
	#include <CoreFoundation/CoreFoundation.h>
#else
	#include "libsaio.h"
#endif

#define DEBUG_BASE64_DECODE	1

#if DEBUG_BASE64_DECODE
	int quickLookups = 0;
#endif

#define PADDINGCHAR		'='

#define TABLELEN        64


//==============================================================================

void decodeQuantum(const char *input, unsigned char *output)
{
#if DEBUG_BASE64_DECODE
	bool found = false;
#endif
	int j = 0;

	unsigned int x = 0; // We need a 32 bit wide variable for pur bit shifting.

	const char * base64Charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	for (int i = 0; i < 4; i++)
	{
#if DEBUG_BASE64_DECODE
		found = false;
#endif
		if (input[i] == PADDINGCHAR)
		{
			x = (x << 6);
#if DEBUG_BASE64_DECODE
			found = true;
#endif
		}
		else if (input[(i - 1)] == input[i]) // Same character as last one?
		{
#if DEBUG_BASE64_DECODE
			found = true;
			quickLookups++;
#endif
			x = (x << 6) + j;
		}
		else // Dig for target character.
		{
			for (j = 0; j < TABLELEN; j++)
			{
				if (base64Charset[j] == input[i])
				{
					x = (x << 6) + j;
#if DEBUG_BASE64_DECODE
					found = true;
#endif
					break;
				}
			}
		}
	}
#if DEBUG_BASE64_DECODE
	if (!found)
	{
		printf("ERROR\n");
	}
#endif

	output[2] = x;
	output[1] = (x >>= 8);
	output[0] = (x >>= 8);
}


//==============================================================================
 
int base64Decode(const char *input, unsigned char *decodedData)
{
	int i				= 0;
	int j				= 0;
	int numQuantums		= 0;
	int paddingChars	= 0;

	size_t bytes		= 0;
	size_t length		= 0;

	// These will be initialized later on
	unsigned char *buffer		= NULL;
	unsigned char *bufferStart	= NULL;
	unsigned char *lastQuantum	= NULL;

	while ((input[length] != PADDINGCHAR) && input[length])
	{
		length++;
	}

	// A maximum of two padding characters is allowed.
	if (input[length] == PADDINGCHAR)
	{
		paddingChars++;

		if (input[length + paddingChars] == PADDINGCHAR)
		{
			paddingChars++;
		}
	}

	numQuantums = ((length + paddingChars) / 4);

#if DEBUG_BASE64_DECODE
	printf("\nnumQuantums: %d\n\n", numQuantums);
#endif

	// Is there anything to decode?
	if (numQuantums)
	{
		buffer = malloc(numQuantums * 3);
		
		if (buffer)
		{
			bufferStart = buffer;
			lastQuantum = (unsigned char *)malloc(4);

			while (*input)
			{
				// Decode all but the last quantum (which may not decode to a multiple of 3 bytes).
				for (i = 0; i < (numQuantums - 1); i++)
				{
					decodeQuantum(input, buffer);
#if DEBUG_BASE64_DECODE
					printf("%2ld : %02x %02x %02x\n", (bytes / 3), *buffer++, *buffer++, *buffer++);
#else
					buffer += 3;
#endif
					input += 4;
					bytes += 3;
				}

				// The final decoding phase.
				decodeQuantum(input, lastQuantum);

				for (j = 0; j < (3 - paddingChars); j++)
				{
					buffer[j] = lastQuantum[j];
					bytes++;
				}

				input += 4;
#if DEBUG_BASE64_DECODE
				printf("%2ld : %02x %02x %02x\n", (bytes / 3), lastQuantum[0], lastQuantum[1], lastQuantum[2]);
#endif
				buffer[(numQuantums * 3)] = 0xAA;
			}
			
			free (lastQuantum);

			if ((decodedData = memcpy(decodedData, bufferStart, bytes)) != NULL)
			{
#if DEBUG_BASE64_DECODE
				printf("\nSuccesfully copied %zd bytes\n", bytes);
#endif
			}
		}
	}

#if DEBUG_BASE64_DECODE
	printf("\nbuffer: %ld bytes (0 - %d)\n", bytes, (numQuantums - 1));
#endif

	return bytes;
}


#if STAND_ALONE
//==============================================================================

#define BUFFFERLEN      128

#include "efi/essentials.h"


void *getGUIDFromDevicePath(EFI_DEVICE_PATH_PROTOCOL *devicePath)
{
	char * guid = NULL;
	
	if (devicePath != NULL)
	{
		while (!IsDevicePathEndType(devicePath) &&
			   !(DevicePathType(devicePath) == MEDIA_DEVICE_PATH && DevicePathSubType(devicePath) == MEDIA_HARDDRIVE_DP))
		{
			devicePath = NextDevicePathNode(devicePath);
		}
		
		if (DevicePathType(devicePath) == MEDIA_DEVICE_PATH && DevicePathSubType(devicePath) == MEDIA_HARDDRIVE_DP)
		{
			HARDDRIVE_DEVICE_PATH * HDDevicePath = (HARDDRIVE_DEVICE_PATH *) devicePath;
			
			if (HDDevicePath->SignatureType == SIGNATURE_TYPE_GUID) // 0x02
			{
				EFI_GUID * uuid = (EFI_GUID*)HDDevicePath->Signature;
				
				guid = (void *)malloc(37);
				
				// Function efi_guid_unparse_upper() in efi/efi_tables.c
				sprintf(guid, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
						uuid->Data1,
						uuid->Data2,
						uuid->Data3,
						uuid->Data4[0], uuid->Data4[1],
						uuid->Data4[2], uuid->Data4[3],
						uuid->Data4[4], uuid->Data4[5],
						uuid->Data4[6], uuid->Data4[7]);
			}
		}
	}
	
	return guid;
}

//==============================================================================

int main(void)
{
	// Test example: DE91E8DA-30B6-4B11-B8DC-76DC067BB57A (taken from a Macmini)

	const char * input = "AgEMANBBAwoAAAAAAQEGAAIfAxIKAAIAAAAAAAQBKgACAAAAKEAGAAAAAABASyklAAAAANrokd62MBFLuNx23AZ7tXoCAn//BAA=";

	// 02 01 0c 00 d0 41 03 0a 00 00 00 00
	// 01 01 06 00 02 1f 03 12 0a 00 02 00 00 00 00 00
	// 04 01 2a 00 02 00 00 00 28 40 06 00 00 00 00 00 40 4b 29 25 00 00 00 00 da e8 91 de b6 30 11 4b b8 dc 76 dc 06 7b b5 7a 02 02
	// 7f ff 04 00

	int len = ((strlen(input) / 4) * 3);

	unsigned char * decodedData = malloc(len);

	// Fill buffer with 0xdd (making errors visible)
	for (int i = 0; i <= len; i++)
	{
		decodedData[i] = 0xdd;
	}

	int rc = base64Decode(input, decodedData);

	// This of course should never happen
	if ((rc == 0) || (decodedData == NULL))
	{
		printf("FAIL\n");
	}

#if DEBUG_BASE64_DECODE
	printf("\nquickLookups: %d\n\n", quickLookups);
#endif

	EFI_DEVICE_PATH_PROTOCOL * dp = (EFI_DEVICE_PATH_PROTOCOL *) decodedData;

	void * guid = getGUIDFromDevicePath(dp);

	printf("GUID: %s\n", guid);

	exit(0);
}
#endif // #if STAND_ALONE
