#pragma once
#include "stdafx.h"

namespace IHHook {
	void InitializeInput();
	void HookWndProc(HWND hWnd);
}//namespace IHHook