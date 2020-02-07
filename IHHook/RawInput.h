#pragma once
#include "stdafx.h"

namespace IHHook {
	namespace RawInput {
		void InitializeInput();
		void HookWndProc(HWND hWnd);
	}//namespace RawInput
}//namespace IHHook