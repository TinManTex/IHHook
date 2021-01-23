#pragma once

namespace IHHook {
	namespace IHMenu {
		void AddMenuCommands();
		void MenuMessage(const char* cmd, const char* message);

		void DrawMenu();

		void QueueMessageIn(std::string message);

		extern std::queue<std::string> messagesIn;

		extern std::mutex inMutex;
	}//namespace IHMenu
}//IHHook