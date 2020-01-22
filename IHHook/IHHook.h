#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <queue>
#include <mutex>

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

//#define ENABLE_CITYHOOK //tex uncomment to enable CityHook hash logging functionality, 
//NOTE: if you run cityhook with IH mod you'll end up picking up a bunch of IH stuff running through cityhash

namespace IHHook {
	static const int Version = 3;
	static const DWORD GameVersion[4] = { 1, 0, 15, 1 }; //tex: version checking game exe
	static const std::wstring exeName = L"mgsvtpp.exe";

	static const std::wstring hookLogName = L"ihhook_log.txt";
	static const std::wstring hookLogNamePrev = L"ihhook_log_prev.txt";

	static const size_t BaseAddr = 0x140000000; // from ImageBase field in the EXE

//tex create hooks // called from DLLMain
	void CreateHooks_CityHash(size_t RealBaseAddr);
	void CreateHooks_LuaIHH(size_t RealBaseAddr);



	//OS
	bool CheckVersion(const DWORD checkVersion[]);
	std::wstring GetGameDir();
	std::string GetGameDirA();
	int StartProcess(LPCWSTR lpApplicationPath, LPWSTR lpCommandLine);
	std::vector<std::string> GetFolderNames(std::string folder);
	std::vector<std::string> GetFileNames(std::string folder);
	bool ListFiles(std::string path, std::string mask, std::vector<std::string>& files);

	//PipeServer
	void StartPipeServer();
	void QueueMessageOut(std::string message);
	extern std::queue<std::string> messagesIn;
	extern std::mutex inMutex;
}
