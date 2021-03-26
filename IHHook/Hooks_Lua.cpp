/*
	tex: msgvtpp has lua 5.1.5 statically linked
	IHHook hooks lua by function addresses (defined in lua/*_Addresses.h), using (macros wrapping) MH_Hook initialised in CreateHooks() below
	it also replaces the lua function declarations in the lua distro (using the HOOKFUNC macros) so other code can build against it.
	In some cases uses actual lua lib implementation.
	See comments on CREATEHOOK entries in *_Creathooks.cpp.

	function signatures/patterns would be more robust to game updates / different game versions than straight addresses, but take a long time to search
	since IHHook is started on it's own thread game initialisation will continue, and IHHook wont be ready in time to start up IH properly.
	an alternative would be to do a hook to an early execution point of the game and init  ihhook there,
	but given the low rate of updates of the game it's better to stick with direct addresses, but have signatures documented as a backup
*/

#include "Hooks_Lua.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//Version,BaseAddr, g_ihhook
#include "LuaIHH.h"
#include "OS.h"
#include "RawInput.h"
#include "MinHook/MinHook.h"

#include "lua/lua_AddressesGEN.h"

#include <string>
#include <Psapi.h>// ModuleInfo, DEBUGNOW

extern void LoadImguiBindings(lua_State* lState);

namespace IHHook {
	extern void CreateHooks_Lua(size_t BaseAddr, size_t RealBaseAddr);
	extern void CreateHooks_Lauxlib(size_t BaseAddr, size_t RealBaseAddr);
	extern void CreateHooks_Lualib(size_t BaseAddr, size_t RealBaseAddr);
	//Hooks_Lua_Test
	extern void TestHooks_Lua(lua_State* L);
	extern void TestHooks_Lua_PostLibs(lua_State* L);

	//tex lua C module (well C++ because I converted so it would play nice with my mixed hooks and definitions version of the lua api)
	//extern int luaopen_winapi(lua_State* L);


	std::shared_ptr<spdlog::logger> luaLog;

	//TEST DEBUGNOW todo shift into another module
	//Get all module related info, this will include the base DLL and the size of the module
	MODULEINFO GetModuleInfo(LPCWSTR szModule) {
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandle(szModule);
		if (hModule == 0)
			return modinfo;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		return modinfo;
	}

	//Pattern Scan https://guidedhacking.com/threads/c-signature-scan-pattern-scanning-tutorial-difficulty-3-10.3981
	uintptr_t FindPattern(LPCWSTR module, char* pattern, char* mask) {
		spdlog::trace("FindPattern:");//DEBUGNOW
		spdlog::trace("Sig:{}", pattern);//DEBUGNOW
		spdlog::trace("Msk:{}", mask);//DEBUGNOW

		//Get all module related information
		MODULEINFO mInfo = GetModuleInfo(module);

		//Assign our base and module size
		uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;

		uintptr_t size = (uintptr_t)mInfo.SizeOfImage;

		//Get length for our mask, this will allow us to loop through our array
		DWORD patternLength = (DWORD)strlen(mask);

		for (DWORD i = 0; i < size - patternLength; i++) {
			bool found = true;
			for (DWORD j = 0; j < patternLength; j++) {
				//if we have a ? in our mask then we have true by default,
				//or if the bytes match then we keep searching until finding it or not
				found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
			}

			//found = true, our entire pattern was found
			if (found) {
				spdlog::trace("Pattern found : {x}", (base + i));
				return base + i;
			}
		}
		spdlog::trace("Pattern not found");
		return NULL;
	}

	int CompareByteArray(PBYTE ByteArray1, PCHAR ByteArray2, PCHAR Mask, DWORD Length) {
		DWORD nextStart = 0;
		char start = ByteArray2[0];
		for (DWORD i = 0; i < Length; i++) {
			if (Mask[i] == '?') {
				continue;
			}
			if (ByteArray1[i] == start) {
				nextStart = i;
			}
			if (ByteArray1[i] != (BYTE)ByteArray2[i]) {
				return nextStart;
			}
		}
		return -1;
	}

	PBYTE FindSignature(LPVOID BaseAddress, DWORD ImageSize, PCHAR Signature, PCHAR Mask) {
		PBYTE Address = NULL;
		PBYTE Buffer = (PBYTE)BaseAddress;

		DWORD Length = strlen(Mask);

		for (DWORD i = 0; i < (ImageSize - Length); i++) {
			int result = CompareByteArray((Buffer + i), Signature, Mask, Length);
			if (result < 0) {
				Address = (PBYTE)BaseAddress + i;
				break;
			}
			else {
				i += result;
			}
		}

		return Address;
	}

	void TestSigScan() {
			//Get all module related information
		MODULEINFO mInfo = GetModuleInfo(NULL);

		//Assign our base and module size
		uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;

		uintptr_t size = (uintptr_t)mInfo.SizeOfImage;

		char* foxmainSig = "\x48\x89\x00\x00\x00\x48\x89\x00\x00\x00\x57\x48\x83\xEC\x00\x83\x64\x24\x20";
		char* foxMainMask = "xx???xx???xxxx?xxxx";


		char* luaI_openlibSig = "\x45\x33\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE9";
		char* luaI_openlibMask = "xx?x????xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

		char* luaI_openlibSigShort = "\x45\x33\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC";
		char* luaI_openlibMaskShort = "xx?x????xxxxxxxx";

		//auto t1 = std::chrono::high_resolution_clock::now();
		//uintptr_t luaI_openlibOrig = FindPattern(NULL, luaI_openlibSig, luaI_openlibMask);
		//auto t2 = std::chrono::high_resolution_clock::now();

		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		//spdlog::debug("sig scan long time: {}",duration);

		auto t3 = std::chrono::high_resolution_clock::now();
		//uintptr_t luaI_openlibOrigShort = FindPattern(NULL, luaI_openlibSigShort, luaI_openlibMaskShort);
		//PBYTE luaI_openlibOrigShort = FindSignature(mInfo.lpBaseOfDll, mInfo.SizeOfImage, luaI_openlibSigShort, luaI_openlibMaskShort);

		//uintptr_t foxMainOrigFoundPattern = FindPattern(NULL, luaI_openlibSigShort, luaI_openlibMaskShort);
		PBYTE foxMainOrigFoundSig = FindSignature(mInfo.lpBaseOfDll, mInfo.SizeOfImage, luaI_openlibSigShort, luaI_openlibMaskShort);

		auto t4 = std::chrono::high_resolution_clock::now();

		auto durationShort = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
		spdlog::debug("sig scan short time: {}", durationShort);
	}
	//< TEST

	namespace Hooks_Lua {
		lua_State* luaState = NULL;
		lua_CFunction foxPanic;
		bool firstUpdate = false;
		static const std::wstring luaLogName = L"mod\\ih_log.txt";
		static const std::wstring luaLogNamePrev = L"mod\\ih_log_prev.txt";

		//fwd decl
		void ReplaceStubedOutLua(lua_State* L);
		void ReplaceStubedOutFox(lua_State* L);
		static int OnPanic(lua_State* L);
		void SetLuaVarMenuInitialized(lua_State* L);


		//tex actual detoured functions

		//tex there seems to be other calls to newstate that don't have lua libraries added, might be good to log calls to this and see if/when it's used)
		//not really doing much with this hook since I shifted to luaL_openlibs as the lua setup func, but it's kinda the start of lua init, in respect to the lua C api.
		//DEBUGNOW why does this crash unless you call the original function immediately?
		lua_State* __fastcall lua_newstateHook(lua_Alloc f, void* ud) {
			lua_State* L = lua_newstate(f, ud);
			spdlog::debug(__func__);

			luaState = L;//tex save reference to local

			return L;
		}//lua_newstateHook

		//tex may be better to hook the fox engine OpenLuawhatever that calls newstate and sets up the lua libraries
		//but don't know fox OpenLuas return type
		void __fastcall luaL_openlibsHook(lua_State* L) {
			spdlog::debug(__func__);
			luaL_openlibs(L);
#ifndef MINIMAL_HOOK
			if (debugMode) {
				TestHooks_Lua(L);
			}
#endif
			lua_pushinteger(L, Version);
			lua_setfield(L, LUA_GLOBALSINDEX, "_IHHook");

			LuaIHH::luaopen_ihh(L);
#ifndef MINIMAL_HOOK
			//OFF luaopen_winapi(L);
			LoadImguiBindings(L);
			if (debugMode) {
				TestHooks_Lua_PostLibs(L);
			}

			//tex: The fox modules wont be up by this point, so they have a seperate ReplaceStubbedOutFox
			ReplaceStubedOutLua(L);
#endif
			spdlog::debug("luaL_openlibsHook complete");
		}//lua_newstateHook

		//tex not doing anything with this, but it may be interesting to see everything that mgsv lua is loading.
		int luaL_loadbufferHook(lua_State *L, const char *buff, size_t size, const char *name) {
			spdlog::trace(__func__);
			spdlog::trace(name);
			//spdlog::trace(buff);
			
			return luaL_loadbuffer(L, buff, size, name);
		}//luaL_loadbufferHook

		//tex: divert to use our panic, which wraps the requested panic 
		lua_CFunction lua_atpanicHook(lua_State* L, lua_CFunction panicf) {
			foxPanic = panicf;
			lua_CFunction oldPanicFunc = lua_atpanic(L, OnPanic);
			return oldPanicFunc;
		}//lua_atpanicDetour

		//tex: caller DLLMain
		//IN/SIDE: IHHook::BaseAddr
		void CreateHooks(size_t RealBaseAddr) {
			spdlog::debug(__func__);

			//tex create ih_log
			DeleteFile(luaLogNamePrev.c_str());
			CopyFile(luaLogName.c_str(), luaLogNamePrev.c_str(), false);
			DeleteFile(luaLogName.c_str());

			luaLog = spdlog::basic_logger_st("lua", luaLogName);//tex st/single threaded since we want to preserver order, it's better performance, and we wont be logging from different threads
			luaLog->set_pattern("|%H:%M:%S:%e|%l: %v");

			if (debugMode) {
				luaLog->set_level(spdlog::level::trace);
				luaLog->flush_on(spdlog::level::trace);
			}
			else {
				luaLog->set_level(spdlog::level::info);
				luaLog->flush_on(spdlog::level::err);
			}

			CreateHooks_Lua(BaseAddr, RealBaseAddr);
			CreateHooks_Lauxlib(BaseAddr, RealBaseAddr);
			CreateHooks_Lualib(BaseAddr, RealBaseAddr);

			CREATEDETOURB(luaL_openlibs)
#ifndef MINIMAL_HOOK
			CREATEDETOURB(lua_newstate)
			CREATEDETOURB(luaL_loadbuffer)
			//OFF CREATEDETOURB(lua_atpanic)

			ENABLEHOOK(lua_newstate)
			ENABLEHOOK(luaL_loadbuffer)
			//OFF ENABLEHOOK(lua_atpanic) //tex works, but if you want to catch exceptions from this dll itself then it just trips here instead of near the actual problem
#endif		
			ENABLEHOOK(luaL_openlibs)
		}//CreateHooks

		//tex: replacement for MGSVs stubbed out "print", original lua implementation in lbaselib.c
		static int luaB_print(lua_State* L) {
			int n = lua_gettop(L);  /* number of arguments */
			int i;
			lua_getglobal(L, "tostring");
			for (i = 1; i <= n; i++) {
				const char* s;
				lua_pushvalue(L, -1);  /* function to be called */
				lua_pushvalue(L, i);   /* value to print */
				lua_call(L, 1, 1);
				s = lua_tostring(L, -1);  /* get result */
				if (s == NULL)
					return luaL_error(L, LUA_QL("tostring") " must return a string to "
						LUA_QL("print"));
				//if (i > 1) luaLog->debug("\t"); //tex was fputs("\t", stdout);
				luaLog->debug("{}", s); //tex was fputs(s, stdout);
				lua_pop(L, 1);  /* pop result */
			}
			//tex OFF fputs("\n", stdout);
			return 0;
		}

		static int FoxLog(spdlog::level::level_enum level, char* levelName, lua_State* L) {
			//TODO: skip out early if not in debug mode or log level?
			int n = lua_gettop(L);  /* number of arguments */
			int i;
			lua_getglobal(L, "tostring");
			std::string fullString = "Fox." + std::string(levelName) + ": ";
			for (i = 1; i <= n; i++) {
				const char* s;
				lua_pushvalue(L, -1);  /* function to be called */
				lua_pushvalue(L, i);   /* value to print */
				lua_call(L, 1, 1);
				s = lua_tostring(L, -1);  /* get result */
				if (s == NULL)
					return luaL_error(L, LUA_QL("tostring") " must return a string to "
						LUA_QL("print"));
				if (i > 1) fullString += "\t";
				fullString += s;
				lua_pop(L, 1);  /* pop result */
			}
			luaLog->log(level, fullString);
			return 0;
		}//FoxLog

		//tex: Since these are stubbed out in normal we should only log them in debug.
		static int l_Fox_Log(lua_State* L) {
			return FoxLog(spdlog::level::debug, "Log", L);
		}

		static int l_Fox_Caution(lua_State* L) {
			return FoxLog(spdlog::level::debug, "Caution", L);
		}

		static int l_Fox_Warning(lua_State* L) {
			return FoxLog(spdlog::level::warn, "Warning", L);
		}

		static int l_Fox_Error(lua_State* L) {
			return FoxLog(spdlog::level::err, "Error", L);
		}

		// game lua to IHHook callbacks>
		//tex called inside-out from init.lua via IH, TODO maybe see where init is loaded to make this independant from IH
		int l_FoxLua_Init(lua_State* L) {
#ifndef MINIMAL_HOOK
			ReplaceStubedOutFox(L);	//tex KLUDGE see comment on this function
#endif
			return 0;
		}//l_FoxLua_Init

		//tex called inside-out from InitMain.lua via IH
		int l_FoxLua_InitMain(lua_State* L) {
			//tex according to logging d3d (and imgui in ihhook) is initialized
			SetLuaVarMenuInitialized(L);

			return 0;
		}//l_FoxLua_Init

		//tex would maybe prefer to hook the funcion that calls mission_main.Onupdate
		//but having the lua call this at top of TppMain.OnUpdate should do
		//OnUpdate(missionTable)
		int l_FoxLua_OnUpdate(lua_State* L) {
			//spdlog::trace(__func__);
			if (!firstUpdate) {
				firstUpdate = true;
				spdlog::debug("First Lua Update");
				luaLog->debug("First Lua Update");
			}

			return 1;
		}//l_onupdate
		//game lua to IHHook callbacks<

		//tex retail build of MGSV stubs out a lot of functions, fortunately lua functions are often just entries in a table so we can try replace them.
		//base lua dist functions that were stubbed
		void ReplaceStubedOutLua(lua_State* L) {
			lua_pushcfunction(L, luaB_print);
			lua_setglobal(L, "print");
		}//ReplaceStubedOutLua

		//tex fox lua functions that were stubbed
		//KLUDGE: haven't got an early execution point figured out for when the Fox modules are done/up
		//so this is called via IH > IHH.Init/l_FoxLua_Init
		//which means on the off chance that Fox engine calls these functions via the lua C api before init is run. Extremely unlikely (they'd more likely call the C function that the lua functions were wrapping), but who knows.
		//DEBUGNOW functions still not being called
		void ReplaceStubedOutFox(lua_State* L) {
			lua_getfield(L, LUA_GLOBALSINDEX, "Fox");
			assert(lua_istable(L, -1));
			lua_pushcfunction(L, l_Fox_Log);
			lua_setfield(L, -2, "Log");
			lua_pushcfunction(L, l_Fox_Caution);
			lua_setfield(L, -2, "Caution");
			lua_pushcfunction(L, l_Fox_Warning);
			lua_setfield(L, -2, "Warning");
			lua_pushcfunction(L, l_Fox_Error);
			lua_setfield(L, -2, "Error");

		}//ReplaceStubedOutFox

		//tex: lua panic function (called on errors in unprotected calls).
		//test by creating an error in a non pcall function lua side.
		//TODO doesn't seem to fire
		static int OnPanic(lua_State* L) {
			const char* errorMsg = lua_tostring(L, -1);
			//tex was fprintf(stderr, "PANIC: unprotected error in call to Lua API (%s)\n",errorMsg);
			luaLog->error("PANIC: unprotected error in call to Lua API({})", errorMsg);
			if (foxPanic != NULL) {
				return foxPanic(L);
			}

			return 0;
		}//OnPanic

		//tex called from lua -> InfInitMain
		void SetLuaVarMenuInitialized(lua_State* L) {
			bool isFrameInitialized = g_ihhook->IsFrameInitialized();
			lua_getglobal(L, "IHH");
			lua_pushboolean(L, isFrameInitialized);
			lua_setfield(L, 1, "menuInitialized");
		}//SetLuaVarMenuInitialized

		//tex DEBUGNOW find a good spot in exection to call it
		void TestHooks_Lua_PostNewState(lua_State* L) {
			//tex cant be in newstate or following functions (luaL_openlibs) or it will recurse
			spdlog::debug(__func__);
			lua_State* nL = luaL_newstate();
			if (nL != NULL) {
				spdlog::debug("lua_close");
				lua_close(nL);
			}
		}//TestHooks_Lua_PostNewState
	}//namespace Hooks_Lua
}//namespace IHHoook