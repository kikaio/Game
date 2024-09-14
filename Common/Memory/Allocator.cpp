#include "pch.h"
#include "Allocator.h"


void* BaseAllocator::Alloc(UInt32 size)
{
	return malloc(size);
}

void BaseAllocator::Release(void* ptr)
{
	SAFE_FREE(ptr);
}

void* StompAllocator::Alloc(UInt32 size)
{
	const UInt64 pageCnt = (PAGE_SIZE + size - 1) / PAGE_SIZE;
	const UInt64 memSize = pageCnt * PAGE_SIZE;
	void* ptr = ::VirtualAlloc(NULL, memSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	const UInt64 dataOffset = memSize - size;
	return static_cast<void*>(static_cast<Int8*>(ptr) + dataOffset);
}

void StompAllocator::Release(void* ptr)
{
	const UInt64 address = (UInt64)ptr;
	const UInt64 dataOffset = address % PAGE_SIZE;
	UInt64  oriAddr = address - dataOffset;
	VirtualFree(reinterpret_cast<void*>(oriAddr), 0, MEM_RELEASE);
	return ;
}

void* PoolAllocator::Alloc(UInt32 size)
{
	return Memory::Get().Alloc(size);
}

void PoolAllocator::Release(void* ptr)
{
	Memory::Get().Release(ptr);
}
