#pragma once
//GENERATED: by AddressCSVToMacroHeader.lua
//using D:\GitHub\IHHook\mgsvtpp_adresses_1_0_15_3_jp.csv
// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason - TODO addt to getllocf,setallocf, actually give reason why not (dont want to mess with allocator function)
// USING_CODE - using the default lapi code implementation instead of hooking

namespace IHHook {
	std::map<std::string, int64_t> mgsvtpp_adresses_1_0_15_3_jp{
		{"_mainCRTStartup", 0x14c966b20},
		{"FoxMain", 0x142e5efe0},
		{"StrCode64", 0x14c96c490},
		{"GetFreeRoamLangId", 0x147a6b040},
		{"UpdateFOVLerp", 0x141116890},
		{"UnkSomePrintFunction", 0x142ee2a90},//Some info printing function that has been stubbed out
		{"l_StubbedOut", 0x141a92a30},
		{"UnkSomePlayerUpdateFunc", 0x1484ebbf0},
		{"UnkAnotherPlayerUpdateFuncButHuge", 0x1412cf230},
		{"nullsub_2", 0x141934f30},
		{"lua_newstate", 0x14c9a52c0},//tex could use default implementation, but may want to hook if we want to see what the engine is up to
		{"lua_close", 0x14c9a5100},
		{"lua_newthread", 0x14c989a70},
		{"lua_atpanic", 0x14c9855b0},
//		{"lua_gettop", USING_CODE},
		{"lua_settop", 0x14c990ed0},
		{"lua_pushvalue", 0x14c98e1d0},
		{"lua_remove", 0x14c98f0f0},
		{"lua_insert", 0x14c9888d0},
		{"lua_replace", 0x14c98f490},
		{"lua_checkstack", 0x14c985da0},
		{"lua_xmove", 0x14c993c00},
		{"lua_isnumber", 0x14c988960},
		{"lua_isstring", 0x14c988ca0},
		{"lua_iscfunction", 0x141a11770},
//		{"lua_isuserdata", USING_CODE},
		{"lua_type", 0x14c9935f0},
//		{"lua_typename", USING_CODE},
//		{"lua_equal", NOT_FOUND},//DEBUGNOW NOT_FOUND//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
		{"lua_rawequal", 0x14c98e690},
		{"lua_lessthan", 0x14c989590},
		{"lua_tonumber", 0x14c9924d0},
		{"lua_tointeger", 0x14c991b80},//MINIMAL_HOOK 
		{"lua_toboolean", 0x14c991120},
		{"lua_tolstring", 0x14c992060},//MINIMAL_HOOK 
		{"lua_objlen", 0x14c98a230},
		{"lua_tocfunction", 0x14c991460},
		{"lua_touserdata", 0x14c992e00},
		{"lua_tothread", 0x14c992bc0},
		{"lua_topointer", 0x14c992610},
		{"lua_pushnil", 0x14c98d570},//MINIMAL_HOOK 
		{"lua_pushnumber", 0x14c98d800},
		{"lua_pushinteger", 0x14c98c7c0},//MINIMAL_HOOK 
		{"lua_pushlstring", 0x14c98ccc0},
		{"lua_pushstring", 0x14c98dcb0},//MINIMAL_HOOK 
		{"lua_pushvfstring", 0x14c98e4a0},
		{"lua_pushfstring", 0x14c98c4b0},
		{"lua_pushcclosure", 0x14c98c080},
		{"lua_pushboolean", 0x14c98b310},//MINIMAL_HOOK 
		{"lua_pushlightuserdata", 0x14c98c9e0},
		{"lua_pushthread", 0x14c98df80},
		{"lua_gettable", 0x14c987b90},
		{"lua_getfield", 0x14c987300},//MINIMAL_HOOK 
		{"lua_rawget", 0x14c98e930},
		{"lua_rawgeti", 0x14c98ebc0},//via MACRO lua_getref
		{"lua_createtable", 0x14c986520},//MINIMAL_HOOK 
		{"lua_newuserdata", 0x14c989bf0},
		{"lua_getmetatable", 0x14c9878c0},
		{"lua_getfenv", 0x14c987110},
		{"lua_settable", 0x14c990bd0},
		{"lua_setfield", 0x14c990870},//MINIMAL_HOOK 
		{"lua_rawset", 0x14c98ed50},
		{"lua_rawseti", 0x14c98efe0},//MINIMAL_HOOK 
		{"lua_setmetatable", 0x14c990a80},
		{"lua_setfenv", 0x14c98f9f0},
		{"lua_call", 0x14c9859f0},
		{"lua_pcall", 0x14c98acb0},
		{"lua_cpcall", 0x1489e59c0},
		{"lua_load", 0x14c9898e0},
		{"lua_dump", 0x14caa27a0},
//		{"lua_yield", USING_CODE},
		{"lua_resume", 0x14c996a10},
//		{"lua_status", USING_CODE},//tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)
		{"lua_gc", 0x141a11340},
		{"lua_error", 0x14c986ea0},
		{"lua_next", 0x14c98a010},
		{"lua_concat", 0x14c986010},
//		{"lua_getallocf", NO_USE},//tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation
//		{"lua_setallocf", NO_USE},//tex don't really want to mess with allocator function anyway
//		{"lua_setlevel", NO_USE},//tex: labeled by lua as a hack to be removed in lua 5.2
		{"lua_getstack", 0x14ca99b40},
		{"lua_getinfo", 0x14ca993e0},
		{"lua_getlocal", 0x14ca99980},
		{"lua_setlocal", 0x14ca9a230},
		{"lua_getupvalue", 0x14c9884b0},
		{"lua_setupvalue", 0x141a12360},
		{"lua_sethook", 0x14ca99f50},
//		{"lua_gethook", USING_CODE},
//		{"lua_gethookmask", USING_CODE},
//		{"lua_gethookcount", USING_CODE},
		{"luaI_openlib", 0x141a18410},//MINIMAL_HOOK 
//		{"luaL_register", USING_CODE},
		{"luaL_getmetafield", 0x14c9a9020},
		{"luaL_callmeta", 0x14c9a6740},
		{"luaL_typerror", 0x141a185d0},
		{"luaL_argerror", 0x14c9a5ff0},
		{"luaL_checklstring", 0x14c9a72e0},
		{"luaL_optlstring", 0x14c9aac90},
		{"luaL_checknumber", 0x14c9a7490},
//		{"luaL_optnumber", USING_CODE},
		{"luaL_checkinteger", 0x14c9a6db0},
		{"luaL_optinteger", 0x14c9aa940},
		{"luaL_checkstack", 0x14c9a7ab0},
		{"luaL_checktype", 0x14c9a8030},
		{"luaL_checkany", 0x14c9a6b30},
		{"luaL_newmetatable", 0x14c9a9f50},
		{"luaL_checkudata", 0x14c9a8430},
		{"luaL_where", 0x14c9ac500},
		{"luaL_error", 0x14c9a8870},
		{"luaL_checkoption", 0x14c9a7600},
//		{"luaL_ref", USING_CODE},//tex: Unsure on this address, see lauxlib_Creathooks CREATE_FUNCPTR(luaL_ref) for more info
//		{"luaL_unref", USING_CODE},
		{"luaL_loadfile", 0x141a17ca0},
		{"luaL_loadbuffer", 0x14c9a98c0},
//		{"luaL_loadstring", USING_CODE},
		{"luaL_newstate", 0x14c9aa1fe},
		{"luaL_gsub", 0x141a17820},
		{"luaL_findtable", 0x14c9a8a20},
//		{"luaL_buffinit", USING_CODE},
		{"luaL_prepbuffer", 0x14c9ab0c0},
		{"luaL_addlstring", 0x141a16f80},
//		{"luaL_addstring", USING_CODE},
		{"luaL_addvalue", 0x14c9a5d20},
		{"luaL_pushresult", 0x14c9ab8b0},
		{"luaopen_base", 0x14caa9570},
		{"luaopen_table", 0x14caa9640},
		{"luaopen_io", 0x14caa9bb0},
		{"luaopen_os", 0x141a32280},
		{"luaopen_string", 0x14caaa490},
		{"luaopen_math", 0x14caaa7d0},
		{"luaopen_debug", 0x14caaab70},
		{"luaopen_package", 0x141a368c0},
		{"luaL_openlibs", 0x14c9a5860},
	};//map mgsvtpp_adresses_1_0_15_3_jp
}//namespace IHHook