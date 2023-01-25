//ZIP: Extending vars.buddy*, a buddy change system

#include "Hooks_Buddy.h"
#include "spdlog/spdlog.h"
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_Buddy {
		bool overrideBuddySystem = false;
		struct Buddy {
			uint buddyType = 255;
			std::string horseFpkPath = "";
			std::string dogFpkPath = "";
			std::string quietFpkPath = "";
			std::string walkerGearFpkPath = "";
		};//Buddy
		Buddy buddy;

		bool overrideBuddyEquipmentSystem = false;
		struct BuddyEquip {
			uint quietWeaponType = 255;
			uint walkerGearArmType = 255;
			uint walkerGearHeadType = 255;
			uint walkerGearWeaponType = 255;

			std::string quietWeaponFpk = "";
			std::string walkerGearArmFpk = "";
			std::string walkerGearHeadFpk = "";
			std::string walkerGearWeaponFpk = "";

			std::string dogCommonFpk = "";
			std::string horseCommonFpk = "";
			std::string walkerGearCommonFpk = "";
		};//BuddyEquip
		BuddyEquip buddyEqp;

		int l_SetOverrideBuddySystem(lua_State* L) {
			overrideBuddySystem = lua_toboolean(L, -1);
			spdlog::debug("SetOverrideBuddySystem override:{}, ", overrideBuddySystem);
			return 0;
		}//l_SetOverrideBuddySystem
		int l_SetBuddyTypeForPartsType(lua_State* L) {
			buddy.buddyType = (uint)lua_tointeger(L, -1);
			spdlog::debug("SetBuddyTypeForPartsType buddyType:{}, ", buddy.buddyType);
			return 0;
		}//l_SetBuddyTypeForPartsType
		/*
			SetBuddy*PartsFpkPath
		*/
		int l_SetBuddyDogPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyDogPartsFpkPath {}, ", filePath);
			buddy.dogFpkPath = filePath;
			return 0;
		}//l_SetBuddyDogPartsFpkPath
		int l_SetBuddyHorsePartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyHorsePartsFpkPath {}, ", filePath);
			buddy.horseFpkPath = filePath;
			return 0;
		}//l_SetBuddyHorsePartsFpkPath
		int l_SetBuddyQuietPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyQuietPartsFpkPath {}, ", filePath);
			buddy.quietFpkPath = filePath;
			return 0;
		}//l_SetBuddyQuietPartsFpkPath
		int l_SetBuddyWalkerGearPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyWalkerGearPartsFpkPath {}, ", filePath);
			buddy.walkerGearFpkPath = filePath;
			return 0;
		}//l_SetBuddyWalkerGearPartsFpkPath
		/*
			SetOverrideBuddyEquipmentSystem/SetBuddyEquipmentType
			ZIP: TODO GetVars for matching equipment type.
		*/
		int l_SetOverrideBuddyEquipmentSystem(lua_State* L) {
			overrideBuddyEquipmentSystem = lua_toboolean(L, -1);
			spdlog::debug("SetOverrideBuddyEquipmentSystem override:{}, ", overrideBuddyEquipmentSystem);
			return 0;
		}//l_SetOverrideBuddyEquipmentSystem

		int l_SetBuddyQuietWeaponType(lua_State* L) {
			buddyEqp.quietWeaponType = (uint)lua_tointeger(L, -1);
			spdlog::debug("SetBuddyQuietWeaponType buddyType:{}, ", buddyEqp.quietWeaponType);
			return 0;
		}//l_SetBuddyQuietWeaponType

		int l_SetBuddyWalkerGearArmType(lua_State* L) {
			buddyEqp.walkerGearArmType = (uint)lua_tointeger(L, -1);
			spdlog::debug("SetBuddyWalkerGearArmType buddyType:{}, ", buddyEqp.walkerGearArmType);
			return 0;
		}//l_SetBuddyWalkerGearArmType

		int l_SetBuddyWalkerGearHeadType(lua_State* L) {
			buddyEqp.walkerGearHeadType = (uint)lua_tointeger(L, -1);
			spdlog::debug("SetBuddyWalkerGearHeadType buddyType:{}, ", buddyEqp.walkerGearHeadType);
			return 0;
		}//l_SetBuddyWalkerGearHeadType

		int l_SetBuddyWalkerGearWeaponType(lua_State* L) {
			buddyEqp.walkerGearWeaponType = (uint)lua_tointeger(L, -1);
			spdlog::debug("SetBuddyWalkerGearWeaponType buddyType:{}, ", buddyEqp.walkerGearWeaponType);
			return 0;
		}//l_SetBuddyWalkerGearWeaponType

		/*
			SetBuddyEquipmentFuncs
		*/
		int l_SetBuddyQuietWeaponFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyQuietWeaponFpkPath {}, ", filePath);
			buddyEqp.quietWeaponFpk = filePath;
			return 0;
		}//l_SetBuddyQuietWeaponFpkPath
		int l_SetBuddyWalkerGearArmFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyWalkerGearArmFpkPath {}, ", filePath);
			buddyEqp.walkerGearArmFpk = filePath;
			return 0;
		}//l_SetBuddyWalkerGearArmFpkPath
		int l_SetBuddyWalkerGearHeadFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyWalkerGearHeadFpkPath {}, ", filePath);
			buddyEqp.walkerGearHeadFpk = filePath;
			return 0;
		}//l_SetBuddyWalkerGearHeadFpkPath
		int l_SetBuddyWalkerGearWeaponFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyWalkerGearWeaponFpkPath {}, ", filePath);
			buddyEqp.walkerGearWeaponFpk = filePath;
			return 0;
		}//l_SetBuddyWalkerGearWeaponFpkPath
		/*
			SetBuddy*CommonFpkPath
		*/
		int l_SetBuddyDogCommonFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyDogCommonFpkPath {}, ", filePath);
			buddyEqp.dogCommonFpk = filePath;

			return 0;
		}//l_SetBuddyDogCommonFpkPath
		int l_SetBuddyHorseCommonFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) { filePath = ""; }
			spdlog::debug("SetBuddyHorseCommonFpkPath {}, ", filePath);
			buddyEqp.horseCommonFpk = filePath;
			return 0;
		}//l_SetBuddyHorseCommonFpkPath
		int l_SetBuddyWalkerGearCommonFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {filePath = "";}
			spdlog::debug("SetBuddyWalkerGearCommonFpkPath {}, ", filePath);
			buddyEqp.walkerGearCommonFpk = filePath;
			return 0;
		}//l_SetBuddyWalkerGearCommonFpkPath
		/*
			Vanilla FPK paths
		*/
		std::string buddyHorsePartsFpksDefault[]{
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_00.fpk",
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_03.fpk",
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_02_0.fpk",
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_02_1.fpk",
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_02_2.fpk",
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_05.fpk",
			"/Assets/tpp/pack/buddy/horse/buddy_horse2_04.fpk",
		};
		std::string buddyDogPartsFpksDefault[]{
			"/Assets/tpp/pack/buddy/dog/buddy_dog2_00.fpk",
			"/Assets/tpp/pack/buddy/dog/buddy_dog2_01.fpk",
			"/Assets/tpp/pack/buddy/dog/buddy_dog2_02.fpk",
			"/Assets/tpp/pack/buddy/dog/buddy_dog2_03.fpk",
			"/Assets/tpp/pack/buddy/dog/buddy_dog2_04.fpk",
		};
		std::string buddyQuietPartsFpksDefault[]{
			"/Assets/tpp/pack/buddy/quiet/buddy_quiet2_00.fpk",
			"/Assets/tpp/pack/buddy/quiet/buddy_quiet2_01.fpk",
			"/Assets/tpp/pack/buddy/quiet/buddy_quiet2_02.fpk",
			"/Assets/tpp/pack/buddy/quiet/buddy_quiet2_03.fpk",
			"/Assets/tpp/pack/buddy/quiet/buddy_quiet2_04.fpk",
			"/Assets/tpp/pack/buddy/quiet/buddy_quiet2_05.fpk",
		};
		std::string buddyWalkerGearPartsFpksDefault[]{
			"/Assets/tpp/pack/buddy/walkergear/buddy_wg2_00.fpk",
		};
		/*
			Vanilla Equipment FPK paths
		*/
		std::string buddyQuietWeaponFpksDefault[]{
			"/Assets/tpp/pack/buddy/quiet/bq_wp_00.fpk",
			"/Assets/tpp/pack/buddy/quiet/bq_wp_01.fpk",
			"/Assets/tpp/pack/buddy/quiet/bq_wp_02.fpk",
		};
		std::string buddyWalkerGearWeaponFpksDefault[]{
			"/Assets/tpp/pack/buddy/walkergear/bw_wp_00.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_wp_01.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_wp_02.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_wp_03.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_wp_04.fpk",
		};
		std::string buddyWalkerGearArmFpksDefault[]{
			"/Assets/tpp/pack/buddy/walkergear/bw_am_00.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_am_01.fpk",
		};
		std::string buddyWalkerGearHeadFpksDefault[]{
			"/Assets/tpp/pack/buddy/walkergear/bw_hd_00.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_hd_01.fpk",
			"/Assets/tpp/pack/buddy/walkergear/bw_hd_02.fpk",
		};
		/*
			Buddy hooks
		*/
		bool IsBuddyTypeValid(unsigned int buddyType) {
			//ZIP: No buddy set
			if (buddyType == 0 || buddy.buddyType == 255 ) {
				return false;
			}
			//ZIP: Buddytype attempting to load doesn't match the override buddy type
			if (buddy.buddyType != buddyType) {
				return false;
			}
			//ZIP: No path set for the current buddy type
			switch (buddyType) {
				case 1: //For D-Horse
					if (buddy.horseFpkPath == "") return false;
					break;
				case 2: //For D-Horse
					if (buddy.dogFpkPath == "") return false;
					break;
				case 3: //For Quiet
					//ZIP: Quiet's costumeType is set to 0 for the mission "A Quiet Exit" ( missionCode 10260 )
					//if (missionCode == 10260) return false;
					if (buddy.quietFpkPath == "") return false;
					break;
				case 4: //For Walker Gear
					if (buddy.walkerGearFpkPath == "") return false;
					break;
			}
			return true;
		}//IsBuddyTypeValid

		ulonglong* LoadBuddyMainFileHook(ulonglong param_1, ulonglong* fileSlotIndex, unsigned int buddyType, ulonglong param_4) {
			spdlog::debug("LoadBuddyMainFileHook buddyType:{}", buddyType);

			if (!IsBuddyTypeValid(buddyType)) {
				overrideBuddySystem = false;
			}
			//ZIP: No override or valid buddy? Fallback
			if (!overrideBuddySystem ) {
				return LoadBuddyMainFile(param_1, fileSlotIndex, buddyType, param_4);
			}
			switch (buddyType) {
				case 1: //For D-Horse
					if (buddy.horseFpkPath != "") return GetFPKFromFilePath(buddy.horseFpkPath, "horseFpkPath", fileSlotIndex);
					break;
				case 2: //For D-Horse
					if (buddy.dogFpkPath != "") return GetFPKFromFilePath(buddy.dogFpkPath, "dogFpkPath", fileSlotIndex);
					break;
				case 3: //For Quiet
					if (buddy.quietFpkPath != "") {
						std::string filePath = buddy.quietFpkPath;
						spdlog::debug("quietFpkPath: {}", filePath);
						ulonglong filePath64 = PathCode64(filePath.c_str());
						fox::Path fileSlotIndex_02;
						LoadFile(&fileSlotIndex_02.Hash, filePath64);
						//ZIP: TODO UnkLoadBuddyFileInHeliSpace
						fox::Path* fileSlotIndex_01 = Path_Copy((fox::Path*)fileSlotIndex, &fileSlotIndex_02);
						return &fileSlotIndex_01->Hash;
					}
					break;
				case 4: //For Walker Gear
					if (buddy.walkerGearFpkPath != "") return GetFPKFromFilePath(buddy.walkerGearFpkPath, "walkerGearFpkPath", fileSlotIndex);
					break;
				default: //Isn't a buddy, but is loaded anyways.
					fox::Path* fileSlotIndex_01 = GetEmptyPath();
					fileSlotIndex_01 = Path_Copy((fox::Path*)fileSlotIndex, fileSlotIndex_01);
					return &fileSlotIndex_01->Hash;
					break;
			}
			return fileSlotIndex;
		}//LoadBuddyMainFileHook
		/*
			Buddy equipment hooks
		*/
		ulonglong* LoadBuddyQuietWeaponFpkHook(ulonglong param_1, ulonglong* fileSlotIndex, short param_quietWeaponId) {
			//ZIP: TODO GetVars for Quiet weapon type
			if (!overrideBuddyEquipmentSystem || buddyEqp.quietWeaponFpk == "") {
				return LoadBuddyQuietWeaponFpk(param_1, fileSlotIndex, param_quietWeaponId);
			}
			return GetFPKFromFilePath(buddyEqp.quietWeaponFpk, "quietWeaponFpk", fileSlotIndex);
		}//LoadBuddyQuietWeaponFpkHook
		ulonglong* LoadBuddyWalkerGearWeaponFpkHook(ulonglong param_1, ulonglong* fileSlotIndex, ulonglong param_3, ulonglong param_4) {
			//ZIP: TODO GetVars for Walker Gear weapon type		
			if (!overrideBuddyEquipmentSystem || buddyEqp.walkerGearWeaponFpk == "") {
				return LoadBuddyWalkerGearWeaponFpk(param_1, fileSlotIndex, param_3, param_4);
			}
			return GetFPKFromFilePath(buddyEqp.walkerGearWeaponFpk, "walkerGearWeaponFpk", fileSlotIndex);
		}//LoadBuddyWalkerGearWeaponFpkHook
		//ZIP: Main buddy FPKs contain head and arm content. Leaving this here, just in case.
		ulonglong* LoadBuddyWalkerGearArmFpkHook(ulonglong param_1, ulonglong* fileSlotIndex, ulonglong param_3, ulonglong param_4) {
			if (!overrideBuddyEquipmentSystem || buddyEqp.walkerGearArmFpk == "") {
				return LoadBuddyWalkerGearArmFpk(param_1, fileSlotIndex, param_3, param_4);
			}
			return GetFPKFromFilePath(buddyEqp.walkerGearArmFpk, "walkerGearArmFpk", fileSlotIndex);
		}//LoadBuddyWalkerGearArmFpkHook
		ulonglong* LoadBuddyWalkerGearHeadFpkHook(ulonglong param_1, ulonglong* fileSlotIndex, ulonglong param_3, ulonglong param_4) {
			if (!overrideBuddyEquipmentSystem || buddyEqp.walkerGearHeadFpk == "") {
				return LoadBuddyWalkerGearHeadFpk(param_1, fileSlotIndex, param_3, param_4);
			}
			return GetFPKFromFilePath(buddyEqp.walkerGearHeadFpk, "walkerGearHeadFpk", fileSlotIndex);
		}//LoadBuddyWalkerGearHeadFpkHook
		void LoadBuddyDogCommonFPKHook(longlong param_1, ulonglong* fileSlotIndex) {
			if (!overrideBuddyEquipmentSystem || buddyEqp.dogCommonFpk == "") {
				return LoadBuddyDogCommonFPK(param_1, fileSlotIndex);
			}
			GetFPKFromFilePath(buddyEqp.dogCommonFpk, "dogCommonFpk", fileSlotIndex);
		}//LoadBuddyDogCommonFPK
		void LoadBuddyHorseCommonFPKHook(longlong param_1, ulonglong* fileSlotIndex) {
			if (!overrideBuddyEquipmentSystem || buddyEqp.horseCommonFpk == "") {
				return LoadBuddyHorseCommonFPK(param_1, fileSlotIndex);
			}
			GetFPKFromFilePath(buddyEqp.horseCommonFpk, "horseCommonFpk", fileSlotIndex);
		}//LoadBuddyHorseCommonFPK
		/*void LoadBuddyWalkerGearCommonFPKHook(longlong param_1, ulonglong* fileSlotIndex) {
			if (!overrideBuddyEquipmentSystem || buddyEqp.walkerGearCommonFpk == "") {
				return LoadBuddyWalkerGearCommonFPK(param_1, fileSlotIndex);
			}
			GetFPKFromFilePath(buddyEqp.walkerGearCommonFpk, "walkerGearCommonFpk", fileSlotIndex);
		}*///LoadBuddyWalkerGearCommonFPK
		ulonglong* GetFPKFromFilePath(std::string filePath, std::string debugMsg, ulonglong* fileSlotIndex) {
			spdlog::debug(debugMsg+": {}", filePath);
			ulonglong filePath64 = PathCode64(filePath.c_str());
			LoadFile(fileSlotIndex, filePath64);
			return fileSlotIndex;
		}

		/*
			IHHook setup
		*/
		void CreateHooks() {
			spdlog::debug(__func__);

			CREATE_HOOK(LoadBuddyMainFile)
			CREATE_HOOK(LoadBuddyQuietWeaponFpk)
			CREATE_HOOK(LoadBuddyWalkerGearArmFpk)
			CREATE_HOOK(LoadBuddyWalkerGearHeadFpk)
			CREATE_HOOK(LoadBuddyWalkerGearWeaponFpk)
			CREATE_HOOK(LoadBuddyDogCommonFPK)
			CREATE_HOOK(LoadBuddyHorseCommonFPK)
			//CREATE_HOOK(LoadBuddyWalkerGearCommonFPK)

			ENABLEHOOK(LoadBuddyMainFile)
			ENABLEHOOK(LoadBuddyQuietWeaponFpk)
			ENABLEHOOK(LoadBuddyWalkerGearArmFpk)
			ENABLEHOOK(LoadBuddyWalkerGearHeadFpk)
			ENABLEHOOK(LoadBuddyWalkerGearWeaponFpk)
			ENABLEHOOK(LoadBuddyDogCommonFPK)
			ENABLEHOOK(LoadBuddyHorseCommonFPK)
			//ENABLEHOOK(LoadBuddyWalkerGearCommonFPK)
		}//CreateHooks

		int CreateLibs(lua_State* L) {
			spdlog::debug(__func__);

			luaL_Reg libFuncs[] = {
				{ "SetOverrideBuddySystem", l_SetOverrideBuddySystem },
				{ "SetBuddyTypeForPartsType", l_SetBuddyTypeForPartsType },

				{ "SetBuddyHorsePartsFpkPath", l_SetBuddyHorsePartsFpkPath },
				{ "SetBuddyDogPartsFpkPath", l_SetBuddyDogPartsFpkPath },
				{ "SetBuddyQuietPartsFpkPath", l_SetBuddyQuietPartsFpkPath },
				{ "SetBuddyWalkerGearPartsFpkPath", l_SetBuddyWalkerGearPartsFpkPath },

				{ "SetOverrideBuddyEquipmentSystem", l_SetOverrideBuddyEquipmentSystem },
				{ "SetBuddyQuietWeaponType", l_SetBuddyQuietWeaponType },
				{ "SetBuddyWalkerGearArmType", l_SetBuddyWalkerGearArmType },
				{ "SetBuddyWalkerGearHeadType", l_SetBuddyWalkerGearHeadType },
				{ "SetBuddyWalkerGearWeaponType", l_SetBuddyWalkerGearWeaponType },

				{ "SetBuddyQuietWeaponFpkPath", l_SetBuddyQuietWeaponFpkPath },
				{ "SetBuddyWalkerGearArmFpkPath", l_SetBuddyWalkerGearArmFpkPath },
				{ "SetBuddyWalkerGearHeadFpkPath", l_SetBuddyWalkerGearHeadFpkPath },
				{ "SetBuddyWalkerGearWeaponFpkPath", l_SetBuddyWalkerGearWeaponFpkPath },

				{ "SetBuddyDogCommonFpkPath", l_SetBuddyDogCommonFpkPath },
				{ "SetBuddyHorseCommonFpkPath", l_SetBuddyHorseCommonFpkPath },
				{ "SetBuddyWalkerGearCommonFpkPath", l_SetBuddyWalkerGearCommonFpkPath },

				{ NULL, NULL }//GOTCHA: crashes without
			};
			luaI_openlib(L, "IhkBuddy", libFuncs, 0);
			return 1;
		}//CreateLibs
	}//Hooks_Buddy
}//namespace IHHook