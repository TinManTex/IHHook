//tex WIP exploring
#include "Hooks_LoadFile.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//BaseAddr,enableCityHook
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	extern std::shared_ptr<spdlog::logger> luaLog;

	namespace Hooks_LoadFile {
		std::wstring logName = L"loadfile_log.txt";
		std::shared_ptr<spdlog::logger> log;

		uint64_t * LoadFileHook(uint64_t* fileSlotIndex, uint64_t filePath64) {
			if (config.enableFnvHook) {
				log->info(filePath64);
			}

			return LoadFile(fileSlotIndex, filePath64);
		}//LoadFileHook		

		//ZIP: LoadFile_0*
		uint64_t * LoadFile_01Hook(uint64_t * param_1, uint64_t * param_2) { return LoadFile_01(param_1, param_2); }//LoadFile_01Hook
		void LoadFile_02Hook(uint64_t* param_1) { return LoadFile_02(param_1); }//LoadFile_03Hook
		uint64_t * LoadFile_03Hook() { return LoadFile_03(); }//LoadFile_03Hook
		uint64_t * LoadFile_05Hook(uint64_t* param_1, uint64_t* param_2) { return LoadFile_05(param_1, param_2); }//LoadFile_05Hook
		//ZIP: LoadFile_0*

		//TODO: move somewhere else
		//UNUSED, only interesting for specific logging, but cityhash hook will catch everything otherwise
		/*uint64_t PathCode64Hook(const char* path) {
			uint64_t hash = PathCode64(path);
			return hash;
		}*/

		void LoadFileSubHook(ulonglong filePath64, ulonglong filePath64_01) {
			if (config.logFileLoad) {
				log->info(filePath64);
				log->info(filePath64_01);
			}

			return LoadFileSub(filePath64, filePath64_01);
		}//LoadFileSubHook

		void CreateHooks() {
			spdlog::debug("Hooks_LoadFile::CreateHooks");			

			if (config.logFileLoad) {//DEBUGNOW
				log = spdlog::basic_logger_st("loadfile", logName);
				log->set_pattern("%v");//tex raw logging
					
				CREATE_HOOK(LoadFileSub)
				CREATE_HOOK(LoadFile)

				//ZIP: LoadFile_0*
				CREATE_HOOK(LoadFile_01)
				CREATE_HOOK(LoadFile_02)
				CREATE_HOOK(LoadFile_03) 
				CREATE_HOOK(LoadFile_05)
				//ZIP: LoadFile_0*
					
				ENABLEHOOK(LoadFileSub)
				//ENABLEHOOK(LoadFile)

				//ZIP: LoadFile_0*
				//ENABLEHOOK(LoadFile_01)
				//ENABLEHOOK(LoadFile_02)
				//ENABLEHOOK(LoadFile_03)
				//ENABLEHOOK(LoadFile_05)
				//ZIP: LoadFile_0*
			}

			//CREATE_HOOK(PathCode64)

			//ENABLEHOOK(PathCode64)
		}//CreateHooks
	}//Hooks_FNVHash
}//namespace IHHook