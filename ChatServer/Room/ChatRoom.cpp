#include "pch.h"
#include "ChatRoom.h"

int32_t ChatRoom::maxUserCnt = 3;
int32_t ChatRoom::maxRoomCnt = 10;

int32_t ChatRoom::GetUserCnt()
{
	return chatUsers.size();
}

void ChatRoom::SetRoomNo(int32_t _no)
{
	roomNo = _no;
}

int32_t ChatRoom::GetRoomNo()
{
	return roomNo;
}

std::map<int64_t, ChatUserSptr> ChatRoom::GetUsers()
{
	return chatUsers;
}

void ChatRoom::GetProfiles(OUT vector<ChatProfileSptr>& _out) {
	for(auto pair : chatUsers) {
		_out.push_back(pair.second->GetProfile());
	}
	return ;
}

void ChatRoom::Enter(ChatUserSptr _user)
{
	int64_t accountId = _user->GetAccountId();
	auto iter = chatUsers.find(accountId);
	if(iter != chatUsers.end()) {
		//todo : duplication error log
		return ;
	}
	chatUsers[accountId] = _user;
	return ;
}

void ChatRoom::Leave(ChatUserSptr _user)
{
	int64_t accountId = _user->GetAccountId();
	auto iter = chatUsers.find(accountId);
	if(iter == chatUsers.end()) {
		//todo : not exist in this room error log
		return ;
	}
	chatUsers.erase(iter);
	return ;
}

void ChatRoom::Broadcast(UserAndChatServer::NotiChat _packet)
{
	auto chatDataSptr = MakeShared<ChatData>();
	ProtoConverter::FromProto(_packet.chat_data(), OUT * chatDataSptr);
	//chat 이력 보관
	chatDatas.push_back(chatDataSptr);
	
	for(auto& _pair : chatUsers) {
		auto chatUser = _pair.second;
		if(chatUser == nullptr) { 
			continue;	
		}
		auto _session = chatUser->GetSession();
		if(_session == nullptr) {
			continue;
		}
		if(_session->IsConnected() == false) {
			continue;
		}
		_session->SendPacket(_packet);
	}
}

void ChatRoom::Render()
{
	CS_DEBUG_LOG("[ChatRoom : {}]-------", roomNo);
	int curChatHistorySize = chatDatas.size();
	int chatPageSize = 5;
	int lastPageIdx = curChatHistorySize / chatPageSize;
	int curChatCnt = curChatHistorySize % chatPageSize;
	int lastIdx = lastPageIdx * chatPageSize + curChatCnt;

	for(int curIdx = lastPageIdx*chatPageSize; curIdx < lastIdx+1; curIdx++) {
		chatDatas[curIdx]->Render();
	}
	CS_DEBUG_LOG("-----------------------", roomNo);
}
	