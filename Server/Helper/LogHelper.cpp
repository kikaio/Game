#include "LogHelper.h"
#include "LogHelper.h"
#include "pch.h"
#include "LogHelper.h"

LoggerSptr LogHelper::gameLogger = nullptr;
LoggerSptr LogHelper::masterServerLogger = nullptr;

void LogHelper::Init(string _logFolderPath, string _lvStr)
{
	auto loggerLv = spdlog::level::debug;
	std::transform(_lvStr.begin(), _lvStr.end(), _lvStr.begin(), ::toupper);
	if(_lvStr == "ERROR") {
		loggerLv = spdlog::level::err;
	}
	else if (_lvStr == "INFO") {
		loggerLv = spdlog::level::info;
	}
	else if (_lvStr == "WARN") {
		loggerLv = spdlog::level::warn;
	}
	else if (_lvStr == "TRACE") {
		loggerLv = spdlog::level::trace;
	}
	else {
		loggerLv = spdlog::level::debug;
	}


	GAME_LOGGER = CreateGameLogger(_logFolderPath + "/game.log");
	GAME_LOGGER->SetLevel(loggerLv);
	
	MASTER_SERVER_LOGGER = CreateMasterServerLogger(_logFolderPath + "/master.log");
	MASTER_SERVER_LOGGER->SetLevel(loggerLv);
}

LoggerSptr LogHelper::CreateGameLogger(string _logFilePath)
{
	return std::make_shared<Logger>("game", _logFilePath, true);
}

LoggerSptr LogHelper::CreateMasterServerLogger(string _logFilePath)
{
	return std::make_shared<Logger>("master", _logFilePath, true);
}
