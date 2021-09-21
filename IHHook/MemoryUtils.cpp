#include "MemoryUtils.h"
#include "windowsapi.h"
#include <Psapi.h>//GetModuleInformation
#include <vector>
#include <chrono>
#include <spdlog/spdlog.h>
#include "ntdll.h"//gh scanner
#include "Hooking.Patterns/Hooking.Patterns.h"

//GH scanner taking longer than simple scanner

//DEBUGNOW TODO evaluate https://github.com/WopsS/RenHook pattern scanner (Yooungis recomendation), looks interesting in that its using std::scan


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

		//https://github.com/ThirteenAG/Hooking.Patterns
		//DEBUGNOW hint system seems interesting, but if you're going to serialize stuff just for performance why arent you dumping addresses themselves?
		//also its 10x slower than basic sig scan for some reason
		uint32_t* PatternScanWithHint(const char* name, const char* pattern) {
			auto tstart = std::chrono::high_resolution_clock::now();

			auto pattern_result = hook::pattern(pattern);
			if (!pattern_result.count_hint(1).empty()) {
				uint32_t* result = pattern_result.count(1).get(0).get<uint32_t>();
				auto tend = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
				spdlog::debug("sigscan found {} in(microseconds): {}", name, duration);
				return result;
			}
			else {
				auto tend = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
				spdlog::debug("sigscan not found {} in(microseconds): {}", name, duration);
			}

			return NULL;
		}//PatternScan

		/*
		 * @brief Scan for a given byte pattern on a module
		 *
		 * @Param module    Base of the module to search
		 * @Param signature IDA-style byte array pattern ex: "48 89 ? ? ? 57 48 83 EC ? 48 8B ? ? ? ? ? 48 89 ? 48 8D ? ? ? ? ? 48 85"
		 *
		 * @Returns Address of the first occurence
		 */
		std::uint8_t* PatternScan(const char* pattern) {
			static auto pattern_to_byte = [](const char* pattern) {
				auto bytes = std::vector<int>{};
				auto start = const_cast<char*>(pattern);
				auto end = const_cast<char*>(pattern) + strlen(pattern);

				for (auto current = start; current < end; ++current) {
					if (*current == '?') {
						++current;
						if (*current == '?')
							++current;
						bytes.push_back(-1);
					}
					else {
						bytes.push_back(strtoul(current, &current, 16));
					}
				}
				return bytes;
			};

			const auto module = GetModuleHandleA(NULL);
			auto dosHeader = (PIMAGE_DOS_HEADER)module;
			auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

			auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
			auto patternBytes = pattern_to_byte(pattern);
			auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

			auto patternSize = patternBytes.size();
			auto patternData = patternBytes.data();

			for (auto i = 0ul; i < sizeOfImage - patternSize; ++i) {
				bool found = true;
				for (auto j = 0ul; j < patternSize; ++j) {
					if (scanBytes[i + j] != patternData[j] && patternData[j] != -1) {
						found = false;
						break;
					}
				}
				if (found) {
					return &scanBytes[i];
				}
			}
			return nullptr;
		}//PatternScan

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