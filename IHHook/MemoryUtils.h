#pragma once
#include "windowsapi.h"
#include <vector>

namespace IHHook {
	namespace MemoryUtils {
		void* RebasePointer(uintptr_t address);
		uintptr_t MultilevelPointer(uintptr_t ptr, std::vector<uintptr_t> offsets);
		void Patch(BYTE* dst, BYTE* src, unsigned int size);
		void Nop(BYTE* dst, unsigned int size);
	}//namespace MemoryUtils
}//namespace IHHook

