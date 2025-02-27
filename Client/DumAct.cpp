#include "pch.h"
#include "DumAct.h"
#include "DummyUser.h"
#include "GameServerSession.h"

void DumActGameServerConnect::DoAct(DummyUserSptr _dumSptr)
{
	GameServerSessionSptr gsSession = MakeShared<GameServerSession>();
	_dumSptr->SetGameServerSession(gsSession);
	gsSession->SetOnSessionDisconnectedFunc([_dumSptr = _dumSptr]() {
		_dumSptr->OnGameServerSessionDisconnected();
	});
	gsSession->Net()->SetAddrAny(0);
	if(gsSession->Bind() == false) {
		printf("[dummy:%d]bind failed.. err : %d\n", _dumSptr->GetDummyIdx(), WSAGetLastError());
		return ;
	}
	IocpCoreSptr iocpCoreSptr = _dumSptr->gameServerNetCore->GetIocpCore();
	gsSession->SetSockOpts();
	gsSession->SetNetCore(_dumSptr->gameServerNetCore);
	gsSession->SetIocpCore(iocpCoreSptr);
	iocpCoreSptr->RegistToIocp(gsSession->Sock());
	gsSession->TryConnect();
	return ;
}

void DumActChat::DoAct(DummyUserSptr _dumSptr) {
	// todo : dummy user send chat packet using msg value
	JobTimer::Get().Reserve(actDelayMsec, _dumSptr, [_dumSptr, chatMsg = chatMsg]() {
		if (_dumSptr->IsConnected() == false) {
			return;
		}
		UserAndGameServer::ReqChat packet;

		auto* chatInfo = packet.mutable_chat_info();
		auto* profile = chatInfo->mutable_user_profile();
		profile->set_nick_name(_dumSptr->GetNickname());
		chatInfo->set_msg(chatMsg + "from " + _dumSptr->GetNickname());
		auto _gsSession = _dumSptr->GetGameServerSession();
		if (_gsSession->SendPacketReqChat(packet) == false) {
			//todo : logging
		}
		return;
		}
	);
	return;
}
