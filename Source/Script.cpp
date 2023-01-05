#pragma once
#include "stdafx.h"
#include "vehicle.hpp"

int TestInt = 420;
float TestFloat = 6.9f;
bool TestBool = false;

void PicoMenu()
{
	switch (MenuClass::Settings::currentMenu)
	{
	case SubMenus::MAIN:
	{
		MenuClass::title("Main Menu");

		if (MenuClass::option("Spawn Adder"))
			vehicle::spawn_vehicle("adder");

		MenuClass::menu_option("Test Menu", TEST);

		MenuClass::int_option("Test Int", TestInt, 0, 500);
		MenuClass::int_option("Test Int Custom Step", TestInt, 0, 500, 100);

		MenuClass::float_option("Test Float", TestFloat, 0.f, 10.f);
		MenuClass::float_option("Test Float Custom Step", TestFloat, 0, 10, 1);

		MenuClass::bool_option("Test Bool", TestBool);

		MenuClass::menu_option("Settings Menu", SubMenus::SETTINGS);
	}
	break;
	case SubMenus::TEST:
	{
		MenuClass::title("Test Menu");

		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
		MenuClass::option("Filler Options");
	}
	break;
	case SubMenus::SETTINGS:
	{
		MenuClass::title("Settings Menu");

		MenuClass::menu_option("Theme Menu", SubMenus::SETTINGS_THEME);

		if (MenuClass::option("Unload")) 
			pico::g_running = false;
		if (MenuClass::option("Exit")) 
			exit(0);
	}
	break;
	case SubMenus::SETTINGS_THEME:
	{
		MenuClass::title("Theme Menu");

		MenuClass::menu_option("Title Text", SubMenus::SETTINGS_THEME_TITLETEXT);
		MenuClass::menu_option("Title Background", SubMenus::SETTINGS_THEME_TITLERECT);
		MenuClass::menu_option("Submenu Bar Text", SubMenus::SETTINGS_THEME_SUBMENUBARTEXT);
		MenuClass::menu_option("Submenu Bar Background", SubMenus::SETTINGS_THEME_SUBMENUBARRECT);
		MenuClass::menu_option("Submenu Arrow", SubMenus::SETTINGS_THEME_SUBMENUARROW);
		MenuClass::menu_option("Option Text", SubMenus::SETTINGS_THEME_OPTIONTEXT);
		MenuClass::menu_option("Option Background", SubMenus::SETTINGS_THEME_OPTIONRECT);
		MenuClass::menu_option("Footer Text", SubMenus::SETTINGS_THEME_FOOTERTEXT);
		MenuClass::menu_option("Footer Background", SubMenus::SETTINGS_THEME_FOOTERRECT);

		if (MenuClass::option("Revert To Default"))
		{
			MenuClass::Settings::TitleText = { 255, 255, 255, 255, 1 };
			MenuClass::Settings::TitleBackground = { 3, 140, 252, 255 };
			MenuClass::Settings::SubmenuBarText = { 255, 255, 255, 255, 4 };
			MenuClass::Settings::SubmenuBarBackground = { 0, 0, 0, 190 };
			MenuClass::Settings::SubmenuRect = { 3, 140, 252, 255 };
			MenuClass::Settings::OptionUnselectedText = { 255, 255, 255, 255, 4 };
			MenuClass::Settings::OptionSelectedText = { 10, 10, 10, 255, 4 };
			MenuClass::Settings::OptionUnselectedBackground = { 0, 0, 0, 160 };
			MenuClass::Settings::OptionSelectedBackground = { 255, 255, 255, 255 };
			MenuClass::Settings::FooterText = { 255, 255, 255, 255, 4 };
			MenuClass::Settings::FooterBackground = { 0, 0, 0, 220 };
			MenuClass::Settings::FooterSprite = { 255, 255, 255, 255 };
		}
	}
	break;
	case SubMenus::SETTINGS_THEME_TITLETEXT:
	{
		MenuClass::title("Title Text");

		MenuClass::int_option("Red", MenuClass::Settings::TitleText.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::TitleText.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::TitleText.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::TitleText.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_TITLERECT:
	{
		MenuClass::title("Title Background");

		MenuClass::int_option("Red", MenuClass::Settings::TitleBackground.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::TitleBackground.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::TitleBackground.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::TitleBackground.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_SUBMENUBARTEXT:
	{
		MenuClass::title("Submenu Bar Text");

		MenuClass::int_option("Red", MenuClass::Settings::SubmenuBarText.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::SubmenuBarText.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::SubmenuBarText.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::SubmenuBarText.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_SUBMENUBARRECT:
	{
		MenuClass::title("Submenu Bar Background");

		MenuClass::int_option("Red", MenuClass::Settings::SubmenuBarBackground.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::SubmenuBarBackground.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::SubmenuBarBackground.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::SubmenuBarBackground.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_SUBMENUARROW:
	{
		MenuClass::title("Submenu Arrow");

		MenuClass::int_option("Red", MenuClass::Settings::SubmenuRect.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::SubmenuRect.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::SubmenuRect.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::SubmenuRect.a, 0, 255);
	}
	break;
	case SETTINGS_THEME_OPTIONTEXT:
	{
		MenuClass::title("Option Text");

		MenuClass::option("Unselected:");
		MenuClass::int_option("Red", MenuClass::Settings::OptionUnselectedText.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::OptionUnselectedText.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::OptionUnselectedText.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::OptionUnselectedText.a, 0, 255);

		MenuClass::option("Selected:");
		MenuClass::int_option("Red", MenuClass::Settings::OptionSelectedText.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::OptionSelectedText.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::OptionSelectedText.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::OptionSelectedText.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_OPTIONRECT:
	{
		MenuClass::title("Option Background");

		MenuClass::option("Unselected:");
		MenuClass::int_option("Red", MenuClass::Settings::OptionUnselectedBackground.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::OptionUnselectedBackground.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::OptionUnselectedBackground.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::OptionUnselectedBackground.a, 0, 255);

		MenuClass::option("Selected:");
		MenuClass::int_option("Red", MenuClass::Settings::OptionSelectedBackground.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::OptionSelectedBackground.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::OptionSelectedBackground.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::OptionSelectedBackground.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_FOOTERTEXT:
	{
		MenuClass::title("Footer Text");

		MenuClass::option("Text:");
		MenuClass::int_option("Red", MenuClass::Settings::FooterText.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::FooterText.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::FooterText.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::FooterText.a, 0, 255);

		MenuClass::option("Sprite:");
		MenuClass::int_option("Red", MenuClass::Settings::FooterSprite.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::FooterSprite.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::FooterSprite.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::FooterSprite.a, 0, 255);
	}
	break;
	case SubMenus::SETTINGS_THEME_FOOTERRECT:
	{
		MenuClass::title("Footer Background");

		MenuClass::int_option("Red", MenuClass::Settings::FooterBackground.r, 0, 255);
		MenuClass::int_option("Green", MenuClass::Settings::FooterBackground.g, 0, 255);
		MenuClass::int_option("Blue", MenuClass::Settings::FooterBackground.b, 0, 255);
		MenuClass::int_option("Alpha", MenuClass::Settings::FooterBackground.a, 0, 255);
	}
	break;
	}
	MenuClass::end();
	WAIT(0);
}

void ScriptMain() 
{
	srand(GetTickCount64());

	while (pico::g_running)
	{
		PicoMenu();
		MenuClass::reset_optioncount();
	}
}