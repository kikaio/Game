#pragma once

#if _DEBUG
#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")
#else
#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")
#endif

#include "CommonPch.h"

#include "MasterConfig.h"
#include "ChatConfig.h"
#include "ProtoConverter.h"
#include "UserAndChatPacketHandle.h"
#include "UserPacketDiscriminator.h"
#include "UserSession.h"
#include "ChatProfile.h"
#include "ChatUser.h"
