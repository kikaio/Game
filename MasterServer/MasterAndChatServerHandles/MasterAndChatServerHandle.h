#pragma once

#define DECL_CHAT_SERVER_HANDLE(_msgType, _protocolType)																		\
bool _msgType##_protocolType(ChatServerSessionSptr _session, const MasterAndChatServer::##_msgType##_protocolType& _packet)		\

namespace MasterAndChatServerHandle
{
	DECL_CHAT_SERVER_HANDLE(Req, ChatConnectMaster);
};