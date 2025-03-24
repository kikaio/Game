#include "pch.h"
#include "MasterAndChatPacketHandle.h"

namespace MasterAndChatPacketHandle {
	bool NotiErrInfo(MasterServerSessionSptr _session, const MasterAndChatServer::NotiErrInfo& _packet) {
		MS_DEBUG_LOG("NotiErrInfo called");
		return true;
	}
}
