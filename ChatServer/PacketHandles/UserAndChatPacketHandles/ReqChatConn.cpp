#include "pch.h"
#include "UserAndChatPacketHandle.h"

namespace UserAndChatPacketHandle {
	bool ReqChatConn(UserSessionSptr _session, const UserAndChatServer::ReqChatConn& _packet) {
		CS_DEBUG_LOG("ReqChatConn called");
		auto chatUser = _session->GetChatUser();
		ASSERT_CRASH(chatUser);
		int64_t accountId = 0;
		ProtoConverter::FromPacket(IN _packet, OUT accountId);
		chatUser->SetAccountId(accountId);
		auto chatProfile = ChatProfileMng::Get().GetProfile(accountId);
		if(chatProfile == nullptr) {
			if(false) {
				//todo : read from redis
				if (chatProfile == nullptr) {
					//todo : read from database
				}

				if (chatProfile == nullptr) {
					//todo : send err packet about profile not exist.
					return false;
				}
			}
			else {
				// testㅣ용 profile 적용
				chatProfile = ChatProfileMng::Get().CreateProfile(
					accountId
					, "test nick"
					, 0
					, 0
				);
				chatUser->SetProfile(chatProfile);
			}
		}
		//todo : GetRoomNo for random to enter
		auto room = ChatRoomMng::Get().GetRoundRobinNormalRoom();
		ASSERT_CRASH(room != nullptr);
		vector<ChatProfileSptr> profiles;
		room->GetProfiles(OUT profiles);
		room->DoAsync(&ChatRoom::Enter, chatUser);

		UserAndChatServer::AnsChatConn ans;
		ProtoConverter::ToPacket(chatProfile, room->GetRoomNo(), profiles, OUT ans);

		return _session->SendPacket(ans);
	}
}
