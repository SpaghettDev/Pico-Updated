#include "../../headers/stdafx.h"

namespace MiscNS
{
	bool RequestModel(Hash model)
	{
		if (STREAMING::IS_MODEL_VALID(model))
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);
				WAIT(0);
			}

			return STREAMING::HAS_MODEL_LOADED(hash);
		}
	}

	Hash $(const char* str) {
		return MISC::GET_HASH_KEY(str);
	}
}