#pragma once


#include "UserAndGameServer.pb.h"


#define PROTOBUF_USE_DLLS

#if _DEBUG
#pragma comment(lib, "../Libraries/Libs/Protobuf/Debug/libprotobufd.lib")
#else
#pragma comment(lib, "../Libraries/Libs/Protobuf/Release/libprotobuf.lib")
#endif