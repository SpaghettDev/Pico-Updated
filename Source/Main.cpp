#include "stdafx.h"

using namespace std::chrono_literals;

//DWORD WINAPI ControlThread(LPVOID lpParam)
//{
//	Hooking::Start(reinterpret_cast<HMODULE>(lpParam));
//
//	while (pico::g_Running)
//	{
//		if (GetAsyncKeyState(VK_END)) 
//			g_Running = false;
//		std::this_thread::sleep_for(10ms);
//		std::this_thread::yield();
//	}
//	
//	Hooking::Cleanup();
//}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, PVOID)
{
	using namespace pico;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
		DisableThreadLibraryCalls(g_hModule);

		g_MainThread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindowA("grcWindow", nullptr))
				std::this_thread::sleep_for(100ms);

			try
			{
				Log::Msg("Pico Menu Initializing");
				Hooking::Start(g_hModule);
				Log::Msg("Pico Menu Initialized");

				pico::g_Running = true;
				while (pico::g_Running)
					std::this_thread::sleep_for(500ms);

				Hooking::Cleanup(g_hModule);
			}
			catch (std::exception const& ex)
			{
				Log::Msg(ex.what());
			}
		}, /*g_hModule*/ nullptr, 0, &g_MainThreadID);
		break;
	}
	return TRUE;
}


