#pragma once

using GetNumberOfEvents = std::int32_t(std::int32_t eventGroup);
using GetLabelText = const char* (const char* label);
using ScriptedGameEvent = bool(__int64 NetEventStruct, __int64 CNetGamePlayer);
using GetPlayerName = const char* (_fastcall*)(Player player);

class Hooking
{
	private:
	static BOOL InitializeHooks();
	static void FindPatterns();

	public:
	static std::vector<LPVOID> m_Hooks;
	static eGameState* m_GameState;
	static GetNumberOfEvents* m_GetNumberOfEvents;
	static GetLabelText* m_GetLabelText;
	static ScriptedGameEvent* m_ScriptedGameEvent;
	static ScriptedGameEvent* m_ReceivedEvent;
	static uint64_t* m_FrameCount;
	static std::uint64_t** m_WorldPointer;
	static std::uint64_t** m_GlobalBase;
	static PVOID m_ModelSpawnBypass;
	static PVOID m_WorldModelSpawnBypass;
	static GetPlayerName m_GetPlayerName;
	static void* m_NativeSpoofer;

	static void Start(HMODULE hmoduleDLL);
	static void __declspec(noreturn) Cleanup();
	static void onTickInit();
	static bool HookNatives();

	// Native function handler type
	typedef void(__cdecl* NativeHandler)(scrNativeCallContext* context);
	struct NativeRegistrationNew
	{
		uint64_t nextRegistration1;
		uint64_t nextRegistration2;
		Hooking::NativeHandler handlers[7];
		uint32_t numEntries1;
		uint32_t numEntries2;
		uint64_t hashes;

		inline NativeRegistrationNew* getNextRegistration() {
			uintptr_t result;
			auto v5 = reinterpret_cast<uintptr_t > (&nextRegistration1);
			auto v12 = 2i64;
			auto v13 = v5 ^ nextRegistration2;
			auto v14 = (char*)&result - v5;
			do
			{
				*(DWORD*)&v14[v5] = (DWORD)(v13 ^ *(DWORD*)v5);
				v5 += 4i64;
				--v12;
			} while (v12);

			return reinterpret_cast<NativeRegistrationNew*>(result);
		}

		inline uint32_t getNumEntries() {
			return (uint32_t)(((uintptr_t)&numEntries1) ^ numEntries1 ^ numEntries2);
		}

		inline uint64_t getHash(uint32_t index) {

			auto naddr = 16 * index + reinterpret_cast<uintptr_t > (&nextRegistration1) + 0x54;
			auto v8 = 2i64;
			uint64_t nResult;
			auto v11 = (char*)&nResult - naddr;
			auto v10 = naddr ^ *(DWORD*)(naddr + 8);
			do
			{
				*(DWORD*)&v11[naddr] = (DWORD)(v10 ^ *(DWORD*)(naddr));
				naddr += 4i64;
				--v8;
			} while (v8);

			return nResult;
		}
	};
	static NativeHandler GetNativeHandler(uint64_t origHash);
};
extern Hooking g_Hooking;

void WAIT(DWORD ms);

struct MinHookKeepalive
{
	MinHookKeepalive();
	~MinHookKeepalive();
};

extern MinHookKeepalive g_MinHookKeepalive;