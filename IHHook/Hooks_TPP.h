#pragma once

#include <stdint.h>

namespace IHHook {
	namespace Hooks_TPP {
		static uint32_t* missionCode;

		void CreateHooks(size_t RealBaseAddr);
	}//namespace Hooks_TPP
}//namespace IHHook