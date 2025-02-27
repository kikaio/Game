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
};

class DumActGameServerConnect : public DumAct {
protected:
	void DoAct(DummyUserSptr _dumSptr) override;
};

class DumActChat : public DumAct{
public:
	string chatMsg = "dum chat";
protected:
	void DoAct(DummyUserSptr _dumSptr) override; 
};

