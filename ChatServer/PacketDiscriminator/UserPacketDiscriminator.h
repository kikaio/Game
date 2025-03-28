#pragma once

#define USER_PACKET_PROTOCOL_FUNC_MAP map<UserAndChatServer::Protocol, PacketFunc*>

#define DECL_MAKE_SENDBUF_USER_CLIENT_PACKET(_msgType, _protocolType)														\
static SendBufferSptr MakePacket##_msgType##_protocolType(const UserAndChatServer::##_msgType##_protocolType& _packet)		\


class UserPacketDiscriminator {
private:
	static USER_PACKET_PROTOCOL_FUNC_MAP reqMap;
	static USER_PACKET_PROTOCOL_FUNC_MAP ansMap;
	static USER_PACKET_PROTOCOL_FUNC_MAP notiMap;
	static USER_PACKET_PROTOCOL_FUNC_MAP errMap;
private:
	static bool DiscriminateReq(SessionSptr _session
		, UserAndChatServer::MsgType _msgType
		, UserAndChatServer::Protocol _protocol, BufReader* _brPtr
	);
	static bool DiscriminateAns(SessionSptr _session
		, UserAndChatServer::MsgType _msgType
		, UserAndChatServer::Protocol _protocol, BufReader* _brPtr
	);
	static bool DiscriminateNoti(SessionSptr _session
		, UserAndChatServer::MsgType _msgType
		, UserAndChatServer::Protocol _protocol, BufReader* _brPtr
	);
	static bool DiscriminateErr(SessionSptr _session
		, UserAndChatServer::MsgType _msgType
		, UserAndChatServer::Protocol _protocol, BufReader* _brPtr
	);
private:
	static void AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf);
public:
	static void Init();
	static void RegistPacketFunc(UserAndChatServer::MsgType _msg_type
		, UserAndChatServer::Protocol _protocol
		, PacketFunc* _packetHandle
	);
public:
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
public:
	template<typename MSG_TYPE, typename P, typename T>
	static SendBufferSptr MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet);
	DECL_MAKE_SENDBUF_USER_CLIENT_PACKET(Noti, Chat);

};


template<typename MSG_TYPE, typename P, typename T>
SendBufferSptr UserPacketDiscriminator::MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet) {

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

