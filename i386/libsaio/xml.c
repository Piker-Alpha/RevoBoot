/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 2003 Apple Computer, Inc.  All Rights
 * Reserved.  
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 *
 * Updates:
 *			- Cleanups, white space and layout changes (PikerAlpha, November 2012)
 *			- New/improved kXMLTagData support (PikerAlpha, November 2012) 
 *
 */

#include "libsaio.h"
#include "xml.h"

typedef struct Module
{
	struct Module *nextModule;
	long		willLoad;
	TagPtr		dict;
	char		* plistAddr;
	long		plistLength;
	char		* driverPath;
} Module, *ModulePtr;

typedef struct DriverInfo
{
	char	* plistAddr;
	long	plistLength;
	void	* moduleAddr;
	long	moduleLength;
} DriverInfo, * DriverInfoPtr;

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

#define kTagsPerBlock (0x1000)

static TagPtr gTagsFree;

typedef struct Symbol
{
	long			refCount;
	struct Symbol *	next;
	char			string[];
} Symbol, *SymbolPtr;

static SymbolPtr FindSymbol(char * string, SymbolPtr * prevSymbol);

static SymbolPtr gSymbolsHead;

static long ParseTagList(char *buffer, TagPtr *tag, long type, long empty);
static long ParseTagKey(char *buffer, TagPtr *tag);
static long ParseTagString(char *buffer, TagPtr *tag);
static long ParseTagInteger(char *buffer, TagPtr *tag);
static long ParseTagData(char *buffer, TagPtr *tag);
static long ParseTagDate(char *buffer, TagPtr *tag);
static long ParseTagBoolean(char *buffer, TagPtr *tag, long type);
static long GetNextTag(char *buffer, char **tag, long *start);
static long FixDataMatchingTag(char *buffer, char *tag);
static TagPtr NewTag(void);
static char *NewSymbol(char *string);
static void FreeSymbol(char *string);


//==============================================================================

TagPtr XMLGetProperty(TagPtr dict, const char * key)
{
	if (dict->type == kTagTypeDict)
	{
		TagPtr tag = 0;
		TagPtr tagList = dict->tag;

		while (tagList)
		{
			tag = tagList;
			tagList = tag->tagNext;

			if ((tag->type != kTagTypeKey) || (tag->string == 0))
			{
				continue;
			}
			else if (!strcmp(tag->string, key))
			{
				return tag->tag;
			}
		}
	}

	return 0;
}


#if UNUSED
//==========================================================================
// Expects to see one dictionary in the XML file.
// Puts the first dictionary it finds in the
// tag pointer and returns 0, or returns -1 if not found.
//
long XMLParseFile(char * buffer, TagPtr * dict)
{
	TagPtr tag = NULL;

	long length, pos = 0L;

	while (TRUE)
	{
		length = XMLParseNextTag(buffer + pos, &tag);

		if (length == -1)
		{
			break;
		}

		pos += length;

		if (tag == NULL)
		{
			continue;
		}

		if (tag->type == kTagTypeDict)
		{
			break;
		}

		XMLFreeTag(tag);
	}

	if (length < 0)
	{
		return -1L;
	}

	*dict = tag;

	return 0L;
}
#endif /* UNUSED */


//==========================================================================

long XMLParseNextTag(char * buffer, TagPtr * tag)
{
	char * tagName;
	long pos	= 0L;
	long length	= GetNextTag(buffer, &tagName, 0);
	
	if (length != -1L)
	{
		pos = length;
		
		if (!strncmp(tagName, kXMLTagPList, 6))
		{
			length = 0L;
		}
		else if (!strcmp(tagName, kXMLTagDict))
		{
			length = ParseTagList(buffer + pos, tag, kTagTypeDict, 0);
		}
		else if (!strcmp(tagName, kXMLTagDict "/"))
		{
			length = ParseTagList(buffer + pos, tag, kTagTypeDict, 1);
		}
		else if (!strcmp(tagName, kXMLTagKey))
		{
			length = ParseTagKey(buffer + pos, tag);
		}
		else if (!strcmp(tagName, kXMLTagString))
		{
			length = ParseTagString(buffer + pos, tag);
		}
		else if (!strcmp(tagName, kXMLTagInteger))
		{
			length = ParseTagInteger(buffer + pos, tag);
		}
		else if (!strcmp(tagName, kXMLTagData))
		{
			length = ParseTagData(buffer + pos, tag);
		}
		else if (!strcmp(tagName, kXMLTagDate))
		{
			length = ParseTagDate(buffer + pos, tag);
		}
		else if (!strcmp(tagName, kXMLTagFalse))
		{
			length = ParseTagBoolean(buffer + pos, tag, kTagTypeFalse);
		}
		else if (!strcmp(tagName, kXMLTagTrue))
		{
			length = ParseTagBoolean(buffer + pos, tag, kTagTypeTrue);
		}
		else if (!strcmp(tagName, kXMLTagArray))
		{
			length = ParseTagList(buffer + pos, tag, kTagTypeArray, 0);
		}
		else if (!strcmp(tagName, kXMLTagArray "/"))
		{
			length = ParseTagList(buffer + pos, tag, kTagTypeArray, 1);
		}
		else
		{
			*tag = 0;
			length = 0L;
		}
		
		if (length == -1)
		{
			pos = 0L;
		}

	}

	return pos + length;
}


//==============================================================================

static long ParseTagList(char * buffer, TagPtr * tag, long type, long empty)
{
	long length, pos = 0L;

	TagPtr tmpTag, tagList = 0;

	if (!empty)
	{
		while (1)
		{
			length = XMLParseNextTag(buffer + pos, &tmpTag);

			if (length == -1)
			{
				break;
			}

			pos += length;

			if (tmpTag == 0)
			{
				break;
			}

			tmpTag->tagNext = tagList;
			tagList = tmpTag;
		}

		if (length == -1)
		{
			XMLFreeTag(tagList);

			return -1L;
		}
	}

	tmpTag = NewTag();

	if (tmpTag == 0)
	{
		XMLFreeTag(tagList);

		return -1L;
	}

	tmpTag->type	= type;
	tmpTag->string	= 0;
	tmpTag->tag		= tagList;
	tmpTag->tagNext	= 0;

	*tag = tmpTag;

	return pos;
}


//==============================================================================

static long ParseTagKey(char * buffer, TagPtr * tag)
{
	long length = FixDataMatchingTag(buffer, kXMLTagKey);

	if (length != -1L)
	{
		TagPtr subTag;

		long length2 = XMLParseNextTag(buffer + length, &subTag);

		if (length2 != -1L)
		{
			TagPtr tmpTag = NewTag();

			if (tmpTag)
			{
				char * string = NewSymbol(buffer);

				if (string)
				{
					tmpTag->type	= kTagTypeKey;
					tmpTag->string	= string;
					tmpTag->tag		= subTag;
					tmpTag->tagNext	= 0;

					*tag = tmpTag;

					return length + length2;
				}
				else
				{
					XMLFreeTag(subTag);
					XMLFreeTag(tmpTag);
				}
			}
			else
			{
				XMLFreeTag(subTag);
			}
		}
	}

	return length;	// -1;
}


//==============================================================================

static long ParseTagString(char * buffer, TagPtr * tag)
{
	long length = FixDataMatchingTag(buffer, kXMLTagString);

	if (length != -1L)
	{
		TagPtr tmpTag = NewTag();

		if (tmpTag)
		{
			char * string = NewSymbol(buffer);

			if (string)
			{
				tmpTag->type	= kTagTypeString;
				tmpTag->string	= string;
				tmpTag->tag		= 0;
				tmpTag->tagNext	= 0;
				
				*tag = tmpTag;
			}
			else
			{
				XMLFreeTag(tmpTag);
			}
		}
	}

	return length;	// -1;
}


//==============================================================================

static long ParseTagInteger(char * buffer, TagPtr * tag)
{
	long length = FixDataMatchingTag(buffer, kXMLTagInteger);

	if (length != -1L)
	{
		TagPtr tmpTag = NewTag();

		if (tmpTag)
		{
			int integer = 0;

			tmpTag->type	= kTagTypeInteger;
			tmpTag->string	= (char *)integer;
			tmpTag->tag		= 0;
			tmpTag->tagNext	= 0;

			*tag = tmpTag;
		}
	}

	return length;	// -1
}


//==============================================================================

static long ParseTagData(char * buffer, TagPtr * tag)
{
	long length = FixDataMatchingTag(buffer, kXMLTagData);

	if (length != -1L)
	{
		TagPtr tmpTag = NewTag();

		if (tmpTag)
		{
			char * string = NewSymbol(buffer);

			tmpTag->type	= kTagTypeData;
			tmpTag->string	= string;
			tmpTag->tag	= 0;
			tmpTag->tagNext	= 0;

			*tag = tmpTag;
		}
	}

	return length;
}


//==============================================================================

static long ParseTagDate(char * buffer, TagPtr * tag)
{
	long length = FixDataMatchingTag(buffer, kXMLTagDate);

	if (length != -1L)
	{
		TagPtr tmpTag = NewTag();

		if (tmpTag)
		{
			tmpTag->type	= kTagTypeDate;
			tmpTag->string	= 0;
			tmpTag->tag		= 0;
			tmpTag->tagNext	= 0;

			*tag = tmpTag;

			return length;
		}
	}

	return -1;
}


//==============================================================================

static long ParseTagBoolean(char * buffer, TagPtr * tag, long type)
{
	TagPtr tmpTag = NewTag();

	if (tmpTag)
	{
		tmpTag->type	= type;
		tmpTag->string	= 0;
		tmpTag->tag		= 0;
		tmpTag->tagNext	= 0;

		*tag = tmpTag;

		return 0L;
	}

	return -1L;
}


//==============================================================================

static long GetNextTag(char * buffer, char ** tag, long * start)
{
	if (tag)
	{
		// Find the start of the tag.
		long cnt = 0L;
		
		while ((buffer[cnt] != '\0') && (buffer[cnt] != '<'))
		{
			cnt++;
		}
		
		if (buffer[cnt] != '\0')
		{
			// Find the end of the tag.
			long cnt2 = cnt + 1L;
			
			while ((buffer[cnt2] != '\0') && (buffer[cnt2] != '>'))
			{
				cnt2++;
			}
			
			if (buffer[cnt2] != '\0')
			{
				// Fix the tag data.
				*tag = buffer + cnt + 1;
				buffer[cnt2] = '\0';
				
				if (start)
				{
					*start = cnt;
				}
				
				return cnt2 + 1;
			}
		}
	}
	
	return -1L;
}


//==============================================================================
// Modifies 'buffer' to add a '\0' at the end of the tag matching 'tag'.
// Returns the length of the data found, counting the end tag,
// or -1 if the end tag was not found.

static long FixDataMatchingTag(char * buffer, char * tag)
{
	char * endTag;

	long length, stop, start = 0;

	while (1)
	{
		length = GetNextTag(buffer + start, &endTag, &stop);

		if (length == -1)
		{
			return -1;
		}
		else if ((*endTag == '/') && !strcmp(endTag + 1, tag))
		{
			break;
		}

		start += length;
	}

	buffer[start + stop] = '\0';

	return start + length;
}


//==============================================================================

static TagPtr NewTag(void)
{
	long	cnt = 0L;

	TagPtr	tag = NULL;

	if (gTagsFree == NULL)
	{
		tag = (TagPtr)malloc(kTagsPerBlock * sizeof(Tag));

		if (tag)
		{
			// Initalize the new tags.
			for (cnt = 0; cnt < kTagsPerBlock; cnt++)
			{
				tag[cnt].type		= kTagTypeNone;
				tag[cnt].string		= 0;
				tag[cnt].tag		= 0;
				tag[cnt].tagNext	= tag + cnt + 1;
			}

			tag[kTagsPerBlock - 1].tagNext = 0;

			gTagsFree = tag;
		}
		else
		{
			return NULL;
		}
	}

	tag = gTagsFree;
	gTagsFree = tag->tagNext;

	return tag;
}


//==============================================================================

void XMLFreeTag(TagPtr tag)
{
	if (tag)
	{
		if (tag->string)
		{
			FreeSymbol(tag->string);
		}

		XMLFreeTag(tag->tag);
		XMLFreeTag(tag->tagNext);

		// Clear and free the tag.
		tag->type		= kTagTypeNone;
		tag->string		= 0;
		tag->tag		= 0;
		tag->tagNext	= gTagsFree;
		gTagsFree		= tag;
	}
}


//==============================================================================

static char * NewSymbol(char * string)
{
	static SymbolPtr lastGuy = 0;

	// Look for string in the list of symbols.
	SymbolPtr symbol = FindSymbol(string, 0);

	// Add new symbol.
	if (symbol == 0)
	{
		symbol = (SymbolPtr)malloc(sizeof(Symbol) + 1 + strlen(string));

		if (symbol)
		{
			// Set the symbol's data.
			symbol->refCount = 0;
			strcpy(symbol->string, string);

			// Add the symbol to the list.
			symbol->next = gSymbolsHead;
			gSymbolsHead = symbol;
		}
		else
		{
			stop ("xml.c");
		}
	}

	// Update the refCount and return the string.
	symbol->refCount++;

	if (lastGuy && lastGuy->next != 0)
	{
		stop ("xml.c");
	}

	return symbol->string;
}


//==============================================================================

static void FreeSymbol(char * string)
{
	SymbolPtr symbol, prev;
	prev = 0;

	// Look for string in the list of symbols.
	symbol = FindSymbol(string, &prev);

	if (symbol)
	{
		// Update the refCount.
		symbol->refCount--;

		if (symbol->refCount == 0)
		{
			// Remove the symbol from the list.
			if (prev != 0)
			{
				prev->next = symbol->next;
			}
			else
			{
				gSymbolsHead = symbol->next;
			}
		}

		// Free the symbol's memory.
		free (symbol);
	}
}


//==============================================================================

static SymbolPtr FindSymbol(char * string, SymbolPtr * prevSymbol)
{
	SymbolPtr prev		= 0;
	SymbolPtr symbol	= gSymbolsHead;

	while (symbol != 0)
	{
		if (!strcmp(symbol->string, string))
		{
			break;
		}

		prev = symbol;
		symbol = symbol->next;
	}

	if ((symbol != 0) && (prevSymbol != 0))
	{
		*prevSymbol = prev;
	}

	return symbol;
}
