#pragma once

using namespace std;

#define FIX_IN_RANGE(minVal, x, maxVal)			min(max(minVal,x), maxVal)
#define IS_IN_RANGE(minVal, x, maxVal)			(x == FIX_IN_RANGE(minVal, x, maxVal)) ? true : false
#define SAFE_DELETE(ptr)					\
{											\
	if(ptr != nullptr) {					\
		delete ptr;							\
	}										\
	ptr = nullptr;							\
}											\


#define SAFE_DELETE_ARR(arr)				\
{											\
	if(arr != nullptr) {					\
		delete[] arr;						\
	}										\
	arr = nullptr;							\
}											\

#define SAFE_RELEASE(ptr)					\
{											\
	if(ptr != nullptr) {					\
		ptr->release();						\
	}										\
	ptr = nullptr;							\
}											\

#define SAFE_FREE(ptr)						\
{											\
	if(ptr != nullptr) {					\
		free(ptr);							\
	}										\
	ptr = nullptr;							\
}											\



#define VAL_LOCK(lockName)								Lock lockName = Lock(#lockName)
#define LOCK_GUARDDING(_targetObj)						LockGuard guardFor##_targetObj(_targetObj, __FILE__, __LINE__)


#define USE_STOMP_ALLOC false
#if USE_STOMP_ALLOC
#define XALLOC(size)					StompAllocator::Alloc(size)
#define XRELEASE(ptr)					StompAllocator::Release(ptr)
#else
#if true
#define XALLOC(size)					PoolAllocator::Alloc(size)
#define XRELEASE(ptr)					PoolAllocator::Release(ptr)
#else
#define XALLOC(size)					BaseAllocator::Alloc(size)
#define XRELEASE(ptr)					BaseAllocator::Release(ptr)
#endif
#endif



inline bool checkOverflow(UInt32 x, UInt32 add) {
	auto orig = x;
	auto ret = x + add;
	return ((x & 0x80000000) != (ret & 0x80000000));
}


inline bool checkOverflow(UInt16 x, UInt16 add) {
	auto orig = x;
	auto ret = x + add;
	return ((x & 0x8000) != (ret & 0x8000));
}

inline bool checkOverflow(UInt8 x, UInt8 add) {
	auto orig = x;
	auto ret = x + add;
	return (( x & 0x80 ) != ( ret & 0x80 ));
}

template<typename T>
UInt32 BufLen(T arr[]) {
	return sizeof(arr) / sizeof(T);
}

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif


