#include "pch.h"
#include "ClientPacketHandler.h"

#define REGIST_PACKET_FUNC(_msgType, _protocol, _func)																\
{																													\
	RegistPacketFunc(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocol, _func);		\
}																													\

#define DECL_PACKET_HANDLE_FUNC(_msgType, _protocolName)																\
[](SessionSptr _session, BufReader* _brPtr)																				\
{																														\
	UserAndGameServer::##_msgType##_protocolName packet;																\
	packet.ParseFromArray(_brPtr->Buffer(), _brPtr->FreeSize());														\
	_brPtr->Close();																									\
																														\
	return UserAndGameServerHandle::##_msgType##_protocolName(_session, packet);										\
};																														\

#define REGIST_USER_AND_GAMESERVER_FUNC(_msgType, _protocolName)																	\
{																																	\
	userAndGameServerReqMap[UserAndGameServer::Protocol::##_protocolName] = DECL_PACKET_HANDLE_FUNC(_msgType, _protocolName);		\
}																																	\



map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerReqMap;	//받은 req를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerAnsMap;  //받은 ans를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerNotiMap;  //받은 noti를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerErrMap;  //받은 err를 handle



bool ClientPacketHandler::HandleUserAndGameServerReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerReqMap.find(_protocol);
	if (finder == userAndGameServerReqMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerReqMap[_protocol](_session, _brPtr);
}

bool ClientPacketHandler::HandleUserAndGameServerAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerAnsMap.find(_protocol);
	if (finder == userAndGameServerAnsMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerAnsMap[_protocol](_session, _brPtr);
}

bool ClientPacketHandler::HandleUserAndGameServerNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerNotiMap.find(_protocol);
	if (finder == userAndGameServerNotiMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerNotiMap[_protocol](_session, _brPtr);
}

bool ClientPacketHandler::HandleUserAndGameServerErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerErrMap.find(_protocol);
	if (finder == userAndGameServerErrMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerErrMap[_protocol](_session, _brPtr);
}


void ClientPacketHandler::AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf)
{
}

void ClientPacketHandler::RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _func)
{
	switch(_msgType) {
	case UserAndGameServer::MsgType::Req : {
		userAndGameServerReqMap[_protocol] = _func;
		break;
	}
	case UserAndGameServer::MsgType::Ans: {
		userAndGameServerAnsMap[_protocol] = _func;
		break;
	}
	case UserAndGameServer::MsgType::Noti: {
		userAndGameServerNotiMap[_protocol] = _func;
		break;
	}
	case UserAndGameServer::MsgType::Err: {
		userAndGameServerErrMap[_protocol] = _func;
		break;
	}
	default: {
		ASSERT_CRASH("INVALID MSG TYPE RTEGIST");
		break;
	}
	}
	return ;
}

void ClientPacketHandler::Init()
{
	// msgType, protocolName을 처리하는 function을 각각의 map에 연결해준다.
	REGIST_USER_AND_GAMESERVER_FUNC(Req, TestMsg);
	return;
}

bool ClientPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	UserAndGameServer::MsgType msgType;
	br >> msgType;
	
	UserAndGameServer::Protocol protocol = UserAndGameServer::Protocol::INVALID_PROTOCOL;
	br >> protocol;

	switch(msgType) {
	case UserAndGameServer::MsgType::Err : {
		break;
	}
	case UserAndGameServer::MsgType::Noti : {
		break;
	}
	case UserAndGameServer::MsgType::Req : {
		return HandleUserAndGameServerReq(_session, msgType, protocol, &br);
	}
	case UserAndGameServer::MsgType::Ans : {
		break;
	}
	default: {
		break;
	}
	}
	return false;
}
