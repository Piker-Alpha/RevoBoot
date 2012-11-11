/*
 * Copyright (c) 1998-2009 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 * @header IOStorage
 * @abstract
 * This header contains the IOStorage class definition.
 */

#ifndef _IOSTORAGE_H
#define _IOSTORAGE_H

#include <IOKit/IOTypes.h>

/*!
 * @defined kIOStorageClass
 * @abstract
 * The name of the IOStorage class.
 */

#define kIOStorageClass "IOStorage"

/*!
 * @defined kIOStorageCategory
 * @abstract
 * kIOStorageCategory is a value for IOService's kIOMatchCategoryKey property.
 * @discussion
 * The kIOStorageCategory value is the standard value for the IOService property
 * kIOMatchCategoryKey ("IOMatchCategory") for all storage drivers.  All storage
 * objects that expect to drive new content (that is, produce new media objects)
 * are expected to compete within the kIOStorageCategory namespace.
 *
 * See the IOService documentation for more information on match categories.
 */

#define kIOStorageCategory "IOStorage"                /* (as IOMatchCategory) */

/*!
 * @defined kIOStorageFeaturesKey
 * @abstract
 * A property of any object in the storage stack.
 * @discussion
 * kIOStorageFeaturesKey is a property of any object in the storage stack that
 * wishes to express support of additional features, such as Force Unit Access.
 * It is typically defined in the device object below the block storage driver
 * object.  It has an OSDictionary value, where each entry describes one given
 * feature.
 */

#define kIOStorageFeaturesKey "IOStorageFeatures"

/*!
 * @defined kIOStorageFeatureDiscard
 * @abstract
 * Describes the presence of the Discard feature.
 * @discussion
 * This property describes the ability of the storage stack to delete unused
 * data from the media.  It is one of the feature entries listed under the top-
 * level kIOStorageFeaturesKey property table.  It has an OSBoolean value.
 */

#define kIOStorageFeatureDiscard "Discard"

/*!
 * @defined kIOStorageFeatureForceUnitAccess
 * @abstract
 * Describes the presence of the Force Unit Access feature.
 * @discussion
 * This property describes the ability of the storage stack to force a request
 * to access the media.  It is one of the feature entries listed under the top-
 * level kIOStorageFeaturesKey property table.  It has an OSBoolean value.
 */

#define kIOStorageFeatureForceUnitAccess "Force Unit Access"

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/assert.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOService.h>

/*!
 * @enum IOStorageAccess
 * @discussion
 * The IOStorageAccess enumeration describes the possible access levels for open
 * requests.
 * @constant kIOStorageAccessNone
 * No access is requested; should not be passed to open().
 * @constant kIOStorageAccessReader
 * Read-only access is requested.
 * @constant kIOStorageAccessReaderWriter
 * Read and write access is requested.
 * @constant kIOStorageAccessSharedLock
 * Shared access is requested.
 * @constant kIOStorageAccessExclusiveLock
 * Exclusive access is requested.
 */

enum
{
    kIOStorageAccessNone          = 0x00,
    kIOStorageAccessReader        = 0x01,
    kIOStorageAccessReaderWriter  = 0x03,
    kIOStorageAccessSharedLock    = 0x04,
    kIOStorageAccessExclusiveLock = 0x08
};

typedef UInt32 IOStorageAccess;

/*!
 * @enum IOStorageOptions
 * @discussion
 * Options for read and write storage requests.
 * @constant kIOStorageOptionForceUnitAccess
 * Force the request to access the media.
 */

enum
{
    kIOStorageOptionNone            = 0x00000000,
    kIOStorageOptionForceUnitAccess = 0x00000001,
    kIOStorageOptionReserved        = 0xFFFFFFFE
};

typedef UInt32 IOStorageOptions;

/*!
 * @struct IOStorageAttributes
 * @discussion
 * Attributes of read and write storage requests.
 * @field options
 * Options for the request.  See IOStorageOptions.
 * @field reserved
 * Reserved for future use.  Set to zero.
 */

struct IOStorageAttributes
{
    IOStorageOptions options;
    UInt32           reserved0032;
    UInt64           reserved0064;
#ifdef __LP64__
    UInt64           reserved0128;
    UInt64           reserved0192;
#endif /* __LP64__ */
};

/*!
 * @typedef IOStorageCompletionAction
 * @discussion
 * The IOStorageCompletionAction declaration describes the C (or C++) completion
 * routine that is called once an asynchronous storage operation completes.
 * @param target
 * Opaque client-supplied pointer (or an instance pointer for a C++ callback).
 * @param parameter
 * Opaque client-supplied pointer.
 * @param status
 * Status of the data transfer.
 * @param actualByteCount
 * Actual number of bytes transferred in the data transfer.
 */

typedef void (*IOStorageCompletionAction)(void *   target,
                                          void *   parameter,
                                          IOReturn status,
                                          UInt64   actualByteCount);

/*!
 * @struct IOStorageCompletion
 * @discussion
 * The IOStorageCompletion structure describes the C (or C++) completion routine
 * that is called once an asynchronous storage operation completes.   The values
 * passed for the target and parameter fields will be passed to the routine when
 * it is called.
 * @field target
 * Opaque client-supplied pointer (or an instance pointer for a C++ callback).
 * @field action
 * Completion routine to call on completion of the data transfer.
 * @field parameter
 * Opaque client-supplied pointer.
 */

struct IOStorageCompletion
{
    void *                    target;
    IOStorageCompletionAction action;
    void *                    parameter;
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOSTORAGE_H */
