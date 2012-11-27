

#include "libsaio.h"

#include "efi/essentials.h"
#include "efi/efi.h"


//==========================================================================
// Used in RevoBoot/i386/libsaio/disk.c

void convertEFIGUIDToString(EFI_GUID const *aGuid, char **aUUIDString)
{
	// Do we need to allocate memory?
	if (*aUUIDString == NULL)
	{
		//          1         2         3
		// 123456789 123456789 123456789 123456
		// 00000000-0000-0000-0000-000000000000
		*aUUIDString = (char *)malloc(36);
	}

	if (*aUUIDString)
	{
		bzero(*aUUIDString, 36);
		sprintf(*aUUIDString, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
				aGuid->Data1, /* - */
				aGuid->Data2, /* - */
				aGuid->Data3, /* - */
				aGuid->Data4[0], aGuid->Data4[1], /* - */
				aGuid->Data4[2], aGuid->Data4[3],
				aGuid->Data4[4], aGuid->Data4[5],
				aGuid->Data4[6], aGuid->Data4[7]);
	}
}


//==========================================================================
// Used in RevoBoot/i386/libsaio/disk.c

bool isEFIGUIDNull(EFI_GUID const *aGuid)
{
	if (aGuid->Data1 == 0 && aGuid->Data2 == 0 && aGuid->Data3 == 0)
	{
		int i = 0;

		for (i = 0; i < 8; ++i)
		{
			if (aGuid->Data4[i] != 0)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}


//=========================================================================
// Used in RevoBoot/i386/libsaio/disk.c

int compareEFIGUID(EFI_GUID const *aSourceGuid, EFI_GUID const *aCompareGuid)
{
	if (aSourceGuid->Data1 == aCompareGuid->Data1) // Comparing two EFI_UINT32's
	{
		if (aSourceGuid->Data2 == aCompareGuid->Data2) // Comparing two EFI_UINT16's
		{
			if (aSourceGuid->Data3 == aCompareGuid->Data3) // Comparing two EFI_UINT16's
			{
				// Returns 0 when equal or -1 when not
				return memcmp((const void *)aSourceGuid->Data4, (const void *)aSourceGuid->Data4, 8);
			}
		}
	}

	return -1;
}


#if STARTUP_DISK_SUPPORT
//=========================================================================
// Helper function for getStartupDiskUUID()

#if USE_DEVICE_PATH
void *getUUIDFromDevicePath(EFI_DEVICE_PATH_PROTOCOL *devicePath)
#else
void *getUUIDFromDevicePath(EFI_GUID *aGUID)
#endif
{
	char * uuid = NULL;

#if USE_DEVICE_PATH
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
				EFI_GUID const * aGUID = (EFI_GUID*)HDDevicePath->Signature;
				
				convertEFIGUIDToString(aGUID, &uuid);
			}
		}
	}
#else
	convertEFIGUIDToString(aGUID, &uuid);
#endif

	return uuid;
}


//==============================================================================
// Used in RevoBoot/i386/boot2/boot.c

char * getStartupDiskUUID(char * aDataPtr)
{
	char * startupDiskUUID = NULL;

	unsigned char * decodedData = NULL;

	int rc = base64Decode(aDataPtr, &decodedData);

	if ((rc == 75) && (decodedData != NULL))
	{
#if USE_DEVICE_PATH
		EFI_DEVICE_PATH_PROTOCOL * dp = (EFI_DEVICE_PATH_PROTOCOL *) decodedData;
		
		startupDiskUUID = getUUIDFromDevicePath(dp);
#else
		EFI_GUID * uuid = (EFI_GUID *) (decodedData + 52);
		
		convertEFIGUIDToString(uuid, &startupDiskUUID);
#endif
		free(decodedData);
	}

	return startupDiskUUID;
}
#endif // #if DISK_TARGET_SUPPORT
