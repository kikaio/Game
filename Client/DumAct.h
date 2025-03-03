#pragma once


class DumAct {
protected:
	uint64_t actDelayMsec = 0;
public:
	void setActDelay(int64_t _delayMsec) {
		actDelayMsec = _delayMsec;
	}
public:
	void Do(weak_ptr<DummyUser> _dumWptr) {
		if(auto _dumSptr = _dumWptr.lock()) {
			DoAct(_dumSptr);
		}
	}
protected:
	virtual void DoAct(DummyUserSptr _dumSptr) = 0;
protected:
	void ReserveAct(DummyUserSptr _dumSptr, CallBackType&& _cb);
};

class DumActGameServerConnect : public DumAct {
public:
	DumActGameServerConnect(uint64_t _delayMsec);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActSetChatProfile : public DumAct {
public: 
	ChatProfile chatProfile;
public:
	DumActSetChatProfile(const ChatProfile& _chatProfile);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActChat : public DumAct{
public:
	CHAT_TYPE chatType;
	string chatMsg = "dum chat";
public:
	DumActChat(uint64_t _delayMsec, string _chatMsg = "dum default chat", CHAT_TYPE _chatType=CHAT_TYPE::NORMAL);
protected:
	void DoAct(DummyUserSptr _dumSptr) override; 
};

class DumActSetLoginData : public DumAct {
public:
	LoginData loginData;
public:
	DumActSetLoginData(string _deviceKey, LOGIN_PLATFORM _platformType);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActLogin : public DumAct {
public:
	DumActLogin(uint64_t _delayMsec);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};