#include "pch.h"
#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

Logger::Logger(string _loggerName, string _filePath, bool _isActive)
 : isActive(_isActive)
{
	auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(_filePath, false);
	stdoutSink->set_level(spdlog::level::trace);
	spdlog::sinks_init_list sinks = {
		stdoutSink 
		, fileSink
	};
	logger = std::make_shared<spdlog::logger>(_loggerName, sinks.begin(), sinks.end());
}

Logger::Logger(string _loggerName, spdlog::sinks_init_list _initList, bool _isActive)
	: isActive(_isActive)
{
	logger = std::make_shared<spdlog::logger>(_loggerName, _initList.begin(), _initList.end());
}

void Logger::ToggleActive()
{
	isActive = !isActive;
}

void Logger::SetLevel(spdlog::level::level_enum _lv)
{
	if(logger == nullptr) {
		return ;
	}
	logger->set_level(_lv);
	logger->flush_on(_lv);
}

void Logger::SetPattern(string _pattern)
{
	if(logger == nullptr) {
		return ;
	}

	logger->set_pattern(_pattern);
}
