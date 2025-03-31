#include "pch.h"
#include "UserAndChatServerHandle.h"

bool UserAndChatServerHandle::AnsChatConn(SessionSptr _session, UserAndChatServer::AnsChatConn& _packet) {
	GET_CHAT_SERVER_SESSION_AND_DUM;
	
	if(dum != nullptr) {
		int32_t chatRoomNo = 0;
		ChatProfileSptr chatProfile = MakeShared<ChatProfile>();
		dum->GetOtherUserChatProfiles().clear();
		ProtoConverter::FromPacket(IN _packet
			, OUT chatProfile
			, OUT chatRoomNo
			, OUT dum->GetOtherUserChatProfiles()
		);
		dum->SetChatProfile(chatProfile);
		dum->SetCurChatRoomNo(chatRoomNo);
	}
	return true;
}
