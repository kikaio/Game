#include "pch.h"
#include "Memory.h"
#include "MemoryPool.h"

Memory::Memory()
{
	UInt32 size = 0;
	UInt32 tableIdx = 0;

	for(size = 32; size <= 1024; size += 32){

		MemoryPool* pool = new MemoryPool(size);
		memPools.push_back(pool);
		while(tableIdx <= size) {
			poolTable[tableIdx++] = pool;
		}
	}

	for (size = 1024; size <= 2048; size += 128) {

		MemoryPool* pool = new MemoryPool(size);
		memPools.push_back(pool);
		while (tableIdx <= size) {
			poolTable[tableIdx++] = pool;
		}
	}

	for (size = 2048; size <= 4096; size += 256) {

		MemoryPool* pool = new MemoryPool(size);
		memPools.push_back(pool);
		while (tableIdx <= size) {
			poolTable[tableIdx++] = pool;
		}
	}

}

Memory::~Memory()
{
	for(auto* pool : memPools) {
		SAFE_DELETE(pool);
	}
}

void* Memory::Alloc(UInt32 size)
{
	MemoryHeader* header = nullptr;
	const UInt32 allocSize = size + sizeof(MemoryHeader);
	if(allocSize > MAX_ALLOC_SIZE) {
		//pooling 제외
		header = reinterpret_cast<MemoryHeader*>(::malloc(allocSize));
	}
	else {
		header = poolTable[allocSize]->Pop();
	}

	return MemoryHeader::AttachHeader(header, allocSize);
}

void Memory::Release(void* ptr)
{
	MemoryHeader* header = MemoryHeader::DetachHeader(ptr);
	const UInt32 allocSize = header->GetAllocSize();
	if(allocSize < 0) {
		//todo err
		return ;
	}
	
	if(allocSize > MAX_ALLOC_SIZE) {
		free(header);
	} 
	else {
		poolTable[allocSize]->Push(header);

	}
}
