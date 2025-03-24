#include "pch.h"
#include "MasterAndChatServerHandle.h"

namespace MasterAndChatServerHandle
{
	bool ReqChatConnectMaster(ChatServerSessionSptr _session, const MasterAndChatServer::ReqChatConnectMaster& _packet) {
		return true;
	}
};