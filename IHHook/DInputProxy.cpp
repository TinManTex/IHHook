//DInputProxy.cpp - from CityHook
//Proxy dinput8.dll
#include "windowsapi.h"
#include <stdlib.h>
#include <stdio.h>

#include "spdlog/spdlog.h"

//DEBUGNOW put this into a header or a DEF
#pragma comment(linker, "/export:DirectInput8Create=DirectInput8Create")
#pragma comment(linker, "/export:DllCanUnloadNow=DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject=DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer=DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer=DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/export:GetdfDIJoystick=GetdfDIJoystick")
//DEBUGNOW not sure if these are correct mangled names. extern C exports unmangled anyway
//#pragma comment(linker,"/EXPORT:DllCanUnloadNow=DllCanUnloadNow@0,PRIVATE")
//#pragma comment(linker, "/EXPORT:DllGetClassObject=DllGetClassObject@12,PRIVATE")
//#pragma comment(linker, "/EXPORT:DllRegisterServer=DllRegisterServer@0,PRIVATE")
//#pragma comment(linker, "/EXPORT:DllUnregisterServer=DllUnregisterServer@0,PRIVATE")

typedef HRESULT(WINAPI*DirectInput8Create_ptr)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, void* punkOuter);
//typedef HRESULT(WINAPI* DirectInput8Create_ptr)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);//DEBUGNOW CULL
//typedef HRESULT(WINAPI* CreateDevice_ptr)(IDirectInput8*, REFGUID, LPDIRECTINPUTDEVICE, LPUNKNOWN);//DEBUGNOW CULL
//typedef HRESULT(WINAPI* GetClassObject_ptr)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);

DirectInput8Create_ptr DirectInput8Create_Orig = NULL;
FARPROC DllCanUnloadNow_Orig;
FARPROC DllGetClassObject_Orig;
FARPROC DllRegisterServer_Orig;
FARPROC DllUnregisterServer_Orig;
FARPROC GetdfDIJoystick_Orig;



extern HMODULE g_thisModule;
bool origLoaded = false;
HMODULE origDll = NULL;

bool LoadProxiedDll()
{
	if (origLoaded)
		return true;

	// get the filename of our DLL and try loading the DLL with the same name from system32
	WCHAR modulePath[MAX_PATH] = { 0 };
	if (!GetSystemDirectoryW(modulePath, _countof(modulePath))) {
		spdlog::error("GetSystemDirectoryW fail");
		return false;
	}

	// get filename of this DLL, which should be the original DLLs filename too
	WCHAR ourModulePath[MAX_PATH] = { 0 };
	GetModuleFileNameW(g_thisModule, ourModulePath, _countof(ourModulePath));

	WCHAR exeName[MAX_PATH] = { 0 };
	WCHAR extName[MAX_PATH] = { 0 };
	_wsplitpath_s(ourModulePath, NULL, NULL, NULL, NULL, exeName, MAX_PATH, extName, MAX_PATH);

	swprintf_s(modulePath, MAX_PATH, L"%ws\\%ws%ws", modulePath, exeName, extName);

	spdlog::debug("modulePath:");
	spdlog::debug(modulePath);
	origDll = LoadLibraryW(modulePath);
	if (!origDll) {
		spdlog::error("Could not load original module");
		return false;
	}

	DirectInput8Create_Orig = (DirectInput8Create_ptr)GetProcAddress(origDll, "DirectInput8Create");
	DllCanUnloadNow_Orig = GetProcAddress(origDll, "DllCanUnloadNow");
	DllGetClassObject_Orig = GetProcAddress(origDll, "DllGetClassObject");
	DllRegisterServer_Orig = GetProcAddress(origDll, "DllRegisterServer");
	DllUnregisterServer_Orig = GetProcAddress(origDll, "DllUnregisterServer");

	origLoaded = true;
	return true;
}

extern "C" __declspec(dllexport) HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, void* punkOuter)
{
	spdlog::debug("IHHook: DirectInput8Create");

	if (!DirectInput8Create_Orig)
		LoadProxiedDll();

	return DirectInput8Create_Orig(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

extern "C" __declspec(dllexport) void __stdcall DllCanUnloadNow() { DllCanUnloadNow_Orig(); }
extern "C" __declspec(dllexport) void __stdcall DllGetClassObject() { DllGetClassObject_Orig(); }
extern "C" __declspec(dllexport) void __stdcall DllRegisterServer() { DllRegisterServer_Orig(); }
extern "C" __declspec(dllexport) void __stdcall DllUnregisterServer() { DllUnregisterServer_Orig(); }
extern "C" __declspec(dllexport) void __stdcall GetdfDIJoystick() { GetdfDIJoystick_Orig(); }
