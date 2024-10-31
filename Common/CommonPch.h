#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#pragma comment (lib, "ws2_32")
#pragma comment(lib,"mswsock.lib") //AcceptEx 사용 용도


#if _DEBUG
#pragma comment(lib, "../Libraries/Libs/Protobuf/Debug/libprotobufd.lib")
#pragma comment(lib, "../Libraries/Libs/mysql_connector_9/Debug/mysqlcppconn-d.lib")
#else
#pragma comment(lib, "../Libraries/Libs/Protobuf/Release/libprotobuf.lib")
#pragma comment(lib, "../Libraries/Libs/mysql_connector_9/Release/mysqlcppconn.lib")
#endif

#include <iostream>
#include <stdio.h>

#include <queue>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <algorithm>
#include <string>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <Windows.h>
#include <memoryapi.h>
#include <atomic>
#include <mutex>

#include <thread>

#include <ws2def.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <MSWSock.h>
using namespace std;
//---------------------------------------------


#include "Types.h"
#include "CommonDefines.h"
#include "Memory.h"
#include "CommonMacro.h"
#include "CommonTLS.h"
#include "Singleton.h"
#include "TLSSingleton.h"
#include "ClockUtil.h"


#include "Allocator.h"
#include "MemoryPool.h"
#include "STLAllocator.h"

#include "Lock.h"
#include "LockManager.h"
#include "ReadWriteLock.h"


#include "Thread.h"
#include "ThreadManager.h"

#include "NetAddr.h"
#include "SocketUtil.h"
#include "WsaReady.h"

#include "RecvBuffer.h"
#include "SendBuffer.h"
#include "PacketBuffer.h"
#include "BufWriter.h"
#include "BufReader.h"


#include "IocpObj.h"
#include "Listener.h"
#include "Session.h"
#include "SessionManager.h"
#include "IocpEvent.h"
#include "IocpCore.h"
#include "NetworkCore.h"


#include "CommonProtocol.h"

#include "Job.h"
#include "LockQueue.h"
#include "JobTimer.h"
#include "JobQueue.h"
#include "GlobalQueue.h"

#include "DBProfile.h"
#include "DBConn.h"
#include "DBManager.h"
#include "DBLink.h"
#include "DBResultSet.h"
#include "DBQuery.h"

#include "JsonParser.h"
#include "JsonWriter.h"
#include "JsonReader.h"