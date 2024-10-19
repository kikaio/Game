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
using LockId = int32_t;
using ThreadId = UInt32;


template<typename T>
using Atomic = std::atomic<T>;

using Mutex = std::mutex;

#define DECL_REF_USING(cName)				using cName##Sptr = std::shared_ptr<class cName>

DECL_REF_USING(Thread);
DECL_REF_USING(NetAddr);
DECL_REF_USING(Listener);
DECL_REF_USING(Session);
DECL_REF_USING(IocpCore);
DECL_REF_USING(WsaReady);
DECL_REF_USING(IocpObj);
DECL_REF_USING(SendBuffer);
DECL_REF_USING(SendBufferChunk);
DECL_REF_USING(NetworkCore);
DECL_REF_USING(Job);
DECL_REF_USING(JobQueue);


using WorkFunc = std::function<void()>;

using PacketFunc = bool(SessionSptr _session, class BufReader* _br);
using PacketHeader = uint32_t;

using CallBackType = std::function<void()>;

using AccountId_t = uint64_t;