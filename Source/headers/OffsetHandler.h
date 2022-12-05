#pragma once 
#include "../headers/stdafx.h"

class OffsetHandler
{
public:
	template <typename T>
	T GetValue(std::vector<DWORD> Offsets) {

		uintptr_t Adress = GetMultilayerPointer((uintptr_t)g_Hooking.m_WorldPointer, Offsets);
		if (Adress == NULL) {
			return NULL;
		}

		return *((T*)Adress);
	}

	template <typename T>
	void SetValue(std::vector<DWORD> Offsets, T Value) {
		uintptr_t Adress = GetMultilayerPointer((uintptr_t)g_Hooking.m_WorldPointer, Offsets);
		if (Adress == NULL) {
			return;
		}

		*reinterpret_cast<T*>(Adress) = Value;
	}
private:
	uintptr_t GetMultilayerPointer(uintptr_t BaseAdress, std::vector<DWORD> Offsets) {
		uintptr_t Pointer = *(uintptr_t*)(BaseAdress);
		if (!Pointer) {

			return NULL;
		}
		auto level = Offsets.size();

		for (auto i = 0; i < level; i++)
		{
			if (i == level - 1)
			{
				Pointer += Offsets[i];
				if (!Pointer) return NULL;
				return Pointer;
			}
			else
			{
				Pointer = *(uint64_t*)(Pointer + Offsets[i]);
				if (!Pointer) return NULL;
			}
		}

		return Pointer;
	}
};

// new offsets taken from https://github.com/CrazyZhang666/GTA5OnlineTools
//offset from WORLD
#define OFFSET_PLAYER					0x08			//playerbase
#define OFFSET_PLAYER_PED				0x8
#define OFFSET_NET_PLAYER				0x1C8

//entity offsets
#define OFFSET_ENTITY_POSBASE			0x30			//base of a structure that contains entity coords
#define	OFFSET_ENTITY_POSBASE_COS		0x20
#define	OFFSET_ENTITY_POSBASE_SIN		0x30
#define OFFSET_ENTITY_POSBASE_POS		0x50			//vector3
#define OFFSET_ENTITY_GOD				0x189			//godmode; on = 1, off = 0; byte
#define OFFSET_ENTITY_HEALTH			0x280			//entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX		0x284			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER			0x2A8			//base to a list of the last 3 entities that attacked the current entity
#define OFFSET_ENTITY_MODEL_INFO		0x20			//CBaseModelInfo
#define OFFSET_PED_ENTITYTYPE       0x2B                // int 156:Player 152:Other
#define OFFSET_ENTITY_POSX 0x90                   // float, vector3
#define OFFSET_ENTITY_POSY 0x94
#define OFFSET_ENTITY_POSZ 0x98
#define OFFSET_ENTITY_PROOF 0x188
#define OFFSET_ENTITY_HOSTILITY 0x18C

//player (entity) offsets
#define OFFSET_PLAYER_VEHICLE					0xD10			//ptr to last used vehicle
#define OFFSET_NET_PLAYER_INFO					0x10A8
#define OFFSET_PLAYER_INVENTORY 0x10B0
#define OFFSET_PLAYER_INFO						0x10C8			//playerInfo struct
#define OFFSET_PLAYER_INFO_NAME					0xA4
#define OFFSET_PLAYER_INFO_SWIM_SPD				0x170			//swim speed; def 1; float
#define	OFFSET_PLAYER_INFO_RUN_SPD				0xCF0			//run speed; def 1; float
#define OFFSET_PLAYER_INFO_FRAMEFLAGS			0x219			//frame flags; DWORD
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE	0x73C			//fWantedCanChange
#define OFFSET_PLAYER_INFO_NPC_IGNORE			0x870			//npc ignore; DWORD; everyone = 0x450000;
#define OFFSET_PLAYER_INFO_WANTED				0x888			//wanted level; DWORD
#define OFFSET_PLAYER_INFO_STAMINA				0xCF4			//fStamina, fStaminaMax
#define OFFSET_PLAYER_RAGDOLL					0x1098			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT					0x143C			//byte; CPed.seatBelt: 0xC8 (55) = off; 0xC9 (56) = on
#define OFFSET_PLAYER_INVEHICLE					0xE32      // int 0:false 1:true
#define OFFSET_PLAYER_ARMOR						0x150C			//armour
#define OFFSET_PLAYER_WATER_PROOF				0x188			//water proof; DWORD; +0x1000000 = on
#define OFFSET_PLAYER_VEHICLE_DAMAGE_MP			0xD1C			//super punck/kick;float;
#define OFFSET_PLAYER_WIDTH                     0x0064          //change player width
#define OFFSET_PLAYER_HEIGHT                    0x88            //change player height
#define OFFSET_PLAYER_INVINCIBLE        0x2C                 // byte 0x01:on 0x24:off

//vehicle offsets
#define OFFSET_VEHICLE_HEALTH						0x280			//vehicle health; 0.f-1000.f
#define	OFFSET_VEHICLE_HEALTH2						0x284			//vehicle health2; 0.f-1000.f
#define OFFSET_VEHICLE_HEALTH_BODY       0x820
#define OFFSET_VEHICLE_HEALTH_PETROL_TANK 0x824
#define OFFSET_VEHICLE_HEALTH_ENGINE 0x8E8
#define OFFSET_VEHICLE_HANDLING_MASS				0xC				//fMass
#define OFFSET_VEHICLE_HANDLING_BUOYANCY			0x40			//fBuoyancy
#define OFFSET_VEHICLE_HANDLING_ACCELERATION		0x4C
#define OFFSET_VEHICLE_HANDLING_UPSHIFT				0x58
#define OFFSET_VEHICLE_HANDLING_DOWNSHIFT			0x5C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE			0x6C
#define OFFSET_VEHICLE_HANDLING_HANDBRAKEFORCE		0x7C			//fHandbrakeForce
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN	0x90			//fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE	0xBC			//fSuspensionForce
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_HEIGH	0xD0			//fSuspensionHeight
#define OFFSET_VEHICLE_HANDLING_COLISION_DAMAGE_MP	0xF0			//fColisionDamageMult
#define OFFSET_VEHICLE_HANDLING_WEAPON_DAMAGE_MP	0xF4			//fWeaponDamageMult
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER	0xF8			//fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_ENGINE_DAMAGE_MP	0xFC			//fEngineDamageMult
#define OFFSET_VEHICLE_BULLETPROOF_TIRES			0x943			//btBulletproofTires;  (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_GRAVITY						0xC5C			//fGravity
#define OFFSET_VEHICLE_BOOST						0x320			//fBoost
#define OFFSET_VEHICLE_RECHARGE_SPEED				0x324			//fRocketRechargeSpeed
#define OFFSET_VEHICLE_MISSLES						0x1280			//btVehicleMissles
#define OFFSET_VEHICLE_BOMBS						0x1294			//btAircraftBombs
#define OFFSET_VEHICLE_COUNTERMEASURES				0x1298			//btAircraftCountermeasures
#define OFFSET_VEHICLE_MK2_MISSLES					0x1284			//btOppressorMK2Misseles
#define OFFSET_VEHICLE_TAMPA_MISSLES				0x127C			//btTampaMissles
#define	OFFSET_VEHICLE_CUSTOM						0x48
#define	OFFSET_VEHICLE_CUSTOM_EMS					0x3D6			//btEngineManagementSystem; 0x3 = max
#define	OFFSET_VEHICLE_CUSTOM_BRAKES				0x3D7			//btBrakes; 0x6 = max
#define	OFFSET_VEHICLE_CUSTOM_TRANSMISSION			0x3D8			//btTransmission; 0x8 = max
#define	OFFSET_VEHICLE_CUSTOM_SUSPENSION			0x3DA			//btSuspension; 0x1B = max
#define	OFFSET_VEHICLE_CUSTOM_ARMOR					0x3DB			//btArmor; 0x1B = max
#define	OFFSET_VEHICLE_CUSTOM_TURBO_TUNING			0x3DD			//btTurboTuning; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_R			0x3A2			//btNeonLightRed
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_G			0x3A1			//btNeonLightGreen
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHT_B			0x3A0			//btNeonLightBlue
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_L			0x402			//btNeonLightLeft; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_R			0x403			//btNeonLightRight; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_F			0x404			//btNeonLightFront; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_NEON_LIGHTS_B			0x405			//btNeonLightBack; 0x0 = off; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE			0x3DF			//btTyreSmoke; 0x1 = on
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_R			0x3FC			//btTyreSmokeRed
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_G			0x3FD			//btTyreSmokeGreen
#define	OFFSET_VEHICLE_CUSTOM_TYRE_SMOKE_B			0x3FE			//btTyreSmokeBlue
#define	OFFSET_VEHICLE_CUSTOM_LIMO_WINDOWS			0x3FF			//btLimoWindows; 0x1 = on
#define OFFSET_VEHICLE_MODEL_INFO_JUMP_ROCK			0x58B			//btJumpOrRock; 0x0 = off; 0x20 = JumpingCar; 0x40 = RocketBoot;  0x42 = Oppressor;

//weapon offsets
#define OFFSET_WEAPON_MANAGER			0x10B8			//from playerbase
#define OFFSET_WEAPON_CURRENT			0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO			0x60			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX		0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1	0x08			//ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2	0x00			//ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO	0x18			//offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE		0x0C			//offset to projectile type?
#define OFFSET_WEAPON_SPREAD			0x74			//float set to 0
#define OFFSET_WEAPON_BULLET_DMG		0xB0			//float times 10 (so when 0, it will stay 0)
#define OFFSET_WEAPON_RELOAD_MULTIPLIER	0x134			//float times 10
#define OFFSET_WEAPON_RECOIL			0x2F4			//float set to 0
#define OFFSET_WEAPON_MODEL_HASH		0x14
#define OFFSET_WEAPON_NAME_HASH			0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE	0x130
#define OFFSET_WEAPON_RANGE				0x28C
#define OFFSET_WEAPON_SPINUP			0x144
#define OFFSET_WEAPON_SPIN				0x148
#define OFFSET_WEAPON_BULLET_BATCH		0x124			//dwBulletInBatch
#define OFFSET_WEAPON_MUZZLE_VELOCITY	0x11C			//fMuzzleVelocity
#define OFFSET_WEAPON_IMPACT_TYPE		0x20			//dwImpactType; 1: Fists,3; Bullets,5: Explosives
#define OFFSET_WEAPON_IMPACT_EXPLOSION	0x24			//dwImpactExplosion
#define OFFSET_WEAPON_PENETRATION		0x110			//fPenetration
#define OFFSET_WEAPON_FORCE_ON_PED		0xDC			//fForceOnPed
#define OFFSET_WEAPON_FORCE_ON_VEHICLE	0xE0			//fForceOnVehicle(Bullet Mass)
#define OFFSET_WEAPON_FORCE_ON_HELI		0xE4			//fForceOnHeli
#define OFFSET_ATTACKER_DISTANCE		0x18			//changed to 0x18, from 0x10