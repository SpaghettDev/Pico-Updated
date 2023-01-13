#include "stdafx.hpp"
#include "input_hook.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, PVOID)
{
	using namespace std::chrono_literals;
	using namespace pico;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hmodule = hModule;
		DisableThreadLibraryCalls(g_hmodule);

		g_mainthread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindowA("grcWindow", nullptr))
				std::this_thread::sleep_for(100ms);

			try
			{
				Log::init();
				Hooking::init();
				InputHook::init();
				LOG_MSG("Pico Menu Initialized");

				g_running = true;
				while (g_running)
					std::this_thread::sleep_for(500ms);

				InputHook::cleanup();
				Hooking::cleanup();
			}
			catch (std::exception const& ex)
			{
				LOG_ERR(ex.what());
			}
		}, nullptr, 0, &g_mainthread_id);
		break;
	}
	return TRUE;
}


