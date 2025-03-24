#include "pch.h"
#include "MasterPacketDiscriminator.h"



// handler 함수 지정용 define

#define REGIST_MASTER_PACKET_FUNC(_msgType, _protocol, _func) {														\
	RegistPacketFunc(MasterAndChatServer::MsgType::##_msgType, MasterAndChatServer::Protocol::##_protocol, _func);	\
}


#define REGIST_MASTER_PACKET_HANDLE(_msgType, _protocol) {																		\
	REGIST_MASTER_PACKET_FUNC(_msgType, _protocol, [](SessionSptr _session, BufReader* _brPtr) {								\
		MasterAndChatServer::##_msgType##_protocol packet;																		\
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());										\
		_brPtr->Close();																										\
		return MasterAndChatPacketHandle::##_msgType##_protocol(static_pointer_cast<MasterServerSession>(_session), packet);	\
		});																														\
}


#define MASTER_IMPL_MAKE_SENDBUF_FROM_PACKET(_msgType, _protocolName)																				\
SendBufferSptr MasterPacketDiscriminator::MakePacket##_msgType##_protocolName(const MasterAndChatServer::##_msgType##_protocolName& _packet)		\
{																																					\
	return MakeProtoSendBuffer(MasterAndChatServer::MsgType::##_msgType, MasterAndChatServer::Protocol::##_protocolName, _packet);					\
}																																					\



MASTER_PROTOCOL_FUN_MAP MasterPacketDiscriminator::reqMap;	//받은 req를 handle
MASTER_PROTOCOL_FUN_MAP MasterPacketDiscriminator::ansMap;  //받은 ans를 handle
MASTER_PROTOCOL_FUN_MAP MasterPacketDiscriminator::notiMap;  //받은 noti를 handle
MASTER_PROTOCOL_FUN_MAP MasterPacketDiscriminator::errMap;  //받은 err를 handle



bool MasterPacketDiscriminator::DiscriminateReq(SessionSptr _session
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

bool MasterPacketDiscriminator::DiscriminateAns(SessionSptr _session
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

bool MasterPacketDiscriminator::DiscriminateNoti(SessionSptr _session
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

bool MasterPacketDiscriminator::DiscriminateErr(SessionSptr _session
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


void MasterPacketDiscriminator::AbusingRecord(SessionSptr _session
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

void MasterPacketDiscriminator::Init()
{
	REGIST_MASTER_PACKET_HANDLE(Noti, ErrInfo);
}


void MasterPacketDiscriminator::RegistPacketFunc(MasterAndChatServer::MsgType _msgType
	, MasterAndChatServer::Protocol _protocol
	, PacketFunc* _packetHandle
	)
{
	switch (_msgType) {
	case MasterAndChatServer::MsgType::Req: {
		reqMap[_protocol] = _packetHandle;
		break;
	}
	case MasterAndChatServer::MsgType::Ans: {
		ansMap[_protocol] = _packetHandle;
		break;
	}
	case MasterAndChatServer::MsgType::Noti: {
		notiMap[_protocol] = _packetHandle;
		break;
	}
	case MasterAndChatServer::MsgType::Err: {
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


bool MasterPacketDiscriminator::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	int32_t msgType;
	MasterAndChatServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch (msgType) {
	case MasterAndChatServer::MsgType::Req: {
		return DiscriminateReq(_session, MasterAndChatServer::MsgType::Req, protocol, &br);
	}
	case MasterAndChatServer::MsgType::Ans: {
		return DiscriminateAns(_session, MasterAndChatServer::MsgType::Ans, protocol, &br);
	}
	case MasterAndChatServer::MsgType::Noti: {
		return DiscriminateNoti(_session, MasterAndChatServer::MsgType::Noti, protocol, &br);
	}
	case MasterAndChatServer::MsgType::Err: {
		return DiscriminateErr(_session, MasterAndChatServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}


//내가 보내는 것들에 대한 define
MASTER_IMPL_MAKE_SENDBUF_FROM_PACKET(Req, ChatConnectMaster);

