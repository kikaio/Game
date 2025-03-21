#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsGameConn(SessionSptr _session, UserAndGameServer::AnsGameConn& _packet) {
		GET_GSESSION_AND_DUM;
		if(dum != nullptr) {
			_session->SetFilterMode(SESSION_FILTER::XOR);
			_session->SetCryptKey(_packet.aes_key());
		}
		return true;
	}
}
