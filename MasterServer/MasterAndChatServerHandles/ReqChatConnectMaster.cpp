#include "pch.h"
#include "MasterAndChatServerHandle.h"

namespace MasterAndChatServerHandle
{
	bool ReqChatConnectMaster(ChatServerSessionSptr _session, const MasterAndChatServer::ReqChatConnectMaster& _packet) {
		string serverName = _packet.server_name();
		int32_t serverNo = _packet.server_no();
		printf("[%s:%d]chat server connected!!\n", serverName.c_str(), serverNo);

		MasterAndChatServer::AnsChatConnectMaster _ans;
		_ans.set_is_success(true);
		return _session->SendPacket(_ans);
		return true;
	}
};