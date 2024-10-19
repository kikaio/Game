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
		if (items.empty()) {
			return T();
		}
		T ret = items.front();
		items.pop();
		return ret;
	}

	void PopAll(OUT Vector<T>& _vect) {
		WRITE_LOCK_GUARDDING(rwLock);
		while (items.empty() == false) {
			auto item = items.front();
			items.pop();
			_vect.push_back(item);
		}
		return;
	}

public:
	void Clear()
	{
		WRITE_LOCK_GUARDDING(rwLock);
		items = queue<T>();
		return;
	}
};
