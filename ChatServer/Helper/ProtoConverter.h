#pragma once

class ProtoConverter {

#pragma region to proto
public:
	static void ToProto(IN const ChatData& _in, OUT UserAndChatServer::ChatData& _out);
	static void ToProto(IN const ChatProfile& _in, OUT UserAndChatServer::ChatProfile& _out);
#pragma endregion to proto

#pragma region to Packet
public:
	static void ToPacket(IN const ChatData& _chatData, OUT UserAndChatServer::NotiChat& _packet);
	static void ToPacket(
		IN ChatProfileSptr _profile
		, const int32_t& _roomNo
		, vector<ChatProfileSptr>& _others
		, OUT UserAndChatServer::AnsChatConn& _packet
	);
	static void ToPacket(
		IN ChatProfileSptr _profile
		, OUT UserAndChatServer::NotiEnterChatRoom& _packet
	);
	static void ToPacket(
		IN int64_t _accountId
		, OUT UserAndChatServer::NotiLeaveChatRoom& _packet
	);
#pragma endregion to Packet

#pragma region from proto
public:
	static void FromProto(IN const UserAndChatServer::ChatData& _in, OUT ChatData& _out);
	static void FromProto(IN const UserAndChatServer::ChatProfile& _in, OUT ChatProfile& _out);
#pragma endregion from proto

#pragma region from Packet
public:
	static void FromPacket(const UserAndChatServer::ReqChatConn& _packet, OUT int64_t& _accountId);
	static void FromPacket(const UserAndChatServer::ReqChat& _packet, OUT ChatData& _chatData);
	static void FromPacket(const UserAndChatServer::ReqEnterChatRoom& _packet, OUT int32_t& _chatRoomNo);
#pragma endregion from Packet
};