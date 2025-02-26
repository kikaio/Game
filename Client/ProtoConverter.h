#pragma once


class ProtoConverter {
public:
	static void toProto(const LoginData& _in, UserAndGameServer::LoginData& _out);
public:
	static void fromProto(const UserAndGameServer::LoginResultData& _in, LoginResultData& _out);
};