#include "../HookMacros.h"
#include <lauxlib.h>

namespace IHHook {

void CreateHooks_Lauxlib(size_t BaseAddr, size_t RealBaseAddr) {
	//lauxlib.h

	//DEBUGNOW signatures are more robust to game updates/different game versions than straight addresses, but take a long time to search
	//since IHHook is started on it's own thread game initialisation will continue, and IHHook wont be ready in time to start up IH properly.
	//an alternative would be to do a hook to an early execution point of the game and init  ihhook there,
	//but given the low rate of updates of the game it's better to stick with direct addresses, but have signatures documented as a backup
	//Address of signature = mgsvtpp.exe + 0x01A0B990
	//char* luaI_openlibSig = "\x45\x33\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE9"; 
	//char* luaI_openlibMask = "xx?x????xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	//DEBUGNOW uintptr_t luaI_openlibOrig = FindPattern(NULL, luaI_openlibSig, luaI_openlibMask);

	//...
	CREATE_FUNCPTR(luaI_openlib)
	//OFF CREATE_FUNCPTR(luaL_register)//tex: Using default implementation.
	CREATE_FUNCPTR(luaL_getmetafield)//TEST
	CREATE_FUNCPTR(luaL_callmeta)//TEST
	CREATE_FUNCPTR(luaL_typerror)//TEST
	CREATE_FUNCPTR(luaL_argerror)//TEST
	CREATE_FUNCPTR(luaL_checklstring)//TEST
	CREATE_FUNCPTR(luaL_optlstring)//TEST
	CREATE_FUNCPTR(luaL_checknumber)//TEST
	//OFF CREATE_FUNCPTR(luaL_optnumber)//tex: Using default implementation. Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes

	CREATE_FUNCPTR(luaL_checkinteger)//TEST
	CREATE_FUNCPTR(luaL_optinteger)//TEST

	CREATE_FUNCPTR(luaL_checkstack)//TEST
	CREATE_FUNCPTR(luaL_checktype)//TEST
	CREATE_FUNCPTR(luaL_checkany)//TEST

	CREATE_FUNCPTR(luaL_newmetatable)//TEST
	CREATE_FUNCPTR(luaL_checkudata)//TEST

	CREATE_FUNCPTR(luaL_where)//TEST
	CREATE_FUNCPTR(luaL_error)//TEST

	CREATE_FUNCPTR(luaL_checkoption)//TEST

	//OFF CREATE_FUNCPTR(luaL_ref)//tex: Using default implementation. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param
	//OFF CREATE_FUNCPTR(luaL_unref)//tex: Using default implementation.

	CREATE_FUNCPTR(luaL_loadfile)//TEST
	CREATE_FUNCPTR(luaL_loadbuffer)//TEST
	//OFF CREATE_FUNCPTR(luaL_loadstring)//tex: Using default implementation.
	CREATE_FUNCPTR(luaL_newstate)

	CREATE_FUNCPTR(luaL_gsub)//TEST

	CREATE_FUNCPTR(luaL_findtable)//TEST


	//...

	/*
	** {======================================================
	** Generic Buffer manipulation
	** =======================================================
	*/

	CREATE_FUNCPTR(luaL_buffinit)//TEST
	CREATE_FUNCPTR(luaL_prepbuffer)
	CREATE_FUNCPTR(luaL_addlstring)//TEST
	//OFF CREATE_FUNCPTR(luaL_addstring)//tex: Using default implementation. Only call in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
	CREATE_FUNCPTR(luaL_addvalue)//TEST
	CREATE_FUNCPTR(luaL_pushresult)//TEST
}//CreateHooks_Lauxlib
}//namespace IHHook