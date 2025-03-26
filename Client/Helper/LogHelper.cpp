#include "pch.h"
#include "LogHelper.h"


LoggerSptr LogHelper::dumLogger = nullptr;
LoggerSptr LogHelper::clientLogger = nullptr;

LoggerSptr LogHelper::CreateDumLogger(string _dumLogPath)
{
	return std::make_shared<Logger>("dummy", _dumLogPath, true);
}
LoggerSptr LogHelper::CreateClientLogger(string _dumLogPath)
{
	return std::make_shared<Logger>("client", _dumLogPath, true);
}

void LogHelper::Init(string _logFolderPath)
{
	DUM_LOOGER = CreateDumLogger(_logFolderPath + "/dum.log");
	DUM_LOOGER->SetLevel(spdlog::level::debug);
	
	CLIENT_LOOGER = CreateClientLogger(_logFolderPath + "/client.log");
	CLIENT_LOOGER->SetLevel(spdlog::level::debug);
}
