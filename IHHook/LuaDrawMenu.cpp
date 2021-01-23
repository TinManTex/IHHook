#include "Hooks_Lua.h"
#include <spdlog/spdlog.h>
namespace IHHook {

	void LuaDrawMenu() {
		if (Hooks_Lua::luaState != NULL) {
			lua_State* L = Hooks_Lua::luaState;
			
			lua_getglobal(L, "InfMenu");
			if (lua_isnil(L, -1)) {
				return;
			}
			spdlog::info("LuaDrawMenu: InfMenu not nil");
			lua_getfield(L, -1, "DrawMenu");
			lua_remove(L, -1);
			lua_pushvalue(L, -1);
			lua_pcall(L, 0, 0, 0);
		}
	}//LuaDrawMenu
}//namespace IHHook