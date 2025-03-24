#pragma once

#define DECL_MASTER_SERVER_SESSION_SEND_PACKET(_msgType, _protocolType)			\
bool SendPacket(const MasterAndChatServer::##_msgType##_protocolType& _packet)	\

class MasterServerSession : public Session {
public:
	~MasterServerSession();
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	DECL_MASTER_SERVER_SESSION_SEND_PACKET(Req, ChatConnectMaster);
};