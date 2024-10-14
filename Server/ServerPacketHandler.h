#pragma once
class ServerPacketHandler
{
private:
	static map<Protocol, PacketFunc*> packetHandlerMap;
public:
	void Init();
public:
	void RegistPacketFunc(UserAndGameServer::MsgType _msg_type, PacketFunc* _packetHandle);
	bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
public:
	SendBufferSptr MakePacket_REQ_TEST(string& _msg);

	static SendBufferSptr MakeReqTestMsg(string& _msg);

	template<typename MSG_TYPE, typename T> 
	static SendBufferSptr MakeProtoPacket(MSG_TYPE _msgType, T& _packet);
};

template<typename MSG_TYPE, typename T>
SendBufferSptr ServerPacketHandler::MakeProtoPacket(MSG_TYPE _msgType, T& _packet) {

	uint16_t byteLen = _packet.ByteSizeLong();
	uint16_t packetSize = sizeof(PacketHeader) + sizeof(MSG_TYPE) + byteLen;
	SendBufferSptr sendBuffer = SendBufferManager::Get().Open(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	*header = byteLen + sizeof(MSG_TYPE);
	MSG_TYPE* msgType = reinterpret_cast<MSG_TYPE>(&header[1]);
	*msgType = _msgType;

	ASSERT_CRASH(testMsg.SerializeToArray(&msgType[1], byteLen));
	sendBuffer->Close(packetSize);
	return sendBuffer;
}

