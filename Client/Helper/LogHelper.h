#pragma once


#define DUM_LOOGER LogHelper::dumLogger

#define DUM_DEBUG_LOG(_str, ...) DUM_LOOGER->Debug(_str, __VA_ARGS__)


class LogHelper {
public:
	static LoggerSptr dumLogger;
public:
	static void Init(string _dumLogPath);
private:
	static LoggerSptr CreateDumLogger(string _dumLogPath);
};

