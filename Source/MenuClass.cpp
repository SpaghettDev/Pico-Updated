#include "stdafx.h"

namespace MenuClass
{
	namespace Drawing
	{
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool right)
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

		void Sprite(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
		{
			if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture.c_str()))
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture.c_str(), false);
			else
				GRAPHICS::DRAW_SPRITE(Streamedtexture.c_str(), textureName.c_str(), x, y, width, height, rotation, r, g, b, a, NULL, NULL);
		}

		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
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
		SubMenus menuLevel = Nothing;
		int optionsArray[1000];
		SubMenus menusArray[1000];

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
		int keyPressPreviousTick = GetTickCount();
		int openKey = VK_F4;
		int backKey = VK_BACK;
		int upKey = VK_UP;
		int downKey = VK_DOWN;
		int leftKey = VK_LEFT;
		int rightKey = VK_RIGHT;
		int selectKey = VK_RETURN;
	}

	void MenuClass::Title(const char* title)
	{
		// Title Bar
		Drawing::Text("Pico", Settings::TitleText, { Settings::menuX, 0.095f - 0.035f }, { 0.85f, 0.85f }, true, false);
		Drawing::Rect(Settings::TitleBackground, { Settings::menuX, 0.1175f - 0.035f, }, { Settings::menuWidth, 0.085f });

		// Submenu Bar
		Drawing::Rect(Settings::SubmenuBarBackground, { Settings::menuX, 0.1415f }, { Settings::menuWidth, 0.035f });
		char BarText[64] = {};
		std::strncpy(&BarText[0], title, sizeof(BarText) - 1);
		std::transform(std::begin(BarText), std::end(BarText), std::begin(BarText), [](char c) { return static_cast<char>(toupper(c)); });
		Drawing::Text(BarText, Settings::SubmenuBarText, { Settings::menuX, 0.125f }, { 0.5f, 0.5f }, true, false);

		// Disable Controls
		HUD::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(10);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(6);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(9);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(8);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
		PAD::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
	}

	bool Option(const char* option)
	{
		Settings::optionCount++;
		bool onThis = Settings::currentOption == Settings::optionCount ? true : false;

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		{
			onThis
				? Drawing::Text(option, Settings::OptionSelectedText, { Settings::menuX - 0.1f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::Text(option, Settings::OptionUnselectedText, { Settings::menuX - 0.1f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::Rect(Settings::OptionUnselectedBackground, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });
			onThis
				? Drawing::Rect(Settings::OptionSelectedBackground, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f })
				: NULL;
		}
		else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
		{
			onThis
				? Drawing::Text(option, Settings::OptionSelectedText, { Settings::menuX - 0.1f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false)
				: Drawing::Text(option, Settings::OptionUnselectedText, { Settings::menuX - 0.1f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::Rect(Settings::OptionUnselectedBackground, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });
			onThis
				? Drawing::Rect(Settings::OptionSelectedBackground, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f })
				: NULL;
		}

		return onThis && Settings::selectPressed;
	}

	bool MenuOption(const char* option, SubMenus newSub)
	{
		Option(option);

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Rect(Settings::SubmenuRect, { Settings::menuX + (Settings::menuWidth / 2) - 0.002f, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.004f, 0.035f });
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Rect(Settings::SubmenuRect, { Settings::menuX + (Settings::menuWidth / 2) - 0.002f,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f }, { 0.004f, 0.035f });

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed)
		{
			MenuLevelHandler::MoveMenu(newSub);
			return true;
		}
		return false;
	}

	bool Bool(const char* option, bool& b00l)
	{
		Option(option);

		if (b00l)
		{
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Drawing::Sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, (Settings::optionCount * 0.035f + 0.141f), 0.014063f, 0.025f, 0, Settings::SubmenuRect.r, Settings::SubmenuRect.g, Settings::SubmenuRect.b, Settings::SubmenuRect.a);
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Drawing::Sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.141f), 0.014063f, 0.025f, 0, Settings::SubmenuRect.r, Settings::SubmenuRect.g, Settings::SubmenuRect.b, Settings::SubmenuRect.a);
		}
		else
		{
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Drawing::Sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, (Settings::optionCount * 0.035f + 0.141f), 0.014063f, 0.025f, 0, 102, 96, 96, 255);
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Drawing::Sprite("commonmenu", "common_medal", Settings::menuX + 0.068f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.141f), 0.014063f, 0.025f, 0, 102, 96, 96, 255);
		}

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed)
		{
			b00l = !b00l;;
			return true;
		}
		return false;
	}

	bool Int(const char* option, int& _int, int min, int max)
	{
		Option(option);
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
			? Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
			: Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
			? Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
			: Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	bool Int(const char* option, int& _int, int min, int max, int step)
	{
		Option(option);
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
			? Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
			: Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
			? Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
			: Drawing::Text(("<" + std::to_string(_int) + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

#pragma warning(disable: 4244)
	bool Float(const char* option, float& _float, float min, float max)
	{
		Option(option);
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
				? Drawing::Text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::Text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::Text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::Text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	bool Float(const char* option, float& _float, float min, float max, float step)
	{
		Option(option);
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
				? Drawing::Text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false)
				: Drawing::Text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			onThis
				? Drawing::Text(("<" + String + ">").c_str(), Settings::OptionSelectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false)
				: Drawing::Text(("<" + String + ">").c_str(), Settings::OptionUnselectedText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true, false);

		return onThis && Settings::selectPressed;
	}

	void End()
	{
		if (Settings::optionCount >= Settings::maxVisOptions)
		{
			Drawing::Text("PAID", Settings::FooterText, { Settings::menuX - (Settings::menuWidth / 2) + 0.005f, (Settings::maxVisOptions + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::Text((std::to_string(Settings::currentOption) + "/" + std::to_string(Settings::optionCount)).c_str(), Settings::FooterText, { Settings::menuX + (Settings::menuWidth / 2) - 0.03f, (Settings::maxVisOptions + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::Rect(Settings::FooterBackground, { Settings::menuX, (Settings::maxVisOptions + 1) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });

			if (Settings::currentOption == 1)
				Drawing::Sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 90, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else if (Settings::currentOption == Settings::optionCount)
				Drawing::Sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 270, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else
				Drawing::Sprite("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::maxVisOptions + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
		}
		else if (Settings::optionCount > 0)
		{
			Drawing::Text("PAID", Settings::FooterText, { Settings::menuX - (Settings::menuWidth / 2) + 0.005f, (Settings::optionCount + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::Text((std::to_string(Settings::currentOption) + "/" + std::to_string(Settings::optionCount)).c_str(), Settings::FooterText, { Settings::menuX + (Settings::menuWidth / 2) - 0.03f, (Settings::optionCount + 1) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false, false);
			Drawing::Rect(Settings::FooterBackground, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { Settings::menuWidth, 0.035f });

			if (Settings::currentOption == 1 && Settings::optionCount > 1)
				Drawing::Sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 90, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else if (Settings::currentOption == Settings::optionCount && Settings::optionCount > 1)
				Drawing::Sprite("commonmenu", "arrowright", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.142f), 0.010f, 0.0175f, 270, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
			else
				Drawing::Sprite("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::FooterSprite.r, Settings::FooterSprite.g, Settings::FooterSprite.b, Settings::FooterSprite.a);
		}
	}

	namespace Checks
	{
		void Keys()
		{
			Settings::selectPressed = false;
			Settings::leftPressed = false;
			Settings::rightPressed = false;
			if (static_cast<int>(GetTickCount()) - Settings::keyPressPreviousTick > Settings::keyPressDelay)
			{
				if (GetAsyncKeyState(Settings::openKey))
				{
					Settings::menuLevel == 0
						? MenuLevelHandler::MoveMenu(SubMenus::Main)
						: MenuLevelHandler::CloseMenu();

					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (GetAsyncKeyState(Settings::backKey))
				{
					if (Settings::menuLevel > Nothing)
						MenuLevelHandler::BackMenu();
			
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (GetAsyncKeyState(Settings::upKey))
				{
					Settings::currentOption > 1
						? Settings::currentOption--
						: Settings::currentOption = Settings::optionCount;
				
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (GetAsyncKeyState(Settings::downKey))
				{
					Settings::currentOption < Settings::optionCount
						? Settings::currentOption++
						: Settings::currentOption = 1;
				
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (GetAsyncKeyState(Settings::leftKey))
				{
					Settings::leftPressed = true;
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (GetAsyncKeyState(Settings::rightKey))
				{
					Settings::rightPressed = true;
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (GetAsyncKeyState(Settings::selectKey))
				{
					Settings::selectPressed = true;
					Settings::keyPressPreviousTick = GetTickCount();
				}
			}
			Settings::optionCount = 0;
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

		void MenuClass::MenuLevelHandler::BackMenu()
		{
			Settings::menuLevel = static_cast<SubMenus>(static_cast<int>(Settings::menuLevel) - 1);
			Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
			Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
		}

		void MenuClass::MenuLevelHandler::CloseMenu()
		{
			Settings::menuLevel = SubMenus::Nothing;
			Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
			Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
		}
	}
}
