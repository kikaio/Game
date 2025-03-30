#pragma once

#define DECL_CHAT_SERVER_HANDLE(_msgType, _protocolName) 													\
bool _msgType##_protocolName##(SessionSptr _session, UserAndChatServer::##_msgType##_protocolName& _packet)	\


namespace UserAndChatServerHandle {
	DECL_CHAT_SERVER_HANDLE(Ans, ChatConn);
}
