#include "../../headers/stdafx.h"

namespace VehicleNS
{
	Vehicle spawn(Hash hash, Vector3 location, float heading, bool is_networked = true)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			WAIT(0);
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
			return 0;

		*(unsigned short*)g_Hooking.m_ModelSpawnBypass = 0x9090;
		auto veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, false, false);
		*(unsigned short*)g_Hooking.m_ModelSpawnBypass = 0x0574;

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
			auto NetworkID = NETWORK::VEH_TO_NET(veh);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NetworkID, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, FALSE);
		}

		return veh;
	}
}