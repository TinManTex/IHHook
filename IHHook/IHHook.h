//IHHook: A Dll proxy to extend MGSV for modding
//See Developers.txt for more notes.
//tex: can run without Infinite Heaven, but IH will use it.

//Based on the bones of CityHook: https://github.com/emoose/MGSV-QAR-Dictionary-Project/tree/master/CityHook
//and RE2 Mod Framework: https://github.com/praydog/RE2-Mod-Framework

//Entry point in dllmain.cpp
//Hooking using MinHook: https://github.com/TsudaKageyu/minhook 
//Logging via spdlog: https://github.com/gabime/spdlog , header only implementation in IHHook\spdlog, but not included in the project/solution explorer just for clarity

//Trying to get coverage of whole LUALIB_API functions so that lua c modules can be compiled in
//The resulting method seems like a huge hack, and there's probably a smarter way to do it. But it works.
//Lua 5.1.5 implementation a mix of hooks and the normal definitions, entire distro files are in IHHook\lua, but as above only modified files included in project/solution explorer for clarity.

//Most mgsvtpp.exe function hooks via includes to Hooks_Lua > Hooks_*, function addresses and defs exported from ghidra via IHHook\ghidra\ExportHooksToHeader.py ghidra script.
//using hooking via addresses, which is fragile to new exe updates
//but also has support for sig scanning, but the performance with the denuvo bloat or whatever hulk that is the current mgsvtpp.exe makes it not viable for actual use.

//Encoding is a mess having pulled in so much code from other projects, and then, should probably try to standardise to utf8 at some point.

//Another GOTCHA might be if you ever export any functions not to break DinputProxy ordinals.

//Dear-imgui based menu for IH via IHMenu.*. Main issue with expanding use of imgui is performance of processing command que between whatever update thread and the d3d present.

//pipe server for commands via PipeServer.*

//RawInput interception/blocking via RawInput.*

//Config: load time options for ihhook (mostly for debug/logging stuff) are controlled by creating ihhook_config.lua in game root (alongside the ihhook dll)
//this is via a manually parsed/fragile system rather than an actual lua file loader.
//example config
/*
--ihhook_config.lua
local this = {
	debugMode = true,
	openConsole = false,
	enableCityHook = false,
	enableFnvHook = false,
	logFileLoad = false,
	forceUsePatterns = false,
}--this
return this
*/

#pragma once
#include <string>
#include <vector>
#include <atomic>
#include <mutex>
#include <spdlog/spdlog.h>
#include "D3D11Hook.hpp"
#include "WindowsMessageHook.hpp"

namespace IHHook {
	//tex SYNC: with ihhook_config-defaults.lua in makebite\GameDir
	struct Config {
		bool debugMode{ true };//TODO debug level instead, or split out logLevel?
		bool openConsole{ false };
		bool enableCityHook{ false }; //log cityhash calls, which underly strcode functions
		bool enableFnvHook{ false }; //log fnvhash
		bool logFileLoad{ false };
		bool enableCreateModuleHook{ false };
		bool forceUsePatterns{ false };
		bool logFoxStringCreateInPlace{ false }; //ZIP: Fox hooks
		bool logTime{ false };//prefix |time| before log (used to be default) time is good for figuring out how long between steps, but makes it harder to compare similar logs. TODO: might be better to have a SetPattern lua call for more control?
	};
	extern struct Config config;
	static const std::string hookConfigName = "ihhook_config.lua";

	static const int Version = 17; //SYNC: fileVersion
	extern int ihVersion;
	static const DWORD GameVersion[4] = { 1, 0, 15, 3 }; //tex: version checking game exe
	//static const std::wstring exeName = L"mgsvtpp.exe"; //tex use GetModuleFileName instead

	static const std::wstring hookLogName = L"ihhook_log.txt";
	static const std::wstring hookLogNamePrev = L"ihhook_log_prev.txt";

	static const std::wstring pipeInName = L"\\\\.\\pipe\\mgsv_in";
	static const std::wstring pipeOutName = L"\\\\.\\pipe\\mgsv_out";

	static const size_t BaseAddr = 0x140000000; // from ImageBase field in the EXE
	extern size_t RealBaseAddr; // Current base address of the EXE

	extern bool isTargetExe;//DEBUGNOW try direct addresses, or sig matching

	extern std::vector<std::string> errorMessages;

	extern std::atomic<bool> doShutDown;
	void Shutdown();

	bool HasFunctionAddress(char* functionName);

	class IHH {
	public:
		IHH();
		virtual ~IHH();

		void Initialize();

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
		void CreateD3DHook();
		
		void OnFrame();
		void OnReset();

		bool OnMessage(HWND wnd, UINT message, WPARAM w_param, LPARAM l_param);
	private:
		void SetupLog();
		std::string GetLangVersion();

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
		bool menuOpen = true;//tex start open, as it's used as a intro and error window during startup
		bool menuOpenPrev = true;

		// HWL ImGui should only be initialized once, even if the game sets up D3D11 twice
		bool ImGuiInitialized = false;

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

		void CreateAllHooks();
	};//IHH
}//namespace IHHook

extern std::unique_ptr<IHHook::IHH> g_ihhook;