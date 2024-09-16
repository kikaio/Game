#pragma once

using namespace std;

using Int8 = __int8;
using Int16 = __int16;
using Int32 = __int32;
using Int64 = __int64;

using UInt8 = unsigned __int8;
using UInt16 = unsigned  __int16;
using UInt32 = unsigned __int32;
using UInt64 = unsigned __int64;

using Char = char;
using Byte = unsigned char;

using str_t = std::string;

template<typename T>
using Atomic = std::atomic<T>;

using Mutex = std::mutex;

#define DCL_REF_USING(cName)				using cName##Sptr = std::shared_ptr<class cName>

DCL_REF_USING(Thread);

using WorkFunc = std::function<void()>;
