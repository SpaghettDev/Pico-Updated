#pragma once

class Log
{
public:
	static void Init(HMODULE hModule);
	static void Msg(const char* fmt, ...);
	static void Error(const char* fmt, ...);
	static void Fatal(const char* fmt, ...);
};