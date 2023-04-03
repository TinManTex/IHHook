//mgsvtpp_hook_stubs.cpp
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteHookStubsFile
//Not intended to be compiled, this is just stub/examples of hook functions
//so you can quickly just copy and paste them to get started.

namespace IHHook {
	StrCode GetStrCodeWithLengthHook(const char * buf, longlong len) {
	
		return GetStrCodeWithLength(buf, len);
	}//GetStrCodeWithLengthHook
	
	StrCode32 GetStrCode32Hook(const char * str) {
	
		return GetStrCode32(str);
	}//GetStrCode32Hook
	
	ulonglong PathCode64ExtHook(const char * inString) {
	
		return PathCode64Ext(inString);
	}//PathCode64ExtHook
	
	uint FNVHash32Hook(const char * strToHash) {
	
		return FNVHash32(strToHash);
	}//FNVHash32Hook
	
	ulonglong * GetFreeRoamLangIdHook(ulonglong * langId, short locationCode, short missionCode) {
	
		return GetFreeRoamLangId(langId, locationCode, missionCode);
	}//GetFreeRoamLangIdHook
	
	void UpdateFOVLerpHook(ulonglong param_1) {
	
		UpdateFOVLerp(param_1);
	}//UpdateFOVLerpHook
	
	void UnkPrintFuncStubbedOutHook(const char * fmt, void * param_2, void * param_3, void * param_4) {
	
		UnkPrintFuncStubbedOut(fmt, param_2, param_3, param_4);
	}//UnkPrintFuncStubbedOutHook
	
	// l_StubbedOut EXPORT_FUNC_FALSE
	// nullsub_2 EXPORT_FUNC_FALSE
	ulonglong * LoadFileHook(ulonglong * fileSlotIndex, ulonglong filePath64) {
	
		return LoadFile(fileSlotIndex, filePath64);
	}//LoadFileHook
	
	void LoadFileSubHook(PathCode64 pathA, PathCode64 pathB) {
	
		LoadFileSub(pathA, pathB);
	}//LoadFileSubHook
	
	Path * Path_CopyHook(Path * This, Path * rhs) {
	
		return Path_Copy(this, rhs);
	}//Path_CopyHook
	
	Path * GetEmptyPathHook() {
	
		return GetEmptyPath();
	}//GetEmptyPathHook
	
	ulonglong * LoadPlayerPartsFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType) {
	
		return LoadPlayerPartsFpk(fileSlotIndex, playerType, playerPartsType);
	}//LoadPlayerPartsFpkHook
	
	ulonglong * LoadPlayerPartsPartsHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType) {
	
		return LoadPlayerPartsParts(fileSlotIndex, playerType, playerPartsType);
	}//LoadPlayerPartsPartsHook
	
	ulonglong * LoadPlayerCamoFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
	
		return LoadPlayerCamoFpk(fileSlotIndex, playerType, playerPartsType, playerCamoType);
	}//LoadPlayerCamoFpkHook
	
	ulonglong * LoadPlayerCamoFv2Hook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType) {
	
		return LoadPlayerCamoFv2(fileSlotIndex, playerType, playerPartsType, playerCamoType);
	}//LoadPlayerCamoFv2Hook
	
	ulonglong * LoadPlayerFacialMotionFpkHook(ulonglong * fileSlotIndex, uint playerType) {
	
		return LoadPlayerFacialMotionFpk(fileSlotIndex, playerType);
	}//LoadPlayerFacialMotionFpkHook
	
	ulonglong * LoadPlayerFacialMotionMtarHook(ulonglong * fileSlotIndex, int playerType) {
	
		return LoadPlayerFacialMotionMtar(fileSlotIndex, playerType);
	}//LoadPlayerFacialMotionMtarHook
	
	ulonglong * LoadPlayerBionicArmFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType) {
	
		return LoadPlayerBionicArmFpk(fileSlotIndex, playerType, playerPartsType, playerHandType);
	}//LoadPlayerBionicArmFpkHook
	
	ulonglong * LoadPlayerBionicArmFv2Hook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType) {
	
		return LoadPlayerBionicArmFv2(fileSlotIndex, playerType, playerPartsType, playerHandType);
	}//LoadPlayerBionicArmFv2Hook
	
	bool CheckPlayerPartsIfShouldApplySkinToneFv2Hook(uint playerType, uint playerPartsType) {
	
		return CheckPlayerPartsIfShouldApplySkinToneFv2(playerType, playerPartsType);
	}//CheckPlayerPartsIfShouldApplySkinToneFv2Hook
	
	ulonglong * LoadPlayerPartsSkinToneFv2Hook(ulonglong * loadFile, uint playerType, uint playerPartsType) {
	
		return LoadPlayerPartsSkinToneFv2(loadFile, playerType, playerPartsType);
	}//LoadPlayerPartsSkinToneFv2Hook
	
	bool IsHeadNeededForPartsTypeHook(uint playerPartsType) {
	
		return IsHeadNeededForPartsType(playerPartsType);
	}//IsHeadNeededForPartsTypeHook
	
	bool IsHeadNeededForPartsTypeAndAvatarHook(uint playerPartsType) {
	
		return IsHeadNeededForPartsTypeAndAvatar(playerPartsType);
	}//IsHeadNeededForPartsTypeAndAvatarHook
	
	ulonglong * LoadPlayerSnakeFaceFpkHook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId) {
	
		return LoadPlayerSnakeFaceFpk(fileSlotIndex, playerType, playerPartsType, playerFaceId, playerFaceEquipId);
	}//LoadPlayerSnakeFaceFpkHook
	
	ulonglong * LoadPlayerSnakeFaceFv2Hook(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId) {
	
		return LoadPlayerSnakeFaceFv2(fileSlotIndex, playerType, playerPartsType, playerFaceId, playerFaceEquipId);
	}//LoadPlayerSnakeFaceFv2Hook
	
	ulonglong * LoadAvatarOgreHornFpkHook(ulonglong * fileSlotIndex, uint ogreLevel) {
	
		return LoadAvatarOgreHornFpk(fileSlotIndex, ogreLevel);
	}//LoadAvatarOgreHornFpkHook
	
	ulonglong * LoadAvatarOgreHornFv2Hook(ulonglong * fileSlotIndex, uint ogreLevel) {
	
		return LoadAvatarOgreHornFv2(fileSlotIndex, ogreLevel);
	}//LoadAvatarOgreHornFv2Hook
	
	ulonglong * LoadBuddyMainFileHook(ulonglong param_1, ulonglong * fileSlotIndex, uint buddyType, ulonglong param_4) {
	
		return LoadBuddyMainFile(param_1, fileSlotIndex, buddyType, param_4);
	}//LoadBuddyMainFileHook
	
	ulonglong * LoadBuddyQuietWeaponFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, short param_quietWeaponId) {
	
		return LoadBuddyQuietWeaponFpk(param_1, fileSlotIndex, param_quietWeaponId);
	}//LoadBuddyQuietWeaponFpkHook
	
	void LoadBuddyDogCommonFPKHook(longlong param_1, ulonglong * fileSlotIndex) {
	
		LoadBuddyDogCommonFPK(param_1, fileSlotIndex);
	}//LoadBuddyDogCommonFPKHook
	
	void LoadBuddyHorseCommonFPKHook(longlong param_1, ulonglong * fileSlotIndex) {
	
		LoadBuddyHorseCommonFPK(param_1, fileSlotIndex);
	}//LoadBuddyHorseCommonFPKHook
	
	ulonglong * LoadBuddyWalkerGearArmFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4) {
	
		return LoadBuddyWalkerGearArmFpk(param_1, fileSlotIndex, param_3, param_4);
	}//LoadBuddyWalkerGearArmFpkHook
	
	ulonglong * LoadBuddyWalkerGearHeadFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4) {
	
		return LoadBuddyWalkerGearHeadFpk(param_1, fileSlotIndex, param_3, param_4);
	}//LoadBuddyWalkerGearHeadFpkHook
	
	ulonglong * LoadBuddyWalkerGearWeaponFpkHook(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4) {
	
		return LoadBuddyWalkerGearWeaponFpk(param_1, fileSlotIndex, param_3, param_4);
	}//LoadBuddyWalkerGearWeaponFpkHook
	
	int * LoadDefaultFpksFuncHook(void * param_1, int * param_2, ulonglong * param_3, uint param_4) {
	
		return LoadDefaultFpksFunc(param_1, param_2, param_3, param_4);
	}//LoadDefaultFpksFuncHook
	
	char PreparePlayerVehicleInSortieHook(longlong param_1) {
	
		return PreparePlayerVehicleInSortie(param_1);
	}//PreparePlayerVehicleInSortieHook
	
	char PreparePlayerVehicleInGameHook(longlong param_1, ulonglong param_2) {
	
		return PreparePlayerVehicleInGame(param_1, param_2);
	}//PreparePlayerVehicleInGameHook
	
	longlong LoadDefaultFpkPtrFuncHook(longlong param_1, uint param_2) {
	
		return LoadDefaultFpkPtrFunc(param_1, param_2);
	}//LoadDefaultFpkPtrFuncHook
	
	ulonglong * LoadAllVehicleCamoFpksHook() {
	
		return LoadAllVehicleCamoFpks();
	}//LoadAllVehicleCamoFpksHook
	
	longlong * BuddyCommandGetNameLangIdHook(longlong * langId, uint commandType) {
	
		return BuddyCommandGetNameLangId(langId, commandType);
	}//BuddyCommandGetNameLangIdHook
	
	longlong * BuddyCommandGetDescriptionLangIdHook(longlong * langId, uint commandType) {
	
		return BuddyCommandGetDescriptionLangId(langId, commandType);
	}//BuddyCommandGetDescriptionLangIdHook
	
	foxlua::module * NewModuleHook(undefined8 param_1, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5) {
	
		return foxlua::NewModule(param_1, moduleName, param_3, param_4, param_5);
	}//NewModuleHook
	
	foxlua::module * NewSubModuleHook(foxlua::module * parentModule, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5) {
	
		return foxlua::NewSubModule(parentModule, moduleName, param_3, param_4, param_5);
	}//NewSubModuleHook
	
	int AddCFuncToModuleHook(foxlua::module * module, const char * funcName, lua_CFunction cfunc, undefined8 param_4, int param_5, void * param_6) {
	
		return foxlua::AddCFuncToModule(module, funcName, cfunc, param_4, param_5, param_6);
	}//AddCFuncToModuleHook
	
	int AddCFuncToModule2Hook(foxlua::module * module, const char * funcName, void * param_3) {
	
		return foxlua::AddCFuncToModule2(module, funcName, param_3);
	}//AddCFuncToModule2Hook
	
	undefined8 AddCFuncToModule3Hook(foxlua::module * moduleName, const char * funcName, lua_CFunction param_3, int param_4, void * param_5) {
	
		return foxlua::AddCFuncToModule3(moduleName, funcName, param_3, param_4, param_5);
	}//AddCFuncToModule3Hook
	
	void AddEnumToModuleHook(foxlua::module * foxModule, const char * enumName, int enumValue) {
	
		foxlua::AddEnumToModule(foxModule, enumName, enumValue);
	}//AddEnumToModuleHook
	
	bool AddEnumToModule2Hook(foxlua::module * module, const char * enumName, int * enumValue) {
	
		return foxlua::AddEnumToModule2(module, enumName, enumValue);
	}//AddEnumToModule2Hook
	
	void AddEnumToModule3Hook(foxlua::module * module, const char * enumName, undefined8 enumValue) {
	
		foxlua::AddEnumToModule3(module, enumName, enumValue);
	}//AddEnumToModule3Hook
	
	undefined AddEnumToModule4Hook(undefined8 module, undefined8 enumName, undefined8 enumValue) {
	
		return foxlua::AddEnumToModule4(module, enumName, enumValue);
	}//AddEnumToModule4Hook
	
	undefined RegisterVarHook(undefined8 foxLua, const char * varName, undefined8 varAddress, lua_CFunction * luaCFunc) {
	
		return RegisterVar(foxLua, varName, varAddress, luaCFunc);
	}//RegisterVarHook
	
	void RegisterVar_01Hook(longlong param_1, const char * varName, undefined4 param_3, undefined8 param_4, undefined2 param_5, undefined param_6) {
	
		RegisterVar_01(param_1, varName, param_3, param_4, param_5, param_6);
	}//RegisterVar_01Hook
	
	void RegisterVar_02Hook(undefined8 param_1, const char * varName, undefined8 param_3, char param_4) {
	
		RegisterVar_02(param_1, varName, param_3, param_4);
	}//RegisterVar_02Hook
	
	int RegisterVar_03Hook(foxlua::module * param_1, const char * varName, void * varAddress, lua_CFunction unkLuaCFunc) {
	
		return RegisterVar_03(param_1, varName, varAddress, unkLuaCFunc);
	}//RegisterVar_03Hook
	
	bool RegisterVarArrayHook(foxlua::module * module, const char * varName, lua_CFunction param_3, lua_CFunction param_4, undefined8 param_5, undefined * param_6, undefined * param_7, undefined8 arraySize) {
	
		return RegisterVarArray(module, varName, param_3, param_4, param_5, param_6, param_7, arraySize);
	}//RegisterVarArrayHook
	
	undefined4 * DeclareEntityClassHook(undefined4 * param_1, const char * className, longlong entityInfo) {
	
		return DeclareEntityClass(param_1, className, entityInfo);
	}//DeclareEntityClassHook
	
	lua_State * lua_newstateHook(lua_Alloc f, void * ud) {
	
		return lua_newstate(f, ud);
	}//lua_newstateHook
	
	void lua_closeHook(lua_State * L) {
	
		lua_close(L);
	}//lua_closeHook
	
	lua_State * lua_newthreadHook(lua_State * L) {
	
		return lua_newthread(L);
	}//lua_newthreadHook
	
	lua_CFunction lua_atpanicHook(lua_State * L, lua_CFunction panicf) {
	
		return lua_atpanic(L, panicf);
	}//lua_atpanicHook
	
	// lua_gettop USING_CODE
	void lua_settopHook(lua_State * L, int idx) {
	
		lua_settop(L, idx);
	}//lua_settopHook
	
	void lua_pushvalueHook(lua_State * L, int idx) {
	
		lua_pushvalue(L, idx);
	}//lua_pushvalueHook
	
	void lua_removeHook(lua_State * L, int idx) {
	
		lua_remove(L, idx);
	}//lua_removeHook
	
	void lua_insertHook(lua_State * L, int idx) {
	
		lua_insert(L, idx);
	}//lua_insertHook
	
	void lua_replaceHook(lua_State * L, int idx) {
	
		lua_replace(L, idx);
	}//lua_replaceHook
	
	int lua_checkstackHook(lua_State * L, int sz) {
	
		return lua_checkstack(L, sz);
	}//lua_checkstackHook
	
	void lua_xmoveHook(lua_State * from, lua_State * to, int n) {
	
		lua_xmove(from, to, n);
	}//lua_xmoveHook
	
	int lua_isnumberHook(lua_State * L, int idx) {
	
		return lua_isnumber(L, idx);
	}//lua_isnumberHook
	
	int lua_isstringHook(lua_State * L, int idx) {
	
		return lua_isstring(L, idx);
	}//lua_isstringHook
	
	int lua_iscfunctionHook(lua_State * L, int idx) {
	
		return lua_iscfunction(L, idx);
	}//lua_iscfunctionHook
	
	// lua_isuserdata USING_CODE
	int lua_typeHook(lua_State * L, int idx) {
	
		return lua_type(L, idx);
	}//lua_typeHook
	
	// lua_typename USING_CODE
	// lua_equal NOT_FOUND
	int lua_rawequalHook(lua_State * L, int idx1, int idx2) {
	
		return lua_rawequal(L, idx1, idx2);
	}//lua_rawequalHook
	
	int lua_lessthanHook(lua_State * L, int idx1, int idx2) {
	
		return lua_lessthan(L, idx1, idx2);
	}//lua_lessthanHook
	
	lua_Number lua_tonumberHook(lua_State * L, int idx) {
	
		return lua_tonumber(L, idx);
	}//lua_tonumberHook
	
	lua_Integer lua_tointegerHook(lua_State * L, int idx) {
	
		return lua_tointeger(L, idx);
	}//lua_tointegerHook
	
	int lua_tobooleanHook(lua_State * L, int idx) {
	
		return lua_toboolean(L, idx);
	}//lua_tobooleanHook
	
	char * lua_tolstringHook(lua_State * L, int idx, size_t * len) {
	
		return lua_tolstring(L, idx, len);
	}//lua_tolstringHook
	
	size_t lua_objlenHook(lua_State * L, int idx) {
	
		return lua_objlen(L, idx);
	}//lua_objlenHook
	
	lua_CFunction lua_tocfunctionHook(lua_State * L, int idx) {
	
		return lua_tocfunction(L, idx);
	}//lua_tocfunctionHook
	
	void * lua_touserdataHook(lua_State * L, int idx) {
	
		return lua_touserdata(L, idx);
	}//lua_touserdataHook
	
	lua_State * lua_tothreadHook(lua_State * L, int idx) {
	
		return lua_tothread(L, idx);
	}//lua_tothreadHook
	
	void * lua_topointerHook(lua_State * L, int idx) {
	
		return lua_topointer(L, idx);
	}//lua_topointerHook
	
	void lua_pushnilHook(lua_State * L) {
	
		lua_pushnil(L);
	}//lua_pushnilHook
	
	void lua_pushnumberHook(lua_State * L, lua_Number n) {
	
		lua_pushnumber(L, n);
	}//lua_pushnumberHook
	
	void lua_pushintegerHook(lua_State * L, lua_Integer n) {
	
		lua_pushinteger(L, n);
	}//lua_pushintegerHook
	
	void lua_pushlstringHook(lua_State * L, const char * s, size_t l) {
	
		lua_pushlstring(L, s, l);
	}//lua_pushlstringHook
	
	void lua_pushstringHook(lua_State * L, const char * s) {
	
		lua_pushstring(L, s);
	}//lua_pushstringHook
	
	char * lua_pushvfstringHook(lua_State * L, const char * fmt, void * argp) {
	
		return lua_pushvfstring(L, fmt, argp);
	}//lua_pushvfstringHook
	
	char * lua_pushfstringHook(lua_State * L, const char * fmt, ...) {
	
		return lua_pushfstring(L, fmt);
	}//lua_pushfstringHook
	
	void lua_pushcclosureHook(lua_State * L, lua_CFunction fn, int n) {
	
		lua_pushcclosure(L, fn, n);
	}//lua_pushcclosureHook
	
	void lua_pushbooleanHook(lua_State * L, int b) {
	
		lua_pushboolean(L, b);
	}//lua_pushbooleanHook
	
	void lua_pushlightuserdataHook(lua_State * L, void * p) {
	
		lua_pushlightuserdata(L, p);
	}//lua_pushlightuserdataHook
	
	int lua_pushthreadHook(lua_State * L) {
	
		return lua_pushthread(L);
	}//lua_pushthreadHook
	
	void lua_gettableHook(lua_State * L, int idx) {
	
		lua_gettable(L, idx);
	}//lua_gettableHook
	
	void lua_getfieldHook(lua_State * L, int idx, const char * k) {
	
		lua_getfield(L, idx, k);
	}//lua_getfieldHook
	
	void lua_rawgetHook(lua_State * L, int idx) {
	
		lua_rawget(L, idx);
	}//lua_rawgetHook
	
	void lua_rawgetiHook(lua_State * L, int idx, int n) {
	
		lua_rawgeti(L, idx, n);
	}//lua_rawgetiHook
	
	void lua_createtableHook(lua_State * L, int narr, int nrec) {
	
		lua_createtable(L, narr, nrec);
	}//lua_createtableHook
	
	void * lua_newuserdataHook(lua_State * L, size_t sz) {
	
		return lua_newuserdata(L, sz);
	}//lua_newuserdataHook
	
	int lua_getmetatableHook(lua_State * L, int objindex) {
	
		return lua_getmetatable(L, objindex);
	}//lua_getmetatableHook
	
	void lua_getfenvHook(lua_State * L, int idx) {
	
		lua_getfenv(L, idx);
	}//lua_getfenvHook
	
	void lua_settableHook(lua_State * L, int idx) {
	
		lua_settable(L, idx);
	}//lua_settableHook
	
	void lua_setfieldHook(lua_State * L, int idx, const char * k) {
	
		lua_setfield(L, idx, k);
	}//lua_setfieldHook
	
	void lua_rawsetHook(lua_State * L, int idx) {
	
		lua_rawset(L, idx);
	}//lua_rawsetHook
	
	void lua_rawsetiHook(lua_State * L, int idx, int n) {
	
		lua_rawseti(L, idx, n);
	}//lua_rawsetiHook
	
	int lua_setmetatableHook(lua_State * L, int objindex) {
	
		return lua_setmetatable(L, objindex);
	}//lua_setmetatableHook
	
	int lua_setfenvHook(lua_State * L, int idx) {
	
		return lua_setfenv(L, idx);
	}//lua_setfenvHook
	
	void lua_callHook(lua_State * L, int nargs, int nresults) {
	
		lua_call(L, nargs, nresults);
	}//lua_callHook
	
	int lua_pcallHook(lua_State * L, int nargs, int nresults, int errfunc) {
	
		return lua_pcall(L, nargs, nresults, errfunc);
	}//lua_pcallHook
	
	int lua_cpcallHook(lua_State * L, lua_CFunction func, void * ud) {
	
		return lua_cpcall(L, func, ud);
	}//lua_cpcallHook
	
	int lua_loadHook(lua_State * L, lua_Reader reader, void * dt, const char * chunkname) {
	
		return lua_load(L, reader, dt, chunkname);
	}//lua_loadHook
	
	int lua_dumpHook(lua_State * L, lua_Writer writer, void * data) {
	
		return lua_dump(L, writer, data);
	}//lua_dumpHook
	
	// lua_yield USING_CODE
	int lua_resumeHook(lua_State * L, int narg) {
	
		return lua_resume(L, narg);
	}//lua_resumeHook
	
	// lua_status USING_CODE
	int lua_gcHook(lua_State * L, int what, int data) {
	
		return lua_gc(L, what, data);
	}//lua_gcHook
	
	int lua_errorHook(lua_State * L) {
	
		return lua_error(L);
	}//lua_errorHook
	
	int lua_nextHook(lua_State * L, int idx) {
	
		return lua_next(L, idx);
	}//lua_nextHook
	
	void lua_concatHook(lua_State * L, int n) {
	
		lua_concat(L, n);
	}//lua_concatHook
	
	// lua_getallocf NO_USE
	// lua_setallocf NO_USE
	// lua_setlevel NO_USE
	int lua_getstackHook(lua_State * L, int level, lua_Debug * ar) {
	
		return lua_getstack(L, level, ar);
	}//lua_getstackHook
	
	int lua_getinfoHook(lua_State * L, const char * what, lua_Debug * ar) {
	
		return lua_getinfo(L, what, ar);
	}//lua_getinfoHook
	
	char * lua_getlocalHook(lua_State * L, lua_Debug * ar, int n) {
	
		return lua_getlocal(L, ar, n);
	}//lua_getlocalHook
	
	char * lua_setlocalHook(lua_State * L, lua_Debug * ar, int n) {
	
		return lua_setlocal(L, ar, n);
	}//lua_setlocalHook
	
	char * lua_getupvalueHook(lua_State * L, int funcindex, int n) {
	
		return lua_getupvalue(L, funcindex, n);
	}//lua_getupvalueHook
	
	char * lua_setupvalueHook(lua_State * L, int funcindex, int n) {
	
		return lua_setupvalue(L, funcindex, n);
	}//lua_setupvalueHook
	
	int lua_sethookHook(lua_State * L, lua_Hook func, int mask, int count) {
	
		return lua_sethook(L, func, mask, count);
	}//lua_sethookHook
	
	// lua_gethook USING_CODE
	// lua_gethookmask USING_CODE
	// lua_gethookcount USING_CODE
	void luaI_openlibHook(lua_State * L, const char * libName, const luaL_Reg * l, int nup) {
	
		luaI_openlib(L, libName, l, nup);
	}//luaI_openlibHook
	
	// luaL_register USING_CODE
	int luaL_getmetafieldHook(lua_State * L, int obj, const char * e) {
	
		return luaL_getmetafield(L, obj, e);
	}//luaL_getmetafieldHook
	
	int luaL_callmetaHook(lua_State * L, int obj, const char * e) {
	
		return luaL_callmeta(L, obj, e);
	}//luaL_callmetaHook
	
	int luaL_typerrorHook(lua_State * L, int narg, const char * tname) {
	
		return luaL_typerror(L, narg, tname);
	}//luaL_typerrorHook
	
	int luaL_argerrorHook(lua_State * L, int numarg, const char * extramsg) {
	
		return luaL_argerror(L, numarg, extramsg);
	}//luaL_argerrorHook
	
	char * luaL_checklstringHook(lua_State * L, int numArg, size_t * l) {
	
		return luaL_checklstring(L, numArg, l);
	}//luaL_checklstringHook
	
	char * luaL_optlstringHook(lua_State * L, int numArg, const char * def, size_t * l) {
	
		return luaL_optlstring(L, numArg, def, l);
	}//luaL_optlstringHook
	
	lua_Number luaL_checknumberHook(lua_State * L, int numArg) {
	
		return luaL_checknumber(L, numArg);
	}//luaL_checknumberHook
	
	// luaL_optnumber USING_CODE
	lua_Integer luaL_checkintegerHook(lua_State * L, int numArg) {
	
		return luaL_checkinteger(L, numArg);
	}//luaL_checkintegerHook
	
	lua_Integer luaL_optintegerHook(lua_State * L, int nArg, lua_Integer def) {
	
		return luaL_optinteger(L, nArg, def);
	}//luaL_optintegerHook
	
	void luaL_checkstackHook(lua_State * L, int sz, const char * msg) {
	
		luaL_checkstack(L, sz, msg);
	}//luaL_checkstackHook
	
	void luaL_checktypeHook(lua_State * L, int narg, int t) {
	
		luaL_checktype(L, narg, t);
	}//luaL_checktypeHook
	
	void luaL_checkanyHook(lua_State * L, int narg) {
	
		luaL_checkany(L, narg);
	}//luaL_checkanyHook
	
	int luaL_newmetatableHook(lua_State * L, const char * tname) {
	
		return luaL_newmetatable(L, tname);
	}//luaL_newmetatableHook
	
	void * luaL_checkudataHook(lua_State * L, int ud, const char * tname) {
	
		return luaL_checkudata(L, ud, tname);
	}//luaL_checkudataHook
	
	void luaL_whereHook(lua_State * L, int lvl) {
	
		luaL_where(L, lvl);
	}//luaL_whereHook
	
	int luaL_errorHook(lua_State * L, const char * fmt, ...) {
	
		return luaL_error(L, fmt);
	}//luaL_errorHook
	
	int luaL_checkoptionHook(lua_State * L, int narg, const char * def, char * * lst) {
	
		return luaL_checkoption(L, narg, def, lst);
	}//luaL_checkoptionHook
	
	// luaL_ref USING_CODE
	// luaL_unref USING_CODE
	int luaL_loadfileHook(lua_State * L, const char * filename) {
	
		return luaL_loadfile(L, filename);
	}//luaL_loadfileHook
	
	int luaL_loadbufferHook(lua_State * L, const char * buff, size_t sz, const char * name) {
	
		return luaL_loadbuffer(L, buff, sz, name);
	}//luaL_loadbufferHook
	
	// luaL_loadstring USING_CODE
	lua_State * luaL_newstateHook() {
	
		return luaL_newstate();
	}//luaL_newstateHook
	
	char * luaL_gsubHook(lua_State * L, const char * s, const char * p, const char * r) {
	
		return luaL_gsub(L, s, p, r);
	}//luaL_gsubHook
	
	char * luaL_findtableHook(lua_State * L, int idx, const char * fname, int szhint) {
	
		return luaL_findtable(L, idx, fname, szhint);
	}//luaL_findtableHook
	
	// luaL_buffinit USING_CODE
	char * luaL_prepbufferHook(luaL_Buffer * B) {
	
		return luaL_prepbuffer(B);
	}//luaL_prepbufferHook
	
	void luaL_addlstringHook(luaL_Buffer * B, const char * s, size_t l) {
	
		luaL_addlstring(B, s, l);
	}//luaL_addlstringHook
	
	// luaL_addstring USING_CODE
	void luaL_addvalueHook(luaL_Buffer * B) {
	
		luaL_addvalue(B);
	}//luaL_addvalueHook
	
	void luaL_pushresultHook(luaL_Buffer * B) {
	
		luaL_pushresult(B);
	}//luaL_pushresultHook
	
	int luaopen_baseHook(lua_State * L) {
	
		return luaopen_base(L);
	}//luaopen_baseHook
	
	int luaopen_tableHook(lua_State * L) {
	
		return luaopen_table(L);
	}//luaopen_tableHook
	
	int luaopen_ioHook(lua_State * L) {
	
		return luaopen_io(L);
	}//luaopen_ioHook
	
	int luaopen_osHook(lua_State * L) {
	
		return luaopen_os(L);
	}//luaopen_osHook
	
	int luaopen_stringHook(lua_State * L) {
	
		return luaopen_string(L);
	}//luaopen_stringHook
	
	int luaopen_mathHook(lua_State * L) {
	
		return luaopen_math(L);
	}//luaopen_mathHook
	
	int luaopen_debugHook(lua_State * L) {
	
		return luaopen_debug(L);
	}//luaopen_debugHook
	
	int luaopen_packageHook(lua_State * L) {
	
		return luaopen_package(L);
	}//luaopen_packageHook
	
	void luaL_openlibsHook(lua_State * L) {
	
		luaL_openlibs(L);
	}//luaL_openlibsHook
	

}//namespace IHHook
