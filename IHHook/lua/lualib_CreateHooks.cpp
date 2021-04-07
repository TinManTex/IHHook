#include "../HookMacros.h"
#include <lualib.h>

namespace IHHook {
	namespace lualib {
		void GetRebasedAddresses(size_t BaseAddr, size_t RealBaseAddr) {
			//lualib.h

			GET_REBASED_ADDR(luaopen_base)//TEST

			GET_REBASED_ADDR(luaopen_table)//TEST

			GET_REBASED_ADDR(luaopen_io)//TEST

			GET_REBASED_ADDR(luaopen_os)//TEST

			GET_REBASED_ADDR(luaopen_string)//TEST

			GET_REBASED_ADDR(luaopen_math)//TEST

			GET_REBASED_ADDR(luaopen_debug)//TEST

			GET_REBASED_ADDR(luaopen_package)//TEST

			GET_REBASED_ADDR(luaL_openlibs)
		}//GetRebasedAddresses

		void GetSigAddresses(size_t BaseAddr, size_t RealBaseAddr) {
			//lualib.h

			GET_SIG_ADDR(luaopen_base)//TEST

			GET_SIG_ADDR(luaopen_table)//TEST

			GET_SIG_ADDR(luaopen_io)//TEST

			GET_SIG_ADDR(luaopen_os)//TEST

			GET_SIG_ADDR(luaopen_string)//TEST

			GET_SIG_ADDR(luaopen_math)//TEST

			GET_SIG_ADDR(luaopen_debug)//TEST

			GET_SIG_ADDR(luaopen_package)//TEST

			GET_SIG_ADDR(luaL_openlibs)
		}//GetSigAddresses
		void CreateFuncPtrs() {
			//lualib.h

			CREATE_FUNCPTR(luaopen_base)//TEST

			CREATE_FUNCPTR(luaopen_table)//TEST

			CREATE_FUNCPTR(luaopen_io)//TEST

			CREATE_FUNCPTR(luaopen_os)//TEST

			CREATE_FUNCPTR(luaopen_string)//TEST

			CREATE_FUNCPTR(luaopen_math)//TEST

			CREATE_FUNCPTR(luaopen_debug)//TEST

			CREATE_FUNCPTR(luaopen_package)//TEST

			CREATE_FUNCPTR(luaL_openlibs)
		}//CreateFuncPtrs
	}//namespace lualib

	extern bool isTargetExe;
	void CreateHooks_Lualib(size_t BaseAddr, size_t RealBaseAddr) {
		if (isTargetExe) {
			lualib::GetRebasedAddresses(BaseAddr, RealBaseAddr);
		}
		else {
			lualib::GetSigAddresses(BaseAddr, RealBaseAddr);
		}

		lualib::CreateFuncPtrs();
	}//CreateHooks_Lualib
}//namespace IHHook