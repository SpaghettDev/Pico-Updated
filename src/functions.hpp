#pragma once
#include "stdafx.hpp"
#include "rage/joaat.hpp"
#include "ped/CPed.hpp"
#include "weapons.hpp"
#include "ipls.hpp"
#include "peds.hpp"
#include "sessions.hpp"

namespace functions
{
	namespace player
	{
		CPed* local_player;
		Player id;
		Ped ped;
		Vector3 pos;
		Vehicle veh;
		int char_slot;

		CPed* get_local_ped();
		CVehicle* get_local_vehicle();
		CPlayerInfo* get_local_playerinfo();

		void update_local_player();
		void update_globals();

		void change_proof_bit(std::uint32_t);
		void max_health();
		void max_armor();
		void max_ammo();
		void max_clip();
		void suicide();
		void clean_ped(Ped, bool);

		void set_wanted_level(int);
		void clear_wanted_level();

		void get_all_weapons();
		void get_weapon(std::string_view);
		void remove_all_weapons();
		void remove_weapon(std::string_view);
		void get_all_weapons_upgrades();
		void get_weapon_upgrade(std::string_view, std::string_view);
		void remove_all_weapons_upgrades();
		void remove_weapon_upgrade(std::string_view, std::string_view);

		void teleport_to(Vector3);
		bool teleport_to_blip(BlipIcons, BlipColors);
		void teleport_to_waypoint();
		void teleport_to_objective();
	}

	namespace utils
	{
		bool request_model(Hash, int);
		bool request_model(std::string, int);
		bool is_model_a_car(Hash);
		bool is_model_a_ped(Hash);
		std::pair<KeyboardState, std::string> keyboard_input(std::string, int);
		bool take_control_of(Entity, int);
		Entity apply_model_spawn_bypass(std::function<Entity()>);
		int get_num_of_elems(const std::vector<std::string_view>&, const std::regex&);
		int get_num_of_elems(const std::vector<std::string_view>&, const std::string&);
		int get_num_of_elems(const std::vector<structs::spawned_obj>&, const std::regex&);
		int get_num_of_elems(const std::vector<structs::spawned_obj>&, const std::string&);
		int get_num_of_elems(const std::vector<structs::spawned_ped>&, const std::regex&);
		int get_num_of_elems(const std::vector<structs::spawned_ped>&, const std::string&);

		namespace math
		{
			float deg_to_rad(float);
			float distance_between_vector3(Vector3, Vector3);
			Vector3 rotation_to_direction(Vector3);
		}

		namespace notify
		{
			void above_map(std::string_view);
			void display_help_text(std::string_view);
		}
	}

	namespace vehicle
	{
		Vehicle spawn_vehicle(Hash, Vector3, bool, bool);
		void max_vehicle(Vehicle);
		bool repair(Vehicle, bool);
		void change_proof_bit(std::uint32_t);
		void collision_proof(bool);
		static float horn_boost_speed_increment = 0.3f;
		void horn_boost(Vehicle);
	}

	namespace world
	{
		void load_sp_map();
		void load_mp_map();
		void load_known_ipl(std::string_view);
		void unload_known_ipl(std::string_view);
		void load_uknown_ipl(std::string_view);

		Object spawn_object(Hash, Vector3, bool, bool);
		Ped spawn_ped(Hash, ePedType, Vector3, float, bool);
		void set_entity_collision(Entity, bool, bool);
		void set_entity_alpha(Entity, int, bool);
		void reset_entity_alpha(Entity);
		void set_entity_visible(Entity, bool);
		void set_entity_visible_network(Entity, bool);
		void set_entity_locally_visible_network(Entity);
		void set_entity_locally_invisible_network(Entity);
		void set_entity_mission_entity(Entity, bool);
		void set_entity_freeze(Entity, bool);
		void set_entity_health(Entity, int);
		void set_ped_armor(Entity, int);
		void create_random_ped(Vector3);
		Vector3 get_entity_coords(Entity);
		float get_entity_heading(Entity);
		int get_entity_health(Entity);
		int get_entity_max_health(Entity);
		int get_ped_armor(Ped);
		void teleport_entity_to(Entity, Vector3);
		void teleport_ped_to_vehicle(Ped, Vehicle);
		void delete_entity(Entity);

		RGBA entity_box_color{ 255, 255, 255, 170 };
		void draw_entity_box(structs::spawned_obj, RGBA);
		void draw_entity_box(structs::spawned_ped, RGBA);
		void draw_entity_box(Hash, Entity, RGBA);
		void preview_entity(Hash);

		std::vector<Entity> get_nearby_ents_of_type(eEntityType, int);

		RGBA esp_ped_box_color{ 0, 255, 0, 255 };
		RGBA esp_veh_box_color{ 0, 0, 255, 140 };
		void esp_peds();
		void esp_vehs();
		RGBA tracer_ped_color{ 0, 255, 0, 255 };
		RGBA tracer_veh_color{ 0, 0, 255, 255 };
		void trace_to_peds();
		void trace_to_vehs();

		void clear_ped_tasks(Ped);

		std::vector<std::string_view> weathers{
			"EXTRASUNNY", "CLEAR", "CLOUDS", "SMOG",
			"FOGGY", "OVERCAST", "RAIN", "THUNDER",
			"CLEARING", "NEUTRAL", "SNOW", "BLIZZARD",
			"SNOWLIGHT", "XMAS", "HALLOWEEN"
		};
		void clear_weather_override();
		void set_local_weather(std::string_view);
		void set_local_time(int, int, int);
		void set_local_time(structs::time);
		void get_local_time(int& hour, int& min, int& sec);
		void get_local_time(structs::time& time);
		void clear_time_override();

		structs::raycast get_raycast_result();
	}

	class looped;

	namespace looped_vals
	{
		namespace settings
		{
			std::vector<std::string_view> input_types{
				"Default", "Arrows", "Numpad",
				"Numpad (With Select & Back)", "Custom"
			};
			std::size_t input_types_idx = 0;

			std::size_t open_idx = 0;
			std::size_t back_idx = 0;
			std::size_t up_idx = 0;
			std::size_t down_idx = 0;
			std::size_t left_idx = 0;
			std::size_t right_idx = 0;
			std::size_t select_idx = 0;
			std::size_t esc_idx = 0;
		}

		void features_loop();
	}
}

#include "utils.hpp"
#include "player.hpp"
#include "vehicle.hpp"
#include "world.hpp"
#include "looped.hpp"
#include "looped_vals.hpp"
