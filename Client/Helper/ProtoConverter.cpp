
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

void ProtoConverter::ToProto(IN const ChatProfile& _in, OUT UserAndChatServer::ChatProfile& _out) {
	_out.set_profile_id(_in.GetAccountId());
	_out.set_nick_name(_in.GetNickName());
	_out.set_profile_hero_id(_in.GetProfileHeroId());
	_out.set_profile_frame_id(_in.GetProfileFrameId());
}

void ProtoConverter::ToProto(IN const ChatData& _in, OUT UserAndChatServer::ChatData& _out) {
	auto chatProfile = _in.GetChatProfile();
	if(chatProfile != nullptr) {
		ToProto(*chatProfile, *_out.mutable_chat_profile());
	}
	_out.set_chat_type(ENUM_TO_INT(_in.GetChatType()));
	_out.set_msg(_in.GetMsg());
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


void ProtoConverter::ToPacket(const int64_t _accountId, UserAndChatServer::ReqChatConn& _out) {
	_out.set_account_id(_accountId);
	return;
}

void ProtoConverter::ToPacket(IN const ChatData& _chatData, OUT UserAndChatServer::ReqChat& _packet) {
	ToProto(_chatData, *_packet.mutable_chat_data());
	return ;
}

void ProtoConverter::ToPacket(IN int32_t _roomNo, OUT UserAndChatServer::ReqEnterChatRoom& _packet) {
	_packet.set_chat_room_no(_roomNo);
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
	return ;
}

void ProtoConverter::FromProto(const UserAndGameServer::CharacterData& _in, CharacterData& _out) {
	_out.basisId = _in.basis_id();
	return ;
}

void ProtoConverter::FromProto(IN const UserAndChatServer::ChatData& _in, OUT ChatData& _out) {
	auto chatProfile = _out.GetChatProfile();
	if(chatProfile == nullptr) {
		chatProfile = MakeShared<ChatProfile>();
		_out.SetChatProfile(chatProfile);
	}
	FromProto(_in.chat_profile(), *chatProfile);
	auto chatTypeOpt = ENUM_FROM_INT(CHAT_TYPE, _in.chat_type());
	if(chatTypeOpt.has_value()) {
		_out.SetChatType(chatTypeOpt.value());
	}
	_out.SetMsg(_in.msg());
	return ;
}

void ProtoConverter::FromProto(IN const UserAndChatServer::ChatProfile& _in, OUT ChatProfile& _out) {
	_out.SetAccountId(_in.profile_id());
	_out.SetNickName(_in.nick_name());
	_out.SetProfileHeroId(_in.profile_hero_id());
	_out.SetProfileFrameId(_in.profile_frame_id());
	return ;
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
	)
{
	_encryptKey = _packet.encrypt_key();
}


void ProtoConverter::FromPacket(const UserAndChatServer::AnsChatConn& _packet
	, IN ChatProfileSptr _profile
	, IN int32_t& _roomNo
	, IN vector<ChatProfileSptr>& _profiles
) {
	FromProto(_packet.profile(), *_profile);
	
	_roomNo = _packet.room_no();
	
	for(const auto& _proto : _packet.profiles()) {
		auto otherProfile = MakeShared<ChatProfile>();
		FromProto(IN _proto, OUT *otherProfile);
		_profiles.push_back(otherProfile);
	}


	return ;
}

void ProtoConverter::FromPacket(IN const UserAndChatServer::NotiChat& _packet, OUT ChatData& _chatData) {
	
	FromProto(IN _packet.chat_data(), OUT _chatData);
	return ;
}

void ProtoConverter::FromPacket(const UserAndChatServer::NotiEnterChatRoom& _packet, OUT ChatProfileSptr& _enterProfile) {
	if (_enterProfile == nullptr) {
		_enterProfile = MakeShared<ChatProfile>();
	}
	FromProto(_packet.enter_profile(), *_enterProfile);
}


void ProtoConverter::FromPacket(const UserAndChatServer::NotiLeaveChatRoom& _packet, OUT int64_t& _leaveAccountId) {
	_leaveAccountId = _packet.accoun_id();
}


///////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion
