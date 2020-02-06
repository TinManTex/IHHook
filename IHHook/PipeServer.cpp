#include "stdafx.h"
#include <strsafe.h>
#include "spdlog/spdlog.h"
#include "IHHook.h"
#include <queue>
#include <mutex>

namespace IHHook {
	//tex: simplest way to allow lua access pipe due to threading
	std::queue<std::string> messagesOut;
	std::queue<std::string> messagesIn;
	
	std::mutex inMutex;
	std::mutex outMutex;

	void QueueMessageOut(std::string message) {
		std::unique_lock<std::mutex> outLock(outMutex);
		messagesOut.push(message);
	}//QueueMessageOut

	void QueueMessageIn(std::string message) {
		std::unique_lock<std::mutex> inLock(inMutex);
		messagesIn.push(message);
	}//QueueMessageIn


#define BUFSIZE 512
#define PSIZE 512

	DWORD WINAPI PipeServerThread(LPVOID lpvParam);
	DWORD WINAPI PipeInThread(LPVOID);
	DWORD WINAPI PipeOutThread(LPVOID);
	VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

	void StartPipeServer() {
		HANDLE hThread = hThread = NULL;
		DWORD  dwThreadId = 0;

		// Create a thread for this client. 
		hThread = CreateThread(
			NULL,              // no security attribute 
			0,                 // default stack size 
			PipeServerThread,    // thread proc
			0,    // thread parameter 
			0,                 // not suspended 
			&dwThreadId);      // returns thread ID 

		if (hThread == NULL) {
			spdlog::error("CreateThread failed, GLE={}.", GetLastError());
			return;
		}
		else CloseHandle(hThread);
	}//StartPipeServer

	//IN/SIDE: pipeInName,pipeOutName
	DWORD WINAPI PipeServerThread(LPVOID lpvParam) {
		DWORD  dwThreadId = 0;
		HANDLE hPipeIn = INVALID_HANDLE_VALUE;
		HANDLE hPipeOut = INVALID_HANDLE_VALUE;
		HANDLE hThread = NULL;
		LPCTSTR lpszPipenameIn = pipeInName.c_str();
		LPCTSTR lpszPipenameOut = pipeOutName.c_str();

		// The main loop creates an instance of the named pipe and 
		// then waits for a client to connect to it. When the client 
		// connects, a thread is created to handle communications 
		// with that client, and this loop is free to wait for the
		// next client connect request. It is an infinite loop.
		for (;;) {
			spdlog::info(L"Pipe Server: Creating pipe: {}", lpszPipenameIn);
			hPipeIn = CreateNamedPipe(
				lpszPipenameIn,           // pipe name 
				PIPE_ACCESS_INBOUND,      // read/write access 
				PIPE_TYPE_MESSAGE |       // message type pipe 
				PIPE_READMODE_MESSAGE |   // message-read mode 
				PIPE_WAIT,                // blocking mode 
				PIPE_UNLIMITED_INSTANCES, // max. instances  
				BUFSIZE,                  // output buffer size 
				BUFSIZE,                  // input buffer size 
				0,                        // client time-out 
				NULL);                    // default security attribute 

			if (hPipeIn == INVALID_HANDLE_VALUE) {
				spdlog::error("CreateNamedPipe PipeIn failed, GLE={}.", GetLastError());
				return -1;
			}

			spdlog::info(L"Pipe Server: Creating pipe: {}", lpszPipenameOut);
			hPipeOut = CreateNamedPipe(
				lpszPipenameOut,          // pipe name 
				PIPE_ACCESS_OUTBOUND,      // read/write access
				PIPE_TYPE_MESSAGE |       // message type pipe 
				PIPE_READMODE_MESSAGE |   // message-read mode 
				PIPE_WAIT,                // blocking mode 
				PIPE_UNLIMITED_INSTANCES, // max. instances  
				BUFSIZE,                  // output buffer size 
				BUFSIZE,                  // input buffer size 
				0,                        // client time-out 
				NULL);                    // default security attribute 

			if (hPipeOut == INVALID_HANDLE_VALUE) {
				spdlog::error("CreateNamedPipe PipeOut failed, GLE={}.", GetLastError());
				return -1;
			}

			// Wait for the client to connect; if it succeeds, 
			// the function returns a nonzero value. If the function
			// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 
			spdlog::info(L"Pipe Server: Main thread awaiting client connection on {}", lpszPipenameIn);
			bool fConnectedIn = ConnectNamedPipe(hPipeIn, NULL) ?
				TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

			spdlog::info(L"Pipe Server: Main thread awaiting client connection on {}", lpszPipenameOut);
			bool fConnectedOut = ConnectNamedPipe(hPipeOut, NULL) ?
				TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

			if (fConnectedIn && fConnectedOut) {
				spdlog::info("Pipe Server: Client connected, creating a processing thread.");

				// Create a thread for this client. 
				hThread = CreateThread(
					NULL,              // no security attribute 
					0,                 // default stack size 
					PipeInThread,    // thread proc
					hPipeIn,    // thread parameter 
					0,                 // not suspended 
					&dwThreadId);      // returns thread ID 

				if (hThread == NULL) {
					spdlog::error("CreateThread PipeInThread failed, GLE={}.", GetLastError());
					return -1;
				}
				else CloseHandle(hThread);

				// Create a thread for this client. 
				hThread = CreateThread(
					NULL,              // no security attribute 
					0,                 // default stack size 
					PipeOutThread,    // thread proc
					hPipeOut,    // thread parameter 
					0,                 // not suspended 
					&dwThreadId);      // returns thread ID 

				if (hThread == NULL) {
					spdlog::error("CreateThread PipeOutThread failed, GLE={}.", GetLastError());
					return -1;
				}
				else CloseHandle(hThread);
			}
			else {
				// The client could not connect, so close the pipe. 
				CloseHandle(hPipeIn);
				CloseHandle(hPipeOut);
			}//if fConnected
		}//for ;;

		return 1;
	}//PipeServerThread

	// This routine is a thread processing function to read from and reply to a client
	// via the open pipe connection passed from the main loop. Note this allows
	// the main loop to continue executing, potentially creating more threads of
	// of this procedure to run concurrently, depending on the number of incoming
	// client connections.
	DWORD WINAPI PipeOutThread(LPVOID lpvParam) {
		DWORD cbBytesRead = 0;
		DWORD cbWritten = 0;
		BOOL fSuccess = FALSE;
		HANDLE hPipeOut;

		// Do some extra error checking since the app will keep running even if this
		// thread fails.

		if (lpvParam == NULL) {
			spdlog::error("ERROR - Pipe Server Failure:");
			spdlog::error("   PipeOutThread got an unexpected NULL value in lpvParam.");
			spdlog::error("   PipeOutThread exitting.");
			return (DWORD)-1;
		}

		// Print verbose messages. In production code, this should be for debugging only.
		spdlog::info("PipeOutThread created, receiving and processing messages.");

		hPipeOut = (HANDLE)lpvParam;

		DWORD dwMode = PIPE_READMODE_MESSAGE;
		BOOL handleSuccess = SetNamedPipeHandleState(
			hPipeOut,  // pipe handle 
			&dwMode, // new pipe mode 
			NULL,   // don't set maximum bytes (only applies to client)
			NULL);  // don't set maximum time (only applies to client)

		//tex thread loop
		while (1) {
			if (!messagesOut.empty()) {//tex this is only a 'may prevent an unnessesary lock' rather than a thread safe check.
				std::unique_lock<std::mutex> outLock(outMutex);
				while (!messagesOut.empty()) {
					std::string message = messagesOut.front();
					messagesOut.pop();

					DWORD messageBytes = static_cast<DWORD>(message.size()) + sizeof('\0');;//tex: std string size() does not include a terminator but c_str() does

					fSuccess = WriteFile(hPipeOut, message.c_str(), messageBytes, &cbWritten, NULL);

					if (!fSuccess || messageBytes != cbWritten) {
						spdlog::warn("PipeOutThread WriteFile failed, GLE={}, fSuccess={}, messageBytes={}, cbWritten={}.", GetLastError(), fSuccess, messageBytes, cbWritten);
						break;//tex DEBUGNOW think this through 
					}
					FlushFileBuffers(hPipeOut);
				}//while messagesout
				
			}//if messagesout
		}//loop while

		FlushFileBuffers(hPipeOut);
		DisconnectNamedPipe(hPipeOut);
		CloseHandle(hPipeOut);

		spdlog::info("PipeOutThread exiting.");
		return 1;
	}//PipeOutThread

	//tex just processes In pipe
	DWORD WINAPI PipeInThread(LPVOID lpvParam) {
		HANDLE hHeap = GetProcessHeap();
		CHAR* pchRequest = (CHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(CHAR));

		DWORD cbBytesRead = 0;
		DWORD cbReplyBytes = 0;
		DWORD cbWritten = 0;

		LPDWORD lpTotalBytesAvail = 0;
		LPDWORD lpBytesLeftThisMessage = 0;

		BOOL fSuccess = FALSE;
		HANDLE hPipeIn;


		// Do some extra error checking since the app will keep running even if this
		// thread fails.

		if (lpvParam == NULL) {
			spdlog::error("ERROR - Pipe Server Failure:");
			spdlog::error("   PipeInThread got an unexpected NULL value in lpvParam.");
			spdlog::error("   PipeInThread exitting.");
			if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
			return (DWORD)-1;
		}

		if (pchRequest == NULL) {
			spdlog::error("ERROR - Pipe Server Failure:");
			spdlog::error("   PipeInThread got an unexpected NULL heap allocation.");
			spdlog::error("   PipeInThread exitting.");
			return (DWORD)-1;
		}

		// Print verbose messages. In production code, this should be for debugging only.
		spdlog::info("PipeInThread created, receiving and processing messages.");

		hPipeIn = (HANDLE)lpvParam;

		DWORD dwMode = PIPE_READMODE_MESSAGE;
		BOOL handleSuccess = SetNamedPipeHandleState(
			hPipeIn,  // pipe handle 
			&dwMode, // new pipe mode 
			NULL,   // don't set maximum bytes (only applies to client)
			NULL);  // don't set maximum time (only applies to client)

		while (1) {
			/*//DEBUG
			fSuccess = PeekNamedPipe(
				hPipeIn,        // handle to pipe 
				pchRequest,    // buffer to receive data 
				BUFSIZE * sizeof(TCHAR), // size of buffer 
				&cbBytesRead, // number of bytes read 
				lpTotalBytesAvail,
				lpBytesLeftThisMessage);
				*/

			// Read client requests from the pipe. This simplistic code only allows messages up to BUFSIZE characters in length.
			fSuccess = ReadFile(
				hPipeIn,        // handle to pipe 
				pchRequest,    // buffer to receive data 
				BUFSIZE * sizeof(TCHAR), // size of buffer 
				&cbBytesRead, // number of bytes read 
				NULL);        // not overlapped I/O 

			if (!fSuccess /*|| cbBytesRead == 0*/) {//DEBUGNOW
				if (GetLastError() == ERROR_BROKEN_PIPE) {
					spdlog::warn("PipeInThread: client disconnected.");
					break;
				} else {
					spdlog::error("PipeInThread ReadFile failed, GLE={}.", GetLastError());
					break;
				}
			} else {
				std::string message;
				message.insert(message.end(), pchRequest, pchRequest + cbBytesRead);
				spdlog::trace("Client Request String:\"{}\"", message);
				QueueMessageIn(message);
			}//if fSuccess
		}//loop while

		DisconnectNamedPipe(hPipeIn);
		CloseHandle(hPipeIn);

		HeapFree(hHeap, 0, pchRequest);

		spdlog::info("PipeInThread exiting.");
		return 1;
	}//PipeInThread
}//namespace IHHoook
