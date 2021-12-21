#pragma once
#include "lua.h"

namespace IHHook {
	namespace Hooks_FoxString {
		void CreateHooks();
		int CreateLibs(lua_State* L);

		void AddReplacementToList(std::string filePathOld, std::string filePathNew);
		int l_AddReplacementFoxString(lua_State* L);
	}//namespace Hooks_FoxString
}//namespace IHHook

