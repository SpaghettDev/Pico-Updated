#pragma once

// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace
{
#define VK_LBUTTON				0x01 	// Left mouse button
#define VK_RBUTTON				0x02 	// Right mouse button
#define VK_CANCEL				0x03 	// Control-break processing
#define VK_MBUTTON				0x04 	// Middle mouse button (three-button mouse)
#define VK_XBUTTON1 	        0x05 	// X1 mouse button
#define VK_XBUTTON2 	        0x06 	// X2 mouse button
#define VK_UNDEFINED1 	        0x07 	// Undefined
#define VK_BACK					0x08 	// BACKSPACE key
#define VK_TAB					0x09 	// TAB key
#define VK_RESERVED1 	        0x0A    // Reserved
#define VK_RESERVED2            0x0B 	// Reserved
#define VK_CLEAR				0x0C 	// CLEAR key
#define VK_RETURN				0x0D 	// ENTER key
#define VK_UNDEFINED2 	        0x0E    // Undefined
#define VK_UNDEFINED3           0x0F 	// Undefined
#define VK_SHIFT				0x10 	// SHIFT key
#define VK_CONTROL				0x11 	// CTRL key
#define VK_MENU					0x12 	// ALT key
#define VK_PAUSE				0x13 	// PAUSE key
#define VK_CAPITAL				0x14 	// CAPS LOCK key
#define VK_KANA					0x15 	// IME Kana mode
#define VK_HANGUEL				0x15 	// IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
#define VK_HANGUL				0x15 	// IME Hangul mode
#define VK_IME_ON				0x16 	// IME On
#define VK_JUNJA				0x17 	// IME Junja mode
#define VK_FINAL				0x18 	// IME final mode
#define VK_HANJA				0x19 	// IME Hanja mode
#define VK_KANJI				0x19 	// IME Kanji mode
#define VK_IME_OFF				0x1A 	// IME Off
#define VK_ESCAPE				0x1B 	// ESC key
#define VK_CONVERT				0x1C 	// IME convert
#define VK_NONCONVERT 	        0x1D 	// IME nonconvert
#define VK_ACCEPT				0x1E 	// IME accept
#define VK_MODECHANGE 	        0x1F 	// IME mode change request
#define VK_SPACE				0x20 	// SPACEBAR
#define VK_PRIOR				0x21 	// PAGE UP key
#define VK_NEXT					0x22 	// PAGE DOWN key
#define VK_END					0x23 	// END key
#define VK_HOME					0x24 	// HOME key
#define VK_LEFT					0x25 	// LEFT ARROW key
#define VK_UP					0x26 	// UP ARROW key
#define VK_RIGHT				0x27 	// RIGHT ARROW key
#define VK_DOWN					0x28 	// DOWN ARROW key
#define VK_SELECT				0x29 	// SELECT key
#define VK_PRINT				0x2A 	// PRINT key
#define VK_EXECUTE				0x2B 	// EXECUTE key
#define VK_SNAPSHOT				0x2C 	// PRINT SCREEN key
#define VK_INSERT				0x2D 	// INS key
#define VK_DELETE				0x2E 	// DEL key
#define VK_HELP					0x2F 	// HELP key
#define VK_0	                0x30 	// 0 key
#define VK_1	                0x31 	// 1 key
#define VK_2	                0x32 	// 2 key
#define VK_3	                0x33 	// 3 key
#define VK_4	                0x34 	// 4 key
#define VK_5	                0x35 	// 5 key
#define VK_6	                0x36 	// 6 key
#define VK_7	                0x37 	// 7 key
#define VK_8	                0x38 	// 8 key
#define VK_9	                0x39 	// 9 key
#define VK_UNDEFINED4 	        0x3A    // Undefined
#define VK_UNDEFINED5           0x40 	// Undefined
#define VK_A	                0x41 	// A key
#define VK_B	                0x42 	// B key
#define VK_C	                0x43 	// C key
#define VK_D	                0x44 	// D key
#define VK_E	                0x45 	// E key
#define VK_F	                0x46 	// F key
#define VK_G	                0x47 	// G key
#define VK_H	                0x48 	// H key
#define VK_I	                0x49 	// I key
#define VK_J	                0x4A 	// J key
#define VK_K	                0x4B 	// K key
#define VK_L	                0x4C 	// L key
#define VK_M	                0x4D 	// M key
#define VK_N	                0x4E 	// N key
#define VK_O	                0x4F 	// O key
#define VK_P	                0x50 	// P key
#define VK_Q	                0x51 	// Q key
#define VK_R	                0x52 	// R key
#define VK_S	                0x53 	// S key
#define VK_T	                0x54 	// T key
#define VK_U	                0x55 	// U key
#define VK_V	                0x56 	// V key
#define VK_W	                0x57 	// W key
#define VK_X	                0x58 	// X key
#define VK_Y	                0x59 	// Y key
#define VK_Z	                0x5A 	// Z key
#define VK_LWIN					0x5B 	// Left Windows key (Natural keyboard)
#define VK_RWIN					0x5C 	// Right Windows key (Natural keyboard)
#define VK_APPS					0x5D 	// Applications key (Natural keyboard)
#define VK_RESERVED3 	        0x5E 	// Reserved
#define VK_SLEEP				0x5F 	// Computer Sleep key
#define VK_NUMPAD0				0x60 	// Numeric keypad 0 key
#define VK_NUMPAD1				0x61 	// Numeric keypad 1 key
#define VK_NUMPAD2				0x62 	// Numeric keypad 2 key
#define VK_NUMPAD3				0x63 	// Numeric keypad 3 key
#define VK_NUMPAD4				0x64 	// Numeric keypad 4 key
#define VK_NUMPAD5				0x65 	// Numeric keypad 5 key
#define VK_NUMPAD6				0x66 	// Numeric keypad 6 key
#define VK_NUMPAD7				0x67 	// Numeric keypad 7 key
#define VK_NUMPAD8				0x68 	// Numeric keypad 8 key
#define VK_NUMPAD9				0x69 	// Numeric keypad 9 key
#define VK_MULTIPLY 	        0x6A 	// Multiply key
#define VK_ADD					0x6B 	// Add key
#define VK_SEPARATOR 	        0x6C 	// Separator key
#define VK_SUBTRACT 	        0x6D 	// Subtract key
#define VK_DECIMAL				0x6E 	// Decimal key
#define VK_DIVIDE				0x6F 	// Divide key
#define VK_F1					0x70 	// F1 key
#define VK_F2					0x71 	// F2 key
#define VK_F3					0x72 	// F3 key
#define VK_F4					0x73 	// F4 key
#define VK_F5					0x74 	// F5 key
#define VK_F6					0x75 	// F6 key
#define VK_F7					0x76 	// F7 key
#define VK_F8					0x77 	// F8 key
#define VK_F9					0x78 	// F9 key
#define VK_F10					0x79 	// F10 key
#define VK_F11					0x7A 	// F11 key
#define VK_F12					0x7B 	// F12 key
#define VK_F13					0x7C 	// F13 key
#define VK_F14					0x7D 	// F14 key
#define VK_F15					0x7E 	// F15 key
#define VK_F16					0x7F 	// F16 key
#define VK_F17					0x80 	// F17 key
#define VK_F18					0x81 	// F18 key
#define VK_F19					0x82 	// F19 key
#define VK_F20					0x83 	// F20 key
#define VK_F21					0x84 	// F21 key
#define VK_F22					0x85 	// F22 key
#define VK_F23					0x86 	// F23 key
#define VK_F24					0x87 	// F24 key
#define VK_UNASSIGNED1          0x88    // Unassigned
#define VK_UNASSIGNED2 	        0x8F 	// Unassigned
#define VK_NUMLOCK  	        0x90 	// NUM LOCK key
#define VK_SCROLL				0x91 	// SCROLL LOCK key
#define VK_OEM_SPEC1	        0x92    // OEM specific
#define VK_OEM_SPEC2	        0x93    // OEM specific
#define VK_OEM_SPEC3	        0x94    // OEM specific
#define VK_OEM_SPEC4	        0x95    // OEM specific
#define VK_OEM_SPEC5	        0x96 	// OEM specific
#define VK_UNASSIGNED3 	        0x97    // Unassigned
#define VK_UNASSIGNED4          0x9F 	// Unassigned
#define VK_LSHIFT				0xA0 	// Left SHIFT key
#define VK_RSHIFT				0xA1 	// Right SHIFT key
#define VK_LCONTROL 	        0xA2 	// Left CONTROL key
#define VK_RCONTROL 	        0xA3 	// Right CONTROL key
#define VK_LMENU				0xA4 	// Left ALT key
#define VK_RMENU				0xA5 	// Right ALT key
#define VK_BROWSER_BACK 	    0xA6 	// Browser Back key
#define VK_BROWSER_FORWARD 	    0xA7 	// Browser Forward key
#define VK_BROWSER_REFRESH 	    0xA8 	// Browser Refresh key
#define VK_BROWSER_STOP 	    0xA9 	// Browser Stop key
#define VK_BROWSER_SEARCH 	    0xAA 	// Browser Search key
#define VK_BROWSER_FAVORITES    0xAB 	// Browser Favorites key
#define VK_BROWSER_HOME 	    0xAC 	// Browser Start and Home key
#define VK_VOLUME_MUTE 	        0xAD 	// Volume Mute key
#define VK_VOLUME_DOWN 	        0xAE 	// Volume Down key
#define VK_VOLUME_UP 	        0xAF 	// Volume Up key
#define VK_MEDIA_NEXT_TRACK 	0xB0 	// Next Track key
#define VK_MEDIA_PREV_TRACK 	0xB1 	// Previous Track key
#define VK_MEDIA_STOP 	        0xB2 	// Stop Media key
#define VK_MEDIA_PLAY_PAUSE 	0xB3 	// Play/Pause Media key
#define VK_LAUNCH_MAIL 	        0xB4 	// Start Mail key
#define VK_LAUNCH_MEDIA_SELECT 	0xB5 	// Select Media key
#define VK_LAUNCH_APP1 	        0xB6 	// Start Application 1 key
#define VK_LAUNCH_APP2      	0xB7 	// Start Application 2 key
#define VK_RESERVED5 	        0xB8    // Reserved
#define VK_RESERVED6            0xB9 	// Reserved
#define VK_OEM_1				0xBA 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key
#define VK_OEM_PLUS 	        0xBB 	// For any country/region, the '+' key
#define VK_OEM_COMMA 	        0xBC 	// For any country/region, the ',' key
#define VK_OEM_MINUS 	        0xBD 	// For any country/region, the '-' key
#define VK_OEM_PERIOD 	        0xBE 	// For any country/region, the '.' key
#define VK_OEM_2				0xBF 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
#define VK_OEM_3				0xC0 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
#define VK_RESERVED7 	        0xC1    // Reserved
#define VK_RESERVED8            0xD7 	// Reserved
#define VK_UNASSIGNED6 	        0xD8    // Unassigned
#define VK_UNASSIGNED7          0xDA 	// Unassigned
#define VK_OEM_4				0xDB 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
#define VK_OEM_5				0xDC 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
#define VK_OEM_6				0xDD 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
#define VK_OEM_7				0xDE 	// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
#define VK_OEM_8				0xDF 	// Used for miscellaneous characters; it can vary by keyboard.
#define VK_RESERVED9 	        0xE0 	// Reserved
#define VK_OEM_SPEC6	        0xE1 	// OEM specific
#define VK_OEM_102          	0xE2 	// The <> keys on the US standard keyboard, or the \\| key on the non-US 102-key keyboard
#define VK_OEM_SPEC7	        0xE3 	// OEM specific
#define VK_OEM_SPEC8	        0xE3 	// OEM specific
#define VK_PROCESSKEY 	        0xE5 	// IME PROCESS key
#define VK_OEM_SPEC9	        0xE6 	// OEM specific
#define VK_PACKET				0xE7 	// Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
#define VK_UNASSIGNED8 	        0xE8 	// Unassigned
#define VK_OEM_SPEC10	        0xE9 	// OEM specific
#define VK_OEM_SPEC11	        0xF5 	// OEM specific
#define VK_ATTN					0xF6 	// Attn key
#define VK_CRSEL				0xF7 	// CrSel key
#define VK_EXSEL				0xF8 	// ExSel key
#define VK_EREOF				0xF9 	// Erase EOF key
#define VK_PLAY					0xFA 	// Play key
#define VK_ZOOM					0xFB 	// Zoom key
#define VK_NONAME				0xFC 	// Reserved
#define VK_PA1              	0xFD 	// PA1 key
#define VK_OEM_CLEAR 	        0xFE 	// Clear key
}

namespace key_codes
{
#define S(s) #s

	inline nlohmann::ordered_map<std::string_view, int> keys{
		{ "VK_LBUTTON", VK_LBUTTON },
		{ "VK_RBUTTON", VK_RBUTTON },
		{ "VK_CANCEL", VK_CANCEL },
		{ "VK_MBUTTON", VK_MBUTTON },
		{ "VK_XBUTTON1", VK_XBUTTON1 },
		{ "VK_XBUTTON2", VK_XBUTTON2 },
		{ "VK_UNDEFINED1", VK_UNDEFINED1 },
		{ "VK_BACK", VK_BACK },
		{ "VK_TAB", VK_TAB },
		{ "VK_RESERVED1", VK_RESERVED1 },
		{ "VK_RESERVED2", VK_RESERVED2 },
		{ "VK_CLEAR", VK_CLEAR },
		{ "VK_RETURN", VK_RETURN },
		{ "VK_UNDEFINED2", VK_UNDEFINED2 },
		{ "VK_UNDEFINED3", VK_UNDEFINED3 },
		{ "VK_SHIFT", VK_SHIFT },
		{ "VK_CONTROL", VK_CONTROL },
		{ "VK_MENU", VK_MENU },
		{ "VK_PAUSE", VK_PAUSE },
		{ "VK_CAPITAL", VK_CAPITAL },
		{ "VK_KANA", VK_KANA },
		{ "VK_HANGUEL", VK_HANGUEL },
		{ "VK_HANGUL", VK_HANGUL },
		{ "VK_IME_ON", VK_IME_ON },
		{ "VK_JUNJA", VK_JUNJA },
		{ "VK_FINAL", VK_FINAL },
		{ "VK_HANJA", VK_HANJA },
		{ "VK_KANJI", VK_KANJI },
		{ "VK_IME_OFF", VK_IME_OFF },
		{ "VK_ESCAPE", VK_ESCAPE },
		{ "VK_CONVERT", VK_CONVERT },
		{ "VK_NONCONVERT", VK_NONCONVERT },
		{ "VK_ACCEPT", VK_ACCEPT },
		{ "VK_MODECHANGE", VK_MODECHANGE },
		{ "VK_SPACE", VK_SPACE },
		{ "VK_PRIOR", VK_PRIOR },
		{ "VK_NEXT", VK_NEXT },
		{ "VK_END", VK_END },
		{ "VK_HOME", VK_HOME },
		{ "VK_LEFT", VK_LEFT },
		{ "VK_UP", VK_UP },
		{ "VK_RIGHT", VK_RIGHT },
		{ "VK_DOWN", VK_DOWN },
		{ "VK_SELECT", VK_SELECT },
		{ "VK_PRINT", VK_PRINT },
		{ "VK_EXECUTE", VK_EXECUTE },
		{ "VK_SNAPSHOT", VK_SNAPSHOT },
		{ "VK_INSERT", VK_INSERT },
		{ "VK_DELETE", VK_DELETE },
		{ "VK_HELP", VK_HELP },
		{ "VK_0", VK_0 },
		{ "VK_1", VK_1 },
		{ "VK_2", VK_2 },
		{ "VK_3", VK_3 },
		{ "VK_4", VK_4 },
		{ "VK_5", VK_5 },
		{ "VK_6", VK_6 },
		{ "VK_7", VK_7 },
		{ "VK_8", VK_8 },
		{ "VK_9", VK_9 },
		{ "VK_UNDEFINED4", VK_UNDEFINED4 },
		{ "VK_UNDEFINED5", VK_UNDEFINED5 },
		{ "VK_A", VK_A },
		{ "VK_B", VK_B },
		{ "VK_C", VK_C },
		{ "VK_D", VK_D },
		{ "VK_E", VK_E },
		{ "VK_F", VK_F },
		{ "VK_G", VK_G },
		{ "VK_H", VK_H },
		{ "VK_I", VK_I },
		{ "VK_J", VK_J },
		{ "VK_K", VK_K },
		{ "VK_L", VK_L },
		{ "VK_M", VK_M },
		{ "VK_N", VK_N },
		{ "VK_O", VK_O },
		{ "VK_P", VK_P },
		{ "VK_Q", VK_Q },
		{ "VK_R", VK_R },
		{ "VK_S", VK_S },
		{ "VK_T", VK_T },
		{ "VK_U", VK_U },
		{ "VK_V", VK_V },
		{ "VK_W", VK_W },
		{ "VK_X", VK_X },
		{ "VK_Y", VK_Y },
		{ "VK_Z", VK_Z },
		{ "VK_LWIN", VK_LWIN },
		{ "VK_RWIN", VK_RWIN },
		{ "VK_APPS", VK_APPS },
		{ "VK_RESERVED3", VK_RESERVED3 },
		{ "VK_SLEEP", VK_SLEEP },
		{ "VK_NUMPAD0", VK_NUMPAD0 },
		{ "VK_NUMPAD1", VK_NUMPAD1 },
		{ "VK_NUMPAD2", VK_NUMPAD2 },
		{ "VK_NUMPAD3", VK_NUMPAD3 },
		{ "VK_NUMPAD4", VK_NUMPAD4 },
		{ "VK_NUMPAD5", VK_NUMPAD5 },
		{ "VK_NUMPAD6", VK_NUMPAD6 },
		{ "VK_NUMPAD7", VK_NUMPAD7 },
		{ "VK_NUMPAD8", VK_NUMPAD8 },
		{ "VK_NUMPAD9", VK_NUMPAD9 },
		{ "VK_MULTIPLY", VK_MULTIPLY },
		{ "VK_ADD", VK_ADD },
		{ "VK_SEPARATOR", VK_SEPARATOR },
		{ "VK_SUBTRACT", VK_SUBTRACT },
		{ "VK_DECIMAL", VK_DECIMAL },
		{ "VK_DIVIDE", VK_DIVIDE },
		{ "VK_F1", VK_F1 },
		{ "VK_F2", VK_F2 },
		{ "VK_F3", VK_F3 },
		{ "VK_F4", VK_F4 },
		{ "VK_F5", VK_F5 },
		{ "VK_F6", VK_F6 },
		{ "VK_F7", VK_F7 },
		{ "VK_F8", VK_F8 },
		{ "VK_F9", VK_F9 },
		{ "VK_F10", VK_F10 },
		{ "VK_F11", VK_F11 },
		{ "VK_F12", VK_F12 },
		{ "VK_F13", VK_F13 },
		{ "VK_F14", VK_F14 },
		{ "VK_F15", VK_F15 },
		{ "VK_F16", VK_F16 },
		{ "VK_F17", VK_F17 },
		{ "VK_F18", VK_F18 },
		{ "VK_F19", VK_F19 },
		{ "VK_F20", VK_F20 },
		{ "VK_F21", VK_F21 },
		{ "VK_F22", VK_F22 },
		{ "VK_F23", VK_F23 },
		{ "VK_F24", VK_F24 },
		{ "VK_UNASSIGNED1", VK_UNASSIGNED1 },
		{ "VK_UNASSIGNED2", VK_UNASSIGNED2 },
		{ "VK_NUMLOCK", VK_NUMLOCK },
		{ "VK_SCROLL", VK_SCROLL },
		{ "VK_OEM_SPEC1", VK_OEM_SPEC1 },
		{ "VK_OEM_SPEC2", VK_OEM_SPEC2 },
		{ "VK_OEM_SPEC3", VK_OEM_SPEC3 },
		{ "VK_OEM_SPEC4", VK_OEM_SPEC4 },
		{ "VK_OEM_SPEC5", VK_OEM_SPEC5 },
		{ "VK_UNASSIGNED3", VK_UNASSIGNED3 },
		{ "VK_UNASSIGNED4", VK_UNASSIGNED4 },
		{ "VK_LSHIFT", VK_LSHIFT },
		{ "VK_RSHIFT", VK_RSHIFT },
		{ "VK_LCONTROL", VK_LCONTROL },
		{ "VK_RCONTROL", VK_RCONTROL },
		{ "VK_LMENU", VK_LMENU },
		{ "VK_RMENU", VK_RMENU },
		{ "VK_BROWSER_BACK", VK_BROWSER_BACK },
		{ "VK_BROWSER_FORWARD", VK_BROWSER_FORWARD },
		{ "VK_BROWSER_REFRESH", VK_BROWSER_REFRESH },
		{ "VK_BROWSER_STOP", VK_BROWSER_STOP },
		{ "VK_BROWSER_SEARCH", VK_BROWSER_SEARCH },
		{ "VK_BROWSER_FAVORITES", VK_BROWSER_FAVORITES },
		{ "VK_BROWSER_HOME", VK_BROWSER_HOME },
		{ "VK_VOLUME_MUTE", VK_VOLUME_MUTE },
		{ "VK_VOLUME_DOWN", VK_VOLUME_DOWN },
		{ "VK_VOLUME_UP", VK_VOLUME_UP },
		{ "VK_MEDIA_NEXT_TRACK", VK_MEDIA_NEXT_TRACK },
		{ "VK_MEDIA_PREV_TRACK", VK_MEDIA_PREV_TRACK },
		{ "VK_MEDIA_STOP", VK_MEDIA_STOP },
		{ "VK_MEDIA_PLAY_PAUSE", VK_MEDIA_PLAY_PAUSE },
		{ "VK_LAUNCH_MAIL", VK_LAUNCH_MAIL },
		{ "VK_LAUNCH_MEDIA_SELECT", VK_LAUNCH_MEDIA_SELECT },
		{ "VK_LAUNCH_APP1", VK_LAUNCH_APP1 },
		{ "VK_LAUNCH_APP2", VK_LAUNCH_APP2 },
		{ "VK_RESERVED5", VK_RESERVED5 },
		{ "VK_RESERVED6", VK_RESERVED6 },
		{ "VK_OEM_1", VK_OEM_1 },
		{ "VK_OEM_PLUS", VK_OEM_PLUS },
		{ "VK_OEM_COMMA", VK_OEM_COMMA },
		{ "VK_OEM_MINUS", VK_OEM_MINUS },
		{ "VK_OEM_PERIOD", VK_OEM_PERIOD },
		{ "VK_OEM_2", VK_OEM_2 },
		{ "VK_OEM_3", VK_OEM_3 },
		{ "VK_RESERVED7", VK_RESERVED7 },
		{ "VK_RESERVED8", VK_RESERVED8 },
		{ "VK_UNASSIGNED6", VK_UNASSIGNED6 },
		{ "VK_UNASSIGNED7", VK_UNASSIGNED7 },
		{ "VK_OEM_4", VK_OEM_4 },
		{ "VK_OEM_5", VK_OEM_5 },
		{ "VK_OEM_6", VK_OEM_6 },
		{ "VK_OEM_7", VK_OEM_7 },
		{ "VK_OEM_8", VK_OEM_8 },
		{ "VK_RESERVED9", VK_RESERVED9 },
		{ "VK_OEM_SPEC6", VK_OEM_SPEC6 },
		{ "VK_OEM_102", VK_OEM_102 },
		{ "VK_OEM_SPEC7", VK_OEM_SPEC7 },
		{ "VK_OEM_SPEC8", VK_OEM_SPEC8 },
		{ "VK_PROCESSKEY", VK_PROCESSKEY },
		{ "VK_OEM_SPEC9", VK_OEM_SPEC9 },
		{ "VK_PACKET", VK_PACKET },
		{ "VK_UNASSIGNED8", VK_UNASSIGNED8 },
		{ "VK_OEM_SPEC10", VK_OEM_SPEC10 },
		{ "VK_OEM_SPEC11", VK_OEM_SPEC11 },
		{ "VK_ATTN", VK_ATTN },
		{ "VK_CRSEL", VK_CRSEL },
		{ "VK_EXSEL", VK_EXSEL },
		{ "VK_EREOF", VK_EREOF },
		{ "VK_PLAY", VK_PLAY },
		{ "VK_ZOOM", VK_ZOOM },
		{ "VK_NONAME", VK_NONAME },
		{ "VK_PA1", VK_PA1 },
		{ "VK_OEM_CLEAR", VK_OEM_CLEAR }
	};

	inline std::vector<std::string_view> names;

	inline void init_names()
	{
		static bool init = false;

		if (!init)
		{
			names.reserve(keys.size());

			for (const auto& [name, _] : keys)
				names.push_back(name);

			init = true;
		}
	}
}
