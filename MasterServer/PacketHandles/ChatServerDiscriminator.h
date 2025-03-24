#pragma once

#define CHAT_PACKET_FUNC_MAP std::map<MasterAndChatServer::Protocol, PacketFunc*>

#define DECL_CHAT_PACKET_SEND_BUF(_msgType, _protocolType)																	\
static SendBufferSptr MakePacket##_msgType##_protocolType(const MasterAndChatServer::##_msgType##_protocolType& _packet)	\

class ChatServerDiscriminator {
private:
	static CHAT_PACKET_FUNC_MAP reqMap;	//받은 req를 handle
	static CHAT_PACKET_FUNC_MAP ansMap;  //받은 ans를 handle
	static CHAT_PACKET_FUNC_MAP notiMap;  //받은 noti를 handle
	static CHAT_PACKET_FUNC_MAP errMap;  //받은 err를 handle
private:
	static bool DiscriminateReq(SessionSptr _session, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol, BufReader* _brPtr);
	static bool DiscriminateAns(SessionSptr _session, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol, BufReader* _brPtr);
	static bool DiscriminateNoti(SessionSptr _session, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol, BufReader* _brPtr);
	static bool DiscriminateErr(SessionSptr _session, MasterAndChatServer::MsgType _msgType, MasterAndChatServer::Protocol _protocol, BufReader* _brPtr);
private:
	static void AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf);
public:
	static void Init();
	static void RegistPacketFunc(MasterAndChatServer::MsgType _msg_type, MasterAndChatServer::Protocol _protocol, PacketFunc* _packetHandle);
public:
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
public:
	template<typename MSG_TYPE, typename P, typename T>
	static SendBufferSptr MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, const T& _packet);
public: //해당 packet에 대해서 전송해주는 함수들.
	DECL_CHAT_PACKET_SEND_BUF(Ans, ChatConnectMaster);
};

template<typename MSG_TYPE, typename P, typename T>
inline SendBufferSptr ChatServerDiscriminator::MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, const T& _packet) {

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

