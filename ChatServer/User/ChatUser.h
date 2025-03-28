#pragma once

class ChatUser {
private:
	int64_t accountId = 0;
	UserSessionWptr userSession;
	ChatProfileSptr profile = nullptr;
	ChatRoomWptr chatRoom;
public:
	int64_t GetAccountId();
	void SetAccountId(int64_t _id);
	ChatProfileSptr GetProfile();
	void SetProfile(ChatProfileSptr _profile);
	UserSessionSptr GetSession();
	void SetSession(UserSessionSptr _session);

	ChatRoomSptr GetChatRoom();
	void SetChatRoom(ChatRoomSptr _room);
};