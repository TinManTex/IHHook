#include "../HookMacros.h"
#include <lua.h>

namespace IHHook {
void CreateHooks_Lua(size_t BaseAddr, size_t RealBaseAddr) {
	//lua.h

	//...

	/*
	** state manipulation
	*/
	CREATEHOOK(lua_newstate)//TEST
	CREATEHOOK(lua_close)//TEST
	CREATEHOOK(lua_newthread)

	CREATEHOOK(lua_atpanic)//TEST

	/*
	** basic stack manipulation
	*/
	//CREATEHOOK(lua_gettop)//tex: Using default implementation.
	CREATEHOOK(lua_settop)
	CREATEHOOK(lua_pushvalue)
	CREATEHOOK(lua_remove)
	CREATEHOOK(lua_insert)
	CREATEHOOK(lua_replace)
	CREATEHOOK(lua_checkstack)//TEST

	CREATEHOOK(lua_xmove)//TEST

	//*
	/** access functions (stack -> C)
	/*/

	CREATEHOOK(lua_isnumber)
	CREATEHOOK(lua_isstring)
	CREATEHOOK(lua_iscfunction)
	//CREATEHOOK(lua_isuserdata)//TEST tex: Using default implementation. No calls in lua distro, so may be hard to find, or have been culled by compilation
	CREATEHOOK(lua_type)
	CREATEHOOK(lua_typename)

	//CREATEHOOK(lua_equal)//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
	CREATEHOOK(lua_rawequal)
	CREATEHOOK(lua_lessthan)

	CREATEHOOK(lua_tonumber)
	CREATEHOOK(lua_tointeger)
	CREATEHOOK(lua_toboolean)
	CREATEHOOK(lua_tolstring)
	CREATEHOOK(lua_objlen)//TEST
	CREATEHOOK(lua_tocfunction)//TEST
	CREATEHOOK(lua_touserdata)//TEST
	CREATEHOOK(lua_tothread)//TEST
	CREATEHOOK(lua_topointer)//TEST


	/*
	** push functions (C -> stack)
	*/
	CREATEHOOK(lua_pushnil)//TEST
	CREATEHOOK(lua_pushnumber)
	CREATEHOOK(lua_pushinteger)
	CREATEHOOK(lua_pushlstring)
	CREATEHOOK(lua_pushstring)
	CREATEHOOK(lua_pushvfstring)//TEST
	CREATEHOOK(lua_pushfstring)//TEST
	CREATEHOOK(lua_pushcclosure)//TEST
	CREATEHOOK(lua_pushboolean)
	CREATEHOOK(lua_pushlightuserdata)//TEST
	CREATEHOOK(lua_pushthread)//TEST

	/*
	** get functions (Lua -> stack)
	*/
	CREATEHOOK(lua_gettable)
	CREATEHOOK(lua_getfield)
	CREATEHOOK(lua_rawget)
	CREATEHOOK(lua_rawgeti)
	CREATEHOOK(lua_createtable)
	CREATEHOOK(lua_newuserdata)//TEST
	CREATEHOOK(lua_getmetatable)//TEST
	CREATEHOOK(lua_getfenv)//TEST


	/*
	** set functions (stack -> Lua)
	*/
	CREATEHOOK(lua_settable)
	CREATEHOOK(lua_setfield)
	CREATEHOOK(lua_rawset)
	CREATEHOOK(lua_rawseti)
	CREATEHOOK(lua_setmetatable)//TEST
	CREATEHOOK(lua_setfenv)//TEST


	/*
	** `load' and `call' functions (load and run Lua code)
	*/
	CREATEHOOK(lua_call)//TEST
	CREATEHOOK(lua_pcall)//TEST
	CREATEHOOK(lua_cpcall)//TEST
	CREATEHOOK(lua_load)//TEST

	CREATEHOOK(lua_dump)//TEST

	/*
	** coroutine functions
	*/
	//CREATEHOOK(lua_yield)//tex: Using default implementation.  DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)
	CREATEHOOK(lua_resume)//TEST
	//CREATEHOOK(lua_status)//TEST //tex: Using default implementation.

	//...

	CREATEHOOK(lua_gc)//TEST


	/*
	** miscellaneous functions
	*/

	CREATEHOOK(lua_error)//TEST

	CREATEHOOK(lua_next)//TEST

	CREATEHOOK(lua_concat)//TEST

	//CREATEHOOK(lua_getallocf)//
	//CREATEHOOK(lua_setallocf)//

	//...

	/* hack */
	//CREATEHOOK(lua_setlevel)//TEST

	//...

	CREATEHOOK(lua_getstack)//TEST
	CREATEHOOK(lua_getinfo)//TEST
	CREATEHOOK(lua_getlocal)//TEST
	CREATEHOOK(lua_setlocal)//TEST
	CREATEHOOK(lua_getupvalue)//TEST
	CREATEHOOK(lua_setupvalue)//TEST

	CREATEHOOK(lua_sethook)//TEST
	CREATEHOOK(lua_gethook)//TEST
	CREATEHOOK(lua_gethookmask)//TEST
	CREATEHOOK(lua_gethookcount)//TEST
}//CreateHooks_Lua
}//namespace IHHook