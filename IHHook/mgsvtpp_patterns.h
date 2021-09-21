#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking
namespace IHHook {
	std::map<std::string, std::string> mgsvtpp_patterns{
		{"StrCode64", "48 89 6C 24 ? 56 48 83 EC 20 80 3C ? 00"},
		{"FNVHash32", "56 48 81 EC 30 01 00 00 48 89 CE"},
		{"GetFreeRoamLangId", "0F B7 C2 83 F8 0A 74 ? 83 F8 14 74 ? 83 F8 32"},
		{"UpdateFOVLerp", "4C 8B DC 49 89 5B ? 55 56 57 41 54 41 57 49 8D AB ? ? ? ?"},
		//{"UnkSomePrintFunction", ""},//WARNING: UnkSomePrintFunction: Instruction at 142ef2c00 is not adjacent to previous (expected 142ef2c3d)
		//{"l_StubbedOut", ""},//WARNING: l_StubbedOut: Instruction at 14024a8e3 is not adjacent to previous (expected 14024a8f0)
		//{"nullsub_2", ""},//WARNING: nullsub_2: Instruction at 1409c8f93 is not adjacent to previous (expected 1409c8fa0)
		{"LoadFile", "53 48 83 EC 20 49 89 D1 49 89 D2"},
		{"lua_newstate", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 89 D7 4C 89 C5"},
		{"lua_close", "48 89 5C 24 ? 57 48 83 EC 20 48 8B 59 ? 48 8B 9B ? ? ? ?"},
		{"lua_newthread", "53 48 83 EC 20 48 8B 51 ? 48 89 CB 48 8B 42 ?"},
		{"lua_atpanic", "4C 8B 41 ? 49 8B 80 ? ? ? ? 49 89 90 ? ? ? ?"},
		//{"lua_gettop", ""},//USING_CODE
		{"lua_settop", "85 D2 78 ? 4C 63 C2"},
		{"lua_pushvalue", "48 83 EC 28 49 89 CA E8 ? ? ? ? 4D 8B 42 ? 48 8B 10"},
		{"lua_remove", "48 83 EC 28 49 89 CA E8 ? ? ? ? 48 83 C0 10"},
		{"lua_insert", "48 83 EC 28 49 89 CB E8 ? ? ? ?"},
		{"lua_replace", "48 89 5C 24 ? 57 48 83 EC 20 89 D7 48 89 CB 81 FA EF D8 FF FF"},
		{"lua_checkstack", "48 89 5C 24 ? 57 48 83 EC 20 48 89 CB 81 FA 40 1F 00 00"},
		{"lua_xmove", "49 89 D3 49 89 CA 48 39 D1 74 ? 4D 63 C8"},
		{"lua_isnumber", "48 83 EC 38 E8 ? ? ? ? 83 78 ? 03 74 ? 48 8D 54 24 ? 48 89 C1 E8 ? ? ? ? 48 85 C0 75 ? 48 83 C4 38 C3 B8 01 00 00 00"},
		{"lua_isstring", "48 83 EC 28 E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 39 C8 74 ?"},
		{"lua_iscfunction", "48 83 EC 28 E8 ? ? ? ? 83 78 ? 06 75 ? 48 8B 00 80 78 ? 00 74 ? B8 01 00 00 00"},
		//{"lua_isuserdata", ""},//USING_CODE
		{"lua_type", "48 83 EC 28 E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 39 C8 75 ?"},
		//{"lua_typename", ""},//USING_CODE
		//{"lua_equal", ""},//WARNING: function NOT_FOUND
		{"lua_rawequal", "53 48 83 EC 20 45 89 C3"},
		{"lua_lessthan", "53 48 83 EC 20 45 89 C2 49 89 CB"},
		{"lua_tonumber", "48 83 EC 38 E8 ? ? ? ? 83 78 ? 03 74 ? 48 8D 54 24 ? 48 89 C1 E8 ? ? ? ? 48 85 C0 75 ? 0F 57 C0"},
		{"lua_tointeger", "48 83 EC 38 E8 ? ? ? ? 83 78 ? 03 74 ? 48 8D 54 24 ? 48 89 C1 E8 ? ? ? ? 48 85 C0 75 ? 48 83 C4 38 C3 F2 48 0F 2C 00"},
		{"lua_toboolean", "48 83 EC 28 E8 ? ? ? ? 8B 48 ? 85 C9"},
		{"lua_tolstring", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 89 C3 89 D6 48 89 CF E8 ? ? ? ? 49 89 C2 83 78 ? 04 74 ? 48 89 C2 48 89 F9 E8 ? ? ? ? 85 C0 75 ? 48 85 DB"},
		{"lua_objlen", "53 48 83 EC 20 49 89 CA E8 ? ? ? ?"},
		{"lua_tocfunction", "48 83 EC 28 E8 ? ? ? ? 83 78 ? 06 75 ? 48 8B 00 80 78 ? 00 74 ? 48 8B 40 ?"},
		{"lua_touserdata", "48 83 EC 28 E8 ? ? ? ? 8B 48 ? 83 F9 02"},
		{"lua_tothread", "48 83 EC 28 E8 ? ? ? ? 83 78 ? 08"},
		{"lua_topointer", "48 83 EC 28 41 89 D2 49 89 CB E8 ? ? ? ?"},
		{"lua_pushnil", "48 8B 41 ? C7 40 ? 00 00 00 00 48 83 41 ? 10"},
		{"lua_pushnumber", "48 8B 41 ? F2 0F 11 08"},
		{"lua_pushinteger", "48 8B 41 ? 0F 57 C0 F2 48 0F 2A C2"},
		{"lua_pushlstring", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 8B 49 ? 4C 89 C6"},
		{"lua_pushstring", "48 85 D2 75 ? 48 8B 41 ?"},
		{"lua_pushvfstring", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 8B 49 ? 4C 89 C7"},
		{"lua_pushfstring", "48 89 54 24 ? 4C 89 44 24 ? 4C 89 4C 24 ? 53 48 83 EC 20 4C 8B 41 ?"},
		{"lua_pushcclosure", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 8B 49 ? 49 63 F8"},
		{"lua_pushboolean", "4C 8B 41 ? 31 C0 85 D2"},
		{"lua_pushlightuserdata", "48 8B 41 ? 48 89 10 C7 40 ? 02 00 00 00"},
		{"lua_pushthread", "48 8B 41 ? 48 89 08 C7 40 ? 08 00 00 00"},
		{"lua_gettable", "48 83 EC 28 49 89 CA E8 ? ? ? ? 4D 8B 42 ? 49 83 C0 F0"},
		{"lua_getfield", "48 89 5C 24 ? 57 48 83 EC 30 4D 89 C2 48 89 CB E8 ? ? ? ? 48 89 C7 49 83 C8 FF 0F 1F 40 00 49 FF C0 43 80 3C ? 00 75 ? 4C 89 D2 48 89 D9 E8 ? ? ? ? 4C 8B 4B ? 4C 8D 44 24 ? 48 89 FA"},
		{"lua_rawget", "53 48 83 EC 20 48 89 CB E8 ? ? ? ? 48 8B 53 ? 48 8B 08"},
		{"lua_rawgeti", "53 48 83 EC 20 45 89 C2 48 89 CB E8 ? ? ? ? 48 8B 08"},
		{"lua_createtable", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 8B 49 ? 44 89 C6"},
		{"lua_newuserdata", "48 89 5C 24 ? 57 48 83 EC 20 4C 8B 41 ? 48 89 D7 48 89 CB 49 8B 40 ?"},
		{"lua_getmetatable", "48 83 EC 28 49 89 CA E8 ? ? ? ? 48 63 48 ?"},
		{"lua_getfenv", "48 83 EC 28 49 89 CA E8 ? ? ? ? 8B 48 ?"},
		{"lua_settable", "53 48 83 EC 20 48 89 CB E8 ? ? ? ? 4C 8B 43 ? 4D 8D 88 ? ? ? ?"},
		{"lua_setfield", "48 89 5C 24 ? 57 48 83 EC 30 4D 89 C2 48 89 CB E8 ? ? ? ? 48 89 C7 49 83 C8 FF 0F 1F 40 00 49 FF C0 43 80 3C ? 00 75 ? 4C 89 D2 48 89 D9 E8 ? ? ? ? 4C 8B 4B ? 4C 8D 44 24 ? 49 83 E9 10"},
		{"lua_rawset", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 89 CF E8 ? ? ? ? 48 8B 5F ?"},
		{"lua_rawseti", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 45 89 C2"},
		{"lua_setmetatable", "53 48 83 EC 20 48 89 CB E8 ? ? ? ? 48 8B 53 ? 83 BA ? ? ? ? 00"},
		{"lua_setfenv", "48 89 5C 24 ? 57 48 83 EC 20 48 89 CB BF 01 00 00 00"},
		{"lua_call", "48 89 5C 24 ? 57 48 83 EC 20 8D 42 ? 48 8B 51 ?"},
		{"lua_pcall", "48 89 5C 24 ? 57 48 83 EC 40 44 89 C7"},
		//{"lua_cpcall", ""},//WARNING: lua_cpcall: Instruction at 146c7dd11 is not adjacent to previous (expected 146c7dde0)
		{"lua_load", "48 89 5C 24 ? 57 48 83 EC 50 4D 85 C9"},
		{"lua_dump", "48 83 EC 38 48 8B 41 ? 49 89 D2"},
		//{"lua_yield", ""},//USING_CODE
		{"lua_resume", "48 89 5C 24 ? 57 48 83 EC 20 0F B6 41 ? 48 89 CF"},
		//{"lua_status", ""},//USING_CODE
		{"lua_gc", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B 59 ? 33 FF"},
		{"lua_error", "48 83 EC 28 E8 ? ? ? ? 31 C0 48 83 C4 28 C3"},//WARNING: Could not find unique Pattern, found 25 matches
		{"lua_next", "53 48 83 EC 20 48 89 CB E8 ? ? ? ? 4C 8B 43 ? 48 8B 10"},
		{"lua_concat", "48 89 5C 24 ? 57 48 83 EC 20 89 D3 48 89 CF 83 FA 02 7C ?"},
		//{"lua_getallocf", ""},//NO_USE
		//{"lua_setallocf", ""},//NO_USE
		//{"lua_setlevel", ""},//NO_USE
		{"lua_getstack", "4C 8B 49 ? 49 89 CB 85 D2"},
		{"lua_getinfo", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 89 CB 31 FF"},
		{"lua_getlocal", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 63 42 ?"},
		{"lua_setlocal", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 63 42 ?"},
		{"lua_getupvalue", "48 83 EC 28 4D 63 D0 49 89 CB"},
		{"lua_setupvalue", "48 83 EC 28 4D 63 D0 4C 8B D9"},
		{"lua_sethook", "44 89 C0 48 85 D2 74 ? 85 C0"},
		//{"lua_gethook", ""},//USING_CODE
		//{"lua_gethookmask", ""},//USING_CODE
		//{"lua_gethookcount", ""},//USING_CODE
		{"luaI_openlib", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 20 41 83 CC FF"},
		//{"luaL_register", ""},//USING_CODE
		{"luaL_getmetafield", "48 89 5C 24 ? 57 48 83 EC 20 4C 89 C7 48 89 CB E8 ? ? ? ? 85 C0 74 ?"},
		{"luaL_callmeta", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8D 82 ? ? ? ? 4C 89 C6"},
		{"luaL_typerror", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B FA 41 8B D0"},
		{"luaL_argerror", "53 56 57 48 81 EC C0 00 00 00 48 8B 05 ? ? ? ? 48 31 E0 48 89 84 24 ? ? ? ? 4C 89 C6"},
		{"luaL_checklstring", "48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 89 D5 48 89 CE E8 ? ? ? ? 48 89 C7"},
		{"luaL_optlstring", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 89 CF 4C 89 C3 89 D6"},
		{"luaL_checknumber", "48 89 5C 24 ? 57 48 83 EC 30 0F 29 74 24 ? 89 D3 48 89 CF E8 ? ? ? ? 0F 57 C9"},
		//{"luaL_optnumber", ""},//USING_CODE
		{"luaL_checkinteger", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 89 D7 48 89 CE E8 ? ? ? ? 48 89 C3 48 85 C0 75 ?"},
		{"luaL_optinteger", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 89 C6 89 D3 48 89 CF E8 ? ? ? ?"},
		{"luaL_checkstack", "48 89 5C 24 ? 57 48 83 EC 20 4C 89 C7 48 89 CB E8 ? ? ? ? 85 C0 75 ?"},
		{"luaL_checktype", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 44 89 C3 89 D7 48 89 CE E8 ? ? ? ?"},
		{"luaL_checkany", "48 89 5C 24 ? 57 48 83 EC 20 89 D3 48 89 CF E8 ? ? ? ? 83 F8 FF"},
		{"luaL_newmetatable", "48 89 5C 24 ? 57 48 83 EC 20 48 89 D7 49 89 D0"},
		{"luaL_checkudata", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 89 C5 89 D7"},
		{"luaL_where", "53 48 81 EC B0 00 00 00 48 8B 05 ? ? ? ? 48 31 E0 48 89 84 24 ? ? ? ? 4C 8D 44 24 ?"},
		{"luaL_error", "48 89 54 24 ? 4C 89 44 24 ? 4C 89 4C 24 ? 53 57 48 83 EC 28"},
		{"luaL_checkoption", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 4C 89 CF 4C 89 C3 89 D5"},
		//{"luaL_ref", ""},//USING_CODE
		//{"luaL_unref", ""},//USING_CODE
		{"luaL_loadfile", "40 53 56 48 81 EC 48 02 00 00"},
		{"luaL_loadbuffer", "48 83 EC 38 48 89 54 24 ? 4C 89 44 24 ?"},
		//{"luaL_loadstring", ""},//USING_CODE
		{"luaL_newstate", "53 48 83 EC 20 48 8D 0D ? ? ? ? 31 D2"},
		{"luaL_gsub", "4C 8B DC 55 49 8D AB ? ? ? ? 48 81 EC A0 02 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 89 6B ?"},
		{"luaL_findtable", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 45 89 CE"},
		//{"luaL_buffinit", ""},//USING_CODE
		{"luaL_prepbuffer", "57 48 83 EC 20 4C 8B 01 48 89 CF 49 29 C8 49 83 E8 18 74 ? 48 89 5C 24 ? 48 8D 59 ? 48 8B 49 ? 48 89 DA E8 ? ? ? ? FF 47 ? 48 89 F9"},
		{"luaL_addlstring", "4D 85 C0 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 74 24 ? 41 56"},
		//{"luaL_addstring", ""},//USING_CODE
		{"luaL_addvalue", "48 89 74 24 ? 57 48 83 EC 20 48 8B 71 ? 48 89 CF 4C 8D 44 24 ?"},
		{"luaL_pushresult", "57 48 83 EC 20 4C 8B 01 48 89 CF 49 29 C8 49 83 E8 18 74 ? 48 89 5C 24 ? 48 8D 59 ? 48 8B 49 ? 48 89 DA E8 ? ? ? ? FF 47 ? 48 89 1F"},
		{"luaopen_base", "53 48 83 EC 20 48 89 CB E8 ? ? ? ? 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 89 D9 E8 ? ? ? ? B8 02 00 00 00"},
		{"luaopen_table", "48 83 EC 28 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? E8 ? ? ? ? B8 01 00 00 00 48 83 C4 28 C3"},//WARNING: Could not find unique Pattern, found 3 matches
		{"luaopen_io", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8D 15 ? ? ? ?"},
		{"luaopen_os", "48 83 EC 28 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? E8 ? ? ? ? B8 01 00 00 00 48 83 C4 28 C3"},//WARNING: Could not find unique Pattern, found 3 matches
		{"luaopen_string", "53 48 83 EC 20 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 89 CB E8 ? ? ? ? 4C 8D 05 ? ? ? ? 83 CA FF"},
		{"luaopen_math", "53 48 83 EC 20 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 89 CB E8 ? ? ? ? 48 89 D9"},
		{"luaopen_debug", "48 83 EC 28 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? E8 ? ? ? ? B8 01 00 00 00 48 83 C4 28 C3"},//WARNING: Could not find unique Pattern, found 3 matches
		{"luaopen_package", "53 48 83 EC 20 48 8D 15 ? ? ? ? 48 89 74 24 ?"},
		{"luaL_openlibs", "48 89 5C 24 ? 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 89 CF 48 8D 1D ? ? ? ?"},
	};//map mgsvtpp_patterns
}//namespace IHHook
