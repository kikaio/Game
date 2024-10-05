#pragma once

class DummySession : public Session
{
public:
	virtual int32_t AfterRecved(RecvBuffer* _buf, UInt32 _bytes) override {
		static const int testMsgLen = 6;
		static BYTE testMsg[] = { "hello~" };

		SendBufferSptr sendBufferSptr = SendBufferManager::Get().Open(BUF_4096);
		memcpy(sendBufferSptr->Buffer(), _buf->ReadPos(), _bytes);
		sendBufferSptr->Close(_bytes);

		printf("server sended : %s\n", sendBufferSptr->Buffer());
		this_thread::sleep_for(2s);
		TrySend(sendBufferSptr);

		return 0;
	};

	virtual void AfterSended(UInt32 _bytes) override {
	}

	virtual void AfterConnected() override {
		static const int testMsgLen = 6;
		static BYTE testMsg[] = { "hello~" };
		SendBufferSptr sendBufferSptr = SendBufferManager::Get().Open(BUF_4096);
		memcpy(sendBufferSptr->Buffer(), testMsg, testMsgLen);
		sendBufferSptr->Close(testMsgLen);
		TrySend(sendBufferSptr);
		return;
	}
};