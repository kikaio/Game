#include "pch.h"
#include "MasterPacketDiscriminator.h"

// handler 함수 지정용 define
#define REGIST_MASTER_PACKET_FUNC(_msgType, _protocol, _func)																\
{																															\
	RegistPacketFunc(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocol, _func);			\
}																															\


#define IMPL_REGIST_MASTER_PACKET(_msgType, _protocol)																		\
{																															\
	REGIST_MASTER_PACKET_FUNC(_msgType, _protocol, [](SessionSptr _session, BufReader* _brPtr) {							\
		MasterAndGameServer::##_msgType##_protocol packet;																	\
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());									\
		_brPtr->Close();																									\
		return MasterAndGameServerHandle::##_msgType##_protocol(static_pointer_cast<MasterSession>(_session), packet);		\
		}																													\
	);																														\
}																															\


#define IMPL_MAKE_MASTER_PACKET_FUNC(_msgType, _protocolName)																			\
SendBufferSptr MasterPacketDiscriminator::MakePacket##_msgType##_protocolName(const MasterAndGameServer::##_msgType##_protocolName& _packet)	\
{																																		\
	return MakeProtoSendBuffer(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocolName, _packet);		\
}																																		\



MASTER_AND_GAME_FUNC_MAP MasterPacketDiscriminator::reqMap;	//받은 req를 handle
MASTER_AND_GAME_FUNC_MAP MasterPacketDiscriminator::ansMap;  //받은 ans를 handle
MASTER_AND_GAME_FUNC_MAP MasterPacketDiscriminator::notiMap;  //받은 noti를 handle
MASTER_AND_GAME_FUNC_MAP MasterPacketDiscriminator::errMap;  //받은 err를 handle


bool MasterPacketDiscriminator::DiscriminateReq(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = reqMap.find(_protocol);
	if(finder == reqMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return reqMap[_protocol](_session, _brPtr);
}

bool MasterPacketDiscriminator::DiscriminateAns(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = ansMap.find(_protocol);
	if (finder == ansMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return ansMap[_protocol](_session, _brPtr);
}

bool MasterPacketDiscriminator::DiscriminateNoti(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = notiMap.find(_protocol);
	if (finder == notiMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return notiMap[_protocol](_session, _brPtr);
}

bool MasterPacketDiscriminator::DiscriminateErr(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = errMap.find(_protocol);
	if (finder == errMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return errMap[_protocol](_session, _brPtr);
}

void MasterPacketDiscriminator::AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf)
{
	//todo : logging
	printf("session[%s] try abusing. check please - msg[%d], protocol[%d]\n"
		, _session->GetSId().c_str(), _msgType, _protocol
	);
	return ;
}

void MasterPacketDiscriminator::Init()
{
	IMPL_REGIST_MASTER_PACKET(Ans, MasterServerConnect);
}

void MasterPacketDiscriminator::RegistPacketFunc(MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, PacketFunc* _packetHandle)
{
	switch(_msgType) {
	case MasterAndGameServer::MsgType::Req: {
		reqMap[_protocol] = _packetHandle;
		break;
	}
	case MasterAndGameServer::MsgType::Ans: {
		ansMap[_protocol] = _packetHandle;
		break;
	}
	case MasterAndGameServer::MsgType::Noti: {
		notiMap[_protocol] = _packetHandle;
		break;
	}
	case MasterAndGameServer::MsgType::Err: {
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
	MasterAndGameServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch(msgType) {
	case MasterAndGameServer::MsgType::Req : {
		return DiscriminateReq(_session, MasterAndGameServer::MsgType::Req, protocol, &br);
	}
	case MasterAndGameServer::MsgType::Ans : {
		return DiscriminateAns(_session, MasterAndGameServer::MsgType::Ans, protocol, &br);
	}
	case MasterAndGameServer::MsgType::Noti : {
		return DiscriminateNoti(_session, MasterAndGameServer::MsgType::Noti, protocol, &br);
	}
	case MasterAndGameServer::MsgType::Err : {
		return DiscriminateErr(_session, MasterAndGameServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}


IMPL_MAKE_MASTER_PACKET_FUNC(Req, MasterServerConnect);