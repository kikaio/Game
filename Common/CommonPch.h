﻿#pragma once

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


#include <memoryapi.h>
#include <atomic>
#include <mutex>
//---------------------------------------------

#include "Types.h"
#include "Singleton.h"
#include "CommonMacro.h"
#include "CommonDefines.h"
#include "Memory.h"
#include "Allocator.h"
#include "STLAllocator.h"
#include "MemoryPool.h"
#include "Lock.h"
#include "ReadWriteLock.h"
#include "CommonTLS.h"