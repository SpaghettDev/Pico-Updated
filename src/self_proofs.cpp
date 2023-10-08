#include "stdafx.hpp"
#include "looped.hpp"
#include "functions.hpp"

namespace
{
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

namespace functions
{
	void looped::self_proofs()
	{
		for (auto& proof : looped_vals::self::proofs)
		{
			if (proof.toggle)
				player::change_proof_bit(id_to_proof.find(proof.id)->second);
		}
		if (
			std::all_of(
				std::begin(looped_vals::self::proofs),
				std::end(looped_vals::self::proofs),
				[](looped_vals::proof_pair proof) { return !proof.toggle; }
			)
			)
			player::change_proof_bit(0);
	}
}
