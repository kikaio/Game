#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet) {
		GS_DEBUG_LOG("ReqLogin Called");
		LoginData loginData;
		ProtoConverter::FromPacket(_packet, OUT loginData);
		GS_DEBUG_LOG("user key : {}, platform : {}", loginData.sId, ENUM_TO_STR(loginData.loginPlatform));

		{
			// platform 정보를 읽는다, 신규 유저라면 use_select_platform에서 account 등 data를 생성한다.
			auto platformError = DBWrapper::SelectPlatform(loginData);
			if(platformError.HasError()) {
				return _session->SendError(platformError);
			}
			//to do : common db 에서 해당 user key 정보가 있는지 확인 및 생성.
			auto selectError = DBWrapper::SelectAccount(loginData);
			if (selectError.HasError()) {
				return _session->SendError(selectError);
			}

		}

		UserAndGameServer::AnsLogin _ans;
		LoginResultData loginResultData;
		UserProfile userProfile;
		loginResultData.isSuccess = true;
		ProtoConverter::ToPacket(loginResultData, userProfile, OUT _ans);
		return _session->SendPacket(_ans);
	}
}