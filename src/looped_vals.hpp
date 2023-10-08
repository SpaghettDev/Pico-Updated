#pragma once
#include "stdafx.hpp"
#include "looped.hpp"

namespace functions::looped_vals
{
	void features_loop()
	{
		player::update_local_player();
		player::update_globals();

		if (player::local_player != nullptr)
		{
			looped::self_proofs();
			looped::self_always_clean_ped();
			looped::self_wanted_level();
			looped::self_mobile_radio();
			looped::self_freecam();
			looped::self_noclip();
			looped::self_no_collision();
			
			// looped::hud_show_fps();

			looped::esp_tracer();
			looped::esp();

			looped::tp_auto_teleport_waypoint();

			looped::weapons_infinite_ammo();
			looped::weapons_infinit_clip();
			looped::weapons_damage_multiplier();
			looped::weapons_rapid_fire();
			looped::weapons_no_reload();
			// stuff
			looped::weapons_custom_weapon();
			looped::weapons_delete_gun();
			looped::weapons_information_gun();

			looped::online_no_idle_kick();

			// misc
			looped::coords_syncer();

			if (player::local_player->m_vehicle != nullptr)
			{
				looped::veh_proofs();
				looped::veh_always_repair();
				looped::veh_horn_boost();
			}
		}
	}
}
