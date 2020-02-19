//dllmain.cpp
//dll entry

#include "windowsapi.h"
#include "IHHook.h"

HMODULE thisModule;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);//tex stops DllMain being called by other created threads (which helps for some issues mentioned below) 

		thisModule = hModule;

		//tex generally CreateThread in DllMain is bad form, 
		//https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices
		//'Some reasons not to do anything scary in your DllMain': https://devblogs.microsoft.com/oldnewthing/20040127-00/?p=40873
		//and Initializing IHHook from the thread is kinda just shifting the goalposts in some respects as it spins up threads too (spdlog, pipeserver)
		//but it should shift execution till after DllMain is exited at least: https://devblogs.microsoft.com/oldnewthing/20070904-00/?p=25283
		//Ideally I should be just initializing hooks in dll main, 
		//and hooking some good spot in mgsvs execution then doing the rest of initialization there.
		HANDLE hInitThread = CreateThread(nullptr, 0, IHHook::Initialize, hModule, 0, nullptr);
		if (hInitThread == NULL) {

		}
		else {
			CloseHandle(hInitThread);
		}
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		IHHook::Shutdown();
	}

	return TRUE;
}

