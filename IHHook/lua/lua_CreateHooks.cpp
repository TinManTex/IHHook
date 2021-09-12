#include "../HookMacros.h"
#include <lua.h>
#include "lua_Signatures.h"

namespace IHHook {
	namespace lua {
		void GetRebasedAddresses(size_t BaseAddr, size_t RealBaseAddr) {
			//lua.h

			//...

			/*
			** state manipulation
			*/
			GET_REBASED_ADDR(lua_newstate)//TEST
			GET_REBASED_ADDR(lua_close)//TEST
			GET_REBASED_ADDR(lua_newthread)

			GET_REBASED_ADDR(lua_atpanic)//TEST

			/*
			** basic stack manipulation
			*/
			//GET_REBASED_ADDR(lua_gettop)//tex: Using default implementation.
			GET_REBASED_ADDR(lua_settop)
			GET_REBASED_ADDR(lua_pushvalue)
			GET_REBASED_ADDR(lua_remove)
			GET_REBASED_ADDR(lua_insert)
			GET_REBASED_ADDR(lua_replace)
			GET_REBASED_ADDR(lua_checkstack)//TEST

			GET_REBASED_ADDR(lua_xmove)//TEST

			//*
			/** access functions (stack -> C)
			/*/

			GET_REBASED_ADDR(lua_isnumber)
			GET_REBASED_ADDR(lua_isstring)
			GET_REBASED_ADDR(lua_iscfunction)
			//GET_REBASED_ADDR(lua_isuserdata)//TEST tex: Using default implementation. No calls in lua distro, so may be hard to find, or have been culled by compilation
			GET_REBASED_ADDR(lua_type)
			//GET_REBASED_ADDR(lua_typename)//tex: Using default implementation. 

			//GET_REBASED_ADDR(lua_equal)//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
			GET_REBASED_ADDR(lua_rawequal)
			GET_REBASED_ADDR(lua_lessthan)

			GET_REBASED_ADDR(lua_tonumber)
			GET_REBASED_ADDR(lua_tointeger)
			GET_REBASED_ADDR(lua_toboolean)
			GET_REBASED_ADDR(lua_tolstring)
			GET_REBASED_ADDR(lua_objlen)//TEST
			GET_REBASED_ADDR(lua_tocfunction)//TEST
			GET_REBASED_ADDR(lua_touserdata)//TEST
			GET_REBASED_ADDR(lua_tothread)//TEST
			GET_REBASED_ADDR(lua_topointer)//TEST


			/*
			** push functions (C -> stack)
			*/
			GET_REBASED_ADDR(lua_pushnil)//TEST
			GET_REBASED_ADDR(lua_pushnumber)
			GET_REBASED_ADDR(lua_pushinteger)
			GET_REBASED_ADDR(lua_pushlstring)
			GET_REBASED_ADDR(lua_pushstring)
			GET_REBASED_ADDR(lua_pushvfstring)//TEST
			GET_REBASED_ADDR(lua_pushfstring)//TEST
			GET_REBASED_ADDR(lua_pushcclosure)//TEST
			GET_REBASED_ADDR(lua_pushboolean)
			GET_REBASED_ADDR(lua_pushlightuserdata)//TEST
			GET_REBASED_ADDR(lua_pushthread)//TEST

			/*
			** get functions (Lua -> stack)
			*/
			GET_REBASED_ADDR(lua_gettable)
			GET_REBASED_ADDR(lua_getfield)
			GET_REBASED_ADDR(lua_rawget)
			GET_REBASED_ADDR(lua_rawgeti)
			GET_REBASED_ADDR(lua_createtable)
			GET_REBASED_ADDR(lua_newuserdata)//TEST
			GET_REBASED_ADDR(lua_getmetatable)//TEST
			GET_REBASED_ADDR(lua_getfenv)//TEST


			/*
			** set functions (stack -> Lua)
			*/
			GET_REBASED_ADDR(lua_settable)
			GET_REBASED_ADDR(lua_setfield)
			GET_REBASED_ADDR(lua_rawset)
			GET_REBASED_ADDR(lua_rawseti)
			GET_REBASED_ADDR(lua_setmetatable)//TEST
			GET_REBASED_ADDR(lua_setfenv)//TEST


			/*
			** `load' and `call' functions (load and run Lua code)
			*/
			GET_REBASED_ADDR(lua_call)//TEST
			GET_REBASED_ADDR(lua_pcall)//TEST
			GET_REBASED_ADDR(lua_cpcall)//TEST
			GET_REBASED_ADDR(lua_load)//TEST

			GET_REBASED_ADDR(lua_dump)//TEST

			/*
			** coroutine functions
			*/
			//GET_REBASED_ADDR(lua_yield)//tex: Using default implementation.  DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)
			GET_REBASED_ADDR(lua_resume)//TEST
			//GET_REBASED_ADDR(lua_status)//TEST //tex: Using default implementation.

			//...

			GET_REBASED_ADDR(lua_gc)//TEST


			/*
			** miscellaneous functions
			*/

			GET_REBASED_ADDR(lua_error)//TEST

			GET_REBASED_ADDR(lua_next)//TEST

			GET_REBASED_ADDR(lua_concat)//TEST

			//GET_REBASED_ADDR(lua_getallocf)//
			//GET_REBASED_ADDR(lua_setallocf)//

			//...

			/* hack */
			//GET_REBASED_ADDR(lua_setlevel)//TEST

			//...

			GET_REBASED_ADDR(lua_getstack)//TEST
			GET_REBASED_ADDR(lua_getinfo)//TEST
			GET_REBASED_ADDR(lua_getlocal)//TEST
			GET_REBASED_ADDR(lua_setlocal)//TEST
			GET_REBASED_ADDR(lua_getupvalue)//TEST
			GET_REBASED_ADDR(lua_setupvalue)//TEST

			GET_REBASED_ADDR(lua_sethook)//TEST
			//GET_REBASED_ADDR(lua_gethook)//TEST //tex: Using default implementation.
			//GET_REBASED_ADDR(lua_gethookmask)//TEST //tex: Using default implementation.
			//GET_REBASED_ADDR(lua_gethookcount)//TEST //tex: Using default implementation.
		}//GetRebasedAddresses

		void GetSigAddresses(size_t BaseAddr, size_t RealBaseAddr) {
			//lua.h

			//...

			/*
			** state manipulation
			*/
			GET_SIG_ADDR(lua_newstate)//TEST
			GET_SIG_ADDR(lua_close)//TEST
			GET_SIG_ADDR(lua_newthread)

			GET_SIG_ADDR(lua_atpanic)//TEST

			/*
			** basic stack manipulation
			*/
			//GET_SIG_ADDR(lua_gettop)//tex: Using default implementation.
			GET_SIG_ADDR(lua_settop)
			GET_SIG_ADDR(lua_pushvalue)
			GET_SIG_ADDR(lua_remove)
			GET_SIG_ADDR(lua_insert)
			GET_SIG_ADDR(lua_replace)
			GET_SIG_ADDR(lua_checkstack)//TEST

			GET_SIG_ADDR(lua_xmove)//TEST

			//*
			/** access functions (stack -> C)
			/*/

			GET_SIG_ADDR(lua_isnumber)
			GET_SIG_ADDR(lua_isstring)
			GET_SIG_ADDR(lua_iscfunction)
			//GET_SIG_ADDR(lua_isuserdata)//TEST tex: Using default implementation. No calls in lua distro, so may be hard to find, or have been culled by compilation
			GET_SIG_ADDR(lua_type)
			//GET_SIG_ADDR(lua_typename)//tex: Using default implementation. 

			//GET_SIG_ADDR(lua_equal)//tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation
			GET_SIG_ADDR(lua_rawequal)
			GET_SIG_ADDR(lua_lessthan)

			GET_SIG_ADDR(lua_tonumber)
			GET_SIG_ADDR(lua_tointeger)
			GET_SIG_ADDR(lua_toboolean)
			GET_SIG_ADDR(lua_tolstring)
			GET_SIG_ADDR(lua_objlen)//TEST
			GET_SIG_ADDR(lua_tocfunction)//TEST
			GET_SIG_ADDR(lua_touserdata)//TEST
			GET_SIG_ADDR(lua_tothread)//TEST
			GET_SIG_ADDR(lua_topointer)//TEST


			/*
			** push functions (C -> stack)
			*/
			GET_SIG_ADDR(lua_pushnil)//TEST
			GET_SIG_ADDR(lua_pushnumber)
			GET_SIG_ADDR(lua_pushinteger)
			GET_SIG_ADDR(lua_pushlstring)
			GET_SIG_ADDR(lua_pushstring)
			GET_SIG_ADDR(lua_pushvfstring)//TEST
			GET_SIG_ADDR(lua_pushfstring)//TEST
			GET_SIG_ADDR(lua_pushcclosure)//TEST
			GET_SIG_ADDR(lua_pushboolean)
			GET_SIG_ADDR(lua_pushlightuserdata)//TEST
			GET_SIG_ADDR(lua_pushthread)//TEST

			/*
			** get functions (Lua -> stack)
			*/
			GET_SIG_ADDR(lua_gettable)
			GET_SIG_ADDR(lua_getfield)
			GET_SIG_ADDR(lua_rawget)
			GET_SIG_ADDR(lua_rawgeti)
			GET_SIG_ADDR(lua_createtable)
			GET_SIG_ADDR(lua_newuserdata)//TEST
			GET_SIG_ADDR(lua_getmetatable)//TEST
			GET_SIG_ADDR(lua_getfenv)//TEST


			/*
			** set functions (stack -> Lua)
			*/
			GET_SIG_ADDR(lua_settable)
			GET_SIG_ADDR(lua_setfield)
			GET_SIG_ADDR(lua_rawset)
			GET_SIG_ADDR(lua_rawseti)
			GET_SIG_ADDR(lua_setmetatable)//TEST
			GET_SIG_ADDR(lua_setfenv)//TEST


			/*
			** `load' and `call' functions (load and run Lua code)
			*/
			GET_SIG_ADDR(lua_call)//TEST
			GET_SIG_ADDR(lua_pcall)//TEST
			GET_SIG_ADDR(lua_cpcall)//TEST
			GET_SIG_ADDR(lua_load)//TEST

			GET_SIG_ADDR(lua_dump)//TEST

			/*
			** coroutine functions
			*/
			//GET_SIG_ADDR(lua_yield)//tex: Using default implementation.  DEBUGNOW uses lua_lock, may not be a good idea due to thread issues and not knowing what the engine is doing to the state. Seems to be inlined in luaB_yield (it's only call in lua distro)
			GET_SIG_ADDR(lua_resume)//TEST
			//GET_SIG_ADDR(lua_status)//TEST //tex: Using default implementation.

			//...

			GET_SIG_ADDR(lua_gc)//TEST


			/*
			** miscellaneous functions
			*/

			GET_SIG_ADDR(lua_error)//TEST

			GET_SIG_ADDR(lua_next)//TEST

			GET_SIG_ADDR(lua_concat)//TEST

			//GET_SIG_ADDR(lua_getallocf)//
			//GET_SIG_ADDR(lua_setallocf)//

			//...

			/* hack */
			//GET_SIG_ADDR(lua_setlevel)//TEST

			//...

			GET_SIG_ADDR(lua_getstack)//TEST
			GET_SIG_ADDR(lua_getinfo)//TEST
			GET_SIG_ADDR(lua_getlocal)//TEST
			GET_SIG_ADDR(lua_setlocal)//TEST
			GET_SIG_ADDR(lua_getupvalue)//TEST
			GET_SIG_ADDR(lua_setupvalue)//TEST

			GET_SIG_ADDR(lua_sethook)//TEST
			//GET_SIG_ADDR(lua_gethook)//TEST //tex: Using default implementation.
			//GET_SIG_ADDR(lua_gethookmask)//TEST //tex: Using default implementation.
			//GET_SIG_ADDR(lua_gethookcount)//TEST //tex: Using default implementation.
		}//GetSigAddresses

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
		if (isTargetExe) {
			lua::GetRebasedAddresses(BaseAddr, RealBaseAddr);
		}
		else {
			lua::GetSigAddresses(BaseAddr, RealBaseAddr);
		}

		lua::CreateFuncPtrs();
	}//CreateHooks_Lua
}//namespace IHHook