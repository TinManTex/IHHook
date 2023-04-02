#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteFuncTypeDefHFile
//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)

#include "mgsvtpp_func_typedefs_manual.h"
//TODO: this is a per category thing/will likely want to manage includes 
//as the number of functions being hooked with various data types expands
#include "lua/lua.h"
#include "lua/lauxlib.h"

typedef StrCode (__fastcall GetStrCodeWithLengthFunc)(const char * buf, longlong len);
typedef StrCode32 (__fastcall GetStrCode32Func)(const char * str);
typedef ulonglong (__fastcall PathCode64ExtFunc)(const char * inString);
typedef uint (__fastcall FNVHash32Func)(const char * strToHash);
typedef ulonglong * (__fastcall GetFreeRoamLangIdFunc)(ulonglong * langId, short locationCode, short missionCode);
typedef void (__fastcall UpdateFOVLerpFunc)(ulonglong param_1);
typedef void (__fastcall UnkPrintFuncStubbedOutFunc)(const char * fmt, void * param_2, void * param_3, void * param_4);
// l_StubbedOut EXPORT_FUNC_FALSE
// nullsub_2 EXPORT_FUNC_FALSE
typedef ulonglong * (__fastcall LoadFileFunc)(ulonglong * fileSlotIndex, ulonglong filePath64);
typedef void (__fastcall LoadFileSubFunc)(PathCode64 pathA, PathCode64 pathB);
typedef Path * (__thiscall Path_CopyFunc)(Path * This, Path * rhs);
typedef Path * (__fastcall GetEmptyPathFunc)();
typedef ulonglong * (__fastcall LoadPlayerPartsFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType);
typedef ulonglong * (__fastcall LoadPlayerPartsPartsFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType);
typedef ulonglong * (__fastcall LoadPlayerCamoFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType);
typedef ulonglong * (__fastcall LoadPlayerCamoFv2Func)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType);
typedef ulonglong * (__fastcall LoadPlayerFacialMotionFpkFunc)(ulonglong * fileSlotIndex, uint playerType);
typedef ulonglong * (__fastcall LoadPlayerFacialMotionMtarFunc)(ulonglong * fileSlotIndex, int playerType);
typedef ulonglong * (__fastcall LoadPlayerBionicArmFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType);
typedef ulonglong * (__fastcall LoadPlayerBionicArmFv2Func)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType);
typedef bool (__fastcall CheckPlayerPartsIfShouldApplySkinToneFv2Func)(uint playerType, uint playerPartsType);
typedef ulonglong * (__fastcall LoadPlayerPartsSkinToneFv2Func)(ulonglong * loadFile, uint playerType, uint playerPartsType);
typedef bool (__fastcall IsHeadNeededForPartsTypeFunc)(uint playerPartsType);
typedef bool (__fastcall IsHeadNeededForPartsTypeAndAvatarFunc)(uint playerPartsType);
typedef ulonglong * (__fastcall LoadPlayerSnakeFaceFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId);
typedef ulonglong * (__fastcall LoadPlayerSnakeFaceFv2Func)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId);
typedef ulonglong * (__fastcall LoadAvatarOgreHornFpkFunc)(ulonglong * fileSlotIndex, uint ogreLevel);
typedef ulonglong * (__fastcall LoadAvatarOgreHornFv2Func)(ulonglong * fileSlotIndex, uint ogreLevel);
typedef ulonglong * (__fastcall LoadBuddyMainFileFunc)(ulonglong param_1, ulonglong * fileSlotIndex, uint buddyType, ulonglong param_4);
typedef ulonglong * (__fastcall LoadBuddyQuietWeaponFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, short param_quietWeaponId);
typedef void (__fastcall LoadBuddyDogCommonFPKFunc)(longlong param_1, ulonglong * fileSlotIndex);
typedef void (__fastcall LoadBuddyHorseCommonFPKFunc)(longlong param_1, ulonglong * fileSlotIndex);
typedef ulonglong * (__fastcall LoadBuddyWalkerGearArmFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4);
typedef ulonglong * (__fastcall LoadBuddyWalkerGearHeadFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4);
typedef ulonglong * (__fastcall LoadBuddyWalkerGearWeaponFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4);
typedef int * (__fastcall LoadDefaultFpksFuncFunc)(void * param_1, int * param_2, ulonglong * param_3, uint param_4);
typedef char (__fastcall PreparePlayerVehicleInSortieFunc)(longlong param_1);
typedef char (__fastcall PreparePlayerVehicleInGameFunc)(longlong param_1, ulonglong param_2);
typedef longlong (__fastcall LoadDefaultFpkPtrFuncFunc)(longlong param_1, uint param_2);
typedef ulonglong * (__fastcall LoadAllVehicleCamoFpksFunc)();
typedef longlong * (__fastcall BuddyCommandGetNameLangIdFunc)(longlong * langId, uint commandType);
typedef longlong * (__fastcall BuddyCommandGetDescriptionLangIdFunc)(longlong * langId, uint commandType);
typedef foxlua::module * (__fastcall NewModuleFunc)(undefined8 param_1, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5);
typedef foxlua::module * (__fastcall NewSubModuleFunc)(foxlua::module * parentModule, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5);
typedef int (__fastcall AddCFuncToModuleFunc)(foxlua::module * module, const char * funcName, lua_CFunction cfunc, undefined8 param_4, int param_5, void * param_6);
typedef int (__fastcall AddCFuncToModule2Func)(foxlua::module * module, const char * funcName, void * param_3);
typedef undefined8 (__fastcall AddCFuncToModule3Func)(foxlua::module * moduleName, const char * funcName, lua_CFunction param_3, int param_4, void * param_5);
typedef void (__fastcall AddEnumToModuleFunc)(foxlua::module * foxModule, const char * enumName, int enumValue);
typedef bool (__fastcall AddEnumToModule2Func)(foxlua::module * module, const char * enumName, int * enumValue);
typedef void (__fastcall AddEnumToModule3Func)(foxlua::module * module, const char * enumName, undefined8 enumValue);
typedef undefined (__fastcall AddEnumToModule4Func)(undefined8 module, undefined8 enumName, undefined8 enumValue);
typedef undefined (__fastcall RegisterVarFunc)(undefined8 foxLua, const char * varName, undefined8 varAddress, lua_CFunction * luaCFunc);
typedef void (__fastcall RegisterVar_01Func)(longlong param_1, const char * varName, undefined4 param_3, undefined8 param_4, undefined2 param_5, undefined param_6);
typedef void (__fastcall RegisterVar_02Func)(undefined8 param_1, const char * varName, undefined8 param_3, char param_4);
typedef int (__fastcall RegisterVar_03Func)(foxlua::module * param_1, const char * varName, void * varAddress, lua_CFunction unkLuaCFunc);
typedef bool (__fastcall RegisterVarArrayFunc)(foxlua::module * module, const char * varName, lua_CFunction param_3, lua_CFunction param_4, undefined8 param_5, undefined * param_6, undefined * param_7, undefined8 arraySize);
typedef undefined4 * (__fastcall DeclareEntityClassFunc)(undefined4 * param_1, const char * className, longlong entityInfo);
typedef lua_State * (__fastcall lua_newstateFunc)(lua_Alloc f, void * ud);
typedef void (__fastcall lua_closeFunc)(lua_State * L);
typedef lua_State * (__fastcall lua_newthreadFunc)(lua_State * L);
typedef lua_CFunction (__fastcall lua_atpanicFunc)(lua_State * L, lua_CFunction panicf);
// lua_gettop USING_CODE
typedef void (__fastcall lua_settopFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_pushvalueFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_removeFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_insertFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_replaceFunc)(lua_State * L, int idx);
typedef int (__fastcall lua_checkstackFunc)(lua_State * L, int sz);
typedef void (__fastcall lua_xmoveFunc)(lua_State * from, lua_State * to, int n);
typedef int (__fastcall lua_isnumberFunc)(lua_State * L, int idx);
typedef int (__fastcall lua_isstringFunc)(lua_State * L, int idx);
typedef int (__fastcall lua_iscfunctionFunc)(lua_State * L, int idx);
// lua_isuserdata USING_CODE
typedef int (__fastcall lua_typeFunc)(lua_State * L, int idx);
// lua_typename USING_CODE
// lua_equal NOT_FOUND
typedef int (__fastcall lua_rawequalFunc)(lua_State * L, int idx1, int idx2);
typedef int (__fastcall lua_lessthanFunc)(lua_State * L, int idx1, int idx2);
typedef lua_Number (__fastcall lua_tonumberFunc)(lua_State * L, int idx);
typedef lua_Integer (__fastcall lua_tointegerFunc)(lua_State * L, int idx);
typedef int (__fastcall lua_tobooleanFunc)(lua_State * L, int idx);
typedef char * (__fastcall lua_tolstringFunc)(lua_State * L, int idx, size_t * len);
typedef size_t (__fastcall lua_objlenFunc)(lua_State * L, int idx);
typedef lua_CFunction (__fastcall lua_tocfunctionFunc)(lua_State * L, int idx);
typedef void * (__fastcall lua_touserdataFunc)(lua_State * L, int idx);
typedef lua_State * (__fastcall lua_tothreadFunc)(lua_State * L, int idx);
typedef void * (__fastcall lua_topointerFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_pushnilFunc)(lua_State * L);
typedef void (__fastcall lua_pushnumberFunc)(lua_State * L, lua_Number n);
typedef void (__fastcall lua_pushintegerFunc)(lua_State * L, lua_Integer n);
typedef void (__fastcall lua_pushlstringFunc)(lua_State * L, const char * s, size_t l);
typedef void (__fastcall lua_pushstringFunc)(lua_State * L, const char * s);
typedef char * (__fastcall lua_pushvfstringFunc)(lua_State * L, const char * fmt, void * argp);
typedef char * (__fastcall lua_pushfstringFunc)(lua_State * L, const char * fmt, ...);
typedef void (__fastcall lua_pushcclosureFunc)(lua_State * L, lua_CFunction fn, int n);
typedef void (__fastcall lua_pushbooleanFunc)(lua_State * L, int b);
typedef void (__fastcall lua_pushlightuserdataFunc)(lua_State * L, void * p);
typedef int (__fastcall lua_pushthreadFunc)(lua_State * L);
typedef void (__fastcall lua_gettableFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_getfieldFunc)(lua_State * L, int idx, const char * k);
typedef void (__fastcall lua_rawgetFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_rawgetiFunc)(lua_State * L, int idx, int n);
typedef void (__fastcall lua_createtableFunc)(lua_State * L, int narr, int nrec);
typedef void * (__fastcall lua_newuserdataFunc)(lua_State * L, size_t sz);
typedef int (__fastcall lua_getmetatableFunc)(lua_State * L, int objindex);
typedef void (__fastcall lua_getfenvFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_settableFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_setfieldFunc)(lua_State * L, int idx, const char * k);
typedef void (__fastcall lua_rawsetFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_rawsetiFunc)(lua_State * L, int idx, int n);
typedef int (__fastcall lua_setmetatableFunc)(lua_State * L, int objindex);
typedef int (__fastcall lua_setfenvFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_callFunc)(lua_State * L, int nargs, int nresults);
typedef int (__fastcall lua_pcallFunc)(lua_State * L, int nargs, int nresults, int errfunc);
typedef int (__fastcall lua_cpcallFunc)(lua_State * L, lua_CFunction func, void * ud);
typedef int (__fastcall lua_loadFunc)(lua_State * L, lua_Reader reader, void * dt, const char * chunkname);
typedef int (__fastcall lua_dumpFunc)(lua_State * L, lua_Writer writer, void * data);
// lua_yield USING_CODE
typedef int (__fastcall lua_resumeFunc)(lua_State * L, int narg);
// lua_status USING_CODE
typedef int (__fastcall lua_gcFunc)(lua_State * L, int what, int data);
typedef int (__fastcall lua_errorFunc)(lua_State * L);
typedef int (__fastcall lua_nextFunc)(lua_State * L, int idx);
typedef void (__fastcall lua_concatFunc)(lua_State * L, int n);
// lua_getallocf NO_USE
// lua_setallocf NO_USE
// lua_setlevel NO_USE
typedef int (__fastcall lua_getstackFunc)(lua_State * L, int level, lua_Debug * ar);
typedef int (__fastcall lua_getinfoFunc)(lua_State * L, const char * what, lua_Debug * ar);
typedef char * (__fastcall lua_getlocalFunc)(lua_State * L, lua_Debug * ar, int n);
typedef char * (__fastcall lua_setlocalFunc)(lua_State * L, lua_Debug * ar, int n);
typedef char * (__fastcall lua_getupvalueFunc)(lua_State * L, int funcindex, int n);
typedef char * (__fastcall lua_setupvalueFunc)(lua_State * L, int funcindex, int n);
typedef int (__fastcall lua_sethookFunc)(lua_State * L, lua_Hook func, int mask, int count);
// lua_gethook USING_CODE
// lua_gethookmask USING_CODE
// lua_gethookcount USING_CODE
typedef void (__fastcall luaI_openlibFunc)(lua_State * L, const char * libName, const luaL_Reg * l, int nup);
// luaL_register USING_CODE
typedef int (__fastcall luaL_getmetafieldFunc)(lua_State * L, int obj, const char * e);
typedef int (__fastcall luaL_callmetaFunc)(lua_State * L, int obj, const char * e);
typedef int (__fastcall luaL_typerrorFunc)(lua_State * L, int narg, const char * tname);
typedef int (__fastcall luaL_argerrorFunc)(lua_State * L, int numarg, const char * extramsg);
typedef char * (__fastcall luaL_checklstringFunc)(lua_State * L, int numArg, size_t * l);
typedef char * (__fastcall luaL_optlstringFunc)(lua_State * L, int numArg, const char * def, size_t * l);
typedef lua_Number (__fastcall luaL_checknumberFunc)(lua_State * L, int numArg);
// luaL_optnumber USING_CODE
typedef lua_Integer (__fastcall luaL_checkintegerFunc)(lua_State * L, int numArg);
typedef lua_Integer (__fastcall luaL_optintegerFunc)(lua_State * L, int nArg, lua_Integer def);
typedef void (__fastcall luaL_checkstackFunc)(lua_State * L, int sz, const char * msg);
typedef void (__fastcall luaL_checktypeFunc)(lua_State * L, int narg, int t);
typedef void (__fastcall luaL_checkanyFunc)(lua_State * L, int narg);
typedef int (__fastcall luaL_newmetatableFunc)(lua_State * L, const char * tname);
typedef void * (__fastcall luaL_checkudataFunc)(lua_State * L, int ud, const char * tname);
typedef void (__fastcall luaL_whereFunc)(lua_State * L, int lvl);
typedef int (__fastcall luaL_errorFunc)(lua_State * L, const char * fmt, ...);
typedef int (__fastcall luaL_checkoptionFunc)(lua_State * L, int narg, const char * def, char * * lst);
// luaL_ref USING_CODE
// luaL_unref USING_CODE
typedef int (__fastcall luaL_loadfileFunc)(lua_State * L, const char * filename);
typedef int (__fastcall luaL_loadbufferFunc)(lua_State * L, const char * buff, size_t sz, const char * name);
// luaL_loadstring USING_CODE
typedef lua_State * (__fastcall luaL_newstateFunc)();
typedef char * (__fastcall luaL_gsubFunc)(lua_State * L, const char * s, const char * p, const char * r);
typedef char * (__fastcall luaL_findtableFunc)(lua_State * L, int idx, const char * fname, int szhint);
// luaL_buffinit USING_CODE
typedef char * (__fastcall luaL_prepbufferFunc)(luaL_Buffer * B);
typedef void (__fastcall luaL_addlstringFunc)(luaL_Buffer * B, const char * s, size_t l);
// luaL_addstring USING_CODE
typedef void (__fastcall luaL_addvalueFunc)(luaL_Buffer * B);
typedef void (__fastcall luaL_pushresultFunc)(luaL_Buffer * B);
typedef int (__fastcall luaopen_baseFunc)(lua_State * L);
typedef int (__fastcall luaopen_tableFunc)(lua_State * L);
typedef int (__fastcall luaopen_ioFunc)(lua_State * L);
typedef int (__fastcall luaopen_osFunc)(lua_State * L);
typedef int (__fastcall luaopen_stringFunc)(lua_State * L);
typedef int (__fastcall luaopen_mathFunc)(lua_State * L);
typedef int (__fastcall luaopen_debugFunc)(lua_State * L);
typedef int (__fastcall luaopen_packageFunc)(lua_State * L);
typedef void (__fastcall luaL_openlibsFunc)(lua_State * L);

//tex the (extern of the) function pointers
extern GetStrCodeWithLengthFunc* GetStrCodeWithLength;
extern GetStrCode32Func* GetStrCode32;
extern PathCode64ExtFunc* PathCode64Ext;
extern FNVHash32Func* FNVHash32;
extern GetFreeRoamLangIdFunc* GetFreeRoamLangId;
extern UpdateFOVLerpFunc* UpdateFOVLerp;
extern UnkPrintFuncStubbedOutFunc* UnkPrintFuncStubbedOut;
extern l_StubbedOutFunc* l_StubbedOut;
extern nullsub_2Func* nullsub_2;
extern LoadFileFunc* LoadFile;
extern LoadFileSubFunc* LoadFileSub;
extern Path_CopyFunc* Path_Copy;
extern GetEmptyPathFunc* GetEmptyPath;
extern LoadPlayerPartsFpkFunc* LoadPlayerPartsFpk;
extern LoadPlayerPartsPartsFunc* LoadPlayerPartsParts;
extern LoadPlayerCamoFpkFunc* LoadPlayerCamoFpk;
extern LoadPlayerCamoFv2Func* LoadPlayerCamoFv2;
extern LoadPlayerFacialMotionFpkFunc* LoadPlayerFacialMotionFpk;
extern LoadPlayerFacialMotionMtarFunc* LoadPlayerFacialMotionMtar;
extern LoadPlayerBionicArmFpkFunc* LoadPlayerBionicArmFpk;
extern LoadPlayerBionicArmFv2Func* LoadPlayerBionicArmFv2;
extern CheckPlayerPartsIfShouldApplySkinToneFv2Func* CheckPlayerPartsIfShouldApplySkinToneFv2;
extern LoadPlayerPartsSkinToneFv2Func* LoadPlayerPartsSkinToneFv2;
extern IsHeadNeededForPartsTypeFunc* IsHeadNeededForPartsType;
extern IsHeadNeededForPartsTypeAndAvatarFunc* IsHeadNeededForPartsTypeAndAvatar;
extern LoadPlayerSnakeFaceFpkFunc* LoadPlayerSnakeFaceFpk;
extern LoadPlayerSnakeFaceFv2Func* LoadPlayerSnakeFaceFv2;
extern LoadAvatarOgreHornFpkFunc* LoadAvatarOgreHornFpk;
extern LoadAvatarOgreHornFv2Func* LoadAvatarOgreHornFv2;
extern LoadBuddyMainFileFunc* LoadBuddyMainFile;
extern LoadBuddyQuietWeaponFpkFunc* LoadBuddyQuietWeaponFpk;
extern LoadBuddyDogCommonFPKFunc* LoadBuddyDogCommonFPK;
extern LoadBuddyHorseCommonFPKFunc* LoadBuddyHorseCommonFPK;
extern LoadBuddyWalkerGearArmFpkFunc* LoadBuddyWalkerGearArmFpk;
extern LoadBuddyWalkerGearHeadFpkFunc* LoadBuddyWalkerGearHeadFpk;
extern LoadBuddyWalkerGearWeaponFpkFunc* LoadBuddyWalkerGearWeaponFpk;
extern LoadDefaultFpksFuncFunc* LoadDefaultFpksFunc;
extern PreparePlayerVehicleInSortieFunc* PreparePlayerVehicleInSortie;
extern PreparePlayerVehicleInGameFunc* PreparePlayerVehicleInGame;
extern LoadDefaultFpkPtrFuncFunc* LoadDefaultFpkPtrFunc;
extern LoadAllVehicleCamoFpksFunc* LoadAllVehicleCamoFpks;
extern BuddyCommandGetNameLangIdFunc* BuddyCommandGetNameLangId;
extern BuddyCommandGetDescriptionLangIdFunc* BuddyCommandGetDescriptionLangId;
extern NewModuleFunc* NewModule;
extern NewSubModuleFunc* NewSubModule;
extern AddCFuncToModuleFunc* AddCFuncToModule;
extern AddCFuncToModule2Func* AddCFuncToModule2;
extern AddCFuncToModule3Func* AddCFuncToModule3;
extern AddEnumToModuleFunc* AddEnumToModule;
extern AddEnumToModule2Func* AddEnumToModule2;
extern AddEnumToModule3Func* AddEnumToModule3;
extern AddEnumToModule4Func* AddEnumToModule4;
extern RegisterVarFunc* RegisterVar;
extern RegisterVar_01Func* RegisterVar_01;
extern RegisterVar_02Func* RegisterVar_02;
extern RegisterVar_03Func* RegisterVar_03;
extern RegisterVarArrayFunc* RegisterVarArray;
extern DeclareEntityClassFunc* DeclareEntityClass;
extern lua_newstateFunc* lua_newstate;
extern lua_closeFunc* lua_close;
extern lua_newthreadFunc* lua_newthread;
extern lua_atpanicFunc* lua_atpanic;
//extern lua_gettopFunc* lua_gettop;//USING_CODE
extern lua_settopFunc* lua_settop;
extern lua_pushvalueFunc* lua_pushvalue;
extern lua_removeFunc* lua_remove;
extern lua_insertFunc* lua_insert;
extern lua_replaceFunc* lua_replace;
extern lua_checkstackFunc* lua_checkstack;
extern lua_xmoveFunc* lua_xmove;
extern lua_isnumberFunc* lua_isnumber;
extern lua_isstringFunc* lua_isstring;
extern lua_iscfunctionFunc* lua_iscfunction;
//extern lua_isuserdataFunc* lua_isuserdata;//USING_CODE
extern lua_typeFunc* lua_type;
//extern lua_typenameFunc* lua_typename;//USING_CODE
//extern lua_equalFunc* lua_equal;//NOT_FOUND
extern lua_rawequalFunc* lua_rawequal;
extern lua_lessthanFunc* lua_lessthan;
extern lua_tonumberFunc* lua_tonumber;
extern lua_tointegerFunc* lua_tointeger;
extern lua_tobooleanFunc* lua_toboolean;
extern lua_tolstringFunc* lua_tolstring;
extern lua_objlenFunc* lua_objlen;
extern lua_tocfunctionFunc* lua_tocfunction;
extern lua_touserdataFunc* lua_touserdata;
extern lua_tothreadFunc* lua_tothread;
extern lua_topointerFunc* lua_topointer;
extern lua_pushnilFunc* lua_pushnil;
extern lua_pushnumberFunc* lua_pushnumber;
extern lua_pushintegerFunc* lua_pushinteger;
extern lua_pushlstringFunc* lua_pushlstring;
extern lua_pushstringFunc* lua_pushstring;
extern lua_pushvfstringFunc* lua_pushvfstring;
extern lua_pushfstringFunc* lua_pushfstring;
extern lua_pushcclosureFunc* lua_pushcclosure;
extern lua_pushbooleanFunc* lua_pushboolean;
extern lua_pushlightuserdataFunc* lua_pushlightuserdata;
extern lua_pushthreadFunc* lua_pushthread;
extern lua_gettableFunc* lua_gettable;
extern lua_getfieldFunc* lua_getfield;
extern lua_rawgetFunc* lua_rawget;
extern lua_rawgetiFunc* lua_rawgeti;
extern lua_createtableFunc* lua_createtable;
extern lua_newuserdataFunc* lua_newuserdata;
extern lua_getmetatableFunc* lua_getmetatable;
extern lua_getfenvFunc* lua_getfenv;
extern lua_settableFunc* lua_settable;
extern lua_setfieldFunc* lua_setfield;
extern lua_rawsetFunc* lua_rawset;
extern lua_rawsetiFunc* lua_rawseti;
extern lua_setmetatableFunc* lua_setmetatable;
extern lua_setfenvFunc* lua_setfenv;
extern lua_callFunc* lua_call;
extern lua_pcallFunc* lua_pcall;
extern lua_cpcallFunc* lua_cpcall;
extern lua_loadFunc* lua_load;
extern lua_dumpFunc* lua_dump;
//extern lua_yieldFunc* lua_yield;//USING_CODE
extern lua_resumeFunc* lua_resume;
//extern lua_statusFunc* lua_status;//USING_CODE
extern lua_gcFunc* lua_gc;
extern lua_errorFunc* lua_error;
extern lua_nextFunc* lua_next;
extern lua_concatFunc* lua_concat;
//extern lua_getallocfFunc* lua_getallocf;//NO_USE
//extern lua_setallocfFunc* lua_setallocf;//NO_USE
//extern lua_setlevelFunc* lua_setlevel;//NO_USE
extern lua_getstackFunc* lua_getstack;
extern lua_getinfoFunc* lua_getinfo;
extern lua_getlocalFunc* lua_getlocal;
extern lua_setlocalFunc* lua_setlocal;
extern lua_getupvalueFunc* lua_getupvalue;
extern lua_setupvalueFunc* lua_setupvalue;
extern lua_sethookFunc* lua_sethook;
//extern lua_gethookFunc* lua_gethook;//USING_CODE
//extern lua_gethookmaskFunc* lua_gethookmask;//USING_CODE
//extern lua_gethookcountFunc* lua_gethookcount;//USING_CODE
extern luaI_openlibFunc* luaI_openlib;
//extern luaL_registerFunc* luaL_register;//USING_CODE
extern luaL_getmetafieldFunc* luaL_getmetafield;
extern luaL_callmetaFunc* luaL_callmeta;
extern luaL_typerrorFunc* luaL_typerror;
extern luaL_argerrorFunc* luaL_argerror;
extern luaL_checklstringFunc* luaL_checklstring;
extern luaL_optlstringFunc* luaL_optlstring;
extern luaL_checknumberFunc* luaL_checknumber;
//extern luaL_optnumberFunc* luaL_optnumber;//USING_CODE
extern luaL_checkintegerFunc* luaL_checkinteger;
extern luaL_optintegerFunc* luaL_optinteger;
extern luaL_checkstackFunc* luaL_checkstack;
extern luaL_checktypeFunc* luaL_checktype;
extern luaL_checkanyFunc* luaL_checkany;
extern luaL_newmetatableFunc* luaL_newmetatable;
extern luaL_checkudataFunc* luaL_checkudata;
extern luaL_whereFunc* luaL_where;
extern luaL_errorFunc* luaL_error;
extern luaL_checkoptionFunc* luaL_checkoption;
//extern luaL_refFunc* luaL_ref;//USING_CODE
//extern luaL_unrefFunc* luaL_unref;//USING_CODE
extern luaL_loadfileFunc* luaL_loadfile;
extern luaL_loadbufferFunc* luaL_loadbuffer;
//extern luaL_loadstringFunc* luaL_loadstring;//USING_CODE
extern luaL_newstateFunc* luaL_newstate;
extern luaL_gsubFunc* luaL_gsub;
extern luaL_findtableFunc* luaL_findtable;
//extern luaL_buffinitFunc* luaL_buffinit;//USING_CODE
extern luaL_prepbufferFunc* luaL_prepbuffer;
extern luaL_addlstringFunc* luaL_addlstring;
//extern luaL_addstringFunc* luaL_addstring;//USING_CODE
extern luaL_addvalueFunc* luaL_addvalue;
extern luaL_pushresultFunc* luaL_pushresult;
extern luaopen_baseFunc* luaopen_base;
extern luaopen_tableFunc* luaopen_table;
extern luaopen_ioFunc* luaopen_io;
extern luaopen_osFunc* luaopen_os;
extern luaopen_stringFunc* luaopen_string;
extern luaopen_mathFunc* luaopen_math;
extern luaopen_debugFunc* luaopen_debug;
extern luaopen_packageFunc* luaopen_package;
extern luaL_openlibsFunc* luaL_openlibs;

