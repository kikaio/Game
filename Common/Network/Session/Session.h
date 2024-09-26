#pragma once


//iocp 용
class Session : public IocpObj //, public enable_shared_from_this<Session>
{
public:
	Session() = default;
	virtual ~Session() {}
};