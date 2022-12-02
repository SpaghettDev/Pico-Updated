#pragma once
#include "../headers/stdafx.h"

int TestInt = 420;
float TestFloat = 6.9f;
bool TestBool = false;

void PicoMenu()
{
	switch (MenuClass::Settings::currentMenu) {

	case Main:
	{
		MenuClass::Title("Main Menu");

		if (MenuClass::Option("Spawn Adder"))
		{
			Hash VehicleHash = MISC::GET_HASH_KEY("adder");
			STREAMING::REQUEST_MODEL(VehicleHash);
			while (!STREAMING::HAS_MODEL_LOADED(VehicleHash)) WAIT(0);

			auto Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			*(unsigned short*)g_Hooking.m_ModelSpawnBypass = 0x9090;
			Vehicle Vehicle = VEHICLE::CREATE_VEHICLE(VehicleHash, Position.x, Position.y, Position.z, 0.f, TRUE, FALSE, FALSE);
			*(unsigned short*)g_Hooking.m_ModelSpawnBypass = 0x0574;

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(VehicleHash);
			if (NETWORK::NETWORK_IS_SESSION_STARTED())
			{
				DECORATOR::DECOR_SET_INT(Vehicle, "MPBitset", 0);
				ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Vehicle, TRUE);
				auto NetworkID = NETWORK::VEH_TO_NET(Vehicle);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Vehicle))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NetworkID, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(Vehicle, FALSE);
			}
			Log::Msg("We safely spawned a vehicle HURRAY!");
		}

		MenuClass::MenuOption("Test Menu", Test);

		MenuClass::Int("Test Int", TestInt, 0, 500);
		MenuClass::Int("Test Int Custom Step", TestInt, 0, 500, 100);

		MenuClass::Float("Test Float", TestFloat, 0.f, 10.f);
		MenuClass::Float("Test Float Custom Step", TestFloat, 0, 10, 1);

		MenuClass::Bool("Test Bool", TestBool);

		MenuClass::MenuOption("Settings Menu", Settings);
	}
	break;
	case Test:
	{
		MenuClass::Title("Test Menu");

		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
		MenuClass::Option("Filler Options");
	}
	break;
	case Settings:
	{
		MenuClass::Title("Settings Menu");

		MenuClass::MenuOption("Theme Menu", Settings_Theme);

		if (MenuClass::Option("Unload")) { g_Running = false; }
		if (MenuClass::Option("Exit")) { exit(0); }
	}
	break;
	case Settings_Theme:
	{
		MenuClass::Title("Theme Menu");

		MenuClass::MenuOption("Title Text", Settings_Theme_TitleText);
		MenuClass::MenuOption("Title Background", Settings_Theme_TitleRect);
		MenuClass::MenuOption("Submenu Bar Text", Settings_Theme_SubmenuBarText);
		MenuClass::MenuOption("Submenu Bar Background", Settings_Theme_SubmenuBarRect);
		MenuClass::MenuOption("Submenu Arrow", Settings_Theme_SubmenuArrow);
		MenuClass::MenuOption("Option Text", Settings_Theme_OptionText);
		MenuClass::MenuOption("Option Background", Settings_Theme_OptionRect);
		MenuClass::MenuOption("Footer Text", Settings_Theme_FooterText);
		MenuClass::MenuOption("Footer Background", Settings_Theme_FooterRect);

		if (MenuClass::Option("Revert To Default"))
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
	case Settings_Theme_TitleText:
	{
		MenuClass::Title("Title Text");

		MenuClass::Int("Red", MenuClass::Settings::TitleText.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::TitleText.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::TitleText.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::TitleText.a, 0, 255);
	}
	break;
	case Settings_Theme_TitleRect:
	{
		MenuClass::Title("Title Background");

		MenuClass::Int("Red", MenuClass::Settings::TitleBackground.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::TitleBackground.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::TitleBackground.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::TitleBackground.a, 0, 255);
	}
	break;
	case Settings_Theme_SubmenuBarText:
	{
		MenuClass::Title("Submenu Bar Text");

		MenuClass::Int("Red", MenuClass::Settings::SubmenuBarText.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::SubmenuBarText.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::SubmenuBarText.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::SubmenuBarText.a, 0, 255);
	}
	break;
	case Settings_Theme_SubmenuBarRect:
	{
		MenuClass::Title("Submenu Bar Background");

		MenuClass::Int("Red", MenuClass::Settings::SubmenuBarBackground.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::SubmenuBarBackground.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::SubmenuBarBackground.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::SubmenuBarBackground.a, 0, 255);
	}
	break;
	case Settings_Theme_SubmenuArrow:
	{
		MenuClass::Title("Submenu Arrow");

		MenuClass::Int("Red", MenuClass::Settings::SubmenuRect.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::SubmenuRect.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::SubmenuRect.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::SubmenuRect.a, 0, 255);
	}
	break;
	case Settings_Theme_OptionText:
	{
		MenuClass::Title("Option Text");

		MenuClass::Option("Unselected:");
		MenuClass::Int("Red", MenuClass::Settings::OptionUnselectedText.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::OptionUnselectedText.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::OptionUnselectedText.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::OptionUnselectedText.a, 0, 255);

		MenuClass::Option("Selected:");
		MenuClass::Int("Red", MenuClass::Settings::OptionSelectedText.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::OptionSelectedText.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::OptionSelectedText.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::OptionSelectedText.a, 0, 255);
	}
	break;
	case Settings_Theme_OptionRect:
	{
		MenuClass::Title("Option Background");

		MenuClass::Option("Unselected:");
		MenuClass::Int("Red", MenuClass::Settings::OptionUnselectedBackground.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::OptionUnselectedBackground.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::OptionUnselectedBackground.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::OptionUnselectedBackground.a, 0, 255);

		MenuClass::Option("Selected:");
		MenuClass::Int("Red", MenuClass::Settings::OptionSelectedBackground.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::OptionSelectedBackground.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::OptionSelectedBackground.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::OptionSelectedBackground.a, 0, 255);
	}
	break;
	case Settings_Theme_FooterText:
	{
		MenuClass::Title("Footer Text");

		MenuClass::Option("Text:");
		MenuClass::Int("Red", MenuClass::Settings::FooterText.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::FooterText.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::FooterText.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::FooterText.a, 0, 255);

		MenuClass::Option("Sprite:");
		MenuClass::Int("Red", MenuClass::Settings::FooterSprite.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::FooterSprite.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::FooterSprite.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::FooterSprite.a, 0, 255);
	}
	break;
	case Settings_Theme_FooterRect:
	{
		MenuClass::Title("Footer Background");

		MenuClass::Int("Red", MenuClass::Settings::FooterBackground.r, 0, 255);
		MenuClass::Int("Green", MenuClass::Settings::FooterBackground.g, 0, 255);
		MenuClass::Int("Blue", MenuClass::Settings::FooterBackground.b, 0, 255);
		MenuClass::Int("Alpha", MenuClass::Settings::FooterBackground.a, 0, 255);
	}
	break;
	}
	MenuClass::End();
	WAIT(0);
}

void ScriptMain() 
{
	srand(GetTickCount64());
	while (true) {
		MenuClass::Checks::Keys();
		PicoMenu();
	}
}