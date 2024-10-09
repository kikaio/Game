#pragma once

class ClientPacketHandler
{
private:
	static map<uint8_t, PacketFunc*> packetHandleMap;
public:
	static void Init();
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
	static bool RegistPacketFunc(PROTOCOL _protocol, PacketFunc _packetHandle);
};