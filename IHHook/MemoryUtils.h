#pragma once
#include "windowsapi.h"
#include <Psapi.h>// ModuleInfo, DEBUGNOW
#include <vector>

namespace IHHook {
	namespace MemoryUtils {
		uintptr_t sigscan(const char* name, const char* sig, const char* mask);
		uintptr_t FindPattern(const char* name, LPCWSTR module, char* pattern, char* mask);
		PBYTE FindSignature(const char* name, LPVOID BaseAddress, DWORD ImageSize, PCHAR Signature, PCHAR Mask);
		MODULEINFO GetModuleInfo(LPCWSTR szModule);

		void* RebasePointer(uintptr_t address);
		uintptr_t MultilevelPointer(uintptr_t ptr, std::vector<uintptr_t> offsets);
		void Patch(BYTE* dst, BYTE* src, unsigned int size);
		void Nop(BYTE* dst, unsigned int size);
	}//namespace MemoryUtils
}//namespace IHHook

