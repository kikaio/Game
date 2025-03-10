#pragma once

#if _DEBUG
#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")
#else
#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")
#endif

#include <iostream>
#include <string.h>


#include "CommonPch.h"
#include "ClientDefine.h"
#include "ClientType.h"

#include "GameServerSession.h"
#include "GameServerPacketHandler.h"
#include "UserAndGameServerHandle.h"

#include "DummyProfile.h"
#include "DummyUser.h"
#include "DumAct.h"
#include "DummyUserManager.h"


#include "ProtoConverter.h"
