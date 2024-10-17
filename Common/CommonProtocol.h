#pragma once


#include "UserAndGameServer.pb.h"


#if _DEBUG
#pragma comment(lib, "../Libraries/Libs/Protobuf/Debug/libprotobufd.lib")
#else
#pragma comment(lib, "../Libraries/Libs/Protobuf/Release/libprotobuf.lib")
#endif