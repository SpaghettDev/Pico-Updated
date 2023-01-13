#include "stdafx.hpp"
#include "menu_class.hpp"
#include "input_hook.hpp"

namespace
{
	bool load_texture_dict(std::string dict_name)
	{
		while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict_name.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict_name.c_str(), true);
			WAIT(0);
		}

		return GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict_name.c_str());
	}
}

namespace menu
{
	namespace Drawing
	{
		void text(const char* text, RGBAF rgbaf, Vector2 position, SizeVector size, bool center, bool right)
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
			if (load_texture_dict(streamedtexture.c_str()))
				GRAPHICS::DRAW_SPRITE(streamedtexture.c_str(), textureName.c_str(), x, y, width, height, rotation, r, g, b, a, NULL, NULL);
		}

		void rect(RGBA rgba, Vector2 position, SizeVector size)
		{
			GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a, NULL);
		}
	}

	namespace settings
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
		Drawing::text("Pico", settings::TitleText, { settings::menuX, 0.095f - 0.035f }, { 0.85f, 0.85f }, true, false);
		Drawing::rect(settings::TitleBackground, { settings::menuX, 0.1175f - 0.035f }, { settings::menuWidth, 0.085f });

		// Submenu Bar
		Drawing::rect(settings::SubmenuBarBackground, { settings::menuX, 0.1415f }, { settings::menuWidth, 0.035f });
		char BarText[64]{};
		strncpy_s(BarText, sizeof(BarText), title, 64);
		std::transform(std::begin(BarText), std::end(BarText), std::begin(BarText), [](char c) { return static_cast<char>(toupper(c)); });
		Drawing::text(BarText, settings::SubmenuBarText, { settings::menuX, 0.125f }, { 0.5f, 0.5f }, true, false);

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

		// Disable Controls
		for (const auto& control : controls)
			PAD::DISABLE_CONTROL_ACTION(ControlTypes::FRONTEND_CONTROL, control, true);
	}

	bool option(const char* option)
	{
		settings::optionCount++;
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
		{
			onThis
				? Drawing::text(option, settings::OptionSelectedText, { settings::menuX - 0.1f, (settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::text(option, settings::OptionUnselectedText, { settings::menuX - 0.1f, (settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(settings::OptionUnselectedBackground, { settings::menuX, (settings::optionCount) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });
			
			if (onThis)
				Drawing::rect(settings::OptionSelectedBackground, { settings::menuX, (settings::optionCount) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });
		}
		else if (settings::optionCount > (settings::currentOption - settings::maxVisOptions) && settings::optionCount <= settings::currentOption)
		{
			onThis
				? Drawing::text(option, settings::OptionSelectedText, { settings::menuX - 0.1f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::text(option, settings::OptionUnselectedText, { settings::menuX - 0.1f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(settings::OptionUnselectedBackground, { settings::menuX,  (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });
			
			if (onThis)
				Drawing::rect(settings::OptionSelectedBackground, { settings::menuX,  (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });
		}

		return onThis && settings::selectPressed;
	}

	bool option(const char* option, bool& toggle_bool)
	{
		settings::optionCount++;
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
		{
			onThis
				? Drawing::text(option, settings::OptionSelectedText, { settings::menuX - 0.1f, (settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::text(option, settings::OptionUnselectedText, { settings::menuX - 0.1f, (settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(settings::OptionUnselectedBackground, { settings::menuX, (settings::optionCount) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });

			if (onThis)
				Drawing::rect(settings::OptionSelectedBackground, { settings::menuX, (settings::optionCount) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });
		}
		else if (settings::optionCount > (settings::currentOption - settings::maxVisOptions) && settings::optionCount <= settings::currentOption)
		{
			onThis
				? Drawing::text(option, settings::OptionSelectedText, { settings::menuX - 0.1f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::text(option, settings::OptionUnselectedText, { settings::menuX - 0.1f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(settings::OptionUnselectedBackground, { settings::menuX,  (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });

			if (onThis)
				Drawing::rect(settings::OptionSelectedBackground, { settings::menuX,  (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });
		}

		toggle_bool = onThis && settings::selectPressed;
		return toggle_bool;
	}

	bool menu_option(const char* option_name, SubMenus newSub)
	{
		option(option_name);

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
			Drawing::rect(settings::SubmenuRect, { settings::menuX + (settings::menuWidth / 2) - 0.002f, (settings::optionCount) * 0.035f + 0.1415f }, { 0.004f, 0.035f });
		else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
			Drawing::rect(settings::SubmenuRect, { settings::menuX + (settings::menuWidth / 2) - 0.002f,  (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.1415f }, { 0.004f, 0.035f });

		if (settings::optionCount == settings::currentOption && settings::selectPressed)
		{
			MenuLevelHandler::MoveMenu(newSub);
			return true;
		}
		return false;
	}

	bool bool_option(const char* option_name, bool& toggle_bool)
	{
		option(option_name);

		if (toggle_bool)
		{
			if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
				Drawing::sprite("commonmenu", "common_medal", settings::menuX + 0.068f, (settings::optionCount * 0.035f + 0.141f), 0.014063f, 0.025f, 0, settings::SubmenuRect.r, settings::SubmenuRect.g, settings::SubmenuRect.b, settings::SubmenuRect.a);
			else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
				Drawing::sprite("commonmenu", "common_medal", settings::menuX + 0.068f, ((settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.141f), 0.014063f, 0.025f, 0, settings::SubmenuRect.r, settings::SubmenuRect.g, settings::SubmenuRect.b, settings::SubmenuRect.a);
		}
		else
		{
			if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
				Drawing::sprite("commonmenu", "common_medal", settings::menuX + 0.068f, (settings::optionCount * 0.035f + 0.141f), 0.014063f, 0.025f, 0, 102, 96, 96, 255);
			else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
				Drawing::sprite("commonmenu", "common_medal", settings::menuX + 0.068f, ((settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.141f), 0.014063f, 0.025f, 0, 102, 96, 96, 255);
		}

		if (settings::optionCount == settings::currentOption && settings::selectPressed)
		{
			toggle_bool = !toggle_bool;
			return true;
		}

		return false;
	}

	bool int_option(const char* option_name, int& _int, int min, int max)
	{
		option(option_name);
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::optionCount == settings::currentOption)
		{
			if (settings::leftPressed)
			{
				if (_int != min)
					_int--;
				else
					_int = max;
			}

			if (settings::rightPressed)
				_int < max ? _int++ : _int = min;
		}

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && settings::selectPressed;
	}

	bool int_option(const char* option_name, int& _int, int min, int max, int step)
	{
		option(option_name);
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::optionCount == settings::currentOption)
		{
			if (settings::leftPressed)
			{
				if (_int != min)
					_int -= step;
				else
					_int = max;
			}

			if (settings::rightPressed)
				_int < max ? _int += step : _int = min;
		}

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
			onThis
				? Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(_int) + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && settings::selectPressed;
	}

	bool float_option(const char* option_name, float& _float, float min, float max)
	{
		option(option_name);
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::optionCount == settings::currentOption)
		{
			if (settings::leftPressed)
				_float <= min ? _float = max : _float -= 0.1f;
			if (settings::rightPressed)
				_float >= max ? _float = min : _float += 0.1f;

			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}

		std::string String = std::to_string(_float);
		String = String.substr(0, 3);

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && settings::selectPressed;
	}

	bool float_option(const char* option_name, float& _float, float min, float max, float step)
	{
		option(option_name);
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::optionCount == settings::currentOption)
		{
			if (settings::leftPressed)
				_float <= min ? _float = max : _float -= step;

			if (settings::rightPressed)
				_float >= max ? _float = min : _float += step;

			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}
		std::string String = std::to_string(_float);
		String = String.substr(0, 3);

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
			onThis
				? Drawing::text(("<" + String + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + String + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && settings::selectPressed;
	}

	template<typename T>
	bool list_option(const char* option_name, std::vector<T> list, int& selected_option)
	{
		option(option_name);
		bool onThis = settings::currentOption == settings::optionCount;

		if (settings::optionCount == settings::currentOption)
		{
			if (settings::leftPressed)
			{
				if (selected_option != 0)
					selected_option--;
				else 
					selected_option = 0;
			}

			if (settings::rightPressed)
				selected_option < static_cast<int>(list.size() - 1) ? selected_option++ : selected_option = 0;
		}

		if (settings::currentOption <= settings::maxVisOptions && settings::optionCount <= settings::maxVisOptions)
			onThis
				? Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (settings::optionCount > settings::currentOption - settings::maxVisOptions && settings::optionCount <= settings::currentOption)
			onThis
				? Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), settings::OptionSelectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::text(("<" + std::to_string(list[selected_option]) + ">").c_str(), settings::OptionUnselectedText, { settings::menuX + 0.068f, (settings::optionCount - (settings::currentOption - settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && settings::selectPressed;
	}

	void end()
	{
		if (settings::optionCount >= settings::maxVisOptions)
		{
			Drawing::text("PAID", settings::FooterText, { settings::menuX - (settings::menuWidth / 2) + 0.005f, (settings::maxVisOptions + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::text((std::to_string(settings::currentOption) + "/" + std::to_string(settings::optionCount)).c_str(), settings::FooterText, { settings::menuX + (settings::menuWidth / 2) - 0.03f, (settings::maxVisOptions + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(settings::FooterBackground, { settings::menuX, (settings::maxVisOptions + 1) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });

			if (settings::currentOption == 1)
				Drawing::sprite("commonmenu", "arrowright", settings::menuX, ((settings::maxVisOptions + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 90, settings::FooterSprite.r, settings::FooterSprite.g, settings::FooterSprite.b, settings::FooterSprite.a);
			else if (settings::currentOption == settings::optionCount)
				Drawing::sprite("commonmenu", "arrowright", settings::menuX, ((settings::maxVisOptions + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 270, settings::FooterSprite.r, settings::FooterSprite.g, settings::FooterSprite.b, settings::FooterSprite.a);
			else
				Drawing::sprite("commonmenu", "shop_arrows_upanddown", settings::menuX, ((settings::maxVisOptions + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, settings::FooterSprite.r, settings::FooterSprite.g, settings::FooterSprite.b, settings::FooterSprite.a);
		}
		else if (settings::optionCount > 0)
		{
			Drawing::text("PAID", settings::FooterText, { settings::menuX - (settings::menuWidth / 2) + 0.005f, (settings::optionCount + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::text((std::to_string(settings::currentOption) + "/" + std::to_string(settings::optionCount)).c_str(), settings::FooterText, { settings::menuX + (settings::menuWidth / 2) - 0.03f, (settings::optionCount + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::rect(settings::FooterBackground, { settings::menuX, (settings::optionCount + 1) * 0.035f + 0.1415f }, { settings::menuWidth, 0.035f });

			if (settings::currentOption == 1 && settings::optionCount > 1)
				Drawing::sprite("commonmenu", "arrowright", settings::menuX, ((settings::optionCount + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 90, settings::FooterSprite.r, settings::FooterSprite.g, settings::FooterSprite.b, settings::FooterSprite.a);
			else if (settings::currentOption == settings::optionCount && settings::optionCount > 1)
				Drawing::sprite("commonmenu", "arrowright", settings::menuX, ((settings::optionCount + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 270, settings::FooterSprite.r, settings::FooterSprite.g, settings::FooterSprite.b, settings::FooterSprite.a);
			else
				Drawing::sprite("commonmenu", "shop_arrows_upanddown", settings::menuX, ((settings::optionCount + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, settings::FooterSprite.r, settings::FooterSprite.g, settings::FooterSprite.b, settings::FooterSprite.a);
		}
	}
	
	void reset_optioncount()
	{
		settings::optionCount = 0;
	}

	namespace checks
	{
		void keys()
		{
			settings::selectPressed = false;
			settings::leftPressed = false;
			settings::rightPressed = false;

			if ((GetTickCount64() - settings::keyPressPreviousTick) > settings::keyPressDelay)
			{
				if (InputHook::get_key(settings::openKey))
				{
					settings::menuLevel == SubMenus::NOTHING
						? MenuLevelHandler::MoveMenu(SubMenus::MAIN)
						: MenuLevelHandler::CloseMenu();

					settings::keyPressPreviousTick = GetTickCount64();
				}
				else if (InputHook::get_key(settings::backKey))
				{
					if (settings::menuLevel > SubMenus::NOTHING)
						MenuLevelHandler::BackMenu();

					settings::keyPressPreviousTick = GetTickCount64();
				}
				else if (InputHook::get_key(settings::upKey))
				{
					settings::currentOption > 1
						? settings::currentOption--
						: settings::currentOption = settings::optionCount;

					settings::keyPressPreviousTick = GetTickCount64();
				}
				else if (InputHook::get_key(settings::downKey))
				{
					settings::currentOption < settings::optionCount
						? settings::currentOption++
						: settings::currentOption = 1;

					settings::keyPressPreviousTick = GetTickCount64();
				}

				settings::leftPressed = InputHook::get_key(settings::leftKey);
				settings::rightPressed = InputHook::get_key(settings::rightKey);
				settings::selectPressed = InputHook::get_key(settings::selectKey);
				settings::keyPressPreviousTick = (settings::leftPressed || settings::rightPressed || settings::selectPressed)
					? GetTickCount64()
					: settings::keyPressPreviousTick;
			}
		}
	}

	namespace MenuLevelHandler
	{
		void MoveMenu(SubMenus menu)
		{
			settings::menusArray[settings::menuLevel] = settings::currentMenu;
			settings::optionsArray[settings::menuLevel] = settings::currentOption;
			settings::menuLevel = static_cast<SubMenus>(static_cast<int>(settings::menuLevel) + 1);
			settings::currentMenu = menu;
			settings::currentOption = 1;
		}

		void BackMenu()
		{
			settings::menuLevel = static_cast<SubMenus>(static_cast<int>(settings::menuLevel) - 1);
			settings::currentMenu = settings::menusArray[settings::menuLevel];
			settings::currentOption = settings::optionsArray[settings::menuLevel];
		}

		void CloseMenu()
		{
			settings::menuLevel = SubMenus::NOTHING;
			settings::currentMenu = settings::menusArray[settings::menuLevel];
			settings::currentOption = settings::optionsArray[settings::menuLevel];
		}
	}
}
