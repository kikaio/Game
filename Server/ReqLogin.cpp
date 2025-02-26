#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet) {
		printf("called ReqLogin");
		return true;
	}
}