#pragma once
#include "rage/vector.hpp"

#pragma pack(push, 1)
struct SizeVector 
{
	float w, h;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RGBAF 
{
	int r, g, b, a, f;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RGBA 
{
	int r, g, b, a;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RGB 
{
	int r, g, b;
};
#pragma pack(pop)

namespace rage
{
#pragma pack(push, 1)
	class scrVector
	{
	public:
		scrVector() = default;

		scrVector(rage::fvector3 vec) :
			x(vec.x), y(vec.y), z(vec.z)
		{}

		scrVector(float x, float y, float z) :
			x(x), y(y), z(z)
		{}

		scrVector operator+(const scrVector& other)
		{
			scrVector vec;
			vec.x = this->x + other.x;
			vec.y = this->y + other.y;
			vec.z = this->z + other.z;
			return vec;
		}

		scrVector operator-(const scrVector& other)
		{
			scrVector vec;
			vec.x = this->x - other.x;
			vec.y = this->y - other.y;
			vec.z = this->z - other.z;
			return vec;
		}

		scrVector operator*(const scrVector& other)
		{
			scrVector vec;
			vec.x = this->x * other.x;
			vec.y = this->y * other.y;
			vec.z = this->z * other.z;
			return vec;
		}

		scrVector operator*(const float& other)
		{
			scrVector vec;
			vec.x = this->x * other;
			vec.y = this->y * other;
			vec.z = this->z * other;
			return vec;
		}
	public:
		float x{};
	private:
		char m_padding1[0x04];
	public:
		float y{};
	private:
		char m_padding2[0x04];
	public:
		float z{};
	private:
		char m_padding3[0x04];
	};
#pragma pack(pop)
}

class Vector2 final
{
public:
	Vector2() = default;

	Vector2(float x, float y)
		: x(x), y(y)
	{}

public:
	float x, y;
};

using Void = void;
using Any = int;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using FireId = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using CarGenerator = std::int32_t;
using Group = std::int32_t;
using Train = std::int32_t;
using Object = Entity;
using Pickup = Object;
using Weapon = std::int32_t;
using Interior = std::int32_t;
using Blip = std::int32_t;
using Texture = std::int32_t;
using TextureDict = std::int32_t;
using CoverPoint = std::int32_t;
using Camera = Entity;
using TaskSequence = std::int32_t;
using ColourIndex = std::int32_t;
using Sphere = std::int32_t;
using ScrHandle = Entity;
using Vector3 = rage::scrVector;
