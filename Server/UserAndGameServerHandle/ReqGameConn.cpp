#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqGameConn(UserSessionSptr _session, UserAndGameServer::ReqGameConn& _packet) {
		GS_DEBUG_LOG("ReqGameConn Called");

		UserAndGameServer::AnsGameConn _ans;
		string aesKey = "dummy_aes_key";
		ProtoConverter::ToPacket(IN aesKey, OUT _ans);
		return _session->SendPacket(_ans);
	}
}