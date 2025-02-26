#pragma once


struct JobData
{
public:
	JobData(weak_ptr<JobQueue> _owner, JobSptr _job)
		: owner(_owner), job(_job)
	{
	}
public:
	weak_ptr<JobQueue> owner;
	JobSptr job;
};

struct TimerItem
{
public:
	bool operator < (const TimerItem& _other) const {
		return executeTick > _other.executeTick;
	}
public:
	uint64_t executeTick = 0;
	JobData* jobData = nullptr;
};

class JobTimer : public Singleton<JobTimer>
{
private:
	VAL_LOCK(timerLock);
	priorityQueue<TimerItem> items;
	atomic<bool> distributing = false;
public:
	void Reserve(uint64_t _afterTick, weak_ptr<JobQueue> _owner, JobSptr _job);
	void Reserve(uint64_t _afterTick, weak_ptr<JobQueue> _owner, CallBackType&& _cb);
	void Distribute(uint64_t _now);
	void Clear();

};