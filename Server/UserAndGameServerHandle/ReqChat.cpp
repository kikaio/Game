#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandler {

	void SetAnsChatPacket(UserAndGameServer::ReqChat& _req, UserAndGameServer::AnsChat& _ans) {
		auto* chatInfo = _ans.mutable_chat_info();
		auto* userProfile = chatInfo->mutable_user_profile();

		chatInfo->set_chat_type(_req.chat_info().chat_type());
		userProfile->set_nick_name(_req.chat_info().user_profile().nick_name());
		return;
	}

	bool ReqChat(SessionSptr _session, UserAndGameServer::ReqChat& _packet) {

		auto curNetCore = _session->GetNetCore();
		UserSessionSptr _userSession = static_pointer_cast<UserSession>(_session);
		if (curNetCore == nullptr) {
			return false;
		}

		UserAndGameServer::AnsChat ans;
		SetAnsChatPacket(_packet, ans);
		SendBufferSptr sendBuf = ServerPacketHandler::MakePacketAnsChat(ans);
		curNetCore->BroadCast(sendBuf);
		return true;
	}

}

