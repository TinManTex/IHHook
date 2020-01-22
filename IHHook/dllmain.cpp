
#include "stdafx.h"
#include <ctime>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"
#include "MinHook/MinHook.h" // MH_Initialize

HMODULE thisModule;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);//tex an optimisation aparently

		thisModule = hModule;

		//tex OFF
		/*
		AllocConsole();
		SetConsoleTitle(L"IHHook");
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
		printf("Console test\n");
		*/

		//tex DEBUG, logged below 
		TCHAR Buffer[MAX_PATH];
		DWORD dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
		std::wstring currentDir(Buffer);

		std::wstring gameDir = IHHook::GetGameDir();
		SetCurrentDirectory(gameDir.c_str());//tex so this dll and lua can use reletive paths

		DeleteFile(IHHook::hookLogNamePrev.c_str());
		CopyFile(IHHook::hookLogName.c_str(), IHHook::hookLogNamePrev.c_str(), false);
		DeleteFile(IHHook::hookLogName.c_str());

		auto log = spdlog::basic_logger_mt("ihhook", IHHook::hookLogName);//DEBUGNOW st vs mt
		log->set_pattern("|%H:%M:%S:%e|%l: %v");
		spdlog::set_default_logger(log);
#ifdef _DEBUG
		spdlog::set_level(spdlog::level::debug);
#else
		spdlog::set_level(spdlog::level::info);
#endif // _DEBUG
		spdlog::flush_on(spdlog::level::err);

		spdlog::info("IHHook r{}", IHHook::Version);

		std::time_t currentTime = time(0);
		std::tm now;
		localtime_s(&now, &currentTime);
		char datestr[100];
		std::strftime(datestr, sizeof(datestr), "Started: %Y/%m/%d %H:%M:%S", &now);
		spdlog::info(datestr);

		spdlog::debug(L"Original CurrentDir: {}", currentDir.c_str());

#ifdef _DEBUG
		std::vector<std::string> modFileNames = IHHook::GetFileNames("./mod");
		std::vector<std::string> folderNames = IHHook::GetFolderNames("./mod");
#endif // _DEBUG

		if (!IHHook::CheckVersion(IHHook::GameVersion)) {
			spdlog::error("IHHook version check mismatch");
		}
		else {
			MH_Initialize();
			size_t RealBaseAddr = (size_t)GetModuleHandle(NULL);
#ifdef ENABLE_CITYHOOK
			IHHook::CreateHooks_CityHash(RealBaseAddr);
#endif
			IHHook::CreateHooks_LuaIHH(RealBaseAddr);
		}

		IHHook::StartPipeServer();

		log->flush();
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		spdlog::debug("IHHook DLL_PROCESS_DETACH");

		spdlog::shutdown();
	}

	return TRUE;
}

