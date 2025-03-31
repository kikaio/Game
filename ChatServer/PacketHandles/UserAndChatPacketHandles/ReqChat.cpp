#include "pch.h"
#include "UserAndChatPacketHandle.h"

namespace UserAndChatPacketHandle {
	bool ReqChat(UserSessionSptr _session, const UserAndChatServer::ReqChat& _packet) {
		CS_DEBUG_LOG("ReqChat called");
		auto chatUser = _session->GetChatUser();
		ChatData chatData;
		ProtoConverter::FromPacket(IN _packet, OUT chatData);
		//todo : 해당 유저의 room에 채팅 전달.
		auto senderProfile = chatData.GetChatProfile();
		int64_t senderAccountId = senderProfile->GetProfileId();

		if(chatUser != nullptr) {
			auto chatRoom = chatUser->GetChatRoom();
			if (chatRoom == nullptr) {
				//todo : error this user need to enter any chat room, send error
				CS_ERROR_LOG("this user's chat room is empty. check please");
				return false;
			}

			auto profile = chatUser->GetProfile();
			if (profile == nullptr) {
				//todo : search from redis
				profile = nullptr;
				if (profile == nullptr) {
					//todo : search from database
					chatUser->SetProfile(profile);
				}
				else {
					chatUser->SetProfile(profile);
				}
			}

			if (profile == nullptr) {
				//todo : error! - user's profile not exist
				// 일단 packet 기반 profile로 설정해준다.
				profile = ChatProfileMng::Get().CreateProfile(
					senderAccountId
					, senderProfile->GetNickName()
					, senderProfile->GetMainHeroId()
					, senderProfile->GetMainFrameId()
				);
			}

			UserAndChatServer::NotiChat _noti;
			ProtoConverter::ToPacket(IN chatData, OUT _noti);
			
			chatRoom->DoAsync(&ChatRoom::Broadcast, _noti);
		}
		return true;
	}
}
