#pragma once

class ChatRoomMng : public Singleton<ChatRoomMng> {
private:
	std::map<int32_t, ChatRoomSptr> normalRooms;
	std::map<int32_t, ChatRoomSptr> guildRooms;
public:
	void Init(int32_t _normalRoomCnt, int32_t _guildRoomCnt);
public:
	ChatRoomSptr GetNormalRoom(int32_t _roomNo);
	ChatRoomSptr GetGuildRoom(int32_t _roomNo);
public:
	void BroadcastToNormalRooms(const UserAndChatServer::NotiChat& _noti);
	void BroadcastToGuildRooms(const UserAndChatServer::NotiChat& _noti);
public:
	void Render();
};