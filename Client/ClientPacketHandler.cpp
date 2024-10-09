#include "pch.h"
#include "ClientPacketHandler.h"

map<uint8_t, PacketFunc*> ClientPacketHandler::packetHandleMap = {};

void ClientPacketHandler::Init()
{
	RegistPacketFunc(PROTOCOL::TEST, [](SessionSptr _session, BufReader& _br){
		string testMsg = "";
		_br.Read(testMsg);
		printf("called TEST Packet Handle, and msg : %s\n", testMsg.c_str());
		return true;
	});
}

bool ClientPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	Protocol protocol = 0;
	br>>protocol;
	//protocol만큼 readpos를 전진시켰기때문에 간단하게 Bufreader를 그냥 넘겨준다.
	if(packetHandleMap.find(protocol) == packetHandleMap.end()) {
		ASSERT_CRASH("invalid protocol.");
		return false;
	}
	return packetHandleMap[protocol](_session, br);
}

bool ClientPacketHandler::RegistPacketFunc(PROTOCOL _protocol, PacketFunc _packetHandle)
{
	if(packetHandleMap.find(_protocol) != packetHandleMap.end()) {
		ASSERT_CRASH("protocol no duplicated. check please!\n");
		return false;
	}
	auto funcPair = make_pair((uint8_t)_protocol, _packetHandle);
	packetHandleMap.insert(funcPair);
	return true;
}
