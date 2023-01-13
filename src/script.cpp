#include "stdafx.hpp"
#include "menu_class.hpp"
#include "functions.hpp"

void pico_menu()
{
	static std::string last_input;

	using namespace functions;

	switch (menu::settings::currentMenu)
	{
	case SubMenus::MAIN:
	{
		menu::title("Main Menu");

		menu::menu_option("Self", SubMenus::SELF);
		menu::menu_option("Vehicle", SubMenus::VEHICLESUB);
		menu::menu_option("Settings Menu", SubMenus::SETTINGS);
	}
	break;

	case SubMenus::SELF:
	{
		menu::title("Self Options");

		menu::menu_option("Proofs", SubMenus::SELF_PROOFS);
		menu::menu_option("Wanted Level", SubMenus::SELF_WANTEDLEVEL);

		if (menu::option("Restore Health"))
			player::max_health();
		
		if (menu::option("Restore Armor"))
			player::max_armor();

		if (menu::option("Restore Everything"))
		{
			player::max_health();
			player::max_armor();
			player::fill_inventory();
		}

		if (menu::option("Suicide"))
			player::suicide();
		
		if (menu::option("Clean Player"))
			player::clean_ped(player::ped);
		
		menu::bool_option("Always Clean Player", looped::self::always_clean_ped);

		if (menu::option("Fill Inventory"))
			player::fill_inventory();

	}
	break;

	case SubMenus::SELF_PROOFS:
	{
		menu::title("Self Proofs");

		menu::bool_option("Godmode", looped::self::proofs[0].toggle);
		menu::bool_option("Bullet Proof", looped::self::proofs[1].toggle);
		menu::bool_option("Fire Proof", looped::self::proofs[2].toggle);
		menu::bool_option("Collision Proof", looped::self::proofs[3].toggle);
		menu::bool_option("Melee Proof", looped::self::proofs[4].toggle);
		menu::bool_option("Explosion Proof", looped::self::proofs[5].toggle);
		menu::bool_option("Steam Proof", looped::self::proofs[6].toggle);
		menu::bool_option("Drown Proof", looped::self::proofs[7].toggle);
		menu::bool_option("Water Proof", looped::self::proofs[8].toggle);
	}
	break;

	case SubMenus::SELF_WANTEDLEVEL:
	{
		menu::title("Self Wanted Level");

		menu::int_option("Wanted Level", looped::self::wanted_level, 0, 5);
		menu::bool_option("Force Wanted Level", looped::self::force_wanted_level);
		if (menu::option("Clear Wanted Level"))
			player::clear_wanted_level();
	}
	break;

	case SubMenus::VEHICLESUB:
	{
		menu::title("Vehicle Options");

		menu::menu_option("Proofs", SubMenus::VEHICLESUB_PROOFS);
		menu::menu_option("Mechanic", SubMenus::VEHICLESUB_MECHANIC);

		if (menu::option("Spawn Vehicle"))
		{
			std::string keyboard_result = utils::keyboard_input(last_input == "" ? "adder" : last_input.c_str(), 25);

			if (vehicle::spawn_vehicle(rage::joaat(keyboard_result), player::pos))
				last_input = keyboard_result;
			else
				utils::notify::above_map(std::format("~r~{} is not a valid vehicle!", keyboard_result));
		}
	}
	break;

	case SubMenus::VEHICLESUB_PROOFS:
	{
		menu::title("Vehicle Proofs");

		menu::bool_option("Godmode", looped::vehicle::proofs[0].toggle);
		menu::bool_option("Bullet Proof", looped::vehicle::proofs[1].toggle);
		menu::bool_option("Fire Proof", looped::vehicle::proofs[2].toggle);
		menu::bool_option("Collision Proof", looped::vehicle::collision_proof);
		menu::bool_option("Melee Proof", looped::vehicle::proofs[4].toggle);
		menu::bool_option("Explosion Proof", looped::vehicle::proofs[5].toggle);
		menu::bool_option("Steam Proof", looped::vehicle::proofs[6].toggle);
		menu::bool_option("Drown Proof", looped::vehicle::proofs[7].toggle);
	}
	break;
	
	case SubMenus::VEHICLESUB_MECHANIC:
	{
		menu::title("Vehicle Mechanic");

		if (menu::option("Repair Vehicle"))
		{
			if (player::veh)
				vehicle::repair(player::veh);
			else
				utils::notify::above_map("~r~Please be in a vehicle!");
		}

		menu::bool_option("Always Repair Vehicle", looped::vehicle::always_repair);

		if (menu::option("Max Vehicle"))
		{
			if (player::veh)
				vehicle::max_vehicle(player::veh);
			else
				utils::notify::above_map("~r~Please be in a vehicle!");
		}

		if (menu::bool_option("Horn Boost", looped::vehicle::horn_boost))
		{
			if (player::veh)
				vehicle::horn_boost(player::veh);
			else
				utils::notify::above_map("~r~Please be in a vehicle!");
		}

		menu::float_option("Horn Boost Speed Multiplier", vehicle::horn_boost_speed_increment, 0.f, 10.f);
	}
	break;

	case SubMenus::SETTINGS:
	{
		menu::title("Settings Menu");

		menu::menu_option("Theme Menu", SubMenus::SETTINGS_THEME);

		if (menu::option("Unload")) 
			pico::g_running = false;
		if (menu::option("Exit")) 
			exit(0);
	}
	break;

	case SubMenus::SETTINGS_THEME:
	{
		menu::title("Theme Menu");

		menu::menu_option("Title Text", SubMenus::SETTINGS_THEME_TITLETEXT);
		menu::menu_option("Title Background", SubMenus::SETTINGS_THEME_TITLERECT);
		menu::menu_option("Submenu Bar Text", SubMenus::SETTINGS_THEME_SUBMENUBARTEXT);
		menu::menu_option("Submenu Bar Background", SubMenus::SETTINGS_THEME_SUBMENUBARRECT);
		menu::menu_option("Submenu Arrow", SubMenus::SETTINGS_THEME_SUBMENUARROW);
		menu::menu_option("Option Text", SubMenus::SETTINGS_THEME_OPTIONTEXT);
		menu::menu_option("Option Background", SubMenus::SETTINGS_THEME_OPTIONRECT);
		menu::menu_option("Footer Text", SubMenus::SETTINGS_THEME_FOOTERTEXT);
		menu::menu_option("Footer Background", SubMenus::SETTINGS_THEME_FOOTERRECT);

		if (menu::option("Revert To Default"))
		{
			menu::settings::TitleText = { 255, 255, 255, 255, 1 };
			menu::settings::TitleBackground = { 3, 140, 252, 255 };
			menu::settings::SubmenuBarText = { 255, 255, 255, 255, 4 };
			menu::settings::SubmenuBarBackground = { 0, 0, 0, 190 };
			menu::settings::SubmenuRect = { 3, 140, 252, 255 };
			menu::settings::OptionUnselectedText = { 255, 255, 255, 255, 4 };
			menu::settings::OptionSelectedText = { 10, 10, 10, 255, 4 };
			menu::settings::OptionUnselectedBackground = { 0, 0, 0, 160 };
			menu::settings::OptionSelectedBackground = { 255, 255, 255, 255 };
			menu::settings::FooterText = { 255, 255, 255, 255, 4 };
			menu::settings::FooterBackground = { 0, 0, 0, 220 };
			menu::settings::FooterSprite = { 255, 255, 255, 255 };
		}
	}
	break;

	case SubMenus::SETTINGS_THEME_TITLETEXT:
	{
		menu::title("Title Text");

		menu::int_option("Red", menu::settings::TitleText.r, 0, 255);
		menu::int_option("Green", menu::settings::TitleText.g, 0, 255);
		menu::int_option("Blue", menu::settings::TitleText.b, 0, 255);
		menu::int_option("Alpha", menu::settings::TitleText.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_TITLERECT:
	{
		menu::title("Title Background");

		menu::int_option("Red", menu::settings::TitleBackground.r, 0, 255);
		menu::int_option("Green", menu::settings::TitleBackground.g, 0, 255);
		menu::int_option("Blue", menu::settings::TitleBackground.b, 0, 255);
		menu::int_option("Alpha", menu::settings::TitleBackground.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_SUBMENUBARTEXT:
	{
		menu::title("Submenu Bar Text");

		menu::int_option("Red", menu::settings::SubmenuBarText.r, 0, 255);
		menu::int_option("Green", menu::settings::SubmenuBarText.g, 0, 255);
		menu::int_option("Blue", menu::settings::SubmenuBarText.b, 0, 255);
		menu::int_option("Alpha", menu::settings::SubmenuBarText.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_SUBMENUBARRECT:
	{
		menu::title("Submenu Bar Background");

		menu::int_option("Red", menu::settings::SubmenuBarBackground.r, 0, 255);
		menu::int_option("Green", menu::settings::SubmenuBarBackground.g, 0, 255);
		menu::int_option("Blue", menu::settings::SubmenuBarBackground.b, 0, 255);
		menu::int_option("Alpha", menu::settings::SubmenuBarBackground.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_SUBMENUARROW:
	{
		menu::title("Submenu Arrow");

		menu::int_option("Red", menu::settings::SubmenuRect.r, 0, 255);
		menu::int_option("Green", menu::settings::SubmenuRect.g, 0, 255);
		menu::int_option("Blue", menu::settings::SubmenuRect.b, 0, 255);
		menu::int_option("Alpha", menu::settings::SubmenuRect.a, 0, 255);
	}
	break;

	case SETTINGS_THEME_OPTIONTEXT:
	{
		menu::title("Option Text");

		menu::option("Unselected:");
		menu::int_option("Red", menu::settings::OptionUnselectedText.r, 0, 255);
		menu::int_option("Green", menu::settings::OptionUnselectedText.g, 0, 255);
		menu::int_option("Blue", menu::settings::OptionUnselectedText.b, 0, 255);
		menu::int_option("Alpha", menu::settings::OptionUnselectedText.a, 0, 255);

		menu::option("Selected:");
		menu::int_option("Red", menu::settings::OptionSelectedText.r, 0, 255);
		menu::int_option("Green", menu::settings::OptionSelectedText.g, 0, 255);
		menu::int_option("Blue", menu::settings::OptionSelectedText.b, 0, 255);
		menu::int_option("Alpha", menu::settings::OptionSelectedText.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_OPTIONRECT:
	{
		menu::title("Option Background");

		menu::option("Unselected:");
		menu::int_option("Red", menu::settings::OptionUnselectedBackground.r, 0, 255);
		menu::int_option("Green", menu::settings::OptionUnselectedBackground.g, 0, 255);
		menu::int_option("Blue", menu::settings::OptionUnselectedBackground.b, 0, 255);
		menu::int_option("Alpha", menu::settings::OptionUnselectedBackground.a, 0, 255);

		menu::option("Selected:");
		menu::int_option("Red", menu::settings::OptionSelectedBackground.r, 0, 255);
		menu::int_option("Green", menu::settings::OptionSelectedBackground.g, 0, 255);
		menu::int_option("Blue", menu::settings::OptionSelectedBackground.b, 0, 255);
		menu::int_option("Alpha", menu::settings::OptionSelectedBackground.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_FOOTERTEXT:
	{
		menu::title("Footer Text");

		menu::option("Text:");
		menu::int_option("Red", menu::settings::FooterText.r, 0, 255);
		menu::int_option("Green", menu::settings::FooterText.g, 0, 255);
		menu::int_option("Blue", menu::settings::FooterText.b, 0, 255);
		menu::int_option("Alpha", menu::settings::FooterText.a, 0, 255);

		menu::option("Sprite:");
		menu::int_option("Red", menu::settings::FooterSprite.r, 0, 255);
		menu::int_option("Green", menu::settings::FooterSprite.g, 0, 255);
		menu::int_option("Blue", menu::settings::FooterSprite.b, 0, 255);
		menu::int_option("Alpha", menu::settings::FooterSprite.a, 0, 255);
	}
	break;

	case SubMenus::SETTINGS_THEME_FOOTERRECT:
	{
		menu::title("Footer Background");

		menu::int_option("Red", menu::settings::FooterBackground.r, 0, 255);
		menu::int_option("Green", menu::settings::FooterBackground.g, 0, 255);
		menu::int_option("Blue", menu::settings::FooterBackground.b, 0, 255);
		menu::int_option("Alpha", menu::settings::FooterBackground.a, 0, 255);
	}
	break;
	}
	menu::end();
}

void ScriptMain() 
{
	srand(GetTickCount());

	while (pico::g_running)
	{
		functions::looped::features();
		pico_menu();
		menu::checks::keys();
		menu::reset_optioncount();

		WAIT(0);
	}
}