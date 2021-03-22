#pragma once
#include "SafeQueue.h"

namespace IHHook {
	namespace IHMenu {
		void AddMenuCommands();
		void ProcessMessages();

		void SetInitialText();
		void DrawMenu(bool* p_open, bool openPrev);

		void QueueMessageOut(std::string message);
		void QueueMessageIn(std::string message);

		extern SafeQueue<std::string> messagesOut;
		extern SafeQueue<std::string> messagesIn;
	}//namespace IHMenu
}//IHHook