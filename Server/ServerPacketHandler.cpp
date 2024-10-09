#include "pch.h"
#include "ServerPacketHandler.h"

map<Protocol, PacketFunc*> ServerPacketHandler::packetHandlerMap = {};

void ServerPacketHandler::Init()
{
	RegistPacketFunc(PROTOCOL::ANS_TEST, [](SessionSptr _session, BufReader* _br){
		printf("recv answer from client ^오^\n");
		return true;
	});
}

void ServerPacketHandler::RegistPacketFunc(PROTOCOL _protocol, PacketFunc* _packetHandle)
{
	if(packetHandlerMap.find(_protocol) != packetHandlerMap.end()) {
		ASSERT_CRASH("packet handle func duplicated!!\n");
		return ;
	}
	packetHandlerMap.insert(make_pair((Protocol)_protocol, _packetHandle));
}

bool ServerPacketHandler::HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size)
{
	BufReader br(_buf, _size);
	Protocol protocol;
	br >> protocol;
	if(packetHandlerMap.find(protocol) == packetHandlerMap.end()) {
		ASSERT_CRASH("invalid protocol!!!\n");
		return false;
	}

	packetHandlerMap[protocol](_session, &br);
	return true;
}

SendBufferSptr ServerPacketHandler::MakePacket_REQ_TEST(string& _msg)
{
	SendBufferSptr sendBuffer = SendBufferManager::Get().Open(BUF_512);
	BufWriter br(sendBuffer->Buffer(), sendBuffer->AllocSize());
	br.Write(_msg);
	sendBuffer->Close(br.WriteSize());
	return sendBuffer;
}
