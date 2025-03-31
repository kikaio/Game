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

DumActSetChatProfile::DumActSetChatProfile(ChatProfileSptr _chatProfile)
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
		if(gsSession->SendPacket(_req) == false) {
			//todo : error logging
			return ;
		}
		//callback 등록
		_dumSptr->SetWaitGamePacket(
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
		if(gsSession->SendPacket(_req) == false){
			//todo : erro logging
			return ;
		}
		//callback 등록
		_dumSptr->SetWaitGamePacket(
			UserAndGameServer::Ans, UserAndGameServer::Login
			, [_dumSptr]() {
				DUM_DEBUG_LOG("dum recv AnsLogin");
				_dumSptr->DoDumAct();
		});
		return ;
	});
	return ;
}

DumActChatServerConn::DumActChatServerConn(uint64_t _delayMsec)
{
	actDelayMsec = _delayMsec;
}

void DumActChatServerConn::DoAct(DummyUserSptr _dumSptr)
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

DumActChatConn::DumActChatConn(uint64_t _delayMsec) {
	actDelayMsec = _delayMsec;
	return;
}

void DumActChatConn::DoAct(DummyUserSptr _dumSptr) {
	ReserveAct(_dumSptr, [_dumSptr, this]() {
		auto gameProfile = _dumSptr->GetProfile();
		int64_t accountId = gameProfile.AccountId();
		UserAndChatServer::ReqChatConn req;
		ProtoConverter::ToPacket(IN accountId, OUT req);
		auto chatSession = _dumSptr->GetChatServerSession();
		if (chatSession->IsConnected()) {
			if(chatSession->SendPacket(req) == false) {
			}
			else {
				//callback 등록
				_dumSptr->SetWaitChatPacket(
					UserAndChatServer::Ans, UserAndChatServer::ChatConn
					, [_dumSptr]() {
						DUM_DEBUG_LOG("dum recv AnsChatConn");
						_dumSptr->DoDumAct();
					});
			}
		}
	});
	return;
}


DumActChat::DumActChat(uint64_t _delayMsec) {
	actDelayMsec = _delayMsec;
}

void DumActChat::DoAct(DummyUserSptr _dumSptr){
	ReserveAct(_dumSptr, [_dumSptr, this] (){
		auto csSession = _dumSptr->GetChatServerSession();
		if(csSession == nullptr || (csSession->IsConnected() == false)) {
			return ;
		}

		auto chatProfile = _dumSptr->GetChatProfile();
		if(chatProfile != nullptr) {
			//todo : error loging, need to call DoActChatConn
			int64_t accountId = chatProfile->GetAccountId();
			UserAndChatServer::ReqChat req;
			string msg = "test chat from dummy account - " + to_string(accountId);
			ChatData chatData;
			chatData.SetChatProfile(chatProfile);
			chatData.SetChatType(CHAT_TYPE::NORMAL);
			chatData.SetMsg(msg);
			ProtoConverter::ToPacket(IN chatData, OUT req);
			if(csSession->SendPacket(req) == false) {
				//todo : erro send packet is failed
				return ;
			}
			//해당 act에 대한 콜백처리는 실제 packet handle 쪽에서 담당한다.
			//이유 : 다른 유저가 보낸 Noti에도 반응할 수 있어 별도의 확인 후 다음 act를 호출해야 하기 때문에.
		}
	});
}
