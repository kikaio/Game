#pragma once


class ProtoConverter {
	// to proto
public:
	static void ToProto(const LoginResultData& _in, UserAndGameServer::LoginResultData& _out);
	static void ToProto(const UserProfile& _in, UserAndGameServer::UserProfile& _out);

	static void ToProto(const ChatProfile& _in, UserAndGameServer::ChatProfile& _out);
	static void ToProto(const ChatData& _in, UserAndGameServer::ChatData& _out);

	//from proto
public:
	static void FromProto(const UserAndGameServer::LoginData& _in, LoginData& _out);
	static void FromProto(const UserAndGameServer::ChatProfile& _profile, ChatProfile& _out);
	static void FromProto(const UserAndGameServer::ChatData& _in, ChatData& _out);

	// to proto packet
public:
	static void ToPacket(
		const LoginResultData& _loginResultData
		, const UserProfile& _profile
		, UserAndGameServer::AnsLogin& _out
	);
	static void ToPacket(const ChatData& _chatData, UserAndGameServer::AnsChat& _out);


	// from proto packet
public:
	static void FromPacket(const UserAndGameServer::ReqLogin& _in, LoginData& _loginData);
	static void FromPacket(const UserAndGameServer::ReqChat& _in, ChatData& _chatData);
};