#pragma once

class ChatRoom : public JobQueue {
private:
	int32_t roomNo = 0;
private:
	std::map<int64_t, ChatUserSptr> chatUsers;
	std::vector<ChatDataSptr> chatDatas;
public:
	int32_t GetUserCnt();
public:
	void SetRoomNo(int32_t _no);
	int32_t GetRoomNo();
public:
	std::map<int64_t, ChatUserSptr> GetUsers();
public:
	void Enter(ChatUserSptr _user);
	void Leave(ChatUserSptr _user);
public:
	void Broadcast(const UserAndChatServer::NotiChat& _packet);
public:
	void Render();
};
