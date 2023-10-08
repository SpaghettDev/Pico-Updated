#pragma once
#include <variant>
#include "stdafx.hpp"
#include "script_global.hpp"

namespace
{
	auto draw_line = [](Vector3 vec1, Vector3 vec2, RGBA rgba)
	{
		GRAPHICS::DRAW_LINE(vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z, rgba.r, rgba.g, rgba.b, rgba.a);
	};
}

namespace functions::world
{
	void load_sp_map()
	{
		DLC::ON_ENTER_SP();
		MISC::SET_INSTANCE_PRIORITY_MODE(2); // disable GTA:O IPLs
		MISC::SET_INSTANCE_PRIORITY_HINT(2); // disable GTA:O CMapData scenes
	}

	void load_mp_map()
	{
		DLC::ON_ENTER_MP();
		MISC::SET_INSTANCE_PRIORITY_MODE(1); // enable GTA:O IPLs
		MISC::SET_INSTANCE_PRIORITY_HINT(1); // enable GTA:O CMapData scenes
	}

	void load_known_ipl(std::string_view name)
	{
		using namespace ipls_data;

		if (useful_ipls.find(name) != useful_ipls.end())
		{
			useful_ipls[name].on_load();
			INTERIOR::REFRESH_INTERIOR(
				INTERIOR::GET_INTERIOR_AT_COORDS(
					useful_ipls[name].ipl_coords.x,
					useful_ipls[name].ipl_coords.y,
					useful_ipls[name].ipl_coords.z
				)
			);
		}
	}

	void unload_known_ipl(std::string_view name)
	{
		using namespace ipls_data;

		if (useful_ipls.find(name) != useful_ipls.end())
		{
			useful_ipls[name].on_unload();
			INTERIOR::REFRESH_INTERIOR(
				INTERIOR::GET_INTERIOR_AT_COORDS(
					useful_ipls[name].ipl_coords.x,
					useful_ipls[name].ipl_coords.y,
					useful_ipls[name].ipl_coords.z
				)
			);
		}
	}

	void load_uknown_ipl(std::string_view name)
	{
		STREAMING::REQUEST_IPL(name.data());
	}
	
	void unload_uknown_ipl(std::string_view name)
	{
		STREAMING::REMOVE_IPL(name.data());
	}


	bool is_model_valid(Hash name)
	{
		return STREAMING::IS_MODEL_VALID(name);
	}


#pragma region Entity Stuff
	Object spawn_object(Hash name, Vector3 position, bool networked = true, bool dynamic = true)
	{
		if (utils::request_model(name))
		{
			Object obj = utils::apply_model_spawn_bypass(
				[name, position, networked, dynamic] {
					return OBJECT::CREATE_OBJECT(name, position.x, position.y, position.z, networked, false, dynamic);
				}
			);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(name);
			return obj;
		}

		return -1;
	}
	
	Ped spawn_ped(Hash name, ePedType type, Vector3 position, float heading = 0.0f, bool networked = true)
	{
		if (utils::request_model(name) && utils::is_model_a_ped(name))
		{
			Ped ped = utils::apply_model_spawn_bypass(
				[name, type, position, heading, networked] {
					return PED::CREATE_PED(static_cast<int>(type), name, position.x, position.y, position.z, heading, networked, false);
				}
			);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(name);
			return ped;
		}

		return -1;
	}

	void set_entity_collision(Entity ent, bool toggle, bool physics)
	{
		ENTITY::SET_ENTITY_COLLISION(ent, toggle, physics);
	}
	
	void set_entity_alpha(Entity ent, int alpha, bool skin)
	{
		ENTITY::SET_ENTITY_ALPHA(ent, alpha, skin);
	}
	
	void reset_entity_alpha(Entity ent)
	{
		ENTITY::RESET_ENTITY_ALPHA(ent);
	}

	void set_entity_visible(Entity ent, bool toggle)
	{
		ENTITY::SET_ENTITY_VISIBLE(ent, toggle, false);
	}
	
	void set_entity_visible_network(Entity ent, bool toggle)
	{
		NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(ent, !toggle);
	}
	
	void set_entity_locally_visible_network(Entity ent)
	{
		NETWORK::SET_ENTITY_LOCALLY_VISIBLE(ent);
	}
	
	void set_entity_locally_invisible_network(Entity ent)
	{
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(ent);
	}

	void set_entity_mission_entity(Entity ent, bool toggle)
	{
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, toggle, false);
	}

	void set_entity_freeze(Entity ent, bool toggle)
	{
		ENTITY::FREEZE_ENTITY_POSITION(ent, toggle);
	}

	void set_entity_health(Entity ent, int health)
	{
		ENTITY::SET_ENTITY_HEALTH(ent, health, 0);
	}
	
	void set_ped_armor(Entity ent, int armor)
	{
		PED::SET_PED_ARMOUR(ent, armor);
	}

	Vector3 get_entity_coords(Entity ent)
	{
		return ENTITY::GET_ENTITY_COORDS(ent, false);
	}

	float get_entity_heading(Entity ent)
	{
		return ENTITY::GET_ENTITY_HEADING(ent);
	}

	int get_entity_health(Entity ent)
	{
		return ENTITY::GET_ENTITY_HEALTH(ent);
	}
	
	int get_entity_max_health(Entity ent)
	{
		return ENTITY::GET_ENTITY_MAX_HEALTH(ent);
	}

	int get_ped_armor(Ped ped)
	{
		return PED::GET_PED_ARMOUR(ped);
	}

	void create_random_ped(Vector3 pos)
	{
		PED::CREATE_RANDOM_PED(pos.x, pos.y, pos.z);
	}

	void teleport_entity_to(Entity ent, Vector3 pos)
	{
		ENTITY::SET_ENTITY_COORDS(ent, pos.x, pos.y, pos.z, true, false, false, false);
	}

	void delete_entity(Entity ent)
	{
		if (utils::take_control_of(ent))
		{
			set_entity_mission_entity(ent, true);

			if (ENTITY::IS_ENTITY_A_PED(ent))
				PED::DELETE_PED(&ent);
			else if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
				VEHICLE::DELETE_VEHICLE(&ent);
			else if (ENTITY::IS_ENTITY_AN_OBJECT(ent))
				OBJECT::DELETE_OBJECT(&ent);
			else
				ENTITY::DELETE_ENTITY(&ent);
		}
	}

	void draw_entity_box(structs::spawned_obj obj, RGBA rgba = world::entity_box_color)
	{
		Vector3 dim_min,
			dim_max,
			ent_coords = world::get_entity_coords(obj.id);

		MISC::GET_MODEL_DIMENSIONS(rage::joaat(obj.name), &dim_min, &dim_max);

		// no rotation because i can't figure it out (TODO?)
		GRAPHICS::DRAW_BOX(
			ent_coords.x + dim_min.x,
			ent_coords.y + dim_min.y,
			ent_coords.z + dim_min.z,

			ent_coords.x + dim_max.x,
			ent_coords.y + dim_max.y,
			ent_coords.z + dim_max.z,

			rgba.r, rgba.g, rgba.b, rgba.a
		);
	}
	
	void draw_entity_box(structs::spawned_ped ped, RGBA rgba = world::entity_box_color)
	{
		Vector3 dim_min,
			dim_max,
			ent_coords = world::get_entity_coords(ped.id);

		MISC::GET_MODEL_DIMENSIONS(rage::joaat(ped.name), &dim_min, &dim_max);

		// no rotation because i can't find how to do it
		GRAPHICS::DRAW_BOX(
			ent_coords.x + dim_min.x,
			ent_coords.y + dim_min.y,
			ent_coords.z + dim_min.z,

			ent_coords.x + dim_max.x,
			ent_coords.y + dim_max.y,
			ent_coords.z + dim_max.z,

			rgba.r, rgba.g, rgba.b, rgba.a
		);
	}
	
	void draw_entity_box(Hash name, Entity id, RGBA rgba)
	{
		Vector3 dim_min,
			dim_max,
			ent_coords = world::get_entity_coords(id);

		MISC::GET_MODEL_DIMENSIONS(name, &dim_min, &dim_max);

		// no rotation because i can't find how to do it
		GRAPHICS::DRAW_BOX(
			ent_coords.x + dim_min.x,
			ent_coords.y + dim_min.y,
			ent_coords.z + dim_min.z,

			ent_coords.x + dim_max.x,
			ent_coords.y + dim_max.y,
			ent_coords.z + dim_max.z,

			rgba.r, rgba.g, rgba.b, rgba.a
		);
	}

	void preview_entity(Hash name)
	{
		static bool preview_active = false;
		auto is_an_escape_key_pressed = []
		{
			return
				menu::keys::is_key_pressed(InputHook::up_key) ||
				menu::keys::is_key_pressed(InputHook::down_key);
		};

		Vector3 location;
		bool is_ped = utils::is_model_a_ped(name);

		if (utils::is_model_a_car(name))
			location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player::ped, 0.f, 10.f, .5f);
		else
			location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player::ped, 0.f, 5.f, -.5f);

		if (auto id = is_ped ? world::spawn_ped(name, ePedType::PED_TYPE_BUM, location) : world::spawn_object(name, location))
		{
			Vector3 rot = ENTITY::GET_ENTITY_ROTATION(id, 1);
			set_entity_mission_entity(id, true);
			set_entity_freeze(id, true);
			set_entity_collision(id, false, false);
			set_entity_alpha(id, 127, true);
			set_entity_visible_network(id, false);
			set_entity_locally_invisible_network(id);

			// make ped T-pose
			if (is_ped)
			{
				while (!STREAMING::HAS_ANIM_DICT_LOADED("nm@hands"))
				{
					STREAMING::REQUEST_ANIM_DICT("nm@hands");
					WAIT(0);
				}

				TASK::CLEAR_PED_TASKS(id);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(id);

				TASK::TASK_PLAY_ANIM(id, "nm@hands", "hands_up", 5.f, -1, -1, 50, 0.f, false, false, false);
			}

			preview_active = true;

			for (int i = 0; !is_an_escape_key_pressed(); i + 1 > 360 ? i = 0 : i++)
			{
				ENTITY::SET_ENTITY_ROTATION(id, rot.x, rot.y, static_cast<float>(i), 1, true);

				utils::notify::display_help_text(
					std::format("To stop the preview, press {} or {}.",
						key_names[VK_UP], key_names[VK_DOWN]
					)
				);
				PAD::DISABLE_CONTROL_ACTION(ControlTypes::FRONTEND_CONTROL, ControllerInputs::INPUT_PHONE, true);

				WAIT(1);
			}

			if (is_ped)
				STREAMING::REMOVE_ANIM_DICT("nm@hands");

			delete_entity(id);

			preview_active = false;
		}
	}


	std::vector<Ped> get_nearby_ents_of_type(eEntityType type, int max)
	{
		return std::vector<Ped>{};
		// coming soon
	}
#pragma endregion

	void trace_to_peds()
	{
		std::vector<Entity> entities = get_nearby_ents_of_type(eEntityType::TYPE_PED, 200);

		for (const auto& ent : entities)
			if (ENTITY::IS_ENTITY_A_PED(ent) && ENTITY::DOES_ENTITY_EXIST(ent))	
				draw_line(player::pos, world::get_entity_coords(ent), pico::g_json.m_settings.tracer_esp.tracer_ped_color);
	}

	void trace_to_vehs()
	{
		std::vector<Entity> entities = get_nearby_ents_of_type(eEntityType::TYPE_VEHICLE, 200);

		for (const auto& ent : entities)
			if (ENTITY::IS_ENTITY_A_VEHICLE(ent) && ENTITY::DOES_ENTITY_EXIST(ent))
				draw_line(player::pos, world::get_entity_coords(ent), pico::g_json.m_settings.tracer_esp.tracer_veh_color);
	}

	void esp_peds()
	{
		std::vector<Entity> entities = get_nearby_ents_of_type(eEntityType::TYPE_PED, 200);

		for (const auto& ent : entities)
		{
			if (ENTITY::IS_ENTITY_A_PED(ent) && ENTITY::DOES_ENTITY_EXIST(ent))
			{
				Vector3 entitylocation = world::get_entity_coords(ent);

				Vector3 top1world = entitylocation + Vector3{ .3f, .3f, .8f };
				Vector3 top2world = entitylocation + Vector3{ -.3f, .3f, .8f };
				Vector3 top3world = entitylocation + Vector3{ .3f, -.3f, .8f };
				Vector3 top4world = entitylocation + Vector3{ -.3f, -.3f, .8f };

				Vector3 bottom1world = entitylocation + Vector3{ .3f, .3f, -.8f };
				Vector3 bottom2world = entitylocation + Vector3{ -.3f, .3f, -.8f };
				Vector3 bottom3world = entitylocation + Vector3{ .3f, -.3f, -.8f };
				Vector3 bottom4world = entitylocation + Vector3{ -.3f, -.3f, -.8f };

				draw_line(top1world, top2world, world::esp_ped_box_color);
				draw_line(top2world, top4world, world::esp_ped_box_color);
				draw_line(top3world, top4world, world::esp_ped_box_color);
				draw_line(top1world, top3world, world::esp_ped_box_color);

				draw_line(bottom1world, bottom2world, world::esp_ped_box_color);
				draw_line(bottom2world, bottom4world, world::esp_ped_box_color);
				draw_line(bottom3world, bottom4world, world::esp_ped_box_color);
				draw_line(bottom1world, bottom3world, world::esp_ped_box_color);

				draw_line(top1world, bottom1world, world::esp_ped_box_color);
				draw_line(top2world, bottom2world, world::esp_ped_box_color);
				draw_line(top3world, bottom3world, world::esp_ped_box_color);
				draw_line(top4world, bottom4world, world::esp_ped_box_color);
			}
		}
	}
	
	void esp_vehs()
	{
		std::vector<Entity> vehs = get_nearby_ents_of_type(eEntityType::TYPE_VEHICLE, 200);

		for (const auto& ent : vehs)
			if (ENTITY::IS_ENTITY_A_VEHICLE(ent) && ENTITY::DOES_ENTITY_EXIST(ent))
				draw_entity_box(ENTITY::GET_ENTITY_MODEL(ent), ent, world::esp_veh_box_color);
	}

	void clear_ped_tasks(Ped ped)
	{
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::CLEAR_PED_TASKS(ped);
		TASK::CLEAR_PED_SECONDARY_TASK(ped);
	}

	void teleport_ped_to_vehicle(Ped ped, Vehicle veh)
	{
		if (veh)
			PED::SET_PED_INTO_VEHICLE(ped, veh, -2);
	}


	void clear_weather_override()
	{
		MISC::CLEAR_OVERRIDE_WEATHER();
	}

	void set_local_weather(std::string_view name)
	{
		if (std::find(world::weathers.begin(), world::weathers.end(), name) != world::weathers.end())
		{
			clear_weather_override();
			MISC::SET_OVERRIDE_WEATHER(name.data());
			*script_global(262145).add(4752).as<bool*>() = name == weathers[13]; /* XMAS */
		}
	}

	void set_local_time(int hour, int min, int sec)
	{
		if (hour > 24 || min > 60 || sec > 60)
			return;

		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hour, min, sec);
	}
	
	void set_local_time(structs::time time)
	{
		set_local_time(time.hour, time.minutes, time.seconds);
	}

	void get_local_time(int& hour, int& min, int& sec)
	{
		NETWORK::NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(&hour, &min, &sec);
	}
	
	void get_local_time(structs::time& time)
	{
		get_local_time(time.hour, time.minutes, time.seconds);
	}

	void clear_time_override()
	{
		NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
	}

	structs::raycast get_raycast_result()
	{
		structs::raycast result;
		Vector3 far_coords;

		Vector3 cam_coords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = utils::math::rotation_to_direction(rot);

		far_coords = { cam_coords.x + dir.x * 1000, cam_coords.y + dir.y * 1000, cam_coords.z + dir.z * 1000 };
 
		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(
			cam_coords.x,
			cam_coords.y,
			cam_coords.z,
			far_coords.x,
			far_coords.y,
			far_coords.z,
			-1, 0, 7
		);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &result.hit, &result.end_coords, &result.surface_normal, &result.entity);

		return result;
	}
}
