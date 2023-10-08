#include "stdafx.hpp"

namespace
{
	std::array<bool, 256> keys_states;
}

void InputHook::init()
{
	pico::g_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(pico::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&InputHook::wndproc)));
	LOG(MESSAGE) << "Successfully hooked WNDPROC";
}

void InputHook::cleanup()
{
	SetWindowLongPtrW(pico::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(pico::g_og_wndproc));
	LOG(MESSAGE) << "Removed WNDPROC hook";
}

bool InputHook::get_key_state(int key_code)
{
	return keys_states[key_code];
}

LRESULT InputHook::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static void* exceptionAddress;

	auto log_ex = [](void* exaddr, DWORD e) -> void {
		LOG(FATAL) << "Exception occured when trying to get input at " << exaddr << " : " << std::system_category().message(e).c_str();
	};

	__try
	{
		if (pico::g_running)
		{
			if (msg == WM_KEYDOWN)
				keys_states[wparam] = true;
			else if (msg == WM_KEYUP)
				keys_states[wparam] = false;
		}

		return CallWindowProcW(pico::g_og_wndproc, hwnd, msg, wparam, lparam);
	}
	__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
	{
		log_ex(exceptionAddress, GetLastError());
	}
}
