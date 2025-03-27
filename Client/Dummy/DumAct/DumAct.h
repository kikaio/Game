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

class DumActSetLoginData : public DumAct {
public:
	bool isNewLogin = false;
	LoginData loginData;
	LoginData nextLoginData;
public:
	DumActSetLoginData(string _userKey, string _token = "", string _refresh_token = "", bool _isNewLogin = true);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActGameConn : public DumAct {
public:
	DumActGameConn(uint64_t _delayMsec);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActLogin : public DumAct {
public:
	DumActLogin(uint64_t _delayMsec);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActChatConn : public DumAct {
public:
	DumActChatConn(uint64_t _delayMsec);
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};