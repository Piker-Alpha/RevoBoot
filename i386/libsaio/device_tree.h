/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 2.0 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __DEVICE_TREE_H
#define __DEVICE_TREE_H

#include <stdbool.h>
#include <stdint.h>


//==============================================================================

typedef struct _Property
{
	const char *		name;
	uint32_t			length;
	void *				value;
	struct _Property *	next;
} Property;


//==============================================================================

typedef struct _Node
{
	struct _Property *	properties;
	struct _Property *	last_prop;
	struct _Node *		children;
	struct _Node *		next;
} Node;

extern Property * DT__AddProperty(Node *node, const char *name, uint32_t length, void *value);

extern Node * DT__AddChild(Node *parent, const char *name);

Node * DT__FindNode(const char *path, bool createIfMissing);

extern void DT__FreeProperty(Property *prop);

extern void DT__FreeNode(Node *node);

extern char * DT__GetName(Node *node);

void DT__Initialize(void);

// Free up memory used by in-memory representation of device tree.
extern void DT__Finalize(void);

void DT__FlattenDeviceTree(void **result, uint32_t *length);

#endif /* __DEVICE_TREE_H */
