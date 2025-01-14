#pragma once

class ServerSession : public Session 
{
public:
	~ServerSession();
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public: //session 에서 해당 packet을 보낼 때 쓰는 함수들.
	
	//bool SendPacket(MasterAndGameServer::AnsMasterServerConnect& _packet);
	DECL_SERVER_SESSION_SEND_GAME_PACKET(Ans, MasterServerConnect);
};

