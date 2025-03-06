#include "pch.h"
#include "LogHelper.h"

LoggerSptr LogHelper::gameLogger = nullptr;
LoggerSptr LogHelper::masterServerLogger = nullptr;

void LogHelper::Init(string _logFilePath)
{
	GAME_LOGGER = CreateGameLogger(_logFilePath);
	MASTER_SERVER_LOGGER = CreateMasterServerLogger(_logFilePath);

	GAME_LOGGER->SetLevel(spdlog::level::debug);
	MASTER_SERVER_LOGGER->SetLevel(spdlog::level::debug);
}

LoggerSptr LogHelper::CreateGameLogger(string _logFilePath)
{
	return std::make_shared<Logger>("game", _logFilePath, true);
}

LoggerSptr LogHelper::CreateMasterServerLogger(string _logFilePath)
{
	return std::make_shared<Logger>("master", _logFilePath, true);
}
