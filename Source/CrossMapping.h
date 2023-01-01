#pragma once

typedef std::unordered_map<uint64_t, uint64_t> nMap;
static std::vector<uint64_t> nativeFailedVec;

class CrossMapping
{
public:
	static void init_native_map();
	static uint64_t MapNative(uint64_t inNative);
	static void dumpNativeMappingCache();
	static bool searchMap(nMap map, uint64_t inNative, uint64_t* outNative);
};
