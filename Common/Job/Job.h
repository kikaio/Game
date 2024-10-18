#pragma once


class Job 
{
public:
	Job(CallBackType&& _cb)
	 : callback(move(_cb))
	{
	}

	template<typename T, typename Ret, typename... Args>
	Job(shared_ptr<T> _owner, Ret(T::*_memFunc)(Args... args), Args&&... _args)
	{
		callback = [_owner, _memFunc, _args...]() {
			(_owner.get()->*_memFunc)(_args...);
		};
	}

	void Execute()
	{
		callback();
	}
private:
	CallBackType callback;
};