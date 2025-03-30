#include "pch.h"
#include "ProtoConverter.h"

#pragma region to proto

void ProtoConverter::ToProto(IN const ChatData& _in, OUT UserAndChatServer::ChatData& _out) {
	auto chatProfile = _in.GetChatProfile();
	ToProto(*chatProfile, *_out.mutable_chat_profile());
	_out.set_chat_type(ENUM_TO_INT(_in.GetChatType()));
	_out.set_msg(_in.GetMsg());
}

void ProtoConverter::ToProto(IN const ChatProfile& _in, OUT UserAndChatServer::ChatProfile& _out) {
	_out.set_profile_id(_in.GetProfileId());
	_out.set_nick_name(_in.GetNickName());
	_out.set_profile_hero_id(_in.GetMainHeroId());
	_out.set_profile_frame_id(_in.GetMainFrameId());
}

#pragma endregion to proto

#pragma region from proto

void ProtoConverter::FromProto(IN const UserAndChatServer::ChatData& _in, OUT ChatData& _out) {
	const auto& protoProfile = _in.chat_profile();
	int64_t profileId = protoProfile.profile_id();
	auto chatProfile = ChatProfileMng::Get().GetProfile(profileId);
	if(chatProfile == nullptr) {
		chatProfile = ChatProfileMng::Get().CreateProfile(
			profileId
			, protoProfile.nick_name()
			, protoProfile.profile_hero_id()
			, protoProfile.profile_frame_id()
		);
	}
	else {
		FromProto(IN protoProfile, OUT * chatProfile);
	}
	
	if(_out.GetChatProfile() == nullptr) {
		_out.SetChatProfile(chatProfile);
	}
	auto enumOpt = ENUM_FROM_INT(CHAT_TYPE, _in.chat_type());
	if(enumOpt.has_value()) {
		_out.SetChatType(enumOpt.value());
	}
	_out.SetMsg(_in.msg());
}

void ProtoConverter::FromProto(IN const UserAndChatServer::ChatProfile& _in, OUT ChatProfile& _out) {
	_out.SetNickName(_in.nick_name());
	_out.SetMainHeroId(_in.profile_hero_id());
	_out.SetMainFrameId(_in.profile_frame_id());
}

#pragma endregion from proto

#pragma region to packet
void ProtoConverter::ToPacket(IN const ChatData& _chatData, OUT UserAndChatServer::NotiChat& _packet) {
	_packet.chat_data()
}

#pragma region to packet

#pragma region from packet
#pragma region from packet
