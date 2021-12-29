//ZIP: Extending vars.Vehicle*, a Vehicle change system

#include "Hooks_Vehicle.h"
#include "spdlog/spdlog.h"
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_Vehicle {
		bool overrideDefaultFpks = false;
		bool overrideVehicleSystem = false;
		struct PlayerVehicle {
			std::string vehicleWestLv = "";
			std::string vehicleEastLv = "";
			std::string vehicleWestTrc = "";
			std::string vehicleEastTrc = "";
			std::string vehicleWestWavMachinegun = "";
			std::string vehicleWestWavCannon = "";
			std::string vehicleWestWav = "";
			std::string vehicleWestWavRocket = "";
			std::string vehicleWestTnk = "";
			std::string vehicleEastTnk = "";
		};//Vehicle
		PlayerVehicle Vehicle;

		int l_SetOverrideVehicleSystem(lua_State* L) {
			overrideVehicleSystem = lua_toboolean(L, -1);

			spdlog::debug("SetOverrideVehicleSystem override:{}, ", overrideVehicleSystem);

			return 0;
		}//l_SetOverrideVehicleSystem

		/*
			SetVehicle*FpkPath
		*/
		int l_SetVehicleWestLvFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleWestLvFpkPath {}, ", filePath);
			Vehicle.vehicleWestLv = filePath;

			return 0;
		}//l_SetVehicleWestLvFpkPath
		
		int l_SetVehicleEastLvFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleEastLvFpkPath {}, ", filePath);
			Vehicle.vehicleEastLv = filePath;

			return 0;
		}//l_SetVehicleEastLvFpkPath
		
		int l_SetVehicleWestTrcFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleWestTrcFpkPath {}, ", filePath);
			Vehicle.vehicleWestTrc = filePath;

			return 0;
		}//l_SetVehicleWestTrcFpkPath
		
		int l_SetVehicleEastTrcFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleEastTrcFpkPath {}, ", filePath);
			Vehicle.vehicleEastTrc = filePath;

			return 0;
		}//l_SetVehicleEastTrcFpkPath
		
		int l_SetVehicleWestWavMachineGunFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleWestWavMachineGunFpkPath {}, ", filePath);
			Vehicle.vehicleWestWavMachinegun = filePath;

			return 0;
		}//l_SetVehicleWestWavMachineGunFpkPath
		
		int l_SetVehicleWestWavCannonFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleWestWavCannonFpkPath {}, ", filePath);
			Vehicle.vehicleWestWavCannon = filePath;

			return 0;
		}//l_SetVehicleWestWavCannonFpkPath
		
		int l_SetVehicleEastWavFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleEastWavFpkPath {}, ", filePath);
			Vehicle.vehicleWestWav = filePath;

			return 0;
		}//l_SetVehicleEastWavFpkPath
		
		int l_SetVehicleEastWavRocketFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleEastWavRocketFpkPath {}, ", filePath);
			Vehicle.vehicleWestWavRocket = filePath;

			return 0;
		}//l_SetVehicleEastWavRocketFpkPath
		
		int l_SetVehicleWestTnkFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleWestTnkFpkPath {}, ", filePath);
			Vehicle.vehicleWestTnk = filePath;

			return 0;
		}//l_SetVehicleWestTnkFpkPath
		
		int l_SetVehicleEastTnkFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("SetVehicleEastTnkFpkPath {}, ", filePath);
			Vehicle.vehicleEastTnk = filePath;

			return 0;
		}//l_SetVehicleEastTnkFpkPath

		/*
			Vanilla FPK paths
		*/
		std::string VehicleFpksDefault[]{
			"/Assets/tpp/pack/vehicle/veh_rl_west_lv.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_east_lv.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_west_trc.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_east_trc.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_west_wav_machinegun.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_west_wav_cannon.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_east_wav.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_east_wav_rocket.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_west_tnk.fpk",
			"/Assets/tpp/pack/vehicle/veh_rl_east_tnk.fpk",
		};
		
		/*
			Vehicle hooks
		*/
		ulonglong GetVehicleOverride(uint vehicleType) {
			if (vehicleType == 0) {
				if (Vehicle.vehicleWestLv != "") {
					spdlog::debug("vehicleWestLv: {}", Vehicle.vehicleWestLv);
					return PathCode64(Vehicle.vehicleWestLv.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_west_lv.fpk");
				}
			}
			else if (vehicleType == 1) {
				if (Vehicle.vehicleEastLv != "") {
					spdlog::debug("vehicleEastLv: {}", Vehicle.vehicleEastLv);
					return PathCode64(Vehicle.vehicleEastLv.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_east_lv.fpk");
				}
			}
			else if (vehicleType == 2) {
				if (Vehicle.vehicleWestTrc != "") {
					spdlog::debug("vehicleWestTrc: {}", Vehicle.vehicleWestTrc);
					return PathCode64(Vehicle.vehicleWestTrc.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_west_trc.fpk");
				}
			}
			else if (vehicleType == 3) {
				if (Vehicle.vehicleEastTrc != "") {
					spdlog::debug("vehicleEastTrc: {}", Vehicle.vehicleEastTrc);
					return PathCode64(Vehicle.vehicleEastTrc.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_east_trc.fpk");
				}
			}
			else if (vehicleType == 4) {
				if (Vehicle.vehicleWestWavMachinegun != "") {
					spdlog::debug("vehicleWestWavMachinegun: {}", Vehicle.vehicleWestWavMachinegun);
					return PathCode64(Vehicle.vehicleWestWavMachinegun.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_west_wav_machinegun.fpk");
				}
			}
			else if (vehicleType == 5) {
				if (Vehicle.vehicleWestWavCannon != "") {
					spdlog::debug("vehicleWestWavCannon: {}", Vehicle.vehicleWestWavCannon);
					return PathCode64(Vehicle.vehicleWestWavCannon.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_west_wav_cannon.fpk");
				}
			}
			else if (vehicleType == 6) {
				if (Vehicle.vehicleWestWav != "") {
					spdlog::debug("vehicleWestWav: {}", Vehicle.vehicleWestWav);
					return PathCode64(Vehicle.vehicleWestWav.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_east_wav.fpk");
				}
			}
			else if (vehicleType == 7) {
				if (Vehicle.vehicleWestWavRocket != "") {
					spdlog::debug("vehicleWestWavRocket: {}", Vehicle.vehicleWestWavRocket);
					return PathCode64(Vehicle.vehicleWestWavRocket.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_east_wav_rocket.fpk");
				}
			}
			else if (vehicleType == 8) {
				if (Vehicle.vehicleWestTnk != "") {
					spdlog::debug("vehicleWestTnk: {}", Vehicle.vehicleWestTnk);
					return PathCode64(Vehicle.vehicleWestTnk.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_west_tnk.fpk");
				}
			}
			else if (vehicleType == 9) {
				if (Vehicle.vehicleEastTnk != "") {
					spdlog::debug("vehicleEastTnk: {}", Vehicle.vehicleEastTnk);
					return PathCode64(Vehicle.vehicleEastTnk.c_str());
				}
				else {
					return PathCode64("/Assets/tpp/pack/vehicle/veh_rl_east_tnk.fpk");
				}
			}

			return 0;
		}

		//ZIP: Function that loads the player vehicle and the select camo for deployment.
		char PreparePlayerVehicleInGameHook(longlong param_1, ulonglong param_2)
		{
			if (!overrideVehicleSystem) {
				return PreparePlayerVehicleInGame(param_1, param_2);
			}

			if (param_2 == 0) {
				return '\0';
			}

			ulonglong lVar2 = *(longlong*)(param_1 + 0x58);
			char vehicleType = *(byte*)(lVar2 + 0x2b);
			ulonglong newVehicleFpk = GetVehicleOverride((ulonglong)(vehicleType - 1));
			return PreparePlayerVehicleInGame(param_1, newVehicleFpk);
		}//PreparePlayerVehicleInGameHook

		//ZIP: Function that loads the player vehicle and all the camos applicable in sortie.
		char PreparePlayerVehicleInSortieHook(longlong param_1) {
			if (!overrideVehicleSystem) {
				return PreparePlayerVehicleInSortie(param_1);
			}

			ulonglong local_318[96];
			char bVar1 = *(byte*)(param_1 + 0x69);
			local_318[0] = GetVehicleOverride((ulonglong)(bVar1 - 1));

			int local_res18[4];
			ulonglong uVar10;
			void* pvVar7 = (void*)LoadDefaultFpkPtrFunc(*(longlong*)(param_1 + 0x50), 0);

			//ZIP: Loads all camos for players to choose.
			ulonglong *puVar8 = LoadAllVehicleCamoFpks();
			longlong lVar11 = 0x5f;
			ulonglong uVar9 = (ulonglong)(bVar1 != 0);
			do {
				puVar8 = puVar8 + 2;
				uVar10 = uVar9;
				if (*puVar8 != 0) {
					uVar10 = (ulonglong)(byte)((char)uVar9 + 1);
					local_318[uVar9] = *puVar8;
				}
				lVar11 = lVar11 + -1;
				uVar9 = uVar10;
			} while (lVar11 != 0);

			LoadDefaultFpksFunc(pvVar7, local_res18, local_318, (uint)uVar10);

			int *puVar2 = *(int**)(param_1 + 0x58);
			int iVar2 = puVar2[1];
			int iVar3 = puVar2[2];
			int iVar4 = puVar2[3];
			*(int*)(param_1 + 0x30) = *puVar2;
			*(int*)(param_1 + 0x34) = iVar2;
			*(int*)(param_1 + 0x38) = iVar3;
			*(int*)(param_1 + 0x3c) = iVar4;
			longlong lVar10 = *(longlong*)(param_1 + 0x58);
			int uVar5 = *(int*)(lVar10 + 0x14);
			int uVar6 = *(int*)(lVar10 + 0x18);
			int uVar7 = *(int*)(lVar10 + 0x1c);
			*(int*)(param_1 + 0x40) = *(int*)(lVar10 + 0x10);
			*(int*)(param_1 + 0x44) = uVar5;
			*(int*)(param_1 + 0x48) = uVar6;
			*(int*)(param_1 + 0x4c) = uVar7;

			return 1;
		}//PreparePlayerVehicleInSortieHook

		/*
			IHHook setup
		*/
		void CreateHooks() {
			spdlog::debug(__func__);

			CREATE_HOOK(PreparePlayerVehicleInSortie)
			CREATE_HOOK(PreparePlayerVehicleInGame)

			ENABLEHOOK(PreparePlayerVehicleInSortie)
			ENABLEHOOK(PreparePlayerVehicleInGame)
		}//CreateHooks

		int CreateLibs(lua_State* L) {
			spdlog::debug(__func__);

			luaL_Reg libFuncs[] = {
				{ "SetOverrideVehicleSystem", l_SetOverrideVehicleSystem },
				
				{ "SetVehicleWestLvFpkPath", l_SetVehicleWestLvFpkPath },
				{ "SetVehicleEastLvFpkPath", l_SetVehicleEastLvFpkPath },
				{ "SetVehicleWestTrcFpkPath", l_SetVehicleWestTrcFpkPath },
				{ "SetVehicleEastTrcFpkPath", l_SetVehicleEastTrcFpkPath },
				{ "SetVehicleWestWavMachineGunFpkPath", l_SetVehicleWestWavMachineGunFpkPath },
				{ "SetVehicleWestWavCannonFpkPath", l_SetVehicleWestWavCannonFpkPath },
				{ "SetVehicleEastWavFpkPath", l_SetVehicleEastWavFpkPath },
				{ "SetVehicleEastWavRocketFpkPath", l_SetVehicleEastWavRocketFpkPath },
				{ "SetVehicleWestTnkFpkPath", l_SetVehicleWestTnkFpkPath },
				{ "SetVehicleEastTnkFpkPath", l_SetVehicleEastTnkFpkPath },

				{ NULL, NULL }//GOTCHA: crashes without
			};
			luaI_openlib(L, "IHH", libFuncs, 0);
			return 1;
		}//CreateLibs
	}//Hooks_Vehicle
}//namespace IHHook