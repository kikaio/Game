#pragma once

class UserSession : public Session
{
public:
	virtual int32_t AfterRecved(RecvBuffer* _buf, UInt32 _bytes) {
		static BYTE testMsg[] = { "hello~" };
		SendBufferSptr sendBufferSptr = MakeShared<SendBuffer>(4096);
		sendBufferSptr->CopyData(testMsg, 6);
		TrySend(sendBufferSptr);
		return 0;
	};

	virtual void AfterSended(UInt32 _bytes) {
		printf("send bytes : %d\n", _bytes);
	}
};