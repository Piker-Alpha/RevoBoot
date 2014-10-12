// picoPNG version 20101224
// Copyright (c) 2005-2010 Lode Vandevenne
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//      claim that you wrote the original software. If you use this software
//      in a product, an acknowledgment in the product documentation would be
//      appreciated but is not required.
//   2. Altered source versions must be plainly marked as such, and must not be
//      misrepresented as being the original software.
//   3. This notice may not be removed or altered from any source distribution.
//
// Note: Ported from CPP to C by kaitek.
//

#include <sys/types.h>
#include "libsa.h"
#include "picopng.h"


/*************************************************************************************************/

typedef struct png_alloc_node
{
	struct png_alloc_node *prev, *next;
	void *addr;
	size_t size;
} png_alloc_node_t;

png_alloc_node_t *png_alloc_head = NULL;
png_alloc_node_t *png_alloc_tail = NULL;

//==============================================================================

png_alloc_node_t *png_alloc_find_node(void *addr)
{
	png_alloc_node_t *node;

	for (node = png_alloc_head; node; node = node->next)
	{
		if (node->addr == addr)
		{
			break;
		}
	}

	return node;
}


//==============================================================================

void png_alloc_add_node(void *addr, size_t size)
{
	png_alloc_node_t *node;

	if (png_alloc_find_node(addr))
	{
		return;
	}

	node = malloc(sizeof(png_alloc_node_t));
	node->addr = addr;
	node->size = size;
	node->prev = png_alloc_tail;
	node->next = NULL;
	png_alloc_tail = node;

	if (node->prev)
	{
		node->prev->next = node;
	}

	if (!png_alloc_head)
	{
		png_alloc_head = node;
	}
}


//==============================================================================

void png_alloc_remove_node(png_alloc_node_t *node)
{
	if (node->prev)
	{
		node->prev->next = node->next;
	}

	if (node->next)
	{
		node->next->prev = node->prev;
	}

	if (node == png_alloc_head)
	{
		png_alloc_head = node->next;
	}

	if (node == png_alloc_tail)
	{
		png_alloc_tail = node->prev;
	}

	node->prev = node->next = node->addr = NULL;
	free(node);
}


//==============================================================================

void *png_alloc_malloc(size_t size)
{
	void *addr = malloc(size);
	png_alloc_add_node(addr, size);

	return addr;
}


//==============================================================================

void *png_alloc_realloc(void *addr, size_t size)
{
	void *new_addr;

	if (!addr)
	{
		return png_alloc_malloc(size);
	}

	new_addr = realloc(addr, size);

	if (new_addr != addr)
	{
		png_alloc_node_t *old_node;
		old_node = png_alloc_find_node(addr);
		png_alloc_remove_node(old_node);
		png_alloc_add_node(new_addr, size);
	}

	return new_addr;
}


//==============================================================================

void png_alloc_free(void *addr)
{
	png_alloc_node_t *node = png_alloc_find_node(addr);

	if (!node)
	{
		return;
	}

	png_alloc_remove_node(node);
	free(addr);
}


//==============================================================================

void png_alloc_free_all()
{
	while (png_alloc_tail)
	{
		void *addr = png_alloc_tail->addr;
		png_alloc_remove_node(png_alloc_tail);
		free(addr);
	}
}


//==============================================================================

uint32_t vector32_resize(vector32_t *p, size_t size)
{
	/*
	 * returns 1 if success, 0 if failure ==> nothing done
	 */
	if (size * sizeof(uint32_t) > p->allocsize)
	{
		size_t newsize = size * sizeof(uint32_t) * 2;
		void *data = png_alloc_realloc(p->data, newsize);

		if (data)
		{
			p->allocsize = newsize;
			p->data = (uint32_t *) data;
			p->size = size;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		p->size = size;
	}

	return 1;
}


//==============================================================================

uint32_t vector32_resizev(vector32_t *p, size_t size, uint32_t value)
{
	/*
	 * resize and give all new elements the value
	 */
	size_t oldsize = p->size, i;

	if (!vector32_resize(p, size))
	{
		return 0;
	}

	for (i = oldsize; i < size; i++)
	{
		p->data[i] = value;
	}

	return 1;
}


//==============================================================================

vector32_t *vector32_new(size_t size, uint32_t value)
{
	vector32_t *p = png_alloc_malloc(sizeof(vector32_t));

	p->data = NULL;
	p->size = p->allocsize = 0;

	if (size && !vector32_resizev(p, size, value))
	{
		return NULL;
	}

	return p;
}


//==============================================================================

uint32_t vector8_resize(vector8_t *p, size_t size)
{
	/*
	 * returns 1 if success, 0 if failure ==> nothing done
	 * xxx: the use of sizeof uint32_t here seems like a bug (this descends from the lodepng vector
	 * compatibility functions which do the same). without this there is corruption in certain cases,
	 * so this was probably done to cover up allocation bug(s) in the original picopng code!
	 */
	if (size * sizeof(uint32_t) > p->allocsize)
	{
		size_t newsize = size * sizeof(uint32_t) * 2;
		void *data = png_alloc_realloc(p->data, newsize);

		if (data)
		{
			p->allocsize = newsize;
			p->data = (uint8_t *) data;
			p->size = size;
		}
		else
		{
			return 0; // error: not enough memory
		}
	}
	else
	{
		p->size = size;
	}

	return 1;
}


/*==============================================================================
 *
 * resize and give all new elements the value
 */

uint32_t vector8_resizev(vector8_t *p, size_t size, uint8_t value)
{
	size_t oldsize = p->size, i;

	if (!vector8_resize(p, size))
	{
		return 0;
	}

	for (i = oldsize; i < size; i++)
	{
		p->data[i] = value;
	}

	return 1;
}


//==============================================================================

vector8_t *vector8_new(size_t size, uint8_t value)
{
	vector8_t *p = png_alloc_malloc(sizeof(vector8_t));

	p->data = NULL;
	p->size = p->allocsize = 0;

	if (size && !vector8_resizev(p, size, value))
	{
		return NULL;
	}

	return p;
}


//==============================================================================

vector8_t *vector8_copy(vector8_t *p)
{
	vector8_t *q = vector8_new(p->size, 0);
	uint32_t n;

	for (n = 0; n < q->size; n++)
	{
		q->data[n] = p->data[n];
	}

	return q;
}

/*************************************************************************************************/

const uint32_t LENBASE[29]		= { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258 };
const uint32_t LENEXTRA[29]		= { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0 };
const uint32_t DISTBASE[30]		= { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577 };
const uint32_t DISTEXTRA[30]	= { 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };
const uint32_t CLCL[19]			= { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 }; // Code Length Code Lengths

/*************************************************************************************************/

typedef struct
{
	// 2D representation of a huffman tree: The one dimension is "0" or "1", the other contains all
	// nodes and leaves of the tree.
	vector32_t *tree2d;
} HuffmanTree;


//==============================================================================

HuffmanTree *HuffmanTree_new()
{
	HuffmanTree *tree = png_alloc_malloc(sizeof(HuffmanTree));
	tree->tree2d = NULL;

	return tree;
}


//==============================================================================

int HuffmanTree_makeFromLengths(HuffmanTree *tree, const vector32_t *bitlen, uint32_t maxbitlen)
{	// make tree given the lengths
	uint32_t bits, n, i;
	uint32_t numcodes = (uint32_t) bitlen->size, treepos = 0, nodefilled = 0;
	vector32_t *tree1d, *blcount, *nextcode;
	tree1d = vector32_new(numcodes, 0);
	blcount = vector32_new(maxbitlen + 1, 0);
	nextcode = vector32_new(maxbitlen + 1, 0);

	for (bits = 0; bits < numcodes; bits++)
	{
		blcount->data[bitlen->data[bits]]++; // count number of instances of each code length
	}

	for (bits = 1; bits <= maxbitlen; bits++)
	{
		nextcode->data[bits] = (nextcode->data[bits - 1] + blcount->data[bits - 1]) << 1;
	}

	for (n = 0; n < numcodes; n++)
	{
		if (bitlen->data[n] != 0)
		{
			tree1d->data[n] = nextcode->data[bitlen->data[n]]++; // generate all the codes
		}
	}

	// 0x7fff here means the tree2d isn't filled there yet
	vector32_t *tree2d = vector32_new(numcodes * 2, 0x7fff);
	tree->tree2d = tree2d;

	for (n = 0; n < numcodes; n++) // the codes
	{
		for (i = 0; i < bitlen->data[n]; i++) // the bits for this code
		{
			uint32_t bit = (tree1d->data[n] >> (bitlen->data[n] - i - 1)) & 1;

			if (treepos > numcodes - 2)
			{
				return 55;
			}
			if (tree2d->data[2 * treepos + bit] == 0x7fff) // not yet filled in
			{
				if (i + 1 == bitlen->data[n]) // last bit
				{
					tree2d->data[2 * treepos + bit] = n;
					treepos = 0;
				}
				else // addresses are encoded as values > numcodes
				{
					tree2d->data[2 * treepos + bit] = ++nodefilled + numcodes;
					treepos = nodefilled;
				}
			}
			else // subtract numcodes from address to get address value
			{
				treepos = tree2d->data[2 * treepos + bit] - numcodes;
			}
		}
	}

	return 0;
}


//==============================================================================

int HuffmanTree_decode(const HuffmanTree *tree, bool *decoded, uint32_t *result, size_t *treepos, uint32_t bit)
{	// Decodes a symbol from the tree
	const vector32_t *tree2d = tree->tree2d;
	uint32_t numcodes = (uint32_t) tree2d->size / 2;

	if (*treepos >= numcodes)
	{
		return 11; // error: you appeared outside the codetree
	}

	*result = tree2d->data[2 * (*treepos) + bit];
	*decoded = (*result < numcodes);
	*treepos = *decoded ? 0 : *result - numcodes;

	return 0;
}


//==============================================================================

int Inflator_error;

uint32_t Zlib_readBitFromStream(size_t *bitp, const uint8_t *bits)
{
	uint32_t result = (bits[*bitp >> 3] >> (*bitp & 0x7)) & 1;
	(*bitp)++;

	return result;
}


//==============================================================================

uint32_t Zlib_readBitsFromStream(size_t *bitp, const uint8_t *bits, size_t nbits)
{
	uint32_t i, result = 0;

	for (i = 0; i < nbits; i++)
	{
		result += (Zlib_readBitFromStream(bitp, bits)) << i;
	}

	return result;
}


//==============================================================================

void Inflator_generateFixedTrees(HuffmanTree *tree, HuffmanTree *treeD)
{	// get the tree of a deflated block with fixed tree
	size_t i;
	vector32_t *bitlen, *bitlenD;
	bitlen = vector32_new(288, 8);
	bitlenD = vector32_new(32, 5);

	for (i = 144; i <= 255; i++)
	{
		bitlen->data[i] = 9;
	}

	for (i = 256; i <= 279; i++)
	{
		bitlen->data[i] = 7;
	}

	HuffmanTree_makeFromLengths(tree, bitlen, 15);
	HuffmanTree_makeFromLengths(treeD, bitlenD, 15);
}


//==============================================================================

uint32_t Inflator_huffmanDecodeSymbol(const uint8_t *in, size_t *bp, const HuffmanTree *codetree, size_t inlength)
{	// decode a single symbol from given list of bits with given code tree. returns the symbol
	bool decoded = false;
	uint32_t ct = 0;
	size_t treepos = 0;

	for (;;)
	{
		if ((*bp & 0x07) == 0 && (*bp >> 3) > inlength)
		{
			Inflator_error = 10; // error: end reached without endcode

			return 0;
		}

		Inflator_error = HuffmanTree_decode(codetree, &decoded, &ct, &treepos, Zlib_readBitFromStream(bp, in));

		if (Inflator_error)
		{
			return 0; // stop, an error happened
		}

		if (decoded)
		{
			return ct;
		}
	}
}


//==============================================================================

void Inflator_getTreeInflateDynamic(HuffmanTree *tree, HuffmanTree *treeD, const uint8_t *in, size_t *bp, size_t inlength)
{	// get the tree of a deflated block with dynamic tree, the tree itself is also Huffman
	// compressed with a known tree
	size_t i, n;
	HuffmanTree *codelengthcodetree = HuffmanTree_new(); // the code tree for code length codes
	vector32_t *bitlen, *bitlenD;
	bitlen = vector32_new(288, 0);
	bitlenD = vector32_new(32, 0);

	if (*bp >> 3 >= inlength - 2)
	{
		Inflator_error = 49; // the bit pointer is or will go past the memory

		return;
	}

	size_t HLIT = Zlib_readBitsFromStream(bp, in, 5) + 257;	// number of literal/length codes + 257
	size_t HDIST = Zlib_readBitsFromStream(bp, in, 5) + 1;	// number of dist codes + 1
	size_t HCLEN = Zlib_readBitsFromStream(bp, in, 4) + 4;	// number of code length codes + 4
	vector32_t *codelengthcode; // lengths of tree to decode the lengths of the dynamic tree
	codelengthcode = vector32_new(19, 0);

	for (i = 0; i < 19; i++)
	{
		codelengthcode->data[CLCL[i]] = (i < HCLEN) ? Zlib_readBitsFromStream(bp, in, 3) : 0;
	}

	Inflator_error = HuffmanTree_makeFromLengths(codelengthcodetree, codelengthcode, 7);

	if (Inflator_error)
	{
		return;
	}

	size_t replength;

	for (i = 0; i < HLIT + HDIST; )
	{
		uint32_t code = Inflator_huffmanDecodeSymbol(in, bp, codelengthcodetree, inlength);

		if (Inflator_error)
		{
			return;
		}

		if (code <= 15) // a length code
		{
			if (i < HLIT)
			{
				bitlen->data[i++] = code;
			}
			else
			{
				bitlenD->data[i++ - HLIT] = code;
			}
		}
		else if (code == 16) // repeat previous
		{
			if (*bp >> 3 >= inlength)
			{
				Inflator_error = 50; // error, bit pointer jumps past memory

				return;
			}

			replength = 3 + Zlib_readBitsFromStream(bp, in, 2);
			uint32_t value; // set value to the previous code

			if ((i - 1) < HLIT)
			{
				value = bitlen->data[i - 1];
			}
			else
			{
				value = bitlenD->data[i - HLIT - 1];
			}

			for (n = 0; n < replength; n++) // repeat this value in the next lengths
			{
				if (i >= HLIT + HDIST)
				{
					Inflator_error = 13; // error: i is larger than the amount of codes

					return;
				}

				if (i < HLIT)
				{
					bitlen->data[i++] = value;
				}
				else
				{
					bitlenD->data[i++ - HLIT] = value;
				}
			}
		}
		else if (code == 17) // repeat "0" 3-10 times
		{
			if (*bp >> 3 >= inlength)
			{
				Inflator_error = 50; // error, bit pointer jumps past memory

				return;
			}

			replength = 3 + Zlib_readBitsFromStream(bp, in, 3);

			for (n = 0; n < replength; n++) // repeat this value in the next lengths
			{
				if (i >= HLIT + HDIST) {
					Inflator_error = 14; // error: i is larger than the amount of codes

					return;
				}

				if (i < HLIT)
				{
					bitlen->data[i++] = 0;
				}
				else
				{
					bitlenD->data[i++ - HLIT] = 0;
				}
			}
		}
		else if (code == 18) // repeat "0" 11-138 times
		{
			if (*bp >> 3 >= inlength)
			{
				Inflator_error = 50; // error, bit pointer jumps past memory

				return;
			}

			replength = 11 + Zlib_readBitsFromStream(bp, in, 7);

			for (n = 0; n < replength; n++) // repeat this value in the next lengths
			{
				if (i >= HLIT + HDIST)
				{
					Inflator_error = 15; // error: i is larger than the amount of codes

					return;
				}

				if (i < HLIT)
				{
					bitlen->data[i++] = 0;
				}
				else
				{
					bitlenD->data[i++ - HLIT] = 0;
				}
			}
		}
		else
		{
			Inflator_error = 16; // error: an nonexitent code appeared. This can never happen.

			return;
		}
	}

	if (bitlen->data[256] == 0)
	{
		Inflator_error = 64; // the length of the end code 256 must be larger than 0
		return;
	}

	// now we've finally got HLIT and HDIST, so generate the code trees, and the function is done
	Inflator_error = HuffmanTree_makeFromLengths(tree, bitlen, 15);

	if (Inflator_error)
	{
		return;
	}

	Inflator_error = HuffmanTree_makeFromLengths(treeD, bitlenD, 15);

	if (Inflator_error)
	{
		return;
	}
}


//==============================================================================

void Inflator_inflateHuffmanBlock(vector8_t *out, const uint8_t *in, size_t *bp, size_t *pos, size_t inlength, uint32_t btype)
{
	HuffmanTree *codetree, *codetreeD; // the code tree for Huffman codes, dist codes
	codetree = HuffmanTree_new();
	codetreeD = HuffmanTree_new();

	if (btype == 1)
	{
		Inflator_generateFixedTrees(codetree, codetreeD);
	}
	else if (btype == 2)
	{
		Inflator_getTreeInflateDynamic(codetree, codetreeD, in, bp, inlength);

		if (Inflator_error)
		{
			return;
		}
	}
	for (;;)
	{
		uint32_t code = Inflator_huffmanDecodeSymbol(in, bp, codetree, inlength);

		if (Inflator_error)
		{
			return;
		}

		if (code == 256) // end code
		{
			return;
		}
		else if (code <= 255) // literal symbol
		{
			if (*pos >= out->size)
			{
				vector8_resize(out, (*pos + 1) * 2); // reserve more room
			}

			out->data[(*pos)++] = (uint8_t) code;
		}
		else if (code >= 257 && code <= 285) // length code
		{
			size_t length = LENBASE[code - 257], numextrabits = LENEXTRA[code - 257];

			if ((*bp >> 3) >= inlength)
			{
				Inflator_error = 51; // error, bit pointer will jump past memory
				return;
			}

			length += Zlib_readBitsFromStream(bp, in, numextrabits);
			uint32_t codeD = Inflator_huffmanDecodeSymbol(in, bp, codetreeD, inlength);

			if (Inflator_error)
			{
				return;
			}

			if (codeD > 29)
			{
				Inflator_error = 18; // error: invalid dist code (30-31 are never used)

				return;
			}

			uint32_t dist = DISTBASE[codeD], numextrabitsD = DISTEXTRA[codeD];

			if ((*bp >> 3) >= inlength)
			{
				Inflator_error = 51; // error, bit pointer will jump past memory

				return;
			}

			dist += Zlib_readBitsFromStream(bp, in, numextrabitsD);
			size_t start = *pos, back = start - dist; // backwards

			if (*pos + length >= out->size)
			{
				vector8_resize(out, (*pos + length) * 2); // reserve more room
			}

			size_t i;

			for (i = 0; i < length; i++)
			{
				out->data[(*pos)++] = out->data[back++];

				if (back >= start)
				{
					back = start - dist;
				}
			}
		}
	}
}


#ifdef USE_ALL_1
//==============================================================================

void Inflator_inflateNoCompression(vector8_t *out, const uint8_t *in, size_t *bp, size_t *pos, size_t inlength)
{
	while ((*bp & 0x7) != 0)
	{
		(*bp)++; // go to first boundary of byte
	}

	size_t p = *bp / 8;

	if (p >= inlength - 4)
	{
		Inflator_error = 52; // error, bit pointer will jump past memory

		return;
	}

	uint32_t LEN = in[p] + 256 * in[p + 1];
	uint32_t NLEN = in[p + 2] + 256 * in[p + 3];
	p += 4;

	if (LEN + NLEN != 65535)
	{
		Inflator_error = 21; // error: NLEN is not one's complement of LEN

		return;
	}

	if (*pos + LEN >= out->size)
	{
		vector8_resize(out, *pos + LEN);
	}

	if (p + LEN > inlength)
	{
		Inflator_error = 23; // error: reading outside of in buffer

		return;
	}

	uint32_t n;

	for (n = 0; n < LEN; n++)
	{
		out->data[(*pos)++] = in[p++]; // read LEN bytes of literal data
	}

	*bp = p * 8;
}
#endif


//==============================================================================

void Inflator_inflate(vector8_t *out, const vector8_t *in, size_t inpos)
{
	size_t bp = 0, pos = 0; // bit pointer and byte pointer
	Inflator_error = 0;
	uint32_t BFINAL = 0;

	while (!BFINAL && !Inflator_error)
	{
		if (bp >> 3 >= in->size)
		{
			Inflator_error = 52; // error, bit pointer will jump past memory

			return;
		}

		BFINAL = Zlib_readBitFromStream(&bp, &in->data[inpos]);
		uint32_t BTYPE = Zlib_readBitFromStream(&bp, &in->data[inpos]);
		BTYPE += 2 * Zlib_readBitFromStream(&bp, &in->data[inpos]);

/*		if (BTYPE == 3)
		{
			Inflator_error = 20; // error: invalid BTYPE

			return;
		}
		else if (BTYPE == 0)
		{
			Inflator_inflateNoCompression(out, &in->data[inpos], &bp, &pos, in->size);
		}
		else
		{*/
			Inflator_inflateHuffmanBlock(out, &in->data[inpos], &bp, &pos, in->size, BTYPE);
		//}
	}

	if (!Inflator_error)
	{
		vector8_resize(out, pos); // Only now we know the true size of out, resize it to that
	}
}


#ifdef USE_ALL_1
//==============================================================================

int Zlib_decompress(vector8_t *out, const vector8_t *in) // returns error value
{
	if (in->size < 2)
	{
		return 53; // error, size of zlib data too small
	}

	if ((in->data[0] * 256 + in->data[1]) % 31 != 0)
	{
		// error: 256 * in->data[0] + in->data[1] must be a multiple of 31, the FCHECK value is
		// supposed to be made that way
		return 24;
	}

	uint32_t CM		= in->data[0] & 15;
	uint32_t CINFO	= (in->data[0] >> 4) & 15;
	uint32_t FDICT	= (in->data[1] >> 5) & 1;

	if (CM != 8 || CINFO > 7)
	{
		// Error: only compression method 8: inflate with sliding window of 32k is supported by the PNG spec
		return 25;
	}

	if (FDICT != 0)
	{
		// Error: the PNG specification states: "The additional flags shall not specify a preset dictionary."
		return 26;
	}

	Inflator_inflate(out, in, 2);

	return Inflator_error; // note: adler32 checksum was skipped and ignored
}
#endif


//==============================================================================

#define PNG_SIGNATURE	0x0a1a0a0d474e5089ull

#define CHUNK_IHDR		0x52444849
#define CHUNK_IDAT		0x54414449
#define CHUNK_IEND		0x444e4549
#define CHUNK_PLTE		0x45544c50
#define CHUNK_tRNS		0x534e5274

int PNG_error;


#ifdef USE_ALL_1
//==============================================================================

uint32_t PNG_readBitFromReversedStream(size_t *bitp, const uint8_t *bits)
{
	uint32_t result = (bits[*bitp >> 3] >> (7 - (*bitp & 0x7))) & 1;
	(*bitp)++;

	return result;
}


//==============================================================================

uint32_t PNG_readBitsFromReversedStream(size_t *bitp, const uint8_t *bits, uint32_t nbits)
{
	uint32_t i, result = 0;

	for (i = nbits - 1; i < nbits; i--)
	{
		result += ((PNG_readBitFromReversedStream(bitp, bits)) << i);
	}

	return result;
}


//==============================================================================

void PNG_setBitOfReversedStream(size_t *bitp, uint8_t *bits, uint32_t bit)
{
	bits[*bitp >> 3] |= (bit << (7 - (*bitp & 0x7)));
	(*bitp)++;
}
#endif


/* typedef struct Pixel32
{
    union
	{
        struct
		{
            uint8 b, g, r, a;
        };
        uint32 u;
    };
}; */

//==============================================================================

uint32_t PNG_read32bitInt(const uint8_t *buffer)
{
	return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}


#ifdef USE_ALL_1
//==============================================================================

int PNG_checkColorValidity(uint32_t colorType, uint32_t bd) // return type is a LodePNG error code
{
	if ((colorType == 2 || colorType == 4 || colorType == 6))
	{
		if (!(bd == 8 || bd == 16))
		{
			return 37;
		}
		else
		{
			return 0;
		}
	}
	else if (colorType == 0)
	{
		if (!(bd == 1 || bd == 2 || bd == 4 || bd == 8 || bd == 16))
		{
			return 37;
		}
		else
		{
			return 0;
		}
	}
	else if (colorType == 3)
	{
		if (!(bd == 1 || bd == 2 || bd == 4 || bd == 8))
		{
			return 37;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 31; // nonexistent color type
	}
}


//==============================================================================

uint32_t PNG_getBpp(const PNG_info_t *info)
{
	uint32_t bitDepth = info->bitDepth;
	uint32_t colorType = info->colorType;

	if (colorType == 2)
	{
		return (3 * bitDepth);
	}
	else if (colorType >= 4)
	{
		return (colorType - 2) * bitDepth;
	}
	else
	{
		return bitDepth;
	}
}
#endif


//==============================================================================

void PNG_readPngHeader(PNG_info_t *info, const uint8_t *in, size_t inlength)
{
	// read the information from the header and store it in the Info
	if (inlength < 29)
	{
		PNG_error = 27; // error: the data length is smaller than the length of the header
		return;
	}

	if (*(uint64_t *) in != PNG_SIGNATURE)
	{
		PNG_error = 28; // no PNG signature
		return;
	}

	if (*(uint32_t *) &in[12] != CHUNK_IHDR)
	{
		PNG_error = 29; // error: it doesn't start with a IHDR chunk!
		return;
	}

	info->width = PNG_read32bitInt(&in[16]);
	info->height = PNG_read32bitInt(&in[20]);
	info->bitDepth = in[24];
	info->colorType = in[25];
	info->compressionMethod = in[26];

	if (in[26] != 0)
	{
		PNG_error = 32; // error: only compression method 0 is allowed in the specification
		return;
	}

	info->filterMethod = in[27];

	if (in[27] != 0)
	{
		PNG_error = 33; // error: only filter method 0 is allowed in the specification
		return;
	}

	info->interlaceMethod = in[28];

	if (in[28] > 1)
	{
		PNG_error = 34; // error: only interlace methods 0 and 1 exist in the specification
		return;
	}
#ifdef USE_ALL_1
	PNG_error = PNG_checkColorValidity(info->colorType, info->bitDepth);
#endif
}


//==============================================================================

int paethPredictor(int a, int b, int c) // Paeth predicter, used by PNG filter type 4
{
	int p = a + b - c;
	int pa = p > a ? (p - a) : (a - p);
	int pb = p > b ? (p - b) : (b - p);
	int pc = p > c ? (p - c) : (c - p);

	return (pa <= pb && pa <= pc) ? a : (pb <= pc ? b : c);
}


//==============================================================================

// void PNG_unFilterScanline(uint8_t *recon, const uint8_t *scanline, const uint8_t *precon, size_t bytewidth, uint32_t filterType, size_t length)
void PNG_unFilterScanline(uint8_t *recon, const uint8_t *scanline, const uint8_t *precon, size_t bytewidth, uint8_t filterType, size_t length)
{
	size_t i;

	switch (filterType)
	{
		case 0:
				for (i = 0; i < length; i++)
				{
					recon[i] = scanline[i];
				}
		break;

		case 1: for (i = 0; i < bytewidth; i++)
				{
					recon[i] = scanline[i];
				}

				for (i = bytewidth; i < length; i++)
				{
					recon[i] = scanline[i] + recon[i - bytewidth];
				}
		break;

		case 2: if (precon)
				{
					for (i = 0; i < length; i++)
					{
						recon[i] = scanline[i] + precon[i];
					}
				}
				else
				{
					for (i = 0; i < length; i++)
					{
						recon[i] = scanline[i];
					}
				}
		break;

		case 3: if (precon)
				{
					for (i = 0; i < bytewidth; i++)
					{
						recon[i] = scanline[i] + precon[i] / 2;
					}

					for (i = bytewidth; i < length; i++)
					{
						recon[i] = scanline[i] + ((recon[i - bytewidth] + precon[i]) / 2);
					}
				}
				else
				{
					for (i = 0; i < bytewidth; i++)
					{
						recon[i] = scanline[i];
					}

					for (i = bytewidth; i < length; i++)
					{
						recon[i] = scanline[i] + recon[i - bytewidth] / 2;
					}
				}
		break;

		case 4: if (precon)
				{
					for (i = 0; i < bytewidth; i++)
					{
						recon[i] = (uint8_t) (scanline[i] + paethPredictor(0, precon[i], 0));
					}

					for (i = bytewidth; i < length; i++)
					{
						recon[i] = (uint8_t) (scanline[i] + paethPredictor(recon[i - bytewidth], precon[i], precon[i - bytewidth]));
					}
				}
				else
				{
					for (i = 0; i < bytewidth; i++)
					{
						recon[i] = scanline[i];
					}

					for (i = bytewidth; i < length; i++)
					{
						recon[i] = (uint8_t) (scanline[i] + paethPredictor(recon[i - bytewidth], 0, 0));
					}
				}
		break;

		default:	PNG_error = 36; // error: nonexistent filter type given
					return;
	}
}

#ifdef USE_ALL_1
/*==============================================================================
 * filter and reposition the pixels into the output when the image is Adam7 interlaced. This
 * function can only do it after the full image is already decoded. The out buffer must have
 * the correct allocated memory size already.
 */

void PNG_adam7Pass(uint8_t *out, uint8_t *linen, uint8_t *lineo, const uint8_t *in, uint32_t w,
				   size_t passleft, size_t passtop, size_t spacex, size_t spacey, size_t passw, size_t passh, uint32_t bpp)
{
	if (passw)
	{
		size_t bytewidth = (bpp + 7) / 8, linelength = 1 + ((bpp * passw + 7) / 8);
		uint32_t y = 0;

		for (; y < passh; y++)
		{
			size_t i, b;
			uint8_t filterType = in[y * linelength];
			uint8_t *prevline = (y == 0) ? 0 : lineo;
			PNG_unFilterScanline(linen, &in[y * linelength + 1], prevline, bytewidth, filterType, (w * bpp + 7) / 8);

			if (!PNG_error)
			{
				if (bpp >= 8)
				{
					for (i = 0; i < passw; i++)
					{
						for (b = 0; b < bytewidth; b++) // b = current byte of this pixel
						{
							out[bytewidth * w * (passtop + spacey * y) + bytewidth * (passleft + spacex * i) + b] = linen[bytewidth * i + b];
						}
					}
				}
				else
				{
					for (i = 0; i < passw; i++)
					{
						size_t obp = bpp * w * (passtop + spacey * y) + bpp * (passleft + spacex * i);
						size_t bp = i * bpp;

						for (b = 0; b < bpp; b++)
						{
							PNG_setBitOfReversedStream(&obp, out, PNG_readBitFromReversedStream(&bp, linen));
						}
					}
				}
			}

			uint8_t *temp = linen;
			linen = lineo;
			lineo = temp; // swap the two buffer pointers "line old" and "line new"
		}
	}
}


/*==============================================================================
 * Converts any color type to 32-bit. 
 * Returns a LodePNG error code
 */

int PNG_convert(const PNG_info_t *info, vector8_t *out, const uint8_t *in)
{
	size_t c, i;
	uint32_t bitDepth, colorType;
	bitDepth = info->bitDepth;
	colorType = info->colorType;
	size_t numpixels = info->width * info->height;
	vector8_resize(out, numpixels * 4);
	uint8_t *out_data = out->size ? out->data : 0;

	size_t  bp = 0;
	
	if (bitDepth == 8 && colorType == 0) // Greyscale
	{
		for (i = 0; i < numpixels; i++)
		{
			out_data[4 * i + 0] = out_data[4 * i + 1] = out_data[4 * i + 2] = in[i];
			out_data[4 * i + 3] = (info->key_defined && (in[i] == info->key_r)) ? 0 : 255;
		}
	}
	else if (bitDepth == 8 && colorType == 2) // RGB color
	{
		for (i = 0; i < numpixels; i++)
		{
			for (c = 0; c < 3; c++)
			{
				out_data[4 * i + c] = in[3 * i + c];
			}

			out_data[4 * i + 3] = (info->key_defined && (in[3 * i + 0] == info->key_r) && (in[3 * i + 1] == info->key_g) && (in[3 * i + 2] == info->key_b)) ? 0 : 255;
		}
	}
	else if (bitDepth == 8 && colorType == 3) // indexed color (palette)
	{
		for (i = 0; i < numpixels; i++)
		{
			if (4U * in[i] >= info->palette->size)
			{
				return 46;
			}

			for (c = 0; c < 4; c++) // Get rgb colors from the palette
			{
				out_data[4 * i + c] = info->palette->data[4 * in[i] + c];
			}
		}
	}
	else if (bitDepth == 8 && colorType == 4) // Greyscale with alpha
	{
		for (i = 0; i < numpixels; i++)
		{
			out_data[4 * i + 0] = out_data[4 * i + 1] = out_data[4 * i + 2] = in[2 * i + 0];
			out_data[4 * i + 3] = in[2 * i + 1];
		}
	}
	else if (bitDepth == 8 && colorType == 6)
	{
		for (i = 0; i < numpixels; i++)
		{
			for (c = 0; c < 4; c++)
			{
				out_data[4 * i + c] = in[4 * i + c]; // RGB with alpha
			}
		}
	}
	else if (bitDepth == 16 && colorType == 0) // Greyscale
	{
		for (i = 0; i < numpixels; i++)
		{
			out_data[4 * i + 0] = out_data[4 * i + 1] = out_data[4 * i + 2] = in[2 * i];
			out_data[4 * i + 3] = (info->key_defined && (256U * in[i] + in[i + 1] == info->key_r)) ? 0 : 255;
		}
	}
	else if (bitDepth == 16 && colorType == 2) // RGB color
	{
		for (i = 0; i < numpixels; i++)
		{
			for (c = 0; c < 3; c++)
			{
				out_data[4 * i + c] = in[6 * i + 2 * c];
			}

			out_data[4 * i + 3] = (info->key_defined &&
								   (256U * in[6 * i + 0] + in[6 * i + 1] == info->key_r) &&
								   (256U * in[6 * i + 2] + in[6 * i + 3] == info->key_g) &&
								   (256U * in[6 * i + 4] + in[6 * i + 5] == info->key_b)) ? 0 : 255;
		}
	}
	else if (bitDepth == 16 && colorType == 4) // Greyscale with alpha
	{
		for (i = 0; i < numpixels; i++)
		{
			out_data[4 * i + 0] = out_data[4 * i + 1] = out_data[4 * i + 2] = in[4 * i]; // msb
			out_data[4 * i + 3] = in[4 * i + 2];
		}
	}
	else if (bitDepth == 16 && colorType == 6)
	{
		for (i = 0; i < numpixels; i++)
		{
			for (c = 0; c < 4; c++)
			{
				out_data[4 * i + c] = in[8 * i + 2 * c]; // RGB with alpha
			}
		}
	}
	else if (bitDepth < 8 && colorType == 0) // Greyscale
	{
		for (i = 0; i < numpixels; i++)
		{
			uint32_t value = (PNG_readBitsFromReversedStream(&bp, in, bitDepth) * 255) / ((1 << bitDepth) - 1); // Scale value from 0 to 255
			out_data[4 * i + 0] = out_data[4 * i + 1] = out_data[4 * i + 2] = (uint8_t) value;
			out_data[4 * i + 3] = (info->key_defined && value && (((1U << bitDepth) - 1U) == info->key_r) && ((1U << bitDepth) - 1U)) ? 0 : 255;
		}
	}
	else if (bitDepth < 8 && colorType == 3) // Palette
	{
		for (i = 0; i < numpixels; i++)
		{
			uint32_t value = PNG_readBitsFromReversedStream(&bp, in, bitDepth);

			if (4 * value >= info->palette->size)
			{
				return 47;
			}

			for (c = 0; c < 4; c++) // Get RGB colors from the palette
			{
				out_data[4 * i + c] = info->palette->data[4 * value + c];
			}
		}
	}
	return 0;
}
#endif


//==============================================================================

PNG_info_t *PNG_info_new()
{
	PNG_info_t *info = png_alloc_malloc(sizeof(PNG_info_t));
	uint32_t i;

	for (i = 0; i < sizeof(PNG_info_t); i++)
	{
		((uint8_t *) info)[i] = 0;
	}

	info->palette	= vector8_new(0, 0);
	info->image		= vector8_new(0, 0);

	return info;
}


//==============================================================================

PNG_info_t *PNG_decode(const uint8_t *in, uint32_t size)
{
	if (size == 0 || in == 0)
	{
		PNG_error = 48; // the given data is empty
		return NULL;
	}

	PNG_error = 0;
	PNG_info_t *info = PNG_info_new();
	PNG_readPngHeader(info, in, size);

	if (PNG_error)
	{
		return NULL;
	}

	size_t pos = 33; // first byte of the first chunk after the header
	vector8_t *idat = NULL; // the data from IDAT chunks
	bool IEND = false;
	bool known_type = true;
	info->key_defined = false;

	/*
	 * Loop through the chunks, ignoring unknown chunks and stopping at IEND chunk.
	 * IDAT data is put at the start of the in buffer
	 */
	while (!IEND)
	{
		size_t i;

		if (pos + 8 >= size)
		{
			PNG_error = 30; // error: size of the in buffer too small to contain next chunk
			return NULL;
		}

		size_t chunkLength = PNG_read32bitInt(&in[pos]);
		pos += 4;

		if (chunkLength > 0x7fffffff)
		{
			PNG_error = 63;
			return NULL;
		}

		if (pos + chunkLength >= size)
		{
			PNG_error = 35; // error: size of the in buffer too small to contain next chunk
			return NULL;
		}

		uint32_t chunkType = *(uint32_t *) &in[pos];

		if (chunkType == CHUNK_IDAT) // IDAT: compressed image data chunk
		{
			size_t offset = 0;

			if (idat)
			{
				offset = idat->size;
				vector8_resize(idat, offset + chunkLength);
			}
			else
			{
				idat = vector8_new(chunkLength, 0);
			}

			for (i = 0; i < chunkLength; i++)
			{
				idat->data[offset + i] = in[pos + 4 + i];
			}

			pos += (4 + chunkLength);
		}
		else if (chunkType == CHUNK_IEND) // IEND
		{
			pos += 4;
			IEND = true;
		}
#ifdef USE_ALL_1
		else if (chunkType == CHUNK_PLTE) // PLTE: palette chunk
		{
			size_t j;
			pos += 4; // go after the 4 letters
			vector8_resize(info->palette, 4 * (chunkLength / 3));

			if (info->palette->size > (4 * 256))
			{
				PNG_error = 38; // error: palette too big
				return NULL;
			}

			for (i = 0; i < info->palette->size; i += 4)
			{
				for (j = 0; j < 3; j++)
				{
					info->palette->data[i + j] = in[pos++]; // RGB
				}

				info->palette->data[i + 3] = 255; // alpha
			}
		}
		else if (chunkType == CHUNK_tRNS) // tRNS: palette transparency chunk
		{
			pos += 4; // go after the 4 letters

			if (info->colorType == 3)
			{
				if (4 * chunkLength > info->palette->size)
				{
					PNG_error = 39; // error: more alpha values given than there are palette entries
					return NULL;
				}

				for (i = 0; i < chunkLength; i++)
				{
					info->palette->data[4 * i + 3] = in[pos++];
				}
			}
			else if (info->colorType == 0)
			{
				if (chunkLength != 2)
				{
					PNG_error = 40; // error: this chunk must be 2 bytes for greyscale image
					return NULL;
				}

				info->key_defined = true;
				info->key_r = info->key_g = info->key_b = 256 * in[pos] + in[pos + 1];
				pos += 2;
			}
			else if (info->colorType == 2)
			{
				if (chunkLength != 6)
				{
					PNG_error = 41; // error: this chunk must be 6 bytes for RGB image
					return NULL;
				}

				info->key_defined = true;
				info->key_r = 256 * in[pos] + in[pos + 1];
				pos += 2;
				info->key_g = 256 * in[pos] + in[pos + 1];
				pos += 2;
				info->key_b = 256 * in[pos] + in[pos + 1];
				pos += 2;
			}
			else
			{
				PNG_error = 42; // error: tRNS chunk not allowed for other color models
				return NULL;
			}
		}
#endif
		else // it's not an implemented chunk type, so ignore it: skip over the data
		{
			if (!(in[pos + 0] & 32))
			{
				// error: unknown critical chunk (5th bit of first byte of chunk type is 0)
				PNG_error = 69;
				return NULL;
			}

			pos += (chunkLength + 4); // skip 4 letters and uninterpreted data of unimplemented chunk
			known_type = false;
		}

		pos += 4; // step over CRC (which is ignored)
	}

#if USE_ALL_1
	uint32_t bpp = PNG_getBpp(info);
#else
	uint32_t bpp = 32;
#endif
	vector8_t *scanlines; // now the out buffer will be filled
	scanlines = vector8_new(((info->width * (info->height * bpp + 7)) / 8) + info->height, 0);
#if USE_ALL_1
	PNG_error = Zlib_decompress(scanlines, idat);
#else
	Inflator_inflate(scanlines, idat, 2);
	PNG_error = Inflator_error;
#endif

	if (PNG_error)
	{
		return NULL; // stop if the zlib decompressor returned an error
	}

	size_t bytewidth = (bpp + 7) / 8, outlength = (info->height * info->width * bpp + 7) / 8;
	vector8_resize(info->image, outlength); // time to fill the out buffer
	uint8_t *out_data = outlength ? info->image->data : 0;

#ifdef USE_ALL_1
	if (info->interlaceMethod == 0) // no interlace, just filter
	{
		size_t obp, bp;
#endif
		size_t y = 0;
		size_t linestart = 0;
		// length in bytes of a scanline, excluding the filtertype byte
		size_t linelength = (info->width * bpp + 7) / 8;
#ifdef USE_ALL_1
		if (bpp >= 8) // byte per byte
		{
#endif
			for (y = 0; y < info->height; y++)
			{
//				uint32_t filterType = scanlines->data[linestart];
				uint8_t filterType = scanlines->data[linestart];
				const uint8_t *prevline;
				prevline = (y == 0) ? 0 : &out_data[(y - 1) * info->width * bytewidth];
				PNG_unFilterScanline(&out_data[linestart - y], &scanlines->data[linestart + 1], prevline, bytewidth, filterType, linelength);

				if (PNG_error)
				{
					return NULL;
				}

				linestart += (1 + linelength); // go to start of next scanline
			}
#ifdef USE_ALL_1
		}
		else // less than 8 bits per pixel, so fill it up bit per bit
		{
			vector8_t *templine; // only used if bpp < 8
			templine = vector8_new((info->width * bpp + 7) >> 3, 0);

			for (y = 0, obp = 0; y < info->height; y++)
			{
				// uint32_t filterType = scanlines->data[linestart];
				uint8_t filterType = scanlines->data[linestart];
				const uint8_t *prevline;
				prevline = (y == 0) ? 0 : &out_data[(y - 1) * info->width * bytewidth];
				PNG_unFilterScanline(templine->data, &scanlines->data[linestart + 1], prevline, bytewidth, filterType, linelength);

				if (PNG_error)
				{
					return NULL;
				}

				for (bp = 0; bp < info->width * bpp;)
				{
					PNG_setBitOfReversedStream(&obp, out_data, PNG_readBitFromReversedStream(&bp, templine->data));
				}

				linestart += (1 + linelength); // go to start of next scanline
			}
		}
	}
	else // interlaceMethod is 1 (Adam7)
	{
		int i;
		size_t passw[7] =
		{
			(info->width + 7) / 8, (info->width + 3) / 8, (info->width + 3) / 4,
			(info->width + 1) / 4, (info->width + 1) / 2, (info->width + 0) / 2,
			(info->width + 0) / 1
		};

		size_t passh[7] =
		{
			(info->height + 7) / 8, (info->height + 7) / 8, (info->height + 3) / 8,
			(info->height + 3) / 4, (info->height + 1) / 4, (info->height + 1) / 2,
			(info->height + 0) / 2
		};

		size_t passstart[7] = { 0 };
		size_t pattern[28] = { 0, 4, 0, 2, 0, 1, 0, 0, 0, 4, 0, 2, 0, 1, 8, 8, 4, 4, 2, 2, 1, 8, 8,
				8, 4, 4, 2, 2 }; // values for the adam7 passes

		for (i = 0; i < 6; i++)
		{
			passstart[i + 1] = passstart[i] + passh[i] * ((passw[i] ? 1 : 0) + (passw[i] * bpp + 7) / 8);
		}

		vector8_t *scanlineo, *scanlinen; // "old" and "new" scanline
		scanlineo = vector8_new((info->width * bpp + 7) / 8, 0);
		scanlinen = vector8_new((info->width * bpp + 7) / 8, 0);

		for (i = 0; i < 7; i++)
		{
			PNG_adam7Pass(out_data, scanlinen->data, scanlineo->data, &scanlines->data[passstart[i]],
					info->width, pattern[i], pattern[i + 7], pattern[i + 14], pattern[i + 21],
					passw[i], passh[i], bpp);
		}
	}

	if (info->colorType != 6 || info->bitDepth != 8) // conversion needed
	{
		vector8_t *copy = vector8_copy(info->image); // xxx: is this copy necessary?
		PNG_error = PNG_convert(info, info->image, copy->data);
	}
#endif
	return info;
}
