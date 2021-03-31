#include <ctime>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"
#include "OS.h"
#include "PipeServer.h"
#include "MinHook/MinHook.h" // MH_Initialize
#include <signal.h>

#include "Hooks_CityHash.h"
#include "Hooks_Lua.h"
#include "Hooks_TPP.h"

#include "RawInput.h"

#include <imgui/imgui.h>
#include "imguiimpl/imgui_impl_win32.h"
#include "imguiimpl/imgui_impl_dx11.h"

#include <string>
#include <filesystem>
// version_info parse
#include <fstream>
#include <sstream>


#include "IHMenu.h"
#include "StyleEditor.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//tex see note in imgui_impl_win32.h

std::unique_ptr<IHHook::IHH> g_ihhook{};

namespace IHHook {
	std::vector<std::string> errorMessages{};

	size_t RealBaseAddr;

	terminate_function terminate_Original;

	void AbortHandler(int signal_number) {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("abort was called");
			log->flush();
		}
	}//AbortHandler

	void TerminateHandler() {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("terminate was called");
			log->flush();
		}
		terminate_Original();
	}//TerminateHandler

	bool g_showCrashDialog = true;
	LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* /*ExceptionInfo*/) {
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("Unhandled exception");
			log->flush();
		}

		return g_showCrashDialog ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
	}//UnhandledExceptionHandler

	LONG WINAPI UnhandledExceptionFilter_Hook(EXCEPTION_POINTERS* /*ExceptionInfo*/) {
		// When the CRT calls SetUnhandledExceptionFilter with NULL parameter
		// our handler will not get removed.
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->error("Unhandled exception H");
			log->flush();
		}

		return 0;
	}//UnhandledExceptionFilter_Hook

	typedef LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI* SetUnhandledExceptionFilter_Type)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
	SetUnhandledExceptionFilter_Type SetUnhandledExceptionFilter_Orig = NULL;

	typedef BOOL(WINAPI* SetCursorPosFunc)(int, int);
	SetCursorPosFunc SetCursorPos_Orig = NULL;

	BOOL WINAPI SetCursorPos_Hook(int X, int Y) {
		if (g_ihhook->IsUnlockCursor())
			return FALSE;

		return SetCursorPos_Orig(X, Y);
	}//SetCursorPos_Hook

	void InitCursorHook() {
		auto log = spdlog::get("ihhook");
		if (MH_CreateHook(&SetCursorPos, &SetCursorPos_Hook, reinterpret_cast<LPVOID*>(&SetCursorPos_Orig)) != MH_OK) {
			log->info("Couldn't create hook for SetCursorPos.");
			return;
		}

		if (MH_EnableHook(&SetCursorPos) != MH_OK) {
			log->info("Couldn't enable SetCursorPos hook.");
		}
	}//InitCursorHook

	void Shutdown() {
		spdlog::debug("IHHook DLL_PROCESS_DETACH");

		spdlog::shutdown();
	}//Shutdown

	//TODO move to utils or something
	//IN/SIDE: BaseAddr, RealBaseAddr
	void* RebasePointer(size_t address) {
		return (void*)((address - BaseAddr) + RealBaseAddr);
	}//RebasePointer
	extern void TestSigScan();//DEBUGNOW
	IHH::IHH()
		: thisModule{ GetModuleHandle(0) } {
		RealBaseAddr = (size_t)GetModuleHandle(NULL);

		//TestSigScan();//DEBUGNOW

		signal(SIGABRT, &AbortHandler);//tex signal handler for SIGABRT which is thrown by abort()
		terminate_Original = set_terminate(TerminateHandler);
		_set_abort_behavior(1, _WRITE_ABORT_MSG);

		SetUnhandledExceptionFilter(UnhandledExceptionHandler);

		//https://www.codeproject.com/Articles/154686/SetUnhandledExceptionFilter-and-the-C-C-Runtime-Li
		//if (MH_CreateHook(&SetUnhandledExceptionFilter, &UnhandledExceptionFilter_Hook, reinterpret_cast<LPVOID*>(&SetUnhandledExceptionFilter_Orig)) != MH_OK) {
		//	//DEBUGNOW message error
		//	return 1;
		//}
		//MH_EnableHook(SetUnhandledExceptionFilter);


		if (openConsole) {
			AllocConsole();
			SetConsoleTitle(L"IHHook");
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
			freopen("CONIN$", "r", stdin);
			printf("Console test\n");
		}

		//tex DEBUG, logged below 
		TCHAR Buffer[MAX_PATH];
		DWORD dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
		std::wstring currentDir(Buffer);

		std::wstring gameDir = OS::GetGameDir();
		SetCurrentDirectory(gameDir.c_str());//tex so this dll and lua can use reletive paths

		SetupLog();

		//tex DEBUGNOW mgo is a seperate exe in the same dir, so bail out on exe name
		HMODULE hExe = GetModuleHandle(NULL);
		WCHAR fullPath[MAX_PATH]{ 0 };
		GetModuleFileNameW(hExe, fullPath, MAX_PATH);
		std::filesystem::path path(fullPath);
		std::wstring exeName = path.filename().c_str();
		if (exeName.find(L"mgo")!= std::wstring::npos) {
			spdlog::warn("IHHook is not for mgo");
			return;
		}
		//

		spdlog::debug(L"Original CurrentDir: {}", currentDir.c_str());
		spdlog::debug(L"gameDir: {}", gameDir);

#ifdef _DEBUG
		std::vector<std::string> modFileNames = OS::GetFileNames("./mod");
		std::vector<std::string> folderNames = OS::GetFolderNames("./mod");
#endif // _DEBUG

		if (!std::filesystem::exists("./mod/modules")) {//tex GOTCHA: since this continues ih_log will be created thus ./mod will actually exist. so check modules instead
			errorMessages.push_back("ERROR: IH mod folder not found.");

			for each (std::string message in errorMessages) {
				spdlog::error(message);
			}
		}

		RealBaseAddr = (size_t)GetModuleHandle(NULL);



		//tex Much of IHHooks hooks are based on direct addresses, so if the exe is different the user needs to know
		//can just hope that konami actually keeps updating the exe version properly and not release multiple updates with no exe version change like they have in the past
		//but version_info.txt should help there

		//DEBUGNOW So jp voice version is actually different exe, so cant just rely on exe version info.
		std::string versionInfoFileName = "version_info.txt";
		std::ifstream infile(versionInfoFileName);
		if (infile.fail()) {//tex likely pirated game, or user has some wierd setup, cant know actual version
			spdlog::warn("Could not load ", versionInfoFileName);
			spdlog::warn("Cannot differentiate what language version the exe is, so game may crash when hooking if exe version matches but using different ");
			//any point using errormessages since if this is an actual lang exe mismatch its going to crash before it gets to the ui
			//DEBUGNOW think what to do.
		}

		//REF
		//Tpp_steam_mst_en_day1820Mgo_patch_0212_1307
		//Tpp_steam_mst_jp_day1820Mgo_patch_0212_1307
		std::string line;
		std::string lang = "";
		while (std::getline(infile, line)) {
			std::istringstream iss(line);

			if (line.length() < std::string("Tpp_steam_mst_en").length()) {
				spdlog::warn("Unexpected version string, string shorter than expected");
				break;
			}
			
			std::string prefix = "Tpp_steam_mst_";
			std::size_t found = line.find(prefix);
			if (found == std::string::npos) {
				spdlog::warn("Unexpected version string, could not find {}", prefix);
				break;
			}

			lang = line.substr(prefix.length(),2);//en,jp etc
			spdlog::debug("Found lang: {}", lang);
	
			if (lang != "en" || lang != "jp") {
				spdlog::warn("Unexpected lang version");
			}
		}//while infile



		std::string exeVersionStr = "";
		int versionDelta = OS::CheckVersionDelta(IHHook::GameVersion, exeVersionStr);
		if (versionDelta != 0) {
			errorMessages.push_back("ERROR: IHHook->exe version mismatch");
			errorMessages.push_back("Infinite Heaven will continue to load");
			errorMessages.push_back("with some limitations.");
			errorMessages.push_back("Including this menu not working in-game.");
			if (versionDelta > 0) {
				errorMessages.push_back("Please update MGSV.");
			}
			else if (versionDelta < 0) {
				errorMessages.push_back("Please update Infinte Heaven.");
			}
			errorMessages.push_back("Click on the x to close this window.");

			for each (std::string message in errorMessages) {
				spdlog::error(message);
			}
			SetCursor(true);//tex DEBUGNOW currently wont auto dismiss, so give user cursor
		} 
		else {
			if (lang != "en") {//DEBUGNOW
				errorMessages.push_back("WARNING: IHHook currently ");
				errorMessages.push_back("only supports the eng version");
				errorMessages.push_back("Infinite Heaven will continue to load");
				errorMessages.push_back("with some limitations.");
				errorMessages.push_back("Including this menu not working in-game.");
				errorMessages.push_back("Click on the x to close this window.");

				for each (std::string message in errorMessages) {
					spdlog::error(message);
				}
				SetCursor(true);//tex DEBUGNOW currently wont auto dismiss, so give user cursor
			}
			else {
				MH_Initialize();
#ifndef MINIMAL_HOOK
			Hooks_CityHash::CreateHooks(RealBaseAddr);
#endif // !MINIMAL_HOOK
			Hooks_Lua::CreateHooks(RealBaseAddr);
			Hooks_TPP::CreateHooks(RealBaseAddr);//DEBUGNOW 
			}
		}// ChecKVersion

		PipeServer::StartPipeServer();

		d3d11Hook = std::make_unique<D3D11Hook>();
		d3d11Hook->on_present([this](D3D11Hook& hook) { OnFrame(); });
		d3d11Hook->on_resize_buffers([this](D3D11Hook& hook) { OnReset(); });

		d3dHooked = d3d11Hook->hook();
		if (d3dHooked) {
			spdlog::info("Hooked D3D11");
		}
		else {
			MessageBox(NULL, L"Could not hook D3D11\n", L"Infinite Heaven IHHook", NULL);
		}

		spdlog::debug("IHH ctor complete");
		log->flush();
	}//IHH

	IHH::~IHH() {
		MH_Uninitialize();
	}//~IHH

	//OUT/SIDE: log file, log file prev
	//OUT/SIDE: log
	void IHH::SetupLog() {
		DeleteFile(IHHook::hookLogNamePrev.c_str());
		CopyFile(IHHook::hookLogName.c_str(), IHHook::hookLogNamePrev.c_str(), false);
		DeleteFile(IHHook::hookLogName.c_str());

		log = spdlog::basic_logger_mt("ihhook", IHHook::hookLogName);//DEBUGNOW st vs mt

		log->set_pattern("|%H:%M:%S:%e|%l: %v");
		log->info("IHHook r{}", IHHook::Version);
		log->flush();

		spdlog::set_default_logger(log);
		if (debugMode) {
			spdlog::set_level(spdlog::level::trace);
			spdlog::flush_on(spdlog::level::trace);
		}
		else {
			spdlog::set_level(spdlog::level::info);		
			spdlog::flush_on(spdlog::level::err);
		}

		std::time_t currentTime = time(0);
		std::tm now;
		localtime_s(&now, &currentTime);
		char datestr[100];
		std::strftime(datestr, sizeof(datestr), "Started: %Y/%m/%d %H:%M:%S", &now);
		spdlog::info(datestr);
		log->flush();
		spdlog::debug("Note: ihhook_log is multithreaded to accept logging from multiple threads so order of entries may not be sequential.");
	}//SetupLog

	//D3D11Hook->present
	//GOTCHA: this is blocking to actual d3d Present, so keep performance in mind
	void IHH::OnFrame() {
		//spdlog::trace("OnFrame");
		auto frameTimeStart = std::chrono::high_resolution_clock::now();

		if (!frameInitialized) {
			if (!FrameInitialize()) {
				spdlog::error("Failed to frame initialize IHHook");
				return;
			}

			//tex IHMenu initial text DEBUGNOW
			IHMenu::SetInitialText();

			spdlog::info("IHHook frame initialized");
			frameInitialized = true;
			return;//tex give it an extra frame to settle I guess?
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//DEBUGNOW
		//if (m_error.empty() && m_game_data_initialized) {
		//	m_mods->on_frame();
		//}


		//DEBUGNOW test frame impact
		//bool boop = false;
		//for (int i = 0; i < 10000000; i++) {
		//	boop = !boop;
		//}


		DrawUI();

		ImGui::EndFrame();
		ImGui::Render();

		ID3D11DeviceContext* context = nullptr;
		d3d11Hook->get_device()->GetImmediateContext(&context);

		context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		auto frameTimeEnd = std::chrono::high_resolution_clock::now();
		auto frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameTimeEnd - frameTimeStart).count();
		//spdlog::trace("frame time microseconds: {}", frameDuration);//DEBUGNOW
	}//OnFrame

	//D3D11Hook
	void IHH::OnReset() {
		spdlog::info("OnReset");
		//DEBUGNOW
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->flush();
		}

		// RE2FW: Crashes if we don't release it at this point.
		CleanupRenderTarget();
		frameInitialized = false;

		//DEBUGNOW
		spdlog::info("OnReset done");
		if (log != NULL) {
			log->flush();
		}

	}//OnReset

	//WindowsMessageHook
	bool IHH::OnMessage(HWND wnd, UINT message, WPARAM w_param, LPARAM l_param) {
		//spdlog::trace("OnMessage");

		if (!frameInitialized) {
			return true;
		}

		bool ret = RawInput::OnMessage(wnd, message, w_param, l_param);
		if (!ret) {
			return false;
		}

		if (drawUI && ImGui_ImplWin32_WndProcHandler(wnd, message, w_param, l_param) != 0) {
			//RE2FW: If the user is interacting with the UI we block the message from going to the game.
			auto& io = ImGui::GetIO();

			if (io.WantCaptureMouse || io.WantCaptureKeyboard || io.WantTextInput) {
				return false;
			}
		}

		return true;
	}//OnMessage

	//tex called on initialize and on device reset
	bool IHH::FrameInitialize() {
		if (frameInitialized) {
			return true;
		}

		spdlog::info("Attempting to frame initialize");

		auto device = d3d11Hook->get_device();
		auto swapChain = d3d11Hook->get_swap_chain();

		// Wait.
		if (device == nullptr || swapChain == nullptr) {
			spdlog::info("Device or SwapChain null. DirectX 12 may be in use. A crash may occur.");
			return false;
		}

		ID3D11DeviceContext* context = nullptr;
		device->GetImmediateContext(&context);

		DXGI_SWAP_CHAIN_DESC swapDesc{};
		swapChain->GetDesc(&swapDesc);

		hwnd = swapDesc.OutputWindow;

		//RE2FW: Explicitly call destructor first
		windowsMessageHook.reset();
		windowsMessageHook = std::make_unique<WindowsMessageHook>(hwnd);
		windowsMessageHook->on_message = [this](auto wnd, auto msg, auto wParam, auto lParam) {
			return OnMessage(wnd, msg, wParam, lParam);
		};

		spdlog::info("Creating render target");

		CreateRenderTarget();

		spdlog::info("Window Handle: {0:x}", (uintptr_t)hwnd);
		spdlog::info("Initializing ImGui");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		spdlog::info("Initializing ImGui Win32");

		if (!ImGui_ImplWin32_Init(hwnd)) {
			spdlog::error("Failed to initialize ImGui.");
			return false;
		}

		spdlog::info("Initializing ImGui D3D11");

		if (!ImGui_ImplDX11_Init(device, context)) {
			spdlog::error("Failed to initialize ImGui.");
			return false;
		}

		ImGui::StyleColorsDark();
		
		//SaveGuiStyle("styledefaultdump.lua");//DEBUGNOW

		if (firstFrame) {
			firstFrame = false;

			RawInput::InitializeInput();

			//HWND hWnd = OS::GetMainWindow();
			//DEBUGNOW RawInput::HookWndProc(hWnd);

			IHMenu::AddMenuCommands();

			InitCursorHook();

			//spdlog::info("Starting game data initialization thread");

			//// Game specific initialization stuff
			//std::thread init_thread([this]() {
			//	m_types = std::make_unique<RETypes>();
			//	m_globals = std::make_unique<REGlobals>();
			//	m_mods = std::make_unique<Mods>();

			//	auto e = m_mods->on_initialize();

			//	if (e) {
			//		if (e->empty()) {
			//			m_error = "An unknown error has occurred.";
			//		}
			//		else {
			//			m_error = *e;
			//		}
			//	}

			//	m_game_data_initialized = true;
			//});

			//init_thread.detach();

			LoadSelectedInitial(NULL);//StyleEditor
		}

		spdlog::info("frame initialized");
		return true;
	}//FrameInitialize

	void IHH::CreateRenderTarget() {
		CleanupRenderTarget();

		ID3D11Texture2D* backBuffer{ nullptr };
		if (d3d11Hook->get_swap_chain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer) == S_OK) {
			d3d11Hook->get_device()->CreateRenderTargetView(backBuffer, NULL, &mainRenderTargetView);
			backBuffer->Release();
		}
	}//CreateRenderTarget

	void IHH::CleanupRenderTarget() {
		spdlog::trace("CleanupRenderTarget");
		//DEBUGNOW
		auto log = spdlog::get("ihhook");
		if (log != NULL) {
			log->flush();
		}

		if (mainRenderTargetView != nullptr) {
			mainRenderTargetView->Release();
			mainRenderTargetView = nullptr;
		}
	}//CleanupRenderTarget

	void IHH::DrawUI() {
		//std::lock_guard _{ inputMutex };//DEBUGNOW

		IHMenu::ProcessMessages();

		auto& io = ImGui::GetIO();
		if (!drawUI) {
			RawInput::UnBlockMouseClick();
			RawInput::UnBlockKeyboard();
			unlockCursor = false;
			io.MouseDrawCursor = false;
			return;
		}

		if (io.WantCaptureMouse) {
			RawInput::BlockMouseClick();
		}
		else {
			RawInput::UnBlockMouseClick();
		}


		if (io.WantCaptureKeyboard) {
			RawInput::BlockKeyboard();
		}
		else {
			RawInput::UnBlockKeyboard();
		}

		io.MouseDrawCursor = unlockCursor;

		if (showStyleEditor) {
			ShowStyleEditor(&showStyleEditor, showStyleEditorPrev, NULL);
			showStyleEditorPrev = showStyleEditor;
		}

		if (showImguiDemo) {
			ImGui::ShowDemoWindow(&showImguiDemo);
		}

		IHMenu::DrawMenu(&menuOpen, menuOpenPrev);
		if (!menuOpen && menuOpenPrev) {
			IHMenu::QueueMessageIn("menuoff");
		}
		menuOpenPrev = menuOpen;

		//ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_::ImGuiCond_Once);
		//ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_::ImGuiCond_Once);

		//ImGui::Begin("Infinite Heaven", &drawUI);
		//ImGui::Text("Menu Key: Insert");

		//DrawAbout();
		//DEBUGNOW
		/*if (errorString.empty() && m_game_data_initialized) {
			m_mods->on_draw_ui();
		}
		else if (!m_game_data_initialized) {
			ImGui::TextWrapped("IHHook is currently initializing...");
		}
		else if*/
		//if (!errorString.empty()) {
		//	ImGui::TextWrapped("IHHook error: %s", errorString.c_str());
		//}

		//ImGui::End();
	}//DrawUI


}//namespace IHHook