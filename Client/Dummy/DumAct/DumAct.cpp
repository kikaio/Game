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
		//callback 등록
		_dumSptr->ReserveGameServerProtocol(
			UserAndGameServer::Ans, UserAndGameServer::GameConn
			, [_dumSptr](){
				DUM_DEBUG_LOG("dum recv AnsGameConn");
				_dumSptr->DoDumAct();
		});
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
		//callback 등록
		_dumSptr->ReserveGameServerProtocol(
			UserAndGameServer::Ans, UserAndGameServer::Login
			, [_dumSptr]() {
				DUM_DEBUG_LOG("dum recv AnsLogin");
				_dumSptr->DoDumAct();
		});
		return ;
	});
	return ;
}

DumActChatConn::DumActChatConn(uint64_t _delayMsec)
{
	actDelayMsec = _delayMsec;
}

void DumActChatConn::DoAct(DummyUserSptr _dumSptr)
{
	ReserveAct(_dumSptr, [_dumSptr, this]() {

		auto _session = MakeShared<ChatServerSession>();
		_dumSptr->SetChatServerSession(_session);
		_session->SetDummyUser(_dumSptr);

		_session->SetOnSessionConnectedFunc([_dumSptr = _dumSptr]() {
			_dumSptr->OnChatServerSessionConnected();
			});
		_session->SetOnSessionDisconnectedFunc([_dumSptr = _dumSptr]() {
			_dumSptr->OnChatServerSessionDisconnected();
			});
		_session->Net()->SetAddrAny(0);
		if (_session->Bind() == false) {
			printf("[dummy:%d]bind failed.. err : %d\n", _dumSptr->GetDummyIdx(), WSAGetLastError());
			return;
		}
		IocpCoreSptr iocpCoreSptr = _dumSptr->chatServerNetCore->GetIocpCore();
		_session->SetSockOpts();
		_session->SetNetCore(_dumSptr->chatServerNetCore);
		_session->SetIocpCore(iocpCoreSptr);
		iocpCoreSptr->RegistToIocp(_session->Sock());
		_session->TryConnect();
	});
	return;
}
