#pragma once

namespace MasterAndGameServerHandle {
	bool ReqChat(UserSessionSptr _session, UserAndGameServer::ReqChat& _packet);
}