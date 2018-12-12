#include<stdio.h>
#include<stdlib.h>
#include "BlockDescriptor.h"
#include "DebugStatement.h"
#include "MemoryAllocator.h"
#include"FixedSizeAllocator.h"
#include<assert.h>
#pragma once

#define DEFAULT_ALIGNMENT 4


MemoryAllocator::MemoryAllocator(void * memPointer, size_t heapSize, unsigned int numDescriptors)
{
	DEBUG_PRINT("constructor called");
	heapFront = _aligned_malloc(heapSize, DEFAULT_ALIGNMENT);
	assert(heapFront != NULL);
	
	heapRemaining = heapSize;
	heapBack = reinterpret_cast<unsigned char*>(heapFront) + heapSize;
	setDescriptors(numDescriptors);
	size8 = new FSA(1000, this, 8);   // Initialising the fixed size allocators from the heap
	size16 = new FSA(1000, this, 16);
	DEBUG_PRINT("constructor completed");
}

MemoryAllocator * MemoryAllocator::makeHeap(void * memPointer, size_t heapSize, unsigned int numDescriptors)
{
	DEBUG_PRINT("make heap function");
	return new MemoryAllocator(memPointer, heapSize, numDescriptors);
}

void MemoryAllocator::setDescriptors(const unsigned int numDescriptors)
{
	BlockDescriptor * tempBD = reinterpret_cast<BlockDescriptor*>(reinterpret_cast<unsigned char*>(heapBack) - (sizeof(BlockDescriptor) * numDescriptors));
	DEBUG_PRINT("init block descroiptor list");
	assert(tempBD > heapFront);

	tempBD->previous = NULL;
	tempBD->baseAddress = NULL;
	tempBD->accessAddress = NULL;
	tempBD->size = 0;
	tempBD->next = NULL;

	BlockDescriptor * temp = tempBD;

	for (size_t i = 0; i < numDescriptors - 1; i++)
	{
		BlockDescriptor * insert = temp + 1;

		temp->next = insert;
		insert->previous = temp;
		insert->next = NULL;
		insert->baseAddress = NULL;
		insert->accessAddress = NULL;
		insert->size = 0;
		temp = insert;
	}
	blockDescriptors = tempBD;
	heapRemaining -= sizeof(BlockDescriptor) * numDescriptors;
	BlockDescriptor * firstFree;
	firstFree = blockDescriptors;
	blockDescriptors = blockDescriptors->next;
	firstFree->previous = NULL;
	firstFree->next = NULL;
	firstFree->baseAddress = heapFront;
	firstFree->accessAddress = NULL;
	firstFree->size = heapRemaining;
	DEBUG_PRINT("put one in free");
	insertToFree(firstFree);
	DEBUG_PRINT("list complete and free list initialised with heap");
}

void MemoryAllocator::insertToFree(BlockDescriptor * toInsert)
{
	BlockDescriptor * tempBD = freeBlocks;
	DEBUG_PRINT("inserting to free");

	if (freeBlocks == 0)
	{
		DEBUG_PRINT("FIRST TIME");
		freeBlocks = toInsert;
		freeBlocks->previous = NULL;
		freeBlocks->next = NULL;
	}
	else
	{
		DEBUG_PRINT("NOT FIRST TIME");
		while (tempBD->next != NULL)
		{
			tempBD = tempBD->next;
		}
		tempBD->next = toInsert;
		toInsert->previous = tempBD;
	}
}

void MemoryAllocator::insertToUnused(BlockDescriptor * toInsert)
{
	assert(toInsert != blockDescriptors);
	DEBUG_PRINT("insert to BD list");
	toInsert->baseAddress = NULL;
	toInsert->accessAddress = NULL;
	toInsert->size = 0;
	toInsert->next = NULL;
	toInsert->previous = NULL;

	if (blockDescriptors == NULL)
	{
		blockDescriptors = toInsert;
		blockDescriptors->previous = NULL;
	}
	else
	{
		toInsert->next = blockDescriptors;
		blockDescriptors->previous = toInsert;
		blockDescriptors = toInsert;
	}
}

void MemoryAllocator::insertToUsed(BlockDescriptor * toInsert)
{
	DEBUG_PRINT("inserting to used");

	BlockDescriptor * tempBD = usedBlocks;

	if (usedBlocks == 0)
	{
		DEBUG_PRINT("used was empty");
		toInsert->previous = NULL;
		toInsert->next = NULL;
		usedBlocks = toInsert;
	}
	else
	{
		while (tempBD->next != NULL)
		{
			tempBD = tempBD->next;
		}
		tempBD->next = toInsert;
		toInsert->previous = tempBD;
	}
}

void * MemoryAllocator::alloc(const size_t blockSize)
{
	return alloc(blockSize, DEFAULT_ALIGNMENT);
}

void * MemoryAllocator::alloc(size_t blockSize, unsigned int alignmentValue)
{
	DEBUG_PRINT("alloc %d", blockSize);
	if (blockSize <= 8 && size8->hasSpace())
	{
		return size8->getBlock();
	}
	else if ((blockSize > 8) && (blockSize <= 16) && size16->hasSpace())
	{
		return size16->getBlock();
	}
	else 
	{
		if (freeBlocks == NULL)
		{
			DEBUG_PRINT("no free blocks");
			return nullptr;
		}
		BlockDescriptor * tempBD = findFreeBlock(blockSize);

		if (tempBD == NULL)
		{
			DEBUG_PRINT("no free block big enough");
			return nullptr;
		}

		BlockDescriptor * dividedBlock = divideBlock(tempBD, blockSize, alignmentValue);

		if (dividedBlock == nullptr)
			return nullptr;

		//dividedBlock->size = blockSize;

		insertToUsed(dividedBlock);
		return dividedBlock->baseAddress;
	}
}



BlockDescriptor * MemoryAllocator::findFreeBlock(const size_t blockSize) const
{
	DEBUG_PRINT("finding big enough free block");
	BlockDescriptor * tempBD = freeBlocks;
	size_t reqSize = blockSize;
	while (tempBD != NULL)
	{
		if (tempBD->size >= reqSize)
		{
			DEBUG_PRINT("found!");
			return tempBD;
		}
		else
		{
			tempBD = tempBD->next;
		}

	}
	DEBUG_PRINT("not found:(");
	return NULL;
}

BlockDescriptor * MemoryAllocator::divideBlock(BlockDescriptor * toDivide, const size_t blockSize, const unsigned int alignmentValue)
{
	DEBUG_PRINT("dividing bigger block");
	if (toDivide->size == blockSize)
	{
		DEBUG_PRINT("the block was EXACTLY the right size wew");
		removeBlock(toDivide->baseAddress, freeBlocks);
		return toDivide;
		//insertToUsed(toDivide);
	}
	if (blockSize == 462)
	{
		int x = 0;
	}
	BlockDescriptor * tempBD = blockDescriptors;

	if (tempBD == nullptr)
		return nullptr;


	blockDescriptors = blockDescriptors->next;

	tempBD->next = NULL;
	tempBD->previous = NULL;

	tempBD->baseAddress = toDivide->baseAddress;
	heapRemaining -= blockSize;

	tempBD->size = blockSize;

	toDivide->size -= blockSize;
	toDivide->baseAddress = static_cast<unsigned char*>(toDivide->baseAddress) + tempBD->size;

	/*if (toDivide->size == 0)
	{
	DEBUG_PRINT("the block was EXACTLY the right size wew");
	removeBlock(toDivide, freeBlocks);
	insertToUsed(toDivide);
	}*/
	return tempBD;
}

BlockDescriptor * MemoryAllocator::removeBlock(const void * address, BlockDescriptor * listName)
{
	DEBUG_PRINT("removing from list");

	BlockDescriptor * tempBD = listName;

	while (tempBD != NULL)
	{
		if (tempBD->baseAddress == address)
		{
			DEBUG_PRINT("FOUND");
			if (tempBD->previous == NULL && tempBD->next != NULL)
			{
				if (tempBD == freeBlocks)
				{
					freeBlocks = tempBD->next;
				}
				else if (tempBD == blockDescriptors)
				{
					blockDescriptors = tempBD->next;
				}
				else if (tempBD == usedBlocks)
				{
					usedBlocks = tempBD->next;
				}

				tempBD->next->previous = NULL;
				tempBD->next = NULL;
			}
			else if (tempBD->previous != NULL && tempBD->next != NULL)
			{
				tempBD->next->previous = tempBD->previous;
				tempBD->previous->next = tempBD->next;

				tempBD->next = NULL;
				tempBD->previous = NULL;
			}
			else if (tempBD->previous != NULL && tempBD->next == NULL)
			{
				tempBD->previous->next = NULL;
				tempBD->previous = NULL;
			}
			else if (tempBD->previous == NULL && tempBD->next == NULL)
			{
				makeNull(tempBD);
			}
			return tempBD;
		}
		else
		{
			tempBD = tempBD->next;
		}
	}
	DEBUG_PRINT("not found :(");
	return nullptr;
}

void MemoryAllocator::makeNull(BlockDescriptor *toNull)
{
	if (toNull == freeBlocks)
	{
		freeBlocks = NULL;
	}
	else if (toNull == blockDescriptors)
	{
		blockDescriptors = NULL;
	}
	else if (toNull == usedBlocks)
	{
		usedBlocks = NULL;
	}
}




void MemoryAllocator::garbageCollection()
{
	BlockDescriptor * tempBD = freeBlocks;

	while (tempBD != NULL)
	{
		unsigned char * toFind = reinterpret_cast<unsigned char *>(tempBD->baseAddress) + tempBD->size;
		BlockDescriptor * foundBlock = findBlock(toFind, freeBlocks);
		if (foundBlock == NULL || foundBlock->baseAddress == tempBD->baseAddress)
		{
			tempBD = tempBD->next;
		}
		else
		{
			fuseBlocks(tempBD, foundBlock);
			DEBUG_PRINT("fusing");
		}
	}
}

BlockDescriptor * MemoryAllocator::findBlock(const void * address, BlockDescriptor * listName) const
{
	BlockDescriptor * tempBD = listName;
	DEBUG_PRINT("searching for a block...");

	while (tempBD != NULL)
	{
		if (tempBD->baseAddress == address)
		{
			DEBUG_PRINT("found");
			return tempBD;
		}
		else
		{
			tempBD = tempBD->next;
		}
	}
	DEBUG_PRINT("not found");
	return nullptr;
}

void MemoryAllocator::fuseBlocks(BlockDescriptor * blockOne, BlockDescriptor * blockTwo)
{
	size_t totalSize = blockOne->size + blockTwo->size;
	printf("fusing %d + %d = %d", blockOne->size, blockTwo->size, totalSize);
	blockOne->size = totalSize;
	blockTwo->size = 0;
	removeBlock(blockTwo->baseAddress, freeBlocks);
	insertToUnused(blockTwo);
}

bool MemoryAllocator::isAddressInHeap(void * address) const
{
	DEBUG_PRINT("looking for address in heap");
	if (address <= heapBack && address >= heapFront)
	{
		DEBUG_PRINT("it is");
		return true;
	}
	else
	{
		DEBUG_PRINT("it's not");
		return false;
	}
}

bool MemoryAllocator::isAddressAllocated(void * address) const
{
	BlockDescriptor * tempBD = usedBlocks;
	DEBUG_PRINT("checking if an address is allocated");
	if (size16->contains(address) || size8->contains(address))
		return true;
	else {
		while (tempBD != NULL)
		{
			if (tempBD->baseAddress == address)
			{
				DEBUG_PRINT("it is");
				return true;
			}
			else
			{

				tempBD = tempBD->next;
			}
		}
		DEBUG_PRINT("it's not");
		return false;
	}
}

size_t MemoryAllocator::getBigBlockSize()
{
	size_t currentBig = 0;
	BlockDescriptor * tempBD = freeBlocks;
	DEBUG_PRINT("checking what the largest avalable block is");

	while (tempBD != NULL)
	{
		if (tempBD->size > currentBig)
		{
			currentBig = tempBD->size;
		}
		else
		{
			tempBD = tempBD->next;
		}
	}
	return currentBig;
}

size_t MemoryAllocator::getFreeMemory()
{
	return heapRemaining;
}

MemoryAllocator::~MemoryAllocator()
{
	DEBUG_PRINT("BOOM");
	size16->~FSA();
	size8->~FSA();
	_aligned_free(heapFront);
}

bool MemoryAllocator::dealloc(const void * toFree)
{
	if (size8->isAllocated(toFree))
	{
		DEBUG_PRINT("dealloc from size8");
		return size8->returnBlock(toFree);
	}
	else if (size16->isAllocated(toFree))
	{
		DEBUG_PRINT("dealloc from size16");
		return size16->returnBlock(toFree);
	}
	else {
		BlockDescriptor * tempBD = removeBlock(toFree, usedBlocks);
		printf("dealloc time = %d", tempBD->size);
		assert(tempBD != NULL);

		if (tempBD == NULL)
		{
			DEBUG_PRINT("there wasn't anything to dealloc");
			return false;
		}

		insertToFree(tempBD);
		printf("\n free list\n");
		DEBUG_PRINT("successful dealloc");
		return true;
	}
}
