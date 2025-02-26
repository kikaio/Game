#pragma once


class DumAct {
private:
	int64_t actDelayMsec = 0;
public:
	void setActDelay(int64_t _delayMsec) {
		actDelayMsec = _delayMsec;
	}
public:
	void Do(weak_ptr<DummyUser> _dumWptr) {
		if(auto _dumSptr = _dumWptr.lock()) {
			DoAct(_dumSptr, _dumSptr->GetDummySession());
		}
	}
protected:
	virtual void DoAct(DummyUserSptr _dumSptr, DummySessionSptr _dumSession) = 0;
};


class DumActChat : public DumAct{
public:
	string msg = "dum chat";
protected:
	void DoAct(DummyUserSptr _dumSptr, DummySessionSptr _dumSession) override {
		// todo : dummy user send chat packet using msg value

		return ;
	}
};