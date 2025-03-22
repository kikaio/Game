#pragma once

class UserSession : public Session {
private :
	ChatUserSptr chatUser = nullptr;
};