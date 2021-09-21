#include "../HookMacros.h"
#include <lualib.h>

namespace IHHook {
	namespace lualib {
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
		lualib::CreateFuncPtrs();
	}//CreateHooks_Lualib
}//namespace IHHook