#include "pch.h"
#include "ChatUser.h"


int64_t ChatUser::GetAccountId() {
	return accountId;
}

void ChatUser::SetAccountId(int64_t _id) {
	accountId = _id;
}

ChatProfileSptr ChatUser::GetProfile() {
	return profile;
}

void ChatUser::SetProfile(ChatProfileSptr _profile) {
	profile = _profile;
}

UserSessionSptr ChatUser::GetSession()
{
	return userSession.lock();;
}

void ChatUser::SetSession(UserSessionSptr _session)
{
	userSession = _session;
}

ChatRoomSptr ChatUser::GetChatRoom() {
	return chatRoom.lock();
}

void ChatUser::SetChatRoom(ChatRoomSptr _room) {
	chatRoom = _room;
}