#include "pch.h"
#include "MasterAndGameServerHandle.h"

namespace MasterAndGameServerHandle
{
	bool ReqMasterServerConnect(ServerSessionSptr _session, MasterAndGameServer::ReqMasterServerConnect& _packet) {
		string serverName = _packet.game_server_name();
		int32_t serverNo = _packet.game_server_no();
		printf("[%s:%d]game server connected!!\n", serverName.c_str(), serverNo);

		MasterAndGameServer::AnsMasterServerConnect _ans;
		_ans.set_is_success(true);
		return true;
	}
};