#include "../../headers/stdafx.h"

namespace MiscNS
{
	bool RequestModel(Hash model)
	{
		if (STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				WAIT(0);

			return true;
		}

		return false;
	}

	Hash $(const char* str) {
		return MISC::GET_HASH_KEY(str);
	}
}