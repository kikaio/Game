#include "pch.h"
#include "DummyUser.h"
#include "DummyUserManager.h"


void DummyUser::ClearUser()
{
	gameServerSession = nullptr;

}
void DummyUser::SetChatServerInfo(const string& _host, int16_t _port) {
	chatHost = _host;
	chatPort = _port;
	return ;
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

bool DummyUser::IsChatConnected() {
	return chatServerSession->IsConnected();
}

void DummyUser::OnChatServerSessionDisconnected() {
	DUM_DEBUG_LOG("chat server disConnected");
	return;
}

void DummyUser::OnChatServerSessionConnected() {
	DUM_DEBUG_LOG("chat server Connected");
	return;
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

void DummyUser::SetProfile(const DummyProfile& _profile)
{
	profile = _profile;
}

DummyProfile& DummyUser::GetProfile()
{
	return profile;
}

void DummyUser::SetInventory(const Inventory& _inven)
{
	inventory = _inven;
}

Inventory& DummyUser::GetInventory()
{
	return inventory;
}

void DummyUser::SetLoginResultData(const LoginResultData& _data)
{
	loginResultData = _data;
}

LoginResultData& DummyUser::GetLoginResultData()
{
	return loginResultData;
}

void DummyUser::Render()
{
	DUM_DEBUG_LOG("Dummy Render======");
	loginResultData.Render();
	profile.Render();
	inventory.Render();
}
