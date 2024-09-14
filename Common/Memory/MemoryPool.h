#pragma once
#include "Lock.h"


struct MemoryHeader
{
public:
	MemoryHeader(UInt32 _size) : allocSize(_size) {}
private:
	UInt32 allocSize = 0;
public:
	static void* AttachHeader(MemoryHeader* _header, UInt32 _size)
	{
		new (_header)MemoryHeader(_size);
		return reinterpret_cast<void*>(++_header);
	}

	static MemoryHeader* DetachHeader(void* ptr) 
	{
		MemoryHeader* header = reinterpret_cast<MemoryHeader*>(ptr) -1;
		return header;
	}
public:
	void ClearSize() {
		allocSize = 0;
	}
	const UInt32 GetAllocSize() {
		return allocSize;
	}	
};


class MemoryPool
{
public:
	MemoryPool(UInt32 _size);
	~MemoryPool();

private:
	VAL_LOCK(headersLock);
	UInt32 allocSize = 0;
	atomic<UInt32> allocCnt = 0;

	queue<MemoryHeader*> headers;
public:
	void Push(MemoryHeader* _header);
	MemoryHeader* Pop();
};

