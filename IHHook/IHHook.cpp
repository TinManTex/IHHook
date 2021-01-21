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

#include "IHMenu.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//tex see note in imgui_impl_win32.h

std::unique_ptr<IHHook::IHH> g_ihhook{};

namespace IHHook {
	size_t RealBaseAddr;
	HMODULE thisModule;

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

	//DEBUGNOW
	typedef BOOL(WINAPI* SetCursorPosFunc)(int, int);
	SetCursorPosFunc SetCursorPos_Orig = NULL;

	BOOL WINAPI SetCursorPos_Hook(int X, int Y) {
		if (g_ihhook->IsDrawUI())
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

	IHH::IHH()
		: thisModule{ GetModuleHandle(0) } 
	{
		RealBaseAddr = (size_t)GetModuleHandle(NULL);

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

		spdlog::debug(L"Original CurrentDir: {}", currentDir.c_str());

#ifdef _DEBUG
		std::vector<std::string> modFileNames = OS::GetFileNames("./mod");
		std::vector<std::string> folderNames = OS::GetFolderNames("./mod");
#endif // _DEBUG

		RealBaseAddr = (size_t)GetModuleHandle(NULL);

		if (!OS::CheckVersion(IHHook::GameVersion)) {
			spdlog::error("IHHook version check mismatch");
		}
		else {
			MH_Initialize();
			Hooks_CityHash::CreateHooks(RealBaseAddr);
			Hooks_Lua::CreateHooks(RealBaseAddr);
			Hooks_TPP::CreateHooks(RealBaseAddr);
		}// ChecKVersion

		PipeServer::StartPipeServer();

		d3d11Hook = std::make_unique<D3D11Hook>();
		d3d11Hook->on_present([this](D3D11Hook& hook) { OnFrame(); });
		d3d11Hook->on_resize_buffers([this](D3D11Hook& hook) { OnReset(); });

		d3dHooked = d3d11Hook->hook();
		if (d3dHooked) {
			spdlog::info("Hooked D3D11");
		}
		//DEBUGNOW TODO: push d3dHooked to lua globals so lua can check if IMGUI available (see "_IHHook" for example)

		spdlog::debug("IHH ctor complete");
		log->flush();
	}//IHH

	IHH::~IHH() {

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
		}
		else {
			spdlog::set_level(spdlog::level::info);
		}
		spdlog::flush_on(spdlog::level::err);

		std::time_t currentTime = time(0);
		std::tm now;
		localtime_s(&now, &currentTime);
		char datestr[100];
		std::strftime(datestr, sizeof(datestr), "Started: %Y/%m/%d %H:%M:%S", &now);
		spdlog::info(datestr);

		spdlog::debug("Note: ihhook_log is multithreaded to accept logging from multiple threads so order of entries may not be sequential.");
	}//SetupLog

	//D3D11Hook
	void IHH::OnFrame() {
		spdlog::debug("OnFrame");

		if (!frameInitialized) {
			if (!FrameInitialize()) {
				spdlog::error("Failed to frame initialize IHHook");
				return;
			}

			spdlog::info("IHHook frame initialized");
			frameInitialized = true;
			return;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//if (m_error.empty() && m_game_data_initialized) {
		//	m_mods->on_frame();
		//}

		DrawUI();

		ImGui::EndFrame();
		ImGui::Render();

		ID3D11DeviceContext* context = nullptr;
		d3d11Hook->get_device()->GetImmediateContext(&context);

		context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}//OnFrame

	//D3D11Hook
	void IHH::OnReset() {
		spdlog::info("OnReset");

		// RE2FW: Crashes if we don't release it at this point.
		CleanupRenderTarget();
		frameInitialized = false;
	}//OnReset

	//WindowsMessageHook
	bool IHH::OnMessage(HWND wnd, UINT message, WPARAM w_param, LPARAM l_param) {
		//spdlog::trace("OnMessage");//DEBUGNOW

		if (!frameInitialized) {
			return true;
		}
		
		bool ret = RawInput::OnMessage(wnd, message, w_param, l_param);//DEBUGNOW
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

	//RE2FW: this is unfortunate. //DEBUGNOW CULL
	void IHH::OnDirectInputKeys(const std::array<uint8_t, 256>& keys) {
		spdlog::trace("OnDirectInputKeys");
		//if (keys[menuKey] && lastKeys[menuKey] == 0) {
		//	std::lock_guard _{ inputMutex };
		//	drawUI = !drawUI;

		//	// Save the config if we close the UI
		//	//DEBUGNOW if (!m_draw_ui && m_game_data_initialized) {
		//	//	save_config();
		//	//}
		//}

		//lastKeys = keys;
	}//OnDirectInputKeys

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
		//DEBUGNOW io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//DEBUGNOW io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//DEBUGNOW io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;//DEBUGNOW

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

		IHMenu::AddMenuCommands();//DEBUGNOW

		if (firstFrame) {
			firstFrame = false;

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
		}

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
		if (mainRenderTargetView != nullptr) {
			mainRenderTargetView->Release();
			mainRenderTargetView = nullptr;
		}
	}//CleanupRenderTarget

	void IHH::DrawUI() {
		std::lock_guard _{ inputMutex };//DEBUGNOW

		auto& io = ImGui::GetIO();
		if (!drawUI) {
			//RawInput::UnBlockAll();//DEBUGNOW
			unlockCursor = false; //DEBUGNOW
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
			//DEBUGNOW RawInput::BlockKeyboard();
		}
		else {
			//DEBUGNOW RawInput::UnBlockKeyboard();
		}

		io.MouseDrawCursor = unlockCursor;
		
		IHMenu::DrawMenu();

		//DEBUGNOW
		//ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_::ImGuiCond_Once);
		//ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_::ImGuiCond_Once);

		//ImGui::Begin("Infinite Heaven", &drawUI);
		//ImGui::Text("Menu Key: Insert");

		//DrawAbout();

		/*if (errorString.empty() && m_game_data_initialized) {
			m_mods->on_draw_ui();
		}
		else if (!m_game_data_initialized) {
			ImGui::TextWrapped("IHHook is currently initializing...");
		}
		else if*/
		//DEBUGNOW
		//if (!errorString.empty()) {
		//	ImGui::TextWrapped("IHHook error: %s", errorString.c_str());
		//}

		//ImGui::End();
	}//DrawUI


	//DEBUGNOW
	void IHH::DrawAbout() {
		if (!ImGui::CollapsingHeader("About")) {
			return;
		}

		ImGui::TreePush("About");

		ImGui::Text("Inspired by (and parts adapted from) various game extension projects.");
		ImGui::Text("https://github.com/TinManTex/IHHook");

		//DEBUGNOW
		if (ImGui::CollapsingHeader("Licenses")) {
			ImGui::TreePush("Licenses");

			if (ImGui::CollapsingHeader("glm")) {
				ImGui::TextWrapped("glmblurg");
			}

			if (ImGui::CollapsingHeader("imgui")) {
				ImGui::TextWrapped("imguifdjhfkjdh");
			}

			if (ImGui::CollapsingHeader("minhook")) {
				ImGui::TextWrapped("minhookmnnjh");
			}

			if (ImGui::CollapsingHeader("spdlog")) {
				ImGui::TextWrapped("spdlogkjkj");
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}//DrawAbout

}//namespace IHHook