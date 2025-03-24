#pragma once


#define DECL_GAME_SERVER_SESSION_SEND_PACKET(_msgType, _protocolName)								\
bool SendPacket(const MasterAndGameServer::##_msgType##_protocolName& _packet)						\



class ServerSession : public Session 
{
public:
	~ServerSession();
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public: //session 에서 해당 packet을 보낼 때 쓰는 함수들.
	DECL_GAME_SERVER_SESSION_SEND_PACKET(Ans, MasterServerConnect);
};

