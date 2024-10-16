#pragma once


#define DECL_MAKE_PACKET_FUNC(_className, _msgType, _protocolName)														\
	static SendBufferSptr MakePacket##_msgType##_protocolName(UserAndGameServer::##_msgType##_protocolName& _packet)	\


#define IMPL_MAKE_PACKET_FUNC(_className, _msgType, _protocolName)																\
SendBufferSptr _className::MakePacket##_msgType##_protocolName(UserAndGameServer::##_msgType##_protocolName& _packet)			\
{																																\
	return MakeProtoPacket(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocolName, _packet);		\
}																																\
