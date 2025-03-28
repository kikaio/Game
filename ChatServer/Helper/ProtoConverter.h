#pragma once

class ProtoConverter {

#pragma region to proto
public:
	static void ToProto(IN const ChatData& _in, OUT UserAndChatServer::ChatData& _out);
	static void ToProto(IN const ChatProfile& _in, OUT UserAndChatServer::ChatProfile& _out);
#pragma endregion to proto

#pragma region from proto
public:
	static void FromProto(IN const UserAndChatServer::ChatData& _in, OUT ChatData& _out);
	static void FromProto(IN const UserAndChatServer::ChatProfile& _in, OUT ChatProfile& _out);
#pragma endregion from proto

};