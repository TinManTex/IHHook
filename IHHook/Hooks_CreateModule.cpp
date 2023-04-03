//tex due to how modules are set up many of the enum and function names aren't viewable in plain text via lua runtime
//so logging the creation of these modules so mockfox build functions can recover them
#include "Hooks_LoadFile.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//BaseAddr,enableCityHook
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_CreateModule {
		std::wstring logName = L"log_createmodule.txt";
		std::shared_ptr<spdlog::logger> log;

		foxlua::module* NewModuleHook(undefined8 param_1, const char* moduleName, undefined8 param_3, undefined8 param_4, char param_5) {
			if (config.enableCreateModuleHook) {
				log->info("module:{}", moduleName);
			}
			return foxlua::NewModule(param_1, moduleName, param_3, param_4, param_5);
		}//NewModuleHook

		foxlua::module* NewSubModuleHook(foxlua::module* parentModule, const char* moduleName, undefined8 param_3, undefined8 param_4, char param_5) {
			if (config.enableCreateModuleHook) {
				log->info("submodule:{}", moduleName);
			}
			return NewSubModule(parentModule, moduleName, param_3, param_4, param_5);
		}//NewSubModuleHook

		int AddCFuncToModuleHook(foxlua::module* module, const char* funcName, lua_CFunction cfunc, undefined8 param_4, int param_5, void* param_6) {
			if (config.enableCreateModuleHook) {
				log->info("function:{}", funcName);
			}
			return AddCFuncToModule(module, funcName, cfunc, param_4, param_5, param_6);
		}//AddCFuncToModuleHook

		int AddCFuncToModule2Hook(foxlua::module* module, const char* funcName, void* param_3) {
			if (config.enableCreateModuleHook) {
				log->info("function2:{}", funcName);
			}
			return AddCFuncToModule2(module, funcName, param_3);
		}//AddCFuncToModule2Hook

		undefined8 AddCFuncToModule3Hook(foxlua::module* moduleName, const char* funcName, lua_CFunction param_3, int param_4, void* param_5) {
			if (config.enableCreateModuleHook) {
		//		log->info("function3:{}", funcName); //tex seems to be just a sub of AddCFuncToModule
			}
			return AddCFuncToModule3(moduleName, funcName, param_3, param_4, param_5);
		}//AddCFuncToModule3Hook

		void AddEnumToModuleHook(foxlua::module* foxModule, const char* enumName, int enumValue) {
			if (config.enableCreateModuleHook) {
				log->info("enum:{}={}", enumName, enumValue);
			}
			return AddEnumToModule(foxModule, enumName, enumValue);
		}//AddEnumToModuleHook

		bool AddEnumToModule2Hook(foxlua::module* module, const char* enumName, int* enumValue) {
			int value = *enumValue;
			if (config.enableCreateModuleHook) {
				//log->info("enum2:{}={}", enumName, value); //tex seems to be just a sub of AddEnumToModule
			}
			return AddEnumToModule2(module, enumName, enumValue);
		}//AddEnumToModule2Hook

		void AddEnumToModule3Hook(foxlua::module* module, const char* enumName, undefined8 enumValue) {
			if (config.enableCreateModuleHook) {
				log->info("enum3:{}={}", enumName, enumValue);
			}
			return AddEnumToModule3(module, enumName, enumValue);
		}//AddEnumToModule3Hook

		undefined AddEnumToModule4Hook(undefined8 module, undefined8 enumName, undefined8 enumValue) {
			if (config.enableCreateModuleHook) {
			//	log->info("enum4:{}={}", enumName, enumValue); //tex dont know whats going on with this at a glance
			}
			return AddEnumToModule4(module, enumName, enumValue);
		}//AddEnumToModule4Hook

		undefined RegisterVarHook(undefined8 foxLua, const char* varName, undefined8 varAddress, lua_CFunction* luaCFunc) {
			if (config.enableCreateModuleHook) {
				log->info("var:{}", varName);
			}
			return RegisterVar(foxLua, varName, varAddress, luaCFunc);
		}//RegisterVarHook

		void RegisterVar_01Hook(longlong param_1, const char* varName, undefined4 param_3, undefined8 param_4, undefined2 param_5, undefined param_6) {
			if (config.enableCreateModuleHook) {
				log->info("var1:{}", varName);
			}
			return RegisterVar_01(param_1, varName, param_3, param_4, param_5, param_6);
		}//RegisterVar_01Hook

		void RegisterVar_02Hook(undefined8 param_1, const char* varName, undefined8 param_3, char param_4) {
			if (config.enableCreateModuleHook) {
			//	log->info("var2:{}", varName);//tex sub of RegisterVar?
			}
			RegisterVar_02(param_1, varName, param_3, param_4);
		}//RegisterVar_02Hook

		//int RegisterVar_03Hook(foxlua::module* param_1, const char* varName, void* varAddress, lua_CFunction unkLuaCFunc) {
		//	if (config.enableCreateModuleHook) {
		//		log->info("var3:{}", varName);
		//	}
		//	RegisterVar_03(param_1, varName, varAddress, unkLuaCFunc);
		//}//RegisterVar_03Hook

		bool RegisterVarArrayHook(foxlua::module* module, const char* varName, lua_CFunction param_3, lua_CFunction param_4, undefined8 param_5, undefined* param_6, undefined* param_7, undefined8 arraySize) {
			if (config.enableCreateModuleHook) {
				log->info("varArray:{}", varName);
			}
			return RegisterVarArray(module, varName, param_3, param_4, param_5, param_6, param_7, arraySize);
		}//RegisterVarArrayHook

		//tex DEBUGNOW not really createmodule, but interesting to get its execflow
		undefined4* DeclareEntityClassHook(undefined4* param_1, const char* className, longlong entityInfo) {
			if (config.enableCreateModuleHook) {
				log->info("DeclareEntityClass:{}", className);
			}
			return DeclareEntityClass(param_1, className, entityInfo);
		}//DeclareEntityClassHook

		void CreateHooks() {
			spdlog::debug("Hooks_CreateModule::CreateHooks");
			DeleteFile(logName.c_str());

			if (config.enableCreateModuleHook) {
				log = spdlog::basic_logger_st("loadfile", logName);
				log->set_pattern("%v");//tex raw logging
										
				CREATE_HOOK_NS(foxlua::NewModule,NewModuleHook)
				CREATE_HOOK_NS(NewSubModule,NewSubModuleHook)
				CREATE_HOOK(AddCFuncToModule)
				CREATE_HOOK(AddCFuncToModule2)
				CREATE_HOOK(AddCFuncToModule3)
				CREATE_HOOK(AddEnumToModule)
				CREATE_HOOK(AddEnumToModule2)
				CREATE_HOOK(AddEnumToModule3)
				CREATE_HOOK(AddEnumToModule4)
				CREATE_HOOK(RegisterVar)
				CREATE_HOOK(RegisterVar_01)
				CREATE_HOOK(RegisterVar_02)
				//CREATE_HOOK(RegisterVar_03)
				CREATE_HOOK(RegisterVarArray)
				CREATE_HOOK(DeclareEntityClass)

				ENABLEHOOK(NewModule)
				ENABLEHOOK(NewSubModule)
				ENABLEHOOK(AddCFuncToModule)
				ENABLEHOOK(AddCFuncToModule2)
				ENABLEHOOK(AddCFuncToModule3)
				ENABLEHOOK(AddEnumToModule)
				ENABLEHOOK(AddEnumToModule2)
				ENABLEHOOK(AddEnumToModule3)
				ENABLEHOOK(AddEnumToModule4)
				ENABLEHOOK(RegisterVar)
				ENABLEHOOK(RegisterVar_01)
				ENABLEHOOK(RegisterVar_02)
				//ENABLEHOOK(RegisterVar_03)
				ENABLEHOOK(RegisterVarArray)
				ENABLEHOOK(DeclareEntityClass)

			}//if enableCreateModuleHook
		}//CreateHooks
	}//Hooks_CreateModule
}//namespace IHHook