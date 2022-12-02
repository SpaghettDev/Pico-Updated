#pragma once
#include "../headers/stdafx.h"

using Void = void;
using Any = int;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using FireId = std::int32_t;
using Interior = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using Object = Entity;
using Pickup = Object;
using Blip = std::int32_t;
using Camera = Entity;
using ScrHandle = Entity;
// using Vector3 = rage::scrVector;
using CarGenerator = std::int32_t;
using Group = std::int32_t;
using Train = std::int32_t;
using Weapon = std::int32_t;
using Interior = std::int32_t;
using Texture = std::int32_t;
using TextureDict = std::int32_t;
using CoverPoint = std::int32_t;
using TaskSequence = std::int32_t;
using ColourIndex = std::int32_t;
using Sphere = std::int32_t;

#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
} Vector2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;
} Vector3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	float x;
	float y;
	float z;
} Vector3_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct VECTOR2 
{
	float x, y;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct VECTOR2_2 
{
	float w, h;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct RGBAF 
{
	int r, g, b, a, f;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct RGBA 
{
	int r, g, b, a;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct RGB 
{
	int r, g, b;
};
#pragma pack(pop)