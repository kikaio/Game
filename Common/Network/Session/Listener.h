#pragma once

//iocp 용
class Listener : public IocpObj //, public enable_shared_from_this<Listener>
{
public:
	Listener(UInt32 _port);
};