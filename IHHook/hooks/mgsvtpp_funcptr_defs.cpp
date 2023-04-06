//GENERATED: by ghidra script ExportHooksToHeader.py
//via WriteFuncPtrDefsFile
//declares function pointers of exported functions

// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason
// USING_CODE - using the default lapi code implementation instead of hooking

#include "mgsvtpp_func_typedefs.h"

GetStrCodeWithLengthFunc* GetStrCodeWithLength;
GetStrCode32Func* GetStrCode32;
PathCode64ExtFunc* PathCode64Ext;
FNVHash32Func* FNVHash32;
ui::lang::GetFreeRoamLangIdFunc* ui::lang::GetFreeRoamLangId;
UpdateFOVLerpFunc* UpdateFOVLerp;
UnkPrintFuncStubbedOutFunc* UnkPrintFuncStubbedOut;
l_StubbedOutFunc* l_StubbedOut;
nullsub_2Func* nullsub_2;
files::LoadFileFunc* files::LoadFile;
files::LoadFileSubFunc* files::LoadFileSub;
Path_CopyFunc* Path_Copy;
fox::PathManager::GetEmptyPathFunc* fox::PathManager::GetEmptyPath;
player::appearance::parts::LoadPlayerPartsFpkFunc* player::appearance::parts::LoadPlayerPartsFpk;
player::appearance::parts::LoadPlayerPartsPartsFunc* player::appearance::parts::LoadPlayerPartsParts;
player::appearance::fova::camo::LoadPlayerCamoFpkFunc* player::appearance::fova::camo::LoadPlayerCamoFpk;
player::appearance::fova::camo::LoadPlayerCamoFv2Func* player::appearance::fova::camo::LoadPlayerCamoFv2;
player::motion::facial::LoadPlayerFacialMotionFpkFunc* player::motion::facial::LoadPlayerFacialMotionFpk;
player::facial::motion::LoadPlayerFacialMotionMtarFunc* player::facial::motion::LoadPlayerFacialMotionMtar;
player::appearance::fova::arm::LoadPlayerBionicArmFpkFunc* player::appearance::fova::arm::LoadPlayerBionicArmFpk;
player::appearance::fova::arm::LoadPlayerBionicArmFv2Func* player::appearance::fova::arm::LoadPlayerBionicArmFv2;
player::appearance::fova::skinTone::CheckPlayerPartsIfShouldApplySkinToneFv2Func* player::appearance::fova::skinTone::CheckPlayerPartsIfShouldApplySkinToneFv2;
player::appearance::fova::skinTone::LoadPlayerPartsSkinToneFv2Func* player::appearance::fova::skinTone::LoadPlayerPartsSkinToneFv2;
player::appearance::IsHeadNeededForPartsTypeFunc* player::appearance::IsHeadNeededForPartsType;
player::appearance::IsHeadNeededForPartsTypeAndAvatarFunc* player::appearance::IsHeadNeededForPartsTypeAndAvatar;
player::appearance::fova::face::LoadPlayerSnakeFaceFpkFunc* player::appearance::fova::face::LoadPlayerSnakeFaceFpk;
player::appearance::fova::face::LoadPlayerSnakeFaceFv2Func* player::appearance::fova::face::LoadPlayerSnakeFaceFv2;
player::appearance::avatar::LoadAvatarOgreHornFpkFunc* player::appearance::avatar::LoadAvatarOgreHornFpk;
player::appearance::avatar::LoadAvatarOgreHornFv2Func* player::appearance::avatar::LoadAvatarOgreHornFv2;
buddy::system::LoadBuddyMainFileFunc* buddy::system::LoadBuddyMainFile;
buddy::quiet::LoadBuddyQuietWeaponFpkFunc* buddy::quiet::LoadBuddyQuietWeaponFpk;
buddy::dog::LoadBuddyDogCommonFPKFunc* buddy::dog::LoadBuddyDogCommonFPK;
buddy::horse::LoadBuddyHorseCommonFPKFunc* buddy::horse::LoadBuddyHorseCommonFPK;
buddy::walker::LoadBuddyWalkerGearArmFpkFunc* buddy::walker::LoadBuddyWalkerGearArmFpk;
buddy::walker::LoadBuddyWalkerGearHeadFpkFunc* buddy::walker::LoadBuddyWalkerGearHeadFpk;
buddy::walker::LoadBuddyWalkerGearWeaponFpkFunc* buddy::walker::LoadBuddyWalkerGearWeaponFpk;
FileLoadDefaultCommon::LoadDefaultFpksFuncFunc* FileLoadDefaultCommon::LoadDefaultFpksFunc;
vehicle::appearance::PreparePlayerVehicleInSortieFunc* vehicle::appearance::PreparePlayerVehicleInSortie;
vehicle::appearance::PreparePlayerVehicleInGameFunc* vehicle::appearance::PreparePlayerVehicleInGame;
FileLoadDefaultCommon::LoadDefaultFpkPtrFuncFunc* FileLoadDefaultCommon::LoadDefaultFpkPtrFunc;
vehicle::appearance::camo::LoadAllVehicleCamoFpksFunc* vehicle::appearance::camo::LoadAllVehicleCamoFpks;
player::callMenu::BuddyCommandGetNameLangIdFunc* player::callMenu::BuddyCommandGetNameLangId;
player::callMenu::BuddyCommandGetDescriptionLangIdFunc* player::callMenu::BuddyCommandGetDescriptionLangId;
foxlua::NewModuleFunc* foxlua::NewModule;
foxlua::NewSubModuleFunc* foxlua::NewSubModule;
foxlua::AddCFuncToModuleFunc* foxlua::AddCFuncToModule;
foxlua::AddCFuncToModule2Func* foxlua::AddCFuncToModule2;
foxlua::AddCFuncToModule3Func* foxlua::AddCFuncToModule3;
foxlua::AddEnumToModuleFunc* foxlua::AddEnumToModule;
foxlua::AddEnumToModule2Func* foxlua::AddEnumToModule2;
foxlua::AddEnumToModule3Func* foxlua::AddEnumToModule3;
foxlua::AddEnumToModule4Func* foxlua::AddEnumToModule4;
RegisterVarFunc* RegisterVar;
RegisterVar_01Func* RegisterVar_01;
RegisterVar_02Func* RegisterVar_02;
RegisterVar_03Func* RegisterVar_03;
RegisterVarArrayFunc* RegisterVarArray;
DeclareEntityClassFunc* DeclareEntityClass;
lua::lua_newstateFunc* lua::lua_newstate;
lua::lua_closeFunc* lua::lua_close;
lua::lua_newthreadFunc* lua::lua_newthread;
lua::lua_atpanicFunc* lua::lua_atpanic;
//lua::lua_gettopFunc* lua::lua_gettop;//USING_CODE
lua::lua_settopFunc* lua::lua_settop;
lua::lua_pushvalueFunc* lua::lua_pushvalue;
lua::lua_removeFunc* lua::lua_remove;
lua::lua_insertFunc* lua::lua_insert;
lua::lua_replaceFunc* lua::lua_replace;
lua::lua_checkstackFunc* lua::lua_checkstack;
lua::lua_xmoveFunc* lua::lua_xmove;
lua::lua_isnumberFunc* lua::lua_isnumber;
lua::lua_isstringFunc* lua::lua_isstring;
lua::lua_iscfunctionFunc* lua::lua_iscfunction;
//lua::lua_isuserdataFunc* lua::lua_isuserdata;//USING_CODE
lua::lua_typeFunc* lua::lua_type;
//lua::lua_typenameFunc* lua::lua_typename;//USING_CODE
lua::lua_equalFunc* lua::lua_equal;
lua::lua_rawequalFunc* lua::lua_rawequal;
lua::lua_lessthanFunc* lua::lua_lessthan;
lua::lua_tonumberFunc* lua::lua_tonumber;
lua::lua_tointegerFunc* lua::lua_tointeger;
lua::lua_tobooleanFunc* lua::lua_toboolean;
lua::lua_tolstringFunc* lua::lua_tolstring;
lua::lua_objlenFunc* lua::lua_objlen;
lua::lua_tocfunctionFunc* lua::lua_tocfunction;
lua::lua_touserdataFunc* lua::lua_touserdata;
lua::lua_tothreadFunc* lua::lua_tothread;
lua::lua_topointerFunc* lua::lua_topointer;
lua::lua_pushnilFunc* lua::lua_pushnil;
lua::lua_pushnumberFunc* lua::lua_pushnumber;
lua::lua_pushintegerFunc* lua::lua_pushinteger;
lua::lua_pushlstringFunc* lua::lua_pushlstring;
lua::lua_pushstringFunc* lua::lua_pushstring;
lua::lua_pushvfstringFunc* lua::lua_pushvfstring;
lua::lua_pushfstringFunc* lua::lua_pushfstring;
lua::lua_pushcclosureFunc* lua::lua_pushcclosure;
lua::lua_pushbooleanFunc* lua::lua_pushboolean;
lua::lua_pushlightuserdataFunc* lua::lua_pushlightuserdata;
lua::lua_pushthreadFunc* lua::lua_pushthread;
lua::lua_gettableFunc* lua::lua_gettable;
lua::lua_getfieldFunc* lua::lua_getfield;
lua::lua_rawgetFunc* lua::lua_rawget;
lua::lua_rawgetiFunc* lua::lua_rawgeti;
lua::lua_createtableFunc* lua::lua_createtable;
lua::lua_newuserdataFunc* lua::lua_newuserdata;
lua::lua_getmetatableFunc* lua::lua_getmetatable;
lua::lua_getfenvFunc* lua::lua_getfenv;
lua::lua_settableFunc* lua::lua_settable;
lua::lua_setfieldFunc* lua::lua_setfield;
lua::lua_rawsetFunc* lua::lua_rawset;
lua::lua_rawsetiFunc* lua::lua_rawseti;
lua::lua_setmetatableFunc* lua::lua_setmetatable;
lua::lua_setfenvFunc* lua::lua_setfenv;
lua::lua_callFunc* lua::lua_call;
lua::lua_pcallFunc* lua::lua_pcall;
lua::lua_cpcallFunc* lua::lua_cpcall;
lua::lua_loadFunc* lua::lua_load;
lua::lua_dumpFunc* lua::lua_dump;
//lua::lua_yieldFunc* lua::lua_yield;//USING_CODE
lua::lua_resumeFunc* lua::lua_resume;
//lua::lua_statusFunc* lua::lua_status;//USING_CODE
lua::lua_gcFunc* lua::lua_gc;
lua::lua_errorFunc* lua::lua_error;
lua::lua_nextFunc* lua::lua_next;
lua::lua_concatFunc* lua::lua_concat;
//lua::lua_getallocfFunc* lua::lua_getallocf;//NO_USE
//lua::lua_setallocfFunc* lua::lua_setallocf;//NO_USE
//lua::lua_setlevelFunc* lua::lua_setlevel;//NO_USE
lua::lua_getstackFunc* lua::lua_getstack;
lua::lua_getinfoFunc* lua::lua_getinfo;
lua::lua_getlocalFunc* lua::lua_getlocal;
lua::lua_setlocalFunc* lua::lua_setlocal;
lua::lua_getupvalueFunc* lua::lua_getupvalue;
lua::lua_setupvalueFunc* lua::lua_setupvalue;
lua::lua_sethookFunc* lua::lua_sethook;
//lua::lua_gethookFunc* lua::lua_gethook;//USING_CODE
//lua::lua_gethookmaskFunc* lua::lua_gethookmask;//USING_CODE
//lua::lua_gethookcountFunc* lua::lua_gethookcount;//USING_CODE
lua::luaI_openlibFunc* lua::luaI_openlib;
//lua::luaL_registerFunc* lua::luaL_register;//USING_CODE
lua::luaL_getmetafieldFunc* lua::luaL_getmetafield;
lua::luaL_callmetaFunc* lua::luaL_callmeta;
lua::luaL_typerrorFunc* lua::luaL_typerror;
lua::luaL_argerrorFunc* lua::luaL_argerror;
lua::luaL_checklstringFunc* lua::luaL_checklstring;
lua::luaL_optlstringFunc* lua::luaL_optlstring;
lua::luaL_checknumberFunc* lua::luaL_checknumber;
//lua::luaL_optnumberFunc* lua::luaL_optnumber;//USING_CODE
lua::luaL_checkintegerFunc* lua::luaL_checkinteger;
lua::luaL_optintegerFunc* lua::luaL_optinteger;
lua::luaL_checkstackFunc* lua::luaL_checkstack;
lua::luaL_checktypeFunc* lua::luaL_checktype;
lua::luaL_checkanyFunc* lua::luaL_checkany;
lua::luaL_newmetatableFunc* lua::luaL_newmetatable;
lua::luaL_checkudataFunc* lua::luaL_checkudata;
lua::luaL_whereFunc* lua::luaL_where;
lua::luaL_errorFunc* lua::luaL_error;
lua::luaL_checkoptionFunc* lua::luaL_checkoption;
//lua::luaL_refFunc* lua::luaL_ref;//USING_CODE
//lua::luaL_unrefFunc* lua::luaL_unref;//USING_CODE
lua::luaL_loadfileFunc* lua::luaL_loadfile;
lua::luaL_loadbufferFunc* lua::luaL_loadbuffer;
//lua::luaL_loadstringFunc* lua::luaL_loadstring;//USING_CODE
lua::luaL_newstateFunc* lua::luaL_newstate;
lua::luaL_gsubFunc* lua::luaL_gsub;
lua::luaL_findtableFunc* lua::luaL_findtable;
//lua::luaL_buffinitFunc* lua::luaL_buffinit;//USING_CODE
lua::luaL_prepbufferFunc* lua::luaL_prepbuffer;
lua::luaL_addlstringFunc* lua::luaL_addlstring;
//lua::luaL_addstringFunc* lua::luaL_addstring;//USING_CODE
lua::luaL_addvalueFunc* lua::luaL_addvalue;
lua::luaL_pushresultFunc* lua::luaL_pushresult;
lua::luaopen_baseFunc* lua::luaopen_base;
lua::luaopen_tableFunc* lua::luaopen_table;
lua::luaopen_ioFunc* lua::luaopen_io;
lua::luaopen_osFunc* lua::luaopen_os;
lua::luaopen_stringFunc* lua::luaopen_string;
lua::luaopen_mathFunc* lua::luaopen_math;
lua::luaopen_debugFunc* lua::luaopen_debug;
lua::luaopen_packageFunc* lua::luaopen_package;
lua::luaL_openlibsFunc* lua::luaL_openlibs;
