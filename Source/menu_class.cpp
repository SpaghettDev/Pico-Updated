#include "stdafx.hpp"
#include "utils.hpp"

namespace MenuClass
{
	namespace Drawing
	{
		void text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool right)
		{
			HUD::SET_TEXT_CENTRE(center);
			HUD::SET_TEXT_RIGHT_JUSTIFY(right);
			HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
			HUD::SET_TEXT_FONT(rgbaf.f);
			HUD::SET_TEXT_SCALE(size.w, size.h);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, NULL);
		}

		void sprite(std::string streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
		{
			if (utils::load_texture_dict(streamedtexture.c_str()))
				GRAPHICS::DRAW_SPRITE(streamedtexture.c_str(), textureName.c_str(), x, y, width, height, rotation, r, g, b, a, NULL, NULL);
		}

		void rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
		{
			GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a, NULL);
		}
	}

	namespace Settings
	{
		float menuX = 0.85f;
		float menuWidth = 0.21f;
		bool selectPressed = false;
		bool leftPressed = false;
		bool rightPressed = false;
		int maxVisOptions = 11;
		int currentOption = 0;
		int optionCount = 0;
		SubMenus currentMenu;
		SubMenus menuLevel = SubMenus::NOTHING;
		std::array<int, 1000> optionsArray;
		std::array<SubMenus, 1000> menusArray;

		RGBAF TitleText{ 255, 255, 255, 255, 1 };
		RGBA TitleBackground{ 3, 140, 252, 255 };
		RGBAF SubmenuBarText{ 255, 255, 255, 255, 4 };
		RGBA SubmenuBarBackground{ 0, 0, 0, 190 };
		RGBA SubmenuRect{ 3, 140, 252, 255 };
		RGBAF OptionUnselectedText{ 255, 255, 255, 255, 4 };
		RGBAF OptionSelectedText{ 10, 10, 10, 255, 4 };
		RGBA OptionUnselectedBackground{ 0, 0, 0, 160 };
		RGBA OptionSelectedBackground{ 255, 255, 255, 255 };
		RGBAF FooterText{ 255, 255, 255, 255, 4 };
		RGBA FooterBackground{ 0, 0, 0, 220 };
		RGBA FooterSprite{ 255, 255, 255, 255 };

		int keyPressDelay = 160;
		ULONGLONG keyPressPreviousTick = GetTickCount64();
		const int openKey = VK_F4;
		const int backKey = VK_BACK;
		const int upKey = VK_UP;
		const int downKey = VK_DOWN;
		const int leftKey = VK_LEFT;
		const int rightKey = VK_RIGHT;
		const int selectKey = VK_RETURN;
	}

	void title(const char* title)
	{
		// Title Bar
		Drawing::text("Pico", Settings::TitleText, { Settings::menuX, 0.095f - 0.035f }, { 0.85f, 0.85f }, true, false);
		Drawing::rect(Settings::TitleBackground, { Settings::menuX, 0.1175f - 0.035f }, { Settings::menuWidth, 0.085f });

		// Submenu Bar
		Drawing::rect(Settings::SubmenuBarBackground, { Settings::menuX, 0.1415f }, { Settings::menuWidth, 0.035f });
		char BarText[64]{};
		strncpy_s(BarText, sizeof(BarText), title, 64);
		std::transform(std::begin(BarText), std::end(BarText), std::begin(BarText), [](char c) { return static_cast<char>(toupper(c)); });
		Drawing::text(BarText, Settings::SubmenuBarText, { Settings::menuX, 0.125f }, { 0.5f, 0.5f }, true, false);

		// Disable Controls
		HUD::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(false);

		const ControllerInputs controls[] = {
			ControllerInputs::INPUT_NEXT_CAMERA,
			ControllerInputs::INPUT_CHARACTER_WHEEL,
			ControllerInputs::INPUT_MELEE_ATTACK_LIGHT,
			ControllerInputs::INPUT_MELEE_ATTACK_HEAVY,
			ControllerInputs::INPUT_MULTIPLAYER_INFO,
			ControllerInputs::INPUT_PHONE,
			ControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE,
			ControllerInputs::INPUT_VEH_CIN_CAM,
			ControllerInputs::INPUT_MAP_POI,
			ControllerInputs::INPUT_PHONE,
			ControllerInputs::INPUT_VEH_RADIO_WHEEL,
			ControllerInputs::INPUT_VEH_HEADLIGHT
		};

		for (const auto& control : controls)
			PAD::DISABLE_CONTROL_ACTION(ControlTypes::FRONTEND_CONTROL, control, true);
	}

	bool option(const char* option)
	{
		Settings::optionCount++;
		bool onThis = Settings::currentOption == Settings::optionCount;

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		{
			onThis
				? Drawing::text(option, Settings::OptionSelectedText, { Settings::menuX - 0.1f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::text(option, Settings::OptionUnselectedText, { Settings::menuX - 0.1f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(Settings::OptionUnselectedBackground, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });
			
			if (onThis)
				Drawing::rect(Settings::OptionSelectedBackground, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });
		}
		else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
		{
			onThis
				? Drawing::text(option, Settings::OptionSelectedText, { Settings::menuX - 0.1f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::text(option, Settings::OptionUnselectedText, { Settings::menuX - 0.1f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(Settings::OptionUnselectedBackground, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });
			
			if (onThis)
				Drawing::rect(Settings::OptionSelectedBackground, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });
		}

		return onThis && Settings::selectPressed;
	}

	bool menu_option(const char* option_name, SubMenus newSub)
	{
		option(option_name);

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::rect(Settings::SubmenuRect, { Settings::menuX + (Settings::menuWidth / 2) - 0.002f, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.004f, 0.035f });
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::rect(Settings::SubmenuRect, { Settings::menuX + (Settings::menuWidth / 2) - 0.002f,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { 0.004f, 0.035f });

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed)
		{
			MenuLevelHandler::MoveMenu(newSub);
			return true;
		}
		return false;
	}

	bool bool_option(const char* option_name, bool& b00l)
	{
		option(option_name);

		if (b00l)
		{
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Drawing::sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, (Settings::optionCount * 0.035f + 0.141f), 0.014063f, 0.025f, 0, Settings::SubmenuRect.r, Settings::SubmenuRect.g, Settings::SubmenuRect.b, Settings::SubmenuRect.a);
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Drawing::sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.141f), 0.014063f, 0.025f, 0, Settings::SubmenuRect.r, Settings::SubmenuRect.g, Settings::SubmenuRect.b, Settings::SubmenuRect.a);
		}
		else
		{
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Drawing::sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, (Settings::optionCount * 0.035f + 0.141f), 0.014063f, 0.025f, 0, 102, 96, 96, 255);
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Drawing::sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.141f), 0.014063f, 0.025f, 0, 102, 96, 96, 255);
		}

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed)
		{
			b00l = !b00l;;
			return true;
		}
		return false;
	}

	bool int_option(const char* option_name, int& _int, int min, int max)
	{
		option(option_name);
		bool onThis = Settings::currentOption == Settings::optionCount;

		if (Settings::optionCount == Settings::currentOption)
		{
			if (Settings::leftPressed)
			{
				if (_int != min)
					_int--;
				else
					_int = max;
			}

			if (Settings::rightPressed)
				_int < max ? _int++ : _int = min;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	bool int_option(const char* option_name, int& _int, int min, int max, int step)
	{
		option(option_name);
		bool onThis = Settings::currentOption == Settings::optionCount;

		if (Settings::optionCount == Settings::currentOption)
		{
			if (Settings::leftPressed)
			{
				if (_int != min)
					_int -= step;
				else
					_int = max;
			}

			if (Settings::rightPressed)
				_int < max ? _int += step : _int = min;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	bool float_option(const char* option_name, float& _float, float min, float max)
	{
		option(option_name);
		bool onThis = Settings::currentOption == Settings::optionCount;

		if (Settings::optionCount == Settings::currentOption)
		{
			if (Settings::leftPressed)
				_float <= min ? _float = max : _float -= 0.1f;
			if (Settings::rightPressed)
				_float >= max ? _float = min : _float += 0.1f;

			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}

		std::string String = std::to_string(_float);
		String = String.substr(0, 3);

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	bool float_option(const char* option_name, float& _float, float min, float max, float step)
	{
		option(option_name);
		bool onThis = Settings::currentOption == Settings::optionCount;

		if (Settings::optionCount == Settings::currentOption)
		{
			if (Settings::leftPressed)
				_float <= min ? _float = max : _float -= step;

			if (Settings::rightPressed)
				_float >= max ? _float = min : _float += step;

			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}
		std::string String = std::to_string(_float);
		String = String.substr(0, 3);

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	template<typename T>
	bool list_option(const char* option_name, std::vector<T> list, int& selected_option)
	{
		option(option_name);
		bool onThis = Settings::currentOption == Settings::optionCount;

		if (Settings::optionCount == Settings::currentOption)
		{
			if (Settings::leftPressed)
			{
				if (selected_option != 0)
					selected_option--;
				else 
					selected_option = 0;
			}

			if (Settings::rightPressed)
				selected_option < static_cast<int>(list.size() - 1) ? selected_option++ : selected_option = 0;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	void end()
	{
		if (Settings::optionCount >= Settings::maxVisOptions)
		{
			Drawing::text("PAID", Settings::FooterText, { Settings::menuX - (Settings::menuWidth / 2) + 0.005f, (Settings::maxVisOptions + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::text((std::to_string(Settings::currentOption) + "/" + std::to_string(Settings::optionCount)).c_str(), Settings::FooterText, { Settings::menuX + (Settings::menuWidth / 2) - 0.03f, (Settings::maxVisOptions + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(Settings::FooterBackground, { Settings::menuX, (Settings::maxVisOptions + 1) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });

			if (Settings::currentOption == 1)
				Drawing::sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 90, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else if (Settings::currentOption == Settings::optionCount)
				Drawing::sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 270, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else
				Drawing::sprite("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
		}
		else if (Settings::optionCount > 0)
		{
			Drawing::text("PAID", Settings::FooterText, { Settings::menuX - (Settings::menuWidth / 2) + 0.005f, (Settings::optionCount + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::text((std::to_string(Settings::currentOption) + "/" + std::to_string(Settings::optionCount)).c_str(), Settings::FooterText, { Settings::menuX + (Settings::menuWidth / 2) - 0.03f, (Settings::optionCount + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(Settings::FooterBackground, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });

			if (Settings::currentOption == 1 && Settings::optionCount > 1)
				Drawing::sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 90, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else if (Settings::currentOption == Settings::optionCount && Settings::optionCount > 1)
				Drawing::sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 270, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else
				Drawing::sprite("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
		}
	}
	
	void reset_optioncount()
	{
		Settings::optionCount = 0;
	}

	namespace Checks
	{
		void keys()
		{
			Settings::selectPressed = false;
			Settings::leftPressed = false;
			Settings::rightPressed = false;

			if ((GetTickCount64() - Settings::keyPressPreviousTick) > Settings::keyPressDelay)
			{
				if (InputHook::get_key(Settings::openKey))
				{
					Settings::menuLevel == SubMenus::NOTHING
						? MenuLevelHandler::MoveMenu(SubMenus::MAIN)
						: MenuLevelHandler::CloseMenu();

					Settings::keyPressPreviousTick = GetTickCount64();
				}
				else if (InputHook::get_key(Settings::backKey))
				{
					if (Settings::menuLevel > SubMenus::NOTHING)
						MenuLevelHandler::BackMenu();

					Settings::keyPressPreviousTick = GetTickCount64();
				}
				else if (InputHook::get_key(Settings::upKey))
				{
					Settings::currentOption > 1
						? Settings::currentOption--
						: Settings::currentOption = Settings::optionCount;

					Settings::keyPressPreviousTick = GetTickCount64();
				}
				else if (InputHook::get_key(Settings::downKey))
				{
					Settings::currentOption < Settings::optionCount
						? Settings::currentOption++
						: Settings::currentOption = 1;

					Settings::keyPressPreviousTick = GetTickCount64();
				}

				Settings::leftPressed = InputHook::get_key(Settings::leftKey);
				Settings::rightPressed = InputHook::get_key(Settings::rightKey);
				Settings::selectPressed = InputHook::get_key(Settings::selectKey);
				Settings::keyPressPreviousTick = (Settings::leftPressed || Settings::rightPressed || Settings::selectPressed)
					? GetTickCount64()
					: Settings::keyPressPreviousTick;
			}
		}
	}

	namespace MenuLevelHandler
	{
		void MoveMenu(SubMenus menu)
		{
			Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
			Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
			Settings::menuLevel = static_cast<SubMenus>(static_cast<int>(Settings::menuLevel) + 1);
			Settings::currentMenu = menu;
			Settings::currentOption = 1;
		}

		void BackMenu()
		{
			Settings::menuLevel = static_cast<SubMenus>(static_cast<int>(Settings::menuLevel) - 1);
			Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
			Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
		}

		void CloseMenu()
		{
			Settings::menuLevel = SubMenus::NOTHING;
			Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
			Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
		}
	}
}
