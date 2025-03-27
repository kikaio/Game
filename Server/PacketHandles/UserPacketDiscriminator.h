#pragma once

//server와 client간의 주고받는 packet에 대한 handler 관련 코드들.

#define USER_AND_GAME_SERVER_FUNC_MAP map<UserAndGameServer::Protocol, PacketFunc*>

#define DECL_MAKE_USER_SENDBUF(_msgType, _protocolName) 																		\
	static SendBufferSptr MakePacket##_msgType##_protocolName(const UserAndGameServer::##_msgType##_protocolName& _packet)		\

class UserPacketDiscriminator
{
private:
	static USER_AND_GAME_SERVER_FUNC_MAP reqMap;	//받은 req를 handle
	static USER_AND_GAME_SERVER_FUNC_MAP ansMap;  //받은 ans를 handle
	static USER_AND_GAME_SERVER_FUNC_MAP notiMap;  //받은 noti를 handle
	static USER_AND_GAME_SERVER_FUNC_MAP errMap;  //받은 err를 handle
private:
	static bool DiscriminatorReq(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool DiscriminatorAns(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool DiscriminatorNoti(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
	static bool DiscriminatorErr(SessionSptr _session, UserAndGameServer::MsgType _msgType, UserAndGameServer::Protocol _protocol, BufReader* _brPtr);
private:
	static void AbusingRecord(SessionSptr _session, int32_t _msgType, int32_t _protocol, BufReader* _buf);
public:
	static void Init();
	static void RegistPacketFunc(UserAndGameServer::MsgType _msg_type, UserAndGameServer::Protocol _protocol, PacketFunc* _packetHandle);
public:
	static bool HandlePayload(SessionSptr _session, BYTE* _buf, uint32_t _size);
public:
	template<typename MSG_TYPE, typename P, typename T> 
	static SendBufferSptr MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet);
public: //해당 packet에 대해서 전송해주는 함수들.
	DECL_MAKE_USER_SENDBUF(Noti, ErrInfo);
	DECL_MAKE_USER_SENDBUF(Ans, Login);
	DECL_MAKE_USER_SENDBUF(Ans, GameConn);
};




template<typename MSG_TYPE, typename P, typename T>
SendBufferSptr UserPacketDiscriminator::MakeProtoSendBuffer(MSG_TYPE _msgType, P _protocol, T& _packet) {

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

