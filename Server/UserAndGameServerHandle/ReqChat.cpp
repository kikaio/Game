#include "pch.h"
#include "UserAndGameServerHandle.h"


namespace UserAndGameServerHandle {

	bool ReqChat(UserSessionSptr _session, UserAndGameServer::ReqChat& _packet) {

		auto curNetCore = _session->GetNetCore();
		if (curNetCore == nullptr) {
			return false;
		}

		ChatData chatData;
		ProtoConverter::FromPacket(_packet, OUT chatData);

		UserAndGameServer::AnsChat ans;
		ProtoConverter::ToPacket(chatData, OUT ans);
		SendBufferSptr sendBuf = ServerPacketHandler::MakePacketAnsChat(ans);
		curNetCore->BroadCast(sendBuf);
		return true;
	}

}

