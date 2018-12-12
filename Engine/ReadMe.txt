Final Exam ReadMe.txt

1) The BitArray class uses uint32_t or uint64_t depending on the system
file: BitArray.h and BitARray.cpp, almost every function uses it in some way

2) _BitScanForward and _BiitScanForward64are used appropriately(I think) in BitArray.cpp line 141 and line 167

3) Some of the bit math in the Bit Array class was fun to come up with
in BitArray.cpp line 165 (firstClear()), I used the same logic as firstSet() to find the first clear bit, except i logical NOT the block before using bitScanForward to find 0s instead of 1s

The math to clear and set bits at line 32 and 48 in BitArray.cpp is interesting. 
To clear a bit, I find the block and index within the block using a divide and modulo respectively
THen i create a mask value of 1 and shift it left by the offset, and then logical OR/ subtract it depending on whether i'm setting it to 0 or 1

4)The Fixed Size Allocators are integrated into my Memory Allocator in MemoryAllocator.h at line 38,39
They are used in allocs and deallocs in MemoryAllocator.cpp at lines 152 and 451
