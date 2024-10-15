#include "pch.h"
#include "ClientPacketHandler.h"

map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerErrMap;  //받은 err를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerNotiMap;  //받은 noti를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerReqMap;	//받은 req를 handle
map<UserAndGameServer::Protocol, PacketFunc*> ClientPacketHandler::userAndGameServerAnsMap;  //받은 ans를 handle


#define IMPL_CONVERT_USER_AND_GAMESERVER_PACKET(_msgType, _protocolName)																\
bool ClientPacketHandler::ConverUserAndGameServerPacket##_msgType##_protocolName(SessionSptr _session, BufReader* _brPtr)				\
{																																		\
	UserAndGameServer::##_msgType##_protocolName protocolPacket;																		\
	if (protocolPacket.ParseFromArray(_brPtr->Buffer(), _brPtr->FreeSize()) == false) {													\
		AbusingRecord(_session, UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocolName, _brPtr);			\
		return false;																													\
	}																																	\
	else {																																\
		return UserAndGameServerHandle::##_msgType##_protocolName(_session, protocolPacket);											\
	}																																	\
}																																		\



#define PROTOCOL_HANDLE(_session, _msgType, _protocol, _brPtr, _handleMap)								\
{																										\
	auto _fidner = _handleMap.find(_protocol);															\
	if(_fidner == _handleMap.end()) {																	\
		AbusingRecord(_session, _msgType, _protocol, _brPtr);											\
		return false;																					\
	}																									\
	else {																								\
		_handleMap[_protocol](_session, _brPtr);														\
		return true;																					\
	}																									\
}																										\


#define USER_AND_GAMESERVER_HANDLE_REGIST(_msgType, _protocolName, _map)				\
{																						\
	auto _protocol = UserAndGameServer::Protocol::_protocolName;						\
	_map[_protocol] = ConverUserAndGameServerPacket##_msgType##_protocolName;			\
}																						\



IMPL_CONVERT_USER_AND_GAMESERVER_PACKET(Req, TestMsg);




void ClientPacketHandler::AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf)
{
}

void ClientPacketHandler::Init()
{
	//Register All Handler.
	USER_AND_GAMESERVER_HANDLE_REGIST(Req, TestMsg, userAndGameServerReqMap);
}

bool ClientPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	UserAndGameServer::MsgType msgType;
	br >> msgType;
	
	UserAndGameServer::Protocol protocol = UserAndGameServer::Protocol::INVALID_PROTOCOL;
	br >> protocol;

	switch(msgType) {
	case UserAndGameServer::MsgType::Err : {
		PROTOCOL_HANDLE(_session, msgType, protocol, &br, userAndGameServerErrMap);
		break;
	}
	case UserAndGameServer::MsgType::Noti : {
		PROTOCOL_HANDLE(_session, msgType, protocol, &br, userAndGameServerNotiMap);
		break;
	}
	case UserAndGameServer::MsgType::Req : {
		PROTOCOL_HANDLE(_session, msgType, protocol, &br, userAndGameServerReqMap);
		break;
	}
	case UserAndGameServer::MsgType::Ans : {
		PROTOCOL_HANDLE(_session, msgType, protocol, &br, userAndGameServerAnsMap);
		break;
	}
	default: {
		break;
	}
	}
	return false;
}
