#exportInfo - list with info on what to export to IHHook headers
#used by other scripts rather than doing anything itself

#Community NOTE: On Ghidra server please set a Plate Comment of "IHHook Export" on the function you want to export: 
#(on the actual function, not its thunk)
#Select the function name in ghidra and press semicolon (;), or right click > comments > plate comment.
#and also bookmark (select the start of function address in listing and ctrl D) with the category of IHHook. 
#This is just to make it clearer in case someone is reworking the function that it will impact the IHHook project.
#(its not required for any functionality of this script)

#NOTE: make sure the function signature (not to be confused with sig string/pattern) 
#for the function you want to export is correct in ghidra, or at least understandable for IHHook, no data types set as 'undefined'
#then right click the function in decompile window (or press P) and choose 'Commit Params/Return'

#GOTCHA: ghidra function signature doesnt have const keyword, so you have to use constParams as a workaround
#all char * are assumed const char *, use "constCharPtr":False to leave it as char * 

#By default all exported functions are set up as function pointers under their original names
#usingHook:True means you are using a <name>Hook function to actually intercept the function
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
	
	{"name":"GetStrCodeWithLength","usingHook":True,},
	{"name":"GetStrCode32","usingHook":True,},
	{"name":"PathCode64Ext","usingHook":True, 
		"note":"tex TODO need to verify naming and purpose. technically this is PathFileNameExt64, but given that PathCode - without ext is likely less used than PathCode would have been a better name for PathFileNameExt64"},
	{"name":"FNVHash32","usingHook":True,},
	#{"name":"FNVHash64",},
	{"name":"GetFreeRoamLangId", "usingHook":True,},
	{"name":"UpdateFOVLerp", "usingHook":True, "enableDetourOnInit":False, 
		"note":"tex: TODO: verify the return AL>RAX"},
	{"name":"UnkPrintFuncStubbedOut", "hasVarArgs":True, "usingHook":True, 
		"note":"tex: Some info printing function that has been stubbed out"},
	{"name":"l_StubbedOut", "exportFunc":False, "note":"tex: another retail stubb out to wrangle",},
	#{"name":"UnkSomePlayerUpdateFunc", "usingHook":True, "note":"exploration"},
	#{"name":"UnkAnotherPlayerUpdateFuncButHuge", "usingHook":True, "note":"exploration"},
	{"name":"nullsub_2", "exportFunc":False, "note":"tex: another retail stubb out to wrangle",},
	{"name":"LoadFile", "usingHook":True,},
	{"name":"LoadFileSub", "usingHook":True,},
	{"name":"Path_Copy", "usingHook":True,},
	{"name":"GetEmptyPath", "usingHook":True,},
	{"name":"LoadPlayerPartsFpk", "usingHook":True,},
	{"name":"LoadPlayerPartsParts", "usingHook":True,},
	{"name":"LoadPlayerCamoFpk", "usingHook":True,},
	{"name":"LoadPlayerCamoFv2", "usingHook":True,},
	{"name":"LoadPlayerFacialMotionFpk", "usingHook":True,},
	{"name":"LoadPlayerFacialMotionMtar", "usingHook":True,},
	{"name":"LoadPlayerBionicArmFpk", "usingHook":True,},
	{"name":"LoadPlayerBionicArmFv2", "usingHook":True,},
	{"name":"CheckPlayerPartsIfShouldApplySkinToneFv2", "usingHook":True,},#//GOTCHA: since its only called in LoadPlayerPartsSkinToneFv2, so this isnt a hook, just calling this extended version from LoadPlayerPartsSkinToneFv2Hook
	{"name":"LoadPlayerPartsSkinToneFv2", "usingHook":True,},
	{"name":"IsHeadNeededForPartsType", "usingHook":True,},
	{"name":"IsHeadNeededForPartsTypeAndAvatar", "usingHook":True,},
	{"name":"LoadPlayerSnakeFaceFpk", "usingHook":True,},
	{"name":"LoadPlayerSnakeFaceFv2", "usingHook":True,},
	{"name":"LoadAvatarOgreHornFpk", "usingHook":True,},
	{"name":"LoadAvatarOgreHornFv2", "usingHook":True,},
	{"name":"LoadBuddyMainFile", "usingHook":True,},
	#{"name":"LoadBuddySubFileFpk", "usingHook":True, "note":"exploration"},
	{"name":"LoadBuddyQuietWeaponFpk", "usingHook":True,},
	{"name":"LoadBuddyDogCommonFPK", "usingHook":True,},
	{"name":"LoadBuddyHorseCommonFPK", "usingHook":True,},
	#{"name":"LoadBuddyWalkerGearCommonFPK", "usingHook":True,},
	{"name":"LoadBuddyWalkerGearArmFpk", "usingHook":True,},
	{"name":"LoadBuddyWalkerGearHeadFpk", "usingHook":True,},
	{"name":"LoadBuddyWalkerGearWeaponFpk", "usingHook":True,},
	{"name":"LoadDefaultFpksFunc", "usingHook":True,},
	{"name":"PreparePlayerVehicleInSortie", "usingHook":True,},
	{"name":"PreparePlayerVehicleInGame", "usingHook":True,},
	{"name":"LoadDefaultFpkPtrFunc", "usingHook":True,},
	{"name":"LoadAllVehicleCamoFpks", "usingHook":True,},
	{"name":"BuddyCommandGetNameLangId", "usingHook":True,},
	{"name":"BuddyCommandGetDescriptionLangId", "usingHook":True,},
	#{"name":"CreateInPlace", "usingHook":True,},##TODO: 0x142e8a5d0 uhh so this was actually std::string?   
	
	
	#tex logging some stuff, probably not for release build
	{"name":"foxlua::NewModule", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::NewSubModule", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddCFuncToModule", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddCFuncToModule2", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddCFuncToModule3", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddEnumToModule", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddEnumToModule2", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddEnumToModule3", "usingHook":True, "debugOnly":True,},
	{"name":"foxlua::AddEnumToModule4", "usingHook":True, "debugOnly":True,},
	{"name":"RegisterVar", "usingHook":True, "debugOnly":True,},
	{"name":"RegisterVar_01", "usingHook":True, "debugOnly":True,},
	{"name":"RegisterVar_02", "usingHook":True, "debugOnly":True,},
	{"name":"RegisterVar_03", "usingHook":True, "debugOnly":True,},
	{"name":"RegisterVarArray", "usingHook":True, "debugOnly":True,},
	{"name":"DeclareEntityClass", "usingHook":True, "debugOnly":True,},
	#######################<
	#lua> tex WORKAROUND: since lua api usually isnt in a namespace (since its c), 
	#but am in ghidra for sanity, mgsvtpp_func_typedefs pushes using namespace lua
	{"name":"lua::lua_newstate", "usingHook":True, 
		"note":"tex could use default implementation, but may want to hook if we want to see what the engine is up to"},
	{"name":"lua::lua_close",},
	{"name":"lua::lua_newthread", "usingHook":True,},

	{"name":"lua::lua_atpanic", "usingHook":True,},

	{"name":"lua::lua_gettop", "noAddress":"USING_CODE",},
	{"name":"lua::lua_settop",},
	{"name":"lua::lua_pushvalue",},
	{"name":"lua::lua_remove",},
	{"name":"lua::lua_insert",},
	{"name":"lua::lua_replace",},
	{"name":"lua::lua_checkstack",},
	{"name":"lua::lua_xmove",},

	{"name":"lua::lua_isnumber",},
	{"name":"lua::lua_isstring",},
	{"name":"lua::lua_iscfunction",},
	{"name":"lua::lua_isuserdata", "noAddress":"USING_CODE", 
		"note":"tex: No calls in lua distro, so may be hard to find, or have been culled by compilation",},
	{"name":"lua::lua_type",},
	{"name":"lua::lua_typename", "noAddress":"USING_CODE",},

	{"name":"lua::lua_equal",},
	{"name":"lua::lua_rawequal",},
	{"name":"lua::lua_lessthan",},
	{"name":"lua::lua_tonumber",},
	{"name":"lua::lua_tointeger",},
	{"name":"lua::lua_toboolean",},
	{"name":"lua::lua_tolstring",},
	{"name":"lua::lua_objlen",},
	{"name":"lua::lua_tocfunction",},
	{"name":"lua::lua_touserdata",},
	{"name":"lua::lua_tothread",},
	{"name":"lua::lua_topointer",},

	{"name":"lua::lua_pushnil",},
	{"name":"lua::lua_pushnumber",},
	{"name":"lua::lua_pushinteger",},
	{"name":"lua::lua_pushlstring",},
	{"name":"lua::lua_pushstring",},
	{"name":"lua::lua_pushvfstring",},
	{"name":"lua::lua_pushfstring",},
	{"name":"lua::lua_pushcclosure",},
	{"name":"lua::lua_pushboolean",},
	{"name":"lua::lua_pushlightuserdata",},
	{"name":"lua::lua_pushthread",},

	{"name":"lua::lua_gettable",},
	{"name":"lua::lua_getfield",},
	{"name":"lua::lua_rawget",},
	{"name":"lua::lua_rawgeti", "note":"via MACRO lua_getref",},
	{"name":"lua::lua_createtable",},
	{"name":"lua::lua_newuserdata",},
	{"name":"lua::lua_getmetatable",},
	{"name":"lua::lua_getfenv",},

	{"name":"lua::lua_settable",},
	{"name":"lua::lua_setfield",},
	{"name":"lua::lua_rawset",},
	{"name":"lua::lua_rawseti",},
	{"name":"lua::lua_setmetatable",},
	{"name":"lua::lua_setfenv",},

	{"name":"lua::lua_call",},
	{"name":"lua::lua_pcall", "usingHook":True,},
	{"name":"lua::lua_cpcall", "usingHook":True,},
	{"name":"lua::lua_load", "usingHook":True,},

	{"name":"lua::lua_dump",},

	{"name":"lua::lua_yield", "noAddress":"USING_CODE", 
		"note":"tex: DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)",},
	{"name":"lua::lua_resume",},
	{"name":"lua::lua_status", "noAddress":"USING_CODE", 
		"note":"tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)",},

	{"name":"lua::lua_gc",},
	{"name":"lua::lua_error", "usingHook":True,},

	{"name":"lua::lua_next",},
	{"name":"lua::lua_concat",},

	{"name":"lua::lua_getallocf", "noAddress":"NO_USE", 
		"note":"tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation" },
	{"name":"lua::lua_setallocf", "noAddress":"NO_USE", 
		"note":"tex don't really want to mess with allocator function anyway"},


	{"name":"lua::lua_setlevel", "noAddress":"NO_USE", "note":"tex: labeled by lua as a hack to be removed in lua 5.2",},

	{"name":"lua::lua_getstack",},
	{"name":"lua::lua_getinfo",},
	{"name":"lua::lua_getlocal",},
	{"name":"lua::lua_setlocal",},
	{"name":"lua::lua_getupvalue",},
	{"name":"lua::lua_setupvalue",},

	{"name":"lua::lua_sethook",},
	{"name":"lua::lua_gethook", "noAddress":"USING_CODE",},
	{"name":"lua::lua_gethookmask", "noAddress":"USING_CODE",},
	{"name":"lua::lua_gethookcount", "noAddress":"USING_CODE",},
	#lua<

	#lauxlib.h>
	{"name":"lua::luaI_openlib", "constParams": ["l"]},
	{"name":"lua::luaL_register", "noAddress":"USING_CODE",},
	{"name":"lua::luaL_getmetafield",},
	{"name":"lua::luaL_callmeta",},
	{"name":"lua::luaL_typerror",},
	{"name":"lua::luaL_argerror",},
	{"name":"lua::luaL_checklstring",},
	{"name":"lua::luaL_optlstring",},
	{"name":"lua::luaL_checknumber",},
	{"name":"lua::luaL_optnumber", "noAddress":"USING_CODE", "note":"tex: Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes",},

	{"name":"lua::luaL_checkinteger",},
	{"name":"lua::luaL_optinteger",},

	{"name":"lua::luaL_checkstack",},
	{"name":"lua::luaL_checktype",},
	{"name":"lua::luaL_checkany",},

	{"name":"lua::luaL_newmetatable",},
	{"name":"lua::luaL_checkudata",},

	{"name":"lua::luaL_where",},
	{"name":"lua::luaL_error",},

	{"name":"lua::luaL_checkoption",},

	{"name":"lua::luaL_ref", "noAddress":"USING_CODE", 
		"note":"tex: Unsure on this address. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param",},
	{"name":"lua::luaL_unref", "noAddress":"USING_CODE",},

	{"name":"lua::luaL_loadfile",},
	{"name":"lua::luaL_loadbuffer", "usingHook":True,},
	{"name":"lua::luaL_loadstring", "noAddress":"USING_CODE",},

	{"name":"lua::luaL_newstate",},

	{"name":"lua::luaL_gsub",},

	{"name":"lua::luaL_findtable",},
	#...
	{"name":"lua::luaL_buffinit", "noAddress":"USING_CODE",},
	{"name":"lua::luaL_prepbuffer",},
	{"name":"lua::luaL_addlstring",},
	{"name":"lua::luaL_addstring", "noAddress":"USING_CODE", 
		"note":"tex: Only call is in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring",},
	{"name":"lua::luaL_addvalue",},
	{"name":"lua::luaL_pushresult",},
	#lauxlib.h<

	#luaLib.h>
	{"name":"lua::luaopen_base",},
	{"name":"lua::luaopen_table",},
	{"name":"lua::luaopen_io",},
	{"name":"lua::luaopen_os",},
	{"name":"lua::luaopen_string",},
	{"name":"lua::luaopen_math",},
	{"name":"lua::luaopen_debug",},
	{"name":"lua::luaopen_package",},
	{"name":"lua::luaL_openlibs","usingHook":True,},
	#luaLib.h<
]#exportInfo
