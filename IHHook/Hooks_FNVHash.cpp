#include "Hooks_FnvHash.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//BaseAddr,enableCityHook
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"

namespace IHHook {
	namespace Hooks_FNVHash {
		std::wstring logName = L"fnvhash_log.txt";
		std::shared_ptr<spdlog::logger> log;

		unsigned __int32 FNVHash32Hook(const char* str) {
			log->info(str);
			return FNVHash32(str);
		}//FNVHash32Hook

		void CreateHooks() {
			spdlog::debug(__func__);

			if (!config.enableFnvHook) {
				spdlog::debug("!enableFnvHook, returning");
				return;
			}

			log = spdlog::basic_logger_st("fnvhash", logName);
			log->set_pattern("%v");//tex raw logging

			if (!HasFunctionAddress("FNVHash32")) {
				spdlog::warn("FNVHash32 == NULL");
				return;
			}

			CREATE_HOOK(FNVHash32, FNVHash32Hook);

			ENABLE_HOOK(FNVHash32);
		}//CreateHooks
	}//Hooks_FNVHash
}//namespace IHHook