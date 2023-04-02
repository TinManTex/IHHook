//mgsvtpp_hook_stubs.cpp
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteHookStubsFile
//Not intended to be compiled, this is just stub/examples of hook functions
//so you can quickly just copy and paste them to get started.

namespace IHHook {
	__fastcall StrCode GetStrCodeWithLengthHook(const char * buf, longlong len) {
	
		return GetStrCodeWithLength(buf, len);
	}//GetStrCodeWithLengthHook
	
	__fastcall StrCode32 GetStrCode32Hook(const char * str) {
	
		return GetStrCode32(str);
	}//GetStrCode32Hook
	
	__fastcall ulonglong PathCode64ExtHook(const char * inString) {
	
		return PathCode64Ext(inString);
	}//PathCode64ExtHook
	
	__fastcall uint FNVHash32Hook(const char * strToHash) {
	
		return FNVHash32(strToHash);
	}//FNVHash32Hook
	
	__fastcall ulonglong * GetFreeRoamLangIdHook(ulonglong * langId, short locationCode, short missionCode) {
	
		return GetFreeRoamLangId(langId, locationCode, missionCode);
	}//GetFreeRoamLangIdHook
	
	__fastcall void UpdateFOVLerpHook(ulonglong param_1) {
	
		return UpdateFOVLerp(param_1);
	}//UpdateFOVLerpHook
	
	__fastcall void UnkPrintFuncStubbedOutHook(const char * fmt, void * param_2, void * param_3, void * param_4) {
	
		return UnkPrintFuncStubbedOut(fmt, param_2, param_3, param_4);
	}//UnkPrintFuncStubbedOutHook
	
	// l_StubbedOut EXPORT_FUNC_FALSE
	// nullsub_2 EXPORT_FUNC_FALSE
	__fastcall ulonglong * LoadFileHook(ulonglong * fileSlotIndex, ulonglong filePath64) {
	
		return LoadFile(fileSlotIndex, filePath64);
	}//LoadFileHook
	
	__fastcall void LoadFileSubHook(PathCode64 pathA, PathCode64 pathB) {
	
		return LoadFileSub(pathA, pathB);
	}//LoadFileSubHook
	
	__thiscall Path * Path_CopyHook(Path * This, Path * rhs) {
	
		return Path_Copy(this, rhs);
	}//Path_CopyHook
	
	__fastcall Path * GetEmptyPathHook() {
	
		return GetEmptyPath();
	}//GetEmptyPathHook
	
	__fastcall ulonglong * LoadPlayerPartsFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType) {
	
		return LoadPlayerPartsFpk(fileSlotIndex, playerType, playerPartsType);
	}//LoadPlayerPartsFpkHook
	
	__fastcall ulonglong * LoadPlayerPartsPartsHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType) {
	
		return LoadPlayerPartsParts(fileSlotIndex, playerType, playerPartsType);
	}//LoadPlayerPartsPartsHook
	
	__fastcall ulonglong * LoadPlayerCamoFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
	
		return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
	}//LoadPlayerCamoFpkHook
	
	__fastcall ulonglong * LoadPlayerCamoFv2Hook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
	
		return LoadPlayerCamoFv2(fileSlotIndex, playerType, playerPartsType, playerCamoType);
	}//LoadPlayerCamoFv2Hook
	
	__fastcall ulonglong * LoadPlayerFacialMotionFpkHook(ulonglong * fileSlotIndex, uint playerType) {
	
		return LoadPlayerFacialMotionFpk(fileSlotIndex, playerType);
	}//LoadPlayerFacialMotionFpkHook
	
	__fastcall ulonglong * LoadPlayerFacialMotionMtarHook(ulonglong * fileSlotIndex, int playerType) {
	
		return LoadPlayerFacialMotionMtar(fileSlotIndex, playerType);
	}//LoadPlayerFacialMotionMtarHook
	
	__fastcall ulonglong * LoadPlayerBionicArmFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType) {
	
		return LoadPlayerBionicArmFpk(fileSlotIndex, playerType, playerPartsType, playerHandType);
	}//LoadPlayerBionicArmFpkHook
	
	__fastcall ulonglong * LoadPlayerBionicArmFv2Hook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType) {
	
		return LoadPlayerBionicArmFv2(fileSlotIndex, playerType, playerPartsType, playerHandType);
	}//LoadPlayerBionicArmFv2Hook
	
	__fastcall bool CheckPlayerPartsIfShouldApplySkinToneFv2Hook(uint playerType, uint playerPartsType) {
	
		return CheckPlayerPartsIfShouldApplySkinToneFv2(playerType, playerPartsType);
	}//CheckPlayerPartsIfShouldApplySkinToneFv2Hook
	
	__fastcall ulonglong * LoadPlayerPartsSkinToneFv2Hook(ulonglong * loadFile, uint playerType, uint playerPartsType) {
	
		return LoadPlayerPartsSkinToneFv2(loadFile, playerType, playerPartsType);
	}//LoadPlayerPartsSkinToneFv2Hook
	
	__fastcall bool IsHeadNeededForPartsTypeHook(uint playerPartsType) {
	
		return IsHeadNeededForPartsType(playerPartsType);
	}//IsHeadNeededForPartsTypeHook
	
	__fastcall bool IsHeadNeededForPartsTypeAndAvatarHook(uint playerPartsType) {
	
		return IsHeadNeededForPartsTypeAndAvatar(playerPartsType);
	}//IsHeadNeededForPartsTypeAndAvatarHook
	
	__fastcall ulonglong * LoadPlayerSnakeFaceFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId) {
	
		return LoadPlayerSnakeFaceFpk(fileSlotIndex, playerType, playerPartsType, playerFaceId, playerFaceEquipId);
	}//LoadPlayerSnakeFaceFpkHook
	
	__fastcall ulonglong * LoadPlayerSnakeFaceFv2Hook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId) {
	
		return LoadPlayerSnakeFaceFv2(fileSlotIndex, playerType, playerPartsType, playerFaceId, playerFaceEquipId);
	}//LoadPlayerSnakeFaceFv2Hook
	
	__fastcall ulonglong * LoadAvatarOgreHornFpkHook(ulonglong * fileSlotIndex, uint ogreLevel) {
	
		return LoadAvatarOgreHornFpk(fileSlotIndex, ogreLevel);
	}//LoadAvatarOgreHornFpkHook
	
	__fastcall ulonglong * LoadAvatarOgreHornFv2Hook(ulonglong * fileSlotIndex, uint ogreLevel) {
	
		return LoadAvatarOgreHornFv2(fileSlotIndex, ogreLevel);
	}//LoadAvatarOgreHornFv2Hook
	
	__fastcall ulonglong * LoadBuddyMainFileHook(ulonglong param_1, ulonglong * fileSlotIndex, uint buddyType, ulonglong param_4) {
	
		return LoadBuddyMainFile(param_1, fileSlotIndex, buddyType, param_4);
	}//LoadBuddyMainFileHook
	
	__fastcall ulonglong * LoadBuddyQuietWeaponFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, short param_quietWeaponId) {
	
		return LoadBuddyQuietWeaponFpk(param_1, fileSlotIndex, param_quietWeaponId);
	}//LoadBuddyQuietWeaponFpkHook
	
	__fastcall void LoadBuddyDogCommonFPKHook(longlong param_1, ulonglong * fileSlotIndex) {
	
		return LoadBuddyDogCommonFPK(param_1, fileSlotIndex);
	}//LoadBuddyDogCommonFPKHook
	
	__fastcall void LoadBuddyHorseCommonFPKHook(longlong param_1, ulonglong * fileSlotIndex) {
	
		return LoadBuddyHorseCommonFPK(param_1, fileSlotIndex);
	}//LoadBuddyHorseCommonFPKHook
	
	__fastcall ulonglong * LoadBuddyWalkerGearArmFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4) {
	
		return LoadBuddyWalkerGearArmFpk(param_1, fileSlotIndex, param_3, param_4);
	}//LoadBuddyWalkerGearArmFpkHook
	
	__fastcall ulonglong * LoadBuddyWalkerGearHeadFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4) {
	
		return LoadBuddyWalkerGearHeadFpk(param_1, fileSlotIndex, param_3, param_4);
	}//LoadBuddyWalkerGearHeadFpkHook
	
	__fastcall ulonglong * LoadBuddyWalkerGearWeaponFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4) {
	
		return LoadBuddyWalkerGearWeaponFpk(param_1, fileSlotIndex, param_3, param_4);
	}//LoadBuddyWalkerGearWeaponFpkHook
	
	__fastcall int * LoadDefaultFpksFuncHook(void * param_1, int * param_2, ulonglong * param_3, uint param_4) {
	
		return LoadDefaultFpksFunc(param_1, param_2, param_3, param_4);
	}//LoadDefaultFpksFuncHook
	
	__fastcall char PreparePlayerVehicleInSortieHook(longlong param_1) {
	
		return PreparePlayerVehicleInSortie(param_1);
	}//PreparePlayerVehicleInSortieHook
	
	__fastcall char PreparePlayerVehicleInGameHook(longlong param_1, ulonglong param_2) {
	
		return PreparePlayerVehicleInGame(param_1, param_2);
	}//PreparePlayerVehicleInGameHook
	
	__fastcall longlong LoadDefaultFpkPtrFuncHook(longlong param_1, uint param_2) {
	
		return LoadDefaultFpkPtrFunc(param_1, param_2);
	}//LoadDefaultFpkPtrFuncHook
	
	__fastcall ulonglong * LoadAllVehicleCamoFpksHook() {
	
		return LoadAllVehicleCamoFpks();
	}//LoadAllVehicleCamoFpksHook
	
	__fastcall longlong * BuddyCommandGetNameLangIdHook(longlong * langId, uint commandType) {
	
		return BuddyCommandGetNameLangId(langId, commandType);
	}//BuddyCommandGetNameLangIdHook
	
	__fastcall longlong * BuddyCommandGetDescriptionLangIdHook(longlong * langId, uint commandType) {
	
		return BuddyCommandGetDescriptionLangId(langId, commandType);
	}//BuddyCommandGetDescriptionLangIdHook
	
	__fastcall lua_State * lua_newstateHook(lua_Alloc f, void * ud) {
	
		return lua_newstate(f, ud);
	}//lua_newstateHook
	
	__fastcall void lua_closeHook(lua_State * L) {
	
		return lua_close(L);
	}//lua_closeHook
	
	__fastcall lua_State * lua_newthreadHook(lua_State * L) {
	
		return lua_newthread(L);
	}//lua_newthreadHook
	
	__fastcall lua_CFunction lua_atpanicHook(lua_State * L, lua_CFunction panicf) {
	
		return lua_atpanic(L, panicf);
	}//lua_atpanicHook
	
	// lua_gettop USING_CODE
	__fastcall void lua_settopHook(lua_State * L, int idx) {
	
		return lua_settop(L, idx);
	}//lua_settopHook
	
	__fastcall void lua_pushvalueHook(lua_State * L, int idx) {
	
		return lua_pushvalue(L, idx);
	}//lua_pushvalueHook
	
	__fastcall void lua_removeHook(lua_State * L, int idx) {
	
		return lua_remove(L, idx);
	}//lua_removeHook
	
	__fastcall void lua_insertHook(lua_State * L, int idx) {
	
		return lua_insert(L, idx);
	}//lua_insertHook
	
	__fastcall void lua_replaceHook(lua_State * L, int idx) {
	
		return lua_replace(L, idx);
	}//lua_replaceHook
	
	__fastcall int lua_checkstackHook(lua_State * L, int sz) {
	
		return lua_checkstack(L, sz);
	}//lua_checkstackHook
	
	__fastcall void lua_xmoveHook(lua_State * from, lua_State * to, int n) {
	
		return lua_xmove(from, to, n);
	}//lua_xmoveHook
	
	__fastcall int lua_isnumberHook(lua_State * L, int idx) {
	
		return lua_isnumber(L, idx);
	}//lua_isnumberHook
	
	__fastcall int lua_isstringHook(lua_State * L, int idx) {
	
		return lua_isstring(L, idx);
	}//lua_isstringHook
	
	__fastcall int lua_iscfunctionHook(lua_State * L, int idx) {
	
		return lua_iscfunction(L, idx);
	}//lua_iscfunctionHook
	
	// lua_isuserdata USING_CODE
	__fastcall int lua_typeHook(lua_State * L, int idx) {
	
		return lua_type(L, idx);
	}//lua_typeHook
	
	// lua_typename USING_CODE
	// lua_equal NOT_FOUND
	__fastcall int lua_rawequalHook(lua_State * L, int idx1, int idx2) {
	
		return lua_rawequal(L, idx1, idx2);
	}//lua_rawequalHook
	
	__fastcall int lua_lessthanHook(lua_State * L, int idx1, int idx2) {
	
		return lua_lessthan(L, idx1, idx2);
	}//lua_lessthanHook
	
	__fastcall lua_Number lua_tonumberHook(lua_State * L, int idx) {
	
		return lua_tonumber(L, idx);
	}//lua_tonumberHook
	
	__fastcall lua_Integer lua_tointegerHook(lua_State * L, int idx) {
	
		return lua_tointeger(L, idx);
	}//lua_tointegerHook
	
	__fastcall int lua_tobooleanHook(lua_State * L, int idx) {
	
		return lua_toboolean(L, idx);
	}//lua_tobooleanHook
	
	__fastcall char * lua_tolstringHook(lua_State * L, int idx, size_t * len) {
	
		return lua_tolstring(L, idx, len);
	}//lua_tolstringHook
	
	__fastcall size_t lua_objlenHook(lua_State * L, int idx) {
	
		return lua_objlen(L, idx);
	}//lua_objlenHook
	
	__fastcall lua_CFunction lua_tocfunctionHook(lua_State * L, int idx) {
	
		return lua_tocfunction(L, idx);
	}//lua_tocfunctionHook
	
	__fastcall void * lua_touserdataHook(lua_State * L, int idx) {
	
		return lua_touserdata(L, idx);
	}//lua_touserdataHook
	
	__fastcall lua_State * lua_tothreadHook(lua_State * L, int idx) {
	
		return lua_tothread(L, idx);
	}//lua_tothreadHook
	
	__fastcall void * lua_topointerHook(lua_State * L, int idx) {
	
		return lua_topointer(L, idx);
	}//lua_topointerHook
	
	__fastcall void lua_pushnilHook(lua_State * L) {
	
		return lua_pushnil(L);
	}//lua_pushnilHook
	
	__fastcall void lua_pushnumberHook(lua_State * L, lua_Number n) {
	
		return lua_pushnumber(L, n);
	}//lua_pushnumberHook
	
	__fastcall void lua_pushintegerHook(lua_State * L, lua_Integer n) {
	
		return lua_pushinteger(L, n);
	}//lua_pushintegerHook
	
	__fastcall void lua_pushlstringHook(lua_State * L, const char * s, size_t l) {
	
		return lua_pushlstring(L, s, l);
	}//lua_pushlstringHook
	
	__fastcall void lua_pushstringHook(lua_State * L, const char * s) {
	
		return lua_pushstring(L, s);
	}//lua_pushstringHook
	
	__fastcall char * lua_pushvfstringHook(lua_State * L, const char * fmt, void * argp) {
	
		return lua_pushvfstring(L, fmt, argp);
	}//lua_pushvfstringHook
	
	__fastcall char * lua_pushfstringHook(lua_State * L, const char * fmt, ...) {
	
		return lua_pushfstring(L, fmt);
	}//lua_pushfstringHook
	
	__fastcall void lua_pushcclosureHook(lua_State * L, lua_CFunction fn, int n) {
	
		return lua_pushcclosure(L, fn, n);
	}//lua_pushcclosureHook
	
	__fastcall void lua_pushbooleanHook(lua_State * L, int b) {
	
		return lua_pushboolean(L, b);
	}//lua_pushbooleanHook
	
	__fastcall void lua_pushlightuserdataHook(lua_State * L, void * p) {
	
		return lua_pushlightuserdata(L, p);
	}//lua_pushlightuserdataHook
	
	__fastcall int lua_pushthreadHook(lua_State * L) {
	
		return lua_pushthread(L);
	}//lua_pushthreadHook
	
	__fastcall void lua_gettableHook(lua_State * L, int idx) {
	
		return lua_gettable(L, idx);
	}//lua_gettableHook
	
	__fastcall void lua_getfieldHook(lua_State * L, int idx, const char * k) {
	
		return lua_getfield(L, idx, k);
	}//lua_getfieldHook
	
	__fastcall void lua_rawgetHook(lua_State * L, int idx) {
	
		return lua_rawget(L, idx);
	}//lua_rawgetHook
	
	__fastcall void lua_rawgetiHook(lua_State * L, int idx, int n) {
	
		return lua_rawgeti(L, idx, n);
	}//lua_rawgetiHook
	
	__fastcall void lua_createtableHook(lua_State * L, int narr, int nrec) {
	
		return lua_createtable(L, narr, nrec);
	}//lua_createtableHook
	
	__fastcall void * lua_newuserdataHook(lua_State * L, size_t sz) {
	
		return lua_newuserdata(L, sz);
	}//lua_newuserdataHook
	
	__fastcall int lua_getmetatableHook(lua_State * L, int objindex) {
	
		return lua_getmetatable(L, objindex);
	}//lua_getmetatableHook
	
	__fastcall void lua_getfenvHook(lua_State * L, int idx) {
	
		return lua_getfenv(L, idx);
	}//lua_getfenvHook
	
	__fastcall void lua_settableHook(lua_State * L, int idx) {
	
		return lua_settable(L, idx);
	}//lua_settableHook
	
	__fastcall void lua_setfieldHook(lua_State * L, int idx, const char * k) {
	
		return lua_setfield(L, idx, k);
	}//lua_setfieldHook
	
	__fastcall void lua_rawsetHook(lua_State * L, int idx) {
	
		return lua_rawset(L, idx);
	}//lua_rawsetHook
	
	__fastcall void lua_rawsetiHook(lua_State * L, int idx, int n) {
	
		return lua_rawseti(L, idx, n);
	}//lua_rawsetiHook
	
	__fastcall int lua_setmetatableHook(lua_State * L, int objindex) {
	
		return lua_setmetatable(L, objindex);
	}//lua_setmetatableHook
	
	__fastcall int lua_setfenvHook(lua_State * L, int idx) {
	
		return lua_setfenv(L, idx);
	}//lua_setfenvHook
	
	__fastcall void lua_callHook(lua_State * L, int nargs, int nresults) {
	
		return lua_call(L, nargs, nresults);
	}//lua_callHook
	
	__fastcall int lua_pcallHook(lua_State * L, int nargs, int nresults, int errfunc) {
	
		return lua_pcall(L, nargs, nresults, errfunc);
	}//lua_pcallHook
	
	__fastcall int lua_cpcallHook(lua_State * L, lua_CFunction func, void * ud) {
	
		return lua_cpcall(L, func, ud);
	}//lua_cpcallHook
	
	__fastcall int lua_loadHook(lua_State * L, lua_Reader reader, void * dt, const char * chunkname) {
	
		return lua_load(L, reader, dt, chunkname);
	}//lua_loadHook
	
	__fastcall int lua_dumpHook(lua_State * L, lua_Writer writer, void * data) {
	
		return lua_dump(L, writer, data);
	}//lua_dumpHook
	
	// lua_yield USING_CODE
	__fastcall int lua_resumeHook(lua_State * L, int narg) {
	
		return lua_resume(L, narg);
	}//lua_resumeHook
	
	// lua_status USING_CODE
	__fastcall int lua_gcHook(lua_State * L, int what, int data) {
	
		return lua_gc(L, what, data);
	}//lua_gcHook
	
	__fastcall int lua_errorHook(lua_State * L) {
	
		return lua_error(L);
	}//lua_errorHook
	
	__fastcall int lua_nextHook(lua_State * L, int idx) {
	
		return lua_next(L, idx);
	}//lua_nextHook
	
	__fastcall void lua_concatHook(lua_State * L, int n) {
	
		return lua_concat(L, n);
	}//lua_concatHook
	
	// lua_getallocf NO_USE
	// lua_setallocf NO_USE
	// lua_setlevel NO_USE
	__fastcall int lua_getstackHook(lua_State * L, int level, lua_Debug * ar) {
	
		return lua_getstack(L, level, ar);
	}//lua_getstackHook
	
	__fastcall int lua_getinfoHook(lua_State * L, const char * what, lua_Debug * ar) {
	
		return lua_getinfo(L, what, ar);
	}//lua_getinfoHook
	
	__fastcall char * lua_getlocalHook(lua_State * L, lua_Debug * ar, int n) {
	
		return lua_getlocal(L, ar, n);
	}//lua_getlocalHook
	
	__fastcall char * lua_setlocalHook(lua_State * L, lua_Debug * ar, int n) {
	
		return lua_setlocal(L, ar, n);
	}//lua_setlocalHook
	
	__fastcall char * lua_getupvalueHook(lua_State * L, int funcindex, int n) {
	
		return lua_getupvalue(L, funcindex, n);
	}//lua_getupvalueHook
	
	__fastcall char * lua_setupvalueHook(lua_State * L, int funcindex, int n) {
	
		return lua_setupvalue(L, funcindex, n);
	}//lua_setupvalueHook
	
	__fastcall int lua_sethookHook(lua_State * L, lua_Hook func, int mask, int count) {
	
		return lua_sethook(L, func, mask, count);
	}//lua_sethookHook
	
	// lua_gethook USING_CODE
	// lua_gethookmask USING_CODE
	// lua_gethookcount USING_CODE
	__fastcall void luaI_openlibHook(lua_State * L, const char * libName, const luaL_Reg * l, int nup) {
	
		return luaI_openlib(L, libName, l, nup);
	}//luaI_openlibHook
	
	// luaL_register USING_CODE
	__fastcall int luaL_getmetafieldHook(lua_State * L, int obj, const char * e) {
	
		return luaL_getmetafield(L, obj, e);
	}//luaL_getmetafieldHook
	
	__fastcall int luaL_callmetaHook(lua_State * L, int obj, const char * e) {
	
		return luaL_callmeta(L, obj, e);
	}//luaL_callmetaHook
	
	__fastcall int luaL_typerrorHook(lua_State * L, int narg, const char * tname) {
	
		return luaL_typerror(L, narg, tname);
	}//luaL_typerrorHook
	
	__fastcall int luaL_argerrorHook(lua_State * L, int numarg, const char * extramsg) {
	
		return luaL_argerror(L, numarg, extramsg);
	}//luaL_argerrorHook
	
	__fastcall char * luaL_checklstringHook(lua_State * L, int numArg, size_t * l) {
	
		return luaL_checklstring(L, numArg, l);
	}//luaL_checklstringHook
	
	__fastcall char * luaL_optlstringHook(lua_State * L, int numArg, const char * def, size_t * l) {
	
		return luaL_optlstring(L, numArg, def, l);
	}//luaL_optlstringHook
	
	__fastcall lua_Number luaL_checknumberHook(lua_State * L, int numArg) {
	
		return luaL_checknumber(L, numArg);
	}//luaL_checknumberHook
	
	// luaL_optnumber USING_CODE
	__fastcall lua_Integer luaL_checkintegerHook(lua_State * L, int numArg) {
	
		return luaL_checkinteger(L, numArg);
	}//luaL_checkintegerHook
	
	__fastcall lua_Integer luaL_optintegerHook(lua_State * L, int nArg, lua_Integer def) {
	
		return luaL_optinteger(L, nArg, def);
	}//luaL_optintegerHook
	
	__fastcall void luaL_checkstackHook(lua_State * L, int sz, const char * msg) {
	
		return luaL_checkstack(L, sz, msg);
	}//luaL_checkstackHook
	
	__fastcall void luaL_checktypeHook(lua_State * L, int narg, int t) {
	
		return luaL_checktype(L, narg, t);
	}//luaL_checktypeHook
	
	__fastcall void luaL_checkanyHook(lua_State * L, int narg) {
	
		return luaL_checkany(L, narg);
	}//luaL_checkanyHook
	
	__fastcall int luaL_newmetatableHook(lua_State * L, const char * tname) {
	
		return luaL_newmetatable(L, tname);
	}//luaL_newmetatableHook
	
	__fastcall void * luaL_checkudataHook(lua_State * L, int ud, const char * tname) {
	
		return luaL_checkudata(L, ud, tname);
	}//luaL_checkudataHook
	
	__fastcall void luaL_whereHook(lua_State * L, int lvl) {
	
		return luaL_where(L, lvl);
	}//luaL_whereHook
	
	__fastcall int luaL_errorHook(lua_State * L, const char * fmt, ...) {
	
		return luaL_error(L, fmt);
	}//luaL_errorHook
	
	__fastcall int luaL_checkoptionHook(lua_State * L, int narg, const char * def, char * * lst) {
	
		return luaL_checkoption(L, narg, def, lst);
	}//luaL_checkoptionHook
	
	// luaL_ref USING_CODE
	// luaL_unref USING_CODE
	__fastcall int luaL_loadfileHook(lua_State * L, const char * filename) {
	
		return luaL_loadfile(L, filename);
	}//luaL_loadfileHook
	
	__fastcall int luaL_loadbufferHook(lua_State * L, const char * buff, size_t sz, const char * name) {
	
		return luaL_loadbuffer(L, buff, sz, name);
	}//luaL_loadbufferHook
	
	// luaL_loadstring USING_CODE
	__fastcall lua_State * luaL_newstateHook() {
	
		return luaL_newstate();
	}//luaL_newstateHook
	
	__fastcall char * luaL_gsubHook(lua_State * L, const char * s, const char * p, const char * r) {
	
		return luaL_gsub(L, s, p, r);
	}//luaL_gsubHook
	
	__fastcall char * luaL_findtableHook(lua_State * L, int idx, const char * fname, int szhint) {
	
		return luaL_findtable(L, idx, fname, szhint);
	}//luaL_findtableHook
	
	// luaL_buffinit USING_CODE
	__fastcall char * luaL_prepbufferHook(luaL_Buffer * B) {
	
		return luaL_prepbuffer(B);
	}//luaL_prepbufferHook
	
	__fastcall void luaL_addlstringHook(luaL_Buffer * B, const char * s, size_t l) {
	
		return luaL_addlstring(B, s, l);
	}//luaL_addlstringHook
	
	// luaL_addstring USING_CODE
	__fastcall void luaL_addvalueHook(luaL_Buffer * B) {
	
		return luaL_addvalue(B);
	}//luaL_addvalueHook
	
	__fastcall void luaL_pushresultHook(luaL_Buffer * B) {
	
		return luaL_pushresult(B);
	}//luaL_pushresultHook
	
	__fastcall int luaopen_baseHook(lua_State * L) {
	
		return luaopen_base(L);
	}//luaopen_baseHook
	
	__fastcall int luaopen_tableHook(lua_State * L) {
	
		return luaopen_table(L);
	}//luaopen_tableHook
	
	__fastcall int luaopen_ioHook(lua_State * L) {
	
		return luaopen_io(L);
	}//luaopen_ioHook
	
	__fastcall int luaopen_osHook(lua_State * L) {
	
		return luaopen_os(L);
	}//luaopen_osHook
	
	__fastcall int luaopen_stringHook(lua_State * L) {
	
		return luaopen_string(L);
	}//luaopen_stringHook
	
	__fastcall int luaopen_mathHook(lua_State * L) {
	
		return luaopen_math(L);
	}//luaopen_mathHook
	
	__fastcall int luaopen_debugHook(lua_State * L) {
	
		return luaopen_debug(L);
	}//luaopen_debugHook
	
	__fastcall int luaopen_packageHook(lua_State * L) {
	
		return luaopen_package(L);
	}//luaopen_packageHook
	
	__fastcall void luaL_openlibsHook(lua_State * L) {
	
		return luaL_openlibs(L);
	}//luaL_openlibsHook
	

}//namespace IHHook
