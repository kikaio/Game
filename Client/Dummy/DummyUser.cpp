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

void DummyUser::SetTestScenario(const std::vector<DumActSptr>& _dumActs)
{	
	dumActs = _dumActs;
}

void DummyUser::DoDumAct()
{
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
	profile.Clear();
	if(dummyUserRecycle == false) {
		DummyUserManager::Get().PopDummyUser(dummyIdx);
	}
}
