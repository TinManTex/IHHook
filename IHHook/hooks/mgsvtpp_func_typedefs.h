#pragma once
//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteFuncTypeDefHFile
//Typdefs and externs for the function pointers as well as detour function declaration (not func ptrs)

#include "mgsvtpp_func_typedefs_manual.h"
//TODO: this is a per category thing/will likely want to manage includes 
//as the number of functions being hooked with various data types expands
#include "lua/lua.h"
#include "lua/lauxlib.h"

namespace fox::StrCode {
typedef StrCode (__fastcall GetStrCodeWithLengthFunc)(const char * buf, longlong len);
}
namespace fox::StrCode32 {
typedef StrCode32 (__fastcall GetStrCode32Func)(const char * str);
}
typedef ulonglong (__fastcall PathCode64ExtFunc)(const char * inString);
typedef uint (__fastcall FNVHash32Func)(const char * strToHash);
namespace ui::lang {
typedef ulonglong * (__fastcall GetFreeRoamLangIdFunc)(ulonglong * langId, short locationCode, short missionCode);
}
typedef void (__fastcall UpdateFOVLerpFunc)(ulonglong param_1);
typedef void (__fastcall UnkPrintFuncStubbedOutFunc)(const char * fmt, void * param_2, void * param_3, void * param_4);
// l_StubbedOut EXPORT_FUNC_FALSE
// nullsub_2 EXPORT_FUNC_FALSE
namespace files {
typedef ulonglong * (__fastcall LoadFileFunc)(ulonglong * fileSlotIndex, ulonglong filePath64);
}
namespace files {
typedef void (__fastcall LoadFileSubFunc)(PathCode64 pathA, PathCode64 pathB);
}
typedef Path * (__thiscall Path_CopyFunc)(Path * This, Path * rhs);
namespace fox::PathManager {
typedef Path * (__fastcall GetEmptyPathFunc)();
}
namespace player::appearance::parts {
typedef ulonglong * (__fastcall LoadPlayerPartsFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType);
}
namespace player::appearance::parts {
typedef ulonglong * (__fastcall LoadPlayerPartsPartsFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType);
}
namespace player::appearance::fova::camo {
typedef ulonglong * (__fastcall LoadPlayerCamoFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType);
}
namespace player::appearance::fova::camo {
typedef ulonglong * (__fastcall LoadPlayerCamoFv2Func)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerCamoType);
}
namespace player::motion::facial {
typedef ulonglong * (__fastcall LoadPlayerFacialMotionFpkFunc)(ulonglong * fileSlotIndex, uint playerType);
}
namespace player::motion::facial {
typedef ulonglong * (__fastcall LoadPlayerFacialMotionMtarFunc)(ulonglong * fileSlotIndex, int playerType);
}
namespace player::appearance::fova::arm {
typedef ulonglong * (__fastcall LoadPlayerBionicArmFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType);
}
namespace player::appearance::fova::arm {
typedef ulonglong * (__fastcall LoadPlayerBionicArmFv2Func)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerHandType);
}
namespace player::appearance::fova::skinTone {
typedef bool (__fastcall CheckPlayerPartsIfShouldApplySkinToneFv2Func)(uint playerType, uint playerPartsType);
}
namespace player::appearance::fova::skinTone {
typedef ulonglong * (__fastcall LoadPlayerPartsSkinToneFv2Func)(ulonglong * loadFile, uint playerType, uint playerPartsType);
}
namespace player::appearance {
typedef bool (__fastcall IsHeadNeededForPartsTypeFunc)(uint playerPartsType);
}
namespace player::appearance {
typedef bool (__fastcall IsHeadNeededForPartsTypeAndAvatarFunc)(uint playerPartsType);
}
namespace player::appearance::fova::face {
typedef ulonglong * (__fastcall LoadPlayerSnakeFaceFpkFunc)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId);
}
namespace player::appearance::fova::face {
typedef ulonglong * (__fastcall LoadPlayerSnakeFaceFv2Func)(ulonglong * fileSlotIndex, uint playerType, uint playerPartsType, uint playerFaceId, char playerFaceEquipId);
}
namespace player::appearance::avatar {
typedef ulonglong * (__fastcall LoadAvatarOgreHornFpkFunc)(ulonglong * fileSlotIndex, uint ogreLevel);
}
namespace player::appearance::avatar {
typedef ulonglong * (__fastcall LoadAvatarOgreHornFv2Func)(ulonglong * fileSlotIndex, uint ogreLevel);
}
namespace buddy::system {
typedef ulonglong * (__fastcall LoadBuddyMainFileFunc)(ulonglong param_1, ulonglong * fileSlotIndex, uint buddyType, ulonglong param_4);
}
namespace buddy::quiet {
typedef ulonglong * (__fastcall LoadBuddyQuietWeaponFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, short param_quietWeaponId);
}
namespace buddy::dog {
typedef void (__fastcall LoadBuddyDogCommonFPKFunc)(longlong param_1, ulonglong * fileSlotIndex);
}
namespace buddy::horse {
typedef void (__fastcall LoadBuddyHorseCommonFPKFunc)(longlong param_1, ulonglong * fileSlotIndex);
}
namespace buddy::walker {
typedef ulonglong * (__fastcall LoadBuddyWalkerGearArmFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4);
}
namespace buddy::walker {
typedef ulonglong * (__fastcall LoadBuddyWalkerGearHeadFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4);
}
namespace buddy::walker {
typedef ulonglong * (__fastcall LoadBuddyWalkerGearWeaponFpkFunc)(ulonglong param_1, ulonglong * fileSlotIndex, ulonglong param_3, ulonglong param_4);
}
namespace FileLoadDefaultCommon {
typedef int * (__fastcall LoadDefaultFpksFuncFunc)(void * param_1, int * param_2, ulonglong * param_3, uint param_4);
}
namespace vehicle::appearance {
typedef char (__fastcall PreparePlayerVehicleInSortieFunc)(longlong param_1);
}
namespace vehicle::appearance {
typedef char (__fastcall PreparePlayerVehicleInGameFunc)(longlong param_1, ulonglong param_2);
}
namespace FileLoadDefaultCommon {
typedef longlong (__fastcall LoadDefaultFpkPtrFuncFunc)(longlong param_1, uint param_2);
}
namespace vehicle::appearance::camo {
typedef ulonglong * (__fastcall LoadAllVehicleCamoFpksFunc)();
}
namespace player::callMenu {
typedef longlong * (__fastcall BuddyCommandGetNameLangIdFunc)(longlong * langId, uint commandType);
}
namespace player::callMenu {
typedef longlong * (__fastcall BuddyCommandGetDescriptionLangIdFunc)(longlong * langId, uint commandType);
}
namespace foxlua {
typedef FoxLuaModule * (__fastcall NewModuleFunc)(undefined8 param_1, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5);
}
namespace foxlua {
typedef FoxLuaModule * (__fastcall NewSubModuleFunc)(FoxLuaModule * parentModule, const char * moduleName, undefined8 param_3, undefined8 param_4, char param_5);
}
namespace foxlua {
typedef int (__fastcall AddCFuncToModuleFunc)(FoxLuaModule * module, const char * funcName, lua_CFunction cfunc, undefined8 param_4, int param_5, void * param_6);
}
namespace foxlua {
typedef int (__fastcall AddCFuncToModule2Func)(FoxLuaModule * module, const char * funcName, void * param_3);
}
namespace foxlua {
typedef undefined8 (__fastcall AddCFuncToModule3Func)(FoxLuaModule * moduleName, const char * funcName, lua_CFunction param_3, int param_4, void * param_5);
}
namespace foxlua {
typedef undefined (__fastcall AddCFuncToModule4AsUdataFunc)(undefined8 moduleUnk, undefined8 funcName, undefined8 cFunctionAndSomethingElseMaybe);
}
namespace foxlua {
typedef void (__fastcall AddEnumToModuleFunc)(FoxLuaModule * foxModule, const char * enumName, int enumValue);
}
namespace foxlua {
typedef bool (__fastcall AddEnumToModule2Func)(FoxLuaModule * module, const char * enumName, int * enumValue);
}
namespace foxlua {
typedef void (__fastcall AddEnumToModule3Func)(FoxLuaModule * module, const char * enumName, undefined8 enumValue);
}
namespace foxlua {
typedef undefined (__fastcall AddEnumToModule4Func)(undefined8 module, undefined8 enumName, undefined8 enumValue);
}
typedef undefined (__fastcall RegisterVarFunc)(undefined8 foxLua, const char * varName, undefined8 varAddress, lua_CFunction * luaCFunc);
typedef void (__fastcall RegisterVar_01Func)(longlong param_1, const char * varName, undefined4 param_3, undefined8 param_4, undefined2 param_5, undefined param_6);
typedef void (__fastcall RegisterVar_02Func)(undefined8 param_1, const char * varName, undefined8 param_3, char param_4);
typedef int (__fastcall RegisterVar_03Func)(FoxLuaModule * param_1, const char * varName, void * varAddress, lua_CFunction unkLuaCFunc);
typedef bool (__fastcall RegisterVarArrayFunc)(FoxLuaModule * module, const char * varName, lua_CFunction param_3, lua_CFunction param_4, undefined8 param_5, undefined * param_6, undefined * param_7, undefined8 arraySize);
typedef undefined4 * (__fastcall DeclareEntityClassFunc)(undefined4 * param_1, const char * className, longlong entityInfo);
namespace lua {
typedef lua_State * (__fastcall lua_newstateFunc)(lua_Alloc f, void * ud);
}
namespace lua {
typedef void (__fastcall lua_closeFunc)(lua_State * L);
}
namespace lua {
typedef lua_State * (__fastcall lua_newthreadFunc)(lua_State * L);
}
namespace lua {
typedef lua_CFunction (__fastcall lua_atpanicFunc)(lua_State * L, lua_CFunction panicf);
}
// lua::lua_gettop USING_CODE
namespace lua {
typedef void (__fastcall lua_settopFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_pushvalueFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_removeFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_insertFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_replaceFunc)(lua_State * L, int idx);
}
namespace lua {
typedef int (__fastcall lua_checkstackFunc)(lua_State * L, int sz);
}
namespace lua {
typedef void (__fastcall lua_xmoveFunc)(lua_State * from, lua_State * to, int n);
}
namespace lua {
typedef int (__fastcall lua_isnumberFunc)(lua_State * L, int idx);
}
namespace lua {
typedef int (__fastcall lua_isstringFunc)(lua_State * L, int idx);
}
namespace lua {
typedef int (__fastcall lua_iscfunctionFunc)(lua_State * L, int idx);
}
// lua::lua_isuserdata USING_CODE
namespace lua {
typedef int (__fastcall lua_typeFunc)(lua_State * L, int idx);
}
// lua::lua_typename USING_CODE
namespace lua {
typedef int (__fastcall lua_equalFunc)(lua_State * L, int index1, int index2);
}
namespace lua {
typedef int (__fastcall lua_rawequalFunc)(lua_State * L, int idx1, int idx2);
}
namespace lua {
typedef int (__fastcall lua_lessthanFunc)(lua_State * L, int idx1, int idx2);
}
namespace lua {
typedef lua_Number (__fastcall lua_tonumberFunc)(lua_State * L, int idx);
}
namespace lua {
typedef lua_Integer (__fastcall lua_tointegerFunc)(lua_State * L, int idx);
}
namespace lua {
typedef int (__fastcall lua_tobooleanFunc)(lua_State * L, int idx);
}
namespace lua {
typedef char * (__fastcall lua_tolstringFunc)(lua_State * L, int idx, size_t * len);
}
namespace lua {
typedef size_t (__fastcall lua_objlenFunc)(lua_State * L, int idx);
}
namespace lua {
typedef lua_CFunction (__fastcall lua_tocfunctionFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void * (__fastcall lua_touserdataFunc)(lua_State * L, int idx);
}
namespace lua {
typedef lua_State * (__fastcall lua_tothreadFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void * (__fastcall lua_topointerFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_pushnilFunc)(lua_State * L);
}
namespace lua {
typedef void (__fastcall lua_pushnumberFunc)(lua_State * L, lua_Number n);
}
namespace lua {
typedef void (__fastcall lua_pushintegerFunc)(lua_State * L, lua_Integer n);
}
namespace lua {
typedef void (__fastcall lua_pushlstringFunc)(lua_State * L, const char * s, size_t l);
}
namespace lua {
typedef void (__fastcall lua_pushstringFunc)(lua_State * L, const char * s);
}
namespace lua {
typedef char * (__fastcall lua_pushvfstringFunc)(lua_State * L, const char * fmt, void * argp);
}
namespace lua {
typedef char * (__fastcall lua_pushfstringFunc)(lua_State * L, const char * fmt, ...);
}
namespace lua {
typedef void (__fastcall lua_pushcclosureFunc)(lua_State * L, lua_CFunction fn, int n);
}
namespace lua {
typedef void (__fastcall lua_pushbooleanFunc)(lua_State * L, int b);
}
namespace lua {
typedef void (__fastcall lua_pushlightuserdataFunc)(lua_State * L, void * p);
}
namespace lua {
typedef int (__fastcall lua_pushthreadFunc)(lua_State * L);
}
namespace lua {
typedef void (__fastcall lua_gettableFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_getfieldFunc)(lua_State * L, int idx, const char * k);
}
namespace lua {
typedef void (__fastcall lua_rawgetFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_rawgetiFunc)(lua_State * L, int idx, int n);
}
namespace lua {
typedef void (__fastcall lua_createtableFunc)(lua_State * L, int narr, int nrec);
}
namespace lua {
typedef void * (__fastcall lua_newuserdataFunc)(lua_State * L, size_t sz);
}
namespace lua {
typedef int (__fastcall lua_getmetatableFunc)(lua_State * L, int objindex);
}
namespace lua {
typedef void (__fastcall lua_getfenvFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_settableFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_setfieldFunc)(lua_State * L, int idx, const char * k);
}
namespace lua {
typedef void (__fastcall lua_rawsetFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_rawsetiFunc)(lua_State * L, int idx, int n);
}
namespace lua {
typedef int (__fastcall lua_setmetatableFunc)(lua_State * L, int objindex);
}
namespace lua {
typedef int (__fastcall lua_setfenvFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_callFunc)(lua_State * L, int nargs, int nresults);
}
namespace lua {
typedef int (__fastcall lua_pcallFunc)(lua_State * L, int nargs, int nresults, int errfunc);
}
namespace lua {
typedef int (__fastcall lua_cpcallFunc)(lua_State * L, lua_CFunction func, void * ud);
}
namespace lua {
typedef int (__fastcall lua_loadFunc)(lua_State * L, lua_Reader reader, void * dt, const char * chunkname);
}
namespace lua {
typedef int (__fastcall lua_dumpFunc)(lua_State * L, lua_Writer writer, void * data);
}
// lua::lua_yield USING_CODE
namespace lua {
typedef int (__fastcall lua_resumeFunc)(lua_State * L, int narg);
}
// lua::lua_status USING_CODE
namespace lua {
typedef int (__fastcall lua_gcFunc)(lua_State * L, int what, int data);
}
namespace lua {
typedef int (__fastcall lua_errorFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall lua_nextFunc)(lua_State * L, int idx);
}
namespace lua {
typedef void (__fastcall lua_concatFunc)(lua_State * L, int n);
}
// lua::lua_getallocf NO_USE
// lua::lua_setallocf NO_USE
// lua::lua_setlevel NO_USE
namespace lua {
typedef int (__fastcall lua_getstackFunc)(lua_State * L, int level, lua_Debug * ar);
}
namespace lua {
typedef int (__fastcall lua_getinfoFunc)(lua_State * L, const char * what, lua_Debug * ar);
}
namespace lua {
typedef char * (__fastcall lua_getlocalFunc)(lua_State * L, lua_Debug * ar, int n);
}
namespace lua {
typedef char * (__fastcall lua_setlocalFunc)(lua_State * L, lua_Debug * ar, int n);
}
namespace lua {
typedef char * (__fastcall lua_getupvalueFunc)(lua_State * L, int funcindex, int n);
}
namespace lua {
typedef char * (__fastcall lua_setupvalueFunc)(lua_State * L, int funcindex, int n);
}
namespace lua {
typedef int (__fastcall lua_sethookFunc)(lua_State * L, lua_Hook func, int mask, int count);
}
// lua::lua_gethook USING_CODE
// lua::lua_gethookmask USING_CODE
// lua::lua_gethookcount USING_CODE
namespace lua {
typedef void (__fastcall luaI_openlibFunc)(lua_State * L, const char * libName, const luaL_Reg * l, int nup);
}
// lua::luaL_register USING_CODE
namespace lua {
typedef int (__fastcall luaL_getmetafieldFunc)(lua_State * L, int obj, const char * e);
}
namespace lua {
typedef int (__fastcall luaL_callmetaFunc)(lua_State * L, int obj, const char * e);
}
namespace lua {
typedef int (__fastcall luaL_typerrorFunc)(lua_State * L, int narg, const char * tname);
}
namespace lua {
typedef int (__fastcall luaL_argerrorFunc)(lua_State * L, int numarg, const char * extramsg);
}
namespace lua {
typedef char * (__fastcall luaL_checklstringFunc)(lua_State * L, int numArg, size_t * l);
}
namespace lua {
typedef char * (__fastcall luaL_optlstringFunc)(lua_State * L, int numArg, const char * def, size_t * l);
}
namespace lua {
typedef lua_Number (__fastcall luaL_checknumberFunc)(lua_State * L, int numArg);
}
// lua::luaL_optnumber USING_CODE
namespace lua {
typedef lua_Integer (__fastcall luaL_checkintegerFunc)(lua_State * L, int numArg);
}
namespace lua {
typedef lua_Integer (__fastcall luaL_optintegerFunc)(lua_State * L, int nArg, lua_Integer def);
}
namespace lua {
typedef void (__fastcall luaL_checkstackFunc)(lua_State * L, int sz, const char * msg);
}
namespace lua {
typedef void (__fastcall luaL_checktypeFunc)(lua_State * L, int narg, int t);
}
namespace lua {
typedef void (__fastcall luaL_checkanyFunc)(lua_State * L, int narg);
}
namespace lua {
typedef int (__fastcall luaL_newmetatableFunc)(lua_State * L, const char * tname);
}
namespace lua {
typedef void * (__fastcall luaL_checkudataFunc)(lua_State * L, int ud, const char * tname);
}
namespace lua {
typedef void (__fastcall luaL_whereFunc)(lua_State * L, int lvl);
}
namespace lua {
typedef int (__fastcall luaL_errorFunc)(lua_State * L, const char * fmt, ...);
}
namespace lua {
typedef int (__fastcall luaL_checkoptionFunc)(lua_State * L, int narg, const char * def, char * * lst);
}
// lua::luaL_ref USING_CODE
// lua::luaL_unref USING_CODE
namespace lua {
typedef int (__fastcall luaL_loadfileFunc)(lua_State * L, const char * filename);
}
namespace lua {
typedef int (__fastcall luaL_loadbufferFunc)(lua_State * L, const char * buff, size_t sz, const char * name);
}
// lua::luaL_loadstring USING_CODE
namespace lua {
typedef lua_State * (__fastcall luaL_newstateFunc)();
}
namespace lua {
typedef char * (__fastcall luaL_gsubFunc)(lua_State * L, const char * s, const char * p, const char * r);
}
namespace lua {
typedef char * (__fastcall luaL_findtableFunc)(lua_State * L, int idx, const char * fname, int szhint);
}
// lua::luaL_buffinit USING_CODE
namespace lua {
typedef char * (__fastcall luaL_prepbufferFunc)(luaL_Buffer * B);
}
namespace lua {
typedef void (__fastcall luaL_addlstringFunc)(luaL_Buffer * B, const char * s, size_t l);
}
// lua::luaL_addstring USING_CODE
namespace lua {
typedef void (__fastcall luaL_addvalueFunc)(luaL_Buffer * B);
}
namespace lua {
typedef void (__fastcall luaL_pushresultFunc)(luaL_Buffer * B);
}
namespace lua {
typedef int (__fastcall luaopen_baseFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_tableFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_ioFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_osFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_stringFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_mathFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_debugFunc)(lua_State * L);
}
namespace lua {
typedef int (__fastcall luaopen_packageFunc)(lua_State * L);
}
namespace lua {
typedef void (__fastcall luaL_openlibsFunc)(lua_State * L);
}

//tex the (extern of the) function pointers
namespace fox::StrCode {
extern GetStrCodeWithLengthFunc* GetStrCodeWithLength;
}
namespace fox::StrCode32 {
extern GetStrCode32Func* GetStrCode32;
}
extern PathCode64ExtFunc* PathCode64Ext;
extern FNVHash32Func* FNVHash32;
namespace ui::lang {
extern GetFreeRoamLangIdFunc* GetFreeRoamLangId;
}
extern UpdateFOVLerpFunc* UpdateFOVLerp;
extern UnkPrintFuncStubbedOutFunc* UnkPrintFuncStubbedOut;
extern l_StubbedOutFunc* l_StubbedOut;
extern nullsub_2Func* nullsub_2;
namespace files {
extern LoadFileFunc* LoadFile;
}
namespace files {
extern LoadFileSubFunc* LoadFileSub;
}
extern Path_CopyFunc* Path_Copy;
namespace fox::PathManager {
extern GetEmptyPathFunc* GetEmptyPath;
}
namespace player::appearance::parts {
extern LoadPlayerPartsFpkFunc* LoadPlayerPartsFpk;
}
namespace player::appearance::parts {
extern LoadPlayerPartsPartsFunc* LoadPlayerPartsParts;
}
namespace player::appearance::fova::camo {
extern LoadPlayerCamoFpkFunc* LoadPlayerCamoFpk;
}
namespace player::appearance::fova::camo {
extern LoadPlayerCamoFv2Func* LoadPlayerCamoFv2;
}
namespace player::motion::facial {
extern LoadPlayerFacialMotionFpkFunc* LoadPlayerFacialMotionFpk;
}
namespace player::motion::facial {
extern LoadPlayerFacialMotionMtarFunc* LoadPlayerFacialMotionMtar;
}
namespace player::appearance::fova::arm {
extern LoadPlayerBionicArmFpkFunc* LoadPlayerBionicArmFpk;
}
namespace player::appearance::fova::arm {
extern LoadPlayerBionicArmFv2Func* LoadPlayerBionicArmFv2;
}
namespace player::appearance::fova::skinTone {
extern CheckPlayerPartsIfShouldApplySkinToneFv2Func* CheckPlayerPartsIfShouldApplySkinToneFv2;
}
namespace player::appearance::fova::skinTone {
extern LoadPlayerPartsSkinToneFv2Func* LoadPlayerPartsSkinToneFv2;
}
namespace player::appearance {
extern IsHeadNeededForPartsTypeFunc* IsHeadNeededForPartsType;
}
namespace player::appearance {
extern IsHeadNeededForPartsTypeAndAvatarFunc* IsHeadNeededForPartsTypeAndAvatar;
}
namespace player::appearance::fova::face {
extern LoadPlayerSnakeFaceFpkFunc* LoadPlayerSnakeFaceFpk;
}
namespace player::appearance::fova::face {
extern LoadPlayerSnakeFaceFv2Func* LoadPlayerSnakeFaceFv2;
}
namespace player::appearance::avatar {
extern LoadAvatarOgreHornFpkFunc* LoadAvatarOgreHornFpk;
}
namespace player::appearance::avatar {
extern LoadAvatarOgreHornFv2Func* LoadAvatarOgreHornFv2;
}
namespace buddy::system {
extern LoadBuddyMainFileFunc* LoadBuddyMainFile;
}
namespace buddy::quiet {
extern LoadBuddyQuietWeaponFpkFunc* LoadBuddyQuietWeaponFpk;
}
namespace buddy::dog {
extern LoadBuddyDogCommonFPKFunc* LoadBuddyDogCommonFPK;
}
namespace buddy::horse {
extern LoadBuddyHorseCommonFPKFunc* LoadBuddyHorseCommonFPK;
}
namespace buddy::walker {
extern LoadBuddyWalkerGearArmFpkFunc* LoadBuddyWalkerGearArmFpk;
}
namespace buddy::walker {
extern LoadBuddyWalkerGearHeadFpkFunc* LoadBuddyWalkerGearHeadFpk;
}
namespace buddy::walker {
extern LoadBuddyWalkerGearWeaponFpkFunc* LoadBuddyWalkerGearWeaponFpk;
}
namespace FileLoadDefaultCommon {
extern LoadDefaultFpksFuncFunc* LoadDefaultFpksFunc;
}
namespace vehicle::appearance {
extern PreparePlayerVehicleInSortieFunc* PreparePlayerVehicleInSortie;
}
namespace vehicle::appearance {
extern PreparePlayerVehicleInGameFunc* PreparePlayerVehicleInGame;
}
namespace FileLoadDefaultCommon {
extern LoadDefaultFpkPtrFuncFunc* LoadDefaultFpkPtrFunc;
}
namespace vehicle::appearance::camo {
extern LoadAllVehicleCamoFpksFunc* LoadAllVehicleCamoFpks;
}
namespace player::callMenu {
extern BuddyCommandGetNameLangIdFunc* BuddyCommandGetNameLangId;
}
namespace player::callMenu {
extern BuddyCommandGetDescriptionLangIdFunc* BuddyCommandGetDescriptionLangId;
}
namespace foxlua {
extern NewModuleFunc* NewModule;
}
namespace foxlua {
extern NewSubModuleFunc* NewSubModule;
}
namespace foxlua {
extern AddCFuncToModuleFunc* AddCFuncToModule;
}
namespace foxlua {
extern AddCFuncToModule2Func* AddCFuncToModule2;
}
namespace foxlua {
extern AddCFuncToModule3Func* AddCFuncToModule3;
}
namespace foxlua {
extern AddCFuncToModule4AsUdataFunc* AddCFuncToModule4AsUdata;
}
namespace foxlua {
extern AddEnumToModuleFunc* AddEnumToModule;
}
namespace foxlua {
extern AddEnumToModule2Func* AddEnumToModule2;
}
namespace foxlua {
extern AddEnumToModule3Func* AddEnumToModule3;
}
namespace foxlua {
extern AddEnumToModule4Func* AddEnumToModule4;
}
extern RegisterVarFunc* RegisterVar;
extern RegisterVar_01Func* RegisterVar_01;
extern RegisterVar_02Func* RegisterVar_02;
extern RegisterVar_03Func* RegisterVar_03;
extern RegisterVarArrayFunc* RegisterVarArray;
extern DeclareEntityClassFunc* DeclareEntityClass;
namespace lua {
extern lua_newstateFunc* lua_newstate;
}
namespace lua {
extern lua_closeFunc* lua_close;
}
namespace lua {
extern lua_newthreadFunc* lua_newthread;
}
namespace lua {
extern lua_atpanicFunc* lua_atpanic;
}
namespace lua {
//extern lua_gettopFunc* lua_gettop;//USING_CODE
}
namespace lua {
extern lua_settopFunc* lua_settop;
}
namespace lua {
extern lua_pushvalueFunc* lua_pushvalue;
}
namespace lua {
extern lua_removeFunc* lua_remove;
}
namespace lua {
extern lua_insertFunc* lua_insert;
}
namespace lua {
extern lua_replaceFunc* lua_replace;
}
namespace lua {
extern lua_checkstackFunc* lua_checkstack;
}
namespace lua {
extern lua_xmoveFunc* lua_xmove;
}
namespace lua {
extern lua_isnumberFunc* lua_isnumber;
}
namespace lua {
extern lua_isstringFunc* lua_isstring;
}
namespace lua {
extern lua_iscfunctionFunc* lua_iscfunction;
}
namespace lua {
//extern lua_isuserdataFunc* lua_isuserdata;//USING_CODE
}
namespace lua {
extern lua_typeFunc* lua_type;
}
namespace lua {
//extern lua_typenameFunc* lua_typename;//USING_CODE
}
namespace lua {
extern lua_equalFunc* lua_equal;
}
namespace lua {
extern lua_rawequalFunc* lua_rawequal;
}
namespace lua {
extern lua_lessthanFunc* lua_lessthan;
}
namespace lua {
extern lua_tonumberFunc* lua_tonumber;
}
namespace lua {
extern lua_tointegerFunc* lua_tointeger;
}
namespace lua {
extern lua_tobooleanFunc* lua_toboolean;
}
namespace lua {
extern lua_tolstringFunc* lua_tolstring;
}
namespace lua {
extern lua_objlenFunc* lua_objlen;
}
namespace lua {
extern lua_tocfunctionFunc* lua_tocfunction;
}
namespace lua {
extern lua_touserdataFunc* lua_touserdata;
}
namespace lua {
extern lua_tothreadFunc* lua_tothread;
}
namespace lua {
extern lua_topointerFunc* lua_topointer;
}
namespace lua {
extern lua_pushnilFunc* lua_pushnil;
}
namespace lua {
extern lua_pushnumberFunc* lua_pushnumber;
}
namespace lua {
extern lua_pushintegerFunc* lua_pushinteger;
}
namespace lua {
extern lua_pushlstringFunc* lua_pushlstring;
}
namespace lua {
extern lua_pushstringFunc* lua_pushstring;
}
namespace lua {
extern lua_pushvfstringFunc* lua_pushvfstring;
}
namespace lua {
extern lua_pushfstringFunc* lua_pushfstring;
}
namespace lua {
extern lua_pushcclosureFunc* lua_pushcclosure;
}
namespace lua {
extern lua_pushbooleanFunc* lua_pushboolean;
}
namespace lua {
extern lua_pushlightuserdataFunc* lua_pushlightuserdata;
}
namespace lua {
extern lua_pushthreadFunc* lua_pushthread;
}
namespace lua {
extern lua_gettableFunc* lua_gettable;
}
namespace lua {
extern lua_getfieldFunc* lua_getfield;
}
namespace lua {
extern lua_rawgetFunc* lua_rawget;
}
namespace lua {
extern lua_rawgetiFunc* lua_rawgeti;
}
namespace lua {
extern lua_createtableFunc* lua_createtable;
}
namespace lua {
extern lua_newuserdataFunc* lua_newuserdata;
}
namespace lua {
extern lua_getmetatableFunc* lua_getmetatable;
}
namespace lua {
extern lua_getfenvFunc* lua_getfenv;
}
namespace lua {
extern lua_settableFunc* lua_settable;
}
namespace lua {
extern lua_setfieldFunc* lua_setfield;
}
namespace lua {
extern lua_rawsetFunc* lua_rawset;
}
namespace lua {
extern lua_rawsetiFunc* lua_rawseti;
}
namespace lua {
extern lua_setmetatableFunc* lua_setmetatable;
}
namespace lua {
extern lua_setfenvFunc* lua_setfenv;
}
namespace lua {
extern lua_callFunc* lua_call;
}
namespace lua {
extern lua_pcallFunc* lua_pcall;
}
namespace lua {
extern lua_cpcallFunc* lua_cpcall;
}
namespace lua {
extern lua_loadFunc* lua_load;
}
namespace lua {
extern lua_dumpFunc* lua_dump;
}
namespace lua {
//extern lua_yieldFunc* lua_yield;//USING_CODE
}
namespace lua {
extern lua_resumeFunc* lua_resume;
}
namespace lua {
//extern lua_statusFunc* lua_status;//USING_CODE
}
namespace lua {
extern lua_gcFunc* lua_gc;
}
namespace lua {
extern lua_errorFunc* lua_error;
}
namespace lua {
extern lua_nextFunc* lua_next;
}
namespace lua {
extern lua_concatFunc* lua_concat;
}
namespace lua {
//extern lua_getallocfFunc* lua_getallocf;//NO_USE
}
namespace lua {
//extern lua_setallocfFunc* lua_setallocf;//NO_USE
}
namespace lua {
//extern lua_setlevelFunc* lua_setlevel;//NO_USE
}
namespace lua {
extern lua_getstackFunc* lua_getstack;
}
namespace lua {
extern lua_getinfoFunc* lua_getinfo;
}
namespace lua {
extern lua_getlocalFunc* lua_getlocal;
}
namespace lua {
extern lua_setlocalFunc* lua_setlocal;
}
namespace lua {
extern lua_getupvalueFunc* lua_getupvalue;
}
namespace lua {
extern lua_setupvalueFunc* lua_setupvalue;
}
namespace lua {
extern lua_sethookFunc* lua_sethook;
}
namespace lua {
//extern lua_gethookFunc* lua_gethook;//USING_CODE
}
namespace lua {
//extern lua_gethookmaskFunc* lua_gethookmask;//USING_CODE
}
namespace lua {
//extern lua_gethookcountFunc* lua_gethookcount;//USING_CODE
}
namespace lua {
extern luaI_openlibFunc* luaI_openlib;
}
namespace lua {
//extern luaL_registerFunc* luaL_register;//USING_CODE
}
namespace lua {
extern luaL_getmetafieldFunc* luaL_getmetafield;
}
namespace lua {
extern luaL_callmetaFunc* luaL_callmeta;
}
namespace lua {
extern luaL_typerrorFunc* luaL_typerror;
}
namespace lua {
extern luaL_argerrorFunc* luaL_argerror;
}
namespace lua {
extern luaL_checklstringFunc* luaL_checklstring;
}
namespace lua {
extern luaL_optlstringFunc* luaL_optlstring;
}
namespace lua {
extern luaL_checknumberFunc* luaL_checknumber;
}
namespace lua {
//extern luaL_optnumberFunc* luaL_optnumber;//USING_CODE
}
namespace lua {
extern luaL_checkintegerFunc* luaL_checkinteger;
}
namespace lua {
extern luaL_optintegerFunc* luaL_optinteger;
}
namespace lua {
extern luaL_checkstackFunc* luaL_checkstack;
}
namespace lua {
extern luaL_checktypeFunc* luaL_checktype;
}
namespace lua {
extern luaL_checkanyFunc* luaL_checkany;
}
namespace lua {
extern luaL_newmetatableFunc* luaL_newmetatable;
}
namespace lua {
extern luaL_checkudataFunc* luaL_checkudata;
}
namespace lua {
extern luaL_whereFunc* luaL_where;
}
namespace lua {
extern luaL_errorFunc* luaL_error;
}
namespace lua {
extern luaL_checkoptionFunc* luaL_checkoption;
}
namespace lua {
//extern luaL_refFunc* luaL_ref;//USING_CODE
}
namespace lua {
//extern luaL_unrefFunc* luaL_unref;//USING_CODE
}
namespace lua {
extern luaL_loadfileFunc* luaL_loadfile;
}
namespace lua {
extern luaL_loadbufferFunc* luaL_loadbuffer;
}
namespace lua {
//extern luaL_loadstringFunc* luaL_loadstring;//USING_CODE
}
namespace lua {
extern luaL_newstateFunc* luaL_newstate;
}
namespace lua {
extern luaL_gsubFunc* luaL_gsub;
}
namespace lua {
extern luaL_findtableFunc* luaL_findtable;
}
namespace lua {
//extern luaL_buffinitFunc* luaL_buffinit;//USING_CODE
}
namespace lua {
extern luaL_prepbufferFunc* luaL_prepbuffer;
}
namespace lua {
extern luaL_addlstringFunc* luaL_addlstring;
}
namespace lua {
//extern luaL_addstringFunc* luaL_addstring;//USING_CODE
}
namespace lua {
extern luaL_addvalueFunc* luaL_addvalue;
}
namespace lua {
extern luaL_pushresultFunc* luaL_pushresult;
}
namespace lua {
extern luaopen_baseFunc* luaopen_base;
}
namespace lua {
extern luaopen_tableFunc* luaopen_table;
}
namespace lua {
extern luaopen_ioFunc* luaopen_io;
}
namespace lua {
extern luaopen_osFunc* luaopen_os;
}
namespace lua {
extern luaopen_stringFunc* luaopen_string;
}
namespace lua {
extern luaopen_mathFunc* luaopen_math;
}
namespace lua {
extern luaopen_debugFunc* luaopen_debug;
}
namespace lua {
extern luaopen_packageFunc* luaopen_package;
}
namespace lua {
extern luaL_openlibsFunc* luaL_openlibs;
}

//tex WORKAROUND: lua usually isnt in a namespace, so just push it so dont have to futz with it for any existing code
//shift this out if you ever break up mgsvtpp_func_typedefs
using namespace lua;

