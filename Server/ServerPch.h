#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#if _DEBUG

#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")

#else

#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")

#endif



#include "CommonPch.h"
#include "ServerDefines.h"
#include "ServerTypes.h"
#include "ServerEnums.h"

s#include "ServerPacketHandler.h"
#include "MasterPacketHandler.h"

#include "UserSession.h"
#include "MasterSession.h"

#include "UserAndGameServerHandle.h"
#include "MasterAndGameServerHandle.h"

#include "GameUser.h"
#include "DBConfig.h"

#include "DBWrapper.h"