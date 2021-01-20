//tex MGSV seems to use raw input for mouse and keyboard
//REF https://docs.microsoft.com/en-us/windows/win32/inputdev/using-raw-input
//By intercepting this we can not only give IHHook a method of input but could also selectively block input to the game.

//DEBUGNOW this only really gets you OnKeyDown, OnKeyUp reliably as Held will be limited by key repeat rate
//the solution there would be to have another state array and have the input events set up,down and querry that with the assumption that down is held

#include "RawInput.h"
#include "spdlog/spdlog.h"
#include "IHHook.h"

namespace IHHook {
	namespace RawInput {
		const int vKeyMax = 256;//tex: virtual keycode max (VK_OEM_CLEAR      0xFE)
		USHORT currFlags[vKeyMax];//tex: indexed by Virtual Keycode
		bool ignore[vKeyMax] = { false };//tex: don't process key, set up in InitIgnoreKeys
		bool blockGameKeys[vKeyMax] = { false };//tex: block game from recieving message
		std::list<ButtonAction>* buttonActions[vKeyMax] = { NULL };

		void BlockMouseClick() {
			blockGameKeys[VK_LBUTTON] = true;
		}//BlockMouseClick

		void UnBlockMouseClick() {
			blockGameKeys[VK_LBUTTON] = false;
		}//UnBlockMouseClick

		void BlockAll() {
			for (int i = 0; i > vKeyMax; i++) {
				blockGameKeys[i] = true;
			}
		}//BlockAll

		void UnBlockAll() {
			for (int i = 0; i > vKeyMax; i++) {
				blockGameKeys[i] = false;
			}
		}//UnBlockAll

		void DoActions(USHORT vKey, RawInput::BUTTONEVENT buttonEvent);


		void ProcessKey(PRAWINPUT pRaw) {
			//spdlog::trace("ProcessKey");//DEBUGNOW
			USHORT vKey = pRaw->data.keyboard.VKey;
			USHORT flags = pRaw->data.keyboard.Flags;
			USHORT oldFlags = currFlags[vKey];

			BUTTONEVENT buttonEvent = BUTTONEVENT::UP;
			if (flags == RI_KEY_MAKE && oldFlags == RI_KEY_BREAK) {//OnKeyDown
				buttonEvent = BUTTONEVENT::ONDOWN;
			}
			else if (flags == RI_KEY_BREAK && oldFlags == RI_KEY_MAKE) {//OnKeyUp
				buttonEvent = BUTTONEVENT::ONUP;
			}
			else if (flags == RI_KEY_MAKE && oldFlags == RI_KEY_MAKE) {//Held
				buttonEvent = BUTTONEVENT::HELD;
			}
			//else up, which you shouldnt hit

			currFlags[vKey] = flags;

			DoActions(vKey, buttonEvent);

#ifdef _DEBUG
			//WCHAR wcTextBuffer[512];
			//UINT keyChar = MapVirtualKey(pRaw->data.keyboard.VKey, MAPVK_VK_TO_CHAR);

			//wsprintf(wcTextBuffer,
			//	TEXT("Type=%d\nDevice=0x%x\nMakeCode=0x%x\nFlags=0x%x\nReserved=0x%x\nExtraInformation=0x%x\nMessage=0x%x\nVKey=0x%x\nEvent=0x%x\nkeyChar=0x%x\n\n"),
			//	/// device header
			//	pRaw->header.dwType,
			//	// device handle, pass this to GetRawInputDeviceInfo
			//	pRaw->header.hDevice,

			//	pRaw->data.keyboard.MakeCode,
			//	pRaw->data.keyboard.Flags,
			//	pRaw->data.keyboard.Reserved,
			//	pRaw->data.keyboard.ExtraInformation,
			//	pRaw->data.keyboard.Message,
			//	pRaw->data.keyboard.VKey,
			//	keyChar);

			//wprintf(wcTextBuffer);
#endif // _DEBUG
		}//ProcessRawInput

		//tex helper to process usButtonFlags
		struct {
			UINT vk;		UINT downflag;					UINT upflag;
		} const k[] = {
			{ VK_LBUTTON,   RI_MOUSE_LEFT_BUTTON_DOWN,		RI_MOUSE_LEFT_BUTTON_UP },
			{ VK_RBUTTON,   RI_MOUSE_RIGHT_BUTTON_DOWN,		RI_MOUSE_RIGHT_BUTTON_UP },
			{ VK_MBUTTON,	RI_MOUSE_MIDDLE_BUTTON_DOWN,	RI_MOUSE_MIDDLE_BUTTON_UP },
			{ VK_XBUTTON1,	RI_MOUSE_BUTTON_4_DOWN,			RI_MOUSE_BUTTON_4_UP },
			{ VK_XBUTTON2,	RI_MOUSE_BUTTON_5_DOWN,			RI_MOUSE_BUTTON_4_UP }
		};

		bool ProcessMouseButtons(PRAWINPUT pRaw) {
			USHORT usButtonFlags = pRaw->data.mouse.usButtonFlags;

			const int numButtons = _countof(k);

			//tex jump through a few hoops to make it similar to ProcessKey
			USHORT oldFlagsB[vKeyMax];
			for (UINT i = 0; i < numButtons; ++i) {
				USHORT vKey = k[i].vk;
				oldFlagsB[vKey] = currFlags[vKey];
			}

			for (UINT i = 0; i < numButtons; ++i) {
				USHORT vKey = k[i].vk;
				if (usButtonFlags & k[i].downflag) {
					currFlags[vKey] = RI_KEY_MAKE;
				}
				//DEBUGNOW not hitting for some reason
				if (usButtonFlags & k[i].upflag) {
					currFlags[vKey] = RI_KEY_BREAK;
				}
			}
			//

			for (UINT i = 0; i < numButtons; ++i) {
				USHORT vKey = k[i].vk;
				USHORT flags = currFlags[vKey];
				USHORT oldFlags = oldFlagsB[vKey];

				BUTTONEVENT buttonEvent = BUTTONEVENT::UP;
				if (flags == RI_KEY_MAKE && oldFlags == RI_KEY_BREAK) {
					buttonEvent = BUTTONEVENT::ONDOWN;
				}
				else if (flags == RI_KEY_BREAK && oldFlags == RI_KEY_MAKE) {
					buttonEvent = BUTTONEVENT::ONUP;
				}
				else if (flags == RI_KEY_MAKE && oldFlags == RI_KEY_MAKE) {
					buttonEvent = BUTTONEVENT::HELD;
				}

				if (blockGameKeys[vKey]) {
					return false;
				}

				if (!ignore[vKey]) {
					DoActions(vKey, buttonEvent);
				}
			}//for numbuttons

#ifdef _DEBUG
		//WCHAR wcTextBuffer[512];

		//wsprintf(wcTextBuffer,
		//	TEXT("Type=%d\nDevice=0x%x\nulButtons=0x%x\nulRawButtons=0x%x\nusButtonData=0x%x\nusButtonFlags=0x%x\nusFlags=0x%x\nlLastX=0x%x\nlLastY=0x%x\n\n"),
		//	pRaw->header.dwType,
		//	pRaw->header.hDevice,

		//	pRaw->data.mouse.ulButtons,
		//	pRaw->data.mouse.ulRawButtons,
		//	pRaw->data.mouse.usButtonData,
		//	pRaw->data.mouse.usButtonFlags,
		//	pRaw->data.mouse.usFlags,
		//	pRaw->data.mouse.lLastX,
		//	pRaw->data.mouse.lLastY);

		//wprintf(wcTextBuffer);
#endif // _DEBUG
			return true;
		}//ProcessMouseButtons

		//IN/SIDE: buttonActions
		void DoActions(USHORT vKey, RawInput::BUTTONEVENT buttonEvent) {
			std::list<ButtonAction>* actions = buttonActions[vKey];
			if (actions != NULL) {
				spdlog::debug("RawInput DoActions for vKey:{}", vKey);
				for (std::list<ButtonAction>::iterator it = actions->begin(); it != actions->end(); ++it) {
					ButtonAction Action = *it;
					Action(buttonEvent);
				}
			}
		}//DoActions


		void RegisterAction(USHORT vKey, ButtonAction action) {
			assert(vKey > 0 && vKey < vKeyMax);
			spdlog::debug("RawInput RegisterAction for vKey:{}", vKey);
			if (buttonActions[vKey] == NULL) {
				buttonActions[vKey] = new std::list<ButtonAction>();
			}

			buttonActions[vKey]->push_back(action);
		}//RegisterAction

		void UnRegisterAction(USHORT vKey, ButtonAction buttonAction) {
			if (buttonActions[vKey] == NULL) {
				spdlog::warn("RawInput UnRegisterAction: No actions for vKey {}", vKey);
				return;
			}

			//for vkey actions
			//remove action

			//if actions empty
			//delete buttonActions[vKey]
			//buttonActions[vKey] = NULL;
		}//UnRegisterAction

		//DEBUG
		void TestAction(BUTTONEVENT buttonEvent) {
			spdlog::debug("ButtonEvent: {:d}, Action: TestAction", buttonEvent);
			if (buttonEvent == BUTTONEVENT::ONDOWN) {
				spdlog::debug("TestAction on ONDOWN");
			}
			else if (buttonEvent == BUTTONEVENT::ONUP) {
				spdlog::debug("TestAction on ONUP");
			}
			else  if (buttonEvent == BUTTONEVENT::HELD) {
				spdlog::debug("TestAction on HELD");
			}
		}//TestAction

		//DEBUGNOW
		void ToggleUI(RawInput::BUTTONEVENT buttonEvent) {
			spdlog::debug("ButtonEvent: {:d}, Action: ToggleUI", buttonEvent);
			if (buttonEvent == RawInput::BUTTONEVENT::ONDOWN) {
				spdlog::debug("ToggleUI on ONDOWN");
				g_ihhook->ToggleDrawUI();//DEBUGNOW
			}
			else if (buttonEvent == RawInput::BUTTONEVENT::ONUP) {
				spdlog::debug("ToggleUI on ONUP");
			}
			else  if (buttonEvent == RawInput::BUTTONEVENT::HELD) {
				spdlog::debug("ToggleUI on HELD");
			}
		}//ToggleUI

		//tex: don't process key
		void InitIgnoreKeys() {
			ignore[VK_KANA] = true;
			ignore[VK_HANGEUL] = true;
			ignore[VK_HANGUL] = true;
			ignore[VK_JUNJA] = true;
			ignore[VK_FINAL] = true;
			ignore[VK_HANJA] = true;
			ignore[VK_KANJI] = true;
			ignore[VK_CONVERT] = true;
			ignore[VK_NONCONVERT] = true;
			ignore[VK_ACCEPT] = true;
			ignore[VK_MODECHANGE] = true;

			ignore[VK_SLEEP] = true;
			ignore[VK_NAVIGATION_VIEW] = true;
			ignore[VK_NAVIGATION_MENU] = true;
			ignore[VK_NAVIGATION_UP] = true;
			ignore[VK_NAVIGATION_DOWN] = true;
			ignore[VK_NAVIGATION_LEFT] = true;
			ignore[VK_NAVIGATION_RIGHT] = true;
			ignore[VK_NAVIGATION_ACCEPT] = true;
			ignore[VK_NAVIGATION_CANCEL] = true;

			ignore[VK_OEM_NEC_EQUAL] = true;


			ignore[VK_OEM_FJ_JISHO] = true;
			ignore[VK_OEM_FJ_MASSHOU] = true;
			ignore[VK_OEM_FJ_TOUROKU] = true;
			ignore[VK_OEM_FJ_LOYA] = true;
			ignore[VK_OEM_FJ_ROYA] = true;

			ignore[VK_OEM_AX] = true;
			ignore[VK_OEM_102] = true;
			ignore[VK_ICO_HELP] = true;
			ignore[VK_ICO_00] = true;

			ignore[VK_PROCESSKEY] = true;
			ignore[VK_ICO_CLEAR] = true;
			ignore[VK_PACKET] = true;

			ignore[VK_OEM_RESET] = true;
			ignore[VK_OEM_JUMP] = true;
			ignore[VK_OEM_PA1] = true;
			ignore[VK_OEM_PA2] = true;
			ignore[VK_OEM_PA3] = true;
			ignore[VK_OEM_WSCTRL] = true;
			ignore[VK_OEM_CUSEL] = true;
			ignore[VK_OEM_ATTN] = true;
			ignore[VK_OEM_FINISH] = true;
			ignore[VK_OEM_COPY] = true;
			ignore[VK_OEM_AUTO] = true;
			ignore[VK_OEM_ENLW] = true;
			ignore[VK_OEM_BACKTAB] = true;

			ignore[VK_ATTN] = true;
			ignore[VK_CRSEL] = true;
			ignore[VK_EXSEL] = true;
			ignore[VK_EREOF] = true;
			ignore[VK_PLAY] = true;
			ignore[VK_ZOOM] = true;
			ignore[VK_NONAME] = true;
			ignore[VK_PA1] = true;
			ignore[VK_OEM_CLEAR] = true;
		}//InitIgnoreKeys

		void InitializeInput() {
			spdlog::debug("Rawinput InitializeInput");

			std::fill_n(currFlags, vKeyMax, RI_KEY_BREAK);

			InitIgnoreKeys();

			//RegisterAction(VK_F1, TestAction);//DEBUG
			RegisterAction(VK_F1, ToggleUI);//DEBUGNOW

			//block[VK_LBUTTON] = true;//DEBUGNOW
			//block[VK_SPACE] = true;//DEBUGNOW
		}//InitializeInput

		//CULL not needed, the game will have set up it's own
		//Could use it to allow funky controllers though
		void InitializeRawInputDevices() {
			RAWINPUTDEVICE Rid[2];

			Rid[0].usUsagePage = 0x01;
			Rid[0].usUsage = 0x02;
			//DEBUGNOW Rid[0].dwFlags = RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
			Rid[0].hwndTarget = 0;

			Rid[1].usUsagePage = 0x01;
			Rid[1].usUsage = 0x06;
			//DEBUGNOW Rid[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
			Rid[1].hwndTarget = 0;

			if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
				spdlog::warn("register raw input devices failed {}", GetLastError());
			}

		}//InitializeRawInput

		bool OnMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
			switch (uMsg) {
			case WM_INPUT:
			{
				// wParam is either RIM_INPUT (this app foreground) or RIM_INPUTSINK (this app background)
				// lParam is the RAWINPUT handle

				UINT dwSize;

				// determine size of buffer
				if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER)) == -1) {
					break;
				}

				LPBYTE lpb = new BYTE[dwSize];
				if (lpb == NULL) {
					break;
				}
				ZeroMemory(lpb, dwSize);

				// get actual data
				if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
					delete[] lpb;
					break;
				}

				// process it
				PRAWINPUT pRaw = (PRAWINPUT)lpb;
				if (pRaw->header.dwType == RIM_TYPEKEYBOARD) {
					USHORT vKey = pRaw->data.keyboard.VKey;
					if (blockGameKeys[vKey]) {
						return false;
					}

					if (!ignore[vKey]) {
						ProcessKey(pRaw);
					}
				}
				else if (pRaw->header.dwType == RIM_TYPEMOUSE) {
					if (!ProcessMouseButtons(pRaw)) {
						return false;
					}
				}

				// not needed
				delete[] lpb;
				break;
			}//case WM_INPUT
			}//switch uMsg

			return true;
		}

		//
		WNDPROC WndProc_Orig = NULL;

		LRESULT CALLBACK WndProc_Hook(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			if (!OnMessage(hwnd, uMsg, wParam, lParam)) {
				return -1L;
			}

			return CallWindowProc(WndProc_Orig, hwnd, uMsg, wParam, lParam);
		}//WndProc_Hook

		void HookWndProc(HWND hWnd) {
			//Redirect WndProc for hWnd
			WndProc_Orig = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc_Hook);
		}
	}//namespace RawInput
}//namespace IHHook