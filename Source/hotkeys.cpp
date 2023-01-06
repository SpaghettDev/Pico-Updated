#include "stdafx.h"
#include "hotkeys.h"

namespace Hotkeys
{
	std::array<bool, 256> keys;

	void init()
	{
		pico::g_og_wndproc = WNDPROC(SetWindowLongPtrW(pico::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Hotkeys::wndproc)));
		LOG_MSG("Successfully hooked WNDPROC");
	}

	void cleanup()
	{
		SetWindowLongPtrW(pico::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(pico::g_og_wndproc));
		LOG_MSG("Removed WNDPROC hook");
	}

	bool get_key(int key_code)
	{
		return keys[key_code];
	}

	LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		static void* exceptionAddress;

		__try
		{
			if (pico::g_running)
			{
				if (msg == WM_KEYDOWN)
					Hotkeys::keys[wparam] = true;
				else if (msg == WM_KEYUP)
					Hotkeys::keys[wparam] = false;
			}

			return CallWindowProcW(pico::g_og_wndproc, hwnd, msg, wparam, lparam);
		}
		__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
		{
			LOG_FATAL("Exception occured when trying to get input at %p", exceptionAddress);
		}
	}
}