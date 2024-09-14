#pragma once

using namespace std;


class BaseAllocator
{
public:
	static void* Alloc(UInt32 size);
	static void Release(void* ptr);
};


class StompAllocator
{
	enum {
		PAGE_SIZE = 0x1000
	};
public:
	static void* Alloc(UInt32 size);
	static void Release(void* ptr);
};

class PoolAllocator
{
public:
	static void* Alloc(UInt32 size);
	static void Release(void* ptr);

};