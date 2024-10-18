#pragma once
#include "LockQueue.h"


class JobSerializer : public enable_shared_from_this<JobSerializer>
{
public:
	void PushJob(CallBackType&& _cb)
	{
		auto job = MakeShared<Job>(std::move(_cb));
		jobQueue.Push(job);
		return ;
	}

	template<typename T, typename Ret, typename... Args>
	void PushJob(Ret(T::*memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		auto job = MakeShared(owner, memFunc, std::forward<Args>(args)...);
		jobQueue.Push(job);
		return ;
	}

	virtual void FlushJob() abstract;

	void ClearJobs() {
		jobQueue.Clear();
	}
protected:
	LockQueue<JobSptr> jobQueue;
};