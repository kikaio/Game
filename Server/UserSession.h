#pragma once

class UserSession : public Session
{
public:
	~UserSession();
public:
	virtual int32_t AfterRecved(RecvBuffer* _buf, UInt32 _bytes) {

		SendBufferSptr sendBufferSptr = SendBufferManager::Get().Open(BUF_4096);
		memcpy(sendBufferSptr->Buffer(), _buf, _bytes);
		sendBufferSptr->Close(_bytes);
		TrySend(sendBufferSptr);

		return 0;
	};

	virtual void AfterSended(UInt32 _bytes) {
		printf("send bytes : %d\n", _bytes);
	}
};