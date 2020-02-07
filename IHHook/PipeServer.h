#pragma once

#include <string>
#include <queue>
#include <mutex>

namespace IHHook {
	namespace PipeServer {
		void StartPipeServer();
		void QueueMessageOut(std::string message);

		extern std::queue<std::string> messagesOut;
		extern std::queue<std::string> messagesIn;

		extern std::mutex inMutex;
		extern std::mutex outMutex;
	}//namespace PipeServer
}//namespace IHHook