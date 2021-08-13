#include "Hooks_FnvHash.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//BaseAddr,enableCityHook
#include "MinHook/MinHook.h"
#include "HookMacros.h"

namespace IHHook {
	namespace Hooks_FNVHash {
		std::wstring logName = L"fnvhash_log.txt";
		std::shared_ptr<spdlog::logger> log;

		FUNCPTRDEF(unsigned __int32, FNVHash32, char* str)
		FUNC_DECL_ADDR(FNVHash32)

		unsigned __int32 FNVHash32Hook(char* str) {
			log->info(str);
			return FNVHash32(str);
		}//FNVHash32Hook

		void CreateHooks(size_t RealBaseAddr) {
			spdlog::debug(__func__);

			if (!enableFnvHook) {
				spdlog::debug("!enableFnvHook, returning");
				return;
			}

			log = spdlog::basic_logger_st("fnvhash", logName);
			log->set_pattern("%v");//tex raw logging

			if (isTargetExe) {
				GET_REBASED_ADDR(FNVHash32)		
			}
			else {
				//GET_SIG_ADDR(FNVHash32)//TODO sigs	
			}

			if (FNVHash32Addr == NULL) {
				spdlog::warn("FNVHash32 == NULL");
				return;
			}

			CREATE_HOOK(FNVHash32)

			ENABLEHOOK(FNVHash32)
		}//CreateHooks
	}//Hooks_FNVHash
}//namespace IHHook