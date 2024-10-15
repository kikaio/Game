#pragma once
#include "UserAndGameServerHandle/ReqTestMsg.h"


#define DECL_USER_AND_GAMESERVER_HANDLE(_msgType, _protocolName)								\
static bool Handle##_msgType##_protocolName(SessionSptr _session, BufReader* _br)				\


#define DECL_CONVERT_USER_AND_GAMESERVER_PACKET(_msgType, _protocolName)									\
static bool ConverUserAndGameServerPacket##_msgType##_protocolName(SessionSptr _session, BufReader* _brPtr)	\


#define DECL_USER_AND_GAMESERVER_PACKET_HANDLE(_msgType, _protocolName) static bool HandleUserAndGameServer##_msgType##_protocolName(SessionSptr _session, UserAndGameServer::##_msgType##_protocolName& packet) \

//위의 define 3개 종합.
#define USER_AND_GAME_SERVER_DECL_DEFINES(_msgType, _protocolName)				\
	DECL_USER_AND_GAMESERVER_PACKET_HANDLE(_msgType, _protocolName);			\
	DECL_USER_AND_GAMESERVER_HANDLE(_msgType, _protocolName);					\
	DECL_CONVERT_USER_AND_GAMESERVER_PACKET(_msgType, _protocolName);			\



class BufReader;


class ClientPacketHandler
{
private:
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerErrMap;  //받은 err를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerNotiMap;  //받은 noti를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerReqMap;	//받은 req를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerAnsMap;  //받은 ans를 handle
private:
	static void AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf);
public:
	static void Init();
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
private:
	template<typename MSG_TYPE, typename T>
	SendBufferSptr MakeProtoPacket(MSG_TYPE _msgType, T& _packet);
	USER_AND_GAME_SERVER_DECL_DEFINES(Req, TestMsg);

};


