#pragma once

enum SubMenus //Add Sub Menus in here
{
	NOTHING,

	MAIN,

	TEST,
	
	SETTINGS,
	SETTINGS_THEME,
	SETTINGS_THEME_TITLETEXT,
	SETTINGS_THEME_TITLERECT,
	SETTINGS_THEME_SUBMENUBARTEXT,
	SETTINGS_THEME_SUBMENUBARRECT,
	SETTINGS_THEME_SUBMENUARROW,
	SETTINGS_THEME_OPTIONTEXT,
	SETTINGS_THEME_OPTIONRECT,
	SETTINGS_THEME_FOOTERTEXT,
	SETTINGS_THEME_FOOTERRECT
};

namespace MenuClass 
{
	namespace Drawing 
	{
		void text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool right);
		void rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void sprite(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	}

	namespace Settings 
	{
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;

		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;

		extern SubMenus currentMenu;
		extern SubMenus menuLevel;
		extern SubMenus previousMenuLevel;
		extern std::array<int, 1000> optionsArray;
		extern int previousOption;
		extern std::array<SubMenus, 1000> menusArray;
		extern SubMenus previousMenu;

		extern float menuX;
		extern float menuWidth;
		extern RGBAF TitleText;
		extern RGBA TitleBackground;
		extern RGBAF SubmenuBarText;
		extern RGBA SubmenuBarBackground;
		extern RGBA SubmenuRect;
		extern RGBAF OptionUnselectedText;
		extern RGBAF OptionSelectedText;
		extern RGBA OptionUnselectedBackground;
		extern RGBA OptionSelectedBackground;
		extern RGBAF FooterText;
		extern RGBA FooterBackground;
		extern RGBA FooterSprite;

		extern int keyPressDelay;
		extern ULONGLONG keyPressPreviousTick;
		extern const int openKey;
		extern const int backKey;
		extern const int upKey;
		extern const int downKey;
		extern const int leftKey;
		extern const int rightKey;
		extern const int selectKey;
	}

	namespace MenuLevelHandler 
	{
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void OpenMenu();
		void CloseMenu();
	}

	namespace Checks 
	{
		void keys();
	}

	void title(const char* title);
	bool option(const char* option_name);
	bool menu_option(const char* option_name, SubMenus newSub);
	bool bool_option(const char* option_name, bool& b00l);
	bool int_option(const char* option_name, int& _int, int min, int max);
	bool int_option(const char* option_name, int& _int, int min, int max, int step);
	bool float_option(const char* option_name, float& _float, float min, float max);
	bool float_option(const char* option_name, float& _float, float min, float max, float step);
	template<typename T>
	bool list_option(const char* option_name, std::vector<T> list, int& selected_option);

	void end();
	void reset_optioncount();
}