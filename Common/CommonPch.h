#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <queue>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <Windows.h>
#include <memoryapi.h>
#include <atomic>
#include <mutex>

#include <thread>
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
