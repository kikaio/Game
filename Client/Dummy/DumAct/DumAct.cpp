#include "pch.h"
#include "DumAct.h"
#include "DummyUser.h"
#include "GameServerSession.h"

void DumAct::ReserveAct(DummyUserSptr _dumSptr, CallBackType&& _cb)
{
	JobTimer::Get().Reserve(actDelayMsec, _dumSptr, std::move(_cb));
}

DumActGameServerConnect::DumActGameServerConnect(uint64_t _delayMsec)
{
	this->actDelayMsec = _delayMsec;
}

void DumActGameServerConnect::DoAct(DummyUserSptr _dumSptr)
{
	JobTimer::Get().Reserve(actDelayMsec, _dumSptr, [_dumSptr]() {

		GameServerSessionSptr gsSession = MakeShared<GameServerSession>();
		_dumSptr->SetGameServerSession(gsSession);
		gsSession->SetDummyUser(_dumSptr);

		gsSession->SetOnSessionConnectedFunc([_dumSptr = _dumSptr]() {
			_dumSptr->OnGameServerSessionConnected();
			});
		gsSession->SetOnSessionDisconnectedFunc([_dumSptr = _dumSptr]() {
			_dumSptr->OnGameServerSessionDisconnected();
			});
		gsSession->Net()->SetAddrAny(0);
		if (gsSession->Bind() == false) {
			printf("[dummy:%d]bind failed.. err : %d\n", _dumSptr->GetDummyIdx(), WSAGetLastError());
			return;
		}
		IocpCoreSptr iocpCoreSptr = _dumSptr->gameServerNetCore->GetIocpCore();
		gsSession->SetSockOpts();
		gsSession->SetNetCore(_dumSptr->gameServerNetCore);
		gsSession->SetIocpCore(iocpCoreSptr);
		iocpCoreSptr->RegistToIocp(gsSession->Sock());
		gsSession->TryConnect();
		}
	);
	return ;
}

DumActSetChatProfile::DumActSetChatProfile(const ChatProfile& _chatProfile)
{
	chatProfile = _chatProfile;
}

void DumActSetChatProfile::DoAct(DummyUserSptr _dumSptr)
{
	_dumSptr->SetChatProfile(chatProfile);
}

DumActChat::DumActChat(uint64_t _delayMsec, string _chatMsg, CHAT_TYPE _chatType)
{
	this->actDelayMsec = _delayMsec;
	chatType = _chatType;
	chatMsg = _chatMsg;
}

void DumActChat::DoAct(DummyUserSptr _dumSptr) {
	// todo : dummy user send chat packet using msg value
	JobTimer::Get().Reserve(actDelayMsec, _dumSptr, [_dumSptr, chatMsg = chatMsg, chatType=chatType]() {
		if (_dumSptr->IsConnected() == false) {
			return;
		}
		UserAndGameServer::ReqChat _req;
		ChatData chatData;
		chatData.chatType = chatType;
		chatData.chatProfile = _dumSptr->GetChatProfile();
		chatData.msg = chatMsg;
		ProtoConverter::ToPacket(chatData, _req);
		auto _gsSession = _dumSptr->GetGameServerSession();
		if (_gsSession->SendPacketReqChat(_req) == false) {
			//todo : logging
		}
		return;
		}
	);
	return;
}


DumActSetLoginData::DumActSetLoginData(string _userKey, string _token, string _refresh_token, bool _isNewLogin)
 : isNewLogin(_isNewLogin)
{
	if (_userKey == "") {
		_userKey = StrUtil::GetRandomStr(16);
	}
	loginData.sId = _userKey;
	loginData.loginToken = _token;
	loginData.refreshToken = _refresh_token;

}

void DumActSetLoginData::DoAct(DummyUserSptr _dumSptr)
{
	_dumSptr->SetLoginData(loginData);
	ReserveAct(_dumSptr, [_dumSptr](){
		_dumSptr->DoDumAct();
	});
	return ;
}

DumActGameConn::DumActGameConn(uint64_t _delayMsec)
{
	actDelayMsec = _delayMsec;
}

void DumActGameConn::DoAct(DummyUserSptr _dumSptr)
{
	ReserveAct(_dumSptr, [_dumSptr]() {
		UserAndGameServer::ReqGameConn _req;
		auto gsSession = _dumSptr->GetGameServerSession();
		if(gsSession->SendPacketReqGameConn(_req) == false) {
			//todo : error logging
			return ;
		}
	});
	return ;
}

DumActLogin::DumActLogin(uint64_t _delayMsec)
{
	actDelayMsec = _delayMsec;
}

void DumActLogin::DoAct(DummyUserSptr _dumSptr)
{
	//지정된 delay 후 행동하도록.
	ReserveAct(_dumSptr, [_dumSptr, this](){
		UserAndGameServer::ReqLogin _req;
		ProtoConverter::ToPacket(IN _dumSptr->GetLoginData(), OUT _req);
		auto gsSession = _dumSptr->GetGameServerSession();
		if(gsSession->SendPacketReqLogin(_req) == false){
			//todo : erro logging
			return ;
		}
		return ;
	});
	return ;
}
