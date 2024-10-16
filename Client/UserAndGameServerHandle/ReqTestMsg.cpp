#include "pch.h"
#include "ReqTestMsg.h"

bool UserAndGameServerHandle::ReqTestMsg(SessionSptr _session, UserAndGameServer::ReqTestMsg& _packet) {
	printf("UserAndGameServerHandle::ReqTestMsg - test msg : %s\n", _packet.msg().c_str());
	return true;
}
