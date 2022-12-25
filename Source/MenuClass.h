#pragma once

#pragma warning (disable: 4091)

enum SubMenus //Add Sub Menus in here
{
	Nothing,
	Main,
	Test,
	Settings,
	Settings_Theme,
	Settings_Theme_TitleText,
	Settings_Theme_TitleRect,
	Settings_Theme_SubmenuBarText,
	Settings_Theme_SubmenuBarRect,
	Settings_Theme_SubmenuArrow,
	Settings_Theme_OptionText,
	Settings_Theme_OptionRect,
	Settings_Theme_FooterText,
	Settings_Theme_FooterRect
};

namespace MenuClass 
{
	namespace Drawing 
	{
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool right);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Sprite(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
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
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];

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
		extern int keyPressPreviousTick;
		extern int openKey;
		extern int backKey;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
	}
	namespace MenuLevelHandler 
	{
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void CloseMenu();
	}
	namespace Checks 
	{
		void Keys();
	}

	void Title(const char* title);
	bool Option(const char* option);
	bool MenuOption(const char* option, SubMenus newSub);
	bool Bool(const char* option, bool& b00l);
	bool Int(const char* option, int& _int, int min, int max);
	bool Int(const char* option, int& _int, int min, int max, int step);
	bool Float(const char* option, float& _float, float min, float max);
	bool Float(const char* option, float& _float, float min, float max, float step);
	void End();
}