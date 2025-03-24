#include "pch.h"
#include "MasterAndChatPacketHandle.h"

namespace MasterAndChatPacketHandle {
	bool AnsChatConnectMaster(MasterServerSessionSptr _session, const MasterAndChatServer::AnsChatConnectMaster& _packet) {
		MS_DEBUG_LOG("AnsChatConnectMaster called");
		return true;
	}
}
