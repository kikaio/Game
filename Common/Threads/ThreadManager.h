#pragma once




class ThreadManager : public Singleton<ThreadManager>
{
private:
	static atomic<UInt32> threadSeedNo;
	std::vector<ThreadSptr> threads;
	VAL_LOCK(threadsLock);
public:
	void PushThread(WorkFunc _func, const char* _tName, const char* _desc = "None Desc");
	void PushAndStart(WorkFunc _func, const char* _tName, const char* _desc = "None Desc");
	void StartAll();
	void JoinAll();
	void RenderThreadsInfo();
};