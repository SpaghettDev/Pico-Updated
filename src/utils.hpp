#pragma once
#include "stdafx.hpp"

namespace
{
	using byte = unsigned char;

	constexpr size_t patch_size = 24;
	static std::once_flag once_flag;
	static std::array<byte, patch_size> backup;
	void setup_backup()
	{
		memcpy(backup.data(), g_hooking.m_ModelSpawnBypass, patch_size);
	}
}

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

	bool is_model_a_car(Hash model)
	{
		return
			STREAMING::IS_MODEL_VALID(model) &&
			STREAMING::IS_MODEL_A_VEHICLE(model);
	}

	bool is_model_a_ped(Hash model)
	{
		return
			STREAMING::IS_MODEL_VALID(model) &&
			STREAMING::IS_MODEL_A_PED(model);
	}

	std::pair<KeyboardState, std::string> keyboard_input(std::string example_text, int max_length)
	{
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "FMMC_KEY_TIP1", "", example_text.data(), "", "", "", max_length);

		while (
			MISC::UPDATE_ONSCREEN_KEYBOARD() == KeyboardState::STILL_EDITING &&
			(
				MISC::UPDATE_ONSCREEN_KEYBOARD() != KeyboardState::CANCELLED_EDITING ||
				MISC::UPDATE_ONSCREEN_KEYBOARD() != KeyboardState::NOT_ACTIVE
			)
			)
			WAIT(0);

		if (MISC::UPDATE_ONSCREEN_KEYBOARD() == KeyboardState::FINISHED_EDITING)
			return { KeyboardState::FINISHED_EDITING, MISC::GET_ONSCREEN_KEYBOARD_RESULT() };

		WAIT(1);
		return { KeyboardState::CANCELLED_EDITING, "" };
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

	Entity apply_model_spawn_bypass(std::function<Entity()> callback)
	{
		std::call_once(once_flag, setup_backup);
		memset(g_hooking.m_ModelSpawnBypass, 0x90, patch_size);
		Entity result = callback();
		memcpy(g_hooking.m_ModelSpawnBypass, backup.data(), patch_size);

		return result;
	}

	int get_num_of_elems(const std::vector<std::string_view>& vec, const std::regex& rx)
	{
		int num = 0;

		for (const auto& str : vec)
			if (std::regex_match(str.data(), rx))
				num++;

		return num;
	}
	
	int get_num_of_elems(const std::vector<structs::spawned_obj>& vec, const std::regex& rx)
	{
		int num = 0;

		for (const auto& str : vec)
			if (std::regex_match(str.name.data(), rx))
				num++;

		return num;
	}
	
	int get_num_of_elems(const std::vector<structs::spawned_ped>& vec, const std::regex& rx)
	{
		int num = 0;

		for (const auto& str : vec)
			if (std::regex_match(str.name.data(), rx))
				num++;

		return num;
	}
	
	int get_num_of_elems(const std::vector<std::string_view>& vec, const std::string& str)
	{
		return get_num_of_elems(vec, std::regex(str));
	}
	
	int get_num_of_elems(const std::vector<structs::spawned_obj>& vec, const std::string& str)
	{
		return get_num_of_elems(vec, std::regex(str));
	}
	
	int get_num_of_elems(const std::vector<structs::spawned_ped>& vec, const std::string& str)
	{
		return get_num_of_elems(vec, std::regex(str));
	}


	namespace math
	{
		float deg_to_rad(float deg)
		{
			return static_cast<float>((3.14159265359 / 180) * deg);
		}

		float distance_between_vector3(Vector3 vec1, Vector3 vec2)
		{
			return static_cast<float>(
				sqrt(
					pow((vec1.x - vec2.x), 2) +
					pow((vec1.y - vec2.y), 2) +
					pow((vec1.z - vec2.z), 2)
				)
			);
		}

		Vector3 rotation_to_direction(Vector3 rotation)
		{
			float x = deg_to_rad(rotation.x);
			float num = abs(cos(x));
			float z = deg_to_rad(rotation.z);

			return {
				-sin(z) * num,
				cos(z) * num,
				sin(x)
			};
		}
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
			HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, false, true, -1);
		}
	}
}