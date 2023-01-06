#pragma once

namespace Hotkeys
{
	void init();
	void cleanup();
	bool get_key(int key_code);
	LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
}