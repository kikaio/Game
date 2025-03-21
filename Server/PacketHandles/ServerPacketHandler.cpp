#include "pch.h"
#include "ServerPacketHandler.h"
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

map<UserAndGameServer::Protocol, PacketFunc*> ServerPacketHandler::userAndGameServerReqMap;	//받은 req를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ServerPacketHandler::userAndGameServerAnsMap;  //받은 ans를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ServerPacketHandler::userAndGameServerNotiMap;  //받은 noti를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ServerPacketHandler::userAndGameServerErrMap;  //받은 err를 handle


bool ServerPacketHandler::HandleUserAndGameServerReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerReqMap.find(_protocol);
	if(finder == userAndGameServerReqMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerReqMap[_protocol](_session, _brPtr);
}

bool ServerPacketHandler::HandleUserAndGameServerAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerAnsMap.find(_protocol);
	if (finder == userAndGameServerAnsMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerAnsMap[_protocol](_session, _brPtr);
}

bool ServerPacketHandler::HandleUserAndGameServerNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerNotiMap.find(_protocol);
	if (finder == userAndGameServerNotiMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerNotiMap[_protocol](_session, _brPtr);
}

bool ServerPacketHandler::HandleUserAndGameServerErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = userAndGameServerErrMap.find(_protocol);
	if (finder == userAndGameServerErrMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return userAndGameServerErrMap[_protocol](_session, _brPtr);
}

void ServerPacketHandler::AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf)
{
	//todo : logging
	printf("session[%s] try abusing. check please - msg[%d], protocol[%d]\n"
		, _session->GetSId().c_str(), _msgType, _protocol
	);
	return ;
}

void ServerPacketHandler::Init()
{
	REGIST_PACKET_FUNC(Ans, TestMsg, [](SessionSptr _session, BufReader* _brPtr){
		printf("handle for AnsTestMsg.\n");
		return false;
	});
	//REGIST_PACKET_FUNC(Req, Chat, [](SessionSptr _session, BufReader* _brPtr){
	//	UserAndGameServer::ReqChat packet;
	//	packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());
	//	_brPtr->Close();
	//	return UserAndGameServerHandle::ReqChat(static_pointer_cast<UserSession>(_session), packet);
	//});
	//REGIST_PACKET_FUNC(Req, Login, [](SessionSptr _session, BufReader* _brPtr){
	//	UserAndGameServer::ReqLogin packet;
	//	packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());
	//	_brPtr->Close();
	//	return UserAndGameServerHandle::ReqLogin(static_pointer_cast<UserSession>(_session), packet);
	//});
	REGIST_USER_PACKET_HANDLE(Req, Chat);
	REGIST_USER_PACKET_HANDLE(Req, Login);
}

void ServerPacketHandler::RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _packetHandle)
{
	switch(_msgType) {
	case UserAndGameServer::MsgType::Req: {
		userAndGameServerReqMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndGameServer::MsgType::Ans: {
		userAndGameServerAnsMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndGameServer::MsgType::Noti: {
		userAndGameServerNotiMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndGameServer::MsgType::Err: {
		userAndGameServerErrMap[_protocol] = _packetHandle;
		break;
	}
	default: {
		//todo : logging
		ASSERT_CRASH("INVALID_MSG_FUNC_REGIST");;
		break;
	}
	}
}

bool ServerPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	int32_t msgType;
	UserAndGameServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch(msgType) {
	case UserAndGameServer::MsgType::Req : {
		return HandleUserAndGameServerReq(_session, UserAndGameServer::MsgType::Req, protocol, &br);
	}
	case UserAndGameServer::MsgType::Ans : {
		return HandleUserAndGameServerAns(_session, UserAndGameServer::MsgType::Ans, protocol, &br);
	}
	case UserAndGameServer::MsgType::Noti : {
		return HandleUserAndGameServerNoti(_session, UserAndGameServer::MsgType::Noti, protocol, &br);
	}
	case UserAndGameServer::MsgType::Err : {
		return HandleUserAndGameServerErr(_session, UserAndGameServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}


IMPL_MAKE_PACKET_FUNC(ServerPacketHandler, Noti, ErrInfo);
IMPL_MAKE_PACKET_FUNC(ServerPacketHandler, Ans, Chat);
IMPL_MAKE_PACKET_FUNC(ServerPacketHandler, Ans, Login);
