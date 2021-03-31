#pragma once

#include <stdint.h>
#include "HookMacros.h"
namespace IHHook {
	FUNCPTRDEF(long long, StrCode64, const char* str, long long len)
	//DEBUGNOW
	//typedef long long ( __fastcall StrCode64Func ) (const char* str, long long len);
	//extern StrCode64Func* StrCode64;

	namespace Hooks_TPP {
		static uint32_t* missionCode;

		void CreateHooks(size_t RealBaseAddr);
	}//namespace Hooks_TPP
}//namespace IHHook