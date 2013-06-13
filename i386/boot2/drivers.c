/*
 * Copyright (c) 1999-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 2.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 *  drivers.c - Driver Loading Functions.
 *
 *  Copyright (c) 2000 Apple Computer, Inc.
 *
 *  DRI: Josh de Cesare
 */

#include <mach-o/fat.h>
#include <libkern/OSByteOrder.h>

#include "sl.h"
#include "boot.h"
#include "bootstruct.h"
#include "xml.h"


#if RAMDISK_SUPPORT
	#include "ramdisk.h"
#endif

#define MAX_KEXT_PATH_LENGTH	256

int gKextLoadStatus = 0; // Used to keep track of MKext loads.

typedef struct Module
{  
	struct Module *nextModule;
	long		willLoad;
	TagPtr		dict;
	char		* plistAddr;
	long		plistLength;
	char		* executablePath;
	char		* bundlePath;
	long		bundlePathLength;
} Module, *ModulePtr;

typedef struct DriverInfo
{
	char	* plistAddr;
	long	plistLength;
	void	* executableAddr;
	long	executableLength;
	void	* bundlePathAddr;
	long	bundlePathLength;
} DriverInfo, *DriverInfoPtr;

// START_DUPLICATED_BLOCK (see xml.c)

#define kDriverPackageSignature1 'MKXT'
#define kDriverPackageSignature2 'MOSX'

typedef struct DriversPackage
{
	unsigned long signature1;
	unsigned long signature2;
	unsigned long length;
	unsigned long adler32;
	unsigned long version;
	unsigned long numDrivers;
	unsigned long reserved1;
	unsigned long reserved2;
} DriversPackage;

enum
{
	kCFBundleType2,
	kCFBundleType3
};
// END_DUPLICATED_BLOCK

// Private functions.
static unsigned long localAdler32(unsigned char * buffer, long length);

#if (MAKE_TARGET_OS == SNOW_LEOPARD)
	static int loadMultiKext(char *fileSpec);
#endif

static int loadKexts(char *dirSpec, bool plugin);
static int loadPlist(char * dirSpec, bool isBundleType2Flag);
static long loadMatchedModules(void);
static long matchLibraries(void);

#ifdef NOTDEF
	static ModulePtr	findModule(char *name);
	static void			ThinFatFile(void **loadAddrP, unsigned long *lengthP);
#endif

static long parseXML(char *buffer, ModulePtr *module, TagPtr *personalities);
static long initDriverSupport(void);

static ModulePtr gModuleHead, gModuleTail;
static TagPtr    gPersonalityHead, gPersonalityTail;


//==============================================================================

static unsigned long localAdler32(unsigned char * buffer, long length)
{
    long          cnt;
    unsigned long result, lowHalf, highHalf;
    
    lowHalf  = 1;
    highHalf = 0;
  
	for (cnt = 0; cnt < length; cnt++)
    {
        if ((cnt % 5000) == 0)
        {
            lowHalf  %= 65521L;
            highHalf %= 65521L;
        }
    
        lowHalf  += buffer[cnt];
        highHalf += lowHalf;
    }

	lowHalf  %= 65521L;
	highHalf %= 65521L;
  
	result = (highHalf << 16) | lowHalf;
  
	return result;
}


//==============================================================================

static long initDriverSupport(void)
{
	gPlatform.KextFileName	= (char *) malloc(MAX_KEXT_PATH_LENGTH); // Used in loadKexts()
	gPlatform.KextPlistSpec	= (char *) malloc(MAX_KEXT_PATH_LENGTH); // Used in loadPlist()
	gPlatform.KextFileSpec	= (char *) malloc(MAX_KEXT_PATH_LENGTH); // Used in loadKexts() and loadMatchedModules()

	if (!gPlatform.KextFileName || !gPlatform.KextPlistSpec || !gPlatform.KextFileSpec)
	{
		stop("initDriverSupport error");
	}
	
	return 0;
}


//==============================================================================

long loadDrivers(char * dirSpec)
{
	if (initDriverSupport() != EFI_SUCCESS)
	{
		return -1;
	}

#if (MAKE_TARGET_OS == SNOW_LEOPARD)
	bool shouldLoadMKext = ((gBootMode & kBootModeSafe) == 0);

	_DRIVERS_DEBUG_DUMP("shouldLoadMKext: %s\n", shouldLoadMKext ? "true" : "false");

	if (shouldLoadMKext) // Skipped in "Safe Boot" mode.
	{
		if (loadMultiKext(gPlatform.KernelCachePath) == EFI_SUCCESS)
		{
			gKextLoadStatus |= 1;
			
			_DRIVERS_DEBUG_DUMP("loadMultiKext(1) OK.\n");
		}
	}

	_DRIVERS_DEBUG_DUMP("gKextLoadStatus: %d\n", gKextLoadStatus); 
	_DRIVERS_DEBUG_SLEEP(5);
#endif

	// Do we need to load individual kexts, in a one by one fashion?
	if (gKextLoadStatus != 3)
	{
		_DRIVERS_DEBUG_DUMP("gKextLoadStatus != 3\n");

		if ((gKextLoadStatus & 1) == 0)
		{
			_DRIVERS_DEBUG_DUMP("\nCalling loadKexts(\"/System/Library/Extensions\");\n");
			// System kexts
			if (loadKexts("/System/Library/Extensions", 0) == EFI_SUCCESS)
			{
				_DRIVERS_DEBUG_DUMP("loadKexts(1) OK.\n");
			}
#if (MAKE_TARGET_OS == MAVERICKS)
			// Signed kexts for Mavericks only!
			if (loadKexts("/Library/Extensions", 0) == EFI_SUCCESS)
			{
				_DRIVERS_DEBUG_DUMP("loadKexts(2) OK.\n");
			}
#endif
			_DRIVERS_DEBUG_DUMP("\n");
		}
	}

	matchLibraries();
	loadMatchedModules();

	_DRIVERS_DEBUG_SLEEP(15);

	return EFI_SUCCESS;
}


#if (MAKE_TARGET_OS == SNOW_LEOPARD)
//==============================================================================
// Returns 0 on success, -1 when not found, -2 on load failures and -3 on 
// verification (signatures, length, adler32) errors.

static int loadMultiKext(char * path)
{
	char fileName[] = "Extensions.mkext";
	long flags, time;

	strcat(path, "/");
	
	_DRIVERS_DEBUG_DUMP("\nloadMultiKext: %s%s\n", path, fileName);

#if DEBUG_DRIVERS
	if (strlen(path) >= 80)
	{
		stop("Error: gPlatform.KextFileSpec >= %d chars. Change soure code!\n", 80);
	}
#endif

	long ret = GetFileInfo(path, fileName, &flags, &time);
	
	// Pre-flight checks; Does the file exists, and is it something we can use?
	if ((ret == EFI_SUCCESS) && ((flags & kFileTypeMask) == kFileTypeFlat))
	{
		unsigned long    driversAddr, driversLength;
		char             segName[32];
		DriversPackage * package;

		char mkextSpec[80];
		sprintf(mkextSpec, "%s%s", path, fileName);

#if DEBUG_DRIVERS
		if (strlen(mkextSpec) >= 80)
		{
			stop("Error: mkextSpec >= %d chars. Change soure code!\n", 80);
		}
#endif

		// Load the MKext.
		long length = LoadThinFatFile(mkextSpec, (void **)&package);

		if (length < sizeof(DriversPackage))
		{
			_DRIVERS_DEBUG_DUMP("loadMultiKext(Load Failure : -2)\n");

			return -2;
		}

		// Handy little macro (_GET_PackageElement).
		#define _GET_PE(e)	OSSwapBigToHostInt32(package->e)

		#if DEBUG_DRIVERS
			printf("\nsignature1: 0x%x\n",	_GET_PE(signature1));
			printf("signature2: 0x%x\n",	_GET_PE(signature2));
			printf("length    : %ld\n",		_GET_PE(length));
			printf("adler32   : 0x%x\n",	_GET_PE(adler32));
			printf("numDrivers: %ld\n",		_GET_PE(numDrivers));
		#endif

		// Check the MKext header.
		if ((_GET_PE(signature1) != kDriverPackageSignature1)	||
			(_GET_PE(signature2) != kDriverPackageSignature2)	||
			(_GET_PE(length)      > kLoadSize)					||
			(_GET_PE(adler32)    !=
			 localAdler32((unsigned char *)&package->version, _GET_PE(length) - 0x10)))
		{
			_DRIVERS_DEBUG_DUMP("loadMultiKext(Verification Error : -3)\n");
	
			return -3;
		}

		// Make space for the MKext.
		driversLength = _GET_PE(length);
		driversAddr   = AllocateKernelMemory(driversLength);

		// Copy the MKext.
		memcpy((void *)driversAddr, (void *)package, driversLength);

		// Add the MKext to the memory map.
		sprintf(segName, "DriversPackage-%lx", driversAddr);
		AllocateMemoryRange(segName, driversAddr, driversLength, kBootDriverTypeMKEXT);

		_DRIVERS_DEBUG_DUMP("loadMultiKext(Success : 0) @ 0x%08x\n", driversAddr);

		return EFI_SUCCESS;
	}

	_DRIVERS_DEBUG_DUMP("loadMultiKext(File Not Found Error: -1)\n");

	return -1;
}
#endif

//==============================================================================

static int loadKexts(char * targetFolder, bool isPluginRun)
{
	bool isBundleType2 = false;
	
    long result = -1;
    long dirEntryFlags, dirEntryTime, dirEntryIndex = 0;
	
    const char * dirEntryName;
	
	while (1)
	{
		_DRIVERS_DEBUG_DUMP("O");
		
		result = GetDirEntry(targetFolder, &dirEntryIndex, &dirEntryName, &dirEntryFlags, &dirEntryTime);
		
		if (result == -1)
		{
			_DRIVERS_DEBUG_DUMP("b");
			
			// Back to loadKexts() when isPluginRun is true or loadDrivers() when false.
			break;
		}
		
		// Kexts are just folders so we need to have one.
		if ((dirEntryFlags & kFileTypeMask) == kFileTypeDirectory)
		{
			// Checking the file extension.
			if (strcmp(dirEntryName + (strlen(dirEntryName) - 5), ".kext") == 0)
			{
				sprintf(gPlatform.KextFileName, "%s/%s", targetFolder, dirEntryName);

#if DEBUG_DRIVERS
				if (strlen(gPlatform.KextFileName) >= MAX_KEXT_PATH_LENGTH)
				{
					stop("Error: gPlatform.KextFileName >= %d chars. Change MAX_KEXT_PATH_LENGTH!", MAX_KEXT_PATH_LENGTH);
				}
#endif
				// Determine bundle type.
				isBundleType2 = (GetFileInfo(gPlatform.KextFileName, "Contents", &dirEntryFlags, &dirEntryTime) == 0);

				result = loadPlist(gPlatform.KextFileName, isBundleType2);

				// False the first time we're here but true for the recursive call.
				if (!isPluginRun)
				{
					// Setup plug-ins path.
					sprintf(gPlatform.KextFileSpec, "%s/%sPlugIns", gPlatform.KextFileName, (isBundleType2) ? "Contents/" : "");

#if DEBUG_DRIVERS
					if (strlen(gPlatform.KextFileSpec) >= MAX_KEXT_PATH_LENGTH)
					{
						stop("Error: gPlatform.KextFileSpec >= %d chars. Change MAX_KEXT_PATH_LENGTH!", MAX_KEXT_PATH_LENGTH);
					}
#endif
					_DRIVERS_DEBUG_DUMP("R");

					// Recursive call for kexts in the PlugIns folder.
					result = loadKexts(gPlatform.KextFileSpec, true);
				}
			}
		}
	}

	return result;
}


//==============================================================================

static int loadPlist(char * targetFolder, bool isBundleType2)
{
    ModulePtr module;
    TagPtr    personalities;

    char * plistBuffer = 0;
    char * tmpExecutablePath = 0;
    char * tmpBundlePath = 0;

    long plistLength, bundlePathLength, result = -1;

	_DRIVERS_DEBUG_DUMP("+");

	// Construct path for executable.
	sprintf(gPlatform.KextPlistSpec, "%s/%s", targetFolder, (isBundleType2) ? "Contents/MacOS/" : "");

#if DRIVERS_DEBUG
	if (strlen(gPlatform.KextPlistSpec) >= MAX_KEXT_PATH_LENGTH)
	{
		stop("Error: gPlatform.KextPlistSpec >= %d chars. Change MAX_KEXT_PATH_LENGTH!", MAX_KEXT_PATH_LENGTH);
	}
#endif

	tmpExecutablePath = malloc(strlen(gPlatform.KextPlistSpec) + 1);

	if (tmpExecutablePath)
	{
		strcpy(tmpExecutablePath, gPlatform.KextPlistSpec);

		sprintf(gPlatform.KextPlistSpec, "%s/", targetFolder);

#if DRIVERS_DEBUG
		if (strlen(gPlatform.KextPlistSpec) >= MAX_KEXT_PATH_LENGTH)
		{
			stop("Error: gPlatform.KextPlistSpec >= %d chars. Change MAX_KEXT_PATH_LENGTH!", MAX_KEXT_PATH_LENGTH);
		}
#endif
		bundlePathLength = strlen(gPlatform.KextPlistSpec) + 1;

		tmpBundlePath = malloc(bundlePathLength);

		if (tmpBundlePath)
		{
			strcpy(tmpBundlePath, gPlatform.KextPlistSpec);

			// Path to plist, which may not exist.
			sprintf(gPlatform.KextPlistSpec, "%s/%sInfo.plist", targetFolder, (isBundleType2) ? "Contents/" : "");

#if DRIVERS_DEBUG
			if (strlen(gPlatform.KextPlistSpec) >= MAX_KEXT_PATH_LENGTH)
			{
				stop("Error: gPlatform.KextPlistSpec >= %d chars. Change MAX_KEXT_PATH_LENGTH!", MAX_KEXT_PATH_LENGTH);
			}
#endif
			// Try to load the plist. Returns -1 on failure, otherwise the file length.
			plistLength = LoadFile(gPlatform.KextPlistSpec);

			if (plistLength > 0)
			{
				plistLength += 1;
				plistBuffer = malloc(plistLength);

				if (plistBuffer)
				{
					strlcpy(plistBuffer, (char *)kLoadAddr, plistLength);

					// parseXML returns 0 on success so we check that here.
					if (parseXML(plistBuffer, &module, &personalities) == 0)
					{
						// Allocate memory for the driver path and the plist.
						module->executablePath = tmpExecutablePath;
						module->bundlePath = tmpBundlePath;
						module->bundlePathLength = bundlePathLength;
						module->plistAddr = (void *)malloc(plistLength);

						if (module->plistAddr)
						{
							// Tell free() to take no action for these two (by passing 0 as argument).
							tmpBundlePath = tmpExecutablePath = 0;

							// Add the plist to the module.
							strlcpy(module->plistAddr, (char *)kLoadAddr, plistLength);
							module->plistLength = plistLength;

							// Add the module to the end of the module list.
							if (gModuleHead == 0)
							{
								gModuleHead = module;
							}
							else
							{
								gModuleTail->nextModule = module;			
							}

							gModuleTail = module;
	
							// Add the personalities to the personalities list.
							if (personalities)
							{
								personalities = personalities->tag;
							}

							while (personalities != 0)
							{
								if (gPersonalityHead == 0)
								{
									gPersonalityHead = personalities->tag;
								}
								else
								{
									gPersonalityTail->tagNext = personalities->tag;
								}

								gPersonalityTail = personalities->tag;
								personalities = personalities->tagNext;
							}

							result = 0;

							_DRIVERS_DEBUG_DUMP(".");
						}
					}

					free(plistBuffer);
				}
			}

			// Free on failure only.
			free(tmpBundlePath);
		}
		// Free on failure only.
		free(tmpExecutablePath);
	}

    return result;
}


//==============================================================================

static long loadMatchedModules(void)
{
    TagPtr        prop;
    ModulePtr     module;
    char          *fileName, segName[32];
    DriverInfoPtr driver;
    long          length, driverAddr, driverLength;
    void          *executableAddr = 0;

    module = gModuleHead;

    while (module != 0)
    {
        if (module->willLoad)
        {
            prop = XMLGetProperty(module->dict, kPropCFBundleExecutable);

            if (prop != 0)
            {
                fileName = prop->string;

                sprintf(gPlatform.KextFileSpec, "%s%s", module->executablePath, fileName);
#if DEBUG_DRIVERS
				if (strlen(gPlatform.KextFileSpec) >= MAX_KEXT_PATH_LENGTH)
				{
					stop("Error: gPlatform.KextFileSpec >= %d chars. Change MAX_KEXT_PATH_LENGTH!", MAX_KEXT_PATH_LENGTH);
				}
#endif
                length = LoadThinFatFile(gPlatform.KextFileSpec, &executableAddr);

				if (length == 0)
				{
					length = LoadFile(gPlatform.KextFileSpec);
					executableAddr = (void *)kLoadAddr;
				}
            }
            else
			{
                length = 0;
			}

            if (length != -1)
            {
                //driverModuleAddr = (void *)kLoadAddr;
                //if (length != 0)
                //{
                //    ThinFatFile(&driverModuleAddr, &length);
                //}

                // Make room in the image area.
                driverLength = sizeof(DriverInfo) + module->plistLength + length + module->bundlePathLength;
                driverAddr = AllocateKernelMemory(driverLength);

                // Set up the DriverInfo.
                driver = (DriverInfoPtr)driverAddr;
                driver->plistAddr = (char *)(driverAddr + sizeof(DriverInfo));
                driver->plistLength = module->plistLength;

                if (length != 0)
                {
                    driver->executableAddr = (void *)(driverAddr + sizeof(DriverInfo) + module->plistLength);
                    driver->executableLength = length;
                }
                else
                {
                    driver->executableAddr   = 0;
                    driver->executableLength = 0;
                }

                driver->bundlePathAddr = (void *)(driverAddr + sizeof(DriverInfo) + module->plistLength + driver->executableLength);
                driver->bundlePathLength = module->bundlePathLength;

                // Save the plist, module and bundle.
                strcpy(driver->plistAddr, module->plistAddr);

				if (length != 0)
				{
					memcpy(driver->executableAddr, executableAddr, length);
				}

                strcpy(driver->bundlePathAddr, module->bundlePath);

                // Add an entry to the memory map.
                sprintf(segName, "Driver-%lx", (unsigned long)driver);
                AllocateMemoryRange(segName, driverAddr, driverLength, kBootDriverTypeKEXT);
            }
        }
        module = module->nextModule;
    }

    return 0;
}


//==============================================================================

static long matchLibraries(void)
{
	// printf("in MatchLibraries()\n");

    TagPtr     prop, prop2;
    ModulePtr  module, module2;
    long       done;

    do
	{
        done = 1;
        module = gModuleHead;
        
        while (module != 0)
        {
            if (module->willLoad == 1)
            {
                prop = XMLGetProperty(module->dict, kPropOSBundleLibraries);

                if (prop != 0)
                {
                    prop = prop->tag;

                    while (prop != 0)
                    {
                        module2 = gModuleHead;

                        while (module2 != 0)
                        {
                            prop2 = XMLGetProperty(module2->dict, kPropCFBundleIdentifier);

                            if ((prop2 != 0) && (!strcmp(prop->string, prop2->string)))
                            {
                                if (module2->willLoad == 0)
								{
                                    module2->willLoad = 1;
								}
                                break;
                            }
                            module2 = module2->nextModule;
                        }
                        prop = prop->tagNext;
                    }
                }
                module->willLoad = 2;
                done = 0;
            }
            module = module->nextModule;
        }
    }
    while (!done);

    return 0;
}


//==============================================================================

#if NOTDEF
static ModulePtr FindModule(char * name)
{
	TagPtr    prop;
	ModulePtr module = gModuleHead;

	while (module != 0)
	{
		prop = GetProperty(module->dict, kPropCFBundleIdentifier);

		if ((prop != 0) && !strcmp(name, prop->string))
		{
			break;
		}

		module = module->nextModule;
	}
    
	return module;
}
#endif /* NOTDEF */


//==============================================================================

// Kext may be required to mount the root filesystem.
#define kOSBundleRequiredRoot			"Root"

// Kext may be required to mount the root filesystem.
#define kOSBundleRequiredLocalRoot		"Local-Root"

// Kext may be required for network connectivity.
#define kOSBundleRequiredNetworkRoot	"Network-Root"

// Kext may be required for "Safe Boot" mode.
// Not loaded by the booter or included in startup kext caches.
#define kOSBundleRequiredSafeBoot		"Safe Boot"

// Kext may be required for console access in single-user mode.
#define kOSBundleRequiredConsole		"Console"

/* kernel.log: SAFE BOOT DETECTED - only valid OSBundleRequired kexts will be loaded.

const char * gRequiredKexts[] = 
{
	"IOPlatformPluginFamily", 
	"ACPI_SMC_PlatformPlugin", 

	"AppleSMBusPCI", 
	"AppleSMC",  

	'\0' // Must be last
};

static bool isLoadableInSafeBoot(char * OSBundleRequired)
{
	if (gBootMode == kBootModeNormal)
	{
		return (strcmp(OSBundleRequired, kOSBundleRequiredSafeBoot) != 0);
	}
	else if (gBootMode == kBootModeSafe)
	{
		if (strcmp(OSBundleRequired, kOSBundleRequiredRoot) == 0 ||
			strcmp(OSBundleRequired, kOSBundleRequiredLocalRoot) == 0 ||
			strcmp(OSBundleRequired, kOSBundleRequiredNetworkRoot) == 0 ||
			strcmp(OSBundleRequired, kOSBundleRequiredSafeBoot)	== 0 ||
			strcmp(OSBundleRequired, kOSBundleRequiredConsole))
		{
        
			return true;
		}
    }

	return false;
} */


//==============================================================================

static long parseXML(char * buffer, ModulePtr * module, TagPtr * personalities)
{
	long       length, pos = 0;
	TagPtr     moduleDict, required;
	ModulePtr  tmpModule;
  
	while (1)
	{
		length = XMLParseNextTag(buffer + pos, &moduleDict);

		if (length == -1)
		{
			break;
		}
    
		pos += length;
    
		if (moduleDict == 0)
		{
			continue;
		}

		if (moduleDict->type == kTagTypeDict)
		{
			break;
		}
    
		XMLFreeTag(moduleDict);
	}

	if (length == -1)
	{
		return -1;
	}

	required = XMLGetProperty(moduleDict, kPropOSBundleRequired);

	if ((required == 0) || (required->type != kTagTypeString) || !strcmp(required->string, "Safe Boot"))
	// if ((required == 0) || (required->type != kTagTypeString) || !isLoadableInSafeBoot(required->string))
	{
		XMLFreeTag(moduleDict);
		return -2;
	}

	tmpModule = (ModulePtr)malloc(sizeof(Module));

	if (tmpModule == 0)
	{
		XMLFreeTag(moduleDict);
		return -1;
	}

	tmpModule->dict = moduleDict;

	// For now, load any module that has OSBundleRequired != "Safe Boot".

	tmpModule->willLoad = 1;

	*module = tmpModule;

	// Get the personalities.

	*personalities = XMLGetProperty(moduleDict, kPropIOKitPersonalities);

	return 0;
}


//==============================================================================

long decodeKernel(void *binary, entry_t *rentry, char **raddr, int *rsize)
{
	// return DecodeMachO(binary, rentry, raddr, rsize);

	void *buffer;
	long ret;
	unsigned long len;

	u_int32_t uncompressedSize, size;
	compressed_kernel_header * kernel_header = (compressed_kernel_header *) binary;

#if DEBUG_DRIVERS
	printf("Kernel header data.\n");
	printf("===================\n");
	printf("signature         : 0x%08x\n",	kernel_header->signature);
	printf("compressType      : 0x%08x\n",	kernel_header->compressType);
	printf("adler32           : 0x%08x\n",	kernel_header->adler32);
	printf("uncompressedSize  : 0x%08x\n",	kernel_header->uncompressedSize);
	printf("compressedSize    : 0x%08x\n",	kernel_header->compressedSize);
	printf("platformName      : %s\n",		kernel_header->platformName);
	printf("rootPath          : %s\n",		kernel_header->rootPath);
	printf("Sleeping for 5 seconds...\n");
	sleep(5);
#endif

	if (kernel_header->signature == OSSwapBigToHostConstInt32('comp'))
	{
		if (kernel_header->compressType != OSSwapBigToHostConstInt32('lzss'))
		{
			error("kernel compression is bad\n");
			return -1;
		}

#if NOTDEF
		if (kernel_header->platformName[0] && strcmp(gPlatform.ModelID, kernel_header->platformName))
		{
			return -1;
		}

		if (kernel_header->rootPath[0] && strcmp(gBootFile, kernel_header->rootPath))
		{
			return -1;
		}
#endif

		uncompressedSize = OSSwapBigToHostInt32(kernel_header->uncompressedSize);
		binary = buffer = malloc(uncompressedSize);

		size = decompressLZSS((u_int8_t *) binary, &kernel_header->data[0], OSSwapBigToHostInt32(kernel_header->compressedSize));

		if (uncompressedSize != size)
        {
			error("Size mismatch from lzss: 0x08%x\n", size);
			return -1;
		}

		if (OSSwapBigToHostInt32(kernel_header->adler32) != localAdler32(binary, uncompressedSize))
		{
			printf("Adler mismatch\n");
			return -1;
		}
	}

	ret = ThinFatFile(&binary, &len);

	if (ret == 0 && len == 0 && gArchCPUType == CPU_TYPE_X86_64)
	{
		gArchCPUType = CPU_TYPE_I386;
		ret = ThinFatFile(&binary, &len);
	}

	ret = DecodeMachO(binary, rentry, raddr, rsize);

	if (ret < 0 && gArchCPUType == CPU_TYPE_X86_64)
	{
		gArchCPUType = CPU_TYPE_I386;
		ret = DecodeMachO(binary, rentry, raddr, rsize);
	}

	return ret;
}
