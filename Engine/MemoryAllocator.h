#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "BlockDescriptor.h"
#include "DebugStatement.h"

class FSA;

class MemoryAllocator {
public:

	MemoryAllocator(void * memPointer,size_t heapSize, unsigned int numDescriptors);
	~MemoryAllocator();

	static MemoryAllocator* makeHeap(void * memPointer, size_t heapSize, unsigned int numDescriptors);

	void * alloc(size_t blockSize);
	void * alloc(size_t blockSize, unsigned int alignmentValue);


	bool dealloc(const void * pointer);

	void garbageCollection();

	bool isAddressInHeap(void * address) const;
	bool isAddressAllocated(void * address) const;

	size_t getBigBlockSize();
	size_t getFreeMemory();


private:

	void * heapFront;
	void * heapBack;
	size_t heapRemaining = 0;
	void setDescriptors(const unsigned int numDescriptors);
	FSA * size8;
	FSA * size16;

	void insertToUnused(BlockDescriptor * toInsert);
	void insertToFree(BlockDescriptor * toInsert);
	void insertToUsed(BlockDescriptor * toInsert);

	BlockDescriptor * freeBlocks = 0;
	BlockDescriptor * usedBlocks = 0;
	BlockDescriptor * blockDescriptors = 0;

	BlockDescriptor * findFreeBlock(const size_t blockSize) const;
	BlockDescriptor * divideBlock(BlockDescriptor * toDivide, const size_t blockSize, const unsigned int alignmentValue);
	BlockDescriptor * removeBlock(const void * address, BlockDescriptor * listName);

	void makeNull(BlockDescriptor * toNull);

	BlockDescriptor * findBlock(const void * address, BlockDescriptor * listName) const;

	void fuseBlocks(BlockDescriptor * blockOne, BlockDescriptor * blockTwo);

	

};
