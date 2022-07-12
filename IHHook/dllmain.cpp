//dllmain.cpp
//dll entry
//See IHHook.h for comments on rough layout of parts of the project

#include "windowsapi.h"
#include "IHHook.h"
#include <filesystem>

#include "Hooks_FOV.h"//DEBUGNOW

HMODULE g_thisModule;
extern HMODULE origDll;//dinputproxy

DWORD WINAPI InitThread(LPVOID lpParameter) {
	g_ihhook->Initialize();

	return 0;
}//InitThread

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);//tex stops DllMain being called by other created threads (which helps for some issues mentioned below) 

		g_thisModule = hModule;

		//tex bulk of IHHook initialization that can be done at this point of fox engine execution (when it loads this dinput8 proxy) 
		g_ihhook = std::make_unique<IHHook::IHH>();

		//tex generally CreateThread in DllMain is bad form, 
		//https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices
		//'Some reasons not to do anything scary in your DllMain': https://devblogs.microsoft.com/oldnewthing/20040127-00/?p=40873
		//and Initializing IHHook from the thread is kinda just shifting the goalposts in some respects as it spins up threads too (spdlog, pipeserver)
		//but it should shift execution till after DllMain is exited at least: https://devblogs.microsoft.com/oldnewthing/20070904-00/?p=25283

		//GOTCHA: KLUDGE: for setting up stuff after dinput8 dll has returned, 
		//but it's a fuzzy to what point of execution fox engine will be at the point any of this is run
		//so in theory if someone manages to delay the main fox engine thread, but this InitThread continues you'll have issues
		//DEBUGNOW actual solution is to hook fox engine functions at the relevant points of execution then run what you need inited
		HANDLE hInitThread = CreateThread(nullptr, 0, InitThread, hModule, 0, nullptr);
		if (hInitThread == NULL) {

		}
		else {
			CloseHandle(hInitThread);
		}
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		IHHook::Shutdown();
		//DInputProxy
		if (origDll) {
			FreeLibrary(origDll);
		}
	}

	return TRUE;
}//DllMain

