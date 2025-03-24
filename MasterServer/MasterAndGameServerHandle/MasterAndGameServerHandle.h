#pragma once

#define DECL_GAME_SERVER_HANDLE(_msgType, _protocolType)																		\
bool _msgType##_protocolType(ServerSessionSptr _session, const MasterAndGameServer::##_msgType##_protocolType& _packet)			\


namespace MasterAndGameServerHandle
{
	DECL_GAME_SERVER_HANDLE(Req, MasterServerConnect);
};