#include "pch.h"
#include "UserAndChatServerHandle.h"

bool UserAndChatServerHandle::NotiEnterChatRoom(SessionSptr _session, UserAndChatServer::NotiEnterChatRoom& _packet) {
	GET_CHAT_SERVER_SESSION_AND_DUM;
	if(dum != nullptr) {
		ChatProfileSptr enterProfile = nullptr;
		ProtoConverter::FromPacket(IN _packet, OUT enterProfile);
		int32_t curRoomNo = dum->GetCurChatRoomNo();
		int64_t newAccountId = enterProfile->GetAccountId();
		const string& newNickName = enterProfile->GetNickName();
		auto& curUsers = dum->GetOtherUserChatProfiles();
		for(int32_t idx = 0; idx < curUsers.size(); idx++) {
			if(curUsers[idx]->GetAccountId() == newAccountId) {
				curUsers.erase(curUsers.begin() + idx);
				break;
			}
		}
		curUsers.push_back(enterProfile);
		DUM_DEBUG_LOG("[Enter New User] {}:{} enter to room no-{}", newAccountId, newNickName, curRoomNo);
	}
	return true;
}

