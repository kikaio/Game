#pragma once

#define DECL_USER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool SendPacket(const UserAndGameServer::##_msgType##_protocolName& _packet)						\


class UserSession : public Session
{
private:
	GameUserSptr gameUser = nullptr;
public:
	UserSession();
public:
	~UserSession();
protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	GameUserSptr GetGameUser();
public:
	bool SendError(const UserAndGameServer::NotiErrInfo& _err);
	bool SendError(const PacketError& _err);
public:
	DECL_USER_SESSION_SEND_PACKET(Noti, ErrInfo);
	DECL_USER_SESSION_SEND_PACKET(Ans, Login);
	DECL_USER_SESSION_SEND_PACKET(Ans, GameConn);
};