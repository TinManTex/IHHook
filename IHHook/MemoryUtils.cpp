#include "MemoryUtils.h"
#include "windowsapi.h"
#include <Psapi.h>//GetModuleInformation
#include <vector>
#include <chrono>
#include <spdlog/spdlog.h>
#include "ntdll.h"//DEBUGNOW

namespace IHHook {
	namespace MemoryUtils {
		/**
		 * get_module_bounds - Get the boundaries of a module
		 * @name:	Name of module
		 * @start:	Pointer to copy start of module bounds to
		 * @end:	Pointer to copy end of module bounds to
		 *
		 * Get the module handle and use GetModuleInformation to get its bounds
		 * cribbed from fov mod
		 * used by sigscan
		 */
		bool get_module_bounds(const char* name, uintptr_t* start, uintptr_t* end) {
			const auto module = GetModuleHandleA(name);
			if (module == nullptr)
				return false;

			MODULEINFO info;
			HANDLE currentProcess = GetCurrentProcess();
			GetModuleInformation(currentProcess, module, &info, sizeof(info));
			*start = (uintptr_t)(info.lpBaseOfDll);
			*end = *start + info.SizeOfImage;
			return true;
		}//get_module_bounds

		/**
		 * sigscan - Scan for a code pattern
		 * @name:	name of function for logging
		 * @sig:	Byte sequence to scan for
		 * @mask:	Wildcard mask, ?s will make the corresponding index in sig be
		 *		ignored
		 *
		 * Check if the pattern matches starting at each byte from start to end.
		 * cribbed from fov mod
		 * 
		 * REF
		 *	sig="\x48\x8B\x8F\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x18\x48\x8D\x4F\xE0\xE8",
		 *	mask="xxx????xxxxxxxxxxx";
		 */
		uintptr_t sigscan(const char* name, const char* sig, const char* mask) {
			auto tstart = std::chrono::high_resolution_clock::now();

			//DEBUGNOW name used to be module name
			uintptr_t start, end;
			if (!get_module_bounds(NULL, &start, &end))
				throw std::runtime_error("Module not loaded");

			const auto last_scan = end - strlen(mask) + 1;
			for (auto addr = start; addr < last_scan; addr++) {
				for (size_t i = 0;; i++) {
					if (mask[i] == '\0') {
						auto tend = std::chrono::high_resolution_clock::now();
						auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
						spdlog::debug("sigscan found {} at 0x{:x} in(microseconds): {}", name, addr, duration);//DEBUGNOW dump addr
						return addr;
					}
					if (mask[i] != '?' && sig[i] != *(char*)(addr + i))
						break;
				}
			}
			auto tend = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
			spdlog::debug("sigscan not found {} in(microseconds): {}", name, duration);
			return NULL;
		}//sigscan

		//gh scanner https://guidedhacking.com/threads/external-internal-pattern-scanning-guide.14112/ >
		/// <summary>
		/// Actual pattern scanning, rest of functions basically narrow down the range of memory to scan
		/// </summary>
		/// <param name="pattern"></param>
		/// <param name="mask"></param>
		/// <param name="begin">address of buffer to scan</param>
		/// <param name="size">size of that buffer</param>
		/// <returns></returns>
		char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size) {
			auto tstart = std::chrono::high_resolution_clock::now();
			intptr_t patternLen = strlen(mask);

			for (int i = 0; i < size; i++) {
				bool found = true;
				for (int j = 0; j < patternLen; j++) {
					if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j)) {
						found = false;
						break;
					}
				}
				if (found) {
					auto tend = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
					spdlog::debug("sigscan found  in(microseconds): {}", duration);//DEBUGNOW name, dump addr
					return (begin + i);
				}
			}
			auto tend = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
			spdlog::debug("sigscan not found in(microseconds): {}", duration);//DEBUGNOW name, addr
			return nullptr;
		}//ScanBasic

		//narrow down to valid memory
		//DEBUGNOW
		//- Scanning pages with PAGE_GUARD protection raises exception, if not handled it crashes. Solution: Don't scan those pages or use VirtualProtect().
		//guard page stuff sure, dont need to vprotect, can just wrap in try/except, whatever your preference is
		char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size) {
			char* match{ nullptr };
			MEMORY_BASIC_INFORMATION mbi{};

			for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize) {
				if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) continue;
				match = ScanBasic(pattern, mask, curr, mbi.RegionSize);

				if (match != nullptr) {
					break;
				}
			}
			return match;
		}//ScanInternal

		char* TO_CHAR(wchar_t* string) {
			size_t len = wcslen(string) + 1;
			char* c_string = new char[len];
			size_t numCharsRead;
			wcstombs_s(&numCharsRead, c_string, len, string, _TRUNCATE);
			return c_string;
		}//TO_CHAR

		PEB* GetPEB() {
#ifdef _WIN64
			PEB* peb = (PEB*)__readgsqword(0x60);

#else
			PEB* peb = (PEB*)__readfsdword(0x30);
#endif

			return peb;
		}//GetPEB

		LDR_DATA_TABLE_ENTRY* GetLDREntry(std::string name) {
			LDR_DATA_TABLE_ENTRY* ldr = nullptr;

			PEB* peb = GetPEB();

			LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;

			LIST_ENTRY curr = head;

			while (curr.Flink != head.Blink) {
				LDR_DATA_TABLE_ENTRY* mod = (LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(curr.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

				if (mod->FullDllName.Buffer) {
					char* cName = TO_CHAR(mod->BaseDllName.Buffer);

					if (_stricmp(cName, name.c_str()) == 0) {
						ldr = mod;
						break;
					}
					delete[] cName;
				}
				curr = *curr.Flink;
			}
			return ldr;
		}//GetLDREntry

		//Actual sig scan function to use
		//narrows down memory to scan even further to the modules ldr entries 
		//ultimately not much different than getting module information but:
		//Why do you prefer walking the module list in the PEB ?
		//	#1 stealth
		//	#2 if they do hooks to prevent you from finding the module, you can still find it in PEB, they would have to unlink it from the PEB or manual map to make the PEB lookup fail
		char* ScanModIn(char* pattern, char* mask, std::string modName) {
			LDR_DATA_TABLE_ENTRY* ldr = GetLDREntry(modName);

			//DEBUGNOW char* match = ScanInternal(pattern, mask, (char*)ldr->DllBase, ldr->SizeOfImage);//DEBUGNOW ScanInternal memory validation just ends up not finding the required sigs
			char* match = ScanBasic(pattern, mask, (char*)ldr->DllBase, ldr->SizeOfImage);//DEBUGNOW

			return match;
		}//ScanModIn

		//< gh scanner

		//IN/SIDE: BaseAddr, RealBaseAddr
		//void* RebasePointer(uintptr_t address) {
		//	return (void*)((address - BaseAddr) + RealBaseAddr);
		//}//RebasePointer

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