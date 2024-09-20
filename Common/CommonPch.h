#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#pragma comment (lib, "ws2_32")
#pragma comment(lib,"mswsock.lib") //AcceptEx 사용 용도

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

using namespace std;
//---------------------------------------------

#include "Types.h"
#include "CommonDefines.h"
#include "Memory.h"
#include "CommonMacro.h"
#include "CommonTLS.h"
#include "Singleton.h"

#include "Allocator.h"
#include "STLAllocator.h"
#include "MemoryPool.h"

#include "Lock.h"
#include "LockManager.h"
#include "ReadWriteLock.h"


#include "Thread.h"
#include "ThreadManager.h"

#include "NetAddr.h"
#include "SocketUtil.h"
#include "WsaReady.h"

#include "IocpCore.h"
#include "Listener.h"