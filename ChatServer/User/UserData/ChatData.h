#pragma once

class ChatData {
private:
	mutable ChatProfileSptr chatProfile = nullptr;
	CHAT_TYPE chatType;
	string msg;
public:
	void SetChatProfile(ChatProfileSptr _profile);
	ChatProfileSptr GetChatProfile() const;
	CHAT_TYPE GetChatType() const;
	void SetChatType(CHAT_TYPE _type);
	const string& GetMsg() const;
	void SetMsg(const string& _msg);
public:
	void Render();
};