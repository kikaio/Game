#pragma once

#define GET_GSESSION_AND_DUM												\
auto gameSession = static_pointer_cast<GameServerSession>(_session);		\
auto dum = gameSession->GetDummyUser();										\

#define DCLE_GAME_SERVER_SEND_FUNC(_protocolType, _protocolName) \
bool SendPacket##_protocolType##_protocolName(UserAndGameServer::##_protocolType##_protocolName& _packet)


class GameServerSession : public Session
{
private:
	DummyUserWptr dummyUserWptr;

protected:
	virtual bool OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes);
public:
	DCLE_GAME_SERVER_SEND_FUNC(Req, Login);
	DCLE_GAME_SERVER_SEND_FUNC(Req, GameConn);
public:
	void SetDummyUser(DummyUserSptr _dum);
	DummyUserSptr GetDummyUser();
};