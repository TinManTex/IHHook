#include "Hooks_TPP.h"
#include "IHHook.h"//BaseAddr
#include "spdlog/spdlog.h"

#include "MinHook/MinHook.h"
#include "HookMacros.h"

namespace IHHook {
	namespace Hooks_TPP {
		uintptr_t missionCode_Addr = 0x142A58A00;
		//uint32_t* missionCode;//tex in header

		HOOKFUNC(void, UnkSomePlayerUpdateFunc, uintptr_t unkPlayerClass, uintptr_t playerIndex)
		HOOKPTR(UnkSomePlayerUpdateFunc, 0x146e3a620)
		
		void UnkSomePlayerUpdateFuncHook(intptr_t unkPlayerClass, uintptr_t playerIndex) {
			spdlog::trace(__func__);
			UnkSomePlayerUpdateFunc(unkPlayerClass, playerIndex);

			intptr_t playerClass = unkPlayerClass;
			
		}//UnkSomePlayerUpdateFuncHook

		void CreateHooks(size_t RealBaseAddr) {
			//DEBUGNOW hitting some kind of exception on caps machine
			missionCode = NULL;
			try {
				missionCode = (uint32_t*)((missionCode_Addr - BaseAddr) + RealBaseAddr);
			}
			catch (std::runtime_error & e) {
				spdlog::error("CHP: runtime exception - {}", e.what());
				auto log = spdlog::get("ihhook");
				log->flush();
			}
			if (missionCode==NULL) {
				spdlog::error("CHP: missionCode==NULL");
			}

			//DEBUGNOW
			//CREATEDETOURB(UnkSomeUpdateFunc)
			//ENABLEHOOK(UnkSomeUpdateFunc)
		}//CreateHooks
	}//Hooks_TPP
}//namespace IHHook