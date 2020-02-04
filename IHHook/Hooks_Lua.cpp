#include "stdafx.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"
#include "MinHook/MinHook.h"

#include "lua/lua_Addresses.h"
#include "lua/lauxlib_Addresses.h"
#include "lua/lualib_Addresses.h"

#include <queue>

//tex lua C module (well C++ because I converted so it would play nice with my mixed hooks and definitions version of the lua api)
int luaopen_winapi(lua_State *L);

namespace IHHook {
	lua_State* lua;
	lua_CFunction foxPanic;
	bool firstUpdate = false;
	std::wstring luaLogName = L"mod\\ih_log.txt";
	std::wstring luaLogNamePrev = L"mod\\ih_log_prev.txt";
	std::shared_ptr<spdlog::logger> luaLog;

	void TestHooks_Lua(lua_State* L);
	void CreateTestTable(lua_State * L);
	void TestHooks_Lua_PostLibs(lua_State * L);
	void ReplaceStubedOutLua(lua_State* L);
	void ReplaceStubedOutFox(lua_State* L);
	static int OnPanic(lua_State *L);
	static int luaopen_ihh(lua_State *L);

	extern void CreateHooks_Lua(size_t BaseAddr, size_t RealBaseAddr);
	extern void CreateHooks_Lauxlib(size_t BaseAddr, size_t RealBaseAddr);
	extern void CreateHooks_Lualib(size_t BaseAddr, size_t RealBaseAddr);

	//tex actual detoured functions

	//tex there seems to be other calls to newstate that don't have lua libraries added, might be good to log calls to this and see if/when it's used)
	//not really doing much with this hook since I shifted to luaL_openlibs as the lua setup func
	//DEBUGNOW why does this crash unless you call the original function immediately?
	lua_State* __fastcall lua_newstateHook(lua_Alloc f, void *ud) {
		lua_State* L = lua_newstate(f, ud);
		spdlog::debug(__func__);

		lua = L;//tex save reference to local

		return L;
	}//lua_newstateHook

	//tex may be better to hook the fox engine OpenLuawhatever that calls newstate and sets up the lua libraries
	//but don't know fox OpenLuas return type
	void __fastcall luaL_openlibsHook(lua_State *L) {
		spdlog::debug(__func__);
		luaL_openlibs(L);

#ifdef _DEBUG
		TestHooks_Lua(L);
#endif // _DEBUG

		lua_pushinteger(L, Version);
		lua_setfield(L, LUA_GLOBALSINDEX, "_IHHook");

		luaopen_ihh(L);
		//OFF luaopen_winapi(L);
#ifdef _DEBUG
		TestHooks_Lua_PostLibs(L);
#endif // _DEBUG

		//tex: The fox modules wont be up by this point, so they have a seperate ReplaceStubbedOutFox
		ReplaceStubedOutLua(L);

		//DEBUGNOW TODO figure out the earliest point the main window is done being created
		//DWORD pid = GetCurrentProcessId();
		//std::vector <HWND> vhWnds;
		//IHHook::GetAllWindowsFromProcessID(pid, vhWnds);
		InitializeInput();
		HWND hWnd = GetMainWindow();
		HookWndProc(hWnd);

		spdlog::debug("luaL_openlibsHook complete");
	}//lua_newstateHook

	//tex: divert to use our panic, which wraps the requested panic //DEBUGNOW test by creating an error in a non pcall function lua side.
	lua_CFunction lua_atpanicHook(lua_State *L, lua_CFunction panicf) {
		foxPanic = panicf;
		lua_CFunction oldPanicFunc = lua_atpanic(L, OnPanic);
		return oldPanicFunc;
	}//lua_atpanicDetour

	//tex: caller DLLMain
	//IN/SIDE: IHHook::BaseAddr
	void CreateHooks_LuaIHH(size_t RealBaseAddr) {
		spdlog::debug(__func__);

		//tex create ih_log
		DeleteFile(luaLogNamePrev.c_str());
		CopyFile(luaLogName.c_str(), luaLogNamePrev.c_str(), false);
		DeleteFile(luaLogName.c_str());

		luaLog = spdlog::basic_logger_st("lua", luaLogName);//tex st/single threaded since we want to preserver order, it's better performance, and we wont be logging from different threads
		luaLog->set_pattern("|%H:%M:%S:%e|%l: %v");

		CreateHooks_Lua(BaseAddr, RealBaseAddr);
		CreateHooks_Lauxlib(BaseAddr, RealBaseAddr);
		CreateHooks_Lualib(BaseAddr, RealBaseAddr);

		//DEBUGNOW CREATEDETOURB(lua_newstate)
		CREATEDETOURB(luaL_openlibs)
		CREATEDETOURB(lua_atpanic)
		//DEBUGNOW ENABLEHOOK(lua_newstate)
		ENABLEHOOK(luaL_openlibs)
		ENABLEHOOK(lua_atpanic)
	}//CreateHooks_Lua

	//tex: replacement for MGSVs stubbed out "print", original lua implementation in lbaselib.c
	static int luaB_print(lua_State *L) {
		int n = lua_gettop(L);  /* number of arguments */
		int i;
		lua_getglobal(L, "tostring");
		for (i = 1; i <= n; i++) {
			const char *s;
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

	static int FoxLog(spdlog::level::level_enum level, char * levelName, lua_State *L) {
		//TODO: skip out early if not in debug mode or log level?
		int n = lua_gettop(L);  /* number of arguments */
		int i;
		lua_getglobal(L, "tostring");
		std::string fullString = "Fox." + std::string(levelName) + ": ";
		for (i = 1; i <= n; i++) {
			const char *s;
			lua_pushvalue(L, -1);  /* function to be called */
			lua_pushvalue(L, i);   /* value to print */
			lua_call(L, 1, 1);
			s = lua_tostring(L, -1);  /* get result */
			if (s == NULL)
				return luaL_error(L, LUA_QL("tostring") " must return a string to "
					LUA_QL("print"));
			if (i > 1) fullString +="\t";
			fullString += s;
			lua_pop(L, 1);  /* pop result */
		}
		luaLog->log(level, fullString);
		return 0;
	}

	//tex: Since these are stubbed out in normal we should only log them in debug.
	static int l_Fox_Log(lua_State *L) {
		return FoxLog(spdlog::level::debug, "Log", L);
	}

	static int l_Fox_Caution(lua_State *L) {
		return FoxLog(spdlog::level::debug, "Caution", L);
	}

	static int l_Fox_Warning(lua_State *L) {
		return FoxLog(spdlog::level::warn, "Warning", L);
	}

	static int l_Fox_Error(lua_State *L) {
		return FoxLog(spdlog::level::err, "Error", L);
	}

	//tex called inside-out from init.lua via IH, TODO maybe see where init is loaded to make this independant from IH
	static int l_FoxLua_Init(lua_State *L) {
		ReplaceStubedOutFox(L);	//tex KLUDGE see comment on this function
		return 0;
	}//l_FoxLua_Init

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
	static int OnPanic(lua_State *L) {//DEBUGNOW TEST
		(void)L;  /* to avoid warnings */
		const char* errorMsg = lua_tostring(L, -1);
		//tex was fprintf(stderr, "PANIC: unprotected error in call to Lua API (%s)\n",errorMsg);
		luaLog->error("PANIC: unprotected error in call to Lua API({})",errorMsg);
		if (foxPanic != NULL) {
			return foxPanic(L);
		}
		
		return 0;
	}//OnPanic

	//tex DEBUGNOW find a good spot in exection to call it
	void TestHooks_Lua_PostNewState(lua_State * L) {
		//tex cant be in newstate or following functions (luaL_openlibs) or it will recurse
		spdlog::debug(__func__);
		lua_State *nL = luaL_newstate();
		if (nL != NULL) {
			spdlog::debug("lua_close");
			lua_close(nL);
		}
	};//TestHooks_Lua_PostNewState

	//IHH module>

	//tex lua doesnt have any explicit unicode support, so forgoing a more general starprocess function via lua for hardcoding to ihext
	static int l_StartIHExt(lua_State *L) {
		spdlog::debug(__func__);

		std::wstring gameDir = GetGameDir();
		std::wstring exeDir = gameDir + L"mod\\IHExt.exe";
		LPTSTR lpszFilePath = new TCHAR[MAX_PATH];
		std::wcscpy(lpszFilePath, exeDir.c_str());

		std::wstring commandLine = L" " + gameDir + L" mod mgsvtpp mgsv_in mgsv_out";//tex seems to need a leading space else ihext won't get the first arg
		LPTSTR lpCommandLine = new TCHAR[MAX_PATH];
		std::wcscpy(lpCommandLine, commandLine.c_str());

		StartProcess(lpszFilePath, lpCommandLine);

		delete[] lpszFilePath;
		delete[] lpCommandLine;

		return 1;
	}//l_startihext

	//log(int level, char * message)
	//OUT/SIDE: luaLog
	static int l_Log(lua_State *L) {
		//spdlog::trace(__func__ );

		int level = static_cast<int>(lua_tointeger(L, 1));
		const char * message = lua_tostring(L, -1);

		if (level < 0 || level > spdlog::level::off) {
			spdlog::warn("l_log: level outside range: {}", message);
			return 0;
		}

		luaLog->log(static_cast<spdlog::level::level_enum>(level), message);

		return 1;
	}//l_log

	static int l_GetModFilesList(lua_State *L) {
		spdlog::trace(__func__);
		std::vector<std::string> fullFileNames;
		std::string modDir = IHHook::GetGameDirA() + "mod";
		bool success = IHHook::ListFiles(modDir, "*", fullFileNames);

		unsigned int numNames = static_cast<unsigned int>(fullFileNames.size());
		if (numNames <= 0) {
			luaLog->error("GetModFilesList could not find any files in ./mod/");
			return 1;
		}

		lua_createtable(L, numNames, 0);
		for (int i = 0; i < fullFileNames.size(); i++) {
			spdlog::trace(fullFileNames[i].c_str());
			lua_pushstring(L, fullFileNames[i].c_str());
			lua_rawseti(L, -2, i + 1);//tex lua index from 1
		}//for fullFileNames

		return 1;
	}//l_getmodfileslist

	//SetLogFlushLevel(int level)
	//By default spdlog is very lazy with it's flush, which really helps performance wise
	//But often when you're debugging or developing stuff you want to read log updates near real time
	//spdlog does have a periodic flush, but can only be used on thread safe loggers (ihh is using st which isn't).
	static int l_Log_SetFlushLevel(lua_State *L) {
		int level = static_cast<int>(lua_tointeger(L, 1));
		if (level < 0 || level > spdlog::level::off) {
			spdlog::warn("l_setlogflushlevel: level outside range");
			return 1;
		}

		spdlog::flush_on(static_cast<spdlog::level::level_enum>(level));
		return 1;
	}//l_Log_SetFlushLevel

	static int l_Log_Flush(lua_State *L) {
		luaLog->flush();
		return 1;
	}//l_Log_Flush

	static int l_QueuePipeOutMessage(lua_State* L) {
		const char * message = lua_tostring(L, -1);
		QueueMessageOut(std::string(message));
		return 1;
	}


	//tex DEBUGNOW will have to rethink if we want something else to read the messages 
	//returns table of string messages from serverPipeIn
	static int l_GetPipeInMessages(lua_State* L) {
		if (!messagesIn.empty()) {
			std::unique_lock<std::mutex> inLock(inMutex);
			int size = (int)messagesIn.size();
			if (size > 0) {
				lua_createtable(L, size, 0);
				int index = 0;
				while (!messagesIn.empty()) {
					std::string message = messagesIn.front();
					messagesIn.pop();

					index++;
					lua_pushstring(L, message.c_str());
					lua_rawseti(L, -2, index);
				}
				assert(lua_gettop(L)==1);//tex table still on stack
				return 1;
			}
		}
		
		lua_pushnil(L);
		return 1;
	}

	//tex would maybe prefer to hook the funcion that calls mission_main.Onupdate
	//but having the lua call this at top of TppMain.OnUpdate should do
	//OnUpdate(missionTable)
	static int l_FoxLua_OnUpdate(lua_State *L) {
		//spdlog::trace("l_onupdate");
		if (!firstUpdate) {
			firstUpdate = true;
			spdlog::debug("First Lua Update");
			luaLog->debug("First Lua Update");
		}


		return 1;
	}//l_onupdate

	// < IHH module

	//tex TODO better module name, will likely break out into IHH<module name> as the amount of functions expands, but would have to change if IHH checks in IH
	static int luaopen_ihh(lua_State *L) {
		spdlog::debug(__func__);

		luaL_Reg ihh_funcs[] = {
			{ "StartIHExt", l_StartIHExt },
			{ "Log", l_Log },
			{ "Log_SetFlushLevel", l_Log_SetFlushLevel},
			{ "Log_Flush", l_Log_Flush},
			{ "GetModFilesList", l_GetModFilesList},
			{ "QueuePipeOutMessage", l_QueuePipeOutMessage },
			{ "GetPipeInMessages", l_GetPipeInMessages },
			{ "Init", l_FoxLua_Init},
			{ "OnUpdate", l_FoxLua_OnUpdate},
			{ NULL, NULL }
		};
		luaI_openlib(L, "IHH", ihh_funcs, 0);
		return 1;
	}//luaopen_ihh
}//namespace IHHoook