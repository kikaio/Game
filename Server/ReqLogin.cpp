#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet) {
		GS_DEBUG_LOG("ReqLogin Called");
		LoginData loginData;
		ProtoConverter::FromPacket(_packet, OUT loginData);
		GS_DEBUG_LOG("user key : {}, platform : {}", loginData.sId, ENUM_TO_STR(loginData.loginPlatform));

		{
			//todo : 기획 data에서 읽은 값으로 대체
			int def_main_hero_id = 1;
			int def_main_frame_id = 1000;
			string def_greeting_ment = "def greeting";
			bool is_old_user = false;

			// platform 정보를 읽는다, 신규 유저라면 use_select_platform에서 account 등 data를 생성한다.
			auto platformError = DBWrapper::SelectPlatform(loginData, IN is_old_user, IN def_main_hero_id, IN def_main_frame_id, IN def_greeting_ment);
			if(platformError.HasError()) {
				return _session->SendError(platformError);
			}

		}

		UserAndGameServer::AnsLogin _ans;
		LoginResultData loginResultData;
		UserProfile userProfile;
		loginResultData.isSuccess = true;
		ProtoConverter::ToPacket(IN loginResultData, IN userProfile, OUT _ans);
		return _session->SendPacket(_ans);
	}
}