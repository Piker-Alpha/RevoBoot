/*
 * Copyright (c) 2014 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Portions Copyright (c) 2003 Apple Computer, Inc.  All Rights
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
 *
 * The lzvn_decode function was first located and disassembled by Pike R.
 * Alpha and later converted to flat C code by someone using the handle
 * 'MinusZwei' over at insanelymac.com. This after Andy Vandijcke published
 * a working version at the for mentioned website.
 *
 * Thanks to Andy Vandijcke and 'MinusZwei' for their work, but I (Pike
 * R. Alpha) will not claim ownership of this work, other than the work
 * that I have done, for educational purpose, to improve the readability
 * so that it is understandable for everyone.
 *
 */

#include <stdio.h>
#include <string.h>

#include <libkern/OSByteOrder.h>

#define DEBUG_STATE_ENABLED			0


#if DEBUG_STATE_ENABLED
  #define _LZVN_DEBUG_DUMP(x...)	printf(x)
#else
  #define _LZVN_DEBUG_DUMP(x...)
#endif

#define LZVN_0		0
#define LZVN_1		1
#define LZVN_2		2
#define LZVN_3		3
#define LZVN_4		4
#define LZVN_5		5
#define LZVN_6		6
#define LZVN_7		7
#define LZVN_8		8
#define LZVN_9		9
#define LZVN_10		10
#define LZVN_11		11

#define CASE_TABLE	127

//==============================================================================

size_t lzvn_decode(void * decompressedData, size_t decompressedSize, void * compressedData, size_t compressedSize)
{
	const uint64_t decompBuffer = (const uint64_t)decompressedData;

	size_t	length	= 0;															// xor	%rax,%rax

	uint64_t compBuffer	= (uint64_t)compressedData;

	uint64_t compBufferPointer	= 0;												// use p(ointer)?
	uint64_t caseTableIndex	= 0;
	uint64_t r10			= 0;
	uint64_t currentLength	= 0;													// xor	%r12,%r12
	uint64_t r12			= 0;

	uint64_t address		= 0;													// ((uint64_t)compBuffer + compBufferPointer)
	unsigned char byte_data	= 0;

	uint8_t jmpTo			= CASE_TABLE;

	/*
	 * This jump table was developed by someone using the handle 'MinusZwei'
	 * over at insanelymac.com
	 */
	static short caseTable[ 256 ] =
	{
		1,  1,  1,  1,    1,  1,  2,  3,    1,  1,  1,  1,    1,  1,  4,  3,
		1,  1,  1,  1,    1,  1,  4,  3,    1,  1,  1,  1,    1,  1,  5,  3,
		1,  1,  1,  1,    1,  1,  5,  3,    1,  1,  1,  1,    1,  1,  5,  3,
		1,  1,  1,  1,    1,  1,  5,  3,    1,  1,  1,  1,    1,  1,  5,  3,
		1,  1,  1,  1,    1,  1,  0,  3,    1,  1,  1,  1,    1,  1,  0,  3,
		1,  1,  1,  1,    1,  1,  0,  3,    1,  1,  1,  1,    1,  1,  0,  3,
		1,  1,  1,  1,    1,  1,  0,  3,    1,  1,  1,  1,    1,  1,  0,  3,
		5,  5,  5,  5,    5,  5,  5,  5,    5,  5,  5,  5,    5,  5,  5,  5,
		1,  1,  1,  1,    1,  1,  0,  3,    1,  1,  1,  1,    1,  1,  0,  3,
		1,  1,  1,  1,    1,  1,  0,  3,    1,  1,  1,  1,    1,  1,  0,  3,
		6,  6,  6,  6,    6,  6,  6,  6,    6,  6,  6,  6,    6,  6,  6,  6,
		6,  6,  6,  6,    6,  6,  6,  6,    6,  6,  6,  6,    6,  6,  6,  6,
		1,  1,  1,  1,    1,  1,  0,  3,    1,  1,  1,  1,    1,  1,  0,  3,
		5,  5,  5,  5,    5,  5,  5,  5,    5,  5,  5,  5,    5,  5,  5,  5,
		7,  8,  8,  8,    8,  8,  8,  8,    8,  8,  8,  8,    8,  8,  8,  8,
		9, 10, 10, 10,   10, 10, 10, 10,   10, 10, 10, 10,   10, 10, 10, 10
	};

	decompressedSize -= 8;															// sub	$0x8,%rsi

	if (decompressedSize < 8)														// jb	Llzvn_exit
	{
		return 0;
	}

	compressedSize = (compBuffer + compressedSize - 8);								// lea	-0x8(%rdx,%rcx,1),%rcx

	if (compBuffer > compressedSize)												// cmp	%rcx,%rdx
	{
		return 0;																	// ja	Llzvn_exit
	}

	compBufferPointer = *(uint64_t *)compBuffer;									// mov	(%rdx),%r8
	caseTableIndex = (compBufferPointer & 255);										// movzbq	(%rdx),%r9

	do																				// jmpq	*(%rbx,%r9,8)
	{
		switch (jmpTo)																// our jump table
		{
			case CASE_TABLE: /******************************************************/

				switch (caseTable[(uint8_t)caseTableIndex])
				{
					case 0: _LZVN_DEBUG_DUMP("caseTable[0]\n");

							caseTableIndex >>= 6;									// shr	$0x6,%r9
							compBuffer = (compBuffer + caseTableIndex + 1);			// lea	0x1(%rdx,%r9,1),%rdx
						
							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}
						
							r10 = 56;												// mov	$0x38,%r10
							r10 &= compBufferPointer;								// and	%r8,%r10
							compBufferPointer >>= 8;								// shr	$0x8,%r8
							r10 >>= 3;												// shr	$0x3,%r10
							r10 += 3;												// add	$0x3,%r10
						
							jmpTo = LZVN_10;										// jmp	Llzvn_l10
							break;
						
					case 1:	_LZVN_DEBUG_DUMP("caseTable[1]\n");

							caseTableIndex >>= 6;									// shr	$0x6,%r9
							compBuffer = (compBuffer + caseTableIndex + 2);			// lea	0x2(%rdx,%r9,1),%rdx

							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}
						
							r12 = compBufferPointer;								// mov	%r8,%r12
							r12 = OSSwapInt64(r12);									// bswap	%r12
							r10 = r12;												// mov	%r12,%r10
							r12 <<= 5;												// shl	$0x5,%r12
							r10 <<= 2;												// shl	$0x2,%r10
							r12 >>= 53;												// shr	$0x35,%r12
							r10 >>= 61;												// shr	$0x3d,%r10
							compBufferPointer >>= 16;								// shr	$0x10,%r8
							r10 += 3;												// add	$0x3,%r10

							jmpTo = LZVN_10;										// jmp	Llzvn_l10
							break;

					case 2: _LZVN_DEBUG_DUMP("caseTable[2]\n");

							return length;
			
					case 3: _LZVN_DEBUG_DUMP("caseTable[3]\n");

							caseTableIndex >>= 6;									// shr	$0x6,%r9
							compBuffer = (compBuffer + caseTableIndex + 3);			// lea	0x3(%rdx,%r9,1),%rdx

							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}
						
							r10 = 56;												// mov	$0x38,%r10
							r12 = 65535;											// mov	$0xffff,%r12
							r10 &= compBufferPointer;								// and	%r8,%r10
							compBufferPointer >>= 8;								// shr	$0x8,%r8
							r10 >>= 3;												// shr	$0x3,%r10
							r12 &= compBufferPointer;								// and	%r8,%r12
							compBufferPointer >>= 16;								// shr	$0x10,%r8
							r10 += 3;												// add	$0x3,%r10
						
							jmpTo = LZVN_10;										// jmp	Llzvn_l10
							break;
						
					case 4:	_LZVN_DEBUG_DUMP("caseTable[4]\n");

							compBuffer += 1;										// add	$0x1,%rdx

							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}
						
							compBufferPointer = *(uint64_t *)compBuffer;			// mov	(%rdx),%r8
							caseTableIndex = (compBufferPointer & 255);				// movzbq (%rdx),%r9
						
							jmpTo = CASE_TABLE;										// continue;
							break;													// jmpq	*(%rbx,%r9,8)

					case 5: _LZVN_DEBUG_DUMP("caseTable[5]\n");

							return 0;												// Llzvn_table5;
					
					case 6: _LZVN_DEBUG_DUMP("caseTable[6]\n");

							caseTableIndex >>= 3;									// shr	$0x3,%r9
							caseTableIndex &= 3;									// and	$0x3,%r9
							compBuffer = (compBuffer + caseTableIndex + 3);			// lea	0x3(%rdx,%r9,1),%rdx

							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}
						
							r10 = compBufferPointer;								// mov	%r8,%r10
							r10 &= 775;												// and	$0x307,%r10
							compBufferPointer >>= 10;								// shr	$0xa,%r8
							r12 = (r10 & 255);										// movzbq %r10b,%r12
							r10 >>= 8;												// shr	$0x8,%r10
							r12 <<= 2;												// shl	$0x2,%r12
							r10 |= r12;												// or	%r12,%r10
							r12 = 16383;											// mov	$0x3fff,%r12
							r10 += 3;												// add	$0x3,%r10
							r12 &= compBufferPointer;								// and	%r8,%r12
							compBufferPointer >>= 14;								// shr	$0xe,%r8

							jmpTo = LZVN_10;										// jmp	Llzvn_l10
							break;
						
					case 7:	_LZVN_DEBUG_DUMP("caseTable[7]\n");

							compBufferPointer >>= 8;								// shr	$0x8,%r8
							compBufferPointer &= 255;								// and	$0xff,%r8
							compBufferPointer += 16;								// add	$0x10,%r8
							compBuffer = (compBuffer + compBufferPointer + 2);		// lea	0x2(%rdx,%r8,1),%rdx

							jmpTo = LZVN_0;											// jmp	Llzvn_l0
							break;
						
					case 8: _LZVN_DEBUG_DUMP("caseTable[8]\n");

							compBufferPointer &= 15;								// and	$0xf,%r8
							compBuffer = (compBuffer + compBufferPointer + 1);		// lea	0x1(%rdx,%r8,1),%rdx
						
							jmpTo = LZVN_0;											// jmp	Llzvn_l0
							break;
					
					case 9:	_LZVN_DEBUG_DUMP("caseTable[9]\n");

							compBuffer += 2;										// add	$0x2,%rdx
					
							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}

							r10 = compBufferPointer;								// mov	%r8,%r10
							r10 >>= 8;												// shr	$0x8,%r10
							r10 &= 255;												// and	$0xff,%r10
							r10 += 16;												// add	$0x10,%r10

							jmpTo = LZVN_11;										// jmp	Llzvn_l11
							break;

					case 10:_LZVN_DEBUG_DUMP("caseTable[10]\n");

							compBuffer += 1;										// add	$0x1,%rdx
							
							if (compBuffer > compressedSize)						// cmp	%rcx,%rdx
							{
								return 0;											// ja	Llzvn_exit
							}
						
							r10 = compBufferPointer;								// mov	%r8,%r10
							r10 &= 15;												// and	$0xf,%r10
						
							jmpTo = LZVN_11;										// jmp	Llzvn_l11
							break;
#if DEBUG_STATE_ENABLED
					default:printf("default() caseTableIndex[%d]\n", (uint8_t)caseTableIndex);
#endif
				}																	// switch (caseTable[caseTableIndex])

				break;

			case LZVN_0: /**********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(0)\n");

				if (compBuffer > compressedSize)									// cmp	%rcx,%rdx
				{
					return 0;														// ja	Llzvn_exit
				}
				
				currentLength = (length + compBufferPointer);						// lea	(%rax,%r8,1),%r11
				compBufferPointer = -compBufferPointer;								// neg	%r8
				
				if (currentLength > decompressedSize)								// cmp	%rsi,%r11
				{
					jmpTo = LZVN_2;													// ja	Llzvn_l2
					break;
				}

				currentLength = (decompBuffer + currentLength);						// lea	(%rdi,%r11,1),%r11

			case LZVN_1: /**********************************************************/

				do																	// Llzvn_l1:
				{
					_LZVN_DEBUG_DUMP("jmpTable(1)\n");

//					address = (compBuffer + compBufferPointer);						// mov	(%rdx,%r8,1),%r9
//					caseTableIndex = *(uint64_t *)address;
					caseTableIndex = *(uint64_t *)((uint64_t)compBuffer + compBufferPointer);

//					address = (currentLength + compBufferPointer);					// mov	%r9,(%r11,%r8,1)
//					*(uint64_t *)address = caseTableIndex;
					*(uint64_t *)((uint64_t)currentLength + compBufferPointer) = caseTableIndex;

					compBufferPointer += 8;											// add	$0x8,%r8

				} while ((UINT64_MAX - (compBufferPointer - 8)) >= 8);				// jae	Llzvn_l1

				length = currentLength;												// mov	%r11,%rax
				length -= decompBuffer;												// sub	%rdi,%rax
				
				compBufferPointer = *(uint64_t *)compBuffer;						// mov	(%rdx),%r8
				caseTableIndex = (compBufferPointer & 255);							// movzbq (%rdx),%r9

				jmpTo = CASE_TABLE;
				break;																// jmpq	*(%rbx,%r9,8)

			case LZVN_2: /**********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(2)\n");

				currentLength = (decompressedSize + 8);								// lea	0x8(%rsi),%r11

			case LZVN_3: /***********************************************************/

				do																	// Llzvn_l3:
				{
					_LZVN_DEBUG_DUMP("jmpTable(3)\n");

					address = (compBuffer + compBufferPointer);						// movzbq (%rdx,%r8,1),%r9
					caseTableIndex = *((uint64_t *)address);
					caseTableIndex &= 255;
					
					address = (decompBuffer + length);								// mov	%r9b,(%rdi,%rax,1)
					byte_data = (unsigned char)caseTableIndex;
					memcpy((void *)address, &byte_data, sizeof(byte_data));
					
					length += 1;													// add	$0x1,%rax
					
					if (currentLength == length)									// cmp	%rax,%r11
					{
						return length;												// je	Llzvn_exit2
					}
					
					compBufferPointer += 1;											// add	$0x1,%r8
					
				} while ((int64_t)compBufferPointer != 0);							// jne	Llzvn_l3
				
				compBufferPointer = *(uint64_t *)compBuffer;						// mov	(%rdx),%r8
				caseTableIndex = (compBufferPointer & 255);							// movzbq	(%rdx),%r9

				jmpTo = CASE_TABLE;
				break;																// jmpq	*(%rbx,%r9,8)

			case LZVN_4: /**********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(4)\n");

				currentLength = (decompressedSize + 8);								// lea	0x8(%rsi),%r11

			case LZVN_9: /**********************************************************/

				do																	// Llzvn_l9:
				{
					_LZVN_DEBUG_DUMP("jmpTable(9)\n");

					address = (decompBuffer + compBufferPointer);					// movzbq (%rdi,%r8,1),%r9
					byte_data = *((unsigned char *)address);
					caseTableIndex = byte_data;
					caseTableIndex &= 255;
					compBufferPointer += 1;											// add	$0x1,%r8
					
					address = (decompBuffer + length);								// mov	%r9,(%rdi,%rax,1)
					byte_data = (unsigned char)caseTableIndex;
					memcpy((void *)address, &byte_data, sizeof(byte_data));
					
					length += 1;													// add	$0x1,%rax
					
					if (length == currentLength)									// cmp	%rax,%r11
					{
						return length;												// je	Llzvn_exit2
					}

					r10 -= 1;														// sub	$0x1,%r10
					
				} while (r10);														// jne	Llzvn_l9
				
				compBufferPointer = *(uint64_t *)compBuffer;						// mov	(%rdx),%r8
				caseTableIndex = (compBufferPointer & 255);							// movzbq	(%rdx),%r9

				jmpTo = CASE_TABLE;
				break;																// jmpq	*(%rbx,%r9,8)

			case LZVN_5: /**********************************************************/

				do
				{
					_LZVN_DEBUG_DUMP("jmpTable(5)\n");

					address = (decompBuffer + compBufferPointer);					// mov	(%rdi,%r8,1),%r9
					caseTableIndex = *((uint64_t *)address);
					compBufferPointer += 8;											// add	$0x8,%r8
					
					address = (decompBuffer + length);								// mov	%r9,(%rdi,%rax,1)
					memcpy((void *)address, &caseTableIndex, sizeof(caseTableIndex));
					
					length += 8;													// add	$0x8,%rax
					r10 -= 8;														// sub	$0x8,%r10
					
				} while ((r10 + 8) > 8);											// ja	Llzvn_l5

				length += r10;														// add	%r10,%rax
				compBufferPointer = *(uint64_t *)compBuffer;						// mov	(%rdx),%r8
				caseTableIndex = (compBufferPointer & 255);							// movzbq	(%rdx),%r9

				jmpTo = CASE_TABLE;
				break;																// jmpq	*(%rbx,%r9,8)

			case LZVN_10: /*********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(10)\n");

				currentLength = (length + caseTableIndex);							// lea	(%rax,%r9,1),%r11
				currentLength += r10;												// add	%r10,%r11

				if (currentLength < decompressedSize)								// cmp	%rsi,%r11 (block_end: jae	Llzvn_l8)
				{
					address = decompBuffer + length;								// mov	%r8,(%rdi,%rax,1)
					memcpy((void *)address, &compBufferPointer, sizeof(compBufferPointer));
						
					length += caseTableIndex;										// add	%r9,%rax
					compBufferPointer = length;										// mov	%rax,%r8
						
					if (compBufferPointer < r12)									// jb	Llzvn_exit
					{
						return 0;
					}

					compBufferPointer -= r12;										// sub	%r12,%r8

					if (r12 < 8)													// cmp	$0x8,%r12
					{
						jmpTo = LZVN_4;												// jb	Llzvn_l4
						break;
					}

					jmpTo = LZVN_5;													// jmpq	*(%rbx,%r9,8)
					break;
				}

			case LZVN_8: /**********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(8)\n");

				if (caseTableIndex == 0)											// test	%r9,%r9
				{
					jmpTo = LZVN_7;													// jmpq	*(%rbx,%r9,8)
					break;
				}

				currentLength = (decompressedSize + 8);								// lea	0x8(%rsi),%r11

			case LZVN_6: /**********************************************************/

				do
				{
					_LZVN_DEBUG_DUMP("jmpTable(6)\n");

					address = (decompBuffer + length);								// mov	%r8b,(%rdi,%rax,1)
					byte_data = (unsigned char)(compBufferPointer & 255);
					memcpy((void *)address, &byte_data, sizeof(byte_data));
					length += 1;													// add	$0x1,%rax
						
					if (length == currentLength)									// cmp	%rax,%r11
					{
						return length;												// je	Llzvn_exit2
					}
						
					compBufferPointer >>= 8;										// shr	$0x8,%r8
					caseTableIndex -= 1;											// sub	$0x1,%r9
						
				} while (caseTableIndex != 1);										// jne	Llzvn_l6

			case LZVN_7: /**********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(7)\n");

				compBufferPointer = length;											// mov	%rax,%r8
				compBufferPointer -= r12;											// sub	%r12,%r8

				if (compBufferPointer < r12)										// jb	Llzvn_exit
				{
					return 0;
				}

				jmpTo = LZVN_4;
				break;																// jmpq	*(%rbx,%r9,8)
	
			case LZVN_11: /*********************************************************/

				_LZVN_DEBUG_DUMP("jmpTable(11)\n");

				compBufferPointer = length;											// mov	%rax,%r8
				compBufferPointer -= r12;											// sub	%r12,%r8
				currentLength = (length + r10);										// lea	(%rax,%r10,1),%r11
				
				if (currentLength < decompressedSize)								// cmp	%rsi,%r11
				{
					if (r12 >= 8)													// cmp	$0x8,%r12
					{
						jmpTo = LZVN_5;												// jae	Llzvn_l5
						break;
					}
				}
				
				jmpTo = LZVN_4;														// jmp	Llzvn_l4
				break;
		}																			// switch (jmpq)

	} while (1);

	return 0;
}
