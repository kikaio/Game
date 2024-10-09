#pragma once
class ServerPacketHandler
{
private:
	static map<Protocol, PacketFunc*> packetHandlerMap;
public:
	void Init();
public:
	void RegistPacketFunc(PROTOCOL _protocol, PacketFunc* _packetHandle);
	bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
public:
	SendBufferSptr MakePacket_REQ_TEST(string& _msg);
};

