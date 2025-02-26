#pragma once


class MonitorHelper : public StatusMonitor {

public:
	virtual void ReportStatus() override;
public:
	void ReserveReport();
};