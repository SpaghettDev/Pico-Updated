#pragma once

enum submenus //Add Sub Menus in here
{
	MAIN,

	SELF,
	SELF_PROOFS,
	SELF_WANTEDLEVEL,

	HUDSUB,
	
	TRACERANDESP,
	TRACERANDESP_COLORS,

	TELEPORT,
	TELEPORT_SAVED,

	WEAPONS,
	WEAPONS_CUSTOMAMMO,
	WEAPONS_CUSTOMGUN,

	VEHICLESUB, // VEHICLE is a native namespace
	VEHICLESUB_SPAWNER,
	VEHICLESUB_PROOFS,
	VEHICLESUB_MECHANIC,

	WORLD,
	WORLD_IPL,
	WORLD_WEATHERANDTIME,
	WORLD_OBJECTSPAWNER,
	WORLD_OBJECTSPAWNER_SPAWNEDOBJECTS,
	WORLD_PEDSPAWNER,
	WORLD_PEDSPAWNER_SPAWNEDPEDS,

	ONLINE,
	
	SETTINGS,
	SETTINGS_INPUT,
	SETTINGS_THEME,
	SETTINGS_THEME_TITLETEXT,
	SETTINGS_THEME_TITLERECT,
	SETTINGS_THEME_SUBMENUBARTEXT,
	SETTINGS_THEME_SUBMENUBARRECT,
	SETTINGS_THEME_SEPERATORRECT,
	SETTINGS_THEME_SUBMENUARROW,
	SETTINGS_THEME_OPTIONTEXT,
	SETTINGS_THEME_OPTIONRECT,
	SETTINGS_THEME_FOOTERTEXT,
	SETTINGS_THEME_FOOTERRECT
};

namespace menu
{
	namespace drawing 
	{
		void text(std::string_view, RGBAF, Vector2, SizeVector, bool, bool);
		void rect(RGBA, Vector2, SizeVector);
		void sprite(std::string_view, std::string_view, float, float, float, float, float, RGBA);
	}

	namespace settings 
	{
		extern int max_vis_options;
		extern int current_option;
		extern int previous_option;
		extern int option_count;
		extern int seperator_count;

		extern submenus current_menu;
		extern submenus previous_menu;
		extern submenus menu_level;
		extern std::array<int, 1000> options_array;
		extern std::array<submenus, 1000> menus_array;
		extern bool menu_visible;
		extern float menu_x;
		extern float menu_width;
	}

	namespace menu_level_handler 
	{
		void move_menu(submenus);
		void move_option(int);
		void back_menu();
	}

	namespace keys
	{
		extern bool select_pressed;
		extern bool left_pressed;
		extern bool right_pressed;

		extern int key_press_delay;
		extern ULONGLONG key_press_previous_tick;

		bool is_key_pressed(int);
	}

	namespace checks 
	{
		void keys();
	}

	void title(std::string_view);
	structs::button option(std::string_view);
	structs::button option(std::string_view, bool&);
	void seperator();
	structs::button menu_option(std::string_view, submenus);
	structs::button bool_option(std::string_view, bool&);
	structs::button int_option(std::string_view, int&, int, int, int = 1);
	structs::button int_option(std::string_view, int&, int = 1);
	structs::button float_option(std::string_view, float&, float, float, float = 0.1f, int = 2);
	structs::button float_option(std::string_view, float&, float = 0.1f, int = 2);
	template <typename T>
	structs::button vector_option(
		std::string_view,
		const std::vector<T>&,
		std::size_t&,
		float = 0.008f,
		std::function<std::string_view(std::string_view)> = [](std::string_view s) { return s; }
	);
	template <>
	structs::button vector_option(
		std::string_view,
		const std::vector<std::string_view>&,
		std::size_t&,
		float,
		std::function<std::string_view(std::string_view)>
	);
	template <>
	structs::button vector_option(
		std::string_view,
		const std::vector<std::string>&,
		std::size_t&,
		float,
		std::function<std::string_view(std::string_view)>
	);

	structs::button object_vector_option(
		std::string_view,
		const std::vector<structs::spawned_obj>&,
		std::size_t&,
		float = 0.008f,
		std::function<std::string_view(structs::spawned_obj)> = [](structs::spawned_obj obj) { return obj.name; }
	);

	structs::button ped_vector_option(
		std::string_view,
		const std::vector<structs::spawned_ped>&,
		std::size_t&,
		float = 0.008f,
		std::function<std::string_view(structs::spawned_ped)> = [](structs::spawned_ped ped) { return ped.name; }
	);

	void end();
	void reset_optioncount();
}