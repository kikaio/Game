#pragma once


#define DECL_MAKE_SENDBUF_FROM_PACKET(_className, _msgType, _protocolName) 														\
	static SendBufferSptr MakePacket##_msgType##_protocolName(UserAndGameServer::##_msgType##_protocolName& _packet)			\


#define IMPL_MAKE_PACKET_FUNC(_className, _msgType, _protocolName)																\
SendBufferSptr _className::MakePacket##_msgType##_protocolName(UserAndGameServer::##_msgType##_protocolName& _packet)			\
{																																\
	return MakeProtoSendBuffer(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocolName, _packet);	\
}																																\

#define DECL_USER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool SendPacket(UserAndGameServer::##_msgType##_protocolName& _packet)								\

#define IMPL_USER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool UserSession::SendPacket(UserAndGameServer::##_msgType##_protocolName& _packet)					\
{																									\
	SendBufferSptr sendBuf = ServerPacketHandler::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																		\
}																									\


#define DECL_MAKE_SENDBUF_FROM_MASTER_PACKET(_msgType, _protocolName) 														\
	static SendBufferSptr MakePacket##_msgType##_protocolName(MasterAndGameServer::##_msgType##_protocolName& _packet)		\


#define IMPL_MAKE_PACKET_MASTER_FUNC(_className, _msgType, _protocolName)																\
SendBufferSptr _className::MakePacket##_msgType##_protocolName(MasterAndGameServer::##_msgType##_protocolName& _packet)					\
{																																		\
	return MakeProtoSendBuffer(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocolName, _packet);		\
}																																		\

#define DECL_MASTER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool SendPacket(MasterAndGameServer::##_msgType##_protocolName& _packet)								\

#define IMPL_MASTER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool MasterSession::SendPacket(MasterAndGameServer::##_msgType##_protocolName& _packet)					\
{																									\
	SendBufferSptr sendBuf = MasterPacketHandler::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																		\
}																									\
