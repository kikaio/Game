#pragma once

class ServerSession : public Session 
{
public:
	~ServerSession();
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
};