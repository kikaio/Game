#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	bool AnsGameConn(SessionSptr _session, UserAndGameServer::AnsGameConn& _packet) {
		GET_GSESSION_AND_DUM;
		if(dum != nullptr) {
			string encryptKey = "";
			string chatHost = "";
			int16_t chatPort = 0;
			ProtoConverter::FromPacket(IN _packet, OUT encryptKey, OUT chatHost, OUT chatPort);
			DUM_DEBUG_LOG("server send encrypt key : {}", encryptKey);
			_session->SetFilterMode(SESSION_FILTER::XOR);
			_session->SetCryptKey(encryptKey);
			dum->SetChatInfo(chatHost, chatPort);
		}
		return true;
	}
}
