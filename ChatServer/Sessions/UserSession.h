#pragma once

#define DECL_USER_SESSION_SEND_PACKET(_msgType, _protocolType) \
bool SendPacket(const UserAndChatServer::##_msgType##_protocolType& _packet);


class UserSession : public Session {
private :
	ChatUserSptr chatUser = nullptr;
public:
	ChatUserSptr GetChatUser();
	void SetChatUser(ChatUserSptr _user);
public:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	DECL_USER_SESSION_SEND_PACKET(Noti, Chat);
};