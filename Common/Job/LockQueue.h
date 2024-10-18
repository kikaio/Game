#pragma once


template<typename T>
class LockQueue
{
private:
	VAL_RW_LOCK(rwLock);
	queue<T> items;
public:
	void Push(T _job)
	{
		WRITE_LOCK_GUARDDING(rwLock);
		items.push(_job);
	}
	T Pop()
	{
		WRITE_LOCK_GUARDDING(rwLock);
		T ret = items.front();
		items.pop();
		return ret;
	}
public:
	void Clear()
	{
		WRITE_LOCK_GUARDDING(rwLock);
		items = queue<T>();
		return;
	}
};
