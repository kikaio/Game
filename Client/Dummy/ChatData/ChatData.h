#pragma once

class ChatData {
private:
	mutable ChatProfileSptr chatProfile = nullptr;
	CHAT_TYPE chatType = CHAT_TYPE::NORMAL;
	string msg = "";
public:
	ChatProfileSptr GetChatProfile()const;
	CHAT_TYPE GetChatType() const;
	const string& GetMsg() const;
public:
	void SetChatProfile(ChatProfileSptr _profile);
	void SetChatType(CHAT_TYPE _type);
	void SetMsg(const string& _msg);
};