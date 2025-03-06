#include "pch.h"
#include "ProtoConverter.h"

void ProtoConverter::ToProto(const LoginResultData& _in, UserAndGameServer::LoginResultData& _out)
{
	_out.set_is_success(_in.isSuccess);
	return;
}

void ProtoConverter::ToProto(const UserProfile& _in, UserAndGameServer::UserProfile& _out)
{
	_out.set_profile_id(_in.profileId);
	_out.set_account_lv(_in.accountLv);
	_out.set_nick_name(_in.nickName);
	_out.set_greeting_ment(_in.greetingMent);
	_out.set_profile_hero_id(_in.profileHeroId);
	_out.set_profile_frame_id(_in.profileFrameId);
	_out.set_main_hero_id(_in.mainHeroId);
}

void ProtoConverter::ToProto(const ChatProfile& _in, UserAndGameServer::ChatProfile& _out)
{
	_out.set_profile_id(_in.profileId);
	_out.set_nick_name(_in.nickName);
	_out.set_profile_hero_id(_in.profileHeroId);
	_out.set_profile_frame_id(_in.profileFrameId);
	_out.set_main_hero_id(_in.mainHeroId);
}

void ProtoConverter::ToProto(const ChatData& _in, UserAndGameServer::ChatData& _out)
{
	_out.set_chat_type(ENUM_TO_INT(_in.chatType));
	ToProto(_in.chatProfile, *_out.mutable_chat_profile());
	_out.set_msg(_in.msg);
}

void ProtoConverter::ToPacket(const LoginResultData& _loginResultData, const UserProfile& _profile, UserAndGameServer::AnsLogin& _out)
{
	ToProto(_loginResultData, *_out.mutable_login_result_data());
	ToProto(_profile, *_out.mutable_user_profile());
}

void ProtoConverter::ToPacket(const ChatData& _chatData, UserAndGameServer::AnsChat& _out) {
	ToProto(_chatData, *_out.mutable_chat_data());
	return ;
}

void ProtoConverter::ToPacket(const PacketError& _packetError, UserAndGameServer::NotiErrInfo& _out)
{
	_out.set_err_no(_packetError.err_no);
	_out.set_err_desc(_packetError.err_desc);
}


void ProtoConverter::FromProto(const UserAndGameServer::LoginData& _in, LoginData& _out)
{
	_out.deviceKey = _in.device_key();
	auto _optional = ENUM_FROM_INT(LOGIN_PLATFORM, _in.login_platform());
	if(_optional.has_value()) {
		_out.loginPlatform = _optional.value();
	}
	else {
		// todo : error logging
	}
	return ;
}

void ProtoConverter::FromProto(const UserAndGameServer::ChatProfile& _in, ChatProfile& _out)
{
	_out.profileId = _in.profile_id();
	_out.nickName = _in.nick_name();
	_out.profileHeroId = _in.profile_hero_id();
	_out.profileFrameId = _in.profile_frame_id();
	_out.mainHeroId = _in.main_hero_id();
}

void ProtoConverter::FromProto(const UserAndGameServer::ChatData& _in, ChatData& _out) {
	auto _optional = ENUM_FROM_INT(CHAT_TYPE, _in.chat_type());
	if(_optional.has_value()) {
		_out.chatType = _optional.value();
	}
	else {
		//todo : error logging
	}
	FromProto(_in.chat_profile(), _out.chatProfile);
	_out.msg = _in.msg();
}


void ProtoConverter::FromPacket(const UserAndGameServer::ReqLogin& _in, LoginData& _loginData)
{
	FromProto(_in.login_data(), _loginData);
}

void ProtoConverter::FromPacket(const UserAndGameServer::ReqChat& _in, ChatData& _chatData) {
	FromProto(_in.chat_data(), _chatData);
}

void ProtoConverter::FromPacket(const UserAndGameServer::NotiErrInfo& _in, PacketError& _packetError)
{
	_packetError.err_no = _in.err_no();
	_packetError.err_desc = _in.err_desc();
}
