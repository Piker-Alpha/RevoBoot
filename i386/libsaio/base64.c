/*
 *
 * Name			: guidTest.c
 * Version		: 0.4
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
 *				- Length and character checking added (PikerAlpha, November 2012)
 *
 */

#ifdef REVOBOOT_VERSION_INFO
	#define STAND_ALONE			0
#else
	#define STAND_ALONE			1
#endif

#if STAND_ALONE
	#include <IOKit/IOKitLib.h>
	#include <CoreFoundation/CoreFoundation.h>
#else
	#include "libsaio.h"
#endif

#define DEBUG_BASE64_DECODE		0

#define FULL_BASE64_DATA_CHECK	0

#if DEBUG_BASE64_DECODE
	int quickLookups = 0;
#endif

#define PADDINGCHAR				'=' // 61 - 0x3d

#define TABLELEN				64


//==============================================================================
// Helper function for base64Decode

bool validBase64Length(char * aDataPtr)
{
	size_t length = (strlen(aDataPtr) - 1);
	
	if (length && (length % 4))
	{
		return true;
	}
	
	return false;
}


//==============================================================================
// Helper function for base64Decode

char *cleanupBase64Data(char *aDataPtr)
{
	int index		= 0;
#if DEBUG_BASE64_DECODE
	int junkChars	= 0;
#endif

	size_t length = strlen(aDataPtr);

	char *cleanedUpData = malloc(length);
	bzero(cleanedUpData, length);

	// Main loop
	while (*aDataPtr)
	{
		/*
		 * This check acts as a first pass filter. Its purpose is to strip invalid
		 * characters from the base64 encoded data, but we are mainly using it to
		 * get rid of the layout enhancement characters (think line feeds and tabs).
		 */
		if (*aDataPtr > 42 && *aDataPtr < 123)
		{
#if FULL_BASE64_DATA_CHECK
			/*
			 * Additional checking is normally not required, but may help people
			 * getting past messed up plist data fields (think hand editing).
			 */
			if (*aDataPtr > 43 && *aDataPtr < 47)		// ,-.
			{
				aDataPtr++;
#if DEBUG_BASE64_DECODE
				junkChars++;
#endif
			}
			else if (*aDataPtr > 57 && *aDataPtr < 65)	// :'<=>?@
			{
				if (*aDataPtr == PADDINGCHAR)
				{
					cleanedUpData[index++] = *aDataPtr;
#if DEBUG_BASE64_DECODE
					printf("%c", cleanedUpData[length]);
#endif
				}
				else
				{
					aDataPtr++;
#if DEBUG_BASE64_DECODE
					junkChars++;
#endif
				}
			}
			else if (*aDataPtr > 90 && *aDataPtr < 97)	// [\]^_`
			{
				aDataPtr++;
#if DEBUG_BASE64_DECODE
				junkChars++;
#endif
			}
			else
			{
#endif
				cleanedUpData[index++] = *aDataPtr;
#if DEBUG_BASE64_DECODE
				printf("%c", cleanedUpData[index]);
#endif
#if FULL_BASE64_DATA_CHECK
			}
#endif
		}
#if DEBUG_BASE64_DECODE
		else
		{
			junkChars++;
		}
#endif
		aDataPtr++;
	}

	cleanedUpData[index] = 0;

#if DEBUG_BASE64_DECODE
	printf("\njunkChars : %d\n", junkChars);
	
	length = strlen(cleanedUpData);

	for (int i = 0; i < length; i++)
	{
		printf("%c", cleanedUpData[i]);
	}
#endif

	return cleanedUpData;
}


//==============================================================================
// Helper function for base64Decode

void decodeQuantum(char *input, unsigned char *output)
{
	int j = 0;
#if DEBUG_BASE64_DECODE
	int found = 0;
#endif
	
	unsigned int x = 0; // We need a 32 bit wide variable for our bit shifting.
	
	const char * base64Charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	
	for (int i = 0; i < 4; i++)
	{
		if (input[i] == PADDINGCHAR)
		{
			x = (x << 6);
#if DEBUG_BASE64_DECODE
			found++;
#endif
		}
		else if (input[(i - 1)] == input[i]) // Same character as last one?
		{
#if DEBUG_BASE64_DECODE
			found++;
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
					found++;
#endif
					break;
				}
			}
		}
	}
#if DEBUG_BASE64_DECODE
	if (found < 4)
	{
		printf("ERROR ");
	}
#endif
	
	output[2] = x;
	output[1] = (x >>= 8);
	output[0] = (x >>= 8);
}


//==============================================================================

int base64Decode(char *input, unsigned char **decodedData)
{
	size_t bytes = 0;

	unsigned char *buffer = NULL;
	
	input = cleanupBase64Data(input);
	
	if (validBase64Length(input))
	{
		int numQuantums = (strlen(input) / 4);
	
		if (numQuantums)
		{
#if DEBUG_BASE64_DECODE
			printf("\nnumQuantums : %d\n\n", numQuantums);
#endif
			buffer = (unsigned char *)malloc(numQuantums * 3);

			if (buffer)
			{
				*decodedData = buffer;

				while (bytes < (numQuantums / 3))
				{
					for (int i = 0; i < numQuantums; i++)
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
				}
			}
		}
	}
#if DEBUG_BASE64_DECODE
	else
	{
		printf("\nError: Invalid length of base64 data!\n");
	}
#endif

	return bytes;
}


#if STAND_ALONE
//==============================================================================

#include "efi/essentials.h"

void *getUUIDFromDevicePath(EFI_DEVICE_PATH_PROTOCOL *devicePath)
{
	char * uuid = NULL;
	
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
				EFI_GUID * guid = (EFI_GUID*)HDDevicePath->Signature;
				
				uuid = (void *)malloc(37);
				
				// Function efi_guid_unparse_upper() in efi/efi_tables.c
				sprintf(uuid, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
						guid->Data1,
						guid->Data2,
						guid->Data3,
						guid->Data4[0], guid->Data4[1],
						guid->Data4[2], guid->Data4[3],
						guid->Data4[4], guid->Data4[5],
						guid->Data4[6], guid->Data4[7]);
			}
		}
	}
	
	return uuid;
}


//==============================================================================
// Used in RevoBoot/i386/boot2/boot.c

char * getStartupDiskUUID(char * aDataPtr)
{
	char * targetDiskUUID = NULL;
	
	unsigned char * decodedData = NULL;
	
	int rc = base64Decode(aDataPtr, &decodedData);
	
	if ((rc == 75) && (decodedData != NULL))
	{
		EFI_DEVICE_PATH_PROTOCOL * dp = (EFI_DEVICE_PATH_PROTOCOL *) decodedData;
			
		char * uuid = getUUIDFromDevicePath(dp);
			
		if (uuid)
		{
			targetDiskUUID = uuid;
		}
			
		dp = NULL;
	}
		
	free(decodedData);
	
	return targetDiskUUID;
}

//==============================================================================

int main(void)
{
	// Test example: DE91E8DA-30B6-4B11-B8DC-76DC067BB57A (taken from a Macmini)

	char * input = "	AgEMANBBAwoAAAAAAQEGAAIfA\n\r\t\
						xIKAAIAAAAAAAQBKgACAAAAKE\n\v\
						AGAAAAAABASyklAAAAANrokd6\n\
						2MBFLuNx23AZ7tXoCAn//BAA=";

	// 02 01 0c 00 d0 41 03 0a 00 00 00 00
	// 01 01 06 00 02 1f 03 12 0a 00 02 00 00 00 00 00
	// 04 01 2a 00 02 00 00 00 28 40 06 00 00 00 00 00 40 4b 29 25 00 00 00 00 da e8 91 de b6 30 11 4b b8 dc 76 dc 06 7b b5 7a 02 02
	// 7f ff 04 00

	char * uuid = getStartupDiskUUID(input);

	if (uuid)
	{
#if DEBUG_BASE64_DECODE
		printf("\nUUID: %s\n", uuid);
#endif
	}

	exit(0);
}
#endif // #if STAND_ALONE
