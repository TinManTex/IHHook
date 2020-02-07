#pragma once

#include <stdint.h>

namespace IHHook {
	namespace Hooks_TPP {
		uint32_t* missionCode;

		void CreateHooks_TPP(size_t RealBaseAddr);
	}//namespace Hooks_TPP
}//namespace IHHook