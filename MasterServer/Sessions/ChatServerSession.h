#pragma once


#define DECL_CHAT_SERVER_SESSION_SEND_PACKET(_msgType, _protocolName)					\
bool SendPacket(const MasterAndChatServer::##_msgType##_protocolName& _packet)			\




class ChatServerSession : public Session
{
public:
	~ChatServerSession();
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public: //session 에서 해당 packet을 보낼 때 쓰는 함수들.
	DECL_CHAT_SERVER_SESSION_SEND_PACKET(Ans, ChatConnectMaster);
};

