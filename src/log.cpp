#include "stdafx.hpp"
#include <iostream>

namespace
{
#define ADD_COLOR(color) "\x1b[" + std::to_string(static_cast<int>(color)) + "m"

	std::map<LogLevel, const char*> level_to_str
	{
		{ LogLevel::MESSAGE, "MESSAGE" },
		{ LogLevel::WARNING, "WARNING" },
		{ LogLevel::DEBUG, "DEBUG" },
		{ LogLevel::ERROR, "ERROR" },
		{ LogLevel::FATAL, "FATAL" }
	};

	std::map<LogLevel, LogColor> level_to_color
	{
		{ LogLevel::MESSAGE, LogColor::CYAN },
		{ LogLevel::WARNING, LogColor::YELLOW },
		{ LogLevel::DEBUG, LogColor::BLUE },
		{ LogLevel::ERROR, LogColor::RED },
		{ LogLevel::FATAL, LogColor::RED }
	};

	// move to std::chrono::*
	tm get_time()
	{
		tm current_tm;
		time_t current_time = time(NULL);

		localtime_s(&current_tm, &current_time);

		return current_tm;
	}
}


#pragma warning(disable: 4996) // getenv is apparently unsafe
void Logger::init()
{
	if (AllocConsole())
	{
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitleW(L"Pico");
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);

		if (m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE); m_console_handle != nullptr)
		{
			DWORD console_mode;
			GetConsoleMode(m_console_handle, &console_mode);
			m_original_console_mode = console_mode;

			// terminal like behaviour enable full color support
			console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
			// prevent clicking in terminal from suspending our main thread
			console_mode &= ~(ENABLE_QUICK_EDIT_MODE);

			SetConsoleMode(m_console_handle, console_mode);
		}
	}

	std::string init_text = std::format("{}Initializing: Pico\n", LogCapture::pretext(LogLevel::MESSAGE));

	std::cout << init_text << "\n";

	std::filesystem::create_directory(m_log_file_path);

	std::ofstream file_in(m_log_file_path / "Pico.log");
	// initialize the file by clearing it
	file_in << "";
	file_in << init_text;
	file_in.close();

	std::cout << R"(
_______
|  __ (_)
| |__) |  ___ ___
|  ___/ |/ __/ _ \
| |   | | (_| (_) |
|_|   |_|\___\___/)" << "\n";
}

void Logger::cleanup()
{
	if (m_original_console_mode)
		SetConsoleMode(m_console_handle, m_original_console_mode);

	fclose(stdout);
	FreeConsole();
}

LogCapture::~LogCapture()
{
	m_stream << "\n";

	std::string text = pretext(m_last_log_level, m_last_source_location) + m_stream.str();

	std::ofstream file_in(Logger::m_log_file_path / "Pico.log", std::ios::app);
	file_in << text;
	file_in.close();

	std::cout << ADD_COLOR(level_to_color[m_last_log_level]) << text;
}

std::string LogCapture::pretext(LogLevel level, std::source_location location)
{
	tm current_tm = get_time();

	return std::format("[{:02d}:{:02d}:{:02d} | {}:{} | {}] ",
		current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec,
		std::filesystem::path(location.file_name()).filename().string(), location.line(), level_to_str[level]
	);
}
