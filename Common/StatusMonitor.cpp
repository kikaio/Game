#include "pch.h"
#include "StatusMonitor.h"
#include "psapi.h"

StatusMonitor::StatusMonitor()
{
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numOfProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

double StatusMonitor::ProcessCpuUsage()
{
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (double)((sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart));
	if((now.QuadPart - lastCPU.QuadPart) != 0) {
		percent /= (now.QuadPart - lastCPU.QuadPart);
	}
	else {
		percent = 0;
	}
	percent /= numOfProcessors;
	percent *= 100;
	return FIX_IN_RANGE(0, (int)percent, 100);
}

SIZE_T StatusMonitor::ProcessMemUsage()
{
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	return (size_t)pmc.WorkingSetSize;
}

SIZE_T StatusMonitor::PhysicMemUsage()
{
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&meminfo);
	return (size_t)(meminfo.ullTotalPhys - meminfo.ullAvailPhys);
}

void StatusMonitor::CalcStatus()
{	
	cpuUsePercent = ProcessCpuUsage();
	memUse = ProcessMemUsage();
	physicMemUse = PhysicMemUsage();
}

void StatusMonitor::ReportStatus()
{
	CalcStatus();
	printf("[cpu usage][%3d], [mem usage][%lld], [physicMem usage][%lld]\n", cpuUsePercent, memUse, physicMemUse);
}
