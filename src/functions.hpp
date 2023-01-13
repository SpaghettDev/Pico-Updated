#pragma once
#include "stdafx.hpp"
#include "rage/joaat.hpp"
#include "ped/CPed.hpp"

namespace functions
{
	namespace player
	{
		CPed* local_player;
		Player id;
		Ped ped;
		Vector3 pos;
		Vehicle veh;
		int char_slot;

		CPed* get_local_ped();
		CVehicle* get_local_vehicle();
		CPlayerInfo* get_local_playerinfo();

		void update_local_player();
		void update_globals();
		void change_proof_bit(std::uint32_t proof);
		void max_health();
		void max_armor();
		void suicide();
		void clean_ped();
		void set_wanted_level(int level);
		void clear_wanted_level();
	}

	namespace utils
	{
		bool request_model(Hash model, int timeout);
		bool request_model(std::string model_name, int timeout);
		std::string keyboard_input(const char* example_text, int max_length);
		bool take_control_of(Entity ent, int timeout);

		namespace notify
		{
			void above_map(std::string_view text);
			void display_help_text(std::string_view text);
		}
	}

	namespace vehicle
	{
		bool spawn_vehicle(Hash name, Vector3 position, bool networked);
		void max_vehicle(Vehicle veh);
		bool repair(Vehicle veh);
		void change_proof_bit(std::uint32_t proof);
		void collision_proof(bool toggle);
		static float horn_boost_speed_increment = 0.3f;
		void horn_boost(Vehicle veh);
	}

	namespace looped
	{
		struct proof_pair
		{
			int id;
			bool toggle;
		};

		namespace self
		{
			bool always_clean_ped = false;
			int wanted_level = 0;
			bool force_wanted_level = false;
			proof_pair proofs[9] = {
				{ 0, false },
				{ 1, false },
				{ 2, false },
				{ 3, false },
				{ 4, false },
				{ 5, false },
				{ 6, false },
				{ 7, false },
				{ 8, false }
			};
		}

		namespace vehicle
		{
			bool always_repair = false;
			bool collision_proof = false;
			bool horn_boost = false;
			proof_pair proofs[8] = {
				{ 0, false },
				{ 1, false },
				{ 2, false }, // 3 (PROOF_COLLISION) is handled by vehice::collision_proof
				{ 4, false },
				{ 5, false },
				{ 6, false },
				{ 7, false },
				{ 8, false }
			};
		}

		void features();
	}
}

#include "player.hpp"
#include "looped.hpp"
#include "utils.hpp"
#include "vehicle.hpp"
