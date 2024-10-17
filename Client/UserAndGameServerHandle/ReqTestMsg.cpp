#include "pch.h"
#include "UserAndGameServerHandle.h"
namespace UserAndGameServerHandle {

	bool ReqTestMsg(SessionSptr _session, UserAndGameServer::ReqTestMsg& _packet) {
		printf("UserAndGameServerHandle::ReqTestMsg - test msg : %s\n", _packet.msg().c_str());
		return true;
	}
}