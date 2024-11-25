#include "pch.h"
#include "GamePacketHandler.h"

// handler 함수 지정용 define
#define REGIST_GAME_PACKET_FUNC(_msgType, _protocol, _func)																\
{																														\
	RegistPacketFunc(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocol, _func);		\
}																														\


map<MasterAndGameServer::Protocol, PacketFunc*> GamePacketHandler::reqMap;
map<MasterAndGameServer::Protocol, PacketFunc*> GamePacketHandler::ansMap;
map<MasterAndGameServer::Protocol, PacketFunc*> GamePacketHandler::notiMap;
map<MasterAndGameServer::Protocol, PacketFunc*> GamePacketHandler::errMap;

bool GamePacketHandler::HandleMasterAndGameServerReq(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = reqMap.find(_protocol);
	if (finder == reqMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return reqMap[_protocol](_session, _brPtr);
}

bool GamePacketHandler::HandleMasterAndGameServerAns(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = ansMap.find(_protocol);
	if (finder == ansMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return ansMap[_protocol](_session, _brPtr);
}

bool GamePacketHandler::HandleMasterAndGameServerNoti(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = notiMap.find(_protocol);
	if (finder == notiMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return notiMap[_protocol](_session, _brPtr);
}

bool GamePacketHandler::HandleMasterAndGameServerErr(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = errMap.find(_protocol);
	if (finder == errMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return errMap[_protocol](_session, _brPtr);
}

void GamePacketHandler::AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf)
{
	//todo : logging
	printf("session[%s] try abusing. check please - msg[%d], protocol[%d]\n"
		, _session->GetSId().c_str(), _msgType, _protocol
	);
	return;
}

void GamePacketHandler::Init()
{
	//master server가 처리할 packet handle을 지정한다.
	REGIST_GAME_PACKET_FUNC(Req, MasterServerConnect, [](SessionSptr _session, BufReader* _brPtr) {
		printf("handle MasterServerConnect called\n");
		return false;
	});
}

void GamePacketHandler::RegistPacketFunc(MasterAndGameServer::MsgType _msg_type, MasterAndGameServer::Protocol _protocol, PacketFunc* _packetHandle)
{
	switch (_msg_type) {
	case UserAndGameServer::MsgType::Req: {
		reqMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndGameServer::MsgType::Ans: {
		ansMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndGameServer::MsgType::Noti: {
		notiMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndGameServer::MsgType::Err: {
		errMap[_protocol] = _packetHandle;
		break;
	}
	default: {
		//todo : logging
		ASSERT_CRASH("INVALID_MSG_FUNC_REGIST");;
		break;
	}
	}
}

bool GamePacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	int32_t msgType;
	MasterAndGameServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch (msgType) {
	case UserAndGameServer::MsgType::Req: {
		return HandleMasterAndGameServerReq(_session, MasterAndGameServer::MsgType::Req, protocol, &br);
	}
	case UserAndGameServer::MsgType::Ans: {
		return HandleMasterAndGameServerAns(_session, MasterAndGameServer::MsgType::Ans, protocol, &br);
	}
	case UserAndGameServer::MsgType::Noti: {
		return HandleMasterAndGameServerNoti(_session, MasterAndGameServer::MsgType::Noti, protocol, &br);
	}
	case UserAndGameServer::MsgType::Err: {
		return HandleMasterAndGameServerErr(_session, MasterAndGameServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}

//IMPL_MAKE_PACKET_GAME_FUNC(Ans, MasterServerConnect);