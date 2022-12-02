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
#include <Psapi.h>
#include <MinHook.h>
#include <timeapi.h>
#include <time.h>

// Additional Header Files:
#include "Log.h"
#include "SignatureScanner.h"
#include "OffsetHandler.h"
#include "Types.h"
#include "enums.h"
#include "CrossMapping.h"
#include "NativeInvoker.h"
#include "NativeCaller.h"
#include "Natives.h"
#include "Hooking.h"
#include "Types.h"
#include "../gta/net_game_event.hpp"
#include "../vendor/GTAV-Classes/network/CNetGamePlayer.hpp" // there must be a better way lol
#include "../gta/vector.hpp"

// Menu Files:
#include "MenuClass.h"
#include "Script.h"

#include <locale>
#include <codecvt>
#include <stdio.h>

extern std::atomic_bool g_Running;
extern constexpr const char* MenuName = "Pico Updated"; // Make sure the string can be used to create a file!
