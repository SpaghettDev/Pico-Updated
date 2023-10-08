#include "stdafx.hpp"
#include "menu_class.hpp"

using namespace pico;

namespace
{
	bool load_texture_dict(std::string_view dict_name)
	{
		while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict_name.data()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict_name.data(), true);
			WAIT(0);
		}

		return GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict_name.data());
	}
}

namespace menu
{
	namespace drawing
	{
		void text(std::string_view text, RGBAF rgbaf, Vector2 position, SizeVector size, bool center, bool right)
		{
			HUD::SET_TEXT_CENTRE(center);
			HUD::SET_TEXT_RIGHT_JUSTIFY(right);
			HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
			HUD::SET_TEXT_FONT(rgbaf.f);
			HUD::SET_TEXT_SCALE(size.w, size.h);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, NULL);
		}

		void sprite(std::string_view dict, std::string_view textureName, float x, float y, float width, float height, float rotation, RGBA rgba)
		{
			if (load_texture_dict(dict))
				GRAPHICS::DRAW_SPRITE(dict.data(), textureName.data(), x, y, width, height, rotation, rgba.r, rgba.g, rgba.b, rgba.a, NULL, NULL);
		}

		void rect(RGBA rgba, Vector2 position, SizeVector size)
		{
			GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a, NULL);
		}
	}

	namespace settings
	{
		float menu_x = .85f;
		float menu_width = .21f;
		int max_vis_options = 11;
		int current_option = 1;
		int previous_option = current_option;
		int option_count = 0;
		int seperator_count = 0;
		submenus current_menu = submenus::MAIN;
		submenus previous_menu = current_menu;
		submenus menu_level = submenus::MAIN;
		std::array<int, 1000> options_array;
		std::array<submenus, 1000> menus_array;
		bool menu_visible = false;
	}

	void title(std::string_view title)
	{
		// Title Bar
		drawing::text("Pico", g_json.m_settings.settings.theme.title_text, { settings::menu_x, .095f - .035f }, { .85f, .85f }, true, false);
		drawing::rect(g_json.m_settings.settings.theme.title_background, { settings::menu_x, .1175f - .035f }, { settings::menu_width, .085f });

		// Submenu Bar
		drawing::rect(g_json.m_settings.settings.theme.submenu_bar_background, { settings::menu_x, .1415f }, { settings::menu_width, .035f });
		char BarText[64]{};
		strncpy_s(BarText, sizeof(BarText), title.data(), 64);
		std::transform(std::begin(BarText), std::end(BarText), std::begin(BarText), [](char c) { return static_cast<char>(toupper(c)); });
		drawing::text(BarText, g_json.m_settings.settings.theme.submenu_bar_text, { settings::menu_x, .125f }, { .5f, .5f }, true, false);

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

	structs::button option(std::string_view option)
	{
		settings::option_count++;
		bool onThis = settings::current_option == settings::option_count;

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
		{
			onThis
				? drawing::text(option, g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x - .1f, (settings::option_count) * .035f + .125f }, { .45f, .45f }, false, false)
				: drawing::text(option, g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x - .1f, (settings::option_count) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::rect(g_json.m_settings.settings.theme.option_unselected_background, { settings::menu_x, (settings::option_count) * .035f + .1415f }, { settings::menu_width, .035f });
			
			if (onThis)
				drawing::rect(g_json.m_settings.settings.theme.option_selected_background, { settings::menu_x, (settings::option_count) * .035f + .1415f }, { settings::menu_width, .035f });
		}
		else if (settings::option_count > (settings::current_option - settings::max_vis_options) && settings::option_count <= settings::current_option)
		{
			onThis
				? drawing::text(option, g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x - .1f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .125f }, { .45f, .45f }, false, false)
				: drawing::text(option, g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x - .1f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::rect(g_json.m_settings.settings.theme.option_unselected_background, { settings::menu_x,  (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .1415f }, { settings::menu_width, .035f });

			if (onThis)
				drawing::rect(g_json.m_settings.settings.theme.option_selected_background, { settings::menu_x,  (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .1415f }, { settings::menu_width, .035f });
		}

		return { onThis, onThis && keys::select_pressed };
	}

	structs::button option(std::string_view option, bool& toggle_bool)
	{
		settings::option_count++;
		bool onThis = settings::current_option == settings::option_count;

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
		{
			onThis
				? drawing::text(option, g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x - .1f, (settings::option_count) * .035f + .125f }, { .45f, .45f }, false, false)
				: drawing::text(option, g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x - .1f, (settings::option_count) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::rect(g_json.m_settings.settings.theme.option_unselected_background, { settings::menu_x, (settings::option_count) * .035f + .1415f }, { settings::menu_width, .035f });

			if (onThis)
				drawing::rect(g_json.m_settings.settings.theme.option_selected_background, { settings::menu_x, (settings::option_count) * .035f + .1415f }, { settings::menu_width, .035f });
		}
		else if (settings::option_count > (settings::current_option - settings::max_vis_options) && settings::option_count <= settings::current_option)
		{
			onThis
				? drawing::text(option, g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x - .1f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .125f }, { .45f, .45f }, false, false)
				: drawing::text(option, g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x - .1f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::rect(g_json.m_settings.settings.theme.option_unselected_background, { settings::menu_x,  (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .1415f }, { settings::menu_width, .035f });

			if (onThis)
				drawing::rect(g_json.m_settings.settings.theme.option_selected_background, { settings::menu_x,  (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .1415f }, { settings::menu_width, .035f });
		}

		toggle_bool = onThis && keys::select_pressed;
		return { onThis, toggle_bool };
	}

	void seperator()
	{
		settings::option_count++; // allows for the option to actually exist
		settings::seperator_count++;

		if (settings::current_option == settings::option_count)
		{
			if (InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::up_key)))
				menu_level_handler::move_option(settings::current_option - 1);
			else
				menu_level_handler::move_option(settings::current_option + 1);
		}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			drawing::rect(g_json.m_settings.settings.theme.seperator_background, { settings::menu_x, (settings::option_count) * .035f + .1415f }, { settings::menu_width, .035f });
		
		else if (settings::option_count > (settings::current_option - settings::max_vis_options) && settings::option_count <= settings::current_option)
			drawing::rect(g_json.m_settings.settings.theme.seperator_background, { settings::menu_x,  (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .1415f }, { settings::menu_width, .035f });
	}

	structs::button menu_option(std::string_view option_name, submenus destination)
	{
		option(option_name);
		structs::button return_val{ false, false };

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			drawing::rect(g_json.m_settings.settings.theme.submenu_rect, { settings::menu_x + (settings::menu_width / 2) - .002f, (settings::option_count) * .035f + .1415f }, { .004f, .035f });
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			drawing::rect(g_json.m_settings.settings.theme.submenu_rect, { settings::menu_x + (settings::menu_width / 2) - .002f,  (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .1415f }, { .004f, .035f });

		if (settings::option_count == settings::current_option)
			return_val.hovered = true;

		if (settings::option_count == settings::current_option && keys::select_pressed)
		{
			menu_level_handler::move_menu(destination);
			return_val.clicked = true;
		}
		return return_val;
	}

	structs::button bool_option(std::string_view option_name, bool& toggle_bool)
	{
		option(option_name);
		structs::button return_val{ false, false };

		if (toggle_bool)
		{
			if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
				drawing::sprite("commonmenu", "common_medal", settings::menu_x + .068f, (settings::option_count * .035f + .141f), .014063f, .025f, 0, g_json.m_settings.settings.theme.submenu_rect);
			else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
				drawing::sprite("commonmenu", "common_medal", settings::menu_x + .068f, ((settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .141f), .014063f, .025f, 0, g_json.m_settings.settings.theme.submenu_rect);
		}
		else
		{
			if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
				drawing::sprite("commonmenu", "common_medal", settings::menu_x + .068f, (settings::option_count * .035f + .141f), .014063f, .025f, 0, { 102, 96, 96, 255 });
			else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
				drawing::sprite("commonmenu", "common_medal", settings::menu_x + .068f, ((settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .141f), .014063f, .025f, 0, { 102, 96, 96, 255 });
		}

		if (settings::option_count == settings::current_option)
			return_val.hovered = true;

		if (settings::option_count == settings::current_option && keys::select_pressed)
		{
			toggle_bool = !toggle_bool;
			return_val.clicked = true;
		}

		return return_val;
	}

	structs::button int_option(std::string_view option_name, int& out_int, int min, int max, int step)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
				out_int <= min
					? out_int = max
					: out_int -= step;

			if (keys::right_pressed)
				out_int >= max
					? out_int = min
					: out_int += step;
		}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}
	
	structs::button int_option(std::string_view option_name, int& out_int, int step)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
				out_int -= step;

			if (keys::right_pressed)
				out_int += step;
		}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", std::to_string(out_int)), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}

	structs::button float_option(std::string_view option_name, float& out_float, float min, float max, float step, int precision)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
				out_float <= min
					? out_float = max
					: out_float -= step;

			if (keys::right_pressed)
				out_float >= max
					? out_float = min
					: out_float += step;

			out_float < min
				? out_float = max
				: out_float > max
					? out_float = min
					: NULL;
		}

		std::string float_str = std::to_string(out_float);
		if (std::size_t dot_ind = float_str.find("."); dot_ind != std::string::npos)
			float_str = float_str.substr(0, (dot_ind + 1) + precision);

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}
	
	structs::button float_option(std::string_view option_name, float& out_float, float step, int precision)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
				out_float -= step;

			if (keys::right_pressed)
				out_float += step;
		}

		std::string float_str = std::to_string(out_float);
		if (std::size_t dot_ind = float_str.find("."); dot_ind != std::string::npos)
			float_str = float_str.substr(0, (dot_ind + 1) + precision);

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", float_str), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + .068f, (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}

	template <>
	structs::button vector_option(
		std::string_view option_name, const std::vector<std::string_view>& list,
		std::size_t& out_idx, float offset_from_normal,
		std::function<std::string_view(std::string_view)> callback)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
			{
				if (out_idx != 0)
					out_idx--;
				else 
					out_idx = list.size() - 1;
			}

			if (keys::right_pressed)
				out_idx < (list.size() - 1) ? out_idx++ : out_idx = 0;
		}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}

	template <>
	structs::button vector_option(
		std::string_view option_name, const std::vector<std::string>& list,
		std::size_t& out_idx, float offset_from_normal,
		std::function<std::string_view(std::string_view)> callback)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
			{
				if (out_idx != 0)
					out_idx--;
				else
					out_idx = list.size() - 1;
			}

			if (keys::right_pressed)
				out_idx < (list.size() - 1) ? out_idx++ : out_idx = 0;
		}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", callback(list[out_idx])), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}

	structs::button object_vector_option(
		std::string_view option_name, const std::vector<structs::spawned_obj>& list,
		std::size_t& out_idx, float offset_from_normal,
		std::function<std::string_view(structs::spawned_obj)> callback)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;
		std::string_view text_val = "NULL";

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
			{
				if (out_idx != 0)
					out_idx--;
				else
					out_idx = list.size() - 1;
			}

			if (keys::right_pressed)
				out_idx < (list.size() - 1) ? out_idx++ : out_idx = 0;
		}

		try
		{
			text_val = callback(list[out_idx]);
		}
		catch (...) {}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}
	
	structs::button ped_vector_option(
		std::string_view option_name, const std::vector<structs::spawned_ped>& list,
		std::size_t& out_idx, float offset_from_normal,
		std::function<std::string_view(structs::spawned_ped)> callback)
	{
		option(option_name);
		bool onThis = settings::current_option == settings::option_count;
		std::string_view text_val = "NULL";

		if (settings::option_count == settings::current_option)
		{
			if (keys::left_pressed)
			{
				if (out_idx != 0)
					out_idx--;
				else
					out_idx = list.size() - 1;
			}

			if (keys::right_pressed)
				out_idx < (list.size() - 1) ? out_idx++ : out_idx = 0;
		}

		try
		{
			text_val = callback(list[out_idx]);
		}
		catch (...) {}

		if (settings::current_option <= settings::max_vis_options && settings::option_count <= settings::max_vis_options)
			onThis
				? drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), settings::option_count * .035f + .125f }, { .5f, .5f }, true, false);
		else if (settings::option_count > settings::current_option - settings::max_vis_options && settings::option_count <= settings::current_option)
			onThis
				? drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_selected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false)
				: drawing::text(std::format("<{}>", text_val), g_json.m_settings.settings.theme.option_unselected_text, { settings::menu_x + (.068f - offset_from_normal), (settings::option_count - (settings::current_option - settings::max_vis_options)) * .035f + .12f }, { .5f, .5f }, true, false);

		return { onThis, onThis && keys::select_pressed };
	}

	void end()
	{
		int actual_option_count = settings::option_count - settings::seperator_count;
		//!? TODO: ugh fix this garbage when seperators exist
		int actual_current_option = (settings::current_option);

		if (settings::option_count >= settings::max_vis_options)
		{
			drawing::text("unPAID", g_json.m_settings.settings.theme.footer_text, { settings::menu_x - (settings::menu_width / 2) + .005f, (settings::max_vis_options + 1) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::text(std::format("{}/{}", actual_current_option, actual_option_count), g_json.m_settings.settings.theme.footer_text, { settings::menu_x + (settings::menu_width / 2) - .03f, (settings::max_vis_options + 1) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::rect(g_json.m_settings.settings.theme.footer_background, { settings::menu_x, (settings::max_vis_options + 1) * .035f + .1415f }, { settings::menu_width, .035f });

			if (actual_current_option == 1)
				drawing::sprite("commonmenu", "arrowright", settings::menu_x, ((settings::max_vis_options + 1) * .035f + .142f), .010f, .0175f, 90, g_json.m_settings.settings.theme.footer_sprite);
			else if (actual_current_option == actual_option_count)
				drawing::sprite("commonmenu", "arrowright", settings::menu_x, ((settings::max_vis_options + 1) * .035f + .142f), .010f, .0175f, 270, g_json.m_settings.settings.theme.footer_sprite);
			else
				drawing::sprite("commonmenu", "shop_arrows_upanddown", settings::menu_x, ((settings::max_vis_options + 1) * .035f + .140f), .020f, .035f, 180, g_json.m_settings.settings.theme.footer_sprite);
		}
		else if (settings::option_count > 0)
		{
			drawing::text("unPAID", g_json.m_settings.settings.theme.footer_text, { settings::menu_x - (settings::menu_width / 2) + .005f, (actual_option_count + 1) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::text(std::format("{}/{}", actual_current_option, actual_option_count), g_json.m_settings.settings.theme.footer_text, { settings::menu_x + (settings::menu_width / 2) - .03f, (actual_option_count + 1) * .035f + .125f }, { .45f, .45f }, false, false);
			drawing::rect(g_json.m_settings.settings.theme.footer_background, { settings::menu_x, (actual_option_count + 1) * .035f + .1415f }, { settings::menu_width, .035f });

			if (actual_current_option == 1 && actual_option_count > 1)
				drawing::sprite("commonmenu", "arrowright", settings::menu_x, ((actual_option_count + 1) * .035f + .142f), .010f, .0175f, 90, g_json.m_settings.settings.theme.footer_sprite);
			else if (actual_current_option == actual_option_count && actual_option_count > 1)
				drawing::sprite("commonmenu", "arrowright", settings::menu_x, ((actual_option_count + 1) * .035f + .142f), .010f, .0175f, 270, g_json.m_settings.settings.theme.footer_sprite);
			else
				drawing::sprite("commonmenu", "shop_arrows_upanddown", settings::menu_x, ((actual_option_count + 1) * .035f + .140f), .020f, .035f, 180, g_json.m_settings.settings.theme.footer_sprite);
		}
	}
	
	void reset_optioncount()
	{
		settings::option_count = 0;
		settings::seperator_count = 0;
	}

	namespace keys
	{
		bool select_pressed = false;
		bool left_pressed = false;
		bool right_pressed = false;

		int key_press_delay = 160;
		ULONGLONG key_press_previous_tick = GetTickCount64();

		// wrapper so that other files can have access to InputHook::get_key_state()
		bool is_key_pressed(int key_code)
		{
			return InputHook::get_key_state(key_code);
		}
	}

	namespace checks
	{
		void keys()
		{
			keys::select_pressed = false;
			keys::left_pressed = false;
			keys::right_pressed = false;

			if ((GetTickCount64() - keys::key_press_previous_tick) > keys::key_press_delay)
			{
				if (InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::open_key)))
				{
					settings::menu_visible = !settings::menu_visible;
					settings::previous_menu = settings::current_menu;
					settings::previous_option = settings::current_option;

					if (settings::menu_visible)
					{
						menu_level_handler::move_menu(settings::previous_menu);
						menu_level_handler::move_option(settings::previous_option);
					}

					keys::key_press_previous_tick = GetTickCount64();
				}
				else if (InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::back_key)))
				{
					if (settings::menu_visible)
						menu_level_handler::back_menu();

					keys::key_press_previous_tick = GetTickCount64();
				}
				else if (InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::up_key)))
				{
					settings::current_option > 1
						? settings::current_option--
						: settings::current_option = settings::option_count;

					keys::key_press_previous_tick = GetTickCount64();
				}
				else if (InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::down_key)))
				{
					settings::current_option < settings::option_count
						? settings::current_option++
						: settings::current_option = 1;

					keys::key_press_previous_tick = GetTickCount64();
				}
				//!? TODO: Remove this before shipping
				else if (InputHook::get_key_state(VK_INSERT))
					pico::g_running = false;

				keys::left_pressed = InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::left_key));
				keys::right_pressed = InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::right_key));
				keys::select_pressed = InputHook::get_key_state(pico::g_custom_input.get_key(InputHook::select_key));
				keys::key_press_previous_tick = (keys::left_pressed || keys::right_pressed || keys::select_pressed)
					? GetTickCount64()
					: keys::key_press_previous_tick;
			}
		}
	}

	namespace menu_level_handler
	{
		void move_menu(submenus menu)
		{
			settings::menus_array[settings::menu_level] = settings::current_menu;
			settings::options_array[settings::menu_level] = settings::current_option;
			settings::menu_level = static_cast<submenus>(static_cast<int>(settings::menu_level) + 1);
			settings::current_menu = menu;
			settings::current_option = 1;
		}

		void move_option(int option)
		{
			settings::options_array[settings::menu_level] = 1;
			settings::current_option = option;
		}

		//!? TODO: fix the broken return
		void back_menu()
		{
			if (settings::current_menu == submenus::MAIN)
			{
				settings::menu_visible = false;
				settings::previous_menu = settings::current_menu;
				settings::previous_option = settings::current_option;
			}
			else
			{
				settings::menu_level = static_cast<submenus>(static_cast<int>(settings::menu_level) - 1);
				settings::current_menu = settings::menus_array[settings::menu_level];
				settings::current_option = settings::options_array[settings::menu_level];
			}
		}
	}
}
