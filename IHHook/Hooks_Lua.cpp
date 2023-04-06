/*
	tex: msgvtpp has lua 5.1.5 statically linked
	IHHook hooks lua by function addresses (defined in lua/*_Addresses.h), using (macros wrapping) MH_Hook initialised in CreateHooks() below
	it also replaces the lua function declarations in the lua distro (using the FUNCPTRDEF macros) so other code can build against it. TODO: this is no longer true, they currently in func_typedefs
	In some cases uses actual lua lib implementation.
	See comments on CREATE_FUNCPTR entries in *_Creathooks.cpp.

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
#include "Hooks_Character.h"//CreateLibs //TODO: don't like this in here
#include "Hooks_Buddy.h" //ZIP: For buddies
#include "Hooks_Vehicle.h" //ZIP: For vehicles
//TODO: see ghidra/ExportInfo.py CreateInPlace//#include "Hooks_FoxString.h" //ZIP: FoxString hook
//#include "Hooks_CallMenu.h" //ZIP: For Call Menu //tex not in zips current pushed fork

#include <string>
#include "hooks/mgsvtpp_func_typedefs.h"
#include "HookMacros.h"

extern void LoadImguiBindings(lua_State* lState);

namespace IHHook {
	//Hooks_Lua_Test
	extern void TestHooks_Lua(lua_State* L);
	extern void TestHooks_Lua_PostLibs(lua_State* L);
	
	//tex CULL lua C module (well C++ because I converted so it would play nice with my mixed hooks and definitions version of the lua api)
	//extern int luaopen_winapi(lua_State* L);

	int ihVersion = 0;

	std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_Lua {
		void CreateLibs(lua_State* L);

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

		//http://www.lua.org/manual/5.1/manual.html#lua_pcall (also see the other functions that call HandleLuaError)
		void HandleLuaError(lua_State* L, int errcode, int errfunc) {
			switch (errcode) {
				case LUA_ERRMEM: {
					spdlog::error("lua_(c)pcall: LUA_ERRMEM: not enough memory");
					luaLog->error("lua_(c)pcall: LUA_ERRMEM: not enough memory");
					break;
				}
				case LUA_ERRERR: {
					spdlog::error("lua_(c)pcall: LUA_ERRERR: error in error handling");
					luaLog->error("lua_(c)pcall: LUA_ERRERR: error in error handling");
					break;
				}
				case LUA_ERRSYNTAX: {
					//if (errfunc == 0) {
						std::string errormsg = lua_tostring(L, -1);
						spdlog::error("lua_(c)pcall: LUA_ERRSYNTAX: {}", errormsg);
						luaLog->error("lua_(c)pcall: LUA_ERRSYNTAX: {}", errormsg);
					//}
					break;
				}
				case LUA_ERRRUN: {
					//if (errfunc == 0) {
						std::string errormsg = lua_tostring(L, -1);
						spdlog::error("lua_(c)pcall: LUA_ERRRUN: {}", errormsg);
						luaLog->error("lua_(c)pcall: LUA_ERRRUN: {}", errormsg);
					//}
					break;
				}
			}//switch errcode
		}//HandleLuaError

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

		lua_State* lua_newthreadHook(lua_State* L) {
			spdlog::debug(__func__);
			lua_State* nL = lua_newthread(L);

			return nL;
		}//lua_newthreadHook

		//tex may be better to hook the fox engine OpenLuawhatever that calls newstate and sets up the lua libraries
		//but don't know fox OpenLuas return type
		void __fastcall luaL_openlibsHook(lua_State* L) {
			spdlog::debug(__func__);
			luaL_openlibs(L);

			if (config.debugMode) {
				TestHooks_Lua(L);
			}
			lua_pushinteger(L, Version);
			lua_setfield(L, LUA_GLOBALSINDEX, "_IHHook");

			CreateLibs(L);

			//OFF luaopen_winapi(L);
			LoadImguiBindings(L);
			if (config.debugMode) {
				TestHooks_Lua_PostLibs(L);
			}

			//tex: The fox modules wont be up by this point, so they have a seperate ReplaceStubbedOutFox
			ReplaceStubedOutLua(L);
#ifdef _DEBUG
			ENABLE_HOOK(l_StubbedOut);//tex: see l_StubbedOutHook
#endif // DEBUG

			spdlog::debug("luaL_openlibsHook complete");
		}//luaL_openlibsHook

		int lua_loadHook(lua_State* L, lua_Reader reader,void* data, const char* chunkname) {
			spdlog::trace("lua_loadHook {}", chunkname);
			int errcode = lua_load(L, reader, data, chunkname);
			if (errcode != 0) {
				//tex OFF hooking lua_error is enough, but keeping the hook because I want to load calls to lua_load -^-
				//spdlog::error(__func__);
				//HandleLuaError(L, errcode, 0);
			}//if errcode != 0
			return errcode;
		}//lua_loadHook

		//tex not doing anything with this, but it may be interesting to see everything that mgsv lua is loading.
		//and dumping the buffer of stuff that's not from a lua file
		//not doing error handling here as lua_loadHook has that
		int luaL_loadbufferHook(lua_State *L, const char *buff, size_t size, const char *name) {
			//spdlog::trace("luaL_loadbufferHook {}", name);//tex OFF since lua_loadHook grabs it fine, but not diabling the hook in case I want to breakpoint this on a whim
			//spdlog::trace(buff);//TODO: dump stuff that's not from a file 
			
			return luaL_loadbuffer(L, buff, size, name);
		}//luaL_loadbufferHook

		//tex: divert to use our panic, which wraps the requested panic 
		lua_CFunction lua_atpanicHook(lua_State* L, lua_CFunction panicf) {
			spdlog::debug(__func__);
			foxPanic = panicf;//tex TODO: see if this is actually a custom panic function/not the lua default
			lua_CFunction oldPanicFunc = lua_atpanic(L, OnPanic);
			return oldPanicFunc;
		}//lua_atpanicDetour

		static int traceback(lua_State* L) {
			lua_getfield(L, LUA_GLOBALSINDEX, "debug");
			lua_getfield(L, -1, "traceback");
			lua_pushvalue(L, 1);
			lua_pushinteger(L, 2);
			lua_call(L, 2, 1);
			std::string tracebackmsg = lua_tostring(L, -1);
			spdlog::error(tracebackmsg);
			luaLog->error(tracebackmsg);
			//tex DEBUGNOW should I be popping off all I added?
			return 1;
		}//traceback

		//tex TODO: hook luaG_errormsg instead since it also catches luaG_runerror (and lua_error also calls)
		int lua_errorHook(lua_State* L) {
			std::string errormsg = lua_tostring(L, -1);
			spdlog::error("lua_error: {}", errormsg);
			luaLog->error("lua_error: {}", errormsg);
			//tex uhh, is this ok calling in the error itself? the usual use is via xpcall error func callback (or failing that on pcall return)
			//lua_pushcfunction(L, traceback);//DEBUGNOW not sure why this isnt working
			return lua_error(L);
		}//lua_errorHook

		int lua_pcallHook(lua_State* L, int nargs, int nresults, int errfunc) {
			int errcode = lua_pcall(L, nargs, nresults, errfunc);
			if (errcode != 0) {
				//tex pcall doesn't call lua_error (because the point of it is you're handling things), 
				//but some stuff like require/loading (see loaderror) that I tend to wrap in pcall in IH 
				//(simply from non IHHook not being able to log it otherwise, and to catch success/fail) 
				//so you'll get doubling of errors up in the logs
				HandleLuaError(L, errcode, errfunc);
			}//errcode != 0
			return errcode;
		}//lua_pcallHook

		int lua_cpcallHook(lua_State* L, lua_CFunction func, void* ud) {
			int errcode = lua_cpcall(L, func, ud);
			if (errcode != 0) {
				HandleLuaError(L, errcode, 0);
			}
			return errcode;
		}//lua_cpcallHook

		//DEBUGNOW move somewhere usefull
		static void dumpstack(lua_State* L) {
			//spdlog::trace(__func__);//DEBUG
			int top = lua_gettop(L);
			if (top < 0) {
				spdlog::warn("dumpstack lua_gettop == {}. is < 0, returning", top);
				return;
			}

			if (top > 100) {
				spdlog::warn("dumpstack lua_gettop == {}. is > 100, returning",top);
				return;
			}

			if (top == 0) {
				return;
			}
			//DEBUGNOW
			for (int i = 1; i <= top; i++) {
				//spdlog::debug("{}\t{}\t", i, luaL_typename(L, i));
				switch (lua_type(L, i)) {
				case LUA_TNUMBER:
					luaLog->debug("{} number:\t {}", i, lua_tonumber(L, i));
					break;
				case LUA_TSTRING:
					luaLog->debug("{} string:\t {}", i, lua_tostring(L, i));
					break;
				case LUA_TBOOLEAN:
					luaLog->debug("{} bool:\t {}", i, (lua_toboolean(L, i) ? "true" : "false"));
					break;
				case LUA_TNIL:
					luaLog->debug("{} nil:\t nil", i);
					break;
				default:
					luaLog->debug("{} pointer:\t {}", i, lua_topointer(L, i));
					break;
				}
			}
		}//dumpstack

		//tex retail build of MGSV stubs out a lot of functions (changes the function name > l_ function to point to same stubbed out function), 
		//unfortunately since they cut it off this way the only viable functions to replace are ones we already know about 
		//(like luaB_print, see ReplaceStubedOutFox below)
		//see in exe the function base_funcs "print" points to, then see all other references to that func to see others that were treated that way
		//Also 
		//DEBUGNOW it's being called before lua is even inited? only enabling hook after for now (the current ENABLEHOOK(l_StubbedOut) and commented out ENABLEHOOK(l_StubbedOut))
		//DEBUGNOW there's a lot of uses of this replaced function that have alternate code paths if something other than 0 is returned
		static int l_StubbedOutHook(lua_State* L) {
			//tex DEBUGNOW crashing on some peoples machines
#ifdef DEBUG
			//spdlog::debug(__func__);//DEBUG also logging func after the guards below
			//DEBUGNOW don't like this, this function is being called before lua is up suggesting its stubbing out non lua stuff?
			if(luaState == NULL) {
				return 0;
			}
			int top = lua_gettop(L);
			if (top <= 0) {
				return 0;
			}
			//KLUDGE:
			if (top > 10) {
				return 0;
			}
			spdlog::debug(__func__);
			//DEBUGNOW dumpstack(L);//tex GOTCHA: logs to lualog/ih_log not ihhook_log
#endif // DEBUG
			return 0;
		}//l_StubbedOutHook

		void SetupLog() {
			//tex create ih_log
			DeleteFile(luaLogNamePrev.c_str());
			CopyFile(luaLogName.c_str(), luaLogNamePrev.c_str(), false);
			DeleteFile(luaLogName.c_str());

			luaLog = spdlog::basic_logger_st("lua", luaLogName);//tex st/single threaded since we want to preserver order, it's better performance, and we wont be logging from different threads
			if (config.logTime) {
				luaLog->set_pattern("|%H:%M:%S:%e|%l: %v");
			}
			else {
				luaLog->set_pattern("%l: %v");
			}
			//tex TODO: should default to trace anyway? following IH style of being verbose during start and switching down if IH debug mode not on, 
			//mostly because otherwise getting user to add ihhook_config with debugMode, rather than just turning on IH debug mode is a bigger ask
			if (config.debugMode) {
				luaLog->set_level(spdlog::level::trace);
				luaLog->flush_on(spdlog::level::trace);
			}
			else {
				luaLog->set_level(spdlog::level::info);
				luaLog->flush_on(spdlog::level::warn);
			}
		}//SetupLog

		//tex: caller DLLMain
		//IN/SIDE: IHHook::BaseAddr
		void CreateHooks() {
			spdlog::debug(__func__);
			
			if (!HAS_ADDRESS(lua::luaL_openlibs)
				|| !HAS_ADDRESS(lua::lua_newstate)
				|| !HAS_ADDRESS(lua::lua_newthread)
				|| !HAS_ADDRESS(lua::lua_load)
				|| !HAS_ADDRESS(lua::luaL_loadbuffer)
				|| !HAS_ADDRESS(lua::lua_atpanic)
				|| !HAS_ADDRESS(lua::lua_error)
				|| !HAS_ADDRESS(lua::lua_pcall)
				|| !HAS_ADDRESS(lua::lua_cpcall)
				|| !HAS_ADDRESS(l_StubbedOut)
				) {//DEBUGNOW 
				spdlog::warn("Hooks_Lua addr fail: address==NULL");
			}
			else {
				CREATE_HOOK(lua::luaL_openlibs, luaL_openlibsHook);
				CREATE_HOOK(lua::lua_newstate, lua_newstateHook);
				CREATE_HOOK(lua::lua_newthread, lua_newthreadHook);
				CREATE_HOOK(lua::lua_load, lua_loadHook);
				CREATE_HOOK(lua::luaL_loadbuffer, luaL_loadbufferHook);
				CREATE_HOOK(lua::lua_atpanic, lua_atpanicHook);
				CREATE_HOOK(lua::lua_error, lua_errorHook);
				CREATE_HOOK(lua::lua_pcall, lua_pcallHook);
				CREATE_HOOK(lua::lua_cpcall, lua_cpcallHook);

				ENABLE_HOOK(lua::luaL_openlibs);
				ENABLE_HOOK(lua::lua_newstate);
				ENABLE_HOOK(lua::lua_newthread);
				ENABLE_HOOK(lua::lua_load);
				ENABLE_HOOK(lua::luaL_loadbuffer);
				ENABLE_HOOK(lua::lua_atpanic); //tex works, but if you want to catch exceptions from this dll itself then it just trips here instead of near the actual problem
				ENABLE_HOOK(lua::lua_error);
				ENABLE_HOOK(lua::lua_pcall);
				ENABLE_HOOK(lua::lua_cpcall);

				CREATE_HOOK(l_StubbedOut, l_StubbedOutHook);
				//ENABLEHOOK(l_StubbedOut)//DEBUGNOW enabling after lua is init in openlibs see l_StubbedOutHook
			}//if name##Addr != NULL
		}//CreateHooks

		//TODO: document/make more discoverable
		void CreateLibs(lua_State* L) {
			LuaIHH::luaopen_ihh(L);
			Hooks_Character::CreateLibs(L);
			Hooks_Buddy::CreateLibs(L); //ZIP: For buddies
			Hooks_Vehicle::CreateLibs(L); //ZIP: For vehicles
			//TODO: see ghidra/ExportInfo.py CreateInPlace//Hooks_FoxString::CreateLibs(L); //ZIP: FoxString hook
			//Hooks_CallMenu::CreateLibs(L); //ZIP: For Call Menu  //tex not in zips current pushed fork
		}//CreateLibs

		//tex: replacement for MGSVs stubbed out "print", original lua implementation in lbaselib.c
		static int luaB_print(lua_State* L) {
			spdlog::trace(__func__);
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
			ReplaceStubedOutFox(L);	//tex KLUDGE see comment on this function

			return 0;
		}//l_FoxLua_Init

		//tex called inside-out from InitMain.lua via IH
		int l_FoxLua_InitMain(lua_State* L) {
			//tex TODO: a SetIHVersion called from InfCore itself may be better
			ihVersion = (int)lua_tointeger(L, -1);
			lua_pop(L, -1);
			spdlog::debug("InitMain IHr{}", ihVersion);

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

		//tex see l_StubbedOutHook
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