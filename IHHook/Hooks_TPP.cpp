#include "IHHook.h"

namespace IHHook {
	int* missionCode = (int*)0x142A58A00;

	void CreateHooks_TPP() {
		missionCode = (int*)RebasePointer((size_t)missionCode);

	}//CreateHooks_TPP

}//namespace IHHook