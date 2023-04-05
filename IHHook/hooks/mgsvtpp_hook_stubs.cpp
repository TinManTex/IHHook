//mgsvtpp_hook_stubs.cpp
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteHookStubsFile
//Not intended to be compiled, this is just stub/examples of hook functions
//so you can quickly just copy and paste them to get started.
//only generated for ExportInfo entries that have usingHook True

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
	
		return lua::lua_newstate(f, ud);
	}//lua_newstateHook
	
	lua_State * lua_newthreadHook(lua_State * L) {
	
		return lua::lua_newthread(L);
	}//lua_newthreadHook
	
	lua_CFunction lua_atpanicHook(lua_State * L, lua_CFunction panicf) {
	
		return lua::lua_atpanic(L, panicf);
	}//lua_atpanicHook
	
	int lua_pcallHook(lua_State * L, int nargs, int nresults, int errfunc) {
	
		return lua::lua_pcall(L, nargs, nresults, errfunc);
	}//lua_pcallHook
	
	int lua_cpcallHook(lua_State * L, lua_CFunction func, void * ud) {
	
		return lua::lua_cpcall(L, func, ud);
	}//lua_cpcallHook
	
	int lua_loadHook(lua_State * L, lua_Reader reader, void * dt, const char * chunkname) {
	
		return lua::lua_load(L, reader, dt, chunkname);
	}//lua_loadHook
	
	int lua_errorHook(lua_State * L) {
	
		return lua::lua_error(L);
	}//lua_errorHook
	
	int luaL_loadbufferHook(lua_State * L, const char * buff, size_t sz, const char * name) {
	
		return lua::luaL_loadbuffer(L, buff, sz, name);
	}//luaL_loadbufferHook
	
	void luaL_openlibsHook(lua_State * L) {
	
		lua::luaL_openlibs(L);
	}//luaL_openlibsHook
	

	void CreateHooks() {
		CREATEHOOK(GetStrCodeWithLength,GetStrCodeWithLengthHook)
		ENABLEHOOK(GetStrCodeWithLength)
		
		CREATEHOOK(GetStrCode32,GetStrCode32Hook)
		ENABLEHOOK(GetStrCode32)
		
		CREATEHOOK(PathCode64Ext,PathCode64ExtHook)
		ENABLEHOOK(PathCode64Ext)
		
		CREATEHOOK(FNVHash32,FNVHash32Hook)
		ENABLEHOOK(FNVHash32)
		
		CREATEHOOK(GetFreeRoamLangId,GetFreeRoamLangIdHook)
		ENABLEHOOK(GetFreeRoamLangId)
		
		CREATEHOOK(UpdateFOVLerp,UpdateFOVLerpHook)
		ENABLEHOOK(UpdateFOVLerp)
		
		CREATEHOOK(UnkPrintFuncStubbedOut,UnkPrintFuncStubbedOutHook)
		ENABLEHOOK(UnkPrintFuncStubbedOut)
		
		CREATEHOOK(LoadFile,LoadFileHook)
		ENABLEHOOK(LoadFile)
		
		CREATEHOOK(LoadFileSub,LoadFileSubHook)
		ENABLEHOOK(LoadFileSub)
		
		CREATEHOOK(Path_Copy,Path_CopyHook)
		ENABLEHOOK(Path_Copy)
		
		CREATEHOOK(GetEmptyPath,GetEmptyPathHook)
		ENABLEHOOK(GetEmptyPath)
		
		CREATEHOOK(LoadPlayerPartsFpk,LoadPlayerPartsFpkHook)
		ENABLEHOOK(LoadPlayerPartsFpk)
		
		CREATEHOOK(LoadPlayerPartsParts,LoadPlayerPartsPartsHook)
		ENABLEHOOK(LoadPlayerPartsParts)
		
		CREATEHOOK(LoadPlayerCamoFpk,LoadPlayerCamoFpkHook)
		ENABLEHOOK(LoadPlayerCamoFpk)
		
		CREATEHOOK(LoadPlayerCamoFv2,LoadPlayerCamoFv2Hook)
		ENABLEHOOK(LoadPlayerCamoFv2)
		
		CREATEHOOK(LoadPlayerFacialMotionFpk,LoadPlayerFacialMotionFpkHook)
		ENABLEHOOK(LoadPlayerFacialMotionFpk)
		
		CREATEHOOK(LoadPlayerFacialMotionMtar,LoadPlayerFacialMotionMtarHook)
		ENABLEHOOK(LoadPlayerFacialMotionMtar)
		
		CREATEHOOK(LoadPlayerBionicArmFpk,LoadPlayerBionicArmFpkHook)
		ENABLEHOOK(LoadPlayerBionicArmFpk)
		
		CREATEHOOK(LoadPlayerBionicArmFv2,LoadPlayerBionicArmFv2Hook)
		ENABLEHOOK(LoadPlayerBionicArmFv2)
		
		CREATEHOOK(CheckPlayerPartsIfShouldApplySkinToneFv2,CheckPlayerPartsIfShouldApplySkinToneFv2Hook)
		ENABLEHOOK(CheckPlayerPartsIfShouldApplySkinToneFv2)
		
		CREATEHOOK(LoadPlayerPartsSkinToneFv2,LoadPlayerPartsSkinToneFv2Hook)
		ENABLEHOOK(LoadPlayerPartsSkinToneFv2)
		
		CREATEHOOK(IsHeadNeededForPartsType,IsHeadNeededForPartsTypeHook)
		ENABLEHOOK(IsHeadNeededForPartsType)
		
		CREATEHOOK(IsHeadNeededForPartsTypeAndAvatar,IsHeadNeededForPartsTypeAndAvatarHook)
		ENABLEHOOK(IsHeadNeededForPartsTypeAndAvatar)
		
		CREATEHOOK(LoadPlayerSnakeFaceFpk,LoadPlayerSnakeFaceFpkHook)
		ENABLEHOOK(LoadPlayerSnakeFaceFpk)
		
		CREATEHOOK(LoadPlayerSnakeFaceFv2,LoadPlayerSnakeFaceFv2Hook)
		ENABLEHOOK(LoadPlayerSnakeFaceFv2)
		
		CREATEHOOK(LoadAvatarOgreHornFpk,LoadAvatarOgreHornFpkHook)
		ENABLEHOOK(LoadAvatarOgreHornFpk)
		
		CREATEHOOK(LoadAvatarOgreHornFv2,LoadAvatarOgreHornFv2Hook)
		ENABLEHOOK(LoadAvatarOgreHornFv2)
		
		CREATEHOOK(LoadBuddyMainFile,LoadBuddyMainFileHook)
		ENABLEHOOK(LoadBuddyMainFile)
		
		CREATEHOOK(LoadBuddyQuietWeaponFpk,LoadBuddyQuietWeaponFpkHook)
		ENABLEHOOK(LoadBuddyQuietWeaponFpk)
		
		CREATEHOOK(LoadBuddyDogCommonFPK,LoadBuddyDogCommonFPKHook)
		ENABLEHOOK(LoadBuddyDogCommonFPK)
		
		CREATEHOOK(LoadBuddyHorseCommonFPK,LoadBuddyHorseCommonFPKHook)
		ENABLEHOOK(LoadBuddyHorseCommonFPK)
		
		CREATEHOOK(LoadBuddyWalkerGearArmFpk,LoadBuddyWalkerGearArmFpkHook)
		ENABLEHOOK(LoadBuddyWalkerGearArmFpk)
		
		CREATEHOOK(LoadBuddyWalkerGearHeadFpk,LoadBuddyWalkerGearHeadFpkHook)
		ENABLEHOOK(LoadBuddyWalkerGearHeadFpk)
		
		CREATEHOOK(LoadBuddyWalkerGearWeaponFpk,LoadBuddyWalkerGearWeaponFpkHook)
		ENABLEHOOK(LoadBuddyWalkerGearWeaponFpk)
		
		CREATEHOOK(LoadDefaultFpksFunc,LoadDefaultFpksFuncHook)
		ENABLEHOOK(LoadDefaultFpksFunc)
		
		CREATEHOOK(PreparePlayerVehicleInSortie,PreparePlayerVehicleInSortieHook)
		ENABLEHOOK(PreparePlayerVehicleInSortie)
		
		CREATEHOOK(PreparePlayerVehicleInGame,PreparePlayerVehicleInGameHook)
		ENABLEHOOK(PreparePlayerVehicleInGame)
		
		CREATEHOOK(LoadDefaultFpkPtrFunc,LoadDefaultFpkPtrFuncHook)
		ENABLEHOOK(LoadDefaultFpkPtrFunc)
		
		CREATEHOOK(LoadAllVehicleCamoFpks,LoadAllVehicleCamoFpksHook)
		ENABLEHOOK(LoadAllVehicleCamoFpks)
		
		CREATEHOOK(BuddyCommandGetNameLangId,BuddyCommandGetNameLangIdHook)
		ENABLEHOOK(BuddyCommandGetNameLangId)
		
		CREATEHOOK(BuddyCommandGetDescriptionLangId,BuddyCommandGetDescriptionLangIdHook)
		ENABLEHOOK(BuddyCommandGetDescriptionLangId)
		
		CREATEHOOK(foxlua::NewModule,NewModuleHook)
		ENABLEHOOK(foxlua::NewModule)
		
		CREATEHOOK(foxlua::NewSubModule,NewSubModuleHook)
		ENABLEHOOK(foxlua::NewSubModule)
		
		CREATEHOOK(foxlua::AddCFuncToModule,AddCFuncToModuleHook)
		ENABLEHOOK(foxlua::AddCFuncToModule)
		
		CREATEHOOK(foxlua::AddCFuncToModule2,AddCFuncToModule2Hook)
		ENABLEHOOK(foxlua::AddCFuncToModule2)
		
		CREATEHOOK(foxlua::AddCFuncToModule3,AddCFuncToModule3Hook)
		ENABLEHOOK(foxlua::AddCFuncToModule3)
		
		CREATEHOOK(foxlua::AddEnumToModule,AddEnumToModuleHook)
		ENABLEHOOK(foxlua::AddEnumToModule)
		
		CREATEHOOK(foxlua::AddEnumToModule2,AddEnumToModule2Hook)
		ENABLEHOOK(foxlua::AddEnumToModule2)
		
		CREATEHOOK(foxlua::AddEnumToModule3,AddEnumToModule3Hook)
		ENABLEHOOK(foxlua::AddEnumToModule3)
		
		CREATEHOOK(foxlua::AddEnumToModule4,AddEnumToModule4Hook)
		ENABLEHOOK(foxlua::AddEnumToModule4)
		
		CREATEHOOK(RegisterVar,RegisterVarHook)
		ENABLEHOOK(RegisterVar)
		
		CREATEHOOK(RegisterVar_01,RegisterVar_01Hook)
		ENABLEHOOK(RegisterVar_01)
		
		CREATEHOOK(RegisterVar_02,RegisterVar_02Hook)
		ENABLEHOOK(RegisterVar_02)
		
		CREATEHOOK(RegisterVar_03,RegisterVar_03Hook)
		ENABLEHOOK(RegisterVar_03)
		
		CREATEHOOK(RegisterVarArray,RegisterVarArrayHook)
		ENABLEHOOK(RegisterVarArray)
		
		CREATEHOOK(DeclareEntityClass,DeclareEntityClassHook)
		ENABLEHOOK(DeclareEntityClass)
		
		CREATEHOOK(lua::lua_newstate,lua_newstateHook)
		ENABLEHOOK(lua::lua_newstate)
		
		CREATEHOOK(lua::lua_newthread,lua_newthreadHook)
		ENABLEHOOK(lua::lua_newthread)
		
		CREATEHOOK(lua::lua_atpanic,lua_atpanicHook)
		ENABLEHOOK(lua::lua_atpanic)
		
		CREATEHOOK(lua::lua_pcall,lua_pcallHook)
		ENABLEHOOK(lua::lua_pcall)
		
		CREATEHOOK(lua::lua_cpcall,lua_cpcallHook)
		ENABLEHOOK(lua::lua_cpcall)
		
		CREATEHOOK(lua::lua_load,lua_loadHook)
		ENABLEHOOK(lua::lua_load)
		
		CREATEHOOK(lua::lua_error,lua_errorHook)
		ENABLEHOOK(lua::lua_error)
		
		CREATEHOOK(lua::luaL_loadbuffer,luaL_loadbufferHook)
		ENABLEHOOK(lua::luaL_loadbuffer)
		
		CREATEHOOK(lua::luaL_openlibs,luaL_openlibsHook)
		ENABLEHOOK(lua::luaL_openlibs)
		
		}//CreateHooks
}//namespace IHHook
