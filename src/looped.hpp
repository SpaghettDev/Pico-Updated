#pragma once
#include "stdafx.hpp"

namespace
{
#define ARE_PROOFS_DISABLED(plist) std::all_of(std::begin(plist), std::end(plist), [](proof_pair proof) { return !proof.toggle; })

	std::map<int, eEntityProofs> id_to_proof{
		{ 0, eEntityProofs::PROOF_GOD },
		{ 1, eEntityProofs::PROOF_BULLET },
		{ 2, eEntityProofs::PROOF_FIRE },
		{ 3, eEntityProofs::PROOF_COLLISION },
		{ 4, eEntityProofs::PROOF_MELEE },
		{ 5, eEntityProofs::PROOF_EXPLOSION },
		{ 6, eEntityProofs::PROOF_STEAM },
		{ 7, eEntityProofs::PROOF_DROWN },
		{ 8, eEntityProofs::PROOF_WATER }
	};
}

namespace functions::looped
{
	void features()
	{
		player::update_local_player();
		player::update_globals();

		if (player::local_player != nullptr)
		{
			// Self loop
			for (auto& proof : self::proofs)
			{
				if (proof.toggle)
					player::change_proof_bit(id_to_proof.find(proof.id)->second);
			}
			if (ARE_PROOFS_DISABLED(self::proofs))
				player::change_proof_bit(0);

			if (self::always_clean_ped)
				player::clean_ped(player::ped);

			if (self::wanted_level != 0 || self::force_wanted_level)
				player::set_wanted_level(self::wanted_level);


			// Vehicle loop
			if (player::local_player->m_vehicle != nullptr)
			{
				for (auto& proof : vehicle::proofs)
				{
					if (proof.toggle)
						functions::vehicle::change_proof_bit(id_to_proof.find(proof.id)->second);
				}
				if (ARE_PROOFS_DISABLED(vehicle::proofs))
					player::change_proof_bit(0);
				functions::vehicle::collision_proof(vehicle::collision_proof);

				if (vehicle::always_repair)
					functions::vehicle::repair(player::veh);
				if (vehicle::horn_boost)
					functions::vehicle::horn_boost(player::veh);
			}
		}
	}
}
