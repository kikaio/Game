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

#pragma endregion 


private:
	DummyProfile profile;
	LoginData loginData;
	ChatProfile chatProfile;
public:
	void SetLoginData(const LoginData& _loginData);
	const LoginData& GetLoginData();

	void SetChatProfile(const ChatProfile& _chatProfile);
	const ChatProfile& GetChatProfile();

	string GetNickname() {
		return profile.Nickname();
	}
	string GetGreetingMent() {
		return profile.GreetingMent();
	}
	bool SetNickname(string _name) {
		return profile.ChangeNickname(_name);
	}
	bool SetGreetingMent(string _ment) {
		return profile.ChangeGreetingMent(_ment);
	}

};