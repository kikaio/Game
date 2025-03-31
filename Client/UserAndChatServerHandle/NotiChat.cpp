#include "pch.h"
#include "UserAndChatServerHandle.h"

bool UserAndChatServerHandle::NotiChat(SessionSptr _session, UserAndChatServer::NotiChat& _packet) {
	GET_CHAT_SERVER_SESSION_AND_DUM;
	ChatData chatData;
	ProtoConverter::FromPacket(IN _packet, OUT chatData);
	if(dum != nullptr) {
		auto dumChatProfile = dum->GetChatProfile();
		ASSERT_CRASH(dumChatProfile != nullptr);
		
		auto chatProfile = chatData.GetChatProfile();
		int senderAccountId = chatProfile->GetAccountId();
		const string& senderName = chatProfile->GetNickName();
		const string& msg = chatData.GetMsg();

		DUM_DEBUG_LOG("[{}:{}] send msg : {}", senderAccountId, senderName, msg);

		if(senderAccountId == dumChatProfile->GetAccountId()) {
			// 본인이 보낸 채팅에 대한 noti.
			if(dum->CheckAndClearWaitChatPacket(UserAndChatServer::Noti, UserAndChatServer::Chat)) {
				dum->DoDumAct();
			}
		}
	}
	return true;
}

