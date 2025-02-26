#include "pch.h"
#include "MonitorHelper.h"

void MonitorHelper::ReportStatus()
{
	CalcStatus();
	printf("[cpu usage][%3d], [mem usage][%lld], [physicMem usage][%lld]\n", cpuUsePercent, memUse, physicMemUse);

	//todo : MasterServer에 packet을 보내 상태를 보고하도록 한다.
}

void MonitorHelper::ReserveReport()
{
	const int64_t reportMsec = 2 * 1000;
	shared_ptr<MonitorHelper> _owner = static_pointer_cast<MonitorHelper>(shared_from_this());
	JobTimer::Get().Reserve(reportMsec , _owner, [_owner](){
		_owner->ReportStatus();
		_owner->ReserveReport();
	});
}

