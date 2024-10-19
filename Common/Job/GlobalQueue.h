#pragma once
#include "LockQueue.h"


class GlobalQueue : public Singleton<GlobalQueue>
{
public:
	GlobalQueue();
	~GlobalQueue();
private:
	LockQueue<JobQueueSptr> jobQueues;

public:
	void Push(JobQueueSptr _jobQueue);
	JobQueueSptr Pop();

};