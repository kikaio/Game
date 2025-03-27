#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#if _DEBUG

#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")

#else

#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")

#endif



#include "CommonPch.h"
#include "ServerDefines.h"
#include "ServerEnums.h"
#include "ServerTypes.h"

#include "ServerDBTypes.h"

#include "LogHelper.h"

#include "UserPacketDiscriminator.h"
#include "MasterPacketDiscriminator.h"

#include "UserSession.h"
#include "MasterSession.h"

#include "UserAndGameServerHandle.h"
#include "MasterAndGameServerHandle.h"


#include "ItemData.h"
#include "CostumeData.h"
#include "CharacterData.h"
#include "Inventory.h"
#include "GameProfile.h"
#include "GameUser.h"
#include "GameConfig.h"
#include "MasterConfig.h"
#include "ChatConfig.h"

#include "DBWrapper.h"

#include "MonitorHelper.h"
#include "ProtoConverter.h"

