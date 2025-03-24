#pragma once

#if _DEBUG
#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")
#else
#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")
#endif

#include "CommonPch.h"
#include "ChatTypes.h"


#include "MasterConfig.h"
#include "ChatConfig.h"

#include "LogHelper.h"
#include "ProtoConverter.h"

#include "UserAndChatPacketHandle.h"
#include "MasterAndChatPacketHandle.h"

#include "UserPacketDiscriminator.h"
#include "MasterPacketDiscriminator.h"

#include "UserSession.h"
#include "MasterServerSession.h"
#include "ChatProfile.h"
#include "ChatUser.h"