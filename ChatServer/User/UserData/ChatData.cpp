#include "pch.h"
#include "ChatData.h"



void ChatData::SetChatProfile(ChatProfileSptr _profile) {
	chatProfile = _profile;
}

ChatProfileSptr ChatData::GetChatProfile() const {
	return chatProfile;
}

CHAT_TYPE ChatData::GetChatType() const {
	return chatType;
}

void ChatData::SetChatType(CHAT_TYPE _type) {
	chatType = _type;
}

const string& ChatData::GetMsg() const {
	return msg;
}

void ChatData::SetMsg(const string& _msg) {
	msg = _msg;
}

void ChatData::Render() {
	string tag = ENUM_TO_STR(chatType);
	CS_DEBUG_LOG("[{}:{}] send msg : {}", tag, chatProfile->GetNickName(), msg);
}
