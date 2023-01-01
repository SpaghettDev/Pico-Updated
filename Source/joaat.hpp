#pragma once

#include "stdafx.h"
#include <span>

namespace rage
{
    using joaat_t = std::uint32_t;

    inline constexpr char joaat_to_lower(char c)
    {
        return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
    }

    inline joaat_t joaat(std::string_view str)
    {
        joaat_t hash = 0;
        for (auto c : str)
        {
            hash += joaat_to_lower(c);
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash;
    }

	consteval joaat_t consteval_joaat(const std::span<const char>& data)
	{
		joaat_t hash = 0;

		for (std::size_t i = 0; i < data.size() - 1; ++i)
		{
			hash += joaat_to_lower(data[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}
	static_assert(consteval_joaat("test") == 0x3f75ccc1);
}

#define RAGE_JOAAT_IMPL(str) (::rage::consteval_joaat(str))
#define RAGE_JOAAT(str) (std::integral_constant<rage::joaat_t, RAGE_JOAAT_IMPL(str)>::value)
