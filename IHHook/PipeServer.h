#pragma once

#include <string>
#include "SafeQueue.h"

namespace IHHook {
	namespace PipeServer {
		static const std::wstring pipeInName = L"\\\\.\\pipe\\mgsv_in";
		static const std::wstring pipeOutName = L"\\\\.\\pipe\\mgsv_out";

		void StartPipeServer();
		void ShutDownPipeServer();
		void QueueMessageOut(std::string message);

		extern SafeQueue<std::string> messagesOut;
		extern SafeQueue<std::string> messagesIn;
	}//namespace PipeServer
}//namespace IHHook