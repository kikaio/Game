#include "pch.h"
#include "ChatRoomMng.h"

void ChatRoomMng::Init(int32_t _normalRoomCnt, int32_t _guildRoomCnt)
{
	for(int idx = 0; idx < _normalRoomCnt; idx++) {
		auto roomSptr = MakeShared<ChatRoom>();
		roomSptr->SetRoomNo(idx+1);
		normalRooms.emplace(idx+1, roomSptr);
	}

	for (int idx = 0; idx < _guildRoomCnt; idx++) {
		auto roomSptr = MakeShared<ChatRoom>();
		roomSptr->SetRoomNo(idx + 1);
		guildRooms.emplace(idx + 1, roomSptr);
	}

}

ChatRoomSptr ChatRoomMng::GetNormalRoom(int32_t _roomNo)
{
	auto iter = normalRooms.find(_roomNo);
	if(iter == normalRooms.end()) {
		return nullptr;
	}
	return iter->second;
}

ChatRoomSptr ChatRoomMng::GetGuildRoom(int32_t _roomNo)
{
	auto iter = guildRooms.find(_roomNo);
	if (iter == guildRooms.end()) {
		return nullptr;
	}
	return iter->second;
}

void ChatRoomMng::BroadcastToNormalRooms(const UserAndChatServer::NotiChat& _noti)
{
	for (auto pair : normalRooms) {
		pair.second->Broadcast(_noti);
	}
}

void ChatRoomMng::BroadcastToGuildRooms(const UserAndChatServer::NotiChat& _noti)
{
	for (auto pair : guildRooms) {
		pair.second->Broadcast(_noti);
	}
}

void ChatRoomMng::Render()
{
	CS_DEBUG_LOG("[Normal Rooms]==========");
	for(auto _pair : normalRooms) {
		if(_pair.second->GetUserCnt() < 1) {
			continue;
		}
		_pair.second->Render();
	}
	CS_DEBUG_LOG("========================");

	CS_DEBUG_LOG("[Guild Rooms]==========");
	for(auto _pair : guildRooms) {
		if (_pair.second->GetUserCnt() < 1) {
			continue;
		}
		_pair.second->Render();
	}
	CS_DEBUG_LOG("========================");
}
