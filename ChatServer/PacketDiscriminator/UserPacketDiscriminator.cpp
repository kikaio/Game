#include "pch.h"
#include "UserPacketDiscriminator.h"


// handler 함수 지정용 define

#define REGIST_USER_CLIENT_PACKET_FUNC(_msgType, _protocol, _func) {											\
	RegistPacketFunc(UserAndChatServer::MsgType::##_msgType, UserAndChatServer::Protocol::##_protocol, _func);	\
}

#define REGIST_USER_CLIENT_PACKET_HANDLE(_msgType, _protocol) {														\
	REGIST_USER_CLIENT_PACKET_FUNC(_msgType, _protocol, [](SessionSptr _session, BufReader* _brPtr) {				\
		UserAndChatServer::##_msgType##_protocol packet;															\
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());							\
		_brPtr->Close();																							\
		return UserAndChatPacketHandle::##_msgType##_protocol(static_pointer_cast<UserSession>(_session), packet);	\
		});																											\
}


#define IMPL_MAKE_SENDBUF_USER_CLIENT_PACKET(_msgType, _protocolName)																			\
SendBufferSptr UserPacketDiscriminator::MakePacket##_msgType##_protocolName(const UserAndChatServer::##_msgType##_protocolName& _packet)		\
{																																				\
	return MakeProtoSendBuffer(UserAndChatServer::MsgType::##_msgType, UserAndChatServer::Protocol::##_protocolName, _packet);					\
}																																				\


USER_PACKET_PROTOCOL_FUNC_MAP UserPacketDiscriminator::reqMap;	//받은 req를 handle
USER_PACKET_PROTOCOL_FUNC_MAP UserPacketDiscriminator::ansMap;  //받은 ans를 handle
USER_PACKET_PROTOCOL_FUNC_MAP UserPacketDiscriminator::notiMap;  //받은 noti를 handle
USER_PACKET_PROTOCOL_FUNC_MAP UserPacketDiscriminator::errMap;  //받은 err를 handle



bool UserPacketDiscriminator::DiscriminateReq(SessionSptr _session
	, UserAndChatServer::MsgType _msgType, UserAndChatServer::Protocol _protocol
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

bool UserPacketDiscriminator::DiscriminateAns(SessionSptr _session
	, UserAndChatServer::MsgType _msgType, UserAndChatServer::Protocol _protocol
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

bool UserPacketDiscriminator::DiscriminateNoti(SessionSptr _session
	, UserAndChatServer::MsgType _msgType, UserAndChatServer::Protocol _protocol
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

bool UserPacketDiscriminator::DiscriminateErr(SessionSptr _session
	, UserAndChatServer::MsgType _msgType, UserAndChatServer::Protocol _protocol
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


void UserPacketDiscriminator::AbusingRecord(SessionSptr _session
	, int32_t _msgType, int32_t _protocol
	, BufReader* _buf
)
{
	//todo : logging
	printf("session[%s] try abusing. check please - msg[%d], protocol[%d]\n"
		, _session->GetSId().c_str(), _msgType, _protocol
	);
	return;
}

void UserPacketDiscriminator::Init()
{
	REGIST_USER_CLIENT_PACKET_HANDLE(Req, ChatConn);
	REGIST_USER_CLIENT_PACKET_HANDLE(Req, Chat);
}

void UserPacketDiscriminator::RegistPacketFunc(UserAndChatServer::MsgType _msgType
	, UserAndChatServer::Protocol _protocol
	, PacketFunc* _packetHandle
)
{
	switch (_msgType) {
	case UserAndChatServer::MsgType::Req: {
		reqMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndChatServer::MsgType::Ans: {
		ansMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndChatServer::MsgType::Noti: {
		notiMap[_protocol] = _packetHandle;
		break;
	}
	case UserAndChatServer::MsgType::Err: {
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
	UserAndChatServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch (msgType) {
	case UserAndChatServer::MsgType::Req: {
		return DiscriminateReq(_session, UserAndChatServer::MsgType::Req, protocol, &br);
	}
	case UserAndChatServer::MsgType::Ans: {
		return DiscriminateAns(_session, UserAndChatServer::MsgType::Ans, protocol, &br);
	}
	case UserAndChatServer::MsgType::Noti: {
		return DiscriminateNoti(_session, UserAndChatServer::MsgType::Noti, protocol, &br);
	}
	case UserAndChatServer::MsgType::Err: {
		return DiscriminateErr(_session, UserAndChatServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}

IMPL_MAKE_SENDBUF_USER_CLIENT_PACKET(Noti, Chat);
IMPL_MAKE_SENDBUF_USER_CLIENT_PACKET(Ans, ChatConn);
