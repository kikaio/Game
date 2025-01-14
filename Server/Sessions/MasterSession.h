#pragma once

class MasterSession : public Session
{
public:
	~MasterSession();
protected:
	//virtual void AfterSended(UInt32 _bytes) {
	//	printf("send bytes : %d\n", _bytes);
	//}
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	DECL_MASTER_SESSION_SEND_PACKET(Req, MasterServerConnect);
};