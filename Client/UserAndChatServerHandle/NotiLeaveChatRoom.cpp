#include "pch.h"
#include "UserAndChatServerHandle.h"

bool UserAndChatServerHandle::NotiLeaveChatRoom(SessionSptr _session, UserAndChatServer::NotiLeaveChatRoom& _packet) {
	GET_CHAT_SERVER_SESSION_AND_DUM;
	if(dum != nullptr) {
		int64_t leaveAccount = 0;
		ProtoConverter::FromPacket(IN _packet, OUT leaveAccount);
		ChatProfileSptr leaveUser = nullptr;
		auto& users = dum->GetOtherUserChatProfiles();
		for(int idx = 0; idx < users.size(); idx++) {
			if(users[idx]->GetAccountId() == leaveAccount) {
				leaveUser = users[idx];
				users.erase(users.begin()+idx);
				break;
			}
		}
		ASSERT_CRASH(leaveUser != nullptr);
		int32_t curRoomNo = dum->GetCurChatRoomNo();
		const string& nickName = leaveUser->GetNickName();
		DUM_DEBUG_LOG("[Leave user] {}:{} user leave room no-{}", leaveAccount, nickName, curRoomNo);
	}
	return true;
}

