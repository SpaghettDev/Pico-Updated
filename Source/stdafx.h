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
#include <algorithm>
#include <functional>
#include <psapi.h>
#include <MinHook.h>
#include <timeapi.h>
#include <time.h>
#include <filesystem>
#include <regex>

// Additional Header Files:
#include "log.h"
#include "signature_scanner.h"
#include "offset_handler.h"
#include "types.h"
#include "enums.h"
#include "crossmapping.h"
#include "native_invoker.h"
#include "native_caller.h"
#include "natives.h"
#include "hooking.h"
#include "types.h"
#include "hotkeys.h"

// Menu Files:
#include "menu_class.h"
#include "script.h"

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
