#pragma once
#include <string>
#include "lua.h"

namespace IHHook {
	namespace Hooks_Buddy {
		void CreateHooks();
		int CreateLibs(lua_State* L);
		ulonglong* GetFPKFromFilePath(std::string filePath, std::string debugMsg, ulonglong* fileSlotIndex);
		
		int l_SetOverrideBuddySystem(lua_State* L);
		int l_SetBuddyTypeForPartsType(lua_State* L);

		int l_SetBuddyHorsePartsFpkPath(lua_State* L);
		int l_SetBuddyDogPartsFpkPath(lua_State* L);
		int l_SetBuddyQuietPartsFpkPath(lua_State* L);
		int l_SetBuddyWalkerGearPartsFpkPath(lua_State* L);

		int l_SetOverrideBuddyEquipmentSystem(lua_State* L);
		int l_SetBuddyQuietWeaponType(lua_State* L);
		int l_SetBuddyWalkerGearArmType(lua_State* L);
		int l_SetBuddyWalkerGearHeadType(lua_State* L);
		int l_SetBuddyWalkerGearWeaponType(lua_State* L);

		int l_SetBuddyQuietWeaponFpkPath(lua_State* L);
		int l_SetBuddyWalkerGearArmFpkPath(lua_State* L);
		int l_SetBuddyWalkerGearHeadFpkPath(lua_State* L);
		int l_SetBuddyWalkerGearWeaponFpkPath(lua_State* L);

		int l_SetBuddyDogCommonFpkPath(lua_State* L);
		int l_SetBuddyHorseCommonFpkPath(lua_State* L);
		//int l_SetBuddyWalkerGearCommonFpkPath(lua_State* L);
	}//namespace Hooks_Buddy
}//namespace IHHook

