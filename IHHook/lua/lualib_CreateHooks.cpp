#include "../HookMacros.h"
#include <lualib.h>

namespace IHHook {
void CreateHooks_Lualib(size_t BaseAddr, size_t RealBaseAddr) {
	//lualib.h

	CREATEHOOK(luaopen_base)//TEST

	CREATEHOOK(luaopen_table)//TEST

	CREATEHOOK(luaopen_io)//TEST

	CREATEHOOK(luaopen_os)//TEST

	CREATEHOOK(luaopen_string)//TEST

	CREATEHOOK(luaopen_math)//TEST

	CREATEHOOK(luaopen_debug)//TEST

	CREATEHOOK(luaopen_package)//TEST

	CREATEHOOK(luaL_openlibs)
}//CreateHooks_Luaxlib
}//namespace IHHook