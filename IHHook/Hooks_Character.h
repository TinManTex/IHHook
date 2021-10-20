#pragma once
#include "lua.h"

namespace IHHook {
	namespace Hooks_Character {
		void CreateHooks();
		int CreateLibs(lua_State* L);
		
		int l_SetOverrideCharacterSystem(lua_State* L);
		int l_SetUseHeadForPlayerParts(lua_State* L);
		int l_SetUseBionicHandForPlayerParts(lua_State* L);
	
		int l_SetPlayerPartsFpkPath(lua_State* L);
		int l_SetPlayerPartsPartsPath(lua_State* L);
		int l_SetSkinToneFv2Path(lua_State* L);
		int l_SetPlayerCamoFpkPath(lua_State* L);
		int l_SetPlayerCamoFv2Path(lua_State* L);
		int l_SetBionicHandFpkPath(lua_State* L);
		int l_SetBionicHandFv2Path(lua_State* L);
		int l_SetSnakeFaceFpkPath(lua_State* L);
		int l_SetSnakeFaceFv2Path(lua_State* L);
		int l_SetAvatarHornFpkPath(lua_State* L);
		int l_SetAvatarHornFv2Path(lua_State* L);
		
		//UNUSED alternative
		int l_SetPlayerPartsFpk(lua_State* L);
		int l_SetPlayerPartsPart(lua_State * L);
	}//namespace Hooks_Character
}//namespace IHHook

