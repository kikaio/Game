#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsGameConn(SessionSptr _session, UserAndGameServer::AnsGameConn& _packet) {
		GET_GSESSION_AND_DUM;
		if(dum != nullptr) {
			string encryptKey = "";
			ProtoConverter::FromPacket(IN _packet, OUT encryptKey);
			DUM_DEBUG_LOG("server send encrypt key : {}", encryptKey);
			_session->SetFilterMode(SESSION_FILTER::XOR);
			_session->SetCryptKey(encryptKey);
		}
		return true;
	}
}
