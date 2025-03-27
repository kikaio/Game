#pragma once

class ChatData {
private:
	ChatProfileSptr chatProfile = nullptr;
	ChatType chatType = ChatType::NORMAL;
	string msg = "";
public:
	ChatProfileSptr GetChatProfile();
	ChatType GetChatType();
	const string& GetMsg();
public:
	void SetChatProfile(ChatProfileSptr _profile);
	void SetChatType(ChatType _type);
	void SetMsg(const string& _msg);
};