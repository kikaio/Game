#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet) {
		GS_DEBUG_LOG("ReqLogin Called");
		LoginData loginData;
		ProtoConverter::FromPacket(_packet, OUT loginData);
		GS_DEBUG_LOG("user key : {}, platform : {}", loginData.deviceKey, ENUM_TO_STR(loginData.loginPlatform));
		//to do : common db 에서 해당 user key 정보가 있는지 확인 및 생성.
		PacketError err = DBWrapper::SelectAccount(loginData);
		if (err.err_no != ENUM_TO_INT(ERR_CATEGORY::NONE)) {
			UserAndGameServer::NotiErrInfo _noti;
			ProtoConverter::ToPacket(err, _noti);
			return _session->SendError(_noti);
		}
		//to do : game db 에서 user character 정보가 있는지 확인 및 생성.

		UserAndGameServer::AnsLogin _ans;
		LoginResultData loginResultData;
		UserProfile userProfile;
		loginResultData.isSuccess = true;
		ProtoConverter::ToPacket(loginResultData, userProfile, OUT _ans);
		return _session->SendPacket(_ans);
	}
}