#include "pch.h"
#include "GlobalQueue.h"

GlobalQueue::GlobalQueue()
{
}

GlobalQueue::~GlobalQueue()
{
}

void GlobalQueue::Push(JobQueueSptr _jobQueue)
{
	jobQueues.Push(_jobQueue);
}

JobQueueSptr GlobalQueue::Pop()
{
	return jobQueues.Pop();
}
