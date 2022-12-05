#pragma once
#include "../headers/stdafx.h"

HMODULE _hmoduleDLL;
HANDLE MainFiber;
DWORD WakeTime;

std::vector<LPVOID> Hooking::m_Hooks;
eGameState* Hooking::m_GameState;
GetNumberOfEvents* Hooking::m_GetNumberOfEvents;
GetLabelText* Hooking::m_GetLabelText;
ScriptedGameEvent* Hooking::m_ScriptedGameEvent;
ScriptedGameEvent* Hooking::m_ReceivedEvent;
uint64_t* Hooking::m_FrameCount;
std::uint64_t** Hooking::m_WorldPointer;
std::uint64_t** Hooking::m_GlobalBase;
PVOID Hooking::m_ModelSpawnBypass;
PVOID Hooking::m_WorldModelSpawnBypass;
GetPlayerName Hooking::m_GetPlayerName;
void* Hooking::m_NativeSpoofer;
static Hooking::NativeRegistrationNew** m_NativeRegistrationTable;
static std::unordered_map < uint64_t, Hooking::NativeHandler > m_NativeHandlerCache;

/* Start Hooking */
void Hooking::Start(HMODULE hmoduleDLL) 
{
	_hmoduleDLL = hmoduleDLL;
	Log::Init(hmoduleDLL);
	FindPatterns();
	while (static_cast<int > (*g_Hooking.m_GameState) != 0)
	Sleep(200);
	CrossMapping::initNativeMap();
	if (!InitializeHooks())
	Cleanup();
}

BOOL Hooking::InitializeHooks() 
{
	if (!HookNatives()) 
	{
		Log::Error("Hooking failed!");
		return FALSE;
	}

	return TRUE;
}

GetNumberOfEvents* m_OriginalGetNumberOfEvents = nullptr;
std::int32_t GetNumberOfEventsHook(std::int32_t eventGroup) 
{
	if (g_Running) 
	{
		static uint64_t LastFrame = 0;
		uint64_t CurrentFrame = *Hooking::m_FrameCount;
		if (LastFrame != CurrentFrame) 
		{
			LastFrame = CurrentFrame;
			Hooking::onTickInit();
		}
	}
	else if (IsThreadAFiber()) 
		ConvertFiberToThread();

	return m_OriginalGetNumberOfEvents(eventGroup);
}

GetLabelText* m_OriginalGetLabelText = nullptr;
const char* GetLabelTextHook(const char* labelName)
{
	/*if (!strcmp(label, "HUD_JOINING"))
		return "Isn't Pico Base the fucking best?";
	if (!strcmp(label, "HUD_TRANSP"))
		return "Isn't Pico Base the fucking best?";*/

	return m_OriginalGetLabelText(labelName);
}

ScriptedGameEvent* m_OriginalScriptedGameEvent = nullptr;
bool ScriptedGameEventHook(__int64 NetEventStruct, __int64 CNetGamePlayer)
{
	auto Arguments = reinterpret_cast<std::int64_t*>(NetEventStruct + 0x70);
	auto Receiver = *reinterpret_cast<std::int8_t*>(CNetGamePlayer + 0x2D);
	auto Sender = *reinterpret_cast<std::int8_t*>(CNetGamePlayer + 0x35);
	const auto EventHash = Arguments[0];

	if (Receiver == PLAYER::PLAYER_ID())
	{
		switch (EventHash)
		{
		case eRemoteEvent::SendToCayoPerico:
			Log::Msg("Blocked 'Send to Island' Event from User %s", g_Hooking.m_GetPlayerName(Sender));
			return true;
			break;
		case eRemoteEvent::SendToLocation:
			Log::Msg("Blocked 'Send to Location' Event from User %s", g_Hooking.m_GetPlayerName(Sender));
			return true;
			break;
		case eRemoteEvent::CeoBan:
			Log::Msg("Blocked 'Ceo Ban' Event from User %s", g_Hooking.m_GetPlayerName(Sender));
			return true;
			break;
		case eRemoteEvent::CeoKick:
			Log::Msg("Blocked 'Ceo Kick' Event from User %s", g_Hooking.m_GetPlayerName(Sender));
			return true;
			break;
		}
	}

	return m_OriginalScriptedGameEvent(NetEventStruct, CNetGamePlayer);
}

bool Hooking::HookNatives()
{
	MH_STATUS Status = MH_CreateHook(Hooking::m_GetNumberOfEvents, GetNumberOfEventsHook, (void**)&m_OriginalGetNumberOfEvents);
	if ((Status != MH_OK && Status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::m_GetNumberOfEvents) != MH_OK)
		return false;
	Hooking::m_Hooks.push_back(Hooking::m_GetNumberOfEvents);
	Log::Msg("Hooked: GNOE");

	Status = MH_CreateHook(Hooking::m_GetLabelText, GetLabelTextHook, (void**)&m_OriginalGetLabelText);
	if ((Status != MH_OK && Status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::m_GetLabelText) != MH_OK)
		return false;
	Hooking::m_Hooks.push_back(Hooking::m_GetLabelText);
	Log::Msg("Hooked: GLT");

	Status = MH_CreateHook(Hooking::m_ScriptedGameEvent, ScriptedGameEventHook, (void**)&m_OriginalScriptedGameEvent);
	if ((Status != MH_OK && Status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::m_ScriptedGameEvent) != MH_OK)
		return false;
	Hooking::m_Hooks.push_back(Hooking::m_ScriptedGameEvent);
	Log::Msg("Hooked: SGE");

	return true;
}

void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();
	}
	catch (...)
	{
		Log::Fatal("Failed ScriptFiber");
	}
}

void Hooking::onTickInit()
{
	if (MainFiber == nullptr)
		MainFiber = IsThreadAFiber() ? GetCurrentFiber(): ConvertThreadToFiber(nullptr);

	if (timeGetTime() < WakeTime)
		return;

	static HANDLE ScriptFiber;
	if (ScriptFiber)
		SwitchToFiber(ScriptFiber);
	else
		ScriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
}

void Hooking::FindPatterns()
{
	Hooking::m_GameState = "83 3D ? ? ? ? ? 75 17 8B 43 20 25"_Scan.add(2).rip().as<decltype(Hooking::m_GameState)>(); Log::Msg("Found: GS");

	Hooking::m_GetNumberOfEvents = "48 83 EC 28 33 D2 85 C9"_Scan.as<decltype(Hooking::m_GetNumberOfEvents)>(); Log::Msg("Found: GNOE");

	Hooking::m_GetLabelText = "75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9"_Scan.sub(19).as<decltype(Hooking::m_GetLabelText)>(); Log::Msg("Found: GLT");

	// Hooking::m_ReceivedEvent = "66 41 83 F9 ? 0F 83"_Scan.as<decltype(Hooking::m_ReceivedEvent)>(); Log::Msg("Found: RE"); // TODO: Change to ReceivedEvent and not ScriptedGameEvent
	Hooking::m_ScriptedGameEvent = "40 53 48 81 EC ? ? ? ? 44 8B 81"_Scan.as<decltype(Hooking::m_ScriptedGameEvent)>(); Log::Msg("Found: SGE");

	// 0x0000000050597EE2
	Hooking::m_FrameCount = "F3 0F 10 0D ? ? ? ? 44 89 6B 08"_Scan.add(4).rip(4).sub(8).as<decltype(Hooking::m_FrameCount)>(); Log::Msg("Found: FC"); // TODO: needs to be found

	Hooking::m_WorldPointer = "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81"_Scan.add(3).rip().as<decltype(Hooking::m_WorldPointer)>(); Log::Msg("Found: WP");

	Hooking::m_GlobalBase = "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D"_Scan.add(3).rip().as<decltype(Hooking::m_GlobalBase)>(); Log::Msg("Found: GB");

	Hooking::m_ModelSpawnBypass = "48 8B C8 FF 52 30 84 C0 74 05 48"_Scan.add(8).as<decltype(Hooking::m_ModelSpawnBypass)>(); Log::Msg("Found: MSB");
	Hooking::m_WorldModelSpawnBypass = "48 8B C8 FF 52 30 84 C0 74 05 48"_Scan.as<decltype(Hooking::m_WorldModelSpawnBypass)>(); Log::Msg("Found: WMSB");

	// 0x6D0DE6A7B5DA71F8
	Hooking::m_GetPlayerName = "40 53 48 83 EC 20 80 3D ? ? ? ? ? 8B D9 74 22"_Scan.as<decltype(Hooking::m_GetPlayerName)>(); Log::Msg("Found: GPN");

	Hooking::m_NativeSpoofer = "FF E3"_Scan.add(0).as<decltype(Hooking::m_NativeSpoofer)>(); Log::Msg("Found: NS");

	scrNativeCallContext::SetVectorResults = "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA"_Scan.as<decltype(scrNativeCallContext::SetVectorResults)>(); Log::Msg("Found: SVR");

	m_NativeRegistrationTable = "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A"_Scan.add(3).rip().as<decltype(m_NativeRegistrationTable)>(); Log::Msg("Found: NRT");
}

static Hooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t NewHash = CrossMapping::MapNative(origHash);
	if (NewHash == 0)
		return nullptr;

	Hooking::NativeRegistrationNew* RegistrationTable = m_NativeRegistrationTable[NewHash & 0xFF];

	for (; RegistrationTable; RegistrationTable = RegistrationTable->getNextRegistration())
	{
		for (uint32_t i = 0; i < RegistrationTable->getNumEntries(); i++)
		{
			if (NewHash == RegistrationTable->getHash(i))
				return RegistrationTable->handlers[i];
		}
	}
	return nullptr;
}

Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
{
	auto& NativeHandler = m_NativeHandlerCache[origHash];

	if (NativeHandler == nullptr)
		NativeHandler = _Handler(origHash);

	return NativeHandler;
}

void WAIT(DWORD ms)
{
	WakeTime = timeGetTime() + ms;
	SwitchToFiber(MainFiber);
}

void __declspec(noreturn) Hooking::Cleanup()
{
	Log::Msg("Cleaning up hooks");
	for (auto func: m_Hooks)
	{
		MH_STATUS Status;
		if ((Status = MH_DisableHook(func)) == MH_OK)
			Log::Msg("Successfully disabled hook %p", func);
		else
			Log::Msg("Failed to disable hook %p (%s)", func, MH_StatusToString(Status));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	for (auto func: m_Hooks)
	{
		MH_STATUS Status;
		if ((Status = MH_RemoveHook(func)) == MH_OK)
			Log::Msg("Successfully removed hook %p", func);
		else
			Log::Msg("Failed to remove hook %p (%s)", func, MH_StatusToString(Status));
	}

	fclose(stdout);
	FreeConsole();
	FreeLibraryAndExitThread(static_cast<HMODULE > (_hmoduleDLL), 0);
}

MinHookKeepalive::MinHookKeepalive() 
{
	MH_Initialize();
}

MinHookKeepalive::~MinHookKeepalive() 
{
	MH_Uninitialize();
}

MinHookKeepalive g_MinHookKeepalive;