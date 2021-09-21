#include "../HookMacros.h"
#include <lua.h>

namespace IHHook {
	namespace lua {
		void CreateFuncPtrs() {
			//lua.h

			//...

			/*
			** state manipulation
			*/
			CREATE_FUNCPTR(lua_newstate)//TEST
			CREATE_FUNCPTR(lua_close)//TEST
			CREATE_FUNCPTR(lua_newthread)

			CREATE_FUNCPTR(lua_atpanic)//TEST

			/*
			** basic stack manipulation
			*/
			//CREATE_FUNCPTR(lua_gettop)//tex: Using default implementation.
			CREATE_FUNCPTR(lua_settop)
			CREATE_FUNCPTR(lua_pushvalue)
			CREATE_FUNCPTR(lua_remove)
			CREATE_FUNCPTR(lua_insert)
			CREATE_FUNCPTR(lua_replace)
			CREATE_FUNCPTR(lua_checkstack)//TEST

			CREATE_FUNCPTR(lua_xmove)//TEST

			//*
			/** access functions (stack -> C)
			/*/

			CREATE_FUNCPTR(lua_isnumber)
			CREATE_FUNCPTR(lua_isstring)
			CREATE_FUNCPTR(lua_iscfunction)
			//CREATE_FUNCPTR(lua_isuserdata)//TEST tex: Using default implementation. No calls in lua distro, so may be hard to find, or have been culled by compilation
			CREATE_FUNCPTR(lua_type)
			//CREATE_FUNCPTR(lua_typename)//tex: Using default implementation. 

			//CREATE_FUNCPTR(lua_equal)//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
			CREATE_FUNCPTR(lua_rawequal)
			CREATE_FUNCPTR(lua_lessthan)

			CREATE_FUNCPTR(lua_tonumber)
			CREATE_FUNCPTR(lua_tointeger)
			CREATE_FUNCPTR(lua_toboolean)
			CREATE_FUNCPTR(lua_tolstring)
			CREATE_FUNCPTR(lua_objlen)//TEST
			CREATE_FUNCPTR(lua_tocfunction)//TEST
			CREATE_FUNCPTR(lua_touserdata)//TEST
			CREATE_FUNCPTR(lua_tothread)//TEST
			CREATE_FUNCPTR(lua_topointer)//TEST


			/*
			** push functions (C -> stack)
			*/
			CREATE_FUNCPTR(lua_pushnil)//TEST
			CREATE_FUNCPTR(lua_pushnumber)
			CREATE_FUNCPTR(lua_pushinteger)
			CREATE_FUNCPTR(lua_pushlstring)
			CREATE_FUNCPTR(lua_pushstring)
			CREATE_FUNCPTR(lua_pushvfstring)//TEST
			CREATE_FUNCPTR(lua_pushfstring)//TEST
			CREATE_FUNCPTR(lua_pushcclosure)//TEST
			CREATE_FUNCPTR(lua_pushboolean)
			CREATE_FUNCPTR(lua_pushlightuserdata)//TEST
			CREATE_FUNCPTR(lua_pushthread)//TEST

			/*
			** get functions (Lua -> stack)
			*/
			CREATE_FUNCPTR(lua_gettable)
			CREATE_FUNCPTR(lua_getfield)
			CREATE_FUNCPTR(lua_rawget)
			CREATE_FUNCPTR(lua_rawgeti)
			CREATE_FUNCPTR(lua_createtable)
			CREATE_FUNCPTR(lua_newuserdata)//TEST
			CREATE_FUNCPTR(lua_getmetatable)//TEST
			CREATE_FUNCPTR(lua_getfenv)//TEST


			/*
			** set functions (stack -> Lua)
			*/
			CREATE_FUNCPTR(lua_settable)
			CREATE_FUNCPTR(lua_setfield)
			CREATE_FUNCPTR(lua_rawset)
			CREATE_FUNCPTR(lua_rawseti)
			CREATE_FUNCPTR(lua_setmetatable)//TEST
			CREATE_FUNCPTR(lua_setfenv)//TEST


			/*
			** `load' and `call' functions (load and run Lua code)
			*/
			CREATE_FUNCPTR(lua_call)//TEST
			CREATE_FUNCPTR(lua_pcall)//TEST
			CREATE_FUNCPTR(lua_cpcall)//TEST
			CREATE_FUNCPTR(lua_load)//TEST

			CREATE_FUNCPTR(lua_dump)//TEST

			/*
			** coroutine functions
			*/
			//CREATE_FUNCPTR(lua_yield)//tex: Using default implementation.  DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)
			CREATE_FUNCPTR(lua_resume)//TEST
			//CREATE_FUNCPTR(lua_status)//TEST //tex: Using default implementation.

			//...

			CREATE_FUNCPTR(lua_gc)//TEST


			/*
			** miscellaneous functions
			*/

			CREATE_FUNCPTR(lua_error)//TEST

			CREATE_FUNCPTR(lua_next)//TEST

			CREATE_FUNCPTR(lua_concat)//TEST

			//CREATE_FUNCPTR(lua_getallocf)//
			//CREATE_FUNCPTR(lua_setallocf)//

			//...

			/* hack */
			//CREATE_FUNCPTR(lua_setlevel)//TEST

			//...

			CREATE_FUNCPTR(lua_getstack)//TEST
			CREATE_FUNCPTR(lua_getinfo)//TEST
			CREATE_FUNCPTR(lua_getlocal)//TEST
			CREATE_FUNCPTR(lua_setlocal)//TEST
			CREATE_FUNCPTR(lua_getupvalue)//TEST
			CREATE_FUNCPTR(lua_setupvalue)//TEST

			CREATE_FUNCPTR(lua_sethook)//TEST
			//CREATE_FUNCPTR(lua_gethook)//TEST //tex: Using default implementation.
			//CREATE_FUNCPTR(lua_gethookmask)//TEST //tex: Using default implementation.
			//CREATE_FUNCPTR(lua_gethookcount)//TEST //tex: Using default implementation.
		}//CreateHooks_Lua
	}//namespace lua

	extern bool isTargetExe;
	void CreateHooks_Lua(size_t BaseAddr, size_t RealBaseAddr) {
		lua::CreateFuncPtrs();
	}//CreateHooks_Lua
}//namespace IHHook