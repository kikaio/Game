#include "pch.h"
#include "ChatRoomMng.h"

int32_t ChatRoomMng::initNormalRoomSize = 1;
int32_t ChatRoomMng::initGuildRoomSize = 1;

void ChatRoomMng::Init()
{
	for(int idx = 0; idx < initNormalRoomSize; idx++) {
		auto roomSptr = MakeShared<ChatRoom>();
		roomSptr->SetRoomNo(idx+1);
		normalRooms.emplace(idx+1, roomSptr);
	}

	for (int idx = 0; idx < initGuildRoomSize; idx++) {
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

ChatRoomSptr ChatRoomMng::GetRoundRobinNormalRoom() {
	bool finded = false;
	int64_t targetNo = roundRobinIdx.fetch_add(1) % normalRooms.size() + 1;
	printf("roundRobinIdx : %d / normalRooms size : %d / target room no : %d\n", roundRobinIdx.load(), normalRooms.size(), targetNo);
	for(int idx = 0; idx < normalRooms.size(); idx++) {
		if (normalRooms[targetNo]->GetUserCnt() >= ChatRoom::maxUserCnt) {
			targetNo = roundRobinIdx.fetch_add(1) % normalRooms.size() + 1;
			continue;
		}
		finded = true;
		break;
	}

	if(finded) {
		return normalRooms[targetNo];
	}
	//모든 방이 가득 찬 경우
	//신규 방 생성
	targetNo = normalRooms.size() + 1;
	normalRooms[targetNo] = MakeShared<ChatRoom>();
	normalRooms[targetNo]->SetRoomNo(targetNo);
	return normalRooms[targetNo];
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
