/*
 * Copyright (c) 2000-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http: *www.apple.com/publicsource and read it before using this file.
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
 * HFSCompare.c - Functions for working with and comparing HFS nams.
 *
 * Copyright (c) 1999-2000 Apple Computer, Inc.
 *
 * DRI: Josh de Cesare
 *
 * Updates:
 *			- Latin is now a seperate table, done to make it faster (PikerAlpha, November 2012)
 *			- UNCOMPRESSED renamed to USE_UNCOMPRESSED_TABLES (PikerAlpha, November 2012)
 *			- Cleanups and other reformatting to pull it out of the 90's (PikerAlpha, November 2012)
 *
 */

#include <sl.h>
#include "hfs_CaseTables.h"


#if USE_COMPRESSED_TABLES
//==============================================================================

static unsigned short * deCompressStructure(struct CompressedBlock *cb, int count, int size)
{
	int i, j;

	unsigned short *out = malloc(size);

	if (out)
	{
		unsigned short *op = out;
		unsigned short data;

		for (i = 0; i < count; i++, cb++)
		{
			/* If this happens (it shouldn't) please fix size and/or double check that count really is
			 * the number of elements in the array.
			 * This was a very hard bug to find, so please leave this code here.
			 */
#if DEBUG
			if ((out + size) <= (op + cb->count))
			{
				stop("HFS+ Unicode tables are malformed\n");
			}
#endif
			data = cb->data;
		
			for (j = 0; j < cb->count; j++)
			{
				*op++ = data;
			
				if (cb->type == kTypeAscending) // 1
				{
					data++;
				}
				else if (cb->type == kTypeAscending256) // 2
				{
					data += 256;
				}
			}
		}

		return out;
	}

	return NULL;
}


//==============================================================================

static void deCompressHFSUnicodeTables(void)
{
	if (gCompareTable == 0)
	{
		gLatinCaseFoldTable	= deCompressStructure(gLatinCaseFoldTableCompressed, kLatinCaseFoldTableNBlocks, kLatinCaseFoldTableDataSize);
		gLowerCaseTable		= deCompressStructure(gLowerCaseTableCompressed, kLowerCaseTableNBlocks, kLowerCaseTableDataSize);
		gCompareTable		= deCompressStructure(gCompareTableCompressed, kCompareTableNBlocks, kCompareTableDataSize);

	}
}
#endif /* ! USE_COMPRESSED_TABLES */


/*==============================================================================
 *
 *	Routine:	FastRelString
 *
 *	Output:		returns -1 if str1 < str2
 *				returns  1 if str1 > str2
 *				return	 0 if equal
 *
 */

int32_t	FastRelString(u_int8_t * str1, u_int8_t * str2)
{
	int32_t  bestGuess;
	u_int8_t length, length2;

	length = *(str1++);
	length2 = *(str2++);

	if (length == length2)
	{
		bestGuess = 0;
	}
	else if (length < length2)
	{
		bestGuess = -1;
	}
	else
	{
		bestGuess = 1;
		length = length2;
	}

#if USE_COMPRESSED_TABLES
	deCompressHFSUnicodeTables();
#endif

	// u_int16_t* compareTable = (u_int16_t*) gCompareTable;

	while (length--)
	{
		u_int32_t aChar, bChar;

		aChar = *(str1++);
		bChar = *(str2++);
		
		if (aChar != bChar)	 /* If they don't match exacly, do case conversion */
		{
			u_int16_t aSortWord, bSortWord;

			aSortWord = gCompareTable[aChar];
			bSortWord = gCompareTable[bChar];

			if (aSortWord > bSortWord)
			{
				return 1;
			}

			if (aSortWord < bSortWord)
			{
				return -1;
			}
		}

		/*
		 * If characters match exactly, then go on to next character
		 * immediately without doing any extra work.
		 */
	}
	
	/* If you got to here, then return bestGuess */
	return bestGuess;
}	


/*==============================================================================
 *
 *	FastUnicodeCompare - Compare two Unicode strings; produce a relative ordering
 *
 *	    IF				RESULT
 *	--------------------------
 *	str1 < str2		=>	-1
 *	str1 = str2		=>	 0
 *	str1 > str2		=>	+1
 *
 *	The lower case table starts with 256 entries (one for each of the upper bytes
 *	of the original Unicode char).  If that entry is zero, then all characters with
 *	that upper byte are already case folded.  If the entry is non-zero, then it is
 *	the _index_ (not byte offset) of the start of the sub-table for the characters
 *	with that upper byte.  All ignorable characters are folded to the value zero.
 *
 *	In pseudocode:
 *
 *		Let c = source Unicode character
 *		Let table[] = lower case table
 *
 *		lower = table[highbyte(c)]
 *		if (lower == 0)
 *			lower = c
 *		else
 *			lower = table[lower+lowbyte(c)]
 *
 *		if (lower == 0)
 *			ignore this character
 *
 *	To handle ignorable characters, we now need a loop to find the next valid character.
 *	Also, we can't pre-compute the number of characters to compare; the string length might
 *	be larger than the number of non-ignorable characters.  Further, we must be able to handle
 *	ignorable characters at any point in the string, including as the first or last characters.
 *	We use a zero value as a sentinel to detect both end-of-string and ignorable characters.
 *	Since the File Manager doesn't prevent the NUL character (value zero) as part of a filename,
 *	the case mapping table is assumed to map u+0000 to some non-zero value (like 0xFFFF, which is
 *	an invalid Unicode character).
 *
 *	Pseudocode:
 *
 *		while (1) {
 *			c1 = GetNextValidChar(str1)			 *	returns zero if at end of string
 *			c2 = GetNextValidChar(str2)
 *
 *			if (c1 != c2) break					 *	found a difference
 *
 *			if (c1 == 0)						 *	reached end of string on both strings at once?
 *				return 0;						 *	yes, so strings are equal
 *		}
 *
 *		// When we get here, c1 != c2.  So, we just need to determine which one is less.
 *		if (c1 < c2)
 *			return -1;
 *		else
 *			return 1;
 */

int32_t FastUnicodeCompare(u_int16_t * str1, register u_int32_t length1, u_int16_t * str2, register u_int32_t length2)
{
	register u_int16_t c1, c2;
	register u_int16_t temp;

	register UInt16 * lowerCaseTable = (UInt16*) gLowerCaseTable;

#if USE_COMPRESSED_TABLES
	deCompressHFSUnicodeTables();
#endif

	while (1)
	{
		/* Set default values for c1, c2 in case there are no more valid chars */
		c1 = 0;
		c2 = 0;

		/* Find next non-ignorable char from str1, or zero if no more */
		while (length1 && c1 == 0)
		{
			c1 = SWAP_BE16(*(str1++));
			--length1;

			/* Check for basic latin first */
			if (c1 < 0x0100)
			{
				c1 =  SWAP_BE16(gLatinCaseFoldTable[c1]);
				break;
			}
			/* Case fold if neccessary */
			if ((temp = lowerCaseTable[c1 >> 8]) != 0)		/* Is there a subtable for this upper byte? */
			{
				c1 = lowerCaseTable[temp + (c1 & 0x00FF)];	/* Yes, so fold the char */
			}
		}

		/* Find next non-ignorable char from str2, or zero if no more */
		while (length2 && c2 == 0)
		{
			c2 = SWAP_BE16(*(str2++));
			--length2;

			/* Check for basic latin first */
			if (c2 < 0x0100)
			{
				c2 = SWAP_BE16(gLatinCaseFoldTable[c2]);
				break;
			}

			/* Case fold if neccessary */
			if ((temp = lowerCaseTable[c2 >> 8]) != 0)		/* Is there a subtable for this upper byte? */
			{
				c2 = lowerCaseTable[temp + (c2 & 0x00FF)];	/* Yes, so fold the char */
			}
		}

		if (c1 != c2)	/* Found a difference, so stop looping */
		{
			break;
		}
		
		if (c1 == 0)	/* Did we reach the end of both strings at the same time? */
		{
			return 0;	/* Yes, so strings are equal */
		}
	}
	
	if (c1 < c2)
	{
		return -1;
	}

	return 1;
}


/*==============================================================================
 * BinaryUnicodeCompare - Compare two Unicode strings; produce a relative ordering
 * Compared using a 16-bit binary comparison (no case folding)
 */

int32_t BinaryUnicodeCompare(u_int16_t * str1, u_int32_t length1, u_int16_t * str2, u_int32_t length2)
{
	register u_int16_t c1, c2;
	int32_t bestGuess = 0;
	u_int32_t length;

	if (length1 < length2)
	{
		length = length1;
		--bestGuess;
	}
	else if (length1 > length2)
	{
		length = length2;
		++bestGuess;
	}
	else
	{
		length = length1;
	}

	while (length--)
	{
		c1 = *(str1++);
		c2 = *(str2++);

		if (c1 > c2)
		{
			return (1);
		}

		if (c1 < c2)
		{
			return (-1);
		}
	}

	return (bestGuess);
}


/*==============================================================================
 * UTF-8 (UCS Transformation Format)
 *
 * The following subset of UTF-8 is used to encode UCS-2 filenames. It
 * requires a maximum of three 3 bytes per UCS-2 character.  Only the
 * shortest encoding required to represent the significant UCS-2 bits
 * is legal.
 *
 * UTF-8 Multibyte Codes
 *
 * Bytes   Bits   UCS-2 Min   UCS-2 Max   UTF-8 Byte Sequence (binary)
 * -------------------------------------------------------------------
 *   1       7     0x0000      0x007F      0xxxxxxx
 *   2      11     0x0080      0x07FF      110xxxxx 10xxxxxx
 *   3      16     0x0800      0xFFFF      1110xxxx 10xxxxxx 10xxxxxx
 * -------------------------------------------------------------------
 */


/*==============================================================================
 * utf_encodestr - Encodes the UCS-2 (Unicode) string at ucsp into a
 * null terminated UTF-8 string at utf8p.
 *
 * ucslen is the number of UCS-2 input characters (not bytes)
 * bufsize is the size of the output buffer in bytes
 */

void utf_encodestr(const u_int16_t * ucsp, int ucslen, u_int8_t * utf8p, u_int32_t bufsize)
{
	u_int8_t *bufend;
	u_int16_t ucs_ch;

	bufend = utf8p + bufsize;

	while (ucslen-- > 0)
	{
		ucs_ch = SWAP_BE16(*ucsp++);

		if (ucs_ch < 0x0080)
		{
			if (utf8p >= bufend)
			{
				break;
			}

			if (ucs_ch == '\0')
			{
				continue;	/* Skip over embedded NULLs */
			}

			*utf8p++ = ucs_ch;

		}
		else if (ucs_ch < 0x800)
		{
			if ((utf8p + 1) >= bufend)
			{
				break;
			}

			*utf8p++ = ((ucs_ch >> 6) | 0xc0);
			*utf8p++ = ((ucs_ch & 0x3f) | 0x80);
		}
		else
		{
			if ((utf8p + 2) >= bufend)
			{
				break;
			}

			*utf8p++ = ((ucs_ch >> 12) | 0xe0);
			*utf8p++ = (((ucs_ch >> 6) & 0x3f) | 0x80);
			*utf8p++ = ((ucs_ch & 0x3f) | 0x80);
		}
	}

	*utf8p = '\0';
}


/*==============================================================================
 * utf_decodestr - Decodes the null terminated UTF-8 string at
 * utf8p into a UCS-2 (Unicode) string at ucsp.
 *
 * ucslen is the number of UCS-2 output characters (not bytes)
 * bufsize is the size of the output buffer in bytes
 */

void utf_decodestr(const u_int8_t * utf8p, u_int16_t * ucsp, u_int16_t * ucslen, u_int32_t bufsize)
{
	u_int16_t *bufstart;
	u_int16_t *bufend;
	u_int16_t ucs_ch;
	u_int8_t  byte;

	bufstart = ucsp;
	bufend = (u_int16_t *)((u_int8_t *)ucsp + bufsize);

	while ((byte = *utf8p++) != '\0')
	{
		if (ucsp >= bufend)
		{
			break;
		}

		/* Check for ASCII */
		if (byte < 0x80)
		{
			ucs_ch = byte;
			*ucsp++ = SWAP_BE16(ucs_ch);
			continue;
		}

		switch (byte & 0xf0)
		{
			/* 2 byte sequence */
			case 0xc0:
			case 0xd0:	/* Extract bits 6 - 10 from first byte */
						ucs_ch = ((byte & 0x1F) << 6);
						break;
			/* 3 byte sequence */
			case 0xe0:
						/* Extract bits 12 - 15 from first byte */
						ucs_ch = ((byte & 0x0F) << 6);

						/* Extract bits 6 - 11 from second byte */
						if (((byte = *utf8p++) & 0xc0) != 0x80)
						{
							goto stop;
						}

						ucs_ch += (byte & 0x3F);
						ucs_ch <<= 6;
						break;
			default:
						goto stop;
		}

		/* Extract bits 0 - 5 from final byte */
		if (((byte = *utf8p++) & 0xc0) != 0x80)
		{
			goto stop;
		}

		ucs_ch += (byte & 0x3F);
		*ucsp++ = SWAP_BE16(ucs_ch);
	}

stop:
	*ucslen = SWAP_BE16(ucsp - bufstart);
}
