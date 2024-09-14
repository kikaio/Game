#pragma once
#include "Allocator.h"
#include "Singleton.h"

class MemoryPool;

template<typename T, typename... Args>
T* xnew(Args&&... args)
{
	T* ptr = nullptr;
	ptr = static_cast<T*>(XALLOC(sizeof(T)));
	new (ptr) T(forward(args)...);
	return ptr
}

template<typename T> 
void xfree(T* ptr)
{
	ptr->~T();
	XRELEASE(ptr);
	ptr = nullptr;
	return ;	
}

class Memory : public Singleton<Memory>
{
	enum {
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256)
		, MAX_ALLOC_SIZE = 4096
	};
public:
	Memory();
	~Memory();
private:
	vector<MemoryPool*> memPools;
	MemoryPool* poolTable[MAX_ALLOC_SIZE+1] = {nullptr, };
public:
	void* Alloc(UInt32 size);
	void Release(void* ptr);

};