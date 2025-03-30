#pragma once
#include "LockQueue.h"


class JobQueue : public enable_shared_from_this<JobQueue>
{
protected:
	LockQueue<JobSptr> jobs;
	Atomic<int32_t> jobCnt = 0;
public:
	void Push(JobSptr _job, bool _pushOnly = false);
public:
	void DoAsync(CallBackType&& _cb)
	{
		Push(MakeShared<Job>(std::move(_cb)));
		return ;
	}

	template<typename T, typename Ret, typename... Args>
	void DoAsync(Ret(T::*memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(MakeShared<Job>(owner, memFunc, std::forward<Args>(args)...));
		return ;
	}

	void DoTimer(uint64_t _afterTick, CallBackType&& _cb)
	{
		JobSptr job = MakeShared<Job>(std::move(_cb));
		JobTimer::Get().Reserve(_afterTick, shared_from_this(), job);
		return;
	}

	template<typename T, typename Ret, typename... Args>
	void DoTimer(uint64_t _afterTick, Ret(T::* memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		JobSptr job = MakeShared(owner, memFunc, std::forward<Args>(args)...);
		JobTimer::Get().Reserve(_afterTick, shared_from_this(), job);
		return;
	}
	void ClearJobs() {
		jobs.Clear();
	}
public:
	void Execute();
};