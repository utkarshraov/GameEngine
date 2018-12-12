#pragma once
#include<stdlib.h>
#include<cstdint>
#include<string.h>
#include<assert.h>
#include<intrin.h>
#include"MemoryManagement.h"
#include"MemoryAllocator.h"

class BitArray
{
public:
	BitArray(size_t numBits, bool initToZero, MemoryAllocator * heap)
	{
		assert(numBits && "bit array size can't be 0");
		assert(heap && "invalid heap passed");
#ifdef _WIN32
		bits = reinterpret_cast<uint32_t *>(operator new(numBits / bitPerByte, heap));
#elif _WIN64
		bits = reinterpret_cast<uint64_t *>(operator new(numBits / bitPerByte, heap));
#endif

		assert(bits);
		memset(bits, initToZero ? 0 : 1, numBits / bitPerByte);
		sizeOfArray = numBits;
		thisHeap = heap;
	}
	static BitArray * Create(size_t numBits, bool initToZero, MemoryAllocator * heap);
	~BitArray() {
	};
	size_t firstSet();
	size_t firstClear();
	bool isClear(size_t index) const;
	bool isSet(size_t index) const;
	void setBit(size_t index);
	void clearBit(size_t index);
	void setAll(bool setValue);
	bool areAllClear();
	bool areAllSet();
private:
#ifdef _WIN32
		uint32_t * bits;
		const size_t bitPerByte = 32;
#elif _WIN64
		uint64_t * bits;
		const size_t bitPerByte = 64;
#endif
		size_t sizeOfArray;
		MemoryAllocator * thisHeap;
};