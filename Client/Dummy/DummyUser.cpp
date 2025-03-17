#include "pch.h"
#include "DummyUser.h"
#include "DummyUserManager.h"


void DummyUser::ClearUser()
{
	gameServerSession = nullptr;

}

bool DummyUser::IsConnected()
{
	if(gameServerSession == nullptr || gameServerSession->IsConnected() == false) {
		return false;
	}
	return true;
}

void DummyUser::SetTestScenario(const std::vector<DumActSptr>& _dumActs, bool _isLoopTest)
{	
	isLoopTest = _isLoopTest;
	dumActs = _dumActs;
}

void DummyUser::DoDumAct()
{
	if(dumActIdx >= dumActs.size()) {
		if(isLoopTest) {
			//처음부터 다시 반족하는 test의 경우
			dumActIdx = 0;
		}
		else {
			printf("[dummy:%d]test scenario fin\n", dummyIdx);
			return ;
		}
	}
	DumActSptr act = dumActs[dumActIdx++];
	if(act == nullptr) {
		// todo : error logging 
		return ;
	}
	act->Do(GetSptr());
}

DummyUserSptr DummyUser::GetSptr()
{
	return static_pointer_cast<DummyUser>(shared_from_this());
}

void DummyUser::SetGameServerSession(GameServerSessionSptr _dummySession)
{
	gameServerSession = _dummySession; gameServerSession;
}

void DummyUser::OnGameServerSessionDisconnected()
{
	//todo : 기존 session 참조를 nullptr로
	gameServerSession = nullptr;
	DoDumAct();
}

void DummyUser::OnGameServerSessionConnected()
{
	DoDumAct();
}

void DummyUser::SetLoginData(const LoginData& _loginData)
{
	loginData = _loginData;
}

const LoginData& DummyUser::GetLoginData() {
	return loginData;
}

void DummyUser::SetChatProfile(const ChatProfile& _chatProfile)
{
	chatProfile = _chatProfile;
}

const ChatProfile& DummyUser::GetChatProfile()
{
	return chatProfile;
}

Inventory& DummyUser::GetInventory()
{
	return inventory;
}
