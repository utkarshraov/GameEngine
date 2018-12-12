#pragma once
#include "MemoryAllocator.h"
#include "BitArray.h"
#include<vector>
#include<assert.h>

class FSA
{
public:
	FSA(size_t numBlocks, MemoryAllocator * heap, size_t blockSize)
	{
		assert(numBlocks);
		assert(heap);
		assert(blockSize);
		thisHeap = heap;
		FSAStart = heap->alloc((blockSize * numBlocks));
		uintptr_t temp = reinterpret_cast<uintptr_t>(FSAStart) + (blockSize*numBlocks);
		FSAEnd = reinterpret_cast<void*>(temp);
		totalBlocks = numBlocks;
		blocksRemaining = numBlocks;
		blockWidth = blockSize;
		bArray = BitArray::Create(numBlocks,0, thisHeap);
		memAddress = new void*[numBlocks];
		setAddresses();
		
		
	}
	~FSA()
	{
#ifdef _DEBUG
		if (blocksRemaining < totalBlocks)
		{
			DEBUG_PRINT("There are still allocations left!! unsafe destructor");
		}
#endif
		thisHeap->dealloc(FSAStart);
	}
	void * getBlock();
	bool returnBlock(const void * pointer);
	bool contains(const void * pointer) const;
	bool isAllocated(const void * pointer) const;
	bool hasSpace() {
		if (blocksRemaining>0)
			return true;
		else
			return false;
	}
private:
	BitArray * bArray;
	MemoryAllocator * thisHeap;
	size_t blockWidth;
	void ** memAddress;
	size_t totalBlocks;
	size_t blocksRemaining;
	void * FSAStart;
	void * FSAEnd;
	void setAddresses();
};