#pragma once
#include "stdafx.hpp"

namespace
{
	auto notify_feature = [](std::string feature_name, std::string text) -> void {
		functions::utils::notify::display_help_text(std::format("{}: {}!", feature_name, text));
	};

	// from YimMenu
	bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ = 0.f;
		const std::uint8_t attempts = 10;

		for (std::uint8_t i = 0; i <= attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (std::uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, static_cast<float>(z));

				WAIT(0);
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;
				return true;
			}

			WAIT(0);
		}

		location.z = 1000.f;
		return false;
	}

	bool get_blip_location(Vector3& location, BlipIcons sprite, BlipColors color = BlipColors::Invalid)
	{
		Blip blip = 0;

		for (
			blip = HUD::GET_FIRST_BLIP_INFO_ID(static_cast<int>(sprite));
			HUD::DOES_BLIP_EXIST(blip) && color != BlipColors::Invalid && HUD::GET_BLIP_COLOUR(blip) != static_cast<int>(color);
			blip = HUD::GET_NEXT_BLIP_INFO_ID(static_cast<int>(sprite))
			);

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != BlipColors::Invalid && HUD::GET_BLIP_COLOUR(blip) != static_cast<int>(color)))
			return false;

		location = HUD::GET_BLIP_COORDS(blip);
		return true;
	}

	bool get_objective_location(Vector3& location)
	{
		if (
			get_blip_location(location, BlipIcons::Circle, BlipColors::YellowMission) ||
			get_blip_location(location, BlipIcons::Circle, BlipColors::YellowMission2) ||
			get_blip_location(location, BlipIcons::Circle, BlipColors::Mission) ||
			get_blip_location(location, BlipIcons::RaceFinish, BlipColors::None) ||
			get_blip_location(location, BlipIcons::Circle, BlipColors::Green) ||
			get_blip_location(location, BlipIcons::Circle, BlipColors::Blue) ||
			get_blip_location(location, BlipIcons::CrateDrop)
			) return true;

		const BlipIcons blips[] = {
			Circle, Circle2, Circle3, Circle4, Circle5, Circle6, Circle7, Circle8, Circle9, Circle10, Circle11, Circle12, Circle13
		};
		for (const auto& blip : blips)
			if (get_blip_location(location, blip, BlipColors::YellowMission))
				return true;

		return false;
	}

	template<typename T>
	std::ptrdiff_t get_index_from_vec(std::vector<T> vec, T key)
	{
		auto it = std::find(vec.begin(), vec.end(), key);

		return it != vec.end() ? it - vec.begin() : -1;
	}
}

namespace functions::player
{
#pragma region usefuls
	CPed* get_local_ped()
	{
		if (auto ped_factory = *g_hooking.m_WorldPointer; ped_factory)
			return ped_factory->m_local_ped;

		return nullptr;
	}

	CVehicle* get_local_vehicle()
	{
		if (const auto ped = get_local_ped(); ped)
			if (const auto veh = ped->m_vehicle; veh)
				return veh;

		return nullptr;
	}

	CPlayerInfo* get_local_playerinfo()
	{
		if (auto ped = get_local_ped(); ped)
			return ped->m_player_info;

		return nullptr;
	}

	void update_local_player()
	{
		local_player = get_local_ped();
	}

	void update_globals()
	{
		player::id = PLAYER::PLAYER_ID();
		player::ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player::id);
		player::pos = world::get_entity_coords(player::ped);

		player::veh = PED::IS_PED_IN_ANY_VEHICLE(player::ped, false) ? PED::GET_VEHICLE_PED_IS_IN(player::ped, false) : 0;
	}

	void get_active_character_slot(int* character_slot)
	{
		STATS::STAT_GET_INT(rage::joaat("MPPLY_LAST_MP_CHAR"), character_slot, true);
	}

	std::string get_mp_prefix()
	{
		get_active_character_slot(&player::char_slot);

		return "MP" + std::to_string(player::char_slot) + "_";
	}
#pragma endregion
	
	void change_proof_bit(std::uint32_t proof)
	{
		static uint32_t last_bits = 0;

		uint32_t changed_bits = proof ^ last_bits;
		uint32_t changed_or_enabled_bits = proof | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = local_player->m_damage_bits & ~changed_or_enabled_bits;
			local_player->m_damage_bits = unchanged_bits | proof;
			last_bits = proof;
		}
	}

	void max_health()
	{
		int ped_health = PED::GET_PED_MAX_HEALTH(player::ped);

		ENTITY::SET_ENTITY_HEALTH(player::ped, ped_health, 0);
		notify_feature("Health", std::format("Maxed at {}%", ped_health));
	}
	
	void max_armor()
	{
		int ped_armor = PLAYER::GET_PLAYER_MAX_ARMOUR(player::id);

		PED::SET_PED_ARMOUR(player::ped, ped_armor);
		notify_feature("Armor", std::format("Maxed at {}%", ped_armor));
	}

	void max_ammo()
	{
		int max_ammo = 0;
		WEAPON::GET_MAX_AMMO(player::ped, WEAPON::GET_SELECTED_PED_WEAPON(player::ped), &max_ammo);
		WEAPON::SET_PED_AMMO(player::ped, WEAPON::GET_SELECTED_PED_WEAPON(player::ped), max_ammo, false);

		notify_feature("Weapon", std::format("Maxed ammo at {}", max_ammo));
	}

	void max_clip()
	{
		int max_clip = WEAPON::GET_MAX_AMMO_IN_CLIP(player::ped, WEAPON::GET_SELECTED_PED_WEAPON(player::ped), true);
		WEAPON::SET_AMMO_IN_CLIP(player::ped, WEAPON::GET_SELECTED_PED_WEAPON(player::ped), max_clip);

		notify_feature("Weapon", std::format("Maxed clip at {}", max_clip));
	}
	
	void suicide()
	{
		ENTITY::SET_ENTITY_HEALTH(player::ped, 0, 0);
	}

	void clean_ped(Ped ped, bool notify = true)
	{
		PED::CLEAR_PED_BLOOD_DAMAGE(ped);
		PED::CLEAR_PED_WETNESS(ped);
		PED::CLEAR_PED_ENV_DIRT(ped);
		PED::RESET_PED_VISIBLE_DAMAGE(ped);

		if (notify)
			notify_feature("Ped", "Cleaned ped");
	}

	void fill_inventory()
	{
		std::string mpPrefix = player::get_mp_prefix();

		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_YUM_SNACKS"), 30, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_HEALTH_SNACKS"), 15, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "NO_BOUGHT_EPIC_SNACKS"), 5, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_1_COUNT"), 10, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_2_COUNT"), 10, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_3_COUNT"), 10, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_4_COUNT"), 10, true);
		STATS::STAT_SET_INT(rage::joaat(mpPrefix + "MP_CHAR_ARMOUR_5_COUNT"), 10, true);

		notify_feature("Inventory", "Filled armor count & snacks");
	}

	void set_wanted_level(int level)
	{
		player::local_player->m_player_info->m_wanted_level = level <= 5 ? level : 5;
	}

	void clear_wanted_level()
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player::id) > 0)
			player::local_player->m_player_info->m_wanted_level = 0;

		notify_feature("Wanted Level", "Cleared wanted level");
	}


	void get_all_weapons()
	{
		for (const auto& [name, hash] : weapons_data::weapons)
		{
			if (name.starts_with("WEAPON_"))
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(player::ped, hash, 9999, false);
		}

		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(player::ped, weapons_data::weapons.find("GADGET_PARACHUTE")->second, 0, false);

		notify_feature("Weapon", "Got all weapons");
	}
	
	void get_weapon(std::string_view name)
	{
		if (auto hash = rage::joaat(name); WEAPON::IS_WEAPON_VALID(hash) || weapons_data::weapons.find(name) != weapons_data::weapons.end())
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(player::ped, hash, 9999, false);

			notify_feature("Weapon", std::format("Got {}", name));
		}
	}
	
	void remove_all_weapons()
	{
		for (const auto& [name, hash] : weapons_data::weapons)
		{
			if (name == "WEAPON_UNARMED") continue;

			if (name.starts_with("WEAPON_"))
				WEAPON::REMOVE_WEAPON_FROM_PED(player::ped, hash);
		}

		WEAPON::REMOVE_WEAPON_FROM_PED(player::ped, weapons_data::weapons.find("GADGET_PARACHUTE")->second);

		notify_feature("Weapon", "Removed all weapons");
	}

	void remove_weapon(std::string_view name)
	{
		if (name == "WEAPON_UNARMED") return;

		if (auto hash = rage::joaat(name); WEAPON::IS_WEAPON_VALID(hash) || weapons_data::weapons.find(name) != weapons_data::weapons.end())
		{
			WEAPON::REMOVE_WEAPON_FROM_PED(player::ped, hash);

			notify_feature("Weapon", std::format("Removed {}", name));
		}
	}

	void get_all_weapons_upgrades()
	{
		// what in the name of leaning tower of piza
		for (const auto& [weapon_name, upgrades] : weapons_data::weapons_upgrades)
			if (WEAPON::HAS_PED_GOT_WEAPON(player::ped, rage::joaat(weapon_name), false))
				for (const auto& upgrade : upgrades)
					if (!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade)))
						WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade));

		notify_feature("Weapon", "Got all weapon upgrades");
		
	}

	void get_weapon_upgrade(std::string_view weapon_name, std::string_view upgrade_name)
	{
		if (weapons_data::weapons_upgrades.find(weapon_name) != weapons_data::weapons_upgrades.end())
		{
			if (get_index_from_vec(weapons_data::weapons_upgrades[weapon_name], upgrade_name) != -1)
				if (WEAPON::HAS_PED_GOT_WEAPON(player::ped, rage::joaat(weapon_name), false))
					if (!WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade_name)))
					{
						WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade_name));

						notify_feature("Weapon", std::format("Got {}", upgrade_name));
					}
		}
		else
			notify_feature("Weapon", std::format("{} is not an upgrade!", upgrade_name));
	}

	void remove_all_weapons_upgrades()
	{
		for (const auto& [weapon_name, upgrades] : weapons_data::weapons_upgrades)
			if (WEAPON::HAS_PED_GOT_WEAPON(player::ped, rage::joaat(weapon_name), false))
				for (const auto& upgrade : upgrades)
					if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade)))
						WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade));

		notify_feature("Weapon", "Removed all weapon upgrades");

	}

	void remove_weapon_upgrade(std::string_view weapon_name, std::string_view upgrade_name)
	{
		if (weapons_data::weapons_upgrades.find(weapon_name) != weapons_data::weapons_upgrades.end())
			if (get_index_from_vec(weapons_data::weapons_upgrades[weapon_name], upgrade_name) != -1)
				if (WEAPON::HAS_PED_GOT_WEAPON(player::ped, rage::joaat(weapon_name), false))
					if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade_name)))
					{
						WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(player::ped, rage::joaat(weapon_name), rage::joaat(upgrade_name));

						notify_feature("Weapon", std::format("Removed {}", upgrade_name));
					}

		notify_feature("Weapon", std::format("{} is not an upgrade!", upgrade_name));
	}


	void teleport_to(Vector3 coords)
	{
		PED::SET_PED_COORDS_KEEP_VEHICLE(player::ped, coords.x, coords.y, coords.z + 1.f);
	}

	bool teleport_to_blip(BlipIcons sprite, BlipColors color = BlipColors::Invalid)
	{
		Vector3 location;

		if (!get_blip_location(location, sprite, color))
			return false;

		if (sprite == BlipIcons::Waypoint)
			load_ground_at_3dcoord(location);

		teleport_to(location);

		return true;
	}

	void teleport_to_waypoint()
	{
		if (!teleport_to_blip(BlipIcons::Waypoint))
		{
			notify_feature("Teleport", "Couldn't find waypoint blip");
			return;
		}
	}

	void teleport_to_objective()
	{
		Vector3 location;

		if (!get_objective_location(location))
		{
			notify_feature("Teleport", "Couldn't find objective blip");
			return;
		}

		PED::SET_PED_COORDS_KEEP_VEHICLE(player::ped, location.x, location.y, location.z);
	}



	// temporarily in player.hpp
	void join_session(eSessionType type)
	{
		*script_global(2695915).as<int*>() = (type == eSessionType::SC_TV ? 1 : 0); // If SC TV Then Enable Spectator Mode

		if (type == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).add(2).as<int*>() = -1;
		else
			*script_global(1575017).as<int*>() = static_cast<int>(type);

		*script_global(1574589).as<int*>() = 1;
		std::this_thread::sleep_for(200ms);
		*script_global(1574589).as<int*>() = 0;
	}
}