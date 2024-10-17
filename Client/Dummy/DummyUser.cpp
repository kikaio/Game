#include "pch.h"
#include "DummyUser.h"

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
	UserAndGameServer::ReqChat packet;

	auto* chatInfo = packet.mutable_chat_info();
	auto* profile = chatInfo->mutable_user_profile();
	profile->set_nick_name(GetNickname());
	chatInfo->set_msg(_msg);
	if(session->SendPacketReqChat(packet) == false) {
		//todo : logging
	}
}
