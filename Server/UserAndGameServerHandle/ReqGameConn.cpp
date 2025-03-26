#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqGameConn(UserSessionSptr _session, UserAndGameServer::ReqGameConn& _packet) {
		GS_DEBUG_LOG("ReqGameConn Called");
		string encryptKey = StrUtil::GetRandomStr(16);

		UserAndGameServer::AnsGameConn _ans;
		GS_DEBUG_LOG("sesison gen encrypt key : {}", encryptKey);
		ProtoConverter::ToPacket(IN encryptKey, OUT _ans);
		bool ret = _session->SendPacket(_ans);
		_session->SetFilterMode(SESSION_FILTER::XOR);
		_session->SetCryptKey(encryptKey);
		return ret;
	}
}