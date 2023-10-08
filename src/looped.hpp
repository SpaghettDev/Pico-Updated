#pragma once
#include "stdafx.hpp"
#include <base/phBoundComposite.hpp>

//! TODO: move each type of looped function into its own file

namespace
{
	std::map<int, eEntityProofs> id_to_proof{
		{ 0, eEntityProofs::PROOF_GOD },
		{ 1, eEntityProofs::PROOF_BULLET },
		{ 2, eEntityProofs::PROOF_FIRE },
		{ 3, eEntityProofs::PROOF_COLLISION },
		{ 4, eEntityProofs::PROOF_MELEE },
		{ 5, eEntityProofs::PROOF_EXPLOSION },
		{ 6, eEntityProofs::PROOF_STEAM },
		{ 7, eEntityProofs::PROOF_DROWN },
		{ 8, eEntityProofs::PROOF_WATER }
	};

	std::ptrdiff_t get_obj_index(Object obj)
	{
		using namespace pico;

		auto ind = std::find_if(
			g_json.m_settings.world.object.previous_spawned.begin(),
			g_json.m_settings.world.object.previous_spawned.end(),
			[obj](const structs::spawned_obj& v_obj)
			{
				return v_obj.id == obj;
			}
		);

		if (ind == g_json.m_settings.world.object.previous_spawned.end())
			return -1;
		
		return ind - g_json.m_settings.world.object.previous_spawned.begin();
	}
	
	std::ptrdiff_t get_ped_index(Ped ped)
	{
		using namespace pico;

		auto ind = std::find_if(
			g_json.m_settings.world.ped.previous_spawned.begin(),
			g_json.m_settings.world.ped.previous_spawned.end(),
			[ped](const structs::spawned_ped& v_ped)
			{
				return v_ped.id == ped;
			}
		);

		if (ind == g_json.m_settings.world.ped.previous_spawned.end())
			return -1;
		
		return ind - g_json.m_settings.world.ped.previous_spawned.begin();
	}
}

namespace functions
{
	class looped
	{
	public:
		static void self_proofs()
		{
			std::uint32_t mask = 0;

			for (int i = 0; i < pico::g_json.m_settings.self.proofs.size(); i++)
			{
				if (pico::g_json.m_settings.self.proofs[i])
					mask |= static_cast<int>(id_to_proof.at(i));
			}

			player::change_proof_bit(mask);
		}
		

		static void self_always_clean_ped()
		{
			if (pico::g_json.m_settings.self.always_clean_ped)
				player::clean_ped(player::ped, false);
		}

		static void self_wanted_level()
		{
			if (pico::g_json.m_settings.self.wanted_level != 0 || pico::g_json.m_settings.self.wanted_forced)
				player::set_wanted_level(pico::g_json.m_settings.self.wanted_level);
		}

		static void self_mobile_radio()
		{
			static bool has_been_set = false;

			if (pico::g_json.m_settings.self.mobile_radio && !has_been_set)
			{
				AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
				AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
				has_been_set = true;
			}
			if (!(pico::g_json.m_settings.self.mobile_radio) && has_been_set)
			{
				AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
				AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
				has_been_set = false;
			}
		}

		static void self_freecam()
		{
			static bool has_been_set = false;

			float speed = 0.5f;
			float mult = 0.f;

			Cam camera = -1;
			Vector3 position;
			Vector3 rotation;

			const ControllerInputs controls[] =
			{
				ControllerInputs::INPUT_LOOK_LR,
				ControllerInputs::INPUT_LOOK_UD,
				ControllerInputs::INPUT_LOOK_UP_ONLY,
				ControllerInputs::INPUT_LOOK_DOWN_ONLY,
				ControllerInputs::INPUT_LOOK_LEFT_ONLY,
				ControllerInputs::INPUT_LOOK_RIGHT_ONLY,
				ControllerInputs::INPUT_LOOK_LEFT,
				ControllerInputs::INPUT_LOOK_RIGHT,
				ControllerInputs::INPUT_LOOK_UP,
				ControllerInputs::INPUT_LOOK_DOWN
			};

			if (pico::g_json.m_settings.self.freecam && !has_been_set)
			{
				camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);

				position = CAM::GET_GAMEPLAY_CAM_COORD();
				rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);

				ENTITY::FREEZE_ENTITY_POSITION(player::veh, true);

				CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
				CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
				CAM::SET_CAM_ACTIVE(camera, true);
				CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true, 0);

				has_been_set = true;
			}

			if (pico::g_json.m_settings.self.freecam && has_been_set)
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

				for (const auto& control : controls)
					PAD::ENABLE_CONTROL_ACTION(ControlTypes::PLAYER_CONTROL, control, true);

				Vector3 vecChange = { 0.f, 0.f, 0.f };

				// Left Shift
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_SPRINT))
					vecChange.z += speed / 2;
				// Left Control
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_DUCK))
					vecChange.z -= speed / 2;
				// Forward
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_MOVE_UP_ONLY))
					vecChange.y += speed;
				// Backward
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_MOVE_DOWN_ONLY))
					vecChange.y -= speed;
				// Left
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_MOVE_LEFT_ONLY))
					vecChange.x -= speed;
				// Right
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
					vecChange.x += speed;

				if (vecChange == 0.f)
					mult = 0.f;
				else if (mult < 10)
					mult += 0.15f;

				Vector3 rot = CAM::GET_CAM_ROT(camera, 2);
				float yaw = utils::math::deg_to_rad(rot.z); // horizontal

				position.x += (vecChange.x * cos(yaw) - vecChange.y * sin(yaw)) * mult;
				position.y += (vecChange.x * sin(yaw) + vecChange.y * cos(yaw)) * mult;
				position.z += vecChange.z * mult;

				CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
				STREAMING::SET_FOCUS_POS_AND_VEL(position.x, position.y, position.z, 0.f, 0.f, 0.f);

				rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
				CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
			}

			if (!(pico::g_json.m_settings.self.freecam) && has_been_set)
			{
				CAM::SET_CAM_ACTIVE(camera, false);
				CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
				CAM::DESTROY_CAM(camera, false);
				STREAMING::CLEAR_FOCUS();

				ENTITY::FREEZE_ENTITY_POSITION(camera, false);

				has_been_set = false;
			}
		}

		static void self_noclip()
		{
			static bool has_been_set = false;

			const ControllerInputs controls[] =
			{
				ControllerInputs::INPUT_SPRINT,
				ControllerInputs::INPUT_MOVE_UP_ONLY,
				ControllerInputs::INPUT_MOVE_DOWN_ONLY,
				ControllerInputs::INPUT_MOVE_LEFT_ONLY,
				ControllerInputs::INPUT_MOVE_RIGHT_ONLY,
				ControllerInputs::INPUT_DUCK
			};
			float speed = 20.f;

			Entity entity = 0;
			float speed_multiplier = 0.f;

			if (pico::g_json.m_settings.self.noclip)
			{
				for (const auto& control : controls)
					PAD::DISABLE_CONTROL_ACTION(ControlTypes::PLAYER_CONTROL, static_cast<int>(control), true);

				const auto location = player::pos;
				const Entity ent = (
					player::veh != 0 &&
					player::local_player->m_ped_task_flag & static_cast<int>(ePedTask::TASK_DRIVING)
				) ? player::veh : player::ped;

				// cleanup when changing entities
				if (entity != ent)
				{
					ENTITY::FREEZE_ENTITY_POSITION(entity, false);
					ENTITY::SET_ENTITY_COLLISION(entity, true, true);

					entity = ent;
				}

				Vector3 vel = { 0.f, 0.f, 0.f };

				// Left Shift
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, static_cast<int>(ControllerInputs::INPUT_SPRINT)))
					vel.z += speed / 2;
				// Left Control
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, static_cast<int>(ControllerInputs::INPUT_DUCK)))
					vel.z -= speed / 2;
				// Forward
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, static_cast<int>(ControllerInputs::INPUT_MOVE_UP_ONLY)))
					vel.y += speed;
				// Backward
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, static_cast<int>(ControllerInputs::INPUT_MOVE_DOWN_ONLY)))
					vel.y -= speed;
				// Left
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, static_cast<int>(ControllerInputs::INPUT_MOVE_LEFT_ONLY)))
					vel.x -= speed;
				// Right
				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, static_cast<int>(ControllerInputs::INPUT_MOVE_RIGHT_ONLY)))
					vel.x += speed;

				auto rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
				ENTITY::SET_ENTITY_ROTATION(ent, 0.f, rot.y, rot.z, 2, 0);
				ENTITY::SET_ENTITY_COLLISION(ent, false, false);
				if (vel == 0.f)
				{
					// freeze entity to prevent drifting when standing still
					ENTITY::FREEZE_ENTITY_POSITION(ent, true);
					speed_multiplier = 0.f;
				}
				else
				{
					if (speed_multiplier < 20.f)
						speed_multiplier += 0.15f;

					ENTITY::FREEZE_ENTITY_POSITION(ent, false);

					const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
					vel.x = offset.x - location.x;
					vel.y = offset.y - location.y;

					ENTITY::SET_ENTITY_VELOCITY(ent, vel.x * speed_multiplier, vel.y * speed_multiplier, vel.z * speed_multiplier);
				}

				has_been_set = true;
			}

			if (!(pico::g_json.m_settings.self.noclip) && has_been_set)
			{
				if (utils::take_control_of(entity))
				{
					ENTITY::FREEZE_ENTITY_POSITION(entity, false);
					ENTITY::SET_ENTITY_COLLISION(entity, true, false);
				}

				has_been_set = false;
			}
		}
		
		static void self_no_collision()
		{
			if (pico::g_json.m_settings.self.no_collision)
				reinterpret_cast<rage::phBoundComposite*>(
					player::local_player->m_navigation->m_damp->m_bound
				)->m_bounds[0]->m_bounding_box_max_xyz_margin_w.w = -1;
			else
				reinterpret_cast<rage::phBoundComposite*>(
					player::local_player->m_navigation->m_damp->m_bound
				)->m_bounds[0]->m_bounding_box_max_xyz_margin_w.w = 0.25;
		}


		/*static void hud_show_fps()
		{
			if (pico::g_json.m_settings.hud.show_fps)
			{
				float LastFrameTime = MISC::GET_FRAME_TIME();
				int getFPS = (1.0f / LastFrameTime);
				char FPStext[60];
				snprintf(FPStext, sizeof(FPStext), "FPS: ~b~ %d", getFPS);
				setupdraw(true);
				HUD::SET_TEXT_FONT(6);
				HUD::SET_TEXT_SCALE(0.5f, 0.5f);
				HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
				HUD::SET_TEXT_CENTRE(0);
				drawstring(FPStext, 0.020f, 0.010f);
			}
		}*/


		static void esp_tracer()
		{
			if (pico::g_json.m_settings.tracer_esp.tracer)
			{
				/*if (pico::g_json.m_settings.tracer_esp.trace_to_peds)
					world::trace_to_peds();
				if (pico::g_json.m_settings.tracer_esp.trace_to_vehs)
					world::trace_to_vehs();*/
			}
		}
		
		static void esp()
		{
			if (pico::g_json.m_settings.tracer_esp.esp)
			{
				/*if (pico::g_json.m_settings.tracer_esp.esp_peds)
					world::esp_peds();
				if (pico::g_json.m_settings.tracer_esp.esp_vehs)
					world::esp_vehs();*/
			}
		}


		static void tp_auto_teleport_waypoint()
		{
			if (pico::g_json.m_settings.tp.auto_tp)
			{
				if (!HUD::IS_PAUSE_MENU_ACTIVE())
				{
					if (HUD::IS_WAYPOINT_ACTIVE())
					{
						player::teleport_to_waypoint();
						HUD::SET_WAYPOINT_OFF();
					}
				}
			}
		}


		static void weapons_infinite_ammo()
		{
			static bool has_been_set = false;

			if (pico::g_json.m_settings.weapons.inf_ammo && !has_been_set)
			{
				WEAPON::SET_PED_INFINITE_AMMO(player::ped, true, 0);
				has_been_set = true;
			}
			if (!(pico::g_json.m_settings.weapons.inf_ammo) && has_been_set)
			{
				WEAPON::SET_PED_INFINITE_AMMO(player::ped, false, 0);
				has_been_set = false;
			}
		}

		static void weapons_infinit_clip()
		{
			static bool has_been_set = false;
			
			if (pico::g_json.m_settings.weapons.inf_clip && !has_been_set)
			{
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(player::ped, true);
				has_been_set = true;
			}
			if (!(pico::g_json.m_settings.weapons.inf_clip) && has_been_set)
			{
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(player::ped, false);
				has_been_set = false;
			}
		}

		static void weapons_damage_multiplier()
		{
			if (float mul = pico::g_json.m_settings.weapons.damage_multiplier; mul != 1.f)
			{
				Hash weapon;
				WEAPON::GET_CURRENT_PED_WEAPON(player::ped, &weapon, 0);
				WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, mul);
			}
		}

		static void weapons_rapid_fire()
		{
			if (pico::g_json.m_settings.weapons.rapid_fire && !(
				HUD::IS_PAUSE_MENU_ACTIVE() &&
				PED::IS_PED_DEAD_OR_DYING(player::ped, true) &&
				PED::IS_PED_IN_ANY_VEHICLE(player::ped, true)
				))
			{
				PAD::DISABLE_CONTROL_ACTION(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_ATTACK, true);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_ATTACK))
				{
					Vector3 direction = utils::math::rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
					Vector3 start = CAM::GET_GAMEPLAY_CAM_COORD() + direction;
					Vector3 end = start + direction * 200.0;

					Hash weapon_hash;
					WEAPON::GET_CURRENT_PED_WEAPON(player::ped, &weapon_hash, false);

					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(
						start.x, start.y, start.z,
						end.x, end.y, end.z,
						static_cast<int>(WEAPON::GET_WEAPON_DAMAGE(weapon_hash, 0)),
						true, weapon_hash, player::ped,
						true, false, -1.0
					);
				}
			}
		}

		static void weapons_no_reload()
		{
			if (pico::g_json.m_settings.weapons.no_reload)
			{
				if (
					Hash weapon = WEAPON::GET_SELECTED_PED_WEAPON(player::ped);
					weapon != weapons_data::weapons["WEAPON_UNARMED"] &&
					weapon != weapons_data::weapons["WEAPON_RAYMINIGUN"] &&
					weapon != weapons_data::weapons["WEAPON_MINIGUN"]
				)
					WEAPON::SET_AMMO_IN_CLIP(player::ped, weapon, WEAPON::GET_MAX_AMMO_IN_CLIP(player::ped, weapon, true));
			}
		}

		static void weapons_delete_gun()
		{
			using namespace pico;

			if (g_json.m_settings.weapons.deleter_gun)
			{
				PAD::DISABLE_CONTROL_ACTION(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_ATTACK, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_ATTACK))
					if (auto ray = world::get_raycast_result(); ray.entity)
						if (
							(
								ENTITY::IS_ENTITY_A_PED(ray.entity) ||
								ENTITY::IS_ENTITY_A_VEHICLE(ray.entity) ||
								ENTITY::IS_ENTITY_AN_OBJECT(ray.entity)
							) && !PED::IS_PED_A_PLAYER(ray.entity)
							)
						{
							if (utils::take_control_of(ray.entity))
							{
								// handle if the object raycasted is registered in our menu (obj/ped_previous_spawned)
								if (auto ind = get_obj_index(ray.entity); ind != -1)
								{
									if (g_json.m_settings.world.object.previous_spawned_idx > 0)
										g_json.m_settings.world.object.previous_spawned_idx--;

									g_json.m_settings.world.object.previous_spawned.erase(g_json.m_settings.world.object.previous_spawned.begin() + ind);
								}
								if (auto ind = get_ped_index(ray.entity); ind != -1)
								{
									if (g_json.m_settings.world.ped.previous_spawned_idx > 0)
										g_json.m_settings.world.ped.previous_spawned_idx--;
									
									g_json.m_settings.world.ped.previous_spawned.erase(g_json.m_settings.world.ped.previous_spawned.begin() + ind);
								}

								world::delete_entity(ray.entity);
							}
						}
			}
		}

		static void weapons_custom_weapon()
		{
			static CWeaponInfo* p_modified_weapon = nullptr;
			static eDamageType modified_weapon_damage_type = eDamageType::None;
			static CWeaponInfo::sExplosion modified_weapon_explosion{};
			static eAmmoSpecialType modified_weapon_ammo_type = eAmmoSpecialType::None;

			if (
				player::local_player->m_weapon_manager == nullptr ||
				player::local_player->m_weapon_manager->m_weapon_info == nullptr ||
				player::local_player->m_weapon_manager->m_weapon_info->m_ammo_info == nullptr
				)
				return;

			const auto custom_ammo = pico::g_json.m_settings.weapons.custom_ammo;

			if (custom_ammo.type != eAmmoSpecialType::None || custom_ammo.explosion_tag != eExplosionTag::DONTCARE)
			{
				CWeaponInfo* weapon_info = player::local_player->m_weapon_manager->m_weapon_info;

				// check if the player changed their weapon
				if (p_modified_weapon != weapon_info)
				{
					// apply the original bullet and impact type to the old weapon
					if (p_modified_weapon != nullptr)
					{
						p_modified_weapon->m_damage_type = modified_weapon_damage_type;
						p_modified_weapon->m_explosion = modified_weapon_explosion;
						p_modified_weapon->m_ammo_info->m_ammo_special_type = modified_weapon_ammo_type;
					}

					// backup the bullet and impact type of the new weapon
					p_modified_weapon = weapon_info;
					modified_weapon_damage_type = weapon_info->m_damage_type;
					modified_weapon_explosion = weapon_info->m_explosion;
					modified_weapon_ammo_type = weapon_info->m_ammo_info->m_ammo_special_type;
				}

				// apply ammo type changes to the current weapon
				eDamageType damage_type = eDamageType::None;
				eExplosionTag explosion_tag = custom_ammo.explosion_tag;
				eAmmoSpecialType ammo_type = eAmmoSpecialType::None;

				if (explosion_tag == eExplosionTag::DONTCARE)
				{
					damage_type = modified_weapon_damage_type;
					ammo_type = custom_ammo.type;
				}
				else
				{
					damage_type = eDamageType::Explosive;
					ammo_type = modified_weapon_ammo_type;
				}

				weapon_info->m_damage_type = damage_type;

				CWeaponInfo::sExplosion explosion{};
				explosion.m_default = explosion_tag;
				explosion.m_hit_bike = explosion_tag;
				explosion.m_hit_boat = explosion_tag;
				explosion.m_hit_car = explosion_tag;
				explosion.m_hit_plane = explosion_tag;
				explosion.m_hit_truck = explosion_tag;
				weapon_info->m_explosion = explosion;

				weapon_info->m_ammo_info->m_ammo_special_type = ammo_type;
			}
			else if (p_modified_weapon != nullptr)
			{
				// apply the original bullet and impact type to the weapon
				// when the ammo type feature is off
				p_modified_weapon->m_damage_type = modified_weapon_damage_type;
				p_modified_weapon->m_explosion = modified_weapon_explosion;
				p_modified_weapon->m_ammo_info->m_ammo_special_type = modified_weapon_ammo_type;
				p_modified_weapon = nullptr;
			}
		}

		static void weapons_information_gun()
		{
			if (pico::g_json.m_settings.weapons.info_gun)
			{
				static structs::entity_info last_ent{};

				PAD::DISABLE_CONTROL_ACTION(ControlTypes::PLAYER_CONTROL, ControllerInputs::INPUT_ATTACK, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(ControlTypes::PLAYER_CONTROL	, ControllerInputs::INPUT_ATTACK))
				{
					if (auto ray = world::get_raycast_result(); ray.entity != last_ent.id)
					{
						last_ent.reset();

						switch (ENTITY::GET_ENTITY_TYPE(ray.entity))
						{
						case eEntityType::INVALID:
							last_ent.info1 += "[INVALID] ";
							break;
						case eEntityType::TYPE_PED:
							last_ent.info1 += "[PED] ";
							last_ent.info2 += std::format("~g~{}/{}HP~s~ | ~d~{} ARMOR~s~ ",
								world::get_entity_health(ray.entity),
								world::get_entity_max_health(ray.entity),
								world::get_ped_armor(ray.entity)
							);
							last_ent.is_ped = true;
							break;
						case eEntityType::TYPE_VEHICLE:
							last_ent.info1 += "[VEHICLE] ";
							last_ent.info2 += std::format("~g~{}/{}HP~s~ ",
								world::get_entity_health(ray.entity),
								world::get_entity_max_health(ray.entity)
							);
							last_ent.is_veh = true;
							break;
						case eEntityType::TYPE_OBJECT:
							last_ent.info1 += "[OBJECT] ";
							last_ent.info2 += std::format("~g~{}/{}HP~s~ ",
								world::get_entity_health(ray.entity),
								world::get_entity_max_health(ray.entity)
							);
							last_ent.is_obj = true;
							break;
						default:
							last_ent.info1 += "[GENERIC] ";
							last_ent.is_generic = true;
							break;
						}

						// handle if the object raycasted is registered in our menu ([obj/ped]_previous_spawned)
						auto obj_ind = get_obj_index(ray.entity);
						auto ped_ind = get_ped_index(ray.entity);
						if (obj_ind == -1 && ped_ind == -1)
							last_ent.info1 += std::format("[NOT REGISTERED (hash: {})]", ENTITY::GET_ENTITY_MODEL(ray.entity));
						else
						{
							if (obj_ind != -1)
							{
								last_ent.info1 += std::format("[REGISTERED ({} #{})]",
									pico::g_json.m_settings.world.object.previous_spawned[obj_ind].name,
									pico::g_json.m_settings.world.object.previous_spawned[obj_ind].internal_id
								);
							}
							if (ped_ind != -1)
							{
								last_ent.info1 += std::format("[REGISTERED ({} #{})]",
									pico::g_json.m_settings.world.ped.previous_spawned[ped_ind].name,
									pico::g_json.m_settings.world.ped.previous_spawned[ped_ind].internal_id
								);
							}
						}

						Vector3 coords = world::get_entity_coords(ray.entity);
						float speed = ENTITY::GET_ENTITY_SPEED(ray.entity);
						last_ent.info3 = std::format("X: {} Y: {} Z: {} ", coords.x, coords.y, coords.z);
						last_ent.info3 += std::format("{} km/h ({} mph)", speed * 3.6f, speed * 2.236936f);
					}
					else
					{
						if (last_ent.is_ped)
							last_ent.info2 = std::format("~g~{}/{}HP~s~ | ~d~{} ARMOR~s~ ",
								world::get_entity_health(last_ent.id),
								world::get_entity_max_health(last_ent.id),
								world::get_ped_armor(last_ent.id)
							);
						else if (last_ent.is_veh)
							last_ent.info2 = std::format("~g~{}/{}HP~s~ ",
								world::get_entity_health(last_ent.id),
								world::get_entity_max_health(last_ent.id)
							);
						else if (last_ent.is_obj)
							last_ent.info2 = std::format("~g~{}/{}HP~s~ ",
								world::get_entity_health(last_ent.id),
								world::get_entity_max_health(last_ent.id)
							);

						Vector3 coords = world::get_entity_coords(last_ent.id);
						float speed = ENTITY::GET_ENTITY_SPEED(last_ent.id);
						last_ent.info3 = std::format("X: {} Y: {} Z: {} ", coords.x, coords.y, coords.z);
						last_ent.info3 += std::format("{} km/h ({} mph)", speed * 3.6f, speed * 2.236936f);
					}

					utils::notify::display_help_text(
						std::format("{}~n~{}~n~{}", last_ent.info1, last_ent.info2, last_ent.info3)
					);
				}
			}
		}


		static void veh_proofs()
		{
			std::uint32_t mask = 0;

			for (int i = 0; i < pico::g_json.m_settings.vehicle.proofs.size(); i++)
			{
				if (i == 3)
					continue;

				if (pico::g_json.m_settings.vehicle.proofs[i])
					mask |= static_cast<int>(id_to_proof.at(i));
			}

			functions::vehicle::change_proof_bit(mask);
			functions::vehicle::collision_proof(pico::g_json.m_settings.vehicle.proofs.at(3));
		}

		static void veh_always_repair()
		{
			if (pico::g_json.m_settings.vehicle.always_repair)
				functions::vehicle::repair(player::veh, false);
		}

		static void veh_horn_boost()
		{
			if (pico::g_json.m_settings.vehicle.horn_boost)
				functions::vehicle::horn_boost(player::veh);
		}

		//! TODO: update vals
		static void online_no_idle_kick()
		{
			if (pico::g_json.m_settings.online.no_idle_kick)
			{
				*script_global(1653919).add(1156).as<int*>() = 0;
				*script_global(1653919).add(1172).as<int*>() = 0;

				*script_global(262145).add(90).as<int*>() = INT_MAX;
			}
		}


		static void coords_syncer()
		{
			using namespace pico;

			if (g_json.m_settings.vehicle.always_sync_coords)
				g_json.m_settings.vehicle.pos = player::pos;
			
			if (g_json.m_settings.tp.always_sync_coords)
				g_json.m_settings.tp.tp_pos = player::pos;
			
			if (g_json.m_settings.world.object.always_sync_coords)
				g_json.m_settings.world.object.pos = g_json.m_settings.world.object.spawn_where_looking
					? world::get_raycast_result().end_coords
					: player::pos;
			if (g_json.m_settings.world.ped.always_sync_coords)
				g_json.m_settings.world.ped.pos = g_json.m_settings.world.ped.spawn_where_looking
					? world::get_raycast_result().end_coords
					: player::pos;

			// technically not a coord but needs to be synced so meh
			if (pico::g_json.m_settings.world.time_and_weather.always_sync_time)
				world::get_local_time(g_json.m_settings.world.time_and_weather.custom_time);
		}
	};
}
