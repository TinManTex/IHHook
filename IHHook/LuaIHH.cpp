#include "LuaIHH.h"

#include "spdlog/spdlog.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "Hooks_Lua.h"// l_FoxLua_Init, l_FoxLua_OnUpdate
#include "OS.h"
#include "PipeServer.h" // QueueMessageOut, messagesIn
#include <filesystem>
#include <string>
#include <optional>
#include <map>

#include "IHMenu.h" // MenuMessage, messagesIn
#include "Hooks_TPP.h"
#include "Hooks_FOV.h"
#include "hooks/mgsvtpp_func_typedefs.h"//StrCode64

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	extern std::map<int, long long> locationLangIds;

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

		static int l_FileExists(lua_State* L) {
			//spdlog::trace(__func__);
			std::string fileName = lua_tostring(L, 1);
			lua_pop(L, 1);
			bool exists=std::filesystem::exists(fileName);
			spdlog::trace("l_FileExists {} = {}", fileName, exists);
			lua_pushboolean(L, exists);
			return 1;
		}//l_FileExists

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
			std::optional <std::string> messageOpt = PipeServer::messagesIn.pop();//tex waits if empty		
			if (!messageOpt) {
				lua_pushnil(L);//tex no messages
				return 1;
			}
			int index = 0;
			lua_createtable(L, 0, 0);
			while (messageOpt) {
				std::string message = *messageOpt;

				index++;
				lua_pushstring(L, message.c_str());
				lua_rawseti(L, -2, index);//tex add to table

				messageOpt = PipeServer::messagesIn.pop();
			}//while messageOpt
			assert(lua_gettop(L) == 1);//tex table still on stack
			return 1;
		}//l_GetPipeInMessages

		static int l_MenuMessage(lua_State* L) {
			//spdlog::trace(__func__);
			const char* cmd = lua_tostring(L, 1);
			const char* message = lua_tostring(L, 2);
			spdlog::trace("l_MenuMessage cmd:{},<> message:{}",cmd,message); //DEBUGNOW
			IHMenu::QueueMessageOut(message);
			return 1;
		}//l_MenuMessage

		//tex since the menu is run through the normal game lua update loop can't really just have ui call lua directly for actions
		//so it dumps them into a queue for the lua menu to grab and process, pretty much the same way pipe in messages are handled
		//may have to rethink if expanding ui stuff beyond the IH menu
		//returns table of string messages from IHMenu
		static int l_GetMenuMessages(lua_State* L) {
			std::optional <std::string> messageOpt = IHMenu::messagesIn.pop();//tex waits if empty
			if (!messageOpt) {
				lua_pushnil(L);//tex no messages
				return 1;
			}
			int index = 0;
			lua_createtable(L, 0, 0);
			while (messageOpt) {
				std::string message = *messageOpt;

				index++;
				lua_pushstring(L, message.c_str());
				lua_rawseti(L, -2, index);

				messageOpt = IHMenu::messagesIn.pop();
			}//while messageOpt
			assert(lua_gettop(L) == 1);//tex table still on stack
			return 1;
		}//l_GetMenuMessages

		//REF
		//{
		//	{locationCode, langIdStr64},
		//	...

		//input lua table {{int langCode,string langId},...}
		//REF IH InfMission.UpdateChangeLocationMenu
		static int l_UpdateChangeLocationMenu(lua_State* L) {
			spdlog::trace(__func__);

			if (!lua_istable(L, -1)) {
				luaLog->error("UpdateChangeLocationMenu expected table");
				return 1;
			}
			//ASSUMPTION: table includes the vanilla location landIds
			//see locationLangIds initialisation for those deaults
			//and IH InfMission.UpdateChangeLocationMenu where it adds them at top
			locationLangIds.clear();

			/* table is in the stack at index 't' */
			lua_pushnil(L);  /* first key */
			while (lua_next(L, -2) != 0) {//tex locationLangIds param now at second on stack since nil was pushed
				/* uses 'key' (at index -2) and 'value' (at index -1) */
				int locationCode = (int)lua_tointeger(L, -2);
				const char* langId = lua_tostring(L, -1);
				luaLog->info("{}={}",locationCode,langId);
				locationLangIds[locationCode] = StrCode64(langId, strlen(langId));
				/* removes 'value'; keeps 'key' for next iteration */
				lua_pop(L, 1);
			}

			return 1;
		}//l_UpdateChangeLocationMenu
		
		//tex use as a callback to test random shiz
		int l_TestCallToIHHook(lua_State* L) {
			spdlog::trace(__func__);

			//DEBUGNOW
			void* data = lua_touserdata(L, -1);
			
			return 1;
		}//l_TestCallToIHHook
		// < IHH module funcs

		//tex TODO better module name, will likely break out into IHH<module name> as the amount of functions expands, but would have to change 'if IHH' checks in IH
		int luaopen_ihh(lua_State* L) {
			spdlog::debug(__func__);

			luaL_Reg ihh_funcs[] = {
				{ "StartIHExt", l_StartIHExt },
				{ "Log", l_Log },
				{ "Log_SetFlushLevel", l_Log_SetFlushLevel},
				{ "Log_Flush", l_Log_Flush},
				{ "GetGamePath", l_GetGamePath},
				{ "GetModFilesList", l_GetModFilesList},
				{ "FileExists", l_FileExists },
				{ "QueuePipeOutMessage", l_QueuePipeOutMessage },
				{ "GetPipeInMessages", l_GetPipeInMessages },
				{ "MenuMessage", l_MenuMessage },
				{ "GetMenuMessages", l_GetMenuMessages },
				{ "Init", Hooks_Lua::l_FoxLua_Init},
				{ "InitMain", Hooks_Lua::l_FoxLua_InitMain},
				{ "OnUpdate", Hooks_Lua::l_FoxLua_OnUpdate},
				{ "UpdateChangeLocationMenu", l_UpdateChangeLocationMenu},
				{ "SetCamHook", Hooks_FOV::l_SetCamHook },
				{ "UpdateCamHook", Hooks_FOV::l_UpdateCamHook },
				{ "TestCallToIHHook", l_TestCallToIHHook},
				{ NULL, NULL }
			};
			luaI_openlib(L, "IHH", ihh_funcs, 0);
			return 1;
		}//luaopen_ihh
	}//namespace LuaIHH
}//namespace IHHook