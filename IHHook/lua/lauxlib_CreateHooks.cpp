#include "../HookMacros.h"
#include <lauxlib.h>

namespace IHHook {
void CreateHooks_Lauxlib(size_t BaseAddr, size_t RealBaseAddr) {
	//lauxlib.h

	//...

	CREATEHOOK(luaI_openlib)
	//OFF CREATEHOOK(luaL_register)//tex: Using default implementation.
	CREATEHOOK(luaL_getmetafield)//TEST
	CREATEHOOK(luaL_callmeta)//TEST
	CREATEHOOK(luaL_typerror)//TEST
	CREATEHOOK(luaL_argerror)//TEST
	CREATEHOOK(luaL_checklstring)//TEST
	CREATEHOOK(luaL_optlstring)//TEST
	CREATEHOOK(luaL_checknumber)//TEST
	//OFF CREATEHOOK(luaL_optnumber)//tex: Using default implementation. Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes

	CREATEHOOK(luaL_checkinteger)//TEST
	CREATEHOOK(luaL_optinteger)//TEST

	CREATEHOOK(luaL_checkstack)//TEST
	CREATEHOOK(luaL_checktype)//TEST
	CREATEHOOK(luaL_checkany)//TEST

	CREATEHOOK(luaL_newmetatable)//TEST
	CREATEHOOK(luaL_checkudata)//TEST

	CREATEHOOK(luaL_where)//TEST
	CREATEHOOK(luaL_error)//TEST

	CREATEHOOK(luaL_checkoption)//TEST

	//OFF CREATEHOOK(luaL_ref)//tex: Using default implementation. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param
	//OFF CREATEHOOK(luaL_unref)//tex: Using default implementation.

	CREATEHOOK(luaL_loadfile)//TEST
	CREATEHOOK(luaL_loadbuffer)//TEST
	//OFF CREATEHOOK(luaL_loadstring)//tex: Using default implementation.

	CREATEHOOK(luaL_newstate)


	CREATEHOOK(luaL_gsub)//TEST

	CREATEHOOK(luaL_findtable)//TEST


	//...

	/*
	** {======================================================
	** Generic Buffer manipulation
	** =======================================================
	*/

	CREATEHOOK(luaL_buffinit)//TEST
	CREATEHOOK(luaL_prepbuffer)
	CREATEHOOK(luaL_addlstring)//TEST
	//OFF CREATEHOOK(luaL_addstring)//tex: Using default implementation. Only call in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
	CREATEHOOK(luaL_addvalue)//TEST
	CREATEHOOK(luaL_pushresult)//TEST
}//CreateHooks_Lauxlib
}//namespace IHHook