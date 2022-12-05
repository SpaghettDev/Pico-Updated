#include "../headers/stdafx.h"

std::atomic_bool g_Running = true;

DWORD WINAPI ControlThread(LPVOID lpParam)
{
	Hooking::Start((HMODULE)lpParam);

	while (g_Running)
	{
		if (GetAsyncKeyState(VK_END))
			g_Running = false;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::this_thread::yield();
	}

	Hooking::Cleanup();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ControlThread, hModule, NULL, NULL);
		break;
	}
	return TRUE;
}
