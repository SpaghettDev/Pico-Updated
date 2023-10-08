#pragma once

namespace vec3jsonimpl
{
	struct JsonVector3
	{
		float x;
		float y;
		float z;

		JsonVector3(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

		JsonVector3(Vector3 vec)
			: x(vec.x), y(vec.y), z(vec.y)
		{}
	};
}

namespace structs
{
	struct button
	{
		bool hovered;
		bool clicked;

		button(bool hovered, bool clicked)
			: hovered(hovered), clicked(clicked)
		{}

		operator bool() const
		{
			return clicked;
		}
	};

	struct proof_pair
	{
		int id; // the ID of the proof (see looped.hpp)
		bool toggle; // wether it's on or off

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(proof_pair, id, toggle);
	};

	struct time
	{
		int hour, minutes, seconds;

		time(int hour, int min, int sec)
			: hour(hour), minutes(min), seconds(sec)
		{}

		time() = default;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(time, hour, minutes, seconds);
	};

	struct custom_ammo
	{
		eAmmoSpecialType type = eAmmoSpecialType::None;
		eExplosionTag explosion_tag = eExplosionTag::DONTCARE;

		custom_ammo(eAmmoSpecialType type, eExplosionTag explosion_tag)
			: type(type), explosion_tag(explosion_tag)
		{}

		custom_ammo() = default;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(custom_ammo, type, explosion_tag);
	};

	struct ipl
	{
		Vector3 ipl_coords; // used to get the interior ID
		Vector3 coords; // player can spawn here, fallbacks to ipl_coords if not given
		std::function<void()> on_load; // loads necessary IPLs and sometimes performs extra stuff (like loading a door in the fib_lobby IPL)
		std::function<void()> on_unload; // does the opposite of on_load()

		ipl(Vector3 ipl_coords, std::function<void()> on_load, std::function<void()> on_unload, Vector3 coords = Vector3())
			: ipl_coords(ipl_coords), on_load(on_load), on_unload(on_unload), coords(coords == Vector3() ? ipl_coords : coords)
		{}

		ipl() = default;
	};

	struct spawned_obj
	{
		std::string_view name; // the name of the spawned object
		int internal_id; // the ID used to distinguish it from other same-named objects
		Object id; // its ID in the game
		Vector3 pos; // its spawn position (not its current location)

		// information about the spawned object
		bool collision = false,
			collision_physics = false,
			alpha_skin = false,
			locally_invisible_network = false,
			mission_entity = false,
			freeze = false;
		bool visible = true,
			visible_network = true,
			locally_visible_network = true;
		int alpha = 255;

		spawned_obj(std::string_view name, int internal_id, Object id, Vector3 pos)
			: name(name), internal_id(internal_id), id(id), pos(pos)
		{}

		bool operator==(const spawned_obj& other) const
		{
			return
				this->name == other.name &&
				this->id == other.id &&
				this->internal_id == other.internal_id &&
				(
					this->pos.x == other.pos.x &&
					this->pos.y == other.pos.y &&
					this->pos.z == other.pos.z
				);
		}

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawned_obj, name);
	};
	
	struct spawned_ped
	{
		std::string_view name; // the name of the spawned ped
		int internal_id; // the ID used to distinguish it from other same-named peds
		Ped id; // its ID in the game
		Vector3 pos; // its spawn position (not its current location)

		// information about the spawned ped
		bool alpha_skin = false,
			locally_invisible_network = false,
			mission_entity = false,
			freeze = false;
		bool collision = true,
			collision_physics = true,
			visible = true,
			visible_network = true,
			locally_visible_network = true;
		int alpha = 255,
			// we don't and can't know a ped's health now, so we assign it a value later
			health = 0,
			armor = 0;

		spawned_ped(std::string_view name, int internal_id, Ped id, Vector3 pos)
			: name(name), internal_id(internal_id), id(id), pos(pos)
		{}

		bool operator==(const spawned_ped& other) const
		{
			return
				this->id == other.id &&
				this->internal_id == other.internal_id;
		}

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawned_ped, name);
	};

	struct raycast
	{
		BOOL hit = 0; // has the raycast hit an entity
		Vector3 end_coords; // the raycast hit coords
		Vector3 surface_normal; // surface level vector
		Entity entity = 0; // the entity hit

		raycast(BOOL hit, Vector3 end_coords, Vector3 surface_normal, Entity entity)
			: hit(hit), end_coords(end_coords), surface_normal(surface_normal), entity(entity)
		{}

		raycast() = default;
	};

	struct entity_info
	{
		Entity id = 0;
		std::string info1; // contains basic info (entity type, registered in menu)
		std::string info2; // contains info related to hp and armor
		std::string info3; // contains position & speed

		bool is_ped = false,
			 is_veh = false,
			 is_obj = false,
			 is_generic = false;

		entity_info(Entity id, std::string info1, std::string info2, std::string info3)
			: id(id), info1(info1), info2(info2), info3(info3)
		{}

		entity_info() = default;

		void reset()
		{
			this->id = 0;
			this->info1.clear();
			this->info2.clear();
			this->info3.clear();
		}
	};

	struct location
	{
		vec3jsonimpl::JsonVector3 coords; // the coords
		vec3jsonimpl::JsonVector3 rot; // rotation info (yaw, pitch, roll)

		location(Vector3 coords, Vector3 rot)
			: coords(coords), rot(rot)
		{};

		friend void to_json(nlohmann::json& j, const location& t)
		{
			j["location"] = nlohmann::json::object({
				{ "coords", nlohmann::json::array({ t.coords.x, t.coords.y, t.coords.z }) },
				{ "rot", nlohmann::json::array({ t.rot.x, t.rot.y, t.rot.z }) },
			});
		}
		friend void from_json(const nlohmann::json& j, location& t)
		{
			j.at("location").get_to(t.coords.x);
			j.at("location").get_to(t.coords.y);
			j.at("location").get_to(t.coords.z);
			j.at("location").get_to(t.rot.x);
			j.at("location").get_to(t.rot.y);
			j.at("location").get_to(t.rot.z);
		};
	};
}
