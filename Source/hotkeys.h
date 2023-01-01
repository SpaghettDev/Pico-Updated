#pragma once

namespace Hotkeys
{
	void init();
	void cleanup();
	LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
}