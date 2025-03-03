#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsChat(SessionSptr _session, UserAndGameServer::AnsChat& _packet) {
		ChatData chatData;
		ProtoConverter::FromProto(_packet, chatData);
		const ChatProfile& chatProfile = chatData.chatProfile;
		printf("[%s] : %s\n", chatProfile.nickName.c_str(), chatData.msg.c_str());
		return true;
	}
}