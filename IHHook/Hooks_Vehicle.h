#pragma once
#include "lua.h"

namespace IHHook {
	namespace Hooks_Vehicle {
		void CreateHooks();

		int CreateLibs(lua_State* L);
		
		int l_SetOverrideVehicleSystem(lua_State* L);

		int l_SetVehicleWestLvFpkPath(lua_State* L);
		int l_SetVehicleEastLvFpkPath(lua_State* L);
		int l_SetVehicleWestTrcFpkPath(lua_State* L);
		int l_SetVehicleEastTrcFpkPath(lua_State* L);
		int l_SetVehicleWestWavMachineGunFpkPath(lua_State* L);
		int l_SetVehicleWestWavCannonFpkPath(lua_State* L);
		int l_SetVehicleEastWavFpkPath(lua_State* L);
		int l_SetVehicleEastWavRocketFpkPath(lua_State* L);
		int l_SetVehicleWestTnkFpkPath(lua_State* L);
		int l_SetVehicleEastTnkFpkPath(lua_State* L);
	}//namespace Hooks_Vehicle
}//namespace IHHook

