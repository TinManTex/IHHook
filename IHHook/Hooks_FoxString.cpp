//ZIP: FoxString hook
#include "Hooks_FoxString.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "IHHook.h"//BaseAddr,enableCityHook
#include "MinHook/MinHook.h"
#include "HookMacros.h"
#include "hooks/mgsvtpp_func_typedefs.h"
#include <list>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "Util.h"//config 
#include "OS.h"

namespace IHHook {
	namespace Hooks_FoxString {
		bool overrideFoxString = false;
		struct foxStringReplace {
			std::string replaceString = "";
			std::string newString = "";
		};
		std::list<foxStringReplace> replaceStrings = {};

		int l_AddReplacementFoxString(lua_State* L) {
			const char* filePathOld = lua_tostring(L, -1);
			if (filePathOld == NULL) {
				filePathOld = "";
			}
			const char* filePathNew = lua_tostring(L, -2);
			if (filePathNew == NULL) {
				filePathNew = "";
			}
			AddReplacementToList(filePathOld, filePathNew);

			return 0;
		}//l_AddReplacementFoxString

		void AddReplacementToList(std::string filePathOld, std::string filePathNew) {
			if (filePathOld == "" || filePathNew == "")
				return;

			spdlog::debug("AddReplacementFoxString: Old: {}, New: {}", filePathOld, filePathNew);
			foxStringReplace newReplace = { filePathOld, filePathNew };
			replaceStrings.push_front(newReplace);
			overrideFoxString = true;
		}

		fox::String * CreateInPlaceHook(fox::String *outFoxString, char *cString) {
			if (config.logFoxStringCreateInPlace) {
				spdlog::debug("CreateInPlaceHook: {}", cString);
			}

			if (!overrideFoxString) {
				return CreateInPlace(outFoxString, cString);
			}

			//ZIP: Iterate through replacements
			if (std::size(replaceStrings) > 0) {
				std::list<foxStringReplace>::iterator it;
				for (it = replaceStrings.begin(); it != replaceStrings.end(); ++it) {
					std::string oldString = it->replaceString;
					if (oldString == cString) {
						std::string newString = it->newString;
						spdlog::debug("CreateInPlaceHook: Old: {}, New: {}", oldString, newString);
						replaceStrings.erase(it);
						if (std::size(replaceStrings) <= 0) {
							spdlog::debug("CreateInPlaceHook: All replacements done.");
							overrideFoxString = false;
						}
						return CreateInPlace(outFoxString, newString.c_str());
					}
				}
			}else{
				spdlog::debug("CreateInPlaceHook: No more replacements.");
				overrideFoxString = false;
			}
			
			return CreateInPlace(outFoxString, cString);
		}//fox::string::CreateInPlaceHook

		bool ParseConfig(std::string fileName) {
			spdlog::debug("ParseConfig {}", fileName);
			std::ifstream infile(fileName);
			if (infile.fail()) {
				spdlog::warn("ParseConfig ifstream.fail for {}", fileName);
				return false;
			}

			std::string line;
			while (std::getline(infile, line)) {
				std::istringstream iss(line);
				//tex trim leading/trailing whitespace
				line = trim(line);
				if (line.size() == 0) {
					continue;
				}

				//tex trim to before comment
				std::size_t found = line.find("--");
				if (found == 0) {
					continue;
				}
				if (found != std::string::npos) {
					line = line.substr(0, found - 1);
				}
				if (line.size() == 0) {
					continue;
				}

				//tex just skip the specific cases outright
				found = line.find("local this");
				if (found != std::string::npos) {
					continue;
				}
				found = line.find("return this");
				if (found != std::string::npos) {
					continue;
				}
				if (line == "}") {
					continue;
				}

				//tex trim trailing comma
				if (line[line.size() - 1] == ',') {
					line = line.substr(0, line.size() - 1);
				}

				found = line.find("=");
				if (found == std::string::npos) {
					continue;
				}

				std::string varName = line.substr(0, found);
				std::string valueStr = line.substr(found + 1);
				varName = trim(varName);
				valueStr = trim(valueStr);

				//ZIP: If there are any valid entries, enable override and add entry to list.
				if (varName != "" && valueStr != "") {
					spdlog::debug("AddReplacementFoxString: Old:{}, New:{}", varName, valueStr);
					foxStringReplace newReplace = { varName, valueStr };
					replaceStrings.push_front(newReplace);
					overrideFoxString = true;
				}
			}//while line

			return true;
		}//ParseConfig

		void CreateHooks() {
			spdlog::debug(__func__);

			CREATE_HOOK(CreateInPlace)
			ENABLEHOOK(CreateInPlace)

			//ZIP: Scans info files in "\MGS_TPP\mod\ihhook" folder.
			spdlog::debug("FoxString: Looking for replacement infos");
			std::vector<std::string> fullFileNames;
			std::string modDir = OS::GetGameDirA() + "mod\\ihhook";
			bool success = OS::ListFiles(modDir, "*", fullFileNames);
			unsigned int numNames = static_cast<unsigned int>(fullFileNames.size());
			if (numNames > 0) {
				for (int i = 0; i < fullFileNames.size(); i++) {
					std::string fileName = fullFileNames[i].c_str();
					spdlog::debug("FoxString: Found replacement info {}", fileName);
					ParseConfig(fileName);
				}
			}
			else {
				spdlog::debug("FoxString: No replacement infos found!");
			}
		}//CreateHooks

		int CreateLibs(lua_State* L) {
			spdlog::debug(__func__);

			luaL_Reg libFuncs[] = {
				{ "AddReplacementFoxString", l_AddReplacementFoxString },

				{ NULL, NULL }//GOTCHA: crashes without
			};
			luaI_openlib(L, "IHH", libFuncs, 0);
			return 1;
		}//CreateLibs
	}//Hooks_Fox
}//namespace IHHook