#pragma once
#include<stdio.h>
struct BlockDescriptor {
public:
	void * baseAddress;
	void * accessAddress;
	size_t size;
	BlockDescriptor * next;
	BlockDescriptor * previous;
};