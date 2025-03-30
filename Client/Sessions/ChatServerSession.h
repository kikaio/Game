#pragma once

#define GET_CHAT_SERVER_ESSION_AND_DUM										\
auto chatSession = static_pointer_cast<ChatServerSession>(_session);		\
auto dum = chatSession->GetDummyUser();										\

#define DECL_CHAT_SERVER_SEND_FUNC(_protocolType, _protocolName) \
bool SendPacket##_protocolType##_protocolName(UserAndChatServer::##_protocolType##_protocolName& _packet)


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
};
