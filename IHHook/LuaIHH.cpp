#include "LuaIHH.h"

#include "spdlog/spdlog.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "Hooks_Lua.h"// l_FoxLua_Init, l_FoxLua_OnUpdate
#include "OS.h"
#include "PipeServer.h"

#include <string>

#include "IHMenu.h" // MenuMessage

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace LuaIHH {
		//IHH module funcs>

		//tex lua doesnt have any explicit unicode support, so forgoing a more general starprocess function via lua for hardcoding to ihext
		static int l_StartIHExt(lua_State* L) {
			spdlog::debug(__func__);

			std::wstring gameDir = OS::GetGameDir();
			std::wstring exeDir = gameDir + L"mod\\IHExt.exe";
			LPTSTR lpszFilePath = new TCHAR[MAX_PATH];
			std::wcscpy(lpszFilePath, exeDir.c_str());

			std::wstring commandLine = L" " + gameDir + L" mod mgsvtpp mgsv_in mgsv_out";//tex seems to need a leading space else ihext won't get the first arg
			LPTSTR lpCommandLine = new TCHAR[MAX_PATH];
			std::wcscpy(lpCommandLine, commandLine.c_str());

			OS::StartProcess(lpszFilePath, lpCommandLine);

			delete[] lpszFilePath;
			delete[] lpCommandLine;

			return 1;
		}//l_startihext

		//log(int level, char * message)
		//OUT/SIDE: luaLog
		static int l_Log(lua_State* L) {
			//spdlog::trace(__func__ );

			int level = static_cast<int>(lua_tointeger(L, 1));
			const char* message = lua_tostring(L, -1);

			if (level < 0 || level > spdlog::level::off) {
				spdlog::warn("l_log: level outside range: {}", message);
				return 0;
			}

			luaLog->log(static_cast<spdlog::level::level_enum>(level), message);

			return 1;
		}//l_log

		static int l_GetGamePath(lua_State* L) {
			std::string gamePath = OS::GetGameDirA() + "\\";
			lua_pushstring(L, gamePath.c_str());
			return 1;
		}//l_GetGamePath

		static int l_GetModFilesList(lua_State* L) {
			spdlog::trace(__func__);
			std::vector<std::string> fullFileNames;
			std::string modDir = OS::GetGameDirA() + "mod";
			bool success = OS::ListFiles(modDir, "*", fullFileNames);

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
		static int l_Log_SetFlushLevel(lua_State* L) {
			int level = static_cast<int>(lua_tointeger(L, 1));
			if (level < 0 || level > spdlog::level::off) {
				spdlog::warn("l_setlogflushlevel: level outside range");
				return 1;
			}

			spdlog::flush_on(static_cast<spdlog::level::level_enum>(level));
			return 1;
		}//l_Log_SetFlushLevel

		static int l_Log_Flush(lua_State* L) {
			spdlog::trace(__func__);
			luaLog->flush();
			return 1;
		}//l_Log_Flush

		static int l_QueuePipeOutMessage(lua_State* L) {
			const char* message = lua_tostring(L, -1);
			PipeServer::QueueMessageOut(std::string(message));
			return 1;
		}//l_QueuePipeOutMessage

		//tex DEBUGNOW will have to rethink if we want something else to read the messages 
		//returns table of string messages from serverPipeIn
		static int l_GetPipeInMessages(lua_State* L) {
			if (!PipeServer::messagesIn.empty()) {
				std::unique_lock<std::mutex> inLock(PipeServer::inMutex);
				int size = (int)PipeServer::messagesIn.size();
				if (size > 0) {
					lua_createtable(L, size, 0);
					int index = 0;
					while (!PipeServer::messagesIn.empty()) {
						std::string message = PipeServer::messagesIn.front();
						PipeServer::messagesIn.pop();

						index++;
						lua_pushstring(L, message.c_str());
						lua_rawseti(L, -2, index);
					}
					assert(lua_gettop(L) == 1);//tex table still on stack
					return 1;
				}
			}

			lua_pushnil(L);//tex DEBUGNOW why am I doing this?
			return 1;
		}//l_GetPipeInMessages

		static int l_MenuMessage(lua_State* L) {
			//spdlog::trace(__func__);
			const char* cmd = lua_tostring(L, 1);
			const char* message = lua_tostring(L, 2);
			spdlog::debug("l_MenuMessage cmd:{},<> message:{}",cmd,message); //DEBUGNOW
			IHMenu::MenuMessage(cmd, message);
			return 1;
		}//l_MenuMessage

		//tex use as a callback to test random shiz
		int l_TestCallToIHHook(lua_State* L) {
			spdlog::trace(__func__);

			//DEBUGNOW
			void* data = lua_touserdata(L, -1);
			
			return 1;
		}//l_TestCallToIHHook
		// < IHH module funcs

		//tex TODO better module name, will likely break out into IHH<module name> as the amount of functions expands, but would have to change if IHH checks in IH
		int luaopen_ihh(lua_State* L) {
			spdlog::debug(__func__);

			luaL_Reg ihh_funcs[] = {
				{ "StartIHExt", l_StartIHExt },
				{ "Log", l_Log },
				{ "Log_SetFlushLevel", l_Log_SetFlushLevel},
				{ "Log_Flush", l_Log_Flush},
				{ "GetGamePath", l_GetGamePath},
				{ "GetModFilesList", l_GetModFilesList},
				{ "QueuePipeOutMessage", l_QueuePipeOutMessage },
				{ "GetPipeInMessages", l_GetPipeInMessages },
				{ "MenuMessage", l_MenuMessage },
				{ "Init", Hooks_Lua::l_FoxLua_Init},
				{ "OnUpdate", Hooks_Lua::l_FoxLua_OnUpdate},
				{ "TestCallToIHHook", l_TestCallToIHHook},
				{ NULL, NULL }
			};
			luaI_openlib(L, "IHH", ihh_funcs, 0);
			return 1;
		}//luaopen_ihh
	}//namespace LuaIHH
}//namespace IHHook