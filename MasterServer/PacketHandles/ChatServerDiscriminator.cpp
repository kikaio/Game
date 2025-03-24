#include "pch.h"
#include "ChatServerDiscriminator.h"


// handler 함수 지정용 define
#define REGIST_CHAT_PACKET_FUNC(_msgType, _protocol, _func)																\
{																														\
	RegistPacketFunc(MasterAndChatServer::MsgType::##_msgType, MasterAndChatServer::Protocol::##_protocol, _func);		\
}																														\


#define REGIST_CHAT_PACKET_HANDLE_FUNC(_msgType, _protocol)																			\
{																																	\
	REGIST_CHAT_PACKET_FUNC(_msgType, _protocol, [](SessionSptr _session, BufReader* _brPtr){										\
		MasterAndChatServer::##_msgType##_protocol packet;																			\
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());											\
		_brPtr->Close();																											\
		return MasterAndChatServerHandle::##_msgType##_protocol(static_pointer_cast<ChatServerSession>(_session), packet);			\
	});																																\
}

#define IMPL_CHAT_PACKET_MAKE_FUNC(_msgType, _protocolName) \
SendBufferSptr ChatServerDiscriminator::MakePacket##_msgType##_protocolName(const MasterAndChatServer::##_msgType##_protocolName& _packet)					\
{																																							\
	return MakeProtoSendBuffer(MasterAndChatServer::MsgType::##_msgType, MasterAndChatServer::Protocol::##_protocolName, _packet);							\
}																																							\



CHAT_PACKET_FUNC_MAP ChatServerDiscriminator::reqMap;
CHAT_PACKET_FUNC_MAP ChatServerDiscriminator::ansMap;
CHAT_PACKET_FUNC_MAP ChatServerDiscriminator::notiMap;
CHAT_PACKET_FUNC_MAP ChatServerDiscriminator::errMap;

bool ChatServerDiscriminator::DiscriminateReq(SessionSptr _session
	, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol
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

bool ChatServerDiscriminator::DiscriminateAns(SessionSptr _session
	, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol
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

bool ChatServerDiscriminator::DiscriminateNoti(SessionSptr _session
	, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol
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

bool ChatServerDiscriminator::DiscriminateErr(SessionSptr _session
	, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol
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

void ChatServerDiscriminator::AbusingRecord(SessionSptr _session
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

void ChatServerDiscriminator::Init()
{
	//master server가 처리할 packet handle을 지정한다.
	//해당 prc에 대한 packet을 생성 및 실제 처리하는 handle인 MasterAndGameServerHandle의 함수를 호출한다.
	REGIST_CHAT_PACKET_HANDLE_FUNC(Req, ChatConnectMaster);
}

void ChatServerDiscriminator::RegistPacketFunc(MasterAndChatServer::MsgType _msg_type, MasterAndChatServer::Protocol _protocol, PacketFunc* _packetHandle)
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

bool ChatServerDiscriminator::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	int32_t msgType;
	MasterAndChatServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch (msgType) {
	case UserAndGameServer::MsgType::Req: {
		return DiscriminateReq(_session, MasterAndChatServer::MsgType::Req, protocol, &br);
	}
	case UserAndGameServer::MsgType::Ans: {
		return DiscriminateAns(_session, MasterAndChatServer::MsgType::Ans, protocol, &br);
	}
	case UserAndGameServer::MsgType::Noti: {
		return DiscriminateNoti(_session, MasterAndChatServer::MsgType::Noti, protocol, &br);
	}
	case UserAndGameServer::MsgType::Err: {
		return DiscriminateErr(_session, MasterAndChatServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}

IMPL_CHAT_PACKET_MAKE_FUNC(Ans, ChatConnectMaster);
