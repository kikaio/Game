#include "pch.h"
#include "ServerPacketHandler.h"

// handler 함수 지정용 define
#define REGIST_MASTER_PACKET_FUNC(_msgType, _protocol, _func)																\
{																															\
	RegistPacketFunc(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocol, _func);			\
}																															\


map<MasterAndGameServer::Protocol, PacketFunc*> MasterPacketHandler::reqMap;	//받은 req를 handle
map<MasterAndGameServer::Protocol, PacketFunc*> MasterPacketHandler::ansMap;  //받은 ans를 handle
map<MasterAndGameServer::Protocol, PacketFunc*> MasterPacketHandler::notiMap;  //받은 noti를 handle
map<MasterAndGameServer::Protocol, PacketFunc*> MasterPacketHandler::errMap;  //받은 err를 handle


bool MasterPacketHandler::HandleMasterAndGameServerReq(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = reqMap.find(_protocol);
	if(finder == reqMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return reqMap[_protocol](_session, _brPtr);
}

bool MasterPacketHandler::HandleMasterAndGameServerAns(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = ansMap.find(_protocol);
	if (finder == ansMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return ansMap[_protocol](_session, _brPtr);
}

bool MasterPacketHandler::HandleMasterAndGameServerNoti(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = notiMap.find(_protocol);
	if (finder == notiMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return notiMap[_protocol](_session, _brPtr);
}

bool MasterPacketHandler::HandleMasterAndGameServerErr(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr)
{
	auto finder = errMap.find(_protocol);
	if (finder == errMap.end()) {
		AbusingRecord(_session, _msgType, _protocol, _brPtr);
		return false;
	}
	return errMap[_protocol](_session, _brPtr);
}

void MasterPacketHandler::AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf)
{
	//todo : logging
	printf("session[%s] try abusing. check please - msg[%d], protocol[%d]\n"
		, _session->GetSId().c_str(), _msgType, _protocol
	);
	return ;
}

void MasterPacketHandler::Init()
{
	REGIST_MASTER_PACKET_FUNC(Ans, MasterServerConnect, [](SessionSptr _session, BufReader* _brPtr){
		MasterAndGameServer::AnsMasterServerConnect packet;
		packet.ParseFromArray(_brPtr->Buffer() + _brPtr->ReadSize(), _brPtr->FreeSize());
		_brPtr->Close();
		return MasterAndGameServerHandle::AnsMasterServerConnect(static_pointer_cast<MasterSession>(_session), packet);
	});
}

void MasterPacketHandler::RegistPacketFunc(MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, PacketFunc* _packetHandle)
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

bool MasterPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	int32_t msgType;
	MasterAndGameServer::Protocol protocol;
	br >> msgType;
	br >> protocol;

	switch(msgType) {
	case MasterAndGameServer::MsgType::Req : {
		return HandleMasterAndGameServerReq(_session, MasterAndGameServer::MsgType::Req, protocol, &br);
	}
	case MasterAndGameServer::MsgType::Ans : {
		return HandleMasterAndGameServerAns(_session, MasterAndGameServer::MsgType::Ans, protocol, &br);
	}
	case MasterAndGameServer::MsgType::Noti : {
		return HandleMasterAndGameServerNoti(_session, MasterAndGameServer::MsgType::Noti, protocol, &br);
	}
	case MasterAndGameServer::MsgType::Err : {
		return HandleMasterAndGameServerErr(_session, MasterAndGameServer::MsgType::Err, protocol, &br);
	}
	default: {
		AbusingRecord(_session, msgType, protocol, &br);
		return false;
	}
	}
	return true;
}


IMPL_MAKE_PACKET_MASTER_FUNC(MasterPacketHandler, Req, MasterServerConnect);