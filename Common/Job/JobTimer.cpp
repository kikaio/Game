#include "pch.h"
#include "JobTimer.h"

void JobTimer::Reserve(uint64_t _afterTick, weak_ptr<JobQueue> _owner, JobSptr _job)
{
	const uint64_t executeTick = ::GetTickCount64() + _afterTick;
	JobData* jobData = reinterpret_cast<JobData*>(XALLOC(sizeof(JobData)));
	new (jobData) JobData(_owner, _job);

	LOCK_GUARDDING(timerLock);
	items.push(TimerItem{ executeTick, jobData });
}

void JobTimer::Distribute(uint64_t _now)
{
	if (this->distributing.exchange(true) == true) {
		return;
	}

	vector<TimerItem> vect;
	{
		LOCK_GUARDDING(timerLock);
		while (items.empty() == false) {
			const TimerItem timerItem = items.top();
			if (timerItem.executeTick > _now) {
				break;
			}

			vect.push_back(timerItem);
			items.pop();
		}
	}

	for (TimerItem& _item : vect) {
		if (JobQueueSptr _owner = _item.jobData->owner.lock()) {
			_owner->Push(_item.jobData->job);
		}

		XRELEASE(_item.jobData);

	}


	distributing.store(false);
	return;
}

void JobTimer::Clear()
{
	LOCK_GUARDDING(timerLock);
	while (items.empty() == false) {
		auto timerItem = items.top();
		items.pop();
		XRELEASE(timerItem.jobData);
	}
}
