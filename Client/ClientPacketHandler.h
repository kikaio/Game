#pragma once
#include "UserAndGameServerHandle/ReqTestMsg.h"

class BufReader;


class ClientPacketHandler
{
private:
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerReqMap;	//받은 req를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerAnsMap;  //받은 ans를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerNotiMap;  //받은 noti를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerErrMap;  //받은 err를 handle
private:
	static bool HandleUserAndGameServerReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleUserAndGameServerAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleUserAndGameServerNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleUserAndGameServerErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
private:
	static void AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf);
	static void RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _func);
public:
	static void Init();
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
};


