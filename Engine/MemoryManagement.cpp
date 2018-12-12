#pragma once
#include<stdlib.h>
#include "MemoryAllocator.h"
#include<assert.h>
#include "MemoryManagement.h"



void * operator new(size_t size, MemoryAllocator * heap, unsigned int alignment)
{
	assert(heap != NULL);
	return heap->alloc(size, alignment);
}

void * operator new(size_t size, MemoryAllocator * heap)
{
	assert(heap != NULL);
	return heap->alloc(size, 4);
}

void * operator new[](size_t size, MemoryAllocator * heap)
{
	assert(heap != NULL);
	return heap->alloc(size, 4);
}


void operator delete(void * pointer, MemoryAllocator * heap)
{
	assert(pointer != 0);
	assert(heap != NULL);
	if (heap->isAddressInHeap(pointer) && heap->isAddressAllocated(pointer))
	{
		heap->dealloc(pointer);
	}
}

void operator delete[](void * pointer, MemoryAllocator * heap)
{
	assert(pointer != 0);
	assert(heap != NULL);
	if (heap->isAddressInHeap(pointer) && heap->isAddressAllocated(pointer))
	{
		heap->dealloc(pointer);
	}
}