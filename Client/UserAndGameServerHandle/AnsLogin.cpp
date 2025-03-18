#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsLogin(SessionSptr _session, UserAndGameServer::AnsLogin& _packet) {
		auto gameSession = static_pointer_cast<GameServerSession>(_session);
		auto dum = gameSession->GetDummyUser();
		if(dum != nullptr) {
			LoginResultData loginRetData;
			DummyProfile& dummyProfile = dum->GetProfile();;
			Inventory& inventory = dum->GetInventory();
			ProtoConverter::FromPacket(_packet
				, OUT loginRetData
				, OUT dummyProfile
				, OUT inventory
			);
			dum->Render();
		}
		return true;
	}
}
