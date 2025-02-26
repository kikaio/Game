#pragma once


class StatusMonitor : public JobQueue {
protected:
	ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	int numOfProcessors;
	HANDLE self;
protected:
	int cpuUsePercent = 0;
	SIZE_T memUse = 0;
	SIZE_T physicMemUse = 0;
public:
	StatusMonitor();
private:
	double ProcessCpuUsage();
	SIZE_T ProcessMemUsage();
	SIZE_T PhysicMemUsage();
protected:
	void CalcStatus();
public :
	//현재 mem, cpu 사용량 확인
	virtual void ReportStatus();
};