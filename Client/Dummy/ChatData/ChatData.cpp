#include "pch.h"
#include "ChatData.h"

ChatProfileSptr ChatData::GetChatProfile() const
{
	return chatProfile;
}

CHAT_TYPE ChatData::GetChatType() const
{
	return chatType;
}

const string& ChatData::GetMsg() const
{
	return msg;
}

void ChatData::SetChatProfile(ChatProfileSptr _profile)
{
	chatProfile = _profile;
}

void ChatData::SetChatType(CHAT_TYPE _type)
{
	chatType = _type;
}

void ChatData::SetMsg(const string& _msg)
{
	msg = _msg;
}
