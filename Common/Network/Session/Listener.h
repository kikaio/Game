﻿#pragma once


class SessionManager;
//iocp 용
class Listener : public IocpObj //, public enable_shared_from_this<Listener>
{
public:
	Listener(uint16_t _port);
private:
	SessionManager* sessionMgr = nullptr;
public:
	void SetSessionMgr(SessionManager* _ptr) {
		sessionMgr = _ptr;
	}

	SessionManager* GetSessionMgr() {
		return sessionMgr;
	}
};