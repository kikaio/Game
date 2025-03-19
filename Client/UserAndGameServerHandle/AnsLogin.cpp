#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsLogin(SessionSptr _session, UserAndGameServer::AnsLogin& _packet) {
		GET_GSESSION_AND_DUM;
		if(dum != nullptr) {
			LoginResultData& loginRetData = dum->GetLoginResultData();
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
