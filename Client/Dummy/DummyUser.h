#pragma once

class DummyUser: public enable_shared_from_this<DummyUser>
{
public:
	DummyUserSptr GetSptr();
private:
	bool dummyUserRecycle = false; //dummy user를 계속 재활용할지 여부.
private:
	DummySessionSptr session;
	DummyProfile profile;
	int32_t dummyIdx = 0;
public:
	void ClearUser();
	bool IsConnected();
public:
	void SetDummySession(DummySessionSptr _dummySession);
	string GetNickname() {
		return profile.Nickname();
	}
	string GetGreetingMent() {
		return profile.GreetingMent();
	}
	void SetDummyUserIdx(int32_t _idx) {
		dummyIdx = _idx;
	}
	bool SetNickname(string _name) {
		return profile.ChangeNickname(_name);
	}
	bool SetGreetingMent(string _ment) {
		return profile.ChangeGreetingMent(_ment);
	}

public:
	void SendChatMsg(string _msg);
public:
	void OnSessionDisconnected();
};