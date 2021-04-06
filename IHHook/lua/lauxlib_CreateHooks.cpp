#include "../HookMacros.h"
#include <lauxlib.h>

namespace IHHook {
	namespace lua_lauxlib {
		void GetRebasedAddresses(size_t BaseAddr, size_t RealBaseAddr) {
			//lauxlib.h

			//...
			GET_REBASED_ADDR(luaI_openlib)
				//OFF GET_REBASED_ADDR(luaL_register)//tex: Using default implementation.
				GET_REBASED_ADDR(luaL_getmetafield)//TEST
				GET_REBASED_ADDR(luaL_callmeta)//TEST
				GET_REBASED_ADDR(luaL_typerror)//TEST
				GET_REBASED_ADDR(luaL_argerror)//TEST
				GET_REBASED_ADDR(luaL_checklstring)//TEST
				GET_REBASED_ADDR(luaL_optlstring)//TEST
				GET_REBASED_ADDR(luaL_checknumber)//TEST
				//OFF GET_REBASED_ADDR(luaL_optnumber)//tex: Using default implementation. Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes

				GET_REBASED_ADDR(luaL_checkinteger)//TEST
				GET_REBASED_ADDR(luaL_optinteger)//TEST

				GET_REBASED_ADDR(luaL_checkstack)//TEST
				GET_REBASED_ADDR(luaL_checktype)//TEST
				GET_REBASED_ADDR(luaL_checkany)//TEST

				GET_REBASED_ADDR(luaL_newmetatable)//TEST
				GET_REBASED_ADDR(luaL_checkudata)//TEST

				GET_REBASED_ADDR(luaL_where)//TEST
				GET_REBASED_ADDR(luaL_error)//TEST

				GET_REBASED_ADDR(luaL_checkoption)//TEST

				//OFF GET_REBASED_ADDR(luaL_ref)//tex: Using default implementation. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param
				//OFF GET_REBASED_ADDR(luaL_unref)//tex: Using default implementation.

				GET_REBASED_ADDR(luaL_loadfile)//TEST
				GET_REBASED_ADDR(luaL_loadbuffer)//TEST
				//OFF GET_REBASED_ADDR(luaL_loadstring)//tex: Using default implementation.
				GET_REBASED_ADDR(luaL_newstate)

				GET_REBASED_ADDR(luaL_gsub)//TEST

				GET_REBASED_ADDR(luaL_findtable)//TEST


				//...

				/*
				** {======================================================
				** Generic Buffer manipulation
				** =======================================================
				*/

				//GET_REBASED_ADDR(luaL_buffinit)//TEST //tex: Using default implementation.
				GET_REBASED_ADDR(luaL_prepbuffer)
				GET_REBASED_ADDR(luaL_addlstring)//TEST
				//OFF GET_REBASED_ADDR(luaL_addstring)//tex: Using default implementation. Only call in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
				GET_REBASED_ADDR(luaL_addvalue)//TEST
				GET_REBASED_ADDR(luaL_pushresult)//TEST
		}//GetRebasedAddresses

		void GetSigAddresses(size_t BaseAddr, size_t RealBaseAddr) {
			//lauxlib.h

			//...
			GET_SIG_ADDR(luaI_openlib)
				//OFF GET_SIG_ADDR(luaL_register)//tex: Using default implementation.
				GET_SIG_ADDR(luaL_getmetafield)//TEST
				GET_SIG_ADDR(luaL_callmeta)//TEST
				GET_SIG_ADDR(luaL_typerror)//TEST
				GET_SIG_ADDR(luaL_argerror)//TEST
				GET_SIG_ADDR(luaL_checklstring)//TEST
				GET_SIG_ADDR(luaL_optlstring)//TEST
				GET_SIG_ADDR(luaL_checknumber)//TEST
				//OFF GET_SIG_ADDR(luaL_optnumber)//tex: Using default implementation. Only use in os_difftime, but decompilation is giving a bunch more params than it usually takes

				GET_SIG_ADDR(luaL_checkinteger)//TEST
				GET_SIG_ADDR(luaL_optinteger)//TEST

				GET_SIG_ADDR(luaL_checkstack)//TEST
				GET_SIG_ADDR(luaL_checktype)//TEST
				GET_SIG_ADDR(luaL_checkany)//TEST

				GET_SIG_ADDR(luaL_newmetatable)//TEST
				GET_SIG_ADDR(luaL_checkudata)//TEST

				GET_SIG_ADDR(luaL_where)//TEST
				GET_SIG_ADDR(luaL_error)//TEST

				GET_SIG_ADDR(luaL_checkoption)//TEST

				//OFF GET_SIG_ADDR(luaL_ref)//tex: Using default implementation. No uses in lua dist, found a function that looks much like it, but it was undefined, and has a errant param
				//OFF GET_SIG_ADDR(luaL_unref)//tex: Using default implementation.

				GET_SIG_ADDR(luaL_loadfile)//TEST
				GET_SIG_ADDR(luaL_loadbuffer)//TEST
				//OFF GET_SIG_ADDR(luaL_loadstring)//tex: Using default implementation.
				GET_SIG_ADDR(luaL_newstate)

				GET_SIG_ADDR(luaL_gsub)//TEST

				GET_SIG_ADDR(luaL_findtable)//TEST


				//...

				/*
				** {======================================================
				** Generic Buffer manipulation
				** =======================================================
				*/

				//GET_SIG_ADDR(luaL_buffinit)//TEST //tex: Using default implementation.
				GET_SIG_ADDR(luaL_prepbuffer)
				GET_SIG_ADDR(luaL_addlstring)//TEST
				//OFF GET_SIG_ADDR(luaL_addstring)//tex: Using default implementation. Only call in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
				GET_SIG_ADDR(luaL_addvalue)//TEST
				GET_SIG_ADDR(luaL_pushresult)//TEST
		}//GetSigAddresses

		void CreateFuncPtrs() {
			//lauxlib.h

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

				//CREATE_FUNCPTR(luaL_buffinit)//TEST //tex: Using default implementation.
				CREATE_FUNCPTR(luaL_prepbuffer)
				CREATE_FUNCPTR(luaL_addlstring)//TEST
				//OFF CREATE_FUNCPTR(luaL_addstring)//tex: Using default implementation. Only call in luaL_gsub, seems to have been optimized out as the function just wraps luaL_addlstring
				CREATE_FUNCPTR(luaL_addvalue)//TEST
				CREATE_FUNCPTR(luaL_pushresult)//TEST
		}//CreateFuncPtrs
	}//namespace lua_lauxlib

	extern bool isTargetExe;
	void CreateHooks_Lauxlib(size_t BaseAddr, size_t RealBaseAddr) {
		if (isTargetExe) {
			lua_lauxlib::GetRebasedAddresses(BaseAddr, RealBaseAddr);
		}
		else {
			lua_lauxlib::GetSigAddresses(BaseAddr, RealBaseAddr);
		}

		lua_lauxlib::CreateFuncPtrs();
	}//CreateHooks_Lauxlib
}//namespace IHHook