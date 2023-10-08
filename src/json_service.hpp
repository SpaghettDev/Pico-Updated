#pragma once

// simple wrapper to keep track of filename & support for std::string
class ifstream_wrapper : std::ifstream
{
public:
	std::string filename; // file.extension
	std::filesystem::path filepath; // X:\...\...\file.extension
	std::string stem; // file
	std::ifstream stream; // actual ifstream

	ifstream_wrapper(std::filesystem::path path)
		: filename(path.filename().string()), filepath(path),
		stem(path.stem().string()), stream(std::ifstream(path))
	{}

	operator std::ifstream&()
	{
		return stream;
	}
};

class JsonService;
class JsonTP;

class JsonSettings
{
public:
	void attempt_save();
	bool load();

private:
	static bool deep_compare(nlohmann::json&, const nlohmann::json&, bool = false);
	bool save();
	bool write_default_config(const char* = nullptr);

	nlohmann::json m_default_options;
	nlohmann::json m_options;

public:
	friend class JsonTP;

	struct self
	{
		std::array<bool, 9> proofs = { false };

		int wanted_level = 0;
		bool wanted_forced = false;

		bool always_clean_ped = false;
		bool mobile_radio = false;
		bool freecam = false;
		bool noclip = false;
		bool no_collision = false;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(self,
			proofs, wanted_level, wanted_forced, always_clean_ped,
			mobile_radio, freecam, noclip, no_collision);
	} self{};

	struct tracer_esp
	{
		bool tracer = false;
		bool esp = false;

		RGBA tracer_ped_color = RGBA{ 0, 255, 0, 255 };
		RGBA tracer_veh_color = RGBA{ 0, 0, 255, 255 };
		RGBA esp_ped_color = RGBA{ 0, 255, 0, 255 };
		RGBA esp_veh_color = RGBA{ 0, 0, 255, 140 };

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(tracer_esp,
			tracer, esp, tracer_ped_color, tracer_veh_color, esp_ped_color, esp_veh_color);
	} tracer_esp{};

	struct tp
	{
		bool auto_tp = false;
		bool always_sync_coords = false;


		Vector3 tp_pos{ 0.f, 0.f, 0.f };

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(tp,
			auto_tp, always_sync_coords);
	} tp{};

	struct weapons
	{
		structs::custom_ammo custom_ammo{};

		bool deleter_gun = false;
		bool info_gun = false;

		float damage_multiplier = 1.f;
		bool inf_ammo = false;
		bool inf_clip = false;
		bool rapid_fire = false;
		bool no_reload = false;


		std::size_t selected_weapon_idx = 0;
		std::size_t selected_upgrade_idx = 0;

		std::size_t selected_impact_idx = 0;
		std::size_t selected_type_idx = 0;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(weapons,
			custom_ammo, deleter_gun, info_gun, damage_multiplier, inf_ammo, inf_clip, rapid_fire, no_reload);
	} weapons{};

	struct vehicle
	{
		std::string last_inp = "";
		std::string last_inp_custom = "adder";

		bool always_sync_coords = false;
		bool spawn_in = false;
		bool put_in = false;
		bool networked = false;

		std::array<bool, 8> proofs = { false };
		bool always_repair = false;

		bool horn_boost = false;
		float horn_boost_increment = 0.3f;


		Vector3 pos{ 0.f, 0.f, 0.f };

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(vehicle,
			last_inp, last_inp_custom, last_inp_custom,
			always_sync_coords, spawn_in, networked,
			proofs, always_repair, horn_boost,
			horn_boost_increment);
	} vehicle{};

	struct world
	{
		struct ipl
		{
			std::string last_input = "";


			std::size_t selected_ipl_idx = 0;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(ipl,
				last_input);
		} ipl{};

		struct time_and_weather
		{
			bool always_sync_time = false;


			structs::time custom_time{ 0, 0, 0 };
			std::size_t selected_weather_idx = 0;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(time_and_weather,
				always_sync_time);
		} time_and_weather{};

		struct object
		{
			std::string last_input = "";
			std::string last_input_custom = "";

			bool spawn_where_looking = false;
			bool always_sync_coords = false;
			bool preview = false;

			bool networked = false;
			bool dynamic = false;


			Vector3 pos{ 0.f, 0.f, 0.f };

			std::vector<structs::spawned_obj> previous_spawned;
			std::size_t previous_spawned_idx = 0;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(object,
				last_input, last_input_custom, spawn_where_looking, always_sync_coords, preview,
				networked, dynamic);
		} object{};

		struct ped
		{
			std::string last_input = "";
			std::string last_input_custom = "";

			bool spawn_where_looking = false;
			bool always_sync_coords = false;
			bool preview = false;
			float heading = .1f;
			bool networked = false;
			ePedType type = ePedType::PED_TYPE_PLAYER_0;


			Vector3 pos{ 0.f, 0.f, 0.f };

			std::vector<structs::spawned_ped> previous_spawned;
			std::size_t previous_spawned_idx = 0;

			std::size_t selected_type_idx = 0;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(ped,
				spawn_where_looking, always_sync_coords, heading, type);
		} ped{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(world,
			ipl, time_and_weather, object, ped);
	} world{};

	struct online
	{
		bool no_idle_kick = false;


		std::size_t session_type_idx = 0;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(online,
			no_idle_kick);
	} online{};

	struct settings
	{
		struct input
		{
			MenuInputType type = MenuInputType::ARROW_KEYS;
			InputHook::custom_input_type custom{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(input,
				type, custom);
		} input{};

		struct theme
		{
			RGBAF title_text{ 255, 255, 255, 255, 1 };
			RGBA title_background{ 3, 140, 252, 255 };
			RGBAF submenu_bar_text{ 255, 255, 255, 255, 4 };
			RGBA submenu_bar_background{ 0, 0, 0, 190 };
			RGBA submenu_rect{ 3, 140, 252, 255 };
			RGBAF option_unselected_text{ 255, 255, 255, 255, 4 };
			RGBAF option_selected_text{ 10, 10, 10, 255, 4 };
			RGBA option_unselected_background{ 0, 0, 0, 160 };
			RGBA option_selected_background{ 255, 255, 255, 255 };
			RGBA seperator_background{ 0, 0, 0, 210 };
			RGBAF footer_text{ 255, 255, 255, 255, 4 };
			RGBA footer_background{ 0, 0, 0, 220 };
			RGBA footer_sprite{ 255, 255, 255, 255 };

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(theme,
				title_text, title_background, submenu_bar_text, submenu_bar_background,
				submenu_rect, option_unselected_text, option_selected_text, option_unselected_background,
				option_selected_background, seperator_background, footer_text, footer_background,
				footer_sprite
			);
		} theme{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(settings,
			input, theme);
	} settings{};

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(JsonSettings,
		self, tracer_esp, tp, weapons, vehicle, world, online, settings);

	friend class JsonService;
};

class JsonTP
{
public:
	void attempt_save();
	bool load();

private:
	bool save();
	bool write_default_config(const char* = nullptr);

	nlohmann::json m_default_options = nlohmann::json::array();
	nlohmann::json m_options = nlohmann::json::array();

public:
	inline static std::size_t selected_location_idx = 0;
	inline static std::vector<std::string> location_names;

	void add_location(std::string, Vector3, Vector3);
	void remove_location(std::string);
	nlohmann::json get_locations() const { return m_options; }

	friend class JsonService;
};

class JsonService
{
private:
	inline static bool m_init = false;

	inline static std::filesystem::path m_json_path = Logger::m_log_file_path;
	inline static std::filesystem::path m_settings_path = m_json_path / "settings.json";
	inline static std::filesystem::path m_tp_path = m_json_path / "tp.json";

	nlohmann::json handle_parse_error_and_return(ifstream_wrapper, nlohmann::json);
	nlohmann::ordered_json handle_parse_error_and_return(ifstream_wrapper, nlohmann::ordered_json);

public:
	void init();
	void attempt_save();

	JsonSettings m_settings;
	JsonTP m_tp;

	friend class JsonSettings;
	friend class JsonTP;
};
