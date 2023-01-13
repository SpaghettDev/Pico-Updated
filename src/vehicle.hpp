#pragma once
#include "stdafx.hpp"
#include "player.hpp"

namespace // from YimMenu
{
	static const std::map<Hash, std::map<int, std::vector<int32_t>>> mod_blacklists = {
		{ rage::joaat("BANSHEE"), {
			{ VehicleModType::MOD_SPOILERS, { 3, 4 } },
			{ VehicleModType::MOD_COLUMNSHIFTERLEVERS, { 0, 1, 2, 3 } },
			{ VehicleModType::MOD_SPEAKERS, { 0 } },
			{ VehicleModType::MOD_LIVERY, { 15, 16 } }
		} },
		{ rage::joaat("SENTINEL"), {
			{ VehicleModType::MOD_SPOILERS, { 4, 5 } },
			{ VehicleModType::MOD_COLUMNSHIFTERLEVERS, { 0, 1, 2, 3 } },
			{ VehicleModType::MOD_SPEAKERS, { 0 } },
			{ VehicleModType::MOD_LIVERY, { 0, 1 } }
		} }
	};

	bool check_mod_blacklist(Hash model, int mod_slot, int mod)
	{
		if (mod_blacklists.find(model) == mod_blacklists.end())
			return false;

		auto& veh_slot_blacklist = mod_blacklists.find(model)->second;
		if (veh_slot_blacklist.find(mod_slot) == veh_slot_blacklist.end())
			return false;

		auto& veh_mod_blacklist = veh_slot_blacklist.find(mod_slot)->second;
		if (std::find(veh_mod_blacklist.begin(), veh_mod_blacklist.end(), mod) != veh_mod_blacklist.end())
			return true;

		return false;
	}
}

namespace functions::vehicle
{
	bool spawn_vehicle(Hash name, Vector3 position, bool networked = true)
	{
		if (!utils::request_model(name) || !STREAMING::IS_MODEL_IN_CDIMAGE(name) || !STREAMING::IS_MODEL_VALID(name) || !STREAMING::IS_MODEL_A_VEHICLE(name))
			return false;

		*reinterpret_cast<unsigned short*>(g_hooking.m_ModelSpawnBypass) = 0x9090;
		Vehicle vehicle = VEHICLE::CREATE_VEHICLE(name, position.x, position.y, position.z, 0.f, networked, false, false);
		*reinterpret_cast<unsigned short*>(g_hooking.m_ModelSpawnBypass) = 0x0574;

		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(name);

		if (*g_hooking.m_IsSessionStarted && networked)
		{
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(vehicle, true);
			int netID = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, false);
		}

		return true;
	}

	void max_vehicle(Vehicle veh)
	{
		Hash model = ENTITY::GET_ENTITY_MODEL(veh);

		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		VEHICLE::TOGGLE_VEHICLE_MOD(veh, VehicleModType::MOD_TURBO, true);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, VehicleModType::MOD_TYRE_SMOKE, true);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, VehicleModType::MOD_XENON_LIGHTS, true);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);

		for (int slot = VehicleModType::MOD_SPOILERS; slot <= VehicleModType::MOD_LIGHTBAR; slot++)
		{
			if (slot == VehicleModType::MOD_LIVERY)
				continue;

			int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, slot);
			if (count > 0)
			{
				int selected_mod = -1;

				for (int mod = count - 1; mod >= -1; mod--)
				{
					if (check_mod_blacklist(model, slot, mod))
						continue;

					selected_mod = mod;
					break;
				}

				if (selected_mod != -1)
					VEHICLE::SET_VEHICLE_MOD(veh, slot, selected_mod, true);
			}
		}
	}

	bool repair(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !utils::take_control_of(veh))
			return false;

		VEHICLE::SET_VEHICLE_FIXED(veh);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);

		return true;
	}

	void change_proof_bit(std::uint32_t proof)
	{
		static uint32_t last_bits = 0;

		uint32_t bits = proof;
		uint32_t changed_bits = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = player::local_player->m_vehicle->m_damage_bits & ~changed_or_enabled_bits;
			player::local_player->m_vehicle->m_damage_bits = unchanged_bits | bits;
			last_bits = bits;
		}
	}

	void collision_proof(bool toggle)
	{
		if (player::local_player->m_ped_task_flag & static_cast<int>(ePedTask::TASK_DRIVING))
		{
			if (toggle)
				player::local_player->m_vehicle->m_deform_god = 0x8C;
		}
		else if (!toggle && player::local_player->m_vehicle->m_deform_god != 0x9C)
			player::local_player->m_vehicle->m_deform_god = 0x9C;
	}

	void horn_boost(Vehicle veh)
	{
		static constexpr float horn_boost_speed_default = 10.f;
		static constexpr float horn_boost_speed_max = 200.f;

		static float horn_boost_speed = horn_boost_speed_default;

		if (!veh)
		{
			horn_boost_speed = horn_boost_speed_default;
			return;
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, static_cast<int>(ControllerInputs::INPUT_VEH_HORN)))
			horn_boost_speed = ENTITY::GET_ENTITY_SPEED(veh);

		if (PAD::IS_CONTROL_PRESSED(0, static_cast<int>(ControllerInputs::INPUT_VEH_HORN)))
		{
			if (horn_boost_speed < horn_boost_speed_max)
				horn_boost_speed += horn_boost_speed_increment;

			const auto velocity =
				ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, 0.f, horn_boost_speed, 0.f) - ENTITY::GET_ENTITY_COORDS(veh, true);

			ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);
		}
		else if (PAD::IS_CONTROL_JUST_RELEASED(0, static_cast<int>(ControllerInputs::INPUT_VEH_HORN)))
			horn_boost_speed = horn_boost_speed_default;
	}
}