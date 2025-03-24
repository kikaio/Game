#include "pch.h"
#include "GamePacketHandler.h"

// handler 함수 지정용 define
#define REGIST_GAME_PACKET_FUNC(_msgType, _protocol, _func)																\
{																														\
	RegistPacketFunc(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocol, _func);		\
}																														\


#define REGIST_HANDLE_GAME_PACKET_FUNC(_msgType, _protocol)																		\
{																																\
	REGIST_GAME_PACKET_FUNC(_msgType, _protocol, [](SessionSptr _session, BufReader* _brPtr){									\
		MasterAndGameServer::##_msgType##_protocol packet;																		\
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());										\
		_brPtr->Close();																										\
		return MasterAndGameServerHandle::##_msgType##_protocol(static_pointer_cast<ServerSession>(_session), packet);			\
	});																															\
}



#define IMPL_MAKE_GAME_PACKET_FUNC(_msgType, _protocolName)																				\
SendBufferSptr GamePacketHandler::MakePacket##_msgType##_protocolName(const MasterAndGameServer::##_msgType##_protocolName& _packet)	\
{																																		\
	return MakeProtoSendBuffer(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocolName, _packet);		\
}																																		\


GAME_PACKET_FUNC_MAP GamePacketHandler::reqMap;
GAME_PACKET_FUNC_MAP GamePacketHandler::ansMap;
GAME_PACKET_FUNC_MAP GamePacketHandler::notiMap;
GAME_PACKET_FUNC_MAP GamePacketHandler::errMap;

bool GamePacketHandler::HandleMasterAndGameServerReq(SessionSptr _session
	, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol
	, BufReader* _brPtr
	)
{
	auto finder = reqMap.find(_protocol);
	if (finder == reqMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return reqMap[_protocol](_session, _brPtr);
}

bool GamePacketHandler::HandleMasterAndGameServerAns(SessionSptr _session
	, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol
	, BufReader* _brPtr
	)
{
	auto finder = ansMap.find(_protocol);
	if (finder == ansMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return ansMap[_protocol](_session, _brPtr);
}

bool GamePacketHandler::HandleMasterAndGameServerNoti(SessionSptr _session
	, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol
	, BufReader* _brPtr
	)
{
	auto finder = notiMap.find(_protocol);
	if (finder == notiMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return notiMap[_protocol](_session, _brPtr);
}

bool GamePacketHandler::HandleMasterAndGameServerErr(SessionSptr _session
	, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol
	, BufReader* _brPtr
	)
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
	//REGIST_GAME_PACKET_FUNC(Req, MasterServerConnect, [](SessionSptr _session, BufReader* _brPtr) {
	//	printf("handle MasterServerConnect called\n");
	//	return false;
	//});

	//해당 prc에 대한 packet을 생성 및 실제 처리하는 handle인 MasterAndGameServerHandle의 함수를 호출한다.
	REGIST_HANDLE_GAME_PACKET_FUNC(Req, MasterServerConnect);
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


IMPL_MAKE_GAME_PACKET_FUNC(Ans, MasterServerConnect);

