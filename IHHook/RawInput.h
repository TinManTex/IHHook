#pragma once
#include "windowsapi.h"

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

		bool OnMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//		
		void BlockAll();
		void UnBlockAll();
		void BlockMouseClick(); 
		void UnBlockMouseClick();
		void BlockKeyboard();
		void UnBlockKeyboard();
	}//namespace RawInput
}//namespace IHHook