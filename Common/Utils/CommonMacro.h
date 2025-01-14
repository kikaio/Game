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


#define CRASH(cause)						\
{											\
	uint32_t* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}

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

template<typename T, typename... Args>
shared_ptr<T> MakeShared(Args&&... args) {
	return shared_ptr<T>(xnew<T>(forward<Args>(args)...), xfree<T>);
}

#define ENUM_TO_INT(_eVal) magic_enum::enum_integer(_eVal)

#define ENUM_TO_STR(_eType) magic_enum::enum_name(_eType)

#define ENUM_NAMES(_eClass) magic_enum::enum_names<_eClass>()

#define ENUM_FROM_STR(_eClass, _eStr) magic_enum::enum_cast<_eClass>(_eStr, magic_enum::case_insensitive)

#define ENUM_FROM_INT(_eClass, _intVal) magic_enum::enum_cast<_eClass>(_intVal)

#define ENUM_ENTRY(_eClass) magic_enum::enum_entries<_eClass>()
