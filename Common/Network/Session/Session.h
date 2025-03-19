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
	string sId;
	SESSION_FILTER sessionFilter = SESSION_FILTER::NONE;
private:
	string GetEncryptKey();
	string GetDecryptKey();
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
	void SetSessionFilter(SESSION_FILTER _filter);
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

};
