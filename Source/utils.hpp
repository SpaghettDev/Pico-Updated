#pragma once
#include "stdafx.hpp"

namespace utils
{
	bool load_texture_dict(std::string dict_name)
	{
		while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict_name.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict_name.c_str(), true);
			WAIT(0);
		}

		return GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict_name.c_str());
	}
}