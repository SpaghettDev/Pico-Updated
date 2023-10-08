#pragma once
#include "stdafx.hpp"
#include "looped.hpp"

namespace functions
{
	void looped::self_proofs(decltype(looped::proof_pair_type) proofs, Player player)
	{
		for (auto& proof : proofs)
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