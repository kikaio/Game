#pragma once

#define DECL_GAME_SERVER_HANDLE(_msgType, _protocolName) 													\
bool _msgType##_protocolName##(SessionSptr _session, UserAndGameServer::##_msgType##_protocolName& _packet)	\



namespace UserAndGameServerHandle {
	//bool ReqTestMsg(SessionSptr _session, UserAndGameServer::ReqTestMsg& _packet);
	DECL_GAME_SERVER_HANDLE(Req, TestMsg);
	DECL_GAME_SERVER_HANDLE(Ans, Chat);
	DECL_GAME_SERVER_HANDLE(Ans, Login);
	DECL_GAME_SERVER_HANDLE(Ans, GameConn);
}