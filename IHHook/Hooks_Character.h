#pragma once
#include "lua.h"

namespace IHHook {
	namespace Hooks_Character {
		void CreateHooks();

		int l_SetPlayerPartsFpk(lua_State* L);
		int l_SetPlayerPartsPart(lua_State * L);
	}//namespace Hooks_Character
}//namespace IHHook

