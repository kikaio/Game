#pragma once

#define GAME_LOGGER LogHelper::gameLogger
#define MASTER_SERVER_LOGGER LogHelper::masterServerLogger


#define GS_TRACE_LOG(_str, ...) GAME_LOGGER->Trace(_str, __VA_ARGS__)
#define GS_DEBUG_LOG(_str, ...) GAME_LOGGER->Debug(_str, __VA_ARGS__)
#define GS_INFO_LOG(_str, ...) GAME_LOGGER->Info(_str, __VA_ARGS__)
#define GS_WARN_LOG(_str, ...) GAME_LOGGER->Warn(_str, __VA_ARGS__)
#define GS_ERROR_LOG(_str, ...) GAME_LOGGER->Error(_str, __VA_ARGS__)


class LogHelper {
public:
	static LoggerSptr gameLogger;
	static LoggerSptr masterServerLogger;
public:
	static void Init(string _logFilePath);
private:
	static LoggerSptr CreateGameLogger(string _logFilePath);
	static LoggerSptr CreateMasterServerLogger(string _logFilePath);
};
