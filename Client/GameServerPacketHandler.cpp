#include "pch.h"
#include "GameServerPacketHandler.h"

#define REGIST_GAME_SERVER_PACKET_FUNC(_msgType, _protocol, _func)																\
{																													\
	RegistPacketFunc(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocol, _func);		\
}																													\

#define FOR_GAME_SERVER_PACKET_HANDLE_FUNC(_msgType, _protocolName)														\
[](SessionSptr _session, BufReader* _brPtr)																				\
{																														\
	UserAndGameServer::##_msgType##_protocolName packet;																\
	packet.ParseFromArray(_brPtr->Buffer()+_brPtr->ReadSize(), _brPtr->FreeSize());										\
	_brPtr->Close();																									\
																														\
	return UserAndGameServerHandle::##_msgType##_protocolName(_session, packet);										\
}																														\

#define REGIST_GAME_SERVER_HANDLE(_msgType, _protocolName)																	\
{																															\
	REGIST_GAME_SERVER_PACKET_FUNC(_msgType, _protocolName, FOR_GAME_SERVER_PACKET_HANDLE_FUNC(_msgType, _protocolName));	\
}																															\


map<UserAndGameServer::Protocol, PacketFunc*> GameServerPacketHandler::userAndGameServerReqMap;	//받은 req를 handle
map<UserAndGameServer::Protocol, PacketFunc*> GameServerPacketHandler::userAndGameServerAnsMap;  //받은 ans를 handle
map<UserAndGameServer::Protocol, PacketFunc*> GameServerPacketHandler::userAndGameServerNotiMap;  //받은 noti를 handle
map<UserAndGameServer::Protocol, PacketFunc*> GameServerPacketHandler::userAndGameServerErrMap;  //받은 err를 handle



bool GameServerPacketHandler::HandleUserAndGameServerReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerReqMap.find(_protocol);
	if (finder == userAndGameServerReqMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerReqMap[_protocol](_session, _brPtr);
}

bool GameServerPacketHandler::HandleUserAndGameServerAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerAnsMap.find(_protocol);
	if (finder == userAndGameServerAnsMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerAnsMap[_protocol](_session, _brPtr);
}

bool GameServerPacketHandler::HandleUserAndGameServerNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerNotiMap.find(_protocol);
	if (finder == userAndGameServerNotiMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerNotiMap[_protocol](_session, _brPtr);
}

bool GameServerPacketHandler::HandleUserAndGameServerErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerErrMap.find(_protocol);
	if (finder == userAndGameServerErrMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerErrMap[_protocol](_session, _brPtr);
}


void GameServerPacketHandler::AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf)
{
}

void GameServerPacketHandler::RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _func)
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

void GameServerPacketHandler::Init()
{
	// msgType, protocolName을 처리하는 function을 각각의 map에 연결해준다.
	//각 msg, packet에 대한 handler를 호출해주는 function을 연결해주는 과정을 여기서 진행한다.
	REGIST_GAME_SERVER_HANDLE(Req, TestMsg);
	REGIST_GAME_SERVER_HANDLE(Ans, Chat);
	return;
}

bool GameServerPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	UserAndGameServer::MsgType msgType;
	br >> msgType;
	
	UserAndGameServer::Protocol protocol = UserAndGameServer::Protocol::INVALID_PROTOCOL;
	br >> protocol;

	switch(msgType) {
	case UserAndGameServer::MsgType::Req: {
		return HandleUserAndGameServerReq(_session, msgType, protocol, &br);
	}
	case UserAndGameServer::MsgType::Ans: {
		return HandleUserAndGameServerAns(_session, msgType, protocol, &br);
		break;
	}
	case UserAndGameServer::MsgType::Noti : {
		return HandleUserAndGameServerNoti(_session, msgType, protocol, &br);
		break;
	}
	case UserAndGameServer::MsgType::Err: {
		return HandleUserAndGameServerErr(_session, msgType, protocol, &br);
		break;
	}
	default: {
		break;
	}
	}
	return false;
}
