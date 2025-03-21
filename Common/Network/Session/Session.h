#pragma once

class SessionManager;

using OnSessionDisconnectedFunc = std::function<void()>;
using OnSessionConnectedFunc = std::function<void()>;

class Session : public IocpObj //, public enable_shared_from_this<Session>
{
public:
	Session();
	virtual ~Session();
private:
	SessionFilter sessionFilter; //session filter를 각 session들이 지닌다.
private:
	string sId;
	string encryptKey = "";
public:
	void SetCryptKey(const string& _key);
	const string& GetCryptKey();
protected:
	virtual int32_t AfterRecved(BYTE* _buf, UInt32 _dataSize) override final ;
	virtual void AfterConnected() override final;
	virtual void AfterDisconnected() override final;
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
	OnSessionDisconnectedFunc onSessionDisconenctedFunc = []() {};
	OnSessionConnectedFunc onSessionConenctedFunc = [](){};
public:
	virtual bool TrySend(SendBufferSptr _sendBuffer) override final;
public: 
	void SetOnSessionDisconnectedFunc(OnSessionDisconnectedFunc _func);
	void SetOnSessionConnectedFunc(OnSessionConnectedFunc _func);
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
	void SetFilterMode(SESSION_FILTER _mode) {
		sessionFilter.SetFilter(_mode);
	}
};
