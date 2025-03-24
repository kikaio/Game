
#include "pch.h"
#include "ProtoConverter.h"

#pragma region to proto
///////////////////////////////////////////////////////////////////////////////////////////

void ProtoConverter::ToProto(const LoginData& _in, UserAndGameServer::LoginData& _out)
{
	_out.set_s_id(_in.sId);
	_out.set_login_platform(ENUM_TO_INT(_in.loginPlatform));
	_out.set_login_token(_in.loginToken);
	_out.set_refresh_token(_in.refreshToken);
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

void ProtoConverter::ToProto(const DummyProfile& _in, UserAndGameServer::GameProfile& _out)
{
	_out.set_account_id(_in.AccountId());
	_out.set_greeting_ment(_in.GreetingMent());
	_out.set_main_hero_id(_in.MainHeroId());
	_out.set_main_frame_id(_in.MainFrameId());
}

void ProtoConverter::ToProto(const Inventory& _in, UserAndGameServer::Inventory& _out)
{
	const auto& items = _in.GetItems();
	for (const auto& _pair : items) {
		auto* _new_ele = _out.add_items();
		ToProto(_pair.second, *_new_ele);
	}
	const auto& costumes= _in.GetCostumes();
	for (const auto& _pair : costumes) {
		auto* _new_ele = _out.add_costumes();
		ToProto(_pair.second, *_new_ele);
	}
	const auto& characters = _in.GetCharacters();
	for (const auto& _pair : characters) {
		auto* _new_ele = _out.add_characters();
		ToProto(_pair.second, *_new_ele);
	}
}

void ProtoConverter::ToProto(const ItemData& _in, UserAndGameServer::ItemData& _out) {
	_out.set_basis_id(_in.basisId);
	_out.set_cnt(_in.cnt);
	_out.set_cnt_prev(_in.cntPrev);
}

void ProtoConverter::ToProto(const CostumeData& _in, UserAndGameServer::CostumeData& _out) {
	_out.set_basis_id(_in.basisId);
}

void ProtoConverter::ToProto(const CharacterData& _in, UserAndGameServer::CharacterData& _out) {
	_out.set_basis_id(_in.basisId);
}

///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion


#pragma region to packet
///////////////////////////////////////////////////////////////////////////////////////////

void ProtoConverter::ToPacket(const LoginData& _loginData, UserAndGameServer::ReqLogin& _outProto)
{
	ToProto(_loginData, *_outProto.mutable_login_data());
	return;
}

void ProtoConverter::ToPacket(const ChatData& _chatData, UserAndGameServer::ReqChat& _outProto)
{
	ToProto(_chatData, *_outProto.mutable_chat_data());
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion to packet

#pragma region from proto
///////////////////////////////////////////////////////////////////////////////////////////

void ProtoConverter::FromProto(const UserAndGameServer::LoginResultData& _in, LoginResultData& _out)
{
	_out.isSuccess = _in.is_success();
	_out.loginToken = _in.login_token();
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

void ProtoConverter::FromProto(const UserAndGameServer::GameProfile& _in, DummyProfile& _out) {
	_out.SetAccountId(_in.account_id());
	_out.SetGreetingMent(_in.greeting_ment());
	_out.SetMainHeroId(_in.main_hero_id());
	_out.SetMainFrameId(_in.main_frame_id());
}

void ProtoConverter::FromProto(const UserAndGameServer::Inventory& _in, Inventory& _out)
{
	for (const auto& _ele : _in.items()) {
		ItemData _item;
		FromProto(_ele, _item);
		_out.items.emplace(_item.basisId, _item);
	}
	for (const auto& _ele : _in.costumes()) {
		CostumeData _costume;
		FromProto(_ele, _costume);
		_out.costumes.emplace(_costume.basisId, _costume);
	}
	for (const auto& _ele : _in.characters()) {
		CharacterData _character;
		FromProto(_ele, _character);
		_out.characters.emplace(_character.basisId, _character);
	}
}


void ProtoConverter::FromProto(const UserAndGameServer::ItemData& _in, ItemData& _out) {
	_out.basisId = _in.basis_id();
	_out.cnt = _in.cnt();
	_out.cntPrev = _in.cnt_prev();
}

void ProtoConverter::FromProto(const UserAndGameServer::CostumeData& _in, CostumeData& _out) {
	_out.basisId = _in.basis_id();
}

void ProtoConverter::FromProto(const UserAndGameServer::CharacterData& _in, CharacterData& _out) {
	_out.basisId = _in.basis_id();
}

///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region from packet
///////////////////////////////////////////////////////////////////////////////////////////

void ProtoConverter::FromPacket(IN const UserAndGameServer::AnsLogin& _packet
	, OUT LoginResultData& _loginRet
	, OUT DummyProfile& _profile
	, OUT Inventory& _inven
) {
	FromProto(IN _packet.login_result_data(), OUT _loginRet);
	FromProto(IN _packet.user_profile(), OUT _profile);
	FromProto(IN _packet.user_inventory(), OUT _inven);
	return ;
}

void ProtoConverter::FromPacket(IN const UserAndGameServer::AnsGameConn& _packet
	, OUT string& _encryptKey
	, OUT string& _chatHost
	, OUT int16_t& _chatPort
	)
{
	_encryptKey = _packet.encrypt_key();
	_chatHost = _packet.chat_host();
	_chatPort = _packet.chat_port();
}


///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion
