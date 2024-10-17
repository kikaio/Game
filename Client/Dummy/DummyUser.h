#pragma once

class DummyUser: public enable_shared_from_this<DummyUser>
{
private:
	DummySessionSptr session;
	DummyProfile profile;
public:
	DummyUserSptr GetSptr();
	void SetDummySession(DummySessionSptr _dummySession);
public:
	string GetNickname() {
		return profile.nickname;
	}
	string GetGreetingMent() {
		return profile.greetingMent;
	}
	void SetNickname(string _name) {
		profile.nickname = _name;
	}
	void SetGreetingMent(string _ment) {
		profile.greetingMent = _ment;
	}
public:
	void SendChatMsg(string _msg);

};