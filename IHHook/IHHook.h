//IHHook: A Dll proxy to extend MGSV for modding
//tex: can run without Infinite Heaven, but IH will use it.

//Based on the bones of CityHook: https://github.com/emoose/MGSV-QAR-Dictionary-Project/tree/master/CityHook
//and RE2 Mod Framework: https://github.com/praydog/RE2-Mod-Framework

//Trying to get coverage of whole LUALIB_API functions so that lua c modules can be compiled in
//The resulting method seems like a huge hack, and there's probably a smarter way to do it. But it works.

//Entry point in dllmain.cpp
//Hooking using MinHook: https://github.com/TsudaKageyu/minhook 
//Logging via spdlog: https://github.com/gabime/spdlog , header only implementation in IHHook\spdlog, but not included in the project/solution explorer just for clarity

//Lua 5.1.5 implementation a mix of hooks and the normal definitions, entire distro files are in IHHook\lua, but as above only modified files included in project/solution explorer for clarity.
//using hooking via addresses, which is fragile to new exe updates
//but haven't got a sigscanning workflow yet to not kill myself with the large number functions I'm hooking

//Encoding is a mess having pulled in so much code from other projects, and then, should probably try to standardise to utf8 at some point.

//Another GOTCHA might be if you ever export any functions not to break DinputProxy ordinals.

#pragma once
#include <string>
#include <vector>
#include <mutex>
#include <spdlog/spdlog.h>
#include "D3D11Hook.hpp"
#include "WindowsMessageHook.hpp"

//#define MINIMAL_HOOK //

namespace IHHook {
	static const bool debugMode = true;//DEBUGNOW //DEBUG CONFIG //TODO debug level instead
	static const bool openConsole = false;//DEBUG CONFIG
	static const bool enableCityHook = false;//DEBUG CONFIG

	static const int Version = 7; //SYNC: fileVersion
	static const DWORD GameVersion[4] = { 1, 0, 15, 3 }; //tex: version checking game exe
	//static const std::wstring exeName = L"mgsvtpp.exe"; //tex use GetModuleFileName instead

	static const std::wstring hookLogName = L"ihhook_log.txt";
	static const std::wstring hookLogNamePrev = L"ihhook_log_prev.txt";

	static const std::wstring pipeInName = L"\\\\.\\pipe\\mgsv_in";
	static const std::wstring pipeOutName = L"\\\\.\\pipe\\mgsv_out";

	static const size_t BaseAddr = 0x140000000; // from ImageBase field in the EXE
	extern size_t RealBaseAddr; // Current base address of the EXE

	extern std::vector<std::string> errorMessages;

	void Shutdown();

	class IHH {
	public:
		IHH();
		void SetupLog();
		virtual ~IHH();

		HMODULE GetModule() {
			return thisModule;
		}//GetModule

		//tex using this as an indicator that ihhmenu is initialized
		bool IsFrameInitialized() {
			return frameInitialized;
		}//IsFrameInitialized

		//DEBUGNOW
		bool IsDrawUI() {
			return drawUI;
		}//IsDrawUI

		void SetDrawUI(bool set) {
			drawUI = set;
			menuOpen = set;//DEBUGNOW
		}//SetDrawUI

		void ToggleDrawUI() {
			SetDrawUI(!drawUI);
		}//ToggleDrawUI

		bool IsUnlockCursor() {
			return unlockCursor;
		}//IsCursorUnlocked

		void SetCursor(bool set) {
			unlockCursor = set;
		}//SetCursor

		void ToggleCursor() {
			unlockCursor = !unlockCursor;
		}//ToggleCursor

		void ToggleImguiDemo() {
			showImguiDemo = !showImguiDemo;
		}//ToggleImguiDemo

		void ToggleStyleEditor() {
			showStyleEditor = !showStyleEditor;
		}//ToggleStyleEditor

		//Dx11
		void OnFrame();
		void OnReset();

		bool OnMessage(HWND wnd, UINT message, WPARAM w_param, LPARAM l_param);
	private:
		bool FrameInitialize();
		void CreateRenderTarget();
		void CleanupRenderTarget();

		void DrawUI();
		void DrawAbout();

		//d3d11
		bool firstFrame = true;
		bool frameInitialized = false;
		bool d3dHooked = false;
		bool drawUI = true;
		bool unlockCursor = false;
		bool menuOpen = false;
		bool menuOpenPrev = true;

		bool showStyleEditor = false;
		bool showStyleEditorPrev = false;

		bool showImguiDemo = false;

		std::mutex inputMutex{};//DEBUGNOW

		HWND hwnd{ 0 };
		HMODULE thisModule{ 0 };

		std::unique_ptr<D3D11Hook> d3d11Hook{};
		std::unique_ptr<WindowsMessageHook> windowsMessageHook;
		std::shared_ptr<spdlog::logger> log;

		std::string errorString{ "" };

		ID3D11RenderTargetView* mainRenderTargetView{ nullptr };
	};
}//namespace IHHook

extern std::unique_ptr<IHHook::IHH> g_ihhook;