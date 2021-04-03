#include "MemoryUtils.h"
#include "windowsapi.h"
#include <Psapi.h>//GetModuleInformation
#include <vector>
#include <chrono>
#include <spdlog/spdlog.h>

//DEBUGNOW TODO: figure out which sig scan to use, cull the others

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
						spdlog::debug("sigscan found {} in(microseconds): {}", name, duration);
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

		//Get all module related info, this will include the base DLL and the size of the module
		//used by FindPattern
		MODULEINFO GetModuleInfo(LPCWSTR szModule) {
			MODULEINFO modinfo = { 0 };
			HMODULE hModule = GetModuleHandle(szModule);
			if (hModule == 0)
				return modinfo;
			GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
			return modinfo;
		}

		//Pattern Scan https://guidedhacking.com/threads/c-signature-scan-pattern-scanning-tutorial-difficulty-3-10.3981
		//REF
		//char* pattern = "\x45\x33\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC";
		//char* mask = "xx?x????xxxxxxxx";
		uintptr_t FindPattern(const char* name, LPCWSTR module, char* pattern, char* mask) {
			auto tstart = std::chrono::high_resolution_clock::now();
			spdlog::trace("FindPattern:");//DEBUGNOW
			spdlog::trace("Sig:{}", pattern);//DEBUGNOW
			spdlog::trace("Msk:{}", mask);//DEBUGNOW

			//Get all module related information
			MODULEINFO mInfo = GetModuleInfo(module);

			//Assign our base and module size
			uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;

			uintptr_t size = (uintptr_t)mInfo.SizeOfImage;

			//Get length for our mask, this will allow us to loop through our array
			DWORD patternLength = (DWORD)strlen(mask);

			for (DWORD i = 0; i < size - patternLength; i++) {
				bool found = true;
				for (DWORD j = 0; j < patternLength; j++) {
					//if we have a ? in our mask then we have true by default,
					//or if the bytes match then we keep searching until finding it or not
					found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
				}

				//found = true, our entire pattern was found
				if (found) {
					spdlog::trace("Pattern found : {x}", (base + i));
					auto tend = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
					spdlog::debug("FindPattern found {} in(microseconds): {}", name, duration);
					return base + i;
				}
			}
			auto tend = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
			spdlog::debug("FindPatter not found {} in(microseconds): {}", name, duration);
			return NULL;
		}//FindPattern

		//Used by FindSignature
		int CompareByteArray(PBYTE ByteArray1, PCHAR ByteArray2, PCHAR Mask, DWORD Length) {
			DWORD nextStart = 0;
			char start = ByteArray2[0];
			for (DWORD i = 0; i < Length; i++) {
				if (Mask[i] == '?') {
					continue;
				}
				if (ByteArray1[i] == start) {
					nextStart = i;
				}
				if (ByteArray1[i] != (BYTE)ByteArray2[i]) {
					return nextStart;
				}
			}
			return -1;
		}//CompareByteArray

		//tex not sure where I got this from lol
		//REF
		//char* sig = "\x45\x33\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC";
		//char* mask = "xx?x????xxxxxxxx";
		PBYTE FindSignature(const char* name, LPVOID BaseAddress, DWORD ImageSize, PCHAR Signature, PCHAR Mask) {
			auto tstart = std::chrono::high_resolution_clock::now();

			PBYTE Address = NULL;
			PBYTE Buffer = (PBYTE)BaseAddress;

			DWORD Length = strlen(Mask);
			for (DWORD i = 0; i < (ImageSize - Length); i++) {
				int result = CompareByteArray((Buffer + i), Signature, Mask, Length);
				if (result < 0) {
					Address = (PBYTE)BaseAddress + i;
					auto tend = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
					spdlog::debug("FindSignature found {} in(microseconds): {}", name, duration);
					return Address;
				}
				else {
					i += result;
				}
			}
			auto tend = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
			spdlog::debug("FindSignature not found {} in(microseconds): {}", name, duration);
			return NULL;
		}//FindSignature

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