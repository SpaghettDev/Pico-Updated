#pragma once
#include "stdafx.hpp"
#include "joaat.hpp"

namespace misc
{
	bool request_model(std::string model_name, int timeout = 1000)
	{
		if (STREAMING::HAS_MODEL_LOADED(rage::joaat(model_name)))
			return true;

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(rage::joaat(model_name)) && i < timeout; i++)
		{
			STREAMING::REQUEST_MODEL(rage::joaat(model_name));
			WAIT(0);
		}

		return STREAMING::HAS_MODEL_LOADED(rage::joaat(model_name));
	}

	bool request_model(Hash model, int timeout = 1000)
	{
		if (STREAMING::HAS_MODEL_LOADED(model))
			return true;

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model) && i < timeout; i++)
		{
			STREAMING::REQUEST_MODEL(model);
			WAIT(0);
		}

		return STREAMING::HAS_MODEL_LOADED(model);
	}
}
