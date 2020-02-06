#include "OS.h"

#include "spdlog/spdlog.h"
#include "IHHook.h"//exename, thisModule
#pragma comment(lib,"Version.lib") // CheckVersion
#include <stack>

namespace IHHook {
	//IN/SIDE: IHHook::exeName
	bool CheckVersion(const DWORD checkVersion[]) {
		spdlog::debug(__func__);

		std::wstring gameDir = GetGameDir();
		std::wstring exeDir = gameDir + exeName;
		spdlog::debug(L"exeDir: {}", exeDir.c_str());
		LPTSTR lpszFilePath = new TCHAR[MAX_PATH];
		std::wcscpy(lpszFilePath, exeDir.c_str());

		DWORD dwDummy;
		DWORD dwFVISize = GetFileVersionInfoSize(lpszFilePath, &dwDummy);

		LPBYTE lpVersionInfo = new BYTE[dwFVISize];

		GetFileVersionInfo(lpszFilePath, 0, dwFVISize, lpVersionInfo);

		delete[] lpszFilePath;

		UINT uLen;
		VS_FIXEDFILEINFO *lpFfi;

		VerQueryValue(lpVersionInfo, L"\\", (LPVOID *)&lpFfi, &uLen);

		DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
		DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;

		delete[] lpVersionInfo;

		//spdlog::debug( "Higher: {}", dwFileVersionMS);
		//spdlog::debug( "Lower: {}", dwFileVersionLS);

		DWORD exeVersion[4] = {
			HIWORD(dwFileVersionMS),
			LOWORD(dwFileVersionMS),
			HIWORD(dwFileVersionLS),
			LOWORD(dwFileVersionLS)
		};

		std::string exeVersionStr =
			std::to_string(exeVersion[0]) + "," +
			std::to_string(exeVersion[1]) + "," +
			std::to_string(exeVersion[2]) + "," +
			std::to_string(exeVersion[3]);

		spdlog::info("mgsv exe version: {}", exeVersionStr);

		for (int i = 0; i < 4; i++) {
			if (checkVersion[i] != exeVersion[i]) {
				return false;
			}
		}

		return true;
	}//CheckVersion

	//IN/SIDE: thisModule
	std::wstring GetGameDir() {
		//tex user having unicode path might be trouble, but on a quick test lua is hinky with utf16
		TCHAR path_buffer[_MAX_PATH];
		GetModuleFileName(thisModule, path_buffer, _MAX_PATH);

		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		_wsplitpath(path_buffer, drive, dir, fname, ext);

		std::wstring path = std::wstring(drive) + std::wstring(dir);

		return path;

	}//GetGameDir

	//KLUDGE till I can shift to relative paths in lua
	std::string GetGameDirA() {
		//tex user having unicode path might be trouble, but on a quick test lua is hinky with utf16
		CHAR path_buffer[_MAX_PATH];
		GetModuleFileNameA(thisModule, path_buffer, sizeof(path_buffer));

		CHAR drive[_MAX_DRIVE];
		CHAR dir[_MAX_DIR];
		CHAR fname[_MAX_FNAME];
		CHAR ext[_MAX_EXT];
		_splitpath(path_buffer, drive, dir, fname, ext);

		std::string path = std::string(drive) + std::string(dir);

		return path;

	}//GetGameDirA

	int StartProcess(LPCWSTR lpApplicationPath, LPWSTR lpCommandLine) {
		spdlog::info(__func__);
		spdlog::info(L"lpApplicationPath: {}", lpApplicationPath);
		spdlog::info(L"lpCommandLine: {}", lpCommandLine);

		// additional information
		STARTUPINFO startupInfo;
		PROCESS_INFORMATION processInfo;
		// set the size of the structures
		ZeroMemory(&startupInfo, sizeof(startupInfo));
		startupInfo.cb = sizeof(startupInfo);
		ZeroMemory(&processInfo, sizeof(processInfo));

		int succeeded = CreateProcess(lpApplicationPath,   // the path
			lpCommandLine,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&startupInfo,            // Pointer to STARTUPINFO structure
			&processInfo             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
		);
		// Close process and thread handles. 
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);

		//tex TODO log errors with GetLastError, GetExitCodeProcess

		return succeeded;
	}//StartProcess

	std::vector<std::string> GetFolderNames(std::string folder) {
		spdlog::debug(__func__);

		std::vector<std::string> names;
		std::string search_path = folder + "/*.*";
		WIN32_FIND_DATAA fd;
		HANDLE hFind = FindFirstFileA(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					//GOTCHA: FindFirstFileA also returns '.' and  '..'
					std::string name = fd.cFileName;
					std::size_t found = name.find(".");
					if (found == std::string::npos) {
						names.push_back(fd.cFileName);
						spdlog::trace(fd.cFileName);
					}
				}//if FILE_ATTRIBUTE_DIRECTORY
			} while (FindNextFileA(hFind, &fd));
			FindClose(hFind);
		}//if !INVALID_HANDLE_VALUE
		return names;
	}//GetFolderNames

	std::vector<std::string> GetFileNames(std::string folder) {
		spdlog::debug(__func__);

		std::vector<std::string> names;
		std::string search_path = folder + "/*.*";
		WIN32_FIND_DATAA fd;
		HANDLE hFind = FindFirstFileA(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				// read all (real) files in current folder
				// delete '!' to read other 2 default folder . and ..
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					names.push_back(fd.cFileName);
					spdlog::trace(fd.cFileName);
				}//if !FILE_ATTRIBUTE_DIRECTORY
			} while (FindNextFileA(hFind, &fd));
			FindClose(hFind);
		}//if !INVALID_HANDLE_VALUE
		return names;
	}//GetFileNames

	//use std::vector<std::string> files;
	//bool success = ListFiles("C:\\somepath", "*", files);
	bool ListFiles(std::string path, std::string mask, std::vector<std::string>& files) {
		HANDLE hFind = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATAA ffd;
		std::string spec;
		std::stack<std::string> directories;

		directories.push(path);
		files.clear();

		while (!directories.empty()) {
			path = directories.top();
			spec = path + "\\" + mask;
			directories.pop();

			hFind = FindFirstFileA(spec.c_str(), &ffd);
			if (hFind == INVALID_HANDLE_VALUE) {
				return false;
			}

			do {
				//wcscmp wide
				if (strcmp(ffd.cFileName, ".") != 0 &&
					strcmp(ffd.cFileName, "..") != 0) {
					if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
						directories.push(path + "\\" + ffd.cFileName);
					}
					else {
						files.push_back(path + "\\" + ffd.cFileName);
					}
				}
			} while (FindNextFileA(hFind, &ffd) != 0);

			if (GetLastError() != ERROR_NO_MORE_FILES) {
				FindClose(hFind);
				return false;
			}

			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}

		return true;
	}//Listfiles

	//DEBUG
	void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND> &vhWnds) {
		// find all hWnds (vhWnds) associated with a process id (dwProcessID)
		HWND hCurWnd = NULL;
		do {
			hCurWnd = FindWindowEx(NULL, hCurWnd, NULL, NULL);
			DWORD dwWindowProcessID = 0;
			GetWindowThreadProcessId(hCurWnd, &dwWindowProcessID);
			if (dwWindowProcessID == dwProcessID) {
				vhWnds.push_back(hCurWnd);  // add the found hCurWnd to the vector

				//DEBUG
				std::wstring title(GetWindowTextLength(hCurWnd) + 1, L'\0');
				if (title.size() > INT_MAX) {
					throw std::overflow_error("window title is larger than INT_MAX");
				}
				GetWindowTextW(hCurWnd, &title[0], static_cast<int>(title.size())); //note: C++11 only

				wprintf(L"Found hWnd %p:%s\n", hCurWnd, title.c_str());
			}
		} while (hCurWnd != NULL);
	}

	//tex ASSUMPTION: Based on running GetAllWindowsFromProcessID, MGSV only has one window (well two if I compile IHHook to open a console while debugging).
	//Don't want to test for the MGSV window title since I don't know if it's localized or not
	//Also would fail if any other funky 3rd party programs that like to inject their own windows
	HWND GetMainWindow() {
		// find all hWnds (vhWnds) associated with a process id (dwProcessID)
		HWND hWnd = NULL;
		DWORD dwProcessID = GetCurrentProcessId();

		do {
			hWnd = FindWindowEx(NULL, hWnd, NULL, NULL);
			DWORD dwWindowProcessID = 0;
			GetWindowThreadProcessId(hWnd, &dwWindowProcessID);
			if (dwWindowProcessID == dwProcessID) {
				std::wstring title(GetWindowTextLength(hWnd) + 1, L'\0');
				if (title.size() > INT_MAX) {
					throw std::overflow_error("window title is larger than INT_MAX");
				}
				GetWindowTextW(hWnd, &title[0], static_cast<int>(title.size()));
				if (title != L"IHHook") {
					return hWnd;
				}
			}
		} while (hWnd != NULL);

		return NULL;
	}
}//IHHook