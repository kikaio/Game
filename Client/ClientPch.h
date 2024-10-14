#pragma once

#if _DEBUG

#pragma comment(lib, "../Libraries/Libs/Common/Debug/Common.lib")
#pragma comment(lib, "../Libraries/Libs/Protobuf/Debug/libprotobufd.lib")
#pragma comment(lib, "../Libraries/Libs/Protobuf/Debug/libprotocd.lib")

#else

#pragma comment(lib, "../Libraries/Libs/Common/Release/Common.lib")
#pragma comment(lib, "../Libraries/Libs/Protobuf/Release/libprotobuf.lib")
#pragma comment(lib, "../Libraries/Libs/Protobuf/Release/libprotoc.lib")

#endif

#include <iostream>
#include <string.h>


#include "CommonPch.h"
#include "DummySession.h"
#include "ClientPacketHandler.h"
