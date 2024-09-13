#pragma once
#include "Allocator.h"

#define USE_STOMP false
#define XALLOC(size)					BaseAllocator::Alloc(size)
#define XRELEASE(ptr)					BaseAllocator::Release(ptr)

template<typename T, typename... Args>
T* xnew(Args&&... args)
{
	T* ptr = nullptr;
#if USE_STOMP
	ptr = StompAllocator::Alloc(sizeof(T));
#else
	ptr = static_cast<T*>(XALLOC(sizeof(T)));
	new (ptr) T(forward(args)...);
#endif
	return ptr
}

template<typename T> 
void xfree(T* ptr)
{
#if USE_STOMP
	StompAllocator::Release(ptr);
#else
	ptr->~T();
	XRELEASE(ptr);
#endif
	ptr = nullptr;
	return ;	
}