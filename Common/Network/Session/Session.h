#pragma once

class SessionManager;

class Session : public IocpObj //, public enable_shared_from_this<Session>
{
public:
	Session();
	virtual ~Session();
private:
	string sId;
public:
	virtual int32_t AfterRecved(BYTE* _buf, UInt32 _dataSize) final ;
	virtual void AfterAccepted(SessionSptr _session) final;
	virtual void AfterConnected() final;
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	SessionSptr GetSession() {
		return static_pointer_cast<Session>(shared_from_this());
	}
public:
	void SetId(string _sid) {
		sId = _sid;
	}
	const string& GetSId() const  {
		return sId;
	}

};
