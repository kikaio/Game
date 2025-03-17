#pragma once


class ProtoConverter {
	// to proto
public:
	static void ToProto(const LoginResultData& _in, UserAndGameServer::LoginResultData& _out);
	static void ToProto(const GameProfile& _in, UserAndGameServer::GameProfile& _out);

	static void ToProto(const ChatProfile& _in, UserAndGameServer::ChatProfile& _out);
	static void ToProto(const ChatData& _in, UserAndGameServer::ChatData& _out);
	
	static void ToProto(const ItemData& _in, UserAndGameServer::ItemData& _out);
	static void ToProto(const CostumeData& _in, UserAndGameServer::CostumeData& _out);
	static void ToProto(const CharacterData& _in, UserAndGameServer::CharacterData& _out);
	static void ToProto(const Inventory& _in, UserAndGameServer::Inventory& _out);

	//from proto
public:
	static void FromProto(const UserAndGameServer::LoginData& _in, LoginData& _out);
	static void FromProto(const UserAndGameServer::ChatProfile& _profile, ChatProfile& _out);
	static void FromProto(const UserAndGameServer::ChatData& _in, ChatData& _out);
	
	static void FromProto(const UserAndGameServer::ItemData& _in, ItemData& _out);
	static void FromProto(const UserAndGameServer::CostumeData& _in, CostumeData& _out);
	static void FromProto(const UserAndGameServer::CharacterData& _in, CharacterData& _out);
	
	// to proto packet
public:
	static void ToPacket(
		const LoginResultData& _loginResultData
		, const GameProfile& _profile
		, const Inventory& _inventory
		, UserAndGameServer::AnsLogin& _out
	);
	static void ToPacket(const ChatData& _chatData, UserAndGameServer::AnsChat& _out);
	static void ToPacket(const PacketError& _packetError, UserAndGameServer::NotiErrInfo& _out);

	// from proto packet
public:
	static void FromPacket(const UserAndGameServer::ReqLogin& _in, LoginData& _loginData);
	static void FromPacket(const UserAndGameServer::ReqChat& _in, ChatData& _chatData);
	static void FromPacket(const UserAndGameServer::NotiErrInfo& _in, PacketError& _packetError);
};