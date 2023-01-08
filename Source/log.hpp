#pragma once

enum LogLevel
{
	MESSAGE,
	DEBUG,
#undef ERROR
	ERROR,
	FATAL
};

class Log
{
public:
	static char* g_log_file_path;
	static void log(LogLevel type, const char* file_name, int line, const char* fmt, ...);
	static void init(HMODULE hModule);
};


#define LOG_MSG(msg, ...) Log::log(LogLevel::MESSAGE, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) Log::log(LogLevel::DEBUG, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_ERR(msg, ...) Log::log(LogLevel::ERROR, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define LOG_FATAL(msg, ...)  Log::log(LogLevel::FATAL, __FILE__, __LINE__, msg, ##__VA_ARGS__)
