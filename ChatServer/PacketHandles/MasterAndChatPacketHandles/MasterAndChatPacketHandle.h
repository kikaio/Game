#pragma once

#define DECL_MASTER_AND_CHAT_PACKET_HANDLE(_msgType, _protocolType) bool _msgType##_protocolType(MasterServerSessionSptr _session, const MasterAndChatServer::##_msgType##_protocolType& _packet)


namespace MasterAndChatPacketHandle {
	DECL_MASTER_AND_CHAT_PACKET_HANDLE(Noti, ErrInfo);
}