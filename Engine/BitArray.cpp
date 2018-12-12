#pragma once
#include "BitArray.h"




 BitArray * BitArray::Create(size_t numBits, bool initToZero, MemoryAllocator * heap)
{
	 return new BitArray(numBits, initToZero, heap);
}

 void BitArray::setAll(bool setValue)
 {
	 //Sets all bits in the BitArray to setValue
	 assert(bits);
	 memset(bits, setValue ? 0 : 1, sizeOfArray / bitPerByte);
 }

void BitArray::setBit(size_t index)
{
	//Sets the bit at index to 1
	assert(index >= 0);
	size_t bitIndex = index / bitPerByte;
	size_t offset = index % bitPerByte;

#ifdef _WIN32
	uint32_t mask = 1;
#elif _WIN64
	uint64_t mask = 1;
#endif
	mask = mask << offset;
	bits[index] = bits[index] | mask;
}

void BitArray::clearBit(size_t index)
{
	//sets the bit at index to 0
	assert(index >= 0);
	size_t bitIndex = index / bitPerByte;
	size_t offset = index % bitPerByte;

#ifdef _WIN32
	uint32_t mask = 1;
#elif _WIN64
	uint64_t mask = 1;
#endif
	mask = mask << offset;
	bits[index] = bits[index] - mask;
}

bool BitArray::isSet(size_t index) const
{
	//checks if the bit at index is 1
	assert(index > 0);
	size_t bitIndex = index / bitPerByte;
	size_t offset = index % bitPerByte;

#ifdef _WIN32
	uint32_t mask = 1;
	uint32_t temp = bits[index];
#elif _WIN64
	uint64_t mask = 1;
	uint64_t temp = bits[index];
#endif
	mask = mask << offset;
	
	temp = temp | mask;
	if (temp == bits[index])
		return true;
	else 
		return false;
}

bool BitArray::isClear(size_t index) const
{
	//checks if the bit at index is 0
	assert(index >= 0);
	size_t bitIndex = index / bitPerByte;
	size_t offset = index % bitPerByte;

#ifdef _WIN32
	uint32_t mask = 1;
	uint32_t temp = bits[index];
#elif _WIN64
	uint64_t mask = 1;
	uint64_t temp = bits[index];
#endif
	mask = mask << offset;
	temp = temp - mask;
	if (temp == bits[index])
		return true;
	else 
		return false;
}

bool BitArray::areAllClear()
{
	//checks if the entire bitarray is empty
	size_t index = 0;
#ifdef _WIN32
	uint32_t mask = 0;
#elif _WIN64
	uint64_t mask = 0;
#endif
	while (index < sizeOfArray)
	{
		if (bits[index] | mask)
			return false;
		index++;
	}
	return true;
}

bool BitArray::areAllSet()
{
	//checks if the entire bitarray is set
	size_t index = 0;
#ifdef _WIN32
	uint32_t mask = UINT32_MAX;
#elif _WIN64
	uint64_t mask = UINT64_MAX;
#endif
	while (index < sizeOfArray)
	{
		if ((bits[index] & (mask)) != mask)
			return false;
		index++;
	}
	return true;
}

size_t BitArray::firstSet()
{
	//returns the index of the first set bit
	size_t index = 0;
	unsigned long position;
	unsigned char result;
	while (index < sizeOfArray)
	{
#ifdef _WIN32
		result = _BitScanForward(&position, bits[index]);
#elif defined _WIN64
		result = _BitScanForward64(&position, bits[index]);
#endif
		if (result)
			return bitPerByte*index + position;
		else
			index++;
	}
	return 0;
}

size_t BitArray::firstClear()
{
	size_t index = 0;
	unsigned long position;
	unsigned char result;
#ifdef _WIN32
	uint32_t temp = 0;
#elif _WIN64
	uint64_t temp = 0;
#endif
	while (index < sizeOfArray)
	{
		temp = !bits[index];
#ifdef _WIN32
		result = _BitScanForward((&position), temp);
#elif _WIN64
		result = _BitScanForward64(&position, temp);
#endif
		if (result)
			return bitPerByte * index + position;
		else
			index++;
	}
	return 0;
}
