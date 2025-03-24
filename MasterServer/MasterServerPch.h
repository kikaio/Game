#pragma once


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#if _DEBUG

#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")

#else

#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")

#endif


#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

#include "CommonPch.h"
#include "MasterTypes.h"
#include "MasterDefines.h"
#include "MasterConfig.h"

#include "DBWrapper.h"

#include "MasterAndChatServerHandle.h"
#include "MasterAndGameServerHandle.h"

#include "ChatServerDiscriminator.h"
#include "GamePacketHandler.h"

#include "ChatServerSession.h"
#include "ServerSession.h"

