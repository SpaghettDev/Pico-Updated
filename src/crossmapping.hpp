#pragma once

using crossmap_type = std::unordered_map<std::uint64_t, std::uint64_t>;
using crossmap_cache = std::vector<std::pair<std::uint64_t, std::uint64_t>>;
static std::vector<std::uint64_t> native_failed_vec;

class CrossMapping
{
public:
	static const crossmap_type crossmap;
	static std::uint64_t map_native(std::uint64_t in_native);
	static void dump_native_mapping_cache();
	static bool search_map(crossmap_type map, std::uint64_t in_native, std::uint64_t* out_native);
	static bool search_map(crossmap_cache map, std::uint64_t in_native, std::uint64_t* out_native);
};
