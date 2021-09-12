#include "Hooks_CityHash.h"
#include "spdlog/spdlog.h"
//OFF #include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//BaseAddr,enableCityHook
#include "MinHook/MinHook.h"


namespace IHHook {
	namespace Hooks_CityHash {
		// uncomment if you only want to log paths (contains '/' or '\', or ends in .lua/.json/.fpk/.ftexs)
		//#define PATHS_ONLY

		typedef unsigned __int64(__fastcall* cityHash_func)(char* str, unsigned int len);

		const size_t CityHash1BaseAddr = 0x141a08ee0; //<//1.0.15.3 //1.0.15.2> 0x141a08ec0;
		const size_t CityHash2BaseAddr = 0x14c1bc140;//<//1.0.15.3 //1.0.15.2> 0x14bcbdfa0;
		cityHash_func origCityHash1;
		cityHash_func origCityHash2;

		//FUNCPTRDEF(unsigned __int64, CityHash1, char* str, unsigned int  len)
		//FUNCPTRDEF(unsigned __int64, CityHash2, char* str, unsigned int  len)
		//FUNC_DECL_SIG(CityHash1,
		//	"\x40\x00\x55\x56\x41\x00\x48\x83\xEC\x00\x44\x8B", 
		//	"x?xxx?xxx?xx")
		//FUNC_DECL_PATTERN(CityHash1,"40 ? 55 56 41 ? 48 83 EC ? 44 8B")
		//FUNC_DECL_SIG(CityHash2,
		//	"\x53\x55\x56\x41\x00\x48\x83\xEC\x00\x41\x89", 
		//	"xxxx?xxx?xx")
		//	FUNC_DECL_PATTERN(CityHash2,"53 55 56 41 ? 48 83 EC ? 41 89")

		std::wstring cityLogName = L"cityhash_log.txt";
		std::shared_ptr<spdlog::logger> cityLog;

		//tex cut from legacy Logger LogString
		void LogString(char* str, int str_len) {
			// string might have a null char anywhere between 0 - str_len, so lets find it and make sure we don't add it to the buffer
			// (because that would stop later buffer entries being written to the log, as the null would come before them)
			int real_len = str_len;
			for (int i = 0; i < str_len - 1; i++) // have to check up to str_len - 1 instead of up to str_len otherwise it crashes?
			{
				if (str[i] == '\0') {
					real_len = i - 1;
					break;
				}
			}

			if (str[real_len - 1] == '\0') // above might have missed the null because we had to do str_len - 1, so check again just incase (we really don't want to copy any nulls)
				real_len--;

			char* buff = new char[real_len + 1];
			memcpy(buff, str, real_len);
			buff[real_len] = '\0';

			cityLog->info("{}", buff);

			delete[] buff;
		}//LogString

		unsigned __int64 __fastcall CityHash1Hook(char* str, unsigned int len) {

			if (str && len) {
#ifdef PATHS_ONLY
				bool isPath = false;
				for (int i = 0; i < a2; i++)
					if (a1[i] == '/' || a1[i] == '\\') {
						isPath = true;
						break;
					}

				// doesn't contain '/' or '\', check for .lua/.json/.fpk/.ftexs
				if (!isPath && a2 > 5) {
					// have to go through the whole string to check, since it seems strings can end with a variable amount of null bytes
					for (int i = 0; i < a2 - 4; i++) {
						if (a1[i] == '.' && a1[i + 1] == 'l' && a1[i + 2] == 'u' && a1[i + 3] == 'a') // check for .lua
						{
							isPath = true;
							break;
						}
						if (a1[i] == '.' && a1[i + 1] == 'j' && a1[i + 2] == 's' && a1[i + 3] == 'o') // check for .jso(n)
						{
							isPath = true;
							break;
						}
						if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 'p' && a1[i + 3] == 'k') // check for .fpk(d)
						{
							isPath = true;
							break;
						}
						if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 't' && a1[i + 3] == 'e') // check for .fte(xs)
						{
							isPath = true;
							break;
						}
					}
				}

				if (!isPath)
					return origCityHash1(a1, a2);
#endif
				LogString(str, len);
			}
			return origCityHash1(str, len);
		}

		unsigned __int64 __fastcall CityHash2Hook(char* str, unsigned int len) {
			if (str && len) {
#ifdef PATHS_ONLY
				bool isPath = false;
				for (int i = 0; i < a2; i++)
					if (a1[i] == '/' || a1[i] == '\\') {
						isPath = true;
						break;
					}

				// doesn't contain '/' or '\', check for .lua/.json/.fpk/.ftexs
				if (!isPath && a2 > 5) {
					// have to go through the whole string to check, since it seems strings can end with a variable amount of null bytes
					for (int i = 0; i < a2 - 4; i++) {
						if (a1[i] == '.' && a1[i + 1] == 'l' && a1[i + 2] == 'u' && a1[i + 3] == 'a') // check for .lua
						{
							isPath = true;
							break;
						}
						if (a1[i] == '.' && a1[i + 1] == 'j' && a1[i + 2] == 's' && a1[i + 3] == 'o') // check for .jso(n)
						{
							isPath = true;
							break;
						}
						if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 'p' && a1[i + 3] == 'k') // check for .fpk(d)
						{
							isPath = true;
							break;
						}
						if (a1[i] == '.' && a1[i + 1] == 'f' && a1[i + 2] == 't' && a1[i + 3] == 'e') // check for .fte(xs)
						{
							isPath = true;
							break;
						}
					}
				}

				if (!isPath)
					return origCityHash2(a1, a2);
#endif
				LogString(str, len);
			}
			return origCityHash2(str, len);
		}

		void CreateHooks(size_t RealBaseAddr) {
			spdlog::debug(__func__);

			if (!enableCityHook) {
				spdlog::debug("!enableCityHook, returning");
				return;
			}

			cityLog = spdlog::basic_logger_st("cityhash", cityLogName);
			// NMC: default thread pool settings can be modified *before* creating the async logger:
			// spdlog::init_thread_pool(8192, 1); // queue with 8k items and 1 backing thread.
			//tex creatong async logger fails for some reason
			//according to the benchmarks on the spdlog github mt non blocking async is the only thing that comes close to st
			//the tradeoffs being I guess different ordering than the actual calls, loss of some logging if the queue overflows
			//upside being performance as mt async returns immediately
			//logger = spdlog::basic_logger_mt<spdlog::async_factory>("cityhash", logName);
			cityLog->set_pattern("%v");//tex raw logging

			if (isTargetExe) {//DEBUGNOW
				// CityHash1BaseAddr / CityHash2BaseAddr addresses are from IDA, which uses the ImageBase field in the exe as the base address (usually 0x140000000)
				// the real base address changes every time the game is run though, so we have to remove that base address and add the real one
				void* CityHash1_rebased = (void*)((CityHash1BaseAddr - BaseAddr) + RealBaseAddr);
				void* CityHash2_rebased = (void*)((CityHash2BaseAddr - BaseAddr) + RealBaseAddr);

				MH_CreateHook(CityHash1_rebased, CityHash1Hook, (LPVOID*)&origCityHash1);
				MH_CreateHook(CityHash2_rebased, CityHash2Hook, (LPVOID*)&origCityHash2);

				if (enableCityHook) {
					MH_EnableHook(CityHash1_rebased);
					MH_EnableHook(CityHash2_rebased);
				}
			}
		}//CreateHooks
	}//namespace Hooks_CityHash
}//namespace IHHook