#include "pch.h"
#include "UserPacketDiscriminator.h"
#include "ServerDefines.h"

// handler 함수 지정용 define
#define REGIST_PACKET_FUNC(_msgType, _protocol, _func)																\
{																													\
	RegistPacketFunc(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocol, _func);		\
}																													\

#define REGIST_USER_PACKET_FUNC(_msgType, _protocol, _func) {														\
	RegistPacketFunc(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocol, _func);		\
}

#define REGIST_USER_PACKET_HANDLE(_msgType, _protocol) {															\
	REGIST_PACKET_FUNC(_msgType, _protocol, [](SessionSptr _session, BufReader* _brPtr) {							\
		UserAndGameServer::##_msgType##_protocol packet;																\
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());							\
		_brPtr->Close();																							\
		return UserAndGameServerHandle::##_msgType##_protocol(static_pointer_cast<UserSession>(_session), packet);	\
		});																											\
}

USER_AND_GAME_SERVER_FUNC_MAP UserPacketDiscriminator::reqMap;	//받은 req를 handle
USER_AND_GAME_SERVER_FUNC_MAP UserPacketDiscriminator::ansMap;  //받은 ans를 handle
USER_AND_GAME_SERVER_FUNC_MAP UserPacketDiscriminator::notiMap;  //받은 noti를 handle
USER_AND_GAME_SERVER_FUNC_MAP UserPacketDiscriminator::errMap;  //받은 err를 handle


bool UserPacketDiscriminator::DiscriminatorReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = reqMap.find(_protocol);
	if(finder == reqMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return reqMap[_protocol](_session, _brPtr);
}

bool UserPacketDiscriminator::DiscriminatorAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = ansMap.find(_protocol);
	if (finder == ansMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return ansMap[_protocol](_session, _brPtr);
}

bool UserPacketDiscriminator::DiscriminatorNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = notiMap.find(_protocol);
	if (finder == notiMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return notiMap[_protocol](_session, _brPtr);
}

bool UserPacketDiscriminator::DiscriminatorErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = errMap.find(_protocol);
	if (finder == errMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return errMap[_protocol](_session, _brPtr);
}

void UserPacketDiscriminator::AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf)
{
	//todo : logging
	printf("session[%s] try abusing. check please - msg[%d], protocol[%d]\n"
		, _session->GetSId().c_str(), _msgType, _protocol
	);
	return ;
}

void UserPacketDiscriminator::Init()
{
	REGIST_PACKET_FUNC(Ans, TestMsg, [](SessionSptr _session, BufReader* _brPtr){
		printf("handle for AnsTestMsg.\n");
		return false;
	});
	REGIST_USER_PACKET_HANDLE(Req, Login);
	REGIST_USER_PACKET_HANDLE(Req, GameConn);
}

void UserPacketDiscriminator::RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _packetHandle)
{
	switch(_msgType) {
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

bool UserPacketDiscriminator::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	int32_t msgType;
	UserAndGameServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch(msgType) {
	case UserAndGameServer::MsgType::Req : {
		return DiscriminatorReq(_session, UserAndGameServer::MsgType::Req, protocol, &br);
	}
	case UserAndGameServer::MsgType::Ans : {
		return DiscriminatorAns(_session, UserAndGameServer::MsgType::Ans, protocol, &br);
	}
	case UserAndGameServer::MsgType::Noti : {
		return DiscriminatorNoti(_session, UserAndGameServer::MsgType::Noti, protocol, &br);
	}
	case UserAndGameServer::MsgType::Err : {
		return DiscriminatorErr(_session, UserAndGameServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}


IMPL_MAKE_PACKET_FUNC(UserPacketDiscriminator, Noti, ErrInfo);
IMPL_MAKE_PACKET_FUNC(UserPacketDiscriminator, Ans, Login);
IMPL_MAKE_PACKET_FUNC(UserPacketDiscriminator, Ans, GameConn);
