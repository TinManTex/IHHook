#include "PipeServer.h"

#include <aclapi.h>//security access
#include <strsafe.h>
#include "spdlog/spdlog.h"
#include <string>
#include <optional>

namespace IHHook {
	namespace PipeServer {
		//tex: simplest way to allow lua access pipe due to threading
		SafeQueue<std::string> messagesOut;
		SafeQueue<std::string> messagesIn;

		void QueueMessageOut(std::string message) {
			//DEBUGNOW only add if pipe connected (but at moment we have no way of tracking since pipeserverthread is hands off as far as launching a pipe
			messagesOut.push(message);
		}//QueueMessageOut

		void QueueMessageIn(std::string message) {
			messagesIn.push(message);
		}//QueueMessageIn


#define BUFSIZE 512
#define PSIZE 512

		DWORD WINAPI PipeServerThread(LPVOID lpvParam);
		DWORD WINAPI PipeInThread(LPVOID);
		DWORD WINAPI PipeOutThread(LPVOID);
		VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

		//tex DEBUGNOW move to util
		const char* GetLastErrorString(int err) {
			static char errbuff[256];
			int sz;
			if (err == 0) {
				err = GetLastError();
			}
			sz = FormatMessageA(//tex was FormatMessage
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, err,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				errbuff, 256, NULL
			);
			if (sz > 2) {//KLUDGE
				errbuff[sz - 2] = '\0'; // strip the \r\n
			}
			return errbuff;
		}//GetLastErrorString

		void StartPipeServer() {
			HANDLE hThread = hThread = NULL;
			DWORD  dwThreadId = 0;

			// start a thread, that starts threads 
			hThread = CreateThread(
				nullptr,			// no security attribute 
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
				//tex security attribute, 
				//only defined this to try and get around namedpipe client needs InOut even for server out/readonly pipe, but I suppose having it defined rather than using default is better
				//ultimately just want this for the pipe, but cant hide it away in a function because stuff created on the function stack would be trashed (and figuring out which is is too much pain for the moment)
				SECURITY_ATTRIBUTES sa;
				//TODO log errors and return instead of throwing exception
				PSID pEveryoneSID = NULL;
				PSID pAdminSID = NULL;
				PACL pACL = NULL;
				EXPLICIT_ACCESS ea[2];
				SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
				SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
				//SCOPE_GUARD{//DEBUGNOW
					if (pEveryoneSID) { FreeSid(pEveryoneSID); }
					if (pAdminSID) { FreeSid(pAdminSID); }
					if (pACL) { LocalFree(pACL); }
				//};

				// Create a well-known SID for the Everyone group.
				if (!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pEveryoneSID)) {
					throw std::runtime_error("AllocateAndInitializeSid failed, GLE=" + std::to_string(GetLastError()));
				}
				// Initialize an EXPLICIT_ACCESS structure for an ACE.
				SecureZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
				// The ACE will allow Everyone full access to the key.
				ea[0].grfAccessPermissions = FILE_ALL_ACCESS | GENERIC_WRITE | GENERIC_READ;
				ea[0].grfAccessMode = SET_ACCESS;
				ea[0].grfInheritance = 0x0; //NO_INHERITANCE;
				ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
				ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
				ea[0].Trustee.ptstrName = (LPTSTR)pEveryoneSID;

				// Create a SID for the BUILTIN\Administrators group.
				if (!AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdminSID)) {
					throw std::runtime_error("AllocateAndInitializeSid failed, GLE=" + std::to_string(GetLastError()));
				}
				// The ACE will allow the Administrators group full access to the key.
				ea[1].grfAccessPermissions = FILE_ALL_ACCESS | GENERIC_WRITE | GENERIC_READ;
				ea[1].grfAccessMode = SET_ACCESS;
				ea[1].grfInheritance = NO_INHERITANCE;
				ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
				ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
				ea[1].Trustee.ptstrName = (LPTSTR)pAdminSID;

				// Create a new ACL that contains the new ACEs.
				DWORD dwRes = SetEntriesInAclW(2, ea, NULL, &pACL);
				if (ERROR_SUCCESS != dwRes) {
					throw std::runtime_error("SetEntriesInAcl failed, GLE=" + std::to_string(GetLastError()));
				}
				// Initialize a security descriptor.  
				auto secDesc = std::vector<unsigned char>(SECURITY_DESCRIPTOR_MIN_LENGTH);
				PSECURITY_DESCRIPTOR pSD = (PSECURITY_DESCRIPTOR)(&secDesc[0]);
				if (nullptr == pSD) {
					throw std::runtime_error("LocalAlloc failed, GLE=" + std::to_string(GetLastError()));
				}
				if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {
					throw std::runtime_error("InitializeSecurityDescriptor failed, GLE=" + std::to_string(GetLastError()));
				}
				// Add the ACL to the security descriptor. 
				if (!SetSecurityDescriptorDacl(pSD, TRUE, pACL, FALSE))   // not a default DACL 
				{
					throw std::runtime_error("SetSecurityDescriptorDacl failed, GLE=" + std::to_string(GetLastError()));
				}
				// Initialize a security attributes structure.
				sa.nLength = sizeof(SECURITY_ATTRIBUTES);
				sa.lpSecurityDescriptor = pSD;
				sa.bInheritHandle = FALSE;
				//< security attibute

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
					PIPE_ACCESS_DUPLEX,       // read/write access //tex WORKAROUND was PIPE_ACCESS_OUTBOUND, see IHExt/PipeClient for issue, GOTCHA: this means a client could stall the pipe if they write as IHHook only treats is as out only
					PIPE_TYPE_MESSAGE |       // message type pipe 
					PIPE_READMODE_MESSAGE |   // message-read mode 
					PIPE_WAIT,                // blocking mode 
					PIPE_UNLIMITED_INSTANCES, // max. instances  
					BUFSIZE,                  // output buffer size 
					BUFSIZE,                  // input buffer size 
					0,                        // client time-out 
					&sa);                    // security attribute 

				if (hPipeOut == INVALID_HANDLE_VALUE) {
					int err = GetLastError();
					spdlog::error("CreateNamedPipe PipeOut failed, GLE={}.", err);
					spdlog::error(":{}", GetLastErrorString(err));
					return -1;
				}

				// Wait for the client to connect; if it succeeds, 
				// the function returns a nonzero value. If the function
				// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 
				// GOTCHA: this means it's waiting for first pipe (pipein) to connect before it tries to connect the second (pipeout)
				spdlog::info(L"Pipe Server: Main thread awaiting client connection on {}", lpszPipenameIn);
				bool fConnectedIn = ConnectNamedPipe(hPipeIn, NULL) ?
					TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

				spdlog::info(L"Pipe Server: Main thread awaiting client connection on {}", lpszPipenameOut);
				bool fConnectedOut = ConnectNamedPipe(hPipeOut, NULL) ?
					TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

				if (fConnectedIn && fConnectedOut) {
					spdlog::info("Pipe Server: Client connected, creating a processing thread.");

					// Create a thread for processing the client that just connected
					hThread = CreateThread(
						nullptr,			// no security attribute 
						0,                 // default stack size 
						PipeInThread,    // thread proc
						hPipeIn,    // thread parameter 
						0,                 // not suspended 
						&dwThreadId);      // returns thread ID 

					if (hThread == NULL) {
						int err = GetLastError();
						spdlog::error("CreateThread PipeInThread failed, GLE={}:{}", err, GetLastErrorString(err));
						return -1;
					}
					else CloseHandle(hThread);

					// Create a thread for processing the client that just connected
					hThread = CreateThread(
						nullptr,			// no security attribute 
						0,                 // default stack size 
						PipeOutThread,    // thread proc
						hPipeOut,    // thread parameter 
						0,                 // not suspended 
						&dwThreadId);      // returns thread ID 

					if (hThread == NULL) {
						int err = GetLastError();
						spdlog::error("CreateThread PipeOutThread failed, GLE={}:{}", err, GetLastErrorString(err));
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
		// tex GOTCHA: however with the current implementation of shunting messages through single message queues, in practice it won't really work out with multiple clients
		DWORD WINAPI PipeOutThread(LPVOID lpvParam) {
			DWORD cbWritten = 0;
			BOOL fSuccess = FALSE;
			HANDLE hPipeOut;

			//PeekNamedPipe
			HANDLE hHeap = GetProcessHeap();
			CHAR* pchRequest = (CHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(CHAR));

			DWORD cbBytesRead = 0;

			LPDWORD lpTotalBytesAvail = 0;
			LPDWORD lpBytesLeftThisMessage = 0;
			//

			// Do some extra error checking since the app will keep running even if this thread fails.
			if (lpvParam == NULL) {
				spdlog::error("ERROR - Pipe Server Failure:");
				spdlog::error("   PipeOutThread got an unexpected NULL value in lpvParam.");
				spdlog::error("   PipeOutThread exitting.");
				if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
				return (DWORD)-1;
			}

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
				fSuccess = true;

				std::optional <std::string> messageOpt = messagesOut.pop();//tex waits if empty
				while (messageOpt) {

				//tex WORKAROUND: check if pipe still up. GOTCHA: only works when serverOut is DUPLEX
					//GOTCHA: DEBUGNOW still a kinda mess, requires the client to fail its write to close its pipe, then the server to write here to notice lol
				fSuccess = PeekNamedPipe(
					hPipeOut,        // handle to pipe
					pchRequest,    // buffer to receive data
					BUFSIZE * sizeof(CHAR), // size of buffer
					&cbBytesRead, // number of bytes read
					lpTotalBytesAvail,
					lpBytesLeftThisMessage);
					if (fSuccess && cbBytesRead > 0) {//tex WORKAROUND clear the pipe else it will clog lol
						fSuccess = ReadFile(
							hPipeOut,        // handle to pipe 
							pchRequest,    // buffer to receive data 
							BUFSIZE * sizeof(CHAR), // size of buffer 
							&cbBytesRead, // number of bytes read 
							NULL);        // not overlapped I/O 
						FlushFileBuffers(hPipeOut);
					}//if success
				if (!fSuccess) {
					int err = GetLastError();
						spdlog::error("PipeOutThread Read failed, GLE={}:{}", err, GetLastErrorString(err));
					spdlog::error("fSuccess={}, cbWritten={}.", fSuccess, cbWritten);
					break;
					}//


					std::string message = *messageOpt;

						//DEBUGNOW warn if over BUFFSIZE?
						
						DWORD messageBytes = static_cast<DWORD>(message.size()) + sizeof('\0');//tex: std string size() does not include a terminator but c_str() does
						//spdlog::trace("PipeOutThread Write:{}", message);//DEBUGNOW
						fSuccess = WriteFile(hPipeOut, message.c_str(), messageBytes, &cbWritten, NULL);

						if (!fSuccess || messageBytes != cbWritten) {
							fSuccess = false;//DEBUGNOW
							int err = GetLastError();
							spdlog::error("PipeOutThread WriteFile failed, GLE={}:{}", err, GetLastErrorString(err));
							spdlog::error("fSuccess={}, messageBytes={}, cbWritten={}.", fSuccess, messageBytes, cbWritten);
							break;//tex DEBUGNOW think this through, what fails WriteFile (GLEs) and how to deal with them
						}
						FlushFileBuffers(hPipeOut);

					messageOpt = messagesOut.pop();
					//if (!messageOpt) {
					//	std::this_thread::sleep_for(1000us);
					//	messageOpt = messagesOut.pop();
					//}
				}//while messageOpt

				//tex continue breakout
				if (!fSuccess) {
					break;
				}
			}//loop while

			FlushFileBuffers(hPipeOut);
			DisconnectNamedPipe(hPipeOut);
			CloseHandle(hPipeOut);

			HeapFree(hHeap, 0, pchRequest);

			spdlog::info("PipeOutThread exiting.");
			return 1;
		}//PipeOutThread

		//tex as above, but for In pipe
		// tex GOTCHA: however with the current implementation of shunting messages through single message queues, in practice it won't really work out with multiple clients
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
					BUFSIZE * sizeof(CHAR), // size of buffer
					&cbBytesRead, // number of bytes read
					lpTotalBytesAvail,
					lpBytesLeftThisMessage);
					*/

					// Read client requests from the pipe. This simplistic code only allows messages up to BUFSIZE characters in length.
				fSuccess = ReadFile(
					hPipeIn,        // handle to pipe 
					pchRequest,    // buffer to receive data 
					BUFSIZE * sizeof(CHAR), // size of buffer 
					&cbBytesRead, // number of bytes read 
					NULL);        // not overlapped I/O 

				if (!fSuccess) {
					if (GetLastError() == ERROR_BROKEN_PIPE) {
						spdlog::warn("PipeInThread: client disconnected.");
						break;
					}
					else {
						//DEBUGNOW what possible errors and what do?
						spdlog::error("PipeInThread ReadFile failed, GLE={}.", GetLastError());
						break;
					}
				}
				else if (cbBytesRead == 0) {
					spdlog::warn("PipeInThread: cbBytesRead == 0");
					//DEBUGNOW and then?
				}
				else {
					std::string message;
					message.insert(message.end(), pchRequest, pchRequest + cbBytesRead);
					//DEBUGNOW spdlog::trace("Client Request String:\"{}\"", message);
					QueueMessageIn(message);
				}//if fSuccess
			}//loop while

			DisconnectNamedPipe(hPipeIn);
			CloseHandle(hPipeIn);

			HeapFree(hHeap, 0, pchRequest);

			spdlog::info("PipeInThread exiting.");
			return 1;
		}//PipeInThread
	}//namespace PipeServer
}//namespace IHHoook
