#pragma once
#include "lua.h"

namespace IHHook {
	namespace Hooks_Buddy {
		void CreateHooks();
		int CreateLibs(lua_State* L);
		
		int l_SetOverrideBuddySystem(lua_State* L);
		int l_SetBuddyTypeForPartsType(lua_State* L);

		int l_SetBuddyHorsePartsFpkPath(lua_State* L);
		int l_SetBuddyDogPartsFpkPath(lua_State* L);
		int l_SetBuddyQuietPartsFpkPath(lua_State* L);
		int l_SetBuddyWalkerGearPartsFpkPath(lua_State* L);
	}//namespace Hooks_Buddy
}//namespace IHHook

