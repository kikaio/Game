#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(UInt32 _size)
 : allocSize(_size)
{
}

MemoryPool::~MemoryPool()
{
	while(headers.empty() == false) {
		auto ptr = headers.front();
		headers.pop();
		SAFE_FREE(ptr);
	}
}

void MemoryPool::Push(MemoryHeader* _header)
{
	//todo : use lock
	headers.push(_header);
	allocCnt.fetch_sub(1);
}

MemoryHeader* MemoryPool::Pop()
{
	//todo : use lock
	MemoryHeader* header = nullptr;
	{
		if(headers.empty() == false) {
			header = headers.front();
			headers.pop();
		}
	} 

	if(header == nullptr) {
		header = reinterpret_cast<MemoryHeader*>(malloc(allocSize));
		MemoryHeader::AttachHeader(header, allocSize);
	}
	else
	{
		//todo : logging, memory issue
	}

	allocCnt.fetch_add(1);

	return header;
}
