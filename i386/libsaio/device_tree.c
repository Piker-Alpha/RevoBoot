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

#include "platform.h"
#include "libsaio.h"
#include "device_tree.h"

#if (DEBUG_EFI & 4)
	void DT__PrintTree(Node *node);
#endif

#define RoundToLong(x)	(((x) + 3) & ~3)

#define kAllocSize 4096

/*
 * Structures for a Flattened Device Tree 
 */

#define kPropNameLength 32

typedef struct DeviceTreeNodeProperty
{
	char		name[kPropNameLength];	// NUL terminated property name
	unsigned long	length;			// Length (bytes) of following prop value
} DeviceTreeNodeProperty;

typedef struct OpaqueDTEntry
{
	unsigned long	nProperties;		// Number of props[] elements (0 => end)
	unsigned long	nChildren;		// Number of children[] elements
} DeviceTreeNode;

typedef char DTPropertyNameBuf[32];

// Entry Name Definitions (Entry Names are C-Strings).
enum {
    kDTMaxEntryNameLength = 31			// Max length of a C-String Entry Name (terminator not included).
};

// Length of DTEntryNameBuf = kDTMaxEntryNameLength + 1.
typedef char DTEntryNameBuf[32];

static struct _DTSizeInfo
{
	uint32_t	numNodes;
	uint32_t	numProperties;
	uint32_t	totalPropertySize;
} DTInfo;

static Node * freeNodes, *allocedNodes;
static Property *freeProperties, *allocedProperties;


//==============================================================================

Property * DT__AddProperty(Node *node, const char *name, uint32_t length, void *value)
{
	Property *prop;

#if (DEBUG_EFI & 2)
		_EFI_DEBUG_DUMP("DT__AddProperty([Node '%s'], '%s', %d, 0x%x)\n", DT__GetName(node), name, length, value);
#endif

	if (freeProperties == NULL)
	{
		void *buf = malloc(kAllocSize);
		int i;

	#if (DEBUG_EFI & 2)
		_EFI_DEBUG_DUMP("Allocating more free properties\n");
	#endif

		if (buf == 0)
		{
			return 0;
		}

		bzero(buf, kAllocSize);
		// Use the first property to record the allocated buffer for later freeing.
		prop = (Property *)buf;
		prop->next = allocedProperties;
		allocedProperties = prop;
		prop->value = buf;
		prop++;

		for (i = 1; i < (kAllocSize / sizeof(Property)); i++)
		{
			prop->next = freeProperties;
			freeProperties = prop;
			prop++;
		}
	}

	prop = freeProperties;
	freeProperties = prop->next;

	prop->name = name;
	prop->length = length;
	prop->value = value;

	// Always add to end of list
	if (node->properties == 0)
	{
		node->properties = prop;
	}
	else
	{
		node->last_prop->next = prop;
	}

	node->last_prop = prop;
	prop->next = 0;

#if (DEBUG_EFI & 8)
	_EFI_DEBUG_DUMP("Done [0x%x]\n", prop);
#endif

	DTInfo.numProperties++;
	DTInfo.totalPropertySize += RoundToLong(length);

	return prop;
}


//==============================================================================

Node * DT__AddChild(Node *parent, const char *name)
{
	Node *node;

	if (freeNodes == NULL)
	{
		void *buf = malloc(kAllocSize);

		if (buf == 0)
		{
			return 0;
		}

		int i;

#if (DEBUG_EFI & 2)
		_EFI_DEBUG_DUMP("Allocating more free nodes\n");
#endif

		bzero(buf, kAllocSize);
		node = (Node *)buf;

		// Use the first node to record the allocated buffer for later freeing.
		node->next = allocedNodes;
		allocedNodes = node;
		node->children = (Node *)buf;
		node++;

		for (i = 1; i < (kAllocSize / sizeof(Node)); i++)
		{
			node->next = freeNodes;
			freeNodes = node;
			node++;
		}
	}

#if (DEBUG_EFI & 2)
	_EFI_DEBUG_DUMP("DT__AddChild(0x%x, '%s')\n", parent, name);
#endif

	node = freeNodes;
	freeNodes = node->next;

#if (DEBUG_EFI & 2)
	_EFI_DEBUG_DUMP("Got free node 0x%x\n", node);
	_EFI_DEBUG_DUMP("prop = 0x%x, children = 0x%x, next = 0x%x\n", node->properties, node->children, node->next);
#endif

	if (parent == NULL)
	{
		gPlatform.DT.RootNode = node;
		node->next = 0;
	}
	else
	{
		node->next = parent->children;
		parent->children = node;
	}

	DTInfo.numNodes++;
	DT__AddProperty(node, "name", strlen(name) + 1, (void *) name);

	return node;
}


//==============================================================================

void DT__FreeProperty(Property *prop)
{
	prop->next = freeProperties;
	freeProperties = prop;
}


//==============================================================================

void DT__FreeNode(Node *node)
{
	node->next = freeNodes;
	freeNodes = node;
}


//==============================================================================

void DT__Initialize(void)
{
	// _EFI_DEBUG_DUMP("DT__Initialize\n");

	freeNodes = 0;
	allocedNodes = 0;
	freeProperties = 0;
	allocedProperties = 0;

	DTInfo.numNodes = 0;
	DTInfo.numProperties = 0;
	DTInfo.totalPropertySize = 0;

	gPlatform.DT.RootNode = DT__AddChild(NULL, "/");

	if (gPlatform.DT.RootNode == 0)
	{
		stop("Couldn't create root node"); // Mimics boot.efi
	}

	// _EFI_DEBUG_DUMP("DT__Initialize done\n");
}


//==============================================================================
// Free up memory used by in-memory representation of device tree.

void DT__Finalize(void)
{
	Node *node;
	Property *prop;

#if (DEBUG_EFI & 8)
	_EFI_DEBUG_DUMP("DT__Finalize\n");
#endif

	for (prop = allocedProperties; prop != NULL; prop = prop->next)
	{
		free(prop->value);
	}

	allocedProperties = NULL;
	freeProperties = NULL;

	for (node = allocedNodes; node != NULL; node = node->next)
	{
		free((void *)node->children);
	}

	allocedNodes = NULL;
	freeNodes = NULL;
	gPlatform.DT.RootNode = NULL;
    
	// XXX leaks any created strings
	DTInfo.numNodes = 0;
	DTInfo.numProperties = 0;
	DTInfo.totalPropertySize = 0;

	// _EFI_DEBUG_DUMP("DT__Finalize done\n");
}


//==============================================================================

static void * FlattenNodes(Node *node, void *buffer)
{
	Property *prop;
	DeviceTreeNode *flatNode;
	DeviceTreeNodeProperty *flatProp;
	int count;

	if (node == 0)
	{
		return buffer;
	}

	flatNode = (DeviceTreeNode *)buffer;
	buffer += sizeof(DeviceTreeNode);

	for (count = 0, prop = node->properties; prop != 0; count++, prop = prop->next)
	{
		flatProp = (DeviceTreeNodeProperty *)buffer;
		strcpy(flatProp->name, prop->name);
		flatProp->length = prop->length;
		buffer += sizeof(DeviceTreeNodeProperty);
		bcopy(prop->value, buffer, prop->length);
		buffer += RoundToLong(prop->length);
	}

	flatNode->nProperties = count;

	for (count = 0, node = node->children; node != 0; count++, node = node->next)
	{
		buffer = FlattenNodes(node, buffer);
	}

	flatNode->nChildren = count;

	return buffer;
}


/*==============================================================================
 * Flatten the in-memory representation of the device tree into a binary DT block.
 * To get the buffer size needed, call with result = 0.
 * To have a buffer allocated for you, call with *result = 0.
 * To use your own buffer, call with *result = &buffer.
 */

void DT__FlattenDeviceTree(void **buffer_p, uint32_t *length)
{
	uint32_t totalSize;
	void * buf;

#if (DEBUG_EFI & 2)
	_EFI_DEBUG_DUMP("DT__FlattenDeviceTree(0x%x, 0x%x)\n", buffer_p, length);
#endif

#if (DEBUG_EFI & 4)
	if (buffer_p) 
	{
		DT__PrintTree(gPlatform.DT.RootNode);
	}
#endif
    
	totalSize = DTInfo.numNodes * sizeof(DeviceTreeNode) + 
	DTInfo.numProperties * sizeof(DeviceTreeNodeProperty) +
	DTInfo.totalPropertySize;

#if (DEBUG_EFI & 2)
	_EFI_DEBUG_DUMP("Total size 0x%x\n", totalSize);
#endif

	if (buffer_p != 0)
	{
		if (totalSize == 0)
		{
			buf = 0;
		}
		else
		{
			if (*buffer_p == 0)
			{
				buf = malloc(totalSize);
			}
			else
			{
				buf = *buffer_p;
			}

			bzero(buf, totalSize);

			FlattenNodes(gPlatform.DT.RootNode, buf);
		}

		*buffer_p = buf;
	}

	if (length)
	{
		*length = totalSize;
	}
}


//==============================================================================

char * DT__GetName(Node *node)
{
	Property *prop;

#if (DEBUG_EFI & 8)
	_EFI_DEBUG_DUMP("DT__GetName(0x%x)\n", node);
	_EFI_DEBUG_DUMP("Node properties = 0x%x\n", node->properties);
#endif

	for (prop = node->properties; prop; prop = prop->next)
	{
#if (DEBUG_EFI & 8)
		_EFI_DEBUG_DUMP("Prop '%s'\n", prop->name);
#endif
		if (strcmp(prop->name, "name") == 0)
		{
			return prop->value;
		}
	}

	//_EFI_DEBUG_DUMP("DT__GetName returns 0\n");
	return "(null)";
}


//==============================================================================

Node * DT__FindNode(const char *path, bool createIfMissing)
{
	Node *node, *child;
	DTPropertyNameBuf nameBuf;
	char *bp;
	int i;

#if (DEBUG_EFI & 2)
	_EFI_DEBUG_DUMP("DT__FindNode('%s', %d)\n", path, createIfMissing);
#endif

	// Start at root
	node = gPlatform.DT.RootNode;

	_EFI_DEBUG_DUMP("root = 0x%x\n", node);

	while (node)
	{
		// Skip leading slash
		while (*path == '/')
		{
			path++;
		}

		for (i = 0, bp = nameBuf; ++i < kDTMaxEntryNameLength && *path && *path != '/'; bp++, path++)
		{
			*bp = *path;
		}

		*bp = '\0';

		if (nameBuf[0] == '\0')
		{
			break; // last path entry
		}
#if (DEBUG_EFI & 2)
		_EFI_DEBUG_DUMP("Node '%s'\n", nameBuf);
#endif

		for (child = node->children; child != 0; child = child->next)
		{
#if (DEBUG_EFI & 2)
			_EFI_DEBUG_DUMP("Child 0x%x\n", child);
#endif
			if (strcmp(DT__GetName(child), nameBuf) == 0)
			{
				break;
			}
		}

		if (child == 0 && createIfMissing)
		{
#if (DEBUG_EFI & 2)
			_EFI_DEBUG_DUMP("Creating node\n");
#endif

			char *str = malloc(strlen(nameBuf) + 1);
			// XXX this will leak
			strcpy(str, nameBuf);

			child = DT__AddChild(node, str);
		}

		node = child;
	}

	return node;
}


#if (DEBUG_EFI & 4)
//==============================================================================

void DT__PrintNode(Node *node, int level)
{
	char spaces[10], *cp = spaces;
	Property *prop;

	if (level > 9)
	{
		level = 9;
	}

	while (level--)
	{
		*cp++ = ' ';
	}

	*cp = '\0';

	_EFI_DEBUG_DUMP("%s===Node===\n", spaces);

	for (prop = node->properties; prop; prop = prop->next)
	{
		char c = *((char *)prop->value);

		if (prop->length < 64 && (strcmp(prop->name, "name") == 0 || 
			(c >= '0' && c <= '9') || 
			(c >= 'a' && c <= 'z') || 
			(c >= 'A' && c <= 'Z') || c == '_'))
		{
			_EFI_DEBUG_DUMP("%s Property '%s' [%d] = '%s'\n", spaces, prop->name, prop->length, prop->value);
		}
		else
		{
			_EFI_DEBUG_DUMP("%s Property '%s' [%d] = (data)\n", spaces, prop->name, prop->length);
		}
	}

	_EFI_DEBUG_DUMP("%s==========\n", spaces);
}


//==============================================================================

static void _PrintTree(Node *node, int level)
{
	DT__PrintNode(node, level);

	level++;

	for (node = node->children; node; node = node->next)
	{
		_PrintTree(node, level);
	}
}


//==============================================================================

void DT__PrintTree(Node *node)
{
	if (node == 0)
	{
		node = gPlatform.DT.RootNode;
	}

	_PrintTree(node, 0);
}

#endif
