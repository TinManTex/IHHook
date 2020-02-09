#pragma once
#include "stdafx.h"

namespace IHHook {
	namespace RawInput {
		enum BUTTONEVENT {
			UP,
			ONDOWN,
			ONUP,
			HELD
		};

		typedef void(*ButtonAction) (BUTTONEVENT buttonEvent);

		void InitializeInput();
		void HookWndProc(HWND hWnd);

		void RegisterAction(USHORT vKey, ButtonAction action);
	}//namespace RawInput
}//namespace IHHook