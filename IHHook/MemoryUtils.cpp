#include "MemoryUtils.h"
#include "IHHook.h"
#include "windowsapi.h"
#include <vector>

namespace IHHook {
	namespace MemoryUtils {
		//TODO move to utils or something
		//IN/SIDE: BaseAddr, RealBaseAddr
		void* RebasePointer(uintptr_t address) {
			return (void*)((address - BaseAddr) + RealBaseAddr);
		}//RebasePointer

		//tex follows a pointer chain and returns the address of the base pointer
		uintptr_t MultilevelPointer(uintptr_t ptr, std::vector<uintptr_t> offsets) {
			uintptr_t addr = ptr;
			for (unsigned int i = 0; i < offsets.size(); ++i) {
				addr = *(uintptr_t*)addr;
				addr += offsets[i];
			}
			return addr;
		}//MultilevelPointer

		void Patch(BYTE* dst, BYTE* src, unsigned int size) {
			DWORD oldProtect;
			VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
			memcpy(dst, src, size);
			VirtualProtect(dst, size, oldProtect, &oldProtect);
		}//Patch

		void Nop(BYTE* dst, unsigned int size) {
			DWORD oldProtect;
			VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
			memset(dst, 0x90, size);
			VirtualProtect(dst, size, oldProtect, &oldProtect);
		}//Patch
	}//namespace MemoryUtils
}//namespace IHHook