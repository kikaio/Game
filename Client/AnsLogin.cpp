#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsLogin(SessionSptr _session, UserAndGameServer::AnsLogin& _packet) {
		if(_packet.login_result_data().is_success()) {
			printf("login success\n");
		}
		else {
			printf("login failed\n");
		}
		return true;
	}
}
