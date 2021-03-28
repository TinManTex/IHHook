#pragma once
#include "windowsapi.h"

#include <string>
#include <vector>

namespace IHHook {
	namespace OS {
		int CheckVersionDelta(const unsigned long checkVersion[], std::string &exeVersionStr);
		std::wstring GetGameDir();
		std::string GetGameDirA();
		int StartProcess(LPCWSTR lpApplicationPath, LPWSTR lpCommandLine);
		std::vector<std::string> GetFolderNames(std::string folder);
		std::vector<std::string> GetFileNames(std::string folder);
		bool ListFiles(std::string path, std::string mask, std::vector<std::string>& files);
		void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND>& vhWnds);
		HWND GetMainWindow();
	}//namespace OS
}//namespace IHHook