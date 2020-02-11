#include "Hooks_TPP.h"
#include "IHHook.h"//BaseAddr
#include "spdlog/spdlog.h"

namespace IHHook {
	extern void* RebasePointer(const size_t address);

	namespace Hooks_TPP {
		uintptr_t missionCode_Addr = 0x142A58A00;
		//uint32_t* missionCode;//tex in header

		void CreateHooks(size_t RealBaseAddr) {
			//DEBUGNOW hitting some kind of exception on caps machine
			missionCode = NULL;
			try {
				missionCode = (uint32_t*)((missionCode_Addr - BaseAddr) + RealBaseAddr);;
			}
			catch (std::runtime_error & e) {
				spdlog::error("CHP: runtime exception - {}", e.what());
				auto log = spdlog::get("ihhook");
				log->flush();
			}
			if (missionCode==NULL) {
				spdlog::error("CHP: missionCode==NULL");
			}

		}//CreateHooks
	}//Hooks_TPP
}//namespace IHHook