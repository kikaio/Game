#pragma once

class MasterPacketHandler
{
private:
	static map<MasterAndGameServer::Protocol, PacketFunc*> reqMap;	//받은 req를 handle
	static map<MasterAndGameServer::Protocol, PacketFunc*> ansMap;  //받은 ans를 handle
	static map<MasterAndGameServer::Protocol, PacketFunc*> notiMap;  //받은 noti를 handle
	static map<MasterAndGameServer::Protocol, PacketFunc*> errMap;  //받은 err를 handle
private:
	static bool HandleMasterAndGameServerReq(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleMasterAndGameServerAns(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleMasterAndGameServerNoti(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool HandleMasterAndGameServerErr(SessionSptr _session, MasterAndGameServer::MsgType _msgType, MasterAndGameServer::Protocol _protocol, BufReader* _brPtr);
private:
	static void AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf);
public:
	static void Init();
	static void RegistPacketFunc(MasterAndGameServer::MsgType _msg_type, MasterAndGameServer::Protocol _protocol, PacketFunc* _packetHandle);
public:
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
public:
	template<typename MSG_TYPE, typename P, typename T> 
	static SendBufferSptr MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet);
public:
	DECL_MAKE_SENDBUF_FROM_MASTER_PACKET(Ans, MasterServerConnect);
};




template<typename MSG_TYPE, typename P, typename T>
SendBufferSptr MasterPacketHandler::MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet) {

	uint16_t byteLen = _packet.ByteSizeLong();
	uint32_t headerVal = sizeof(MSG_TYPE) + sizeof(P) + byteLen;
	uint16_t packetSize = sizeof(PacketHeader) + headerVal ;
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

