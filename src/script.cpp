#include "stdafx.hpp"
#include "menu_class.hpp"
#include "functions.hpp"

void pico_menu()
{
	using namespace functions;
	using namespace pico;

	if (!menu::settings::menu_visible)
		return;

	switch (menu::settings::current_menu)
	{
	case submenus::MAIN:
	{
		menu::title("Main Menu");

		menu::menu_option("Self", submenus::SELF);
		menu::menu_option("HUD", submenus::HUDSUB);
		// menu::menu_option("Tracer", submenus::TRACERANDESP);
		menu::menu_option("Teleport", submenus::TELEPORT);
		menu::menu_option("Weapons", submenus::WEAPONS);
		menu::menu_option("Vehicle", submenus::VEHICLESUB);
		menu::menu_option("World", submenus::WORLD);
		menu::menu_option("Online", submenus::ONLINE);
		menu::menu_option("Settings Menu", submenus::SETTINGS);
	}
	break;

	case submenus::SELF:
	{
		menu::title("Self");

		menu::menu_option("Proofs", submenus::SELF_PROOFS);
		menu::menu_option("Wanted Level", submenus::SELF_WANTEDLEVEL);

		if (menu::option("Restore Health"))
			player::max_health();
		if (menu::option("Restore Armor"))
			player::max_armor();
		if (menu::option("Restore Everything"))
		{
			player::max_health();
			player::max_armor();
			player::fill_inventory();
		}

		if (menu::option("Suicide"))
			player::suicide();
		
		if (menu::option("Clean Player"))
			player::clean_ped(player::ped, false);
		menu::bool_option("Always Clean Player", g_json.m_settings.self.always_clean_ped);

		if (menu::option("Fill Inventory"))
			player::fill_inventory();

		menu::bool_option("Mobile Radio", g_json.m_settings.self.mobile_radio);
		menu::bool_option("Freecam", g_json.m_settings.self.freecam);
		menu::bool_option("Noclip", g_json.m_settings.self.noclip);
		menu::bool_option("No Collision", g_json.m_settings.self.no_collision);
	}
	break;

	case submenus::SELF_PROOFS:
	{
		menu::title("Self Proofs");

		menu::bool_option("Godmode", (g_json.m_settings.self.proofs[0]));
		menu::bool_option("Bullet Proof", (g_json.m_settings.self.proofs[1]));
		menu::bool_option("Fire Proof", (g_json.m_settings.self.proofs[2]));
		menu::bool_option("Collision Proof", (g_json.m_settings.self.proofs[3]));
		menu::bool_option("Melee Proof", (g_json.m_settings.self.proofs[4]));
		menu::bool_option("Explosion Proof", (g_json.m_settings.self.proofs[5]));
		menu::bool_option("Steam Proof", (g_json.m_settings.self.proofs[6]));
		menu::bool_option("Drown Proof", (g_json.m_settings.self.proofs[7]));
		menu::bool_option("Water Proof", (g_json.m_settings.self.proofs[8]));

		if (menu::option("Toggle All"))
		{
			for (int i = 0; i < 9; i++)
				(g_json.m_settings.self.proofs[i]) = !(g_json.m_settings.self.proofs[i]);
		}
	}
	break;

	case submenus::SELF_WANTEDLEVEL:
	{
		menu::title("Self Wanted Level");

		menu::int_option("Wanted Level", g_json.m_settings.self.wanted_level, 0, 5);
		menu::bool_option("Force Wanted Level", g_json.m_settings.self.wanted_forced);
		if (menu::option("Clear Wanted Level"))
			player::clear_wanted_level();
	}
	break;
	
	
	case submenus::HUDSUB:
	{
		menu::title("HUD");

		//menu::bool_option("Show FPS", g_json.m_settings.hud.show_fps);
	}
	break;


	/*case submenus::TRACERANDESP:
	{
		menu::title("Tracer & ESP");

		menu::menu_option("Colors", submenus::TRACERANDESP_COLORS);
		menu::bool_option("Enable Tracer", looped_vals::esp::tracer_toggle);
		menu::bool_option("Enable ESP", looped_vals::esp::esp_toggle);

		if (looped_vals::esp::tracer_toggle)
		{
			menu::bool_option("Trace Peds Only", looped_vals::esp::trace_to_peds);
			menu::bool_option("Trace Vehs Only", looped_vals::esp::trace_to_vehs);
		}
		
		if (looped_vals::esp::esp_toggle)
		{
			menu::bool_option("ESP Peds Only", looped_vals::esp::esp_peds);
			menu::bool_option("ESP Vehs Only", looped_vals::esp::esp_vehs);
		}
	}
	break;
	*/

	case submenus::TRACERANDESP_COLORS:
	{
		menu::title("Tracer & ESP Colors");

		menu::option("Tracer Color (Ped)");
		menu::int_option("Red", g_json.m_settings.tracer_esp.tracer_ped_color.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.tracer_esp.tracer_ped_color.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.tracer_esp.tracer_ped_color.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.tracer_esp.tracer_ped_color.a, 0, 255);
		menu::option("Tracer Color (Veh)");
		menu::int_option("Red", g_json.m_settings.tracer_esp.tracer_veh_color.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.tracer_esp.tracer_veh_color.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.tracer_esp.tracer_veh_color.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.tracer_esp.tracer_veh_color.a, 0, 255);
		if (menu::option("Reset To Default"))
		{
			g_json.m_settings.tracer_esp.tracer_ped_color = { 0, 255, 0, 255 };
			g_json.m_settings.tracer_esp.tracer_veh_color = { 0, 0, 255, 255 };
		}

		menu::seperator();
		
		menu::option("ESP Color (Ped)");
		menu::int_option("Red", g_json.m_settings.tracer_esp.esp_ped_color.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.tracer_esp.esp_ped_color.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.tracer_esp.esp_ped_color.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.tracer_esp.esp_ped_color.a, 0, 255);
		menu::option("ESP Color (Veh)");
		menu::int_option("Red", g_json.m_settings.tracer_esp.esp_veh_color.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.tracer_esp.esp_veh_color.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.tracer_esp.esp_veh_color.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.tracer_esp.esp_veh_color.a, 0, 255);
		if (menu::option("Reset To Default"))
		{
			g_json.m_settings.tracer_esp.esp_ped_color = { 0, 255, 0, 255 };
			g_json.m_settings.tracer_esp.esp_veh_color = { 0, 0, 255, 140 };
		}
	}
	break;

	
	case submenus::TELEPORT:
	{
		menu::title("Teleport");

		menu::menu_option("Saved Teleports", submenus::TELEPORT_SAVED);

		if (menu::option("Teleport to Waypoint"))
			player::teleport_to_waypoint();
		if (menu::option("Teleport to Objective"))
			player::teleport_to_objective();

		menu::bool_option("Auto-Teleport to Waypoint", g_json.m_settings.tp.auto_tp);

		if (menu::option("Sync Coords"))
			g_json.m_settings.tp.tp_pos = player::pos;
		menu::bool_option("Always Sync Coords", g_json.m_settings.tp.always_sync_coords);

		menu::float_option("X", g_json.m_settings.tp.tp_pos.x, 0.1f, 3);
		menu::float_option("Y", g_json.m_settings.tp.tp_pos.y, 0.1f, 3);
		menu::float_option("Z", g_json.m_settings.tp.tp_pos.z, 0.1f, 3);

		if (menu::option("Teleport To Inserted Coords"))
			player::teleport_to(g_json.m_settings.tp.tp_pos);

		if (menu::option("Save Inserted Coords"))
		{
			auto [state, string] = utils::keyboard_input("Location Name", 64);

			if (state == KeyboardState::CANCELLED_EDITING)
				return;

			if (std::find(g_json.m_tp.location_names.begin(), g_json.m_tp.location_names.end(), string) != g_json.m_tp.location_names.end())
				utils::notify::above_map(std::format("~r~{} is already a location name!", string));
			else
				g_json.m_tp.add_location(string, g_json.m_settings.tp.tp_pos, ENTITY::GET_ENTITY_ROTATION(player::ped, 2));
		}
	}
	break;

	case submenus::TELEPORT_SAVED:
	{
		menu::title("Saved Teleports");

		if (auto locations = g_json.m_tp.get_locations(); locations.size() != 0)
		{
			menu::vector_option("Location", g_json.m_tp.location_names, g_json.m_tp.selected_location_idx);

			auto location = locations[g_json.m_tp.selected_location_idx][g_json.m_tp.location_names[g_json.m_tp.selected_location_idx]]["location"]["coords"].get<nlohmann::json::array_t>();
			auto rotation = locations[g_json.m_tp.selected_location_idx][g_json.m_tp.location_names[g_json.m_tp.selected_location_idx]]["location"]["rot"].get<nlohmann::json::array_t>();

			menu::seperator();

			//! TODO: make editable
			menu::option(std::format("Name: {}", g_json.m_tp.location_names[g_json.m_tp.selected_location_idx]));
			menu::option(std::format("X: {}", location[0].get<float>()));
			menu::option(std::format("Y: {}", location[1].get<float>()));
			menu::option(std::format("Z: {}", location[2].get<float>()));
			
			if (menu::option("Teleport"))
				player::teleport_to({ location[0], location[1], location[2] });

			//! TODO: fix this xd
			if (menu::option("Delete"))
			{
				g_json.m_tp.remove_location(g_json.m_tp.location_names[g_json.m_tp.selected_location_idx]);

				g_json.m_tp.location_names.erase(
					g_json.m_tp.location_names.begin() +
					g_json.m_tp.selected_location_idx
				);

				if (g_json.m_tp.selected_location_idx > 0)
					g_json.m_tp.selected_location_idx--;
				if (g_json.m_tp.location_names.size() == 0)
					menu::menu_level_handler::move_option(1);
			}
		}
		else
		{
			menu::option("No Saved Locations");
		}
	}
	break;


	case submenus::WEAPONS:
	{
		menu::title("Weapons");

		menu::menu_option("Custom Ammo", submenus::WEAPONS_CUSTOMAMMO);
		menu::menu_option("Custom Gun", submenus::WEAPONS_CUSTOMGUN);

		if (menu::option("Get All Weapons"))
			player::get_all_weapons();
		if (menu::option("Remove All Weapons"))
			player::remove_all_weapons();
		
		if (menu::option("Get All Weapons Upgrades"))
			player::get_all_weapons_upgrades();
		if (menu::option("Remove All Weapons Upgrades"))
			player::remove_all_weapons_upgrades();

		menu::vector_option("Weapon", weapons_data::weapons_names, g_json.m_settings.weapons.selected_weapon_idx, 0.01f);
		if (weapons_data::weapons_upgrades.find(weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]) != weapons_data::weapons_upgrades.end())
			menu::vector_option(
				"Weapon Upgrade",
				weapons_data::weapons_upgrades[weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]],
				g_json.m_settings.weapons.selected_upgrade_idx,
				0.01f
			);

		if (menu::option(std::format("Get {}", weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx])))
			player::get_weapon(weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]);
		if (menu::option(std::format("Remove {}", weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx])))
			player::remove_weapon(weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]);
		
		if (weapons_data::weapons_upgrades.find(weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]) != weapons_data::weapons_upgrades.end())
		{
			if (
				auto size = weapons_data::weapons_upgrades[weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]].size() - 1;
				g_json.m_settings.weapons.selected_weapon_idx > size 
				)
				g_json.m_settings.weapons.selected_weapon_idx = size;

			auto& upgrades = weapons_data::weapons_upgrades[weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx]];

			if (menu::option(std::format("Get {}", upgrades[g_json.m_settings.weapons.selected_upgrade_idx])))
				player::get_weapon_upgrade(weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx], upgrades[g_json.m_settings.weapons.selected_upgrade_idx]);
			if (menu::option(std::format("Remove {}", upgrades[g_json.m_settings.weapons.selected_upgrade_idx])))
				player::remove_weapon_upgrade(weapons_data::weapons_names[g_json.m_settings.weapons.selected_weapon_idx], upgrades[g_json.m_settings.weapons.selected_upgrade_idx]);
		}

		menu::bool_option("Infinite Ammo", g_json.m_settings.weapons.inf_ammo);
		menu::bool_option("Infinite Clip", g_json.m_settings.weapons.inf_clip);
		menu::bool_option("Rapid Fire", g_json.m_settings.weapons.rapid_fire);
		menu::bool_option("No Reload", g_json.m_settings.weapons.no_reload);

		if (menu::option("Max Ammo"))
			player::max_ammo();
		if (menu::option("Max Magazine"))
			player::max_clip();

		menu::float_option("Damage Multiplier", g_json.m_settings.weapons.damage_multiplier, -10.f, 10.f, 1.f, 1);
	}
	break;

	case submenus::WEAPONS_CUSTOMAMMO:
	{
		menu::title("Weapons Custom Ammo");

		menu::vector_option("Impact Types", weapons_data::bullet_impacts_names, g_json.m_settings.weapons.selected_impact_idx);
		menu::vector_option("Bullet Types", weapons_data::bullet_types_names, g_json.m_settings.weapons.selected_type_idx);

		if (menu::option(std::format("Apply {}", weapons_data::bullet_impacts_names[g_json.m_settings.weapons.selected_impact_idx])))
			g_json.m_settings.weapons.custom_ammo.explosion_tag = weapons_data::bullet_impacts[weapons_data::bullet_impacts_names[g_json.m_settings.weapons.selected_impact_idx]];
		if (menu::option(std::format("Apply {}", weapons_data::bullet_types_names[g_json.m_settings.weapons.selected_type_idx])))
			g_json.m_settings.weapons.custom_ammo.type = weapons_data::bullet_types[weapons_data::bullet_types_names[g_json.m_settings.weapons.selected_type_idx]];
	}
	break;

	case submenus::WEAPONS_CUSTOMGUN:
	{
		menu::title("Weapons Custom Gun");

		menu::bool_option("Object Deleter Gun", g_json.m_settings.weapons.deleter_gun);
		menu::bool_option("Information Gun", g_json.m_settings.weapons.info_gun);
	}
	break;


	case submenus::VEHICLESUB:
	{
		menu::title("Vehicle");

		menu::menu_option("Spawner", submenus::VEHICLESUB_SPAWNER);
		menu::menu_option("Proofs", submenus::VEHICLESUB_PROOFS);
		menu::menu_option("Mechanic", submenus::VEHICLESUB_MECHANIC);
	}
	break;

	case submenus::VEHICLESUB_SPAWNER:
	{
		menu::title("Vehicle Spawner");

		if (menu::option("Spawn Vehicle"))
		{
			auto [state, string] = utils::keyboard_input(g_json.m_settings.vehicle.last_inp.empty() ? "adder" : g_json.m_settings.vehicle.last_inp_custom, 14);

			if (state == KeyboardState::CANCELLED_EDITING)
				return;

			if (vehicle::spawn_vehicle(rage::joaat(string), player::pos) != -1)
				g_json.m_settings.vehicle.last_inp = string;
			else
				utils::notify::above_map(std::format("~r~{} is not a valid vehicle!", string));
		}

		if (menu::option("Spawn Vehicle (Maxed)"))
		{
			auto [state, string] = utils::keyboard_input(g_json.m_settings.vehicle.last_inp.empty() ? "adder" : g_json.m_settings.vehicle.last_inp_custom, 14);

			if (state == KeyboardState::CANCELLED_EDITING)
				return;

			if (Vehicle veh_id = vehicle::spawn_vehicle(rage::joaat(string), player::pos); veh_id != -1)
			{
				vehicle::max_vehicle(veh_id);
				g_json.m_settings.vehicle.last_inp = string;
			}
			else
				utils::notify::above_map(std::format("~r~{} is not a valid vehicle!", string));
		}

		menu::seperator();

		if (menu::option(std::format("Inputed Vehicle: {}", g_json.m_settings.vehicle.last_inp_custom.empty() ? "None" : g_json.m_settings.vehicle.last_inp_custom)))
		{
			auto [state, string] = utils::keyboard_input(g_json.m_settings.vehicle.last_inp_custom, 14);

			if (state == KeyboardState::CANCELLED_EDITING)
				return;

			if (utils::is_model_a_car(rage::joaat(string)))
				g_json.m_settings.vehicle.last_inp_custom = string;
			else
				utils::notify::above_map(std::format("~r~{} is not a valid vehicle!", string));
		}

		if (menu::option("Sync Coords"))
			g_json.m_settings.vehicle.pos = player::pos;
		menu::bool_option("Always Sync Coords", g_json.m_settings.vehicle.always_sync_coords);

		menu::float_option("X", g_json.m_settings.vehicle.pos.x, 0.1f, 3);
		menu::float_option("Y", g_json.m_settings.vehicle.pos.y, 0.1f, 3);
		menu::float_option("Z", g_json.m_settings.vehicle.pos.z, 0.1f, 3);
		menu::bool_option("Spawn In Vehicle", g_json.m_settings.vehicle.spawn_in);
		menu::bool_option("Networked", g_json.m_settings.vehicle.networked);

		if (menu::option(std::format("Spawn {}", g_json.m_settings.vehicle.last_inp_custom.empty() ? "None" : g_json.m_settings.vehicle.last_inp_custom)))
		{
			vehicle::spawn_vehicle(
				rage::joaat(g_json.m_settings.vehicle.last_inp_custom),
				g_json.m_settings.vehicle.pos,
				g_json.m_settings.vehicle.put_in,
				g_json.m_settings.vehicle.networked
			);
		}
		
		if (menu::option(std::format("Spawn {} (Maxed)", g_json.m_settings.vehicle.last_inp_custom.empty() ? "None" : g_json.m_settings.vehicle.last_inp_custom)))
		{
			Vehicle veh_id = vehicle::spawn_vehicle(
				rage::joaat(g_json.m_settings.vehicle.last_inp_custom),
				g_json.m_settings.vehicle.pos,
				g_json.m_settings.vehicle.put_in,
				g_json.m_settings.vehicle.networked
			);

			vehicle::max_vehicle(veh_id);
		}
	}
	break;

	case submenus::VEHICLESUB_PROOFS:
	{
		menu::title("Vehicle Proofs");

		menu::bool_option("Godmode", (g_json.m_settings.vehicle.proofs[0]));
		menu::bool_option("Bullet Proof", (g_json.m_settings.vehicle.proofs[1]));
		menu::bool_option("Fire Proof", (g_json.m_settings.vehicle.proofs[2]));
		menu::bool_option("Collision Proof", (g_json.m_settings.vehicle.proofs[3]));
		menu::bool_option("Melee Proof", (g_json.m_settings.vehicle.proofs[4]));
		menu::bool_option("Explosion Proof", (g_json.m_settings.vehicle.proofs[5]));
		menu::bool_option("Steam Proof", (g_json.m_settings.vehicle.proofs[6]));
		menu::bool_option("Drown Proof", (g_json.m_settings.vehicle.proofs[7]));

		if (menu::option("Toggle All"))
		{
			for (int i = 0; i < g_json.m_settings.vehicle.proofs.size(); i++)
				(g_json.m_settings.vehicle.proofs[i]) = !(g_json.m_settings.vehicle.proofs[i]);
		}
	}
	break;
	
	case submenus::VEHICLESUB_MECHANIC:
	{
		menu::title("Vehicle Mechanic");

		if (menu::option("Repair Vehicle"))
			vehicle::repair(player::veh);

		if (menu::bool_option("Always Repair Vehicle", g_json.m_settings.vehicle.always_repair))
		{
			if (!player::veh)
				g_json.m_settings.vehicle.always_repair = false;
		}

		if (menu::option("Max Vehicle"))
			vehicle::max_vehicle(player::veh);

		if (menu::bool_option("Horn Boost", g_json.m_settings.vehicle.horn_boost))
		{
			if (!player::veh)
				g_json.m_settings.vehicle.horn_boost = false;
		}
		menu::float_option("Horn Boost Speed Inceremnt", g_json.m_settings.vehicle.horn_boost_increment, 0.f, 10.f, 0.1f, 1);
	}
	break;


	case submenus::WORLD:
	{
		menu::title("World");

		menu::menu_option("IPLs", submenus::WORLD_IPL);
		menu::menu_option("Weather & Time", submenus::WORLD_WEATHERANDTIME);
		menu::menu_option("Object Spawner", submenus::WORLD_OBJECTSPAWNER);
		menu::menu_option("Ped Spawner", submenus::WORLD_PEDSPAWNER);

		if (menu::option("Load SP Map"))
			world::load_sp_map();
		if (menu::option("Load MP Map"))
			world::load_mp_map();
	}
	break;

	case submenus::WORLD_IPL:
	{
		menu::title("World IPL");

		menu::vector_option("IPLs", ipls_data::useful_ipls_names, g_json.m_settings.world.ipl.selected_ipl_idx, 0.01f);

		if (menu::option(std::format("Load {}", ipls_data::useful_ipls_names[g_json.m_settings.world.ipl.selected_ipl_idx])))
			world::load_known_ipl(ipls_data::useful_ipls_names[g_json.m_settings.world.ipl.selected_ipl_idx]);
		if (menu::option(std::format("Unload {}", ipls_data::useful_ipls_names[g_json.m_settings.world.ipl.selected_ipl_idx])))
			world::unload_known_ipl(ipls_data::useful_ipls_names[g_json.m_settings.world.ipl.selected_ipl_idx]);
		if (menu::option(std::format("Teleport to {}", ipls_data::useful_ipls_names[g_json.m_settings.world.ipl.selected_ipl_idx])))
			player::teleport_to(ipls_data::useful_ipls[ipls_data::useful_ipls_names[g_json.m_settings.world.ipl.selected_ipl_idx]].coords);

		menu::seperator();
		
		if (menu::option(std::format("Inputed IPL: {}", g_json.m_settings.world.ipl.last_input.empty() ? "None" : g_json.m_settings.world.ipl.last_input)))
			g_json.m_settings.world.ipl.last_input = std::get<1>(utils::keyboard_input(g_json.m_settings.world.ipl.last_input, 67));
		
		if (menu::option(std::format("Load {}", g_json.m_settings.world.ipl.last_input.empty() ? "None" : g_json.m_settings.world.ipl.last_input)))
			world::load_uknown_ipl(g_json.m_settings.world.ipl.last_input);
		if (menu::option(std::format("Unload {}", g_json.m_settings.world.ipl.last_input.empty() ? "None" : g_json.m_settings.world.ipl.last_input)))
			world::unload_uknown_ipl(g_json.m_settings.world.ipl.last_input);
	}
	break;

	case submenus::WORLD_WEATHERANDTIME:
	{
		menu::title("World Weather & Time");

		if (menu::option("Clear Weather Override"))
			world::clear_weather_override();
		if (menu::option("Clear Time Override"))
			world::clear_time_override();

		menu::vector_option("Weathers", world::weathers, g_json.m_settings.world.time_and_weather.selected_weather_idx);

		if (menu::option("Apply Weather"))
			world::set_local_weather(world::weathers[g_json.m_settings.world.time_and_weather.selected_weather_idx]);

		menu::seperator();

		if (menu::option("Sync Time"))
			world::get_local_time(g_json.m_settings.world.time_and_weather.custom_time);
		
		menu::bool_option("Always Sync Time", g_json.m_settings.world.time_and_weather.always_sync_time);

		menu::int_option("Hour", g_json.m_settings.world.time_and_weather.custom_time.hour, 0, 24);
		menu::int_option("Minutes", g_json.m_settings.world.time_and_weather.custom_time.minutes, 0, 60);
		menu::int_option("Seconds", g_json.m_settings.world.time_and_weather.custom_time.seconds, 0, 60);

		if (menu::option("Apply Custom Time"))
			world::set_local_time(g_json.m_settings.world.time_and_weather.custom_time);
	}
	break;

	case submenus::WORLD_OBJECTSPAWNER:
	{
		menu::title("World Object Spawner");

		menu::menu_option("Spawned Objects", submenus::WORLD_OBJECTSPAWNER_SPAWNEDOBJECTS);

		menu::bool_option("Spawn Where Player Is Looking", g_json.m_settings.world.object.spawn_where_looking);

		if (menu::option("Spawn Object"))
		{
			auto [state, string] = utils::keyboard_input(g_json.m_settings.world.object.last_input, 45);

			if (state == KeyboardState::CANCELLED_EDITING)
				return;

			if (
				auto obj_id = world::spawn_object(
					rage::joaat(string),
					g_json.m_settings.world.object.spawn_where_looking ? g_json.m_settings.world.object.pos : player::pos
				); obj_id != -1)
			{
				g_json.m_settings.world.object.last_input = string;

				g_json.m_settings.world.object.previous_spawned.push_back({
					std::string_view(g_json.m_settings.world.object.last_input),
					utils::get_num_of_elems(
						g_json.m_settings.world.object.previous_spawned,
						g_json.m_settings.world.object.last_input
					),
					obj_id,
					g_json.m_settings.world.object.spawn_where_looking ? g_json.m_settings.world.object.pos : player::pos
				});
			}
			else
				utils::notify::above_map(std::format("~r~{} is not a valid object!", string));
		}

		menu::seperator();

		if (menu::option(
			std::format("Inputed Object: {}", g_json.m_settings.world.object.last_input_custom.empty() ? "None" : g_json.m_settings.world.object.last_input_custom)
		))
			g_json.m_settings.world.object.last_input_custom = std::get<1>(utils::keyboard_input(g_json.m_settings.world.object.last_input_custom, 45));

		menu::bool_option("Preview Object", g_json.m_settings.world.object.preview);

		if (g_json.m_settings.world.object.preview && !g_json.m_settings.world.object.last_input_custom.empty())
			if (auto btn = menu::option("Hover To Show Preview"); btn.hovered)
				world::preview_entity(rage::joaat(g_json.m_settings.world.object.last_input_custom));

		if (menu::option("Sync Coords"))
			g_json.m_settings.world.object.pos = g_json.m_settings.world.object.spawn_where_looking ? world::get_raycast_result().end_coords : player::pos;
		menu::bool_option("Always Sync Coords", g_json.m_settings.world.object.always_sync_coords);

		menu::float_option("X", g_json.m_settings.world.object.pos.x, 0.1f, 3);
		menu::float_option("Y", g_json.m_settings.world.object.pos.y, 0.1f, 3);
		menu::float_option("Z", g_json.m_settings.world.object.pos.z, 0.1f, 3);
		menu::bool_option("Networked", g_json.m_settings.world.object.networked);
		menu::bool_option("Dynamic", g_json.m_settings.world.object.dynamic);

		if (menu::option(std::format("Spawn {}", g_json.m_settings.world.object.last_input_custom.empty() ? "None" : g_json.m_settings.world.object.last_input_custom)))
		{
			auto obj_id = world::spawn_object(
				rage::joaat(g_json.m_settings.world.object.last_input_custom),
				g_json.m_settings.world.object.pos,
				g_json.m_settings.world.object.networked,
				g_json.m_settings.world.object.dynamic
			);

			g_json.m_settings.world.object.previous_spawned.push_back({
				std::string_view(g_json.m_settings.world.object.last_input_custom),
				utils::get_num_of_elems(
					g_json.m_settings.world.object.previous_spawned,
					g_json.m_settings.world.object.last_input_custom
				),
				obj_id,
				g_json.m_settings.world.object.pos
			});
		}
	}
	break;

	case submenus::WORLD_OBJECTSPAWNER_SPAWNEDOBJECTS:
	{
		menu::title("Spawned Objects");

		if (g_json.m_settings.world.object.previous_spawned.size() != 0)
		{
			auto& selected_obj = g_json.m_settings.world.object.previous_spawned[g_json.m_settings.world.object.previous_spawned_idx];
			std::string_view formatted_obj_name;
			formatted_obj_name = std::format("{} #{}", selected_obj.name, selected_obj.internal_id).c_str();

			world::draw_entity_box(selected_obj);

			menu::object_vector_option(
				"Previous Spawned Objects",
				g_json.m_settings.world.object.previous_spawned,
				g_json.m_settings.world.object.previous_spawned_idx,
				0.01f,
				[](structs::spawned_obj obj) { return std::format("{} #{}", obj.name, obj.internal_id); }
			);

			menu::seperator();

			if (menu::option(std::format("TP To {} Spawn Location", formatted_obj_name)))
				player::teleport_to(selected_obj.pos);
			if (menu::option(std::format("TP To {} Curent Location", formatted_obj_name)))
				player::teleport_to(world::get_entity_coords(selected_obj.id));
			if (menu::option(std::format("TP {} To Me", formatted_obj_name)))
				world::teleport_entity_to(selected_obj.id, player::pos);

			if (menu::option("Sync Coords"))
				g_json.m_settings.world.object.pos = player::pos;
			menu::bool_option("Always Sync Coords", g_json.m_settings.world.object.always_sync_coords);

			menu::float_option("X", g_json.m_settings.world.object.pos.x, 0.1f, 3);
			menu::float_option("Y", g_json.m_settings.world.object.pos.y, 0.1f, 3);
			menu::float_option("Z", g_json.m_settings.world.object.pos.z, 0.1f, 3);

			if (menu::option(std::format("TP {} To Inserted Coords", formatted_obj_name)))
				world::teleport_entity_to(selected_obj.id, g_json.m_settings.world.object.pos);

			menu::seperator();

			if (menu::bool_option("Collision Physics", selected_obj.collision_physics))
				world::set_entity_collision(
					selected_obj.id,
					selected_obj.collision,
					selected_obj.collision_physics
				);
			if (menu::bool_option("Collision", selected_obj.collision))
				world::set_entity_collision(
					selected_obj.id,
					selected_obj.collision,
					selected_obj.collision_physics
				);

			menu::seperator();

			if (menu::bool_option("Freeze", selected_obj.freeze))
				world::set_entity_freeze(selected_obj.id, selected_obj.freeze);

			menu::seperator();
			
			if (menu::bool_option("Mission Entity", selected_obj.mission_entity))
				world::set_entity_mission_entity(selected_obj.id, selected_obj.mission_entity);

			menu::seperator();

			menu::int_option("Alpha", selected_obj.alpha, 0, 255);
			menu::bool_option("Alpha Skin", selected_obj.alpha_skin);
			if (menu::option("Apply Alpha"))
				world::set_entity_alpha(
					selected_obj.id,
					selected_obj.alpha,
					selected_obj.alpha_skin
				);
			if (menu::option("Reset Alpha"))
			{
				world::reset_entity_alpha(selected_obj.id);
				selected_obj.alpha = 255;
			}

			menu::seperator();

			if (menu::bool_option("Visible", selected_obj.visible))
				world::set_entity_visible(selected_obj.id, selected_obj.visible);
			if (menu::bool_option("Visible (Network)", selected_obj.visible_network))
				world::set_entity_visible_network(selected_obj.id, selected_obj.visible_network);
			if (menu::bool_option("Visible (Network, Locally)", selected_obj.locally_visible_network))
				world::set_entity_locally_visible_network(selected_obj.id);
			if (menu::bool_option("Invisible (Network, Locally)", selected_obj.locally_invisible_network))
				world::set_entity_locally_invisible_network(selected_obj.id);
			
			menu::seperator();

			if (menu::option(std::format("Delete {}", formatted_obj_name)))
			{
				OBJECT::DELETE_OBJECT(&selected_obj.id);
				g_json.m_settings.world.object.previous_spawned.erase(
					g_json.m_settings.world.object.previous_spawned.begin() +
					g_json.m_settings.world.object.previous_spawned_idx
				);

				if (g_json.m_settings.world.object.previous_spawned_idx > 0)
					g_json.m_settings.world.object.previous_spawned_idx--;
				if (g_json.m_settings.world.object.previous_spawned.size() == 0)
					menu::menu_level_handler::move_option(1);
			}
		}
		else
		{
			menu::option("No Spawned Objects");
		}
	}
	break;

	case submenus::WORLD_PEDSPAWNER:
	{
		menu::title("World Ped Spawner");

		menu::menu_option("Spawned Peds", submenus::WORLD_PEDSPAWNER_SPAWNEDPEDS);

		menu::bool_option("Spawn Where Player Is Looking", g_json.m_settings.world.ped.spawn_where_looking);

		if (menu::option("Spawn Ped"))
		{
			auto [state, string] = utils::keyboard_input(g_json.m_settings.world.ped.last_input, 25);

			if (state == KeyboardState::CANCELLED_EDITING)
				return;

			if (
				auto ped_id = world::spawn_ped(
					rage::joaat(string),
					ePedType::PED_TYPE_ARMY,
					g_json.m_settings.world.ped.spawn_where_looking ? g_json.m_settings.world.ped.pos : player::pos,
					world::get_entity_heading(player::ped)
				); ped_id != -1)
			{
				g_json.m_settings.world.ped.last_input = string;

				g_json.m_settings.world.ped.previous_spawned.push_back({
					std::string_view(g_json.m_settings.world.ped.last_input),
					utils::get_num_of_elems(
						g_json.m_settings.world.ped.previous_spawned,
						g_json.m_settings.world.ped.last_input
					),
					ped_id,
					g_json.m_settings.world.ped.spawn_where_looking ? g_json.m_settings.world.ped.pos : player::pos
				});
			}
			else
				utils::notify::above_map(std::format("~r~{} is not a valid ped!", string));
		}

		if (menu::option("Spawn Random Ped"))
			world::create_random_ped(player::pos);

		menu::seperator();

		if (menu::option(
			std::format("Inputed Ped: {}", g_json.m_settings.world.ped.last_input_custom.empty() ? "None" : g_json.m_settings.world.ped.last_input_custom)
		))
			g_json.m_settings.world.ped.last_input_custom = std::get<1>(utils::keyboard_input(g_json.m_settings.world.ped.last_input_custom, 45));

		menu::bool_option("Preview Ped", g_json.m_settings.world.ped.preview);

		if (g_json.m_settings.world.ped.preview && !g_json.m_settings.world.ped.last_input_custom.empty())
			if (auto btn = menu::option("Hover To Show Preview"); btn.hovered)
				world::preview_entity(rage::joaat(g_json.m_settings.world.ped.last_input_custom));

		if (menu::option("Sync Coords"))
			g_json.m_settings.world.ped.pos = g_json.m_settings.world.ped.spawn_where_looking ? world::get_raycast_result().end_coords : player::pos;
		menu::bool_option("Always Sync Coords", g_json.m_settings.world.ped.always_sync_coords);

		menu::float_option("X", g_json.m_settings.world.ped.pos.x, 0.1f, 3);
		menu::float_option("Y", g_json.m_settings.world.ped.pos.y, 0.1f, 3);
		menu::float_option("Z", g_json.m_settings.world.ped.pos.z, 0.1f, 3);
		menu::float_option("Heading", g_json.m_settings.world.ped.heading, 0.1f, 3);
		menu::bool_option("Networked", g_json.m_settings.world.ped.networked);
		menu::vector_option("Ped Type", ped_data::ped_types, g_json.m_settings.world.ped.selected_type_idx);

		if (menu::option(std::format("Spawn {}", g_json.m_settings.world.ped.last_input_custom.empty() ? "None" : g_json.m_settings.world.ped.last_input_custom)))
		{
			auto ped_id = world::spawn_ped(
				rage::joaat(g_json.m_settings.world.ped.last_input_custom),
				static_cast<ePedType>(g_json.m_settings.world.ped.selected_type_idx),
				g_json.m_settings.world.ped.pos,
				g_json.m_settings.world.ped.heading,
				g_json.m_settings.world.ped.networked
			);

			g_json.m_settings.world.ped.previous_spawned.push_back({
				std::string_view(g_json.m_settings.world.ped.last_input_custom),
				utils::get_num_of_elems(
					g_json.m_settings.world.ped.previous_spawned,
					g_json.m_settings.world.ped.last_input_custom
				),
				ped_id,
				g_json.m_settings.world.ped.pos
			});

			// set the ped's health and armor
			auto& itm = g_json.m_settings.world.ped.previous_spawned[g_json.m_settings.world.ped.previous_spawned.size() - 1];
			itm.health = world::get_entity_health(itm.id);
			itm.armor = world::get_ped_armor(itm.id);
		}

		if (menu::option("Spawn Random Ped At Coords"))
			world::create_random_ped(g_json.m_settings.world.ped.pos);
	}
	break;

	case submenus::WORLD_PEDSPAWNER_SPAWNEDPEDS:
	{
		menu::title("Spawned Peds");

		if (g_json.m_settings.world.ped.previous_spawned.size() != 0)
		{
			auto& selected_ped = g_json.m_settings.world.ped.previous_spawned[g_json.m_settings.world.ped.previous_spawned_idx];
			std::string_view formatted_ped_name;
			formatted_ped_name = std::format("{} #{}", selected_ped.name, selected_ped.internal_id).c_str();

			world::draw_entity_box(selected_ped);

			menu::ped_vector_option(
				"Previous Spawned Peds",
				g_json.m_settings.world.ped.previous_spawned,
				g_json.m_settings.world.ped.previous_spawned_idx,
				0.01f,
				[](structs::spawned_ped ped) { return std::format("{} #{}", ped.name, ped.internal_id); }
			);

			menu::seperator();

			if (menu::option(std::format("TP To {} Spawn Location", formatted_ped_name)))
				player::teleport_to(selected_ped.pos);
			if (menu::option(std::format("TP To {} Curent Location", formatted_ped_name)))
				player::teleport_to(world::get_entity_coords(selected_ped.id));
			if (menu::option(std::format("TP {} To Me", formatted_ped_name)))
				world::teleport_entity_to(selected_ped.id, player::pos);
			if (menu::option(std::format("TP {} To Vehicle", formatted_ped_name)))
				world::teleport_ped_to_vehicle(selected_ped.id, player::veh);

			if (menu::option("Sync Coords"))
				g_json.m_settings.world.ped.pos = player::pos;
			menu::bool_option("Always Sync Coords", g_json.m_settings.world.ped.always_sync_coords);

			menu::float_option("Y", g_json.m_settings.world.ped.pos.y, 0.1f, 3);
			menu::float_option("Z", g_json.m_settings.world.ped.pos.z, 0.1f, 3);
			menu::float_option("X", g_json.m_settings.world.ped.pos.x, 0.1f, 3);

			if (menu::option(std::format("TP {} To Inserted Coords", formatted_ped_name)))
				world::teleport_entity_to(selected_ped.id, g_json.m_settings.world.ped.pos);

			menu::seperator();

			menu::int_option("Set Ped Health", selected_ped.health, 0, world::get_entity_max_health(selected_ped.id));
			menu::int_option("Set Ped Armor", selected_ped.armor);

			if (menu::option("Apply Health"))
				world::set_entity_health(selected_ped.id, selected_ped.health);
			if (menu::option("Apply Armor"))
				world::set_ped_armor(selected_ped.id, selected_ped.armor);

			menu::seperator();

			if (menu::bool_option("Collision Physics", selected_ped.collision_physics))
				world::set_entity_collision(
					selected_ped.id,
					selected_ped.collision,
					selected_ped.collision_physics
				);
			if (menu::bool_option("Collision", selected_ped.collision))
				world::set_entity_collision(
					selected_ped.id,
					selected_ped.collision,
					selected_ped.collision_physics
				);

			menu::seperator();

			if (menu::bool_option("Freeze", selected_ped.freeze))
				world::set_entity_freeze(selected_ped.id, selected_ped.freeze);

			menu::seperator();

			if (menu::bool_option("Mission Entity", selected_ped.mission_entity))
				world::set_entity_mission_entity(selected_ped.id, selected_ped.mission_entity);

			menu::seperator();

			menu::int_option("Alpha", selected_ped.alpha, 0, 255);
			menu::bool_option("Alpha Skin", selected_ped.alpha_skin);
			if (menu::option("Apply Alpha"))
				world::set_entity_alpha(
					selected_ped.id,
					selected_ped.alpha,
					selected_ped.alpha_skin
				);
			if (menu::option("Reset Alpha"))
			{
				world::reset_entity_alpha(selected_ped.id);
				selected_ped.alpha = 255;
			}

			menu::seperator();

			if (menu::bool_option("Visible", selected_ped.visible))
				world::set_entity_visible(selected_ped.id, selected_ped.visible);
			if (menu::bool_option("Visible (Network)", selected_ped.visible_network))
				world::set_entity_visible_network(selected_ped.id, selected_ped.visible_network);
			if (menu::bool_option("Visible (Network, Locally)", selected_ped.locally_visible_network))
				world::set_entity_locally_visible_network(selected_ped.id);
			if (menu::bool_option("Invisible (Network, Locally)", selected_ped.locally_invisible_network))
				world::set_entity_locally_invisible_network(selected_ped.id);

			menu::seperator();

			if (menu::option(std::format("Delete {}", formatted_ped_name)))
			{
				PED::DELETE_PED(&selected_ped.id);
				g_json.m_settings.world.ped.previous_spawned.erase(
					g_json.m_settings.world.ped.previous_spawned.begin() +
					g_json.m_settings.world.ped.previous_spawned_idx
				);

				if (g_json.m_settings.world.ped.previous_spawned_idx > 0)
					g_json.m_settings.world.ped.previous_spawned_idx--;
				if (g_json.m_settings.world.ped.previous_spawned.size() == 0)
					menu::menu_level_handler::move_option(1);
			}
		}
		else
		{
			menu::option("No Spawned Peds");
		}
	}
	break;


	case submenus::ONLINE:
	{
		menu::title("Online");

		if (menu::vector_option("Join Session", sessions_data::session_types, g_json.m_settings.online.session_type_idx))
			player::join_session(sessions_data::str_to_session[sessions_data::session_types[g_json.m_settings.online.session_type_idx]]);

		menu::bool_option("No Idle Kick", g_json.m_settings.online.no_idle_kick);
	}
	break;


	case submenus::SETTINGS:
	{
		menu::title("Settings Menu");

		menu::menu_option("Input", submenus::SETTINGS_INPUT);
		menu::menu_option("Theme", submenus::SETTINGS_THEME);

		if (menu::option("Unload")) 
			pico::g_running = false;
		if (menu::option("Exit Game")) 
			exit(0);
	}
	break;

	case submenus::SETTINGS_INPUT:
	{
		menu::title("Input");

		std::size_t input_type = static_cast<size_t>(g_json.m_settings.settings.input.type);

		menu::vector_option("Input Types", looped_vals::settings::input_types, input_type);

		g_json.m_settings.settings.input.type = static_cast<MenuInputType>(input_type);

		if (static_cast<MenuInputType>(looped_vals::settings::input_types_idx) == MenuInputType::CUSTOM)
		{
			menu::vector_option("Open Key", key_codes::names, looped_vals::settings::open_idx, 0.01f);
			menu::vector_option("Back Key", key_codes::names, looped_vals::settings::back_idx, 0.01f);
			menu::vector_option("Up Key", key_codes::names, looped_vals::settings::up_idx, 0.01f);
			menu::vector_option("Down Key", key_codes::names, looped_vals::settings::down_idx, 0.01f);
			menu::vector_option("Left Key", key_codes::names, looped_vals::settings::left_idx, 0.01f);
			menu::vector_option("Right Key", key_codes::names, looped_vals::settings::right_idx, 0.01f);
			menu::vector_option("Select Key", key_codes::names, looped_vals::settings::select_idx, 0.01f);
			menu::vector_option("Escape Key", key_codes::names, looped_vals::settings::esc_idx, 0.01f);
		}

		if (menu::option("Apply"))
		{
			if (auto type = static_cast<MenuInputType>(looped_vals::settings::input_types_idx); type < MenuInputType::CUSTOM)
				pico::g_custom_input.apply_preset(type);
			else
			{
				pico::g_custom_input.change_key(InputHook::open_key, key_codes::keys[key_codes::names[looped_vals::settings::open_idx]]);
				pico::g_custom_input.change_key(InputHook::back_key, key_codes::keys[key_codes::names[looped_vals::settings::back_idx]]);
				pico::g_custom_input.change_key(InputHook::up_key, key_codes::keys[key_codes::names[looped_vals::settings::up_idx]]);
				pico::g_custom_input.change_key(InputHook::down_key, key_codes::keys[key_codes::names[looped_vals::settings::down_idx]]);
				pico::g_custom_input.change_key(InputHook::left_key, key_codes::keys[key_codes::names[looped_vals::settings::left_idx]]);
				pico::g_custom_input.change_key(InputHook::right_key, key_codes::keys[key_codes::names[looped_vals::settings::right_idx]]);
				pico::g_custom_input.change_key(InputHook::select_key, key_codes::keys[key_codes::names[looped_vals::settings::select_idx]]);
				pico::g_custom_input.change_key(InputHook::esc_key, key_codes::keys[key_codes::names[looped_vals::settings::esc_idx]]);
			}
		}
	}
	break;

	case submenus::SETTINGS_THEME:
	{
		menu::title("Theme Menu");

		menu::menu_option("Title Text", submenus::SETTINGS_THEME_TITLETEXT);
		menu::menu_option("Title Background", submenus::SETTINGS_THEME_TITLERECT);
		menu::menu_option("Submenu Bar Text", submenus::SETTINGS_THEME_SUBMENUBARTEXT);
		menu::menu_option("Submenu Bar Background", submenus::SETTINGS_THEME_SUBMENUBARRECT);
		menu::menu_option("Submenu Arrow", submenus::SETTINGS_THEME_SUBMENUARROW);
		menu::menu_option("Option Text", submenus::SETTINGS_THEME_OPTIONTEXT);
		menu::menu_option("Option Background", submenus::SETTINGS_THEME_OPTIONRECT);
		menu::menu_option("Seperator Background", submenus::SETTINGS_THEME_SEPERATORRECT);
		menu::menu_option("Footer Text", submenus::SETTINGS_THEME_FOOTERTEXT);
		menu::menu_option("Footer Background", submenus::SETTINGS_THEME_FOOTERRECT);

		if (menu::option("Revert To Default"))
		{
			g_json.m_settings.settings.theme.title_text = { 255, 255, 255, 255, 1 };
			g_json.m_settings.settings.theme.title_background = { 3, 140, 252, 255 };
			g_json.m_settings.settings.theme.submenu_bar_text = { 255, 255, 255, 255, 4 };
			g_json.m_settings.settings.theme.submenu_bar_background = { 0, 0, 0, 190 };
			g_json.m_settings.settings.theme.submenu_rect = { 3, 140, 252, 255 };
			g_json.m_settings.settings.theme.option_unselected_text = { 255, 255, 255, 255, 4 };
			g_json.m_settings.settings.theme.option_selected_text = { 10, 10, 10, 255, 4 };
			g_json.m_settings.settings.theme.option_unselected_background = { 0, 0, 0, 160 };
			g_json.m_settings.settings.theme.option_selected_background = { 255, 255, 255, 255 };
			g_json.m_settings.settings.theme.seperator_background = { 0, 0, 0, 210 };
			g_json.m_settings.settings.theme.footer_text = { 255, 255, 255, 255, 4 };
			g_json.m_settings.settings.theme.footer_background = { 0, 0, 0, 220 };
			g_json.m_settings.settings.theme.footer_sprite = { 255, 255, 255, 255 };
		}
	}
	break;

	case submenus::SETTINGS_THEME_TITLETEXT:
	{
		menu::title("Title Text");
		
		menu::int_option("Red", g_json.m_settings.settings.theme.title_text.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.title_text.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.title_text.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.title_text.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_TITLERECT:
	{
		menu::title("Title Background");

		menu::int_option("Red", g_json.m_settings.settings.theme.title_background.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.title_background.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.title_background.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.title_background.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_SUBMENUBARTEXT:
	{
		menu::title("Submenu Bar Text");

		menu::int_option("Red", g_json.m_settings.settings.theme.submenu_bar_text.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.submenu_bar_text.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.submenu_bar_text.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.submenu_bar_text.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_SUBMENUBARRECT:
	{
		menu::title("Submenu Bar Background");

		menu::int_option("Red", g_json.m_settings.settings.theme.submenu_bar_background.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.submenu_bar_background.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.submenu_bar_background.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.submenu_bar_background.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_SUBMENUARROW:
	{
		menu::title("Submenu Arrow");

		menu::int_option("Red", g_json.m_settings.settings.theme.submenu_rect.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.submenu_rect.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.submenu_rect.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.submenu_rect.a, 0, 255);
	}
	break;

	case SETTINGS_THEME_OPTIONTEXT:
	{
		menu::title("Option Text");

		menu::option("Unselected:");
		menu::int_option("Red", g_json.m_settings.settings.theme.option_unselected_text.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.option_unselected_text.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.option_unselected_text.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.option_unselected_text.a, 0, 255);

		menu::option("Selected:");
		menu::int_option("Red", g_json.m_settings.settings.theme.option_selected_text.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.option_selected_text.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.option_selected_text.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.option_selected_text.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_OPTIONRECT:
	{
		menu::title("Option Background");

		menu::option("Unselected:");
		menu::int_option("Red", g_json.m_settings.settings.theme.option_unselected_background.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.option_unselected_background.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.option_unselected_background.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.option_unselected_background.a, 0, 255);

		menu::option("Selected:");
		menu::int_option("Red", g_json.m_settings.settings.theme.option_selected_background.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.option_selected_background.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.option_selected_background.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.option_selected_background.a, 0, 255);
	}
	break;
	
	case submenus::SETTINGS_THEME_SEPERATORRECT:
	{
		menu::title("Seperator Background");
		
		menu::seperator();

		menu::int_option("Red", g_json.m_settings.settings.theme.seperator_background.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.seperator_background.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.seperator_background.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.seperator_background.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_FOOTERTEXT:
	{
		menu::title("Footer Text");

		menu::option("Text:");
		menu::int_option("Red", g_json.m_settings.settings.theme.footer_text.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.footer_text.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.footer_text.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.footer_text.a, 0, 255);

		menu::option("Sprite:");
		menu::int_option("Red", g_json.m_settings.settings.theme.footer_sprite.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.footer_sprite.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.footer_sprite.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.footer_sprite.a, 0, 255);
	}
	break;

	case submenus::SETTINGS_THEME_FOOTERRECT:
	{
		menu::title("Footer Background");

		menu::int_option("Red", g_json.m_settings.settings.theme.footer_background.r, 0, 255);
		menu::int_option("Green", g_json.m_settings.settings.theme.footer_background.g, 0, 255);
		menu::int_option("Blue", g_json.m_settings.settings.theme.footer_background.b, 0, 255);
		menu::int_option("Alpha", g_json.m_settings.settings.theme.footer_background.a, 0, 255);
	}
	break;
	}
	menu::end();
}

void script_main() 
{
	key_codes::init_names();
	weapons_data::init_names();
	ipls_data::init_names();

	while (pico::g_running)
	{
		functions::looped_vals::features_loop();
		pico_menu();
		menu::checks::keys();
		menu::reset_optioncount();

		WAIT(0);
	}
}