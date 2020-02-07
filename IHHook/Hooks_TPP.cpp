#include "IHHook.h"
#include "spdlog/spdlog.h"

namespace IHHook {
	extern void* RebasePointer(const size_t address);

	uintptr_t missionCode_Addr = 0x142A58A00;
	uint32_t* missionCode;

	void CreateHooks_TPP(size_t RealBaseAddr) {		
		//DEBUGNOW hitting some kind of exception on caps machine
		try {
			missionCode = (uint32_t*)((missionCode_Addr - BaseAddr) + RealBaseAddr);;
		}
		catch (std::runtime_error & e) {
			spdlog::error("CHP: runtime exception - {}", e.what());
			auto log = spdlog::get("ihhook");
			log->flush();
		}

	}//CreateHooks_TPP
}//namespace IHHook