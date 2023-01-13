#include "stdafx.hpp"
#include "input_hook.hpp"

namespace
{
	std::array<bool, 256> keys;
}

void InputHook::init()
{
	pico::g_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(pico::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&InputHook::wndproc)));
	LOG_MSG("Successfully hooked WNDPROC");
}

void InputHook::cleanup()
{
	SetWindowLongPtrW(pico::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(pico::g_og_wndproc));
	LOG_MSG("Removed WNDPROC hook");
}

bool InputHook::get_key(int key_code)
{
	return keys[key_code];
}

LRESULT InputHook::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static void* exceptionAddress;

	__try
	{
		if (pico::g_running)
		{
			if (msg == WM_KEYDOWN)
				keys[wparam] = true;
			else if (msg == WM_KEYUP)
				keys[wparam] = false;
		}

		return CallWindowProcW(pico::g_og_wndproc, hwnd, msg, wparam, lparam);
	}
	__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
	{
		LOG_FATAL("Exception occured when trying to get input at %p", exceptionAddress);
	}
}
