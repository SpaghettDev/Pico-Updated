#pragma once

class netEventMgr;
class datBitBuffer;
class CNetGamePlayer;

using GetNumberOfEvents = std::int32_t(std::int32_t eventGroup);
using GetLabelText = const char* (void* unk, const char* label);
using ReceivedEvent = void(
	netEventMgr* event_manager,
	CNetGamePlayer* source_player,
	CNetGamePlayer* target_player,
	uint16_t event_id,
	int event_index,
	int event_handled_bitset,
	int buffer_size,
	datBitBuffer* buffer
);
using ScriptedGameEvent = bool(__int64 NetEventStruct, __int64 CNetGamePlayer);
using SendEventAcknowledge = void(netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);

// Bitbuffer functions
using ReadBitbufferDWORD = bool(datBitBuffer* buffer, PVOID read, int bits);
using ReadBitbufferString = bool(datBitBuffer* buffer, char* read, int bits);
using ReadBitbufferBool = bool(datBitBuffer* buffer, bool* read, int bits);
using ReadBitbufferArray = bool(datBitBuffer* buffer, PVOID read, int bits, int unk);
using WriteBitbufferQWORD = bool(datBitBuffer* buffer, uint64_t val, int bits);
using WriteBitbufferDWORD = bool(datBitBuffer* buffer, uint32_t val, int bits);
using WriteBitbufferInt64 = bool(datBitBuffer* buffer, int64_t val, int bits);
using WriteBitbufferInt32 = bool(datBitBuffer* buffer, int32_t val, int bits);
using WriteBitbufferBool = bool(datBitBuffer* buffer, bool val, int bits);
using WriteBitbufferArray = bool(datBitBuffer* buffer, void* val, int bits, int unk);


class Hooking
{
private:
	static bool initialize_hooks();
	static void find_patterns();

public:
	static std::vector<LPVOID> m_Hooks;

	static eGameState* m_GameState;
	static GetNumberOfEvents* m_GetNumberOfEvents;
	static GetLabelText* m_GetLabelText;
	static ReceivedEvent* m_ReceivedEvent;
	static ScriptedGameEvent* m_ScriptedGameEvent;
	static uint64_t* m_FrameCount;
	static std::uint64_t** m_WorldPointer;
	static std::uint64_t** m_GlobalBase;
	static PVOID m_ModelSpawnBypass;
	static void* m_NativeSpoofer;
	static bool* m_IsSessionStarted;
	static SendEventAcknowledge* m_SendEventAcknowledge;

	static ReadBitbufferDWORD* m_ReadBitbufferDWORD;
	static ReadBitbufferArray* m_ReadBitbufferArray;
	static ReadBitbufferString* m_ReadBitbufferString;
	static ReadBitbufferBool* m_ReadBitbufferBoolean;
	static WriteBitbufferDWORD* m_WriteBitbufferDWORD;
	static WriteBitbufferQWORD* m_WriteBitbufferQWORD;
	static WriteBitbufferInt64* m_WriteBitbufferInt64;
	static WriteBitbufferInt32* m_WriteBitbufferInt32;
	static WriteBitbufferBool* m_WriteBitbufferBoolean;
	static WriteBitbufferArray* m_WriteBitbufferArray;

	static void init(HMODULE hmoduleDLL);
	static void __declspec(noreturn) cleanup(HMODULE hModule);
	static void on_tick_init();
	static bool hook_natives();

	// Native function handler type
	typedef void(__cdecl * NativeHandler)(scrNativeCallContext* context);
	struct NativeRegistrationNew
	{
		uint64_t nextRegistration1;
		uint64_t nextRegistration2;
		Hooking::NativeHandler handlers[7];
		uint32_t numEntries1;
		uint32_t numEntries2;
		uint64_t hashes;

		inline NativeRegistrationNew* getNextRegistration()
		{
			uintptr_t result;
			auto v5 = reinterpret_cast<uintptr_t>(&nextRegistration1);
			auto v12 = 2i64;
			auto v13 = v5 ^ nextRegistration2;
			auto v14 = reinterpret_cast<char*>(&result) - v5;
			do
			{
				*reinterpret_cast<DWORD*>(&v14[v5]) = static_cast<DWORD>(v13 ^ *reinterpret_cast<DWORD*>(v5));
				v5 += 4i64;
				--v12;
			} while (v12);

			return reinterpret_cast<NativeRegistrationNew*>(result);
		}

		inline uint32_t getNumEntries()
		{
			return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&numEntries1) ^ numEntries1 ^ numEntries2);
		}

		inline uint64_t getHash(uint32_t index)
		{

			auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&nextRegistration1) + 0x54;
			auto v8 = 2i64;
			uint64_t nResult;
			auto v11 = reinterpret_cast<char*>(&nResult) - naddr;
			auto v10 = naddr ^ *reinterpret_cast<DWORD*>(naddr + 8);
			do
			{
				*reinterpret_cast<DWORD*>(&v11[naddr]) = static_cast<DWORD>(v10 ^ *reinterpret_cast<DWORD*>(naddr));
				naddr += 4i64;
				--v8;
			} while (v8);

			return nResult;
		}
	};
	static NativeHandler get_native_handler(uint64_t origHash);
};

extern Hooking g_hooking;

void WAIT(DWORD ms);

struct MinHookKeepalive
{
	MinHookKeepalive();
	~MinHookKeepalive();
};

extern MinHookKeepalive g_minhook_keepalive;

#include "net_game_event.hpp" // I hate this but bitBuffer class needs g_hooking to function
