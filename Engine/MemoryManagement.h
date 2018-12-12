#pragma once

#include<stdlib.h>
#include "MemoryAllocator.h"
#include<assert.h>

class MemoryAllocator;
enum ALIGNMENT {
	DEFAULT,
	ALIGN_16,
	ALIGN_32
};


void * operator new(size_t size, MemoryAllocator * heap);

void * operator new(size_t size, MemoryAllocator * heap, unsigned int alignment);

void * operator new[](size_t size, MemoryAllocator * heap);

void operator delete(void * pointer, MemoryAllocator * heap);

void operator delete[](void * pointer, MemoryAllocator * heap);
