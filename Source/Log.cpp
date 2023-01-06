#include "stdafx.h"
#include <time.h>
#include <cstdio>

char* Log::g_log_file_path;
static char g_debug_log_file[MAX_PATH];

#define CHARS_FOR_BUFF 4096
#define CHARS_FOR_PARAMS 3500

namespace
{
	std::map<LogLevel, const char*> level_to_str = {
		{ LogLevel::MESSAGE, "MESSAGE" },
		{ LogLevel::DEBUG, "DEBUG" },
		{ LogLevel::ERROR_, "ERROR" },
		{ LogLevel::FATAL, "FATAL" }
	};
}


void Log::init(HMODULE hModule)
{
	if (AllocConsole())
	{
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitleW(L"Pico");
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
	}

	char log_buffer[CHARS_FOR_BUFF];
	char timestamp[50];
	struct tm current_tm;
	time_t current_time = time(NULL);

	localtime_s(&current_tm, &current_time);
	sprintf_s(timestamp, "[%02d:%02d:%02d] %%s\n", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
	sprintf_s(log_buffer, timestamp, "Initialize: Pico Base");

	{
		std::string temp = std::format(R"({}\Pico\)", std::getenv("appdata"));
		g_log_file_path = temp.data();
	}

	std::filesystem::create_directory(g_log_file_path);

	strcpy_s(g_debug_log_file, g_log_file_path);
	strcat_s(g_debug_log_file, "Pico.log");

	std::ofstream file_in(g_debug_log_file);
	file_in << ""; // clear file
	file_in << log_buffer;
	file_in.close();

	LOG_MSG(R"(
_______
|  __ (_)
| |__) |  ___ ___
|  ___/ |/ __/ _ \
| |   | | (_| (_) |
|_|   |_|\___\___/)");
}

void Log::log(LogLevel type, const char* file_name, int line, const char* fmt, ...)
{
	va_list va_alist;
	char chLogBuff[CHARS_FOR_BUFF];
	char chParameters[CHARS_FOR_PARAMS];
	char szTimestamp[50];
	struct tm current_tm;
	time_t current_time = time(NULL);
	std::string actual_file_name = file_name;

	std::smatch sm;

	if (std::regex_search(actual_file_name, sm, std::regex(R"(\\(\w+)\.(cpp|h|hpp))")))
	{
		actual_file_name = sm[0];
		actual_file_name = actual_file_name.erase(0, 1);
	}
	else
		actual_file_name = "uknown";

	localtime_s(&current_tm, &current_time);
	sprintf_s(szTimestamp, "[%02d:%02d:%02d | %s:%i | %s] %%s\n",
		current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec, actual_file_name.c_str(), line, level_to_str[type]
	);

	va_start(va_alist, fmt);
	vsnprintf_s(chParameters, sizeof(chParameters), fmt, va_alist);
	va_end(va_alist);
	sprintf_s(chLogBuff, szTimestamp, chParameters);

	OutputDebugStringA(chLogBuff);

	std::ofstream file(g_debug_log_file, std::ios::app);
	file << chLogBuff;
	file.close();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	char buffer[4096]{};
	va_list args{};

	va_start(args, fmt);
	vsnprintf_s(buffer, sizeof(buffer), fmt, args);
	printf(buffer);
	printf("\n");
	va_end(args);

	if (type == LogLevel::FATAL)
		pico::g_running = false;
}
