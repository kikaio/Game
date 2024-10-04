#pragma once

class DummySession : public Session
{
public:
	virtual int32_t AfterRecved(RecvBuffer* _buf, UInt32 _bytes) {
		static const int testMsgLen = 6;
		static BYTE testMsg[] = { "hello~" };
		this_thread::sleep_for(5s);

		SendBufferSptr sendBufferSptr = MakeShared<SendBuffer>(BUF_4096);
		sendBufferSptr->CopyData(testMsg, testMsgLen);
		TrySend(sendBufferSptr);

		return 0;
	};

	virtual void AfterSended(UInt32 _bytes) {
		printf("send bytes : %d\n", _bytes);
	}

	virtual void AfterConnected() {
		static const int testMsgLen = 6;
		static BYTE testMsg[] = { "hello~" };
		SendBufferSptr sendBufferSptr = MakeShared<SendBuffer>(BUF_4096);
		sendBufferSptr->CopyData(testMsg, testMsgLen);
		TrySend(sendBufferSptr);
		return;
	}
};