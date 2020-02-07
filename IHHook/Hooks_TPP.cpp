#include "IHHook.h"
#include "spdlog/spdlog.h"

namespace IHHook {
	extern void* RebasePointer(const size_t address);

	int* missionCode = (int*)0x142A58A00;

	void CreateHooks_TPP() {
		//DEBUGNOW hitting some kind of exception on caps machine
		try {
			missionCode = (int*)RebasePointer((size_t)missionCode);
		}
		catch (std::runtime_error & e) {
			spdlog::error("CHP: runtime exception - {}", e.what());
			auto log = spdlog::get("ihhook");
			log->flush();
		}

	}//CreateHooks_TPP

}//namespace IHHook