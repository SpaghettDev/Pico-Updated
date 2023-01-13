#pragma once
#include "stdafx.hpp"

namespace functions::utils
{
	bool request_model(Hash model, int timeout = 1000)
	{
		if (STREAMING::HAS_MODEL_LOADED(model))
			return true;

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model) && i < timeout; i++)
		{
			STREAMING::REQUEST_MODEL(model);
			WAIT(0);
		}

		return STREAMING::HAS_MODEL_LOADED(model);
	}

	bool request_model(std::string model_name, int timeout = 1000)
	{
		return request_model(rage::joaat(model_name));
	}

	std::string keyboard_input(const char* example_text, int max_length)
	{
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "FMMC_KEY_TIP1", "", example_text, "", "", "", max_length);

		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == KeyboardStates::STILL_EDITING)
			WAIT(0);

		if (MISC::UPDATE_ONSCREEN_KEYBOARD() == KeyboardStates::FINISHED_EDITING)
			return MISC::GET_ONSCREEN_KEYBOARD_RESULT();

		WAIT(10);
		return "";
	}

	bool take_control_of(Entity ent, int timeout = 1000)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) || !*g_hooking.m_IsSessionStarted)
			return true;

		for (int i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < timeout; i++)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);
			WAIT(0);
		}

		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent))
			return false;

		int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

		return true;
	}

	namespace notify
	{
		// for colors and text options: https://pastebin.com/nqNYWMSB
		void above_map(std::string_view text)
		{
			HUD::SET_TEXT_OUTLINE();
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
		}

		void display_help_text(std::string_view text)
		{
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
			HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
		}
	}
}