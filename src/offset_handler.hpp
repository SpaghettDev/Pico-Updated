#pragma once 
#include "stdafx.hpp"

class OffsetHandler
{
public:
	template <typename T>
	T GetValue(std::vector<DWORD> Offsets)
	{

		uintptr_t Adress = GetMultilayerPointer(reinterpret_cast<uintptr_t>(g_hooking.m_WorldPointer), Offsets);
		if (Adress == NULL)
			return NULL;

		return *reinterpret_cast<T*>(Adress);
	}

	template <typename T>
	void SetValue(std::vector<DWORD> Offsets, T value)
	{
		uintptr_t adress = GetMultilayerPointer(reinterpret_cast<uintptr_t>(g_hooking.m_WorldPointer), Offsets);
		if (adress == NULL)
			return;

		*reinterpret_cast<T*>(adress) = value;
	}
private:
	uintptr_t GetMultilayerPointer(uintptr_t BaseAdress, std::vector<DWORD> offsets)
	{
		uintptr_t pointer = *reinterpret_cast<uintptr_t*>(BaseAdress);
		if (!pointer)
			return NULL;

		auto num_offsets = offsets.size();

		for (auto i = 0; i < num_offsets; i++)
		{
			pointer = *reinterpret_cast<uint64_t*>(pointer + offsets[i]);
			if (!pointer)
				return NULL;
		}
		
		pointer += offsets[num_offsets - 1];
		if (!pointer)
			return NULL;

		return pointer;
	}
};
