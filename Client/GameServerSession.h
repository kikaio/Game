#pragma once

#define GET_GSESSION_AND_DUM												\
auto gameSession = static_pointer_cast<GameServerSession>(_session);		\
auto dum = gameSession->GetDummyUser();										\



class GameServerSession : public Session
{
private:
	DummyUserWptr dummyUserWptr;
protected:
	//virtual void AfterSended(UInt32 _bytes) override {
	//	return ;
	//}

	//virtual void AfterConnected() override {
	//	static const int testMsgLen = 6;
	//	static BYTE testMsg[] = { "hello~" };
	//	SendBufferSptr sendBufferSptr = SendBufferManager::Get().Open(BUF_4096);
	//	memcpy(sendBufferSptr->Buffer(), testMsg, testMsgLen);
	//	sendBufferSptr->Close(testMsgLen);
	//	TrySend(sendBufferSptr);
	//	return;
	//}
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	bool SendPacketReqChat(UserAndGameServer::ReqChat& _packet);
	bool SendPacketReqLogin(UserAndGameServer::ReqLogin& _packet);
public:
	void SetDummyUser(DummyUserSptr _dum);
	DummyUserSptr GetDummyUser();
};