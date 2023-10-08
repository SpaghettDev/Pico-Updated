#pragma once

enum LogLevel
{
	MESSAGE,
	WARNING,
	DEBUG,
#undef ERROR
	ERROR,
	FATAL
};

enum LogColor
{
	RESET,
	WHITE = 97,
	CYAN = 36,
	MAGENTA = 35,
	BLUE = 34,
	GREEN = 32,
	YELLOW = 33,
	RED = 31,
	BLACK = 30
};

class LogCapture
{
private:
	std::ostringstream m_stream;

	LogLevel m_last_log_level;
	std::source_location m_last_source_location;

public:
	static std::string pretext(LogLevel, std::source_location = std::source_location::current());

	template<typename T>
	std::ostream& operator<<(const T& t)
	{
		m_stream << t;

		return m_stream;
	}

	LogCapture(const LogLevel level, std::source_location location = std::source_location::current()) :
		m_last_log_level(level), m_last_source_location(location)
	{};
	~LogCapture();
};

class Logger
{
private:
	inline static DWORD m_original_console_mode;
	inline static HANDLE m_console_handle;

public:
	inline static std::filesystem::path m_log_file_path = std::filesystem::path(std::getenv("appdata")) / "Pico";

	static void init();
	static void cleanup();

	// static LogCapture log(const LogLevel level, std::source_location location = std::source_location::current());
};

namespace
{
	LogCapture LOG(const LogLevel level, std::source_location location = std::source_location::current())
	{
		return { level, std::move(location) };
	}
}
