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

		int l_SetOverrideBuddySystem(lua_State* L) {
			overrideBuddySystem = lua_toboolean(L, -1);

			spdlog::debug("l_SetOverrideBuddySystem override:{}, ", overrideBuddySystem);

			return 0;
		}//l_SetOverrideBuddySystem
		int l_SetBuddyTypeForPartsType(lua_State* L) {
			buddy.buddyType = (uint)lua_tointeger(L, -1);

			spdlog::debug("l_SetBuddyTypeForPartsType buddyType:{}, ", buddy.buddyType);

			return 0;
		}//l_SetBuddyTypeForPartsType

		/*
			SetBuddy*PartsFpkPath
		*/
		int l_SetBuddyDogPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetBuddyDogPartsFpkPath {}, ", filePath);
			buddy.dogFpkPath = filePath;

			return 0;
		}//l_SetBuddyDogPartsFpkPath
		int l_SetBuddyHorsePartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetBuddyHorsePartsFpkPath {}, ", filePath);
			buddy.horseFpkPath = filePath;

			return 0;
		}//l_SetBuddyHorsePartsFpkPath
		int l_SetBuddyQuietPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetBuddyQuietPartsFpkPath {}, ", filePath);
			buddy.quietFpkPath = filePath;

			return 0;
		}//l_SetBuddyQuietPartsFpkPath
		int l_SetBuddyWalkerGearPartsFpkPath(lua_State* L) {
			const char* filePath = lua_tostring(L, -1);
			if (filePath == NULL) {
				filePath = "";
			}
			spdlog::debug("l_SetBuddyWalkerGearPartsFpkPath {}, ", filePath);
			buddy.walkerGearFpkPath = filePath;

			return 0;
		}//l_SetBuddyWalkerGearPartsFpkPath

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
			Buddy hooks/IHHook setup
		*/
		bool IsBuddyTypeValid(int buddyType) {
			//ZIP: No buddy set
			if (buddyType == 0) {
				return false;
			}

			//ZIP: Buddytype attempting to load doesn't match the override buddy type
			if (buddy.buddyType != 255) {
				if (buddy.buddyType != buddyType) {
					return false;
				}
			}

			//ZIP: No paths set
			if (buddy.horseFpkPath == "" && buddy.dogFpkPath == "" && buddy.quietFpkPath == "" && buddy.walkerGearFpkPath == "") {
				return false;
			}

			return true;
		}//IsBuddyTypeValid

		ulonglong* LoadBuddyMainFileHook(ulonglong param_1, ulonglong* fileSlotIndex, int buddyType, ulonglong param_4) {
			spdlog::debug("LoadBuddyMainFileHook buddyType:{}", buddyType);

			if (!IsBuddyTypeValid(buddyType)) {
				overrideBuddySystem = false;
			}

			//ZIP: No override or valid buddy? Fallback
			if (!overrideBuddySystem ) {
				return LoadBuddyMainFile(param_1, fileSlotIndex, buddyType, param_4);
			}

			std::string filePath = "";
			ulonglong filePath64 = 0;
			if (buddyType == 1) { 
				//For D-Horse
				if (buddy.horseFpkPath != "") {
					filePath = buddy.horseFpkPath;
					spdlog::debug("horseFpkPath: {}", filePath);
					filePath64 = PathCode64(filePath.c_str());
					LoadFile(fileSlotIndex, filePath64);
				}
			}
			else {
				//For D-Dog
				if (buddyType == 2) {
					if (buddy.dogFpkPath != "") {
						filePath = buddy.dogFpkPath;
						spdlog::debug("dogFpkPath: {}", filePath);
						filePath64 = PathCode64(filePath.c_str());
						LoadFile(fileSlotIndex, filePath64);
					}
				}
				else {
					ulonglong * fileSlotIndex_01;
					if (buddyType == 3) { //For Quiet
						//ZIP: Quiet's costumeType is set to 0 for the mission "A Quiet Exit" ( missionCode 10260 )
						//if (vars_02->missionCode == 10260) {
						//	vars_02[3].buddyQuietCostumeType = 0;
						//}
						if (buddy.quietFpkPath != "") {
							filePath = buddy.quietFpkPath;
							spdlog::debug("quietFpkPath: {}", filePath);
							filePath64 = PathCode64(filePath.c_str());

							ulonglong fileSlotIndex_02;
							LoadFile(&fileSlotIndex_02, filePath64);
							//ZIP: TODO UnkLoadBuddyFileInHeliSpace
							fileSlotIndex_01 = LoadFile_01(fileSlotIndex, &fileSlotIndex_02);
							return fileSlotIndex_01; 
						}
					}
				
					if (buddyType != 4) { //If not walker gear nor Quiet.
						ulonglong *filePath64_01 = (ulonglong*)LoadFile_03();
						fileSlotIndex_01 = LoadFile_01(fileSlotIndex, filePath64_01);
						return fileSlotIndex;
					}
			
					if (buddy.walkerGearFpkPath != "") { //For Walker Gear
						filePath = buddy.walkerGearFpkPath;
						spdlog::debug("walkerGearFpkPath: {}", filePath);
						filePath64 = PathCode64(filePath.c_str());
						LoadFile(fileSlotIndex, filePath64);
					}
				}
			}

			return fileSlotIndex;
		}//LoadBuddyMainFileHook

		void CreateHooks() {
			spdlog::debug(__func__);

			CREATE_HOOK(LoadBuddyMainFile)
			ENABLEHOOK(LoadBuddyMainFile)
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

				{ NULL, NULL }//GOTCHA: crashes without
			};
			luaI_openlib(L, "IHH", libFuncs, 0);
			return 1;
		}//CreateLibs
	}//Hooks_Buddy
}//namespace IHHook