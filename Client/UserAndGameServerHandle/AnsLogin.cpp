#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsLogin(SessionSptr _session, UserAndGameServer::AnsLogin& _packet) {
		LoginResultData loginRetData;
		DummyProfile dummyProfile;
		Inventory inventory;
		ProtoConverter::FromPacket(_packet
			, OUT loginRetData
			, OUT dummyProfile
			, OUT inventory
		);
		
		return true;
	}
}
