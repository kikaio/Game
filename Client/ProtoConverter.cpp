
#include "pch.h"
#include "ProtoConverter.h"

#pragma region to proto
///////////////////////////////////////////////////////////////////////////////////////////

void ProtoConverter::ToProto(const LoginData& _in, UserAndGameServer::LoginData& _out)
{
	_out.set_device_key(_in.deviceKey);
	_out.set_login_platform(ENUM_TO_INT(_in.loginPlatform));
}

void ProtoConverter::ToProto(const ChatProfile& _in, UserAndGameServer::ChatProfile _out)
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

void ProtoConverter::ToProto(const LoginData& _loginData, UserAndGameServer::ReqLogin& _outProto)
{
	ToProto(_loginData, *_outProto.mutable_login_data());
	return;
}

void ProtoConverter::ToProto(const ChatData& _chatData, UserAndGameServer::ReqChat& _outProto)
{
	ToProto(_chatData, *_outProto.mutable_chat_data());
	return;
}


///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion


#pragma region from proto
///////////////////////////////////////////////////////////////////////////////////////////

void ProtoConverter::FromProto(const UserAndGameServer::LoginResultData& _in, LoginResultData& _out)
{
	_out.isSuccess = _in.is_success();
}

void ProtoConverter::FromProto(const UserAndGameServer::ChatProfile& _in, ChatProfile& _out)
{
	_out.profileId = _in.profile_id();
	_out.nickName = _in.nick_name();
	_out.profileHeroId = _in.profile_hero_id();
	_out.profileFrameId = _in.profile_frame_id();
	_out.mainHeroId = _in.main_hero_id();
}

void ProtoConverter::FromProto(const UserAndGameServer::ChatData& _in, ChatData& _out)
{
	auto _optinal = ENUM_FROM_INT(CHAT_TYPE, _in.chat_type());
	if(_optinal.has_value()) {
		_out.chatType = _optinal.value();
	}
	else {
		//todo : error logging
	}
	FromProto(_in.chat_profile(), _out.chatProfile);
	_out.msg = _in.msg();
}

void ProtoConverter::FromProto(const UserAndGameServer::AnsChat& _in, ChatData& _out)
{
	FromProto(_in.chat_data(), _out);
}

///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

