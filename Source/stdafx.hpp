#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN         

// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

// Windows Header Files:
#include <windows.h>
#include <Mmsystem.h>


#include <atomic>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <regex>


#include <psapi.h>
#include <MinHook.h>
#include <timeapi.h>
#include <time.h>

// Additional Header Files:
#include "log.hpp"
#include "signature_scanner.hpp"
#include "offset_handler.hpp"
#include "types.hpp"
#include "enums.hpp"
#include "crossmapping.hpp"
#include "native_invoker.hpp"
#include "native_caller.hpp"
#include "natives.hpp"
#include "hooking.hpp"
#include "types.hpp"
#include "input_hook.hpp"

// Menu Files:
#include "menu_class.hpp"
#include "script.hpp"

#include <locale>
#include <codecvt>
#include <stdio.h>

namespace pico
{
	inline std::atomic_bool g_running{ false };
	inline HANDLE g_mainthread;
	inline DWORD g_mainthread_id;
	inline HMODULE g_hmodule;
	inline HWND g_hwnd;
	inline WNDPROC g_og_wndproc;
}
