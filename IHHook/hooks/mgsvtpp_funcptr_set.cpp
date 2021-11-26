//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteFuncPtrSetFile
//function for setting function pointers of exported functions.
//addresses in addressset should be rebased or found by sig scan before this is called
// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking

#include "mgsvtpp_func_typedefs.h"

extern std::map<std::string, int64_t> addressSet;

namespace IHHook {
	void SetFuncPtrs() {
		StrCode64 = (StrCode64Func*)addressSet["StrCode64"];
		PathCode64 = (PathCode64Func*)addressSet["PathCode64"];
		FNVHash32 = (FNVHash32Func*)addressSet["FNVHash32"];
		GetFreeRoamLangId = (GetFreeRoamLangIdFunc*)addressSet["GetFreeRoamLangId"];
		UpdateFOVLerp = (UpdateFOVLerpFunc*)addressSet["UpdateFOVLerp"];
		UnkPrintFuncStubbedOut = (UnkPrintFuncStubbedOutFunc*)addressSet["UnkPrintFuncStubbedOut"];
		l_StubbedOut = (l_StubbedOutFunc*)addressSet["l_StubbedOut"];
		nullsub_2 = (nullsub_2Func*)addressSet["nullsub_2"];
		LoadFileSub = (LoadFileSubFunc*)addressSet["LoadFileSub"];
		LoadFile = (LoadFileFunc*)addressSet["LoadFile"];
		LoadPlayerPartsFpk = (LoadPlayerPartsFpkFunc*)addressSet["LoadPlayerPartsFpk"];
		LoadPlayerPartsParts = (LoadPlayerPartsPartsFunc*)addressSet["LoadPlayerPartsParts"];
		LoadPlayerCamoFpk = (LoadPlayerCamoFpkFunc*)addressSet["LoadPlayerCamoFpk"];
		LoadPlayerCamoFv2 = (LoadPlayerCamoFv2Func*)addressSet["LoadPlayerCamoFv2"];
		LoadPlayerFacialMotionFpk = (LoadPlayerFacialMotionFpkFunc*)addressSet["LoadPlayerFacialMotionFpk"];
		LoadPlayerFacialMotionMtar = (LoadPlayerFacialMotionMtarFunc*)addressSet["LoadPlayerFacialMotionMtar"];
		LoadPlayerBionicArmFpk = (LoadPlayerBionicArmFpkFunc*)addressSet["LoadPlayerBionicArmFpk"];
		LoadPlayerBionicArmFv2 = (LoadPlayerBionicArmFv2Func*)addressSet["LoadPlayerBionicArmFv2"];
		CheckPlayerPartsIfShouldApplySkinToneFv2 = (CheckPlayerPartsIfShouldApplySkinToneFv2Func*)addressSet["CheckPlayerPartsIfShouldApplySkinToneFv2"];
		LoadPlayerPartsSkinToneFv2 = (LoadPlayerPartsSkinToneFv2Func*)addressSet["LoadPlayerPartsSkinToneFv2"];
		IsHeadNeededForPartsType = (IsHeadNeededForPartsTypeFunc*)addressSet["IsHeadNeededForPartsType"];
		IsHeadNeededForPartsTypeAndAvatar = (IsHeadNeededForPartsTypeAndAvatarFunc*)addressSet["IsHeadNeededForPartsTypeAndAvatar"];
		LoadPlayerSnakeFaceFpk = (LoadPlayerSnakeFaceFpkFunc*)addressSet["LoadPlayerSnakeFaceFpk"];
		LoadPlayerSnakeFaceFv2 = (LoadPlayerSnakeFaceFv2Func*)addressSet["LoadPlayerSnakeFaceFv2"];
		LoadAvatarOgreHornFpk = (LoadAvatarOgreHornFpkFunc*)addressSet["LoadAvatarOgreHornFpk"];
		LoadAvatarOgreHornFv2 = (LoadAvatarOgreHornFv2Func*)addressSet["LoadAvatarOgreHornFv2"];
		LoadBuddyMainFile = (LoadBuddyMainFileFunc*)addressSet["LoadBuddyMainFile"]; //ZIP: For buddies
		lua_newstate = (lua_newstateFunc*)addressSet["lua_newstate"];
		lua_close = (lua_closeFunc*)addressSet["lua_close"];
		lua_newthread = (lua_newthreadFunc*)addressSet["lua_newthread"];
		lua_atpanic = (lua_atpanicFunc*)addressSet["lua_atpanic"];
		//lua_gettop = (lua_gettopFunc*)addressSet["lua_gettop"];//USING_CODE
		lua_settop = (lua_settopFunc*)addressSet["lua_settop"];
		lua_pushvalue = (lua_pushvalueFunc*)addressSet["lua_pushvalue"];
		lua_remove = (lua_removeFunc*)addressSet["lua_remove"];
		lua_insert = (lua_insertFunc*)addressSet["lua_insert"];
		lua_replace = (lua_replaceFunc*)addressSet["lua_replace"];
		lua_checkstack = (lua_checkstackFunc*)addressSet["lua_checkstack"];
		lua_xmove = (lua_xmoveFunc*)addressSet["lua_xmove"];
		lua_isnumber = (lua_isnumberFunc*)addressSet["lua_isnumber"];
		lua_isstring = (lua_isstringFunc*)addressSet["lua_isstring"];
		lua_iscfunction = (lua_iscfunctionFunc*)addressSet["lua_iscfunction"];
		//lua_isuserdata = (lua_isuserdataFunc*)addressSet["lua_isuserdata"];//USING_CODE
		lua_type = (lua_typeFunc*)addressSet["lua_type"];
		//lua_typename = (lua_typenameFunc*)addressSet["lua_typename"];//USING_CODE
		//lua_equal = (lua_equalFunc*)addressSet["lua_equal"];//NOT_FOUND
		lua_rawequal = (lua_rawequalFunc*)addressSet["lua_rawequal"];
		lua_lessthan = (lua_lessthanFunc*)addressSet["lua_lessthan"];
		lua_tonumber = (lua_tonumberFunc*)addressSet["lua_tonumber"];
		lua_tointeger = (lua_tointegerFunc*)addressSet["lua_tointeger"];
		lua_toboolean = (lua_tobooleanFunc*)addressSet["lua_toboolean"];
		lua_tolstring = (lua_tolstringFunc*)addressSet["lua_tolstring"];
		lua_objlen = (lua_objlenFunc*)addressSet["lua_objlen"];
		lua_tocfunction = (lua_tocfunctionFunc*)addressSet["lua_tocfunction"];
		lua_touserdata = (lua_touserdataFunc*)addressSet["lua_touserdata"];
		lua_tothread = (lua_tothreadFunc*)addressSet["lua_tothread"];
		lua_topointer = (lua_topointerFunc*)addressSet["lua_topointer"];
		lua_pushnil = (lua_pushnilFunc*)addressSet["lua_pushnil"];
		lua_pushnumber = (lua_pushnumberFunc*)addressSet["lua_pushnumber"];
		lua_pushinteger = (lua_pushintegerFunc*)addressSet["lua_pushinteger"];
		lua_pushlstring = (lua_pushlstringFunc*)addressSet["lua_pushlstring"];
		lua_pushstring = (lua_pushstringFunc*)addressSet["lua_pushstring"];
		lua_pushvfstring = (lua_pushvfstringFunc*)addressSet["lua_pushvfstring"];
		lua_pushfstring = (lua_pushfstringFunc*)addressSet["lua_pushfstring"];
		lua_pushcclosure = (lua_pushcclosureFunc*)addressSet["lua_pushcclosure"];
		lua_pushboolean = (lua_pushbooleanFunc*)addressSet["lua_pushboolean"];
		lua_pushlightuserdata = (lua_pushlightuserdataFunc*)addressSet["lua_pushlightuserdata"];
		lua_pushthread = (lua_pushthreadFunc*)addressSet["lua_pushthread"];
		lua_gettable = (lua_gettableFunc*)addressSet["lua_gettable"];
		lua_getfield = (lua_getfieldFunc*)addressSet["lua_getfield"];
		lua_rawget = (lua_rawgetFunc*)addressSet["lua_rawget"];
		lua_rawgeti = (lua_rawgetiFunc*)addressSet["lua_rawgeti"];
		lua_createtable = (lua_createtableFunc*)addressSet["lua_createtable"];
		lua_newuserdata = (lua_newuserdataFunc*)addressSet["lua_newuserdata"];
		lua_getmetatable = (lua_getmetatableFunc*)addressSet["lua_getmetatable"];
		lua_getfenv = (lua_getfenvFunc*)addressSet["lua_getfenv"];
		lua_settable = (lua_settableFunc*)addressSet["lua_settable"];
		lua_setfield = (lua_setfieldFunc*)addressSet["lua_setfield"];
		lua_rawset = (lua_rawsetFunc*)addressSet["lua_rawset"];
		lua_rawseti = (lua_rawsetiFunc*)addressSet["lua_rawseti"];
		lua_setmetatable = (lua_setmetatableFunc*)addressSet["lua_setmetatable"];
		lua_setfenv = (lua_setfenvFunc*)addressSet["lua_setfenv"];
		lua_call = (lua_callFunc*)addressSet["lua_call"];
		lua_pcall = (lua_pcallFunc*)addressSet["lua_pcall"];
		lua_cpcall = (lua_cpcallFunc*)addressSet["lua_cpcall"];
		lua_load = (lua_loadFunc*)addressSet["lua_load"];
		lua_dump = (lua_dumpFunc*)addressSet["lua_dump"];
		//lua_yield = (lua_yieldFunc*)addressSet["lua_yield"];//USING_CODE
		lua_resume = (lua_resumeFunc*)addressSet["lua_resume"];
		//lua_status = (lua_statusFunc*)addressSet["lua_status"];//USING_CODE
		lua_gc = (lua_gcFunc*)addressSet["lua_gc"];
		lua_error = (lua_errorFunc*)addressSet["lua_error"];
		lua_next = (lua_nextFunc*)addressSet["lua_next"];
		lua_concat = (lua_concatFunc*)addressSet["lua_concat"];
		//lua_getallocf = (lua_getallocfFunc*)addressSet["lua_getallocf"];//NO_USE
		//lua_setallocf = (lua_setallocfFunc*)addressSet["lua_setallocf"];//NO_USE
		//lua_setlevel = (lua_setlevelFunc*)addressSet["lua_setlevel"];//NO_USE
		lua_getstack = (lua_getstackFunc*)addressSet["lua_getstack"];
		lua_getinfo = (lua_getinfoFunc*)addressSet["lua_getinfo"];
		lua_getlocal = (lua_getlocalFunc*)addressSet["lua_getlocal"];
		lua_setlocal = (lua_setlocalFunc*)addressSet["lua_setlocal"];
		lua_getupvalue = (lua_getupvalueFunc*)addressSet["lua_getupvalue"];
		lua_setupvalue = (lua_setupvalueFunc*)addressSet["lua_setupvalue"];
		lua_sethook = (lua_sethookFunc*)addressSet["lua_sethook"];
		//lua_gethook = (lua_gethookFunc*)addressSet["lua_gethook"];//USING_CODE
		//lua_gethookmask = (lua_gethookmaskFunc*)addressSet["lua_gethookmask"];//USING_CODE
		//lua_gethookcount = (lua_gethookcountFunc*)addressSet["lua_gethookcount"];//USING_CODE
		luaI_openlib = (luaI_openlibFunc*)addressSet["luaI_openlib"];
		//luaL_register = (luaL_registerFunc*)addressSet["luaL_register"];//USING_CODE
		luaL_getmetafield = (luaL_getmetafieldFunc*)addressSet["luaL_getmetafield"];
		luaL_callmeta = (luaL_callmetaFunc*)addressSet["luaL_callmeta"];
		luaL_typerror = (luaL_typerrorFunc*)addressSet["luaL_typerror"];
		luaL_argerror = (luaL_argerrorFunc*)addressSet["luaL_argerror"];
		luaL_checklstring = (luaL_checklstringFunc*)addressSet["luaL_checklstring"];
		luaL_optlstring = (luaL_optlstringFunc*)addressSet["luaL_optlstring"];
		luaL_checknumber = (luaL_checknumberFunc*)addressSet["luaL_checknumber"];
		//luaL_optnumber = (luaL_optnumberFunc*)addressSet["luaL_optnumber"];//USING_CODE
		luaL_checkinteger = (luaL_checkintegerFunc*)addressSet["luaL_checkinteger"];
		luaL_optinteger = (luaL_optintegerFunc*)addressSet["luaL_optinteger"];
		luaL_checkstack = (luaL_checkstackFunc*)addressSet["luaL_checkstack"];
		luaL_checktype = (luaL_checktypeFunc*)addressSet["luaL_checktype"];
		luaL_checkany = (luaL_checkanyFunc*)addressSet["luaL_checkany"];
		luaL_newmetatable = (luaL_newmetatableFunc*)addressSet["luaL_newmetatable"];
		luaL_checkudata = (luaL_checkudataFunc*)addressSet["luaL_checkudata"];
		luaL_where = (luaL_whereFunc*)addressSet["luaL_where"];
		luaL_error = (luaL_errorFunc*)addressSet["luaL_error"];
		luaL_checkoption = (luaL_checkoptionFunc*)addressSet["luaL_checkoption"];
		//luaL_ref = (luaL_refFunc*)addressSet["luaL_ref"];//USING_CODE
		//luaL_unref = (luaL_unrefFunc*)addressSet["luaL_unref"];//USING_CODE
		luaL_loadfile = (luaL_loadfileFunc*)addressSet["luaL_loadfile"];
		luaL_loadbuffer = (luaL_loadbufferFunc*)addressSet["luaL_loadbuffer"];
		//luaL_loadstring = (luaL_loadstringFunc*)addressSet["luaL_loadstring"];//USING_CODE
		luaL_newstate = (luaL_newstateFunc*)addressSet["luaL_newstate"];
		luaL_gsub = (luaL_gsubFunc*)addressSet["luaL_gsub"];
		luaL_findtable = (luaL_findtableFunc*)addressSet["luaL_findtable"];
		//luaL_buffinit = (luaL_buffinitFunc*)addressSet["luaL_buffinit"];//USING_CODE
		luaL_prepbuffer = (luaL_prepbufferFunc*)addressSet["luaL_prepbuffer"];
		luaL_addlstring = (luaL_addlstringFunc*)addressSet["luaL_addlstring"];
		//luaL_addstring = (luaL_addstringFunc*)addressSet["luaL_addstring"];//USING_CODE
		luaL_addvalue = (luaL_addvalueFunc*)addressSet["luaL_addvalue"];
		luaL_pushresult = (luaL_pushresultFunc*)addressSet["luaL_pushresult"];
		luaopen_base = (luaopen_baseFunc*)addressSet["luaopen_base"];
		luaopen_table = (luaopen_tableFunc*)addressSet["luaopen_table"];
		luaopen_io = (luaopen_ioFunc*)addressSet["luaopen_io"];
		luaopen_os = (luaopen_osFunc*)addressSet["luaopen_os"];
		luaopen_string = (luaopen_stringFunc*)addressSet["luaopen_string"];
		luaopen_math = (luaopen_mathFunc*)addressSet["luaopen_math"];
		luaopen_debug = (luaopen_debugFunc*)addressSet["luaopen_debug"];
		luaopen_package = (luaopen_packageFunc*)addressSet["luaopen_package"];
		luaL_openlibs = (luaL_openlibsFunc*)addressSet["luaL_openlibs"];
	}//SetFuncPtrs

}//namespace IHHook
