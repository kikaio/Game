#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsLogin(SessionSptr _session, UserAndGameServer::AnsLogin& _packet) {
		LoginResultData loginRetData;
		UserProfile userProfile;
		ProtoConverter::FromPacket(_packet, OUT loginRetData, OUT userProfile);
		
		return true;
	}
}
