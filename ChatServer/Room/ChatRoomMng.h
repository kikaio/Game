#pragma once

class ChatRoomMng : public Singleton<ChatRoomMng> {
public:
	static int32_t initNormalRoomSize;
	static int32_t initGuildRoomSize;
private:
	atomic<int64_t> roundRobinIdx = 0;
	std::map<int32_t, ChatRoomSptr> normalRooms;
	std::map<int32_t, ChatRoomSptr> guildRooms;
public:
	void Init();
public:
	ChatRoomSptr GetNormalRoom(int32_t _roomNo);
	ChatRoomSptr GetRoundRobinNormalRoom();
	ChatRoomSptr GetGuildRoom(int32_t _roomNo);
public:
	void BroadcastToNormalRooms(const UserAndChatServer::NotiChat& _noti);
	void BroadcastToGuildRooms(const UserAndChatServer::NotiChat& _noti);
public:
	void Render();
};