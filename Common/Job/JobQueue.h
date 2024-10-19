#pragma once
#include "LockQueue.h"


class JobQueue : public enable_shared_from_this<JobQueue>
{
protected:
	LockQueue<JobSptr> jobs;
	Atomic<int32_t> jobCnt = 0;
private:
	void Push(JobSptr&& _job);
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
		Push(MakeShared(owner, memFunc, std::forward<Args>(args)...));
		return ;
	}

	void ClearJobs() {
		jobs.Clear();
	}
public:
	void Execute();
};