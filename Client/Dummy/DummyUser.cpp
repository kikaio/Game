#include "pch.h"
#include "DummyUser.h"
#include "DummyUserManager.h"

void DummyUser::ClearUser()
{
	session = nullptr;

}

bool DummyUser::IsConnected()
{
	if (session == nullptr || session->IsConnected() == false) {
		return false;
	}
	return true;
}

DummyUserSptr DummyUser::GetSptr()
{
	return shared_from_this();
}

void DummyUser::SetDummySession(DummySessionSptr _dummySession)
{
	session = _dummySession; session;
}

void DummyUser::SendChatMsg(string _msg)
{
	if (IsConnected() == false) {
		return;
	}

	UserAndGameServer::ReqChat packet;

	auto* chatInfo = packet.mutable_chat_info();
	auto* profile = chatInfo->mutable_user_profile();
	profile->set_nick_name(GetNickname());
	chatInfo->set_msg(_msg);
	if (session->SendPacketReqChat(packet) == false) {
		//todo : logging
	}
}

void DummyUser::OnSessionDisconnected()
{
	//todo : 기존 session 참조를 nullptr로
	session = nullptr;
	profile.Clear();
	if (dummyUserRecycle == false) {
		DummyUserManager::Get().PopDummyUser(dummyIdx);
	}
}
