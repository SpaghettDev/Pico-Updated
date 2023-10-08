#include "stdafx.hpp"
#include "input_hook.hpp"

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD ul_reason_for_call, PVOID)
{
	using namespace std::chrono_literals;
	using namespace pico;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		srand(GetTickCount());

		g_hmodule = hmodule;
		DisableThreadLibraryCalls(g_hmodule);

		g_mainthread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindowA("grcWindow", nullptr))
				std::this_thread::sleep_for(100ms);

			try
			{
				Logger::init();
				g_json.init();
				Hooking::init();
				g_inputhook.init();
				LOG(MESSAGE) << "Pico Menu Initialized";

				g_running = true;
				while (g_running)
				{
					g_json.attempt_save();
					std::this_thread::sleep_for(500ms);
				}
			}
			catch (const std::exception& ex)
			{
				LOG(FATAL) << "Encountered error while running main loop: " << ex.what();
			}

			// gracefully cleanup even after encountering an error
			g_inputhook.cleanup();
			Hooking::cleanup();
			Logger::cleanup();

			FreeLibraryAndExitThread(pico::g_hmodule, 0);
		}, nullptr, 0, &g_mainthread_id);
		break;
	}

	return TRUE;
}


