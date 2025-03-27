#pragma once


#define DECL_MAKE_SENDBUF_FROM_PACKET(_className, _msgType, _protocolName) 														\
	static SendBufferSptr MakePacket##_msgType##_protocolName(const UserAndGameServer::##_msgType##_protocolName& _packet)		\


#define IMPL_MAKE_PACKET_FUNC(_className, _msgType, _protocolName)																\
SendBufferSptr _className::MakePacket##_msgType##_protocolName(const UserAndGameServer::##_msgType##_protocolName& _packet)		\
{																																\
	return MakeProtoSendBuffer(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocolName, _packet);	\
}																																\





#define DECL_MASTER_SESSION_SEND_PACKET(_msgType, _protocolName)									\
bool SendPacket(const MasterAndGameServer::##_msgType##_protocolName& _packet)						\


