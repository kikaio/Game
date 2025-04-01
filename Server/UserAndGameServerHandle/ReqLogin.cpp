#include "pch.h"
#include "UserAndGameServerHandle.h"

namespace UserAndGameServerHandle {
	
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet) {
		GS_DEBUG_LOG("ReqLogin Called");
		LoginData loginData;
		ProtoConverter::FromPacket(_packet, OUT loginData);
		GS_DEBUG_LOG("user key : {}, platform : {}, token : {}, refresh token : {}"
			, loginData.sId, ENUM_TO_STR(loginData.loginPlatform)
			, loginData.loginToken, loginData.refreshToken
		);
		
		GameUserSptr gameUser = _session->GetGameUser();
		{
			//todo : 기획 data에서 읽은 값으로 대체
			string def_nick_name = "dum";
			int def_main_hero_id = 1;
			int def_main_frame_id = 1000;
			string def_greeting_ment = "def greeting";
			bool isOldUser = false;
			//todo : gen token string
			if(loginData.loginToken == "") {
				loginData.loginToken = "dum_token";
				loginData.refreshToken = "dum_refresh_token";
			}
			
			
			// platform 정보를 읽는다, 신규 유저라면 use_select_platform에서 account 등 data를 생성한다.
			auto platformError = DBWrapper::PlatformSelect(
				loginData, gameUser
				, OUT isOldUser, IN def_nick_name, IN def_main_hero_id, IN def_main_frame_id, IN def_greeting_ment
			);
			if (platformError.HasError()) {
				return _session->SendError(platformError);
			}

			//신규유저는 생성부터.
			if(isOldUser == false) {
				auto gameError = DBWrapper::GameUserCreate(gameUser);
				if (gameError.HasError()) {
					return _session->SendError(gameError);
				}
			}

			auto gameError = DBWrapper::GameUserSelect(gameUser);

			// todo : render 지울 것.
			gameUser->Render();
		}
		//todo : redis save


		UserAndGameServer::AnsLogin _ans;
		LoginResultData loginResultData;
		loginResultData.isSuccess = true;
		loginResultData.loginToken = loginData.loginToken;
		GameProfile& gameProfile = gameUser->GetProfile();
		Inventory& inventory = gameUser->GetInventory();
		ProtoConverter::ToPacket(IN loginResultData, IN gameProfile, IN inventory, OUT _ans);
		return _session->SendPacket(_ans);
	}
}