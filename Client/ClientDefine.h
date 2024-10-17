#pragma once

#define DECL_USER_AND_GAMESERVER_HANDLE(_msgType, _protocolName) 											\
bool _msgType##_protocolName##(SessionSptr _session, UserAndGameServer::##_msgType##_protocolName& _packet)	\
