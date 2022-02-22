#exportInfo - list with info on what to export to IHHook headers
#used by other scripts rather than doing anything itself

#GOTCHA: assumes that function names in ghdira for the exe are unique (ignoring thunks)

#NOTE: make sure the function signature (not to be confused with sig string/pattern) 
#for the function you want to export is correct in ghidra, or at least understandable for IHHook, no data types set as 'undefined'
#then right click the function in decompile window (or press P) and choose 'Commit Params/Return'

#GOTCHA: ghidra function signature doesnt have const keyword, so you have to use constParams as a workaround
#all char * are assumed const char *, use "constCharPtr":False to leave it as char * 

#By default all exported functions are set up as function pointers under their original names
#usingDetour:True means you are using a <name>Hook function to actually intercept the function
#enableDetourOnInit:False means detour will be enabled from the start TODO: not yet implemented

#noAddress for stuff that's not actually exported for whatever reason, but will still write it out as commented out entries
#USING_CODE is where I use actual lua implementation instead of hooking

#exportFunc: False to not actually export the ghidra function signature / typdef, 
#for manually defining it on the IHHook side and stuff like the retail stubbed out/empty functions that are a mess because they collide a bunch of parameter types/returns.

#notes are appended as comments in mgsv_tpp_addresses_<version>_en.h 
#for want of a better place, entries there are short enough to tack on comment at end and be discoverable at a glance

#TODO add NO_USE to getllocf,setallocf, actually give reason why not (dont want to mess with allocator function)
#todo namespaces - not actual, just to split into different files
#fox, lua
exportInfo=[
	#{"name":"_mainCRTStartup","note: since its the entry point no point trying hooking since it's already done"},
	#{"name":"FoxMain","note: since its the entry point no point trying hooking since it's already done"},
	
	{"name":"StrCode64",},
	{"name":"PathCode64","usingDetour":True, 
		"note":"tex TODO need to verify naming and purpose. technically this is PathFileNameExt64, but given that PathCode - without ext is likely less used than PathCode would have been a better name for PathFileNameExt64"},
	{"name":"FNVHash32","usingDetour":True,},
	#{"name":"FNVHash64",},
	{"name":"GetFreeRoamLangId", "usingDetour":True,},
	{"name":"UpdateFOVLerp", "usingDetour":True, "enableDetourOnInit":False, 
		"note":"tex: TODO: verify the return AL>RAX"},
	{"name":"UnkPrintFuncStubbedOut", "hasVarArgs":True, "usingDetour":True, 
		"note":"tex: Some info printing function that has been stubbed out"},
	{"name":"l_StubbedOut", "exportFunc":False, "note":"tex: another retail stubb out to wrangle",},
	#{"name":"UnkSomePlayerUpdateFunc", "usingDetour":True, "note":"exploration"},
	#{"name":"UnkAnotherPlayerUpdateFuncButHuge", "usingDetour":True, "note":"exploration"},
	{"name":"nullsub_2", "exportFunc":False, "note":"tex: another retail stubb out to wrangle",},
	{"name":"LoadFileSub", "usingDetour":True,},
	{"name":"LoadFile", "usingDetour":True,},
	{"name":"LoadFile_01", "usingDetour":True,},
	{"name":"LoadFile_02", "usingDetour":True,},
	{"name":"LoadFile_03", "usingDetour":True,},
	{"name":"LoadFile_05", "usingDetour":True,},
	{"name":"LoadPlayerPartsFpk", "usingDetour":True,},
	{"name":"LoadPlayerPartsParts", "usingDetour":True,},
	{"name":"LoadPlayerCamoFpk", "usingDetour":True,},
	{"name":"LoadPlayerCamoFv2", "usingDetour":True,},
	{"name":"LoadPlayerFacialMotionFpk", "usingDetour":True,},
	{"name":"LoadPlayerFacialMotionMtar", "usingDetour":True,},
	{"name":"LoadPlayerBionicArmFpk", "usingDetour":True,},
	{"name":"LoadPlayerBionicArmFv2", "usingDetour":True,},
	{"name":"CheckPlayerPartsIfShouldApplySkinToneFv2", "usingDetour":True,},#//GOTCHA: since its only called in LoadPlayerPartsSkinToneFv2, so this isnt a hook, just calling this extended version from LoadPlayerPartsSkinToneFv2Hook
	{"name":"LoadPlayerPartsSkinToneFv2", "usingDetour":True,},
	{"name":"IsHeadNeededForPartsType", "usingDetour":True,},
	{"name":"IsHeadNeededForPartsTypeAndAvatar", "usingDetour":True,},
	{"name":"LoadPlayerSnakeFaceFpk", "usingDetour":True,},
	{"name":"LoadPlayerSnakeFaceFv2", "usingDetour":True,},
	{"name":"LoadAvatarOgreHornFpk", "usingDetour":True,},
	{"name":"LoadAvatarOgreHornFv2", "usingDetour":True,},
	{"name":"LoadBuddyMainFile", "usingDetour":True,},
	#{"name":"LoadBuddySubFileFpk", "usingDetour":True, "note":"exploration"},
	{"name":"LoadBuddyQuietWeaponFpk", "usingDetour":True,},
	{"name":"LoadBuddyWalkerGearArmFpk", "usingDetour":True,},
	{"name":"LoadBuddyWalkerGearHeadFpk", "usingDetour":True,},
	{"name":"LoadBuddyWalkerGearWeaponFpk", "usingDetour":True,},
	{"name":"LoadDefaultFpksFunc", "usingDetour":True,},
	{"name":"PreparePlayerVehicleInSortie", "usingDetour":True,},
	{"name":"PreparePlayerVehicleInGame", "usingDetour":True,},
	{"name":"LoadDefaultFpkPtrFunc", "usingDetour":True,},
	{"name":"LoadAllVehicleCamoFpks", "usingDetour":True,},
	{"name":"CreateInPlace", "usingDetour":True,},  
	#<
	#lua>
	{"name":"lua_newstate", "usingDetour":True, 
		"note":"tex could use default implementation, but may want to hook if we want to see what the engine is up to"},
	{"name":"lua_close",},
	{"name":"lua_newthread", "usingDetour":True,},

	{"name":"lua_atpanic", "usingDetour":True,},

	{"name":"lua_gettop", "noAddress":"USING_CODE",},
	{"name":"lua_settop",},
	{"name":"lua_pushvalue",},
	{"name":"lua_remove",},
	{"name":"lua_insert",},
	{"name":"lua_replace",},
	{"name":"lua_checkstack",},
	{"name":"lua_xmove",},

	{"name":"lua_isnumber",},
	{"name":"lua_isstring",},
	{"name":"lua_iscfunction",},
	{"name":"lua_isuserdata", "noAddress":"USING_CODE", 
		"note":"tex: No calls in lua distro, so may be hard to find, or have been culled by compilation",},
	{"name":"lua_type",},
	{"name":"lua_typename", "noAddress":"USING_CODE",},

	{"name":"lua_equal", 
		"note":"tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation" },
	{"name":"lua_rawequal",},
	{"name":"lua_lessthan",},
	{"name":"lua_tonumber",},
	{"name":"lua_tointeger",},
	{"name":"lua_toboolean",},
	{"name":"lua_tolstring",},
	{"name":"lua_objlen",},
	{"name":"lua_tocfunction",},
	{"name":"lua_touserdata",},
	{"name":"lua_tothread",},
	{"name":"lua_topointer",},

	{"name":"lua_pushnil",},
	{"name":"lua_pushnumber",},
	{"name":"lua_pushinteger",},
	{"name":"lua_pushlstring",},
	{"name":"lua_pushstring",},
	{"name":"lua_pushvfstring",},
	{"name":"lua_pushfstring",},
	{"name":"lua_pushcclosure",},
	{"name":"lua_pushboolean",},
	{"name":"lua_pushlightuserdata",},
	{"name":"lua_pushthread",},

	{"name":"lua_gettable",},
	{"name":"lua_getfield",},
	{"name":"lua_rawget",},
	{"name":"lua_rawgeti", "note":"via MACRO lua_getref",},
	{"name":"lua_createtable",},
	{"name":"lua_newuserdata",},
	{"name":"lua_getmetatable",},
	{"name":"lua_getfenv",},

	{"name":"lua_settable",},
	{"name":"lua_setfield",},
	{"name":"lua_rawset",},
	{"name":"lua_rawseti",},
	{"name":"lua_setmetatable",},
	{"name":"lua_setfenv",},

	{"name":"lua_call",},
	{"name":"lua_pcall", "usingDetour":True,},
	{"name":"lua_cpcall", "usingDetour":True,},
	{"name":"lua_load", "usingDetour":True,},

	{"name":"lua_dump",},

	{"name":"lua_yield", "noAddress":"USING_CODE", 
		"note":"tex: DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)",},
	{"name":"lua_resume",},
	{"name":"lua_status", "noAddress":"USING_CODE", 
		"note":"tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)",},

	{"name":"lua_gc",},
	{"name":"lua_error", "usingDetour":True,},

	{"name":"lua_next",},
	{"name":"lua_concat",},

	{"name":"lua_getallocf", "noAddress":"NO_USE", 
		"note":"tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation" },
	{"name":"lua_setallocf", "noAddress":"NO_USE", 
		"note":"tex don't really want to mess with allocator function anyway"},


	{"name":"lua_setlevel", "noAddress":"NO_USE", "note":"tex: labeled by lua as a hack to be removed in lua 5.2",},

	{"name":"lua_getstack",},
	{"name":"lua_getinfo",},
	{"name":"lua_getlocal",},
	{"name":"lua_setlocal",},
	{"name":"lua_getupvalue",},
	{"name":"lua_setupvalue",},

	{"name":"lua_sethook",},
	{"name":"lua_gethook", "noAddress":"USING_CODE",},
	{"name":"lua_gethookmask", "noAddress":"USING_CODE",},
	{"name":"lua_gethookcount", "noAddress":"USING_CODE",},
	#lua<

	#lauxlib.h>
	{"name":"luaI_openlib", "constParams": ["l"]},
	{"name":"luaL_register", "noAddress":"USING_CODE",},
	{"name":"luaL_getmetafield",},
	{"name":"luaL_callmeta",},
	{"name":"luaL_typerror",},
	{"name":"luaL_argerror",},
	{"name":"luaL_checklstring",},
	{"name":"luaL_optlstring",},
	{"name":"luaL_checknumber",},
	{"name":"luaL_optnumber", "noAddress":"USING_CODE", "note":"tex: Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes",},

	{"name":"luaL_checkinteger",},
	{"name":"luaL_optinteger",},

	{"name":"luaL_checkstack",},
	{"name":"luaL_checktype",},
	{"name":"luaL_checkany",},

	{"name":"luaL_newmetatable",},
	{"name":"luaL_checkudata",},

	{"name":"luaL_where",},
	{"name":"luaL_error",},

	{"name":"luaL_checkoption",},

	{"name":"luaL_ref", "noAddress":"USING_CODE", 
		"note":"tex: Unsure on this address. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param",},
	{"name":"luaL_unref", "noAddress":"USING_CODE",},

	{"name":"luaL_loadfile",},
	{"name":"luaL_loadbuffer", "usingDetour":True,},
	{"name":"luaL_loadstring", "noAddress":"USING_CODE",},

	{"name":"luaL_newstate",},

	{"name":"luaL_gsub",},

	{"name":"luaL_findtable",},
	#...
	{"name":"luaL_buffinit", "noAddress":"USING_CODE",},
	{"name":"luaL_prepbuffer",},
	{"name":"luaL_addlstring",},
	{"name":"luaL_addstring", "noAddress":"USING_CODE", 
		"note":"tex: Only call is in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring",},
	{"name":"luaL_addvalue",},
	{"name":"luaL_pushresult",},
	#lauxlib.h<

	#luaLib.h>
	{"name":"luaopen_base",},
	{"name":"luaopen_table",},
	{"name":"luaopen_io",},
	{"name":"luaopen_os",},
	{"name":"luaopen_string",},
	{"name":"luaopen_math",},
	{"name":"luaopen_debug",},
	{"name":"luaopen_package",},
	{"name":"luaL_openlibs","usingDetour":True,},
	#luaLib.h<
]#exportInfo
