#pragma once

/// <summary>
/// packet을 수령 후 실질적인 handler 호출까지 담당, 
/// 추가적으로 특정 proto packet 을 send buffer로 가공하는 것까지 담당
/// </summary>

class BufReader;

#define DECL_MAKE_SENDBUF_FROM_GAME_SERVER_PACKET(_msgType, _protocolName)														\
static SendBufferSptr MakeSendBufferFromPacket(UserAndGameServer::##_msgType##_protocolName& _packet)							\
{																																\
	return MakeProtoSendBuffer(UserAndGameServer::MsgType::##_msgType, UserAndGameServer::Protocol::##_protocolName, _packet);	\
}																																\


class GameServerPacketHandler
{
private:
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerReqMap;	//받은 req를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerAnsMap;  //받은 ans를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerNotiMap;  //받은 noti를 handle
	static map<UserAndGameServer::Protocol, PacketFunc*> userAndGameServerErrMap;  //받은 err를 handle
private:
	static bool HandleUserAndGameServerReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleUserAndGameServerAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleUserAndGameServerNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleUserAndGameServerErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
private:
	static void AbusingRecord(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _buf);
	static void RegistPacketFunc(UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, PacketFunc* _func);
public:
	static void Init();
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);

	
public: //server에 보낼 packet을 통해 sendBytes를 만드는 과정에 대한 영역, 모든 gameserver로 보내는 packet에 대하여 선언해야한다.
	template<typename MSG_TYPE, typename P, typename T>
	static SendBufferSptr MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet);
	DECL_MAKE_SENDBUF_FROM_GAME_SERVER_PACKET(Req, Chat);
	DECL_MAKE_SENDBUF_FROM_GAME_SERVER_PACKET(Req, Login);
};

template<typename MSG_TYPE, typename P, typename T>
SendBufferSptr GameServerPacketHandler::MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet) {

	uint16_t byteLen = _packet.ByteSizeLong();
	uint32_t headerVal = sizeof(MSG_TYPE) + sizeof(P) + byteLen;
	uint16_t packetSize = sizeof(PacketHeader) + headerVal;
	SendBufferSptr sendBuffer = SendBufferManager::Get().Open(packetSize);

	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	*header = headerVal;

	MSG_TYPE* msgType = reinterpret_cast<MSG_TYPE*>(&header[1]);
	*msgType = _msgType;

	P* _protocolPtr = reinterpret_cast<P*>(&msgType[1]);
	*_protocolPtr = _protocol;

	ASSERT_CRASH(_packet.SerializeToArray(&_protocolPtr[1], byteLen));
	sendBuffer->Close(packetSize);
	return sendBuffer;
}




