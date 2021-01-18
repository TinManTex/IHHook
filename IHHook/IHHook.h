//IHHook: A Dll proxy to extend MGSV for modding
//tex: can run without Infinite Heaven, but IH will use it.

//Based on the bones of CityHook: https://github.com/emoose/MGSV-QAR-Dictionary-Project/tree/master/CityHook

//Trying to get coverage of whole LUALIB_API functions so that lua c modules can be compiled in
//The resulting method seems like a huge hack, and there's probably a smarter way to do it. But it works.

//Entry point in dllmain.cpp
//Hooking using MinHook: https://github.com/TsudaKageyu/minhook 
//Logging via spdlog: https://github.com/gabime/spdlog , header only implementation in IHHook\spdlog, but not included in the project/solution explorer just for clarity

//Lua 5.1.5 implementation a mix of hooks and the normal definitions, entire distro files are in IHHook\lua, but as above only modified files included in project/solution explorer for clarity.
//using hooking via addresses, which is fragile to new exe updates
//but haven't got a sigscanning workflow yet to not kill myself with the large number functions I'm hooking

//Encoding is a mess having pulled in so much code from other projects, and then, should probably try to standardise to utf8 at some point.

#pragma once
#include "windowsapi.h"
#include <string>
#include <queue>
#include <mutex>
#include <spdlog/spdlog.h>

namespace IHHook {
	static const bool debugMode = true;//DEBUGNOW //DEBUG CONFIG //TODO debug level instead
	static const bool openConsole = false;//DEBUG CONFIG
	static const bool enableCityHook = false;//DEBUG CONFIG

	static const int Version = 4; //SYNC: fileVersion
	static const DWORD GameVersion[4] = { 1, 0, 15, 1 }; //tex: version checking game exe
	static const std::wstring exeName = L"mgsvtpp.exe";

	static const std::wstring hookLogName = L"ihhook_log.txt";
	static const std::wstring hookLogNamePrev = L"ihhook_log_prev.txt";

	static const std::wstring pipeInName = L"\\\\.\\pipe\\mgsv_in";
	static const std::wstring pipeOutName = L"\\\\.\\pipe\\mgsv_out";

	static const size_t BaseAddr = 0x140000000; // from ImageBase field in the EXE
	extern size_t RealBaseAddr; // Current base address of the EXE

	extern HMODULE thisModule;

	void Shutdown();

	class IHH {
	public:
		IHH();
		virtual ~IHH();

		HMODULE GetModule() {
			return thisModule;
		}
	private:
		HMODULE thisModule{ 0 };

		std::shared_ptr<spdlog::logger> log;
	};

	extern std::unique_ptr<IHH> g_ihhook;
}//namespace IHHook
