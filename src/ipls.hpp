#pragma once
#include "stdafx.hpp"

namespace
{
	template <std::size_t S>
	using ipl_array = std::array<std::string_view, S>;

	// https://www.gta5-mods.com/scripts/interior-manager
	ipl_array<1> casino_main_ipls{
		"vw_casino_main"
	};
	ipl_array<1> casino_garage_ipls{
		"vw_casino_garage"
	};
	ipl_array<1> casino_carpark_ipls{
		"vw_casino_carpark"
	};
	ipl_array<1> casino_billboard_ipls{
		"vw_casino_billboard"
	};
	ipl_array<1> casino_penthouse_ipls{
		"vw_casino_penthouse"
	};
	ipl_array<1> casino_door_ipls{
		"vw_dlc_casino_door"
	};

	ipl_array<1> medium_warehouse_ipls{
		"ex_exec_warehouse_placement_interior_0_int_warehouse_m_dlc_milo_"
	};
	ipl_array<1> small_warehouse_ipls{
		"ex_exec_warehouse_placement_interior_1_int_warehouse_s_dlc_milo_"
	};
	ipl_array<1> large_warehouse_ipls{
		"ex_exec_warehouse_placement_interior_2_int_warehouse_l_dlc_milo_"
	};
	
	ipl_array<1> clubhouse1_ipls{
		"bkr_biker_interior_placement_interior_0_biker_dlc_int_01_milo_"
	};
	ipl_array<1> clubhouse2_ipls{
		"bkr_biker_interior_placement_interior_1_biker_dlc_int_02_milo_"
	};

	ipl_array<67> north_yankton_ipls{
		"plg_01", "prologue01", "prologue01k", "prologue01k_lod",
		"prologue01z", "prologue01z_lod", "prologue01_lod", "prologue01c",
		"prologue01c_lod", "prologue01d", "prologue01d_lod", "prologue01e",
		"prologue01e_lod", "prologue01f", "prologue01f_lod", "prologue01g",
		"prologue01h", "prologue01h_lod", "prologue01i", "prologue01i_lod",
		"prologue01j", "prologue01j_lod",

		"plg_02", "prologue02", "prologue02_lod",

		"plg_03", "prologue03", "prologue03_lod", "prologue03b",
		"prologue03b_lod", "prologue03_grv_cov", "prologue03_grv_cov_lod", "prologue03_grv_dug",
		"prologue03_grv_dug_lod", "prologue03_grv_fun", "prologue_grv_torch",

		"plg_04", "prologue04", "prologue04_lod", "prologue04b",
		"prologue04b_lod", "prologue04_cover", "des_protree_end", "des_protree_start",
		"des_protree_start_lod",

		"plg_05", "prologue05", "prologue05_lod", "prologue05b",
		"prologue05b_lod",

		"plg_06", "prologue06", "prologue06_lod", "prologue06b",
		"prologue06b_lod", "prologue06_int", "prologue06_int_lod", "prologue06_pannel",
		"prologue06_pannel_lod", "prologue_m2_door", "prologue_m2_door_lod",

		"plg_occl_00", "prologue_occl",

		"plg_rd", "prologuerd", "prologuerdb", "prologuerd_lod",
	};

	ipl_array<5> cluckin_bell_ipls{
		"CS1_02_cf_onmission1",
		"CS1_02_cf_onmission2",
		"CS1_02_cf_onmission3",
		"CS1_02_cf_onmission4",
		"CS1_02_cf_offmission"
	};

	ipl_array<4> fame_or_shame_stadium_ipls{
		"sp1_10_fake_interior",
		"sp1_10_fake_interior_lod",
		"sp1_10_real_interior",
		"sp1_10_real_interior_lod",
	};

	ipl_array<2> fib_lobby_ipls{
		"FIBlobby",
		"FIBlobbyfake"
	};

	ipl_array<1> epsilon_ipls{
		"v_epsilonism"
	};

	ipl_array<1> hospital_default_ipls{
		"RC12B_Default"
	};
	ipl_array<1> hospital_destroyed_ipls{
		"RC12B_Destroyed"
	};
	ipl_array<1> hospital_interior_ipls{
		"RC12B_HospitalInterior"
	};
	ipl_array<1> hospital_fixed_ipls{
		"RC12B_Fixed"
	};

	ipl_array<1> lifeinvader_ipls{
		"facelobby"
	};
	ipl_array<1> lifeinvaderfake_ipls{
		"facelobbyfake"
	};
}

namespace ipls_data
{
#define DEFAULT_LOAD_IPL(coords, ipl_name) \
	STREAMING::REQUEST_IPL(ipl_name); \
	const Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z); \
	INTERIOR::DISABLE_INTERIOR(interior, true); \
	INTERIOR::PIN_INTERIOR_IN_MEMORY(interior); \
	INTERIOR::DISABLE_INTERIOR(interior, false); \
	INTERIOR::REFRESH_INTERIOR(interior) \

#define DEFAULT_UNLOAD_IPL(coords, ipl_name) \
	STREAMING::REMOVE_IPL(ipl_name); \
	const Interior interior = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z); \
	INTERIOR::DISABLE_INTERIOR(interior, true); \
	INTERIOR::REFRESH_INTERIOR(interior) \
	

	// https://github.com/DurtyFree/gta-v-data-dumps/blob/master/ipls.json
	nlohmann::ordered_map<std::string_view, structs::ipl> useful_ipls{
		{ "casino_main",
			{
				{ 1120.4658f, 237.23846f, -48.06224f },
				[] {
					Vector3 coords{ 1120.4658f, 237.23846f, -48.06224f };

					DEFAULT_LOAD_IPL(coords, casino_main_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1120.4658f, 237.23846f, -48.06224f };

					DEFAULT_UNLOAD_IPL(coords, casino_main_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},
		{ "casino_garage",
			{
				{ 1281.8566f, 241.06073f, -46.385574f },
				[] {
					Vector3 coords{ 1281.8566f, 241.06073f, -46.385574f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(casino_garage_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1281.8566f, 241.06073f, -46.385574f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(casino_garage_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},
		{ "casino_carpark",
			{
				{ 1373.0952f, 218.92924f, -46.518463f },
				[] {
					Vector3 coords{ 1373.0952f, 218.92924f, -46.518463f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(casino_carpark_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1373.0952f, 218.92924f, -46.518463f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(casino_carpark_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},
		{ "casino_billboard",
			{
				{ 613.1593f, -162.99255f, 81.68674f },
				[] {
					Vector3 coords{ 613.1593f, -162.99255f, 81.68674f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(casino_billboard_ipls[0].data());
				},
				[] {
					Vector3 coords{ 613.1593f, -162.99255f, 81.68674f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(casino_billboard_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},
		{ "casino_penthouse",
			{
				{ 959.0497f, 40.086292f, 115.643135f },
				[] {
					Vector3 coords{ 959.0497f, 40.086292f, 115.643135f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(casino_penthouse_ipls[0].data());
				},
				[] {
					Vector3 coords{ 959.0497f, 40.086292f, 115.643135f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(casino_penthouse_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},
		{ "casino_door",
			{
				{ 925.57684f, 46.154076f, 81.54187f },
				[] {
					Vector3 coords{ 925.57684f, 46.154076f, 81.54187f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(casino_door_ipls[0].data());
				},
				[] {
					Vector3 coords{ 925.57684f, 46.154076f, 81.54187f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(casino_door_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},
		{ "casino_all",
			{
				{ 1120.4658f, 237.23846f, -48.06224f },
				[] {
					Vector3 main_coords{ 1120.4658f, 237.23846f, -48.06224f };
					Vector3 garage_coords{ 1281.8566f, 241.06073f, -46.385574f };
					Vector3 carpark_coords{ 1373.0952f, 218.92924f, -46.518463f };
					Vector3 billboard_coords{ 613.1593f, -162.99255f, 81.68674f };
					Vector3 penthouse_coords{ 959.0497f, 40.086292f, 115.643135f };
					Vector3 door_coords{ 925.57684f, 46.154076f, 81.54187f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(main_coords.x, main_coords.y, main_coords.z), false);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(garage_coords.x, garage_coords.y, garage_coords.z), false);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(carpark_coords.x, carpark_coords.y, carpark_coords.z), false);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(billboard_coords.x, billboard_coords.y, billboard_coords.z), false);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(penthouse_coords.x, penthouse_coords.y, penthouse_coords.z), false);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(door_coords.x, door_coords.y, door_coords.z), false);
					STREAMING::REQUEST_IPL(casino_main_ipls[0].data());
					STREAMING::REQUEST_IPL(casino_garage_ipls[0].data());
					STREAMING::REQUEST_IPL(casino_carpark_ipls[0].data());
					STREAMING::REQUEST_IPL(casino_billboard_ipls[0].data());
					STREAMING::REQUEST_IPL(casino_penthouse_ipls[0].data());
					STREAMING::REQUEST_IPL(casino_door_ipls[0].data());
				},
				[] {
					Vector3 main_coords{ 1120.4658f, 237.23846f, -48.06224f };
					Vector3 garage_coords{ 1281.8566f, 241.06073f, -46.385574f };
					Vector3 carpark_coords{ 1373.0952f, 218.92924f, -46.518463f };
					Vector3 billboard_coords{ 613.1593f, -162.99255f, 81.68674f };
					Vector3 penthouse_coords{ 959.0497f, 40.086292f, 115.643135f };
					Vector3 door_coords{ 925.57684f, 46.154076f, 81.54187f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(main_coords.x, main_coords.y, main_coords.z), true);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(garage_coords.x, garage_coords.y, garage_coords.z), true);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(carpark_coords.x, carpark_coords.y, carpark_coords.z), true);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(billboard_coords.x, billboard_coords.y, billboard_coords.z), true);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(penthouse_coords.x, penthouse_coords.y, penthouse_coords.z), true);
					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(door_coords.x, door_coords.y, door_coords.z), true);
					STREAMING::REMOVE_IPL(casino_main_ipls[0].data());
					STREAMING::REMOVE_IPL(casino_garage_ipls[0].data());
					STREAMING::REMOVE_IPL(casino_carpark_ipls[0].data());
					STREAMING::REMOVE_IPL(casino_billboard_ipls[0].data());
					STREAMING::REMOVE_IPL(casino_penthouse_ipls[0].data());
					STREAMING::REMOVE_IPL(casino_door_ipls[0].data());
				},
				{ 918.f, -49.f, 80.f }
			}
		},

		{ "medium_warehouse",
			{
				{ 1061.9365f, -3102.4705f, -36.571033f },
				[] {
					Vector3 coords{ 1061.9365f, -3102.4705f, -36.571033f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(medium_warehouse_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1061.9365f, -3102.4705f, -36.571033f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(medium_warehouse_ipls[0].data());
				},
				{ 1056.f, -3105.f, 5.f }
			}
		},
		{ "small_warehouse",
			{
				{ 1096.3739f, -3099.5176f, -38.032825f },
				[] {
					Vector3 coords{ 1096.3739f, -3099.5176f, -38.032825f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(small_warehouse_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1096.3739f, -3099.5176f, -38.032825f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(small_warehouse_ipls[0].data());
				},
				{ 1093.f, -3100.f, 5.f }
			}
		},
		{ "large_warehouse",
			{
				{ 1010.13696f, -3101.4297f, -35.09293f },
				[] {
					Vector3 coords{ 1010.13696f, -3101.4297f, -35.09293f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(large_warehouse_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1010.13696f, -3101.4297f, -35.09293f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(large_warehouse_ipls[0].data());
				},
				{ 1056.f, -3105.f, 5.f }
			}
		},

		{ "clubhouse1",
			{
				{ 1111.1968f, -3154.0728f, -34.81927f },
				[] {
					Vector3 coords{ 1111.1968f, -3154.0728f, -34.81927f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(clubhouse1_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1111.1968f, -3154.0728f, -34.81927f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(clubhouse1_ipls[0].data());
				},
				{ 1056.f, -3105.f, 5.f }
			}
		},
		{ "clubhouse2",
			{
				{ 1005.19385f, -3161.5413f, -35.10899f },
				[] {
					Vector3 coords{ 1005.19385f, -3161.5413f, -35.10899f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), false);
					STREAMING::REQUEST_IPL(clubhouse2_ipls[0].data());
				},
				[] {
					Vector3 coords{ 1005.19385f, -3161.5413f, -35.10899f };

					INTERIOR::DISABLE_INTERIOR(INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z), true);
					STREAMING::REMOVE_IPL(clubhouse2_ipls[0].data());
				},
				{ 1056.f, -3105.f, 5.f }
			}
		},

		{ "north_yankton",
			{
				{ 3360.19f, -4849.67f, 111.8f },
				[] { for (const auto& ipl_name : north_yankton_ipls) STREAMING::REQUEST_IPL(ipl_name.data()); },
				[] { for (const auto& ipl_name : north_yankton_ipls) STREAMING::REMOVE_IPL(ipl_name.data()); },
			}
		},

		{ "cluckin_bell",
			{
				{ -75.49429f, 6270.23f, 30.49062f },
				[] { for (const auto& ipl_name : cluckin_bell_ipls) STREAMING::REQUEST_IPL(ipl_name.data()); },
				[] { for (const auto& ipl_name : cluckin_bell_ipls) STREAMING::REMOVE_IPL(ipl_name.data()); },
			}
		},

		{ "fame_or_shame_stadium",
			{
				{ -230.4916f, -2040.509f, 27.f },
				[] { for (const auto& ipl_name : fame_or_shame_stadium_ipls) STREAMING::REQUEST_IPL(ipl_name.data()); },
				[] { for (const auto& ipl_name : fame_or_shame_stadium_ipls) STREAMING::REMOVE_IPL(ipl_name.data()); },
			}
		},

		{ "fib_lobby",
			{
				{ 100.3793f, -743.6982f, 44.51962f },
				[] {
					for (const auto& ipl_name : fib_lobby_ipls)
						STREAMING::REQUEST_IPL(ipl_name.data());

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_fibl_door01"), 105.7607f, -746.646f, 46.18266f, false, 0.f, 0.f, 0.f);
					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_fibl_door02"), 106.3793f, -742.6982f, 46.51962f, false, 0.f, 0.f, 0.f);
				},
				[] {
					for (const auto& ipl_name : fib_lobby_ipls)
						STREAMING::REMOVE_IPL(ipl_name.data());

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_fibl_door01"), 105.7607f, -746.646f, 46.18266f, true, 0.f, 0.f, 0.f);
					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_fibl_door02"), 106.3793f, -742.6982f, 46.51962f, true, 0.f, 0.f, 0.f);
				},
			}
		},

		{ "epsilon",
			{
				{ 241.3621f, 361.0471f, 105.8883f },
				[] {
					Vector3 coords{ 241.3621f, 361.0471f, 105.8883f };
					int id = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);

					INTERIOR::CAP_INTERIOR(id, false);
					INTERIOR::DISABLE_INTERIOR(id, false);

					for (const auto& ipl_name : epsilon_ipls)
						STREAMING::REQUEST_IPL(ipl_name.data());

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_epsstoredoor"), coords.x, coords.y, coords.z, false, 0.f, 0.f, 0.f);
				},
				[] {
					Vector3 coords{ 241.3621f, 361.0471f, 105.8883f };
					int id = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);

					INTERIOR::CAP_INTERIOR(id, true);
					INTERIOR::DISABLE_INTERIOR(id, true);

					for (const auto& ipl_name : epsilon_ipls)
						STREAMING::REMOVE_IPL(ipl_name.data());

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_epsstoredoor"), coords.x, coords.y, coords.z, true, 0.f, 0.f, 0.f);
				},
			}
		},
		{ "epsilon2",
			{
				{ 241.3621f, 361.0471f, 105.8883f },
				[] {
					Vector3 coords{ 241.3621f, 361.0471f, 105.8883f };
					int id = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);

					INTERIOR::CAP_INTERIOR(id, false);
					INTERIOR::DISABLE_INTERIOR(id, false);
					INTERIOR::PIN_INTERIOR_IN_MEMORY(id);

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_epsstoredoor"), 241.3621f, 361.0471f, 105.8883f, false, 0.f, 0.f, 0.f);
				},
				[] {
					Vector3 coords{ 241.3621f, 361.0471f, 105.8883f };
					int id = INTERIOR::GET_INTERIOR_AT_COORDS(coords.x, coords.y, coords.z);

					INTERIOR::CAP_INTERIOR(id, true);
					INTERIOR::DISABLE_INTERIOR(id, true);
					INTERIOR::UNPIN_INTERIOR(id);

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_fibl_door01"), 241.3621f, 361.0471f, 105.8883f, true, 0.f, 0.f, 0.f);
				},
			}
		},

		{ "hospital_normal",
			{
				{ 290.7717f, -580.9828f, 42.26085f },
				[] {
					STREAMING::REMOVE_IPL(hospital_destroyed_ipls[0].data());
					STREAMING::REMOVE_IPL(hospital_interior_ipls[0].data());
					STREAMING::REMOVE_IPL(hospital_fixed_ipls[0].data());

					STREAMING::REQUEST_IPL(hospital_default_ipls[0].data());
				},
				[] {
					STREAMING::REQUEST_IPL(hospital_destroyed_ipls[0].data());
					STREAMING::REQUEST_IPL(hospital_interior_ipls[0].data());
					STREAMING::REQUEST_IPL(hospital_fixed_ipls[0].data());

					STREAMING::REMOVE_IPL(hospital_default_ipls[0].data());
				},
			}
		},
		{ "hospital_boarded_up",
			{
				{ 290.7717f, -580.9828f, 42.26085f },
				[] {
					STREAMING::REMOVE_IPL(hospital_destroyed_ipls[0].data());
					STREAMING::REMOVE_IPL(hospital_interior_ipls[0].data());
					STREAMING::REMOVE_IPL(hospital_default_ipls[0].data());

					STREAMING::REQUEST_IPL(hospital_fixed_ipls[0].data());
				},
				[] {
					STREAMING::REQUEST_IPL(hospital_destroyed_ipls[0].data());
					STREAMING::REQUEST_IPL(hospital_interior_ipls[0].data());
					STREAMING::REQUEST_IPL(hospital_default_ipls[0].data());

					STREAMING::REMOVE_IPL(hospital_fixed_ipls[0].data());
				},
			}
		},
		{ "hospital_destroyed",
			{
				{ 290.7717f, -580.9828f, 42.26085f },
				[] {
					STREAMING::REMOVE_IPL(hospital_fixed_ipls[0].data());
					STREAMING::REMOVE_IPL(hospital_default_ipls[0].data());

					STREAMING::REQUEST_IPL(hospital_destroyed_ipls[0].data());
					STREAMING::REQUEST_IPL(hospital_interior_ipls[0].data());
				},
				[] {
					STREAMING::REQUEST_IPL(hospital_fixed_ipls[0].data());
					STREAMING::REQUEST_IPL(hospital_default_ipls[0].data());

					STREAMING::REMOVE_IPL(hospital_destroyed_ipls[0].data());
					STREAMING::REMOVE_IPL(hospital_interior_ipls[0].data());
				},
			}
		},
		{ "lifeinvader",
			{
				{ -1042.518f, -240.6915f, 38.11796f },
				[] {
					STREAMING::REQUEST_IPL(lifeinvader_ipls[0].data());
					STREAMING::REMOVE_IPL(lifeinvaderfake_ipls[0].data());

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_gtdoor02"), -1042.518f, -240.6915f, 38.11796f, false, 0.f, 0.f, -1.f);
				},
				[] {
					STREAMING::REMOVE_IPL(lifeinvader_ipls[0].data());
					STREAMING::REQUEST_IPL(lifeinvaderfake_ipls[0].data());

					OBJECT::SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(rage::joaat("v_ilev_gtdoor02"), -1042.518f, -240.6915f, 38.11796f, true, 0.f, 0.f, -1.f);
				}
			}
		}
	};

	std::vector<std::string_view> useful_ipls_names;

	void init_names()
	{
		static bool init = false;

		if (!init)
		{
			useful_ipls_names.reserve(useful_ipls.size());

			for (const auto& [name, _] : useful_ipls)
				useful_ipls_names.push_back(name);

			init = true;
		}
	}
}
