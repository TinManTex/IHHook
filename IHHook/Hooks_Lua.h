#pragma once

#include <lua.h>

namespace IHHook {
	namespace Hooks_Lua {
		void CreateHooks(size_t RealBaseAddr);

		int l_FoxLua_Init(lua_State* L);
		int l_FoxLua_OnUpdate(lua_State* L);

		extern lua_State* luaState;
	}//namespace Hooks_Lua
}//namespace IHHook