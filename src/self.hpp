#include "stdafx.hpp"

namespace functions
{
	void looped::self_proofs()
	{
		std::uint32_t mask = 0;

		for (auto& proof : looped_vals::self::proofs)
		{
			if (proof.toggle)
				mask |= static_cast<int>(id_to_proof.find(proof.id)->second);
		}

		player::change_proof_bit(mask);
	}
}