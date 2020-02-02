#include <ctime>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"
#include "MinHook/MinHook.h" // MH_Initialize
#include <signal.h>

namespace IHHook {
	//DEBUGNOW
	terminate_function terminate_Original;

	//DEBUGNOW
	void AbortHandler(int signal_number) {
		//MessageBoxA(
		//	NULL,
		//	"abort was called",
		//	"IHHook: unknown error",
		//	MB_ICONWARNING
		//);

		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("abort was called");
			log->flush();
		}
	}//AbortHandler

	//DEBUGNOW
	void Terminate_MsgBox() {
		//MessageBoxA(
		//	NULL,
		//	"terminate was called",
		//	"IHHook: unknown error",
		//	MB_ICONWARNING
		//);
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("terminate was called");
			log->flush();
		}
		//DEBUGNOW abort();
		terminate_Original();
	}//Terminate_MsgBox

	//DEBUGNOW
	bool g_showCrashDialog = true;
	LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* /*ExceptionInfo*/) {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("Unhandled exception");
			log->flush();
		}

		//std::cout << "Gotcha!" << std::endl;
		//MessageBoxA(
		//	NULL,
		//	"unhandled exception",
		//	"IHHook: unknown error",
		//	MB_ICONWARNING
		//);

		return g_showCrashDialog ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
	}

	LONG WINAPI UnhandledExceptionFilter_Hook(EXCEPTION_POINTERS* /*ExceptionInfo*/) {
		// When the CRT calls SetUnhandledExceptionFilter with NULL parameter
		// our handler will not get removed.
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("Unhandled exception H");
			log->flush();
		}

		return 0;
	}

	//
	typedef LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI* SetUnhandledExceptionFilter_Type)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
	SetUnhandledExceptionFilter_Type SetUnhandledExceptionFilter_Orig = NULL;


	DWORD Initialize(LPVOID lpParameter) {
		//DEBUGNOW
		//MessageBoxA(
		//	NULL,
		//	"Init",
		//	"IHH",
		//	0
		//);

		MH_Initialize();


		signal(SIGABRT, &AbortHandler);//tex signal handler for SIGABRT which is thrown by abort()
		terminate_Original = set_terminate(Terminate_MsgBox);
		_set_abort_behavior(1, _WRITE_ABORT_MSG);

		::SetUnhandledExceptionFilter(UnhandledExceptionHandler);
		//https://www.codeproject.com/Articles/154686/SetUnhandledExceptionFilter-and-the-C-C-Runtime-Li
		if (MH_CreateHook(&SetUnhandledExceptionFilter, &UnhandledExceptionFilter_Hook, reinterpret_cast<LPVOID*>(&SetUnhandledExceptionFilter_Orig)) != MH_OK) {
			//DEBUGNOW message error
			return 1;
		}
		MH_EnableHook(SetUnhandledExceptionFilter);


		//tex OFF //DEBUGNOW
		//AllocConsole();
		//SetConsoleTitle(L"IHHook");
		//freopen("CONOUT$", "w", stdout);
		//freopen("CONOUT$", "w", stderr);
		//freopen("CONIN$", "r", stdin);
		//printf("Console test\n");

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
		log->info("IHHook r{}", IHHook::Version);
		log->flush();

		spdlog::set_default_logger(log);
#ifdef _DEBUG
		spdlog::set_level(spdlog::level::debug);
#else
		spdlog::set_level(spdlog::level::info);
#endif // _DEBUG
		spdlog::flush_on(spdlog::level::err);

		std::time_t currentTime = time(0);
		std::tm now;
		localtime_s(&now, &currentTime);
		char datestr[100];
		std::strftime(datestr, sizeof(datestr), "Started: %Y/%m/%d %H:%M:%S", &now);
		spdlog::info(datestr);

		spdlog::debug("Note: ihhook_log is multithreaded to accept logging from multiple threads so order of entries may not be sequential.");

		spdlog::debug(L"Original CurrentDir: {}", currentDir.c_str());

#ifdef _DEBUG
		std::vector<std::string> modFileNames = IHHook::GetFileNames("./mod");
		std::vector<std::string> folderNames = IHHook::GetFolderNames("./mod");
#endif // _DEBUG

		if (!IHHook::CheckVersion(IHHook::GameVersion)) {
			spdlog::error("IHHook version check mismatch");
		}
		else {
			size_t RealBaseAddr = (size_t)GetModuleHandle(NULL);
#ifdef ENABLE_CITYHOOK
			IHHook::CreateHooks_CityHash(RealBaseAddr);
#endif
			IHHook::CreateHooks_LuaIHH(RealBaseAddr);
		}

		IHHook::StartPipeServer();

		spdlog::debug("Initialize complete");
		log->flush();

		return 0;
		}//Initialize

	void Shutdown() {
		spdlog::debug("IHHook DLL_PROCESS_DETACH");

		spdlog::shutdown();
	}//Shutdown
	}