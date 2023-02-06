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
		//TODO: move somewhere else
		//UNUSED, only interesting for specific logging, but cityhash hook will catch everything otherwise
		/*uint64_t PathCode64Hook(const char* path) {
			uint64_t hash = PathCode64(path);
			return hash;
		}*/
		//tex LoadFile Actual, the other LoadFile* functions call this, so it's the only one I'm logging at the moment
		void LoadFileSubHook(PathCode64 filePath64, PathCode64 filePath64_01) {
			if (config.logFileLoad) {
				log->info(filePath64);
				log->info(filePath64_01);
				log->info("");
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

				ENABLEHOOK(LoadFileSub)
				//ENABLEHOOK(LoadFile)
			}

			//CREATE_HOOK(PathCode64)

			//ENABLEHOOK(PathCode64)
		}//CreateHooks
	}//Hooks_FNVHash
}//namespace IHHook