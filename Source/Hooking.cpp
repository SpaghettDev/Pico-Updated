#pragma once
#include "stdafx.hpp"

HANDLE MainFiber;
DWORD WakeTime;

std::vector<LPVOID> Hooking::m_Hooks;
eGameState* Hooking::m_GameState;
GetNumberOfEvents* Hooking::m_GetNumberOfEvents;
GetLabelText* Hooking::m_GetLabelText;
ReceivedEvent* Hooking::m_ReceivedEvent;
ScriptedGameEvent* Hooking::m_ScriptedGameEvent;
uint64_t* Hooking::m_FrameCount;
std::uint64_t** Hooking::m_WorldPointer;
std::uint64_t** Hooking::m_GlobalBase;
PVOID Hooking::m_ModelSpawnBypass;
void* Hooking::m_NativeSpoofer;
static Hooking::NativeRegistrationNew**	m_NativeRegistrationTable;
bool* Hooking::m_IsSessionStarted;
SendEventAcknowledge* Hooking::m_SendEventAcknowledge;
static std::unordered_map<uint64_t, Hooking::NativeHandler>	m_NativeHandlerCache;

ReadBitbufferDWORD* Hooking::m_ReadBitbufferDWORD;
ReadBitbufferArray* Hooking::m_ReadBitbufferArray;
ReadBitbufferString* Hooking::m_ReadBitbufferString;
ReadBitbufferBool* Hooking::m_ReadBitbufferBoolean;
WriteBitbufferDWORD* Hooking::m_WriteBitbufferDWORD;
WriteBitbufferQWORD* Hooking::m_WriteBitbufferQWORD;
WriteBitbufferInt64* Hooking::m_WriteBitbufferInt64;
WriteBitbufferInt32* Hooking::m_WriteBitbufferInt32;
WriteBitbufferBool* Hooking::m_WriteBitbufferBoolean;
WriteBitbufferArray* Hooking::m_WriteBitbufferArray;

using namespace std::chrono_literals;

/* Start Hooking */
void Hooking::init(HMODULE hmoduleDLL)
{
	find_patterns();
	while (*g_hooking.m_GameState != eGameState::Playing)
		Sleep(200);
	if (!initialize_hooks())
		cleanup(hmoduleDLL);
}

bool Hooking::initialize_hooks()
{
	if (!hook_natives())
	{
		LOG_ERR("Hooking failed!");
		return false;
	}

	return true;
}

#pragma region hooks
GetNumberOfEvents* m_OriginalGetNumberOfEvents = nullptr;
std::int32_t GetNumberOfEventsHook(std::int32_t eventGroup)
{
	if (pico::g_running)
	{
		static uint64_t LastFrame = 0;
		uint64_t CurrentFrame = *Hooking::m_FrameCount;
		if (LastFrame != CurrentFrame)
		{
			LastFrame = CurrentFrame;
			Hooking::on_tick_init();
		}
	}
	else if (IsThreadAFiber())
		ConvertFiberToThread();

	return m_OriginalGetNumberOfEvents(eventGroup);
}

GetLabelText* m_OriginalGetLabelText = nullptr;
const char* GetLabelTextHook(void* unk, const char* label)
{
	std::map<const char*, const char*> label_to_custom_text = {
		{ "HUD_JOINING", "Isn't Pico Base the fucking best?" },
		{ "HUD_TRANSP", "Isn't Pico Base the fucking best?" }
	};

	try
	{
		return label_to_custom_text.at(label);
	}
	catch (...)
	{
		return m_OriginalGetLabelText(unk, label);
	}
}

bool scan_scripted_game_event(CScriptedGameEvent* game_event, CNetGamePlayer* player)
{
	auto constexpr log_blocked_event = [](const char* event_name, const char* player_name) -> void {
		LOG_MSG("Blocked '%s' event from %s", event_name, player_name);
	};
	const auto args = game_event->m_args;

	const auto player_name = player->get_name();

	switch (static_cast<eRemoteEvent>(args[0]))
	{
	case eRemoteEvent::SendToCayoPerico:
		log_blocked_event("Send to Cayo Perico", player_name);

		return true;
		break;
	case eRemoteEvent::SendToLocation:
	{
		bool known_location = false;

		if (args[2] == 0 && args[3] == 0)
		{
			if (args[4] == 4 && args[5] == 0)
			{
				known_location = true;

				log_blocked_event("Send to Beach", player_name);
				return true;
			}
			else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
			{
				known_location = true;

				log_blocked_event("Send to Cayo Perico", player_name);
				return true;
			}
		}

		if (!known_location)
		{
			log_blocked_event("TSE Freeze", player_name);
			return true;
		}
		break;
	}

	return false;
	}
}

ReceivedEvent* m_OriginalReceivedEvent = nullptr;
void ReceivedEventHook( // skidded from YimMenu, because this Network stuff scares me
	netEventMgr* event_manager,
	CNetGamePlayer* source_player,
	CNetGamePlayer* target_player,
	uint16_t event_id,
	int event_index,
	int event_handled_bitset,
	int buffer_size,
	datBitBuffer* buffer
) {
	if (event_id > 91u)
	{
		g_hooking.m_SendEventAcknowledge(event_manager, source_player, target_player, event_index, event_handled_bitset);
		return;
	}

	const auto event_name = *reinterpret_cast<char**>(reinterpret_cast<DWORD64>(event_manager) + 8i64 * event_id + 243376);
	if (event_name == nullptr || source_player == nullptr || source_player->m_player_id < 0 || source_player->m_player_id >= 32)
	{
		g_hooking.m_SendEventAcknowledge(event_manager, source_player, target_player, event_index, event_handled_bitset);
		return;
	}

	switch (static_cast<eNetworkEvents>(event_id))
	{
	case eNetworkEvents::SCRIPTED_GAME_EVENT:
		const auto scripted_game_event = std::make_unique<CScriptedGameEvent>();
		buffer->ReadDword(&scripted_game_event->m_args_size, 32);
		if (scripted_game_event->m_args_size - 1 <= 0x1AF)
			buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

		if (scan_scripted_game_event(scripted_game_event.get(), source_player))
		{
			g_hooking.m_SendEventAcknowledge(event_manager, source_player, target_player, event_index, event_handled_bitset);

			return;
		}
		buffer->Seek(0);
		break;
	}

	return m_OriginalReceivedEvent(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, buffer_size, buffer);
}

bool Hooking::hook_natives()
{
#define IS_HOOK_UNSUCCESSFULLY_INSTALLED(status, hook) ((status != MH_STATUS::MH_OK && status != MH_STATUS::MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::hook) != MH_STATUS::MH_OK)

	MH_STATUS status = MH_CreateHook(Hooking::m_GetNumberOfEvents, GetNumberOfEventsHook, reinterpret_cast<void**>(&m_OriginalGetNumberOfEvents));
	if (IS_HOOK_UNSUCCESSFULLY_INSTALLED(status, m_GetNumberOfEvents))
		return false;
	Hooking::m_Hooks.push_back(Hooking::m_GetNumberOfEvents);
	LOG_MSG("Hooked: GNOE");

	status = MH_CreateHook(Hooking::m_GetLabelText, GetLabelTextHook, reinterpret_cast<void**>(&m_OriginalGetLabelText));
	if (IS_HOOK_UNSUCCESSFULLY_INSTALLED(status, m_GetLabelText))
		return false;
	Hooking::m_Hooks.push_back(Hooking::m_GetLabelText);
	LOG_MSG("Hooked: GLT");

	status = MH_CreateHook(Hooking::m_ReceivedEvent, ReceivedEventHook, reinterpret_cast<void**>(&m_OriginalReceivedEvent));
	if (IS_HOOK_UNSUCCESSFULLY_INSTALLED(status, m_ReceivedEvent))
		return false;
	Hooking::m_Hooks.push_back(Hooking::m_ReceivedEvent);
	LOG_MSG("Hooked: RE");

	return true;
}
#pragma endregion

void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();
	}
	catch (...)
	{
		LOG_FATAL("Failed ScriptFiber");
	}
}

void Hooking::on_tick_init()
{
	if (MainFiber == nullptr)
		MainFiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);
	
	if (timeGetTime() < WakeTime)
		return;

	static HANDLE ScriptFiber;
	if (ScriptFiber)
		SwitchToFiber(ScriptFiber);
	else
		ScriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
}

void Hooking::find_patterns()
{
	using namespace SignatureScanner;

	m_GameState = "83 3D ? ? ? ? ? 75 17 8B 43 20 25"_Scan.add(2).rip().as<decltype(Hooking::m_GameState)>(); LOG_MSG("Found: GS");
	m_GetNumberOfEvents = "48 83 EC 28 33 D2 85"_Scan.as<decltype(Hooking::m_GetNumberOfEvents)>(); LOG_MSG("Found: GNOE");
	m_GetLabelText = "75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9"_Scan.sub(19).as<decltype(Hooking::m_GetLabelText)>(); LOG_MSG("Found: GLT");
	m_ReceivedEvent = "66 41 83 F9 ? 0F 83"_Scan.as<decltype(Hooking::m_ReceivedEvent)>(); LOG_MSG("Found: RE");
	m_FrameCount = "8B 15 ? ? ? ? 41 FF CF"_Scan.add(2).rip().add(4).as<decltype(Hooking::m_FrameCount)>(); LOG_MSG("Found: FC");
	m_WorldPointer = "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81"_Scan.add(3).rip().as<decltype(Hooking::m_WorldPointer)>(); LOG_MSG("Found: WP");
	m_GlobalBase = "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D"_Scan.add(3).rip().as<decltype(Hooking::m_GlobalBase)>(); LOG_MSG("Found: GB");
	m_ModelSpawnBypass = "48 85 C0 0F 84 ? ? ? ? 8B 48 50"_Scan.as<decltype(Hooking::m_ModelSpawnBypass)>(); LOG_MSG("Found: MSB");
	m_NativeSpoofer = "FF E3"_Scan.add(0).as<decltype(Hooking::m_NativeSpoofer)>(); LOG_MSG("Found: NS");
	scrNativeCallContext::SetVectorResults = "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA"_Scan.as<decltype(scrNativeCallContext::SetVectorResults)>(); LOG_MSG("Found: SVR");
	m_NativeRegistrationTable = "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A"_Scan.add(3).rip().as<decltype(m_NativeRegistrationTable)>(); LOG_MSG("Found: NRT");
	m_IsSessionStarted = "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE"_Scan.add(3).rip().as<decltype(Hooking::m_IsSessionStarted)>(); LOG_MSG("Found: ISS");
	m_SendEventAcknowledge = "48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 7A"_Scan.sub(5).as<decltype(Hooking::m_SendEventAcknowledge)>(); LOG_MSG("Found: SEA");

	// Bitbuffer patterns
	m_ReadBitbufferDWORD = "48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A"_Scan.sub(5).as<decltype(Hooking::m_ReadBitbufferDWORD)>(); LOG_MSG("Found: RBBDWORD");
	m_ReadBitbufferArray = "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C"_Scan.as<decltype(Hooking::m_ReadBitbufferArray)>(); LOG_MSG("Found: RBBA");
	m_ReadBitbufferString = "E8 ? ? ? ? 48 8D 4F 3C"_Scan.add(1).rip().as<decltype(Hooking::m_ReadBitbufferString)>(); LOG_MSG("Found: RBBS");
	m_ReadBitbufferBoolean = "E8 ? ? ? ? 84 C0 74 2D 48 8D 57 20"_Scan.add(1).rip().as<decltype(Hooking::m_ReadBitbufferBoolean)>(); LOG_MSG("Found: RBBB");
	m_WriteBitbufferDWORD = "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 8B EA BF 01"_Scan.as<decltype(Hooking::m_WriteBitbufferDWORD)>(); LOG_MSG("Found: WBBDWORD");
	m_WriteBitbufferQWORD = "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20"_Scan.as<decltype(Hooking::m_WriteBitbufferQWORD)>(); LOG_MSG("Found: WBBQWORD");
	m_WriteBitbufferInt64 = "E8 ? ? ? ? 8A 53 39 48 8B CF"_Scan.add(1).rip().as<decltype(Hooking::m_WriteBitbufferInt64)>(); LOG_MSG("Found: WBBI64");
	m_WriteBitbufferInt32 = "E8 ? ? ? ? 8A 53 74"_Scan.add(1).rip().as<decltype(Hooking::m_WriteBitbufferInt32)>(); LOG_MSG("Found: WBBI32");
	m_WriteBitbufferBoolean = "E8 ? ? ? ? 8A 57 39"_Scan.add(1).rip().as<decltype(Hooking::m_WriteBitbufferBoolean)>(); LOG_MSG("Found: WBBB");
	m_WriteBitbufferArray = "E8 ? ? ? ? 01 7E 08"_Scan.add(1).rip().as<decltype(Hooking::m_WriteBitbufferArray)>(); LOG_MSG("Found: WBBA");

	pico::g_hwnd = FindWindowW(L"grcWindow", nullptr);
}

static Hooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t NewHash = CrossMapping::map_native(origHash);
	if (NewHash == 0)
		return nullptr;

	Hooking::NativeRegistrationNew* RegistrationTable = m_NativeRegistrationTable[NewHash & 0xFF];

	for (; RegistrationTable; RegistrationTable = RegistrationTable->getNextRegistration())
		for (uint32_t i = 0; i < RegistrationTable->getNumEntries(); i++)
			if (NewHash == RegistrationTable->getHash(i))
				return RegistrationTable->handlers[i];

	return nullptr;
}

Hooking::NativeHandler Hooking::get_native_handler(uint64_t origHash)
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

void __declspec(noreturn) Hooking::cleanup(HMODULE hModule)
{
	LOG_MSG("Cleaning up hooks");
	for (auto func : m_Hooks)
	{
		MH_STATUS Status;
		if ((Status = MH_DisableHook(func)) == MH_OK)
			LOG_MSG("Successfully disabled hook %p", func);
		else
			LOG_MSG("Failed to disable hook %p (%s)", func, MH_StatusToString(Status));
	}

	std::this_thread::sleep_for(500ms);

	for (auto func : m_Hooks)
	{
		MH_STATUS Status;
		if ((Status = MH_RemoveHook(func)) == MH_OK)
			LOG_MSG("Successfully removed hook %p", func);
		else
			LOG_MSG("Failed to remove hook %p (%s)", func, MH_StatusToString(Status));
	}

	fclose(stdout);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

MinHookKeepalive::MinHookKeepalive()
{
	MH_Initialize();
}

MinHookKeepalive::~MinHookKeepalive()
{
	MH_Uninitialize();
}

MinHookKeepalive g_minhook_keepalive;
