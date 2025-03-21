#pragma once

class DummyUser : public JobQueue
{
#pragma region dummy 자체정보
private:
	int32_t dummyIdx = 0;
	bool dummyUserRecycle = false; //dummy user를 계속 재활용할지 여부.
public:
	void SetDummyUserIdx(int32_t _idx) {
		dummyIdx = _idx;
	}
	int32_t GetDummyIdx() {
		return dummyIdx;
	}
public:
	DummyUserSptr GetSptr();
	void ClearUser();
#pragma endregion

#pragma region test scenario 관련
private:
	int32_t dumActIdx = 0;
	bool isLoopTest = false;
	vector<DumActSptr> dumActs;
public:
	void SetTestScenario(const std::vector<DumActSptr>& _dumActs, bool _isLoopTest = false);
	void DoDumAct();
#pragma endregion

#pragma region network 관련
public:
	NetworkCoreSptr gameServerNetCore = nullptr;
	ProtocolCallbackMap gameServerProtoCallback; //game server 용 protocol callback 담당.
private:
	GameServerSessionSptr gameServerSession;
public:
	bool IsConnected();
	void SetGameServerSession(GameServerSessionSptr _dummySession);
	GameServerSessionSptr GetGameServerSession() {
		return gameServerSession;
	}
public:
	void OnGameServerSessionDisconnected();
	void OnGameServerSessionConnected();
public:
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void ReserveGameServerProtocol(MSG_TYPE _msg, PROTO_TYPE _proto, DUM_PROTOCOL_CB&& _cb) {
		gameServerProtoCallback.ReserveCallback(_msg, _proto, std::move(_cb));
	}
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void RecvGameServerProtocol(MSG_TYPE _msg, PROTO_TYPE _proto) {
		gameServerProtoCallback.RecvProtocol(_msg, _proto);
	}

#pragma endregion 


private:
	DummyProfile profile;
	Inventory inventory;
	LoginData loginData;
	LoginResultData loginResultData;
	ChatProfile chatProfile;
public:
	void SetLoginData(const LoginData& _loginData);
	const LoginData& GetLoginData();

	void SetChatProfile(const ChatProfile& _chatProfile);
	const ChatProfile& GetChatProfile();

	void SetProfile(const DummyProfile& _profile);
	DummyProfile& GetProfile();
	
	void SetInventory(const Inventory& _inven);
	Inventory& GetInventory();

	void SetLoginResultData(const LoginResultData& _data);
	LoginResultData& GetLoginResultData();

public:
	void Render();
};