#pragma once

#define DECL_CHAT_SERVER_HANDLE(_msgType, _protocolName) 													\
static bool _msgType##_protocolName##(SessionSptr _session, UserAndChatServer::##_msgType##_protocolName& _packet)	\


class UserAndChatServerHandle {
public:
	DECL_CHAT_SERVER_HANDLE(Ans, ChatConn);
	DECL_CHAT_SERVER_HANDLE(Noti, Chat);
};
