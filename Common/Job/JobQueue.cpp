#include "pch.h"
#include "JobQueue.h"

void JobQueue::Push(JobSptr&& _job)
{
	const int32_t prevCnt = jobCnt.fetch_add(1);
	jobs.Push(_job);
	
	if (prevCnt == 0) {
		if (LCurrentJobQueue == nullptr) {
			Execute();
		}
		else {
			GlobalQueue::Get().Push(shared_from_this());
		}
		return;
	}
	return;
}

void JobQueue::Execute()
{
	LCurrentJobQueue = this;
	while (true) {
		Vector<JobSptr> _jobs;
		jobs.PopAll(_jobs);
		int32_t curJobCnt = _jobs.size();
		for (auto _jobSptr : _jobs) {
			_jobSptr->Execute();
		}
		//모든 job을 현재 스레드가 다 처리한 경우 종료.
		if (jobCnt.fetch_sub(curJobCnt) == curJobCnt) {
			LCurrentJobQueue = nullptr; 
			return;
		}
		
	}
	return;
}
