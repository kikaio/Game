#include "pch.h"
#include "GameServerDiscriminator.h"

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


USER_AND_GAME_FUNC_MAP  GameServerDiscriminator::reqMap;	//받은 req를 handle
USER_AND_GAME_FUNC_MAP  GameServerDiscriminator::ansMap;  //받은 ans를 handle
USER_AND_GAME_FUNC_MAP  GameServerDiscriminator::notiMap;  //받은 noti를 handle
USER_AND_GAME_FUNC_MAP  GameServerDiscriminator::errMap;  //받은 err를 handle


bool GameServerDiscriminator::DiscriminateReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = reqMap.find(_protocol);
	if (finder == reqMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return reqMap[_protocol](_session, _brPtr);
}

bool GameServerDiscriminator::DiscriminateAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = ansMap.find(_protocol);
	if (finder == ansMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return ansMap[_protocol](_session, _brPtr);
}

bool GameServerDiscriminator::DiscriminateNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = notiMap.find(_protocol);
	if (finder == notiMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return notiMap[_protocol](_session, _brPtr);
}

bool GameServerDiscriminator::DiscriminateErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = errMap.find(_protocol);
	if (finder == errMap.end()) {
		//abusing 기록
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return errMap[_protocol](_session, _brPtr);
}


void GameServerDiscriminator::AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf)
{
}

void GameServerDiscriminator::RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _func)
{
	switch(_msgType) {
	case UserAndGameServer::MsgType::Req : {
		reqMap[_protocol] = _func;
		break;
	}
	case UserAndGameServer::MsgType::Ans: {
		ansMap[_protocol] = _func;
		break;
	}
	case UserAndGameServer::MsgType::Noti: {
		notiMap[_protocol] = _func;
		break;
	}
	case UserAndGameServer::MsgType::Err: {
		errMap[_protocol] = _func;
		break;
	}
	default: {
		ASSERT_CRASH("INVALID MSG TYPE RTEGIST");
		break;
	}
	}
	return ;
}

void GameServerDiscriminator::Init()
{
	// msgType, protocolName을 처리하는 function을 각각의 map에 연결해준다.
	//각 msg, packet에 대한 handler를 호출해주는 function을 연결해주는 과정을 여기서 진행한다.
	REGIST_GAME_SERVER_HANDLE(Req, TestMsg);
	REGIST_GAME_SERVER_HANDLE(Ans, Login);
	REGIST_GAME_SERVER_HANDLE(Ans, GameConn);
	return;
}

bool GameServerDiscriminator::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	UserAndGameServer::MsgType msgType;
	br >> msgType;
	
	UserAndGameServer::Protocol protocol = UserAndGameServer::Protocol::INVALID_PROTOCOL;
	br >> protocol;
	bool ret = false;
	switch(msgType) {
	case UserAndGameServer::MsgType::Req: {
		ret = DiscriminateReq(_session, msgType, protocol, &br);
		break;
	}
	case UserAndGameServer::MsgType::Ans: {
		ret = DiscriminateAns(_session, msgType, protocol, &br);
		break;
	}
	case UserAndGameServer::MsgType::Noti : {
		ret = DiscriminateNoti(_session, msgType, protocol, &br);
		break;
	}
	case UserAndGameServer::MsgType::Err: {
		ret = DiscriminateErr(_session, msgType, protocol, &br);
		break;
	}
	default: {
		break;
	}
	}

	//todo : dum에게 어떤 packet에 대한 처리가 완료되었는지 통보.
	if(ret == true) {
		GameServerSessionSptr _gsSession = static_pointer_cast<GameServerSession>(_session);
		auto dummy = _gsSession->GetDummyUser();
		if(dummy != nullptr) {
			dummy->RecvGameServerProtocol(msgType, protocol);
		}
	}
	return ret;
}
