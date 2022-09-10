#pragma once
#include "windowsapi.h"
#include <Psapi.h>// ModuleInfo, DEBUGNOW
#include <vector>
#include <string>

namespace IHHook {
	namespace MemoryUtils {
		uintptr_t sigscan(const char* name,  const char* sig,  const char* mask);
		char* ScanModIn(char* pattern, char* mask, std::string modName);
		uint32_t* PatternScanWithHint(const char* name, const char* pattern);
		std::uint8_t* PatternScan(const char* pattern);

		void* RebasePointer(uintptr_t address);
		uintptr_t MultilevelPointer(uintptr_t ptr, std::vector<uintptr_t> offsets);
		void Patch(BYTE* dst, BYTE* src, unsigned int size);
		void Nop(BYTE* dst, unsigned int size);
	}//namespace MemoryUtils
}//namespace IHHook

