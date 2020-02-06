#pragma once

#include <string>
#include <queue>
#include <mutex>

namespace IHHook {
	void StartPipeServer();
	void QueueMessageOut(std::string message);
	extern std::queue<std::string> messagesIn;
	extern std::mutex inMutex;
}//namespace IHHook