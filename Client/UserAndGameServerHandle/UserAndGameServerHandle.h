#pragma once


namespace UserAndGameServerHandle {
	//bool ReqTestMsg(SessionSptr _session, UserAndGameServer::ReqTestMsg& _packet);
	DECL_USER_AND_GAMESERVER_HANDLE(Req, TestMsg);
	DECL_USER_AND_GAMESERVER_HANDLE(Ans, Chat);
}