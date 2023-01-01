#pragma once
#include "stdafx.h"
#include "joaat.hpp"
#include "misc.hpp"

namespace vehicle
{
	void spawn_vehicle(std::string name)
	{
		Hash vehicle_hash = rage::joaat(name);

		if (!misc::request_model(name) || !STREAMING::IS_MODEL_IN_CDIMAGE(vehicle_hash) || !STREAMING::IS_MODEL_VALID(vehicle_hash))
			return;

		auto position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

		*reinterpret_cast<unsigned short*>(g_hooking.m_ModelSpawnBypass) = 0x9090;
		Vehicle vehicle = VEHICLE::CREATE_VEHICLE(rage::joaat(name), position.x, position.y, position.z, 0.f, true, false, false);
		*reinterpret_cast<unsigned short*>(g_hooking.m_ModelSpawnBypass) = 0x0574;

		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(rage::joaat(name));

		if (*g_hooking.m_IsSessionStarted)
		{
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(vehicle, true);
			int netID = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, false);
		}
	}
}