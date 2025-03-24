#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqGameConn(UserSessionSptr _session, UserAndGameServer::ReqGameConn& _packet) {
		GS_DEBUG_LOG("ReqGameConn Called");
		string encryptKey = StrUtil::GetRandomStr(16);
		string chatHost = "localhost";
		int32_t chatPort = 23301;

		UserAndGameServer::AnsGameConn _ans;
		GS_DEBUG_LOG("sesison gen encrypt key : {}", encryptKey);
		GS_DEBUG_LOG("caht server {}:{}", chatHost, chatPort);
		ProtoConverter::ToPacket(IN encryptKey, chatHost, chatPort, OUT _ans);
		bool ret = _session->SendPacket(_ans);
		_session->SetFilterMode(SESSION_FILTER::XOR);
		_session->SetCryptKey(encryptKey);
		return ret;
	}
}