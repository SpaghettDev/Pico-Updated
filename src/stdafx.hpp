#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN // no need for extra stuff in windows library
#define NOVIRTUALKEYCODES // we will supply our own key codes (key_codes.hpp)

// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

// Windows Header Files:
#include <windows.h>
#include <Mmsystem.h>


#include <atomic>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <regex>
#include <variant>
#include <source_location>


#include <psapi.h>
#include <MinHook.h>
#include <nlohmann/json.hpp>
#include <timeapi.h>
#include <time.h>

// Additional Header Files:
#include "key_codes.hpp"
#include "key_names.hpp"
#include "log.hpp"
#include "enums.hpp"
#include "input_hook.hpp"
#include "natives.hpp"
#include "hooking.hpp"
#include "script_global.hpp"
#include "structs.hpp"
#include "json_service.hpp"

#include <locale>
#include <codecvt>
#include <stdio.h>

using namespace std::chrono_literals;

namespace pico
{
	inline std::atomic_bool g_running{ false };
	inline HANDLE g_mainthread;
	inline DWORD g_mainthread_id;
	inline HMODULE g_hmodule;
	inline HWND g_hwnd;
	inline WNDPROC g_og_wndproc;

	inline InputHook g_inputhook;
	inline InputHook::custom_input_type g_custom_input;
	inline JsonService g_json;
}
