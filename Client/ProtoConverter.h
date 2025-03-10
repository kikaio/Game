#pragma once


class ProtoConverter {

	// ToProto : 구조체->proto 구조체로 변환 담당
public:
	static void ToProto(const LoginData& _in, UserAndGameServer::LoginData& _out);
	static void ToProto(const ChatProfile& _in, UserAndGameServer::ChatProfile _out);
	static void ToProto(const ChatData& _in, UserAndGameServer::ChatData& _out);

	//proto packet 까지 생성하는 함수들.
	static void ToProto(const LoginData& _loginData, UserAndGameServer::ReqLogin& _outProto);
	static void ToProto(const ChatData& _chatData, UserAndGameServer::ReqChat& _outProto);


	// FromProto : proto 구조체->구조체로 변환 담당
public:
	static void FromProto(const UserAndGameServer::LoginResultData& _in, LoginResultData& _out);
	static void FromProto(const UserAndGameServer::ChatProfile& _in, ChatProfile& _out);
	static void FromProto(const UserAndGameServer::ChatData& _in, ChatData& _out);
	static void FromProto(const UserAndGameServer::AnsChat& _in, ChatData& _out);
	// MakeProto : 구조체 등의 인자를 통한 message packet 값 설정.
};