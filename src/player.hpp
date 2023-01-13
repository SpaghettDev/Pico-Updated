#pragma once
#include "stdafx.hpp"

namespace functions::player
{
#pragma region usefuls
	inline CPed* get_local_ped()
	{
		if (auto ped_factory = *g_hooking.m_WorldPointer; ped_factory)
			return ped_factory->m_local_ped;

		return nullptr;
	}

	inline CVehicle* get_local_vehicle()
	{
		if (const auto ped = get_local_ped(); ped)
			if (const auto veh = ped->m_vehicle; veh)
				return veh;

		return nullptr;
	}

	inline CPlayerInfo* get_local_playerinfo()
	{
		if (auto ped = get_local_ped(); ped)
			return ped->m_player_info;

		return nullptr;
	}

	inline void update_local_player()
	{
		local_player = get_local_ped();
	}

	inline void update_globals()
	{
		player::id = PLAYER::PLAYER_ID();

		player::ped = PLAYER::PLAYER_PED_ID();

		player::pos = ENTITY::GET_ENTITY_COORDS(player::ped, false);

		if (PED::IS_PED_IN_ANY_VEHICLE(player::ped, false))
			player::veh = PED::GET_VEHICLE_PED_IS_IN(player::ped, false);
		else
			player::veh = 0;
	}

	inline void get_active_character_slot(int* character_slot)
	{
		STATS::STAT_GET_INT(rage::joaat("MPPLY_LAST_MP_CHAR"), character_slot, true);
	}

	inline std::string get_mp_prefix()
	{
		get_active_character_slot(&player::char_slot);

		return "MP" + std::to_string(player::char_slot) + "_";
	}
#pragma endregion
	
	inline void change_proof_bit(std::uint32_t proof)
	{
		static uint32_t last_bits = 0;

		if (local_player == nullptr) return;

		uint32_t changed_bits = proof ^ last_bits;
		uint32_t changed_or_enabled_bits = proof | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = local_player->m_damage_bits & ~changed_or_enabled_bits;
			local_player->m_damage_bits = unchanged_bits | proof;
			last_bits = proof;
		}
	}

	inline void max_health()
	{
		ENTITY::SET_ENTITY_HEALTH(player::ped, PED::GET_PED_MAX_HEALTH(player::ped), 0);
	}
	
	inline void max_armor()
	{
		PED::SET_PED_ARMOUR(player::ped, PLAYER::GET_PLAYER_MAX_ARMOUR(player::id));
	}
	
	inline void suicide()
	{
		ENTITY::SET_ENTITY_HEALTH(player::ped, 0, 0);
	}

	inline void clean_ped(Ped ped)
	{
		PED::CLEAR_PED_BLOOD_DAMAGE(ped);
		PED::CLEAR_PED_WETNESS(ped);
		PED::CLEAR_PED_ENV_DIRT(ped);
		PED::RESET_PED_VISIBLE_DAMAGE(ped);
	}

	inline void fill_inventory()
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
	}

	inline void set_wanted_level(int level)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(player::id, level, false);
	}

	inline void clear_wanted_level()
	{
		if (PLAYER::GET_PLAYER_WANTED_LEVEL(player::id) > 0)
			PLAYER::SET_PLAYER_WANTED_LEVEL(player::id, 0, false);
	}
}