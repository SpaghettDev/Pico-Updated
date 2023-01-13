#pragma once

class InputHook
{
public:
	static void init();
	static void cleanup();
	static bool get_key(int key_code);
	static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};
