#pragma once

#define GET_CHAT_SERVER_SESSION_AND_DUM										\
auto chatSession = static_pointer_cast<ChatServerSession>(_session);		\
auto dum = chatSession->GetDummyUser();										\


#define DECL_CHAT_SERVER_SEND_FUNC(_msgType, _protocolType)						\
bool SendPacket(const UserAndChatServer::##_msgType##_protocolType& _packet)	\



class ChatServerSession : public Session
{
private:
	DummyUserWptr dummyUserWptr;

protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	void SetDummyUser(DummyUserSptr _dum);
	DummyUserSptr GetDummyUser();
public:
	DECL_CHAT_SERVER_SEND_FUNC(Req, ChatConn);
	DECL_CHAT_SERVER_SEND_FUNC(Req, Chat);
};
