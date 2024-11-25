#pragma once


#define DECL_MAKE_SENDBUF_FROM_GAME_PACKET(_msgType, _protocolName) 														\
	static SendBufferSptr MakePacket##_msgType##_protocolName(MasterAndGameServer::##_msgType##_protocolName& _packet)		\


#define IMPL_MAKE_PACKET_GAME_FUNC(_className, _msgType, _protocolName)																	\
SendBufferSptr _className::MakePacket##_msgType##_protocolName(MasterAndGameServer::##_msgType##_protocolName& _packet)					\
{																																		\
	return MakeProtoSendBuffer(MasterAndGameServer::MsgType::##_msgType, MasterAndGameServer::Protocol::##_protocolName, _packet);		\
}																																		\

#define DECL_SERVER_SESSION_SEND_GAME_PACKET(_msgType, _protocolName)								\
bool SendPacket(MasterAndGameServer::##_msgType##_protocolName& _packet)							\

#define IMPL_SERVER_SESSION_SEND_GAME_PACKET(_msgType, _protocolName)								\
bool UserSession::SendPacket(MasterAndGameServer::##_msgType##_protocolName& _packet)				\
{																									\
	SendBufferSptr sendBuf = ServerPacketHandler::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																		\
}																									\
