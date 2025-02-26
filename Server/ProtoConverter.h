#pragma once


class ProtoConverter {
// to proto
public:
	static void toProto(const UserAndGameServer::LoginData& _in, LoginData& _out);


//from proto
public:
	static void fromProto(const LoginResultData& _in, UserAndGameServer::LoginResultData& _out);
};