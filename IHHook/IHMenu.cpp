#include <string>
#include <vector>
#include <map>
#include <imgui/imgui.h>
#include "spdlog/spdlog.h"
#include <queue>

namespace IHHook {
	namespace IHMenu {
		//tex would like to keep it const char* all the way through from lua to imgui instead of back and forthing bewtween char* and string, but imgui shits the bed at some point when I try that
		//try converting just menuItems to see
		std::string menuTitle{ "menuTitle" };

		int selectedItem = 0;

		std::vector<std::string> menuItems{
			"1:Menu line test: 1:SomeSetting",
			"2:Menu line test: 1:SomeSetting",
			"3:Menu line test: 1:SomeSetting",
			"4:Menu line test: 1:SomeSetting",
			"5:Menu line test: 1:SomeSetting",
		};

		//DEBUGNOW static char menuLine[128] = "1:Menu line test:";
		std::string menuLine{ "menuLine" };
		int selectedSetting = 0;
		std::vector<std::string> menuSettings{
			"1:SomeSetting",
			"2:SomeSetting",
			"3:SomeSetting",
			"4:SomeSetting",
		};

		std::string menuHelp = "Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.And more.Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.How much more.Some super long textand stuff that might describeand option.Yet more text lets see how this wraps.So much more.Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.";

		void DrawMenu() {
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_::ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_::ImGuiCond_Once);

			//DEBUGNOW tex: name acts as id by default so setting it to something dynamic like menuTitle means each submenu is a new window so it will have individual position and size if user changes it.
			//Alternative is to menuTitle + "##menuTitle"? or pushID, popID
			ImGui::Begin("Infinite Heaven");//DEBUGNOW, &drawUI); //tex: TODO: there's probably a better way to handle the x/close button somehow rather than this which just flips a bool
			//ImGui::Text("Menu Key: F1");//DEBUGNOW
			ImGui::Text(menuTitle.c_str());
			ImGui::PushItemWidth(-1);//tex push out label
			int listboxHeightInItems = 20;
			ImGui::ListBoxHeader("##menuItems", menuItems.size(), listboxHeightInItems);
			for (int i = 0; i < menuItems.size(); i++) {
				bool selected = (selectedItem == i);
				ImGui::Selectable(menuItems[i].c_str(), selected);
				if (selected) {
					// handle selection
				}
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
					// Do stuff on Selectable() double click.                                                                                                                                                                                                                           
					//selectedItem = i;//DEBUGNOW send tomegv select this equivalent
				}
			}
			ImGui::ListBoxFooter();

			//DEBUGNOW ImGui::InputText("##menuLine", menuLine, IM_ARRAYSIZE(inputBuffer));
			ImGui::Text(menuLine.c_str());
			//ImGui::Selectable(menuLine.c_str());

			//DEBUGNOW ImGui::Combo("##menuSettings", &selectedSetting, menuSettings.data(), menuSettings.size());

			const char* comboLabel = menuSettings[selectedSetting].c_str();  // Label to preview before opening the combo (technically it could be anything)
			static ImGuiComboFlags flags = 0;
			if (ImGui::BeginCombo("##menuSettings", comboLabel, flags)) {
				for (int n = 0; n < menuSettings.size(); n++) {
					const bool isSelected = (selectedSetting == n);
					if (ImGui::Selectable(menuSettings[n].c_str(), isSelected))
						selectedSetting = n;

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::TextWrapped(menuHelp.c_str());

			ImGui::End();
		}//DrawMenu

		//IH/Lua > IHMenu
		//DEBUGNOW tex: this is pretty trash, it's really just getting the IHExt api (which was also trash but atleas more flexible so since pushing through WPF) satisfied with the least fuss.
		//If IHHook and D3D hook turns out to be robust enough for users then IHExt can be ditched and this should be overhauled along with the IH side where it pushes menu or imgui specific stuff and leaves ExtCmd/Pipe stuff for other purposes

		void SetContent(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string content = args[3];

			if (name == "menuTitle") {
				menuTitle = content;
			}
		}//SetContent

		void SetText(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string content = args[3];

			if (name == "menuHelp") {
				menuHelp = content;
			}
		}//SetText

		void SetTextBox(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string content = args[3];

			if (name == "menuLine") {
				menuLine = content;
			}
		}//SetTextBox

		//args: string name, bool visible
		void UiElementVisible(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			int visible = std::stoi(args[3]);

			if (name == "menuHelp") {
				if (visible == 0) {
					menuHelp = "";
				}
				else {

				}
			}
			else if (name == "menuTitle") {
				//bool hideMenu = (visible == 0);
				//if (hideMenu) {
				//	//DEBUGNOW   ClearMenu();
				//}
			}
		}//UiElementVisible

		void ClearTable(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 1) {
				return;
			}

			std::string name = args[2];

			if (name == "menuItems") {
				menuItems.clear();
			}
		}//ClearTable

		void AddToTable(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string itemString = args[3];

			if (name == "menuItems") {
				menuItems.push_back(itemString);
			}
		}//AddToTable

		//args: string name, int itemIndex, string itemString
		void UpdateTable(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 3) {
				return;
			}

			std::string name = args[2];
			int itemIndex = std::stoi(args[3]);
			std::string itemString = args[4];

			if (name == "menuItems") {
				if (itemIndex >= 0 && itemIndex < menuItems.size()) {
					menuItems[itemIndex] = itemString;
				}
			}
		}//UpdateTable

		//args: string name, int itemIndex
		void SelectItem(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			int itemIndex = std::stoi(args[3]);
			if (name == "menuItems") {
				if (itemIndex >= 0 && itemIndex < menuItems.size()) {
					selectedItem = itemIndex;
				}
			}
		}//SelectItem

		void ClearCombo(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 1) {
				return;
			}

			std::string name = args[2];

			if (name == "menuSetting") {
				menuSettings.clear();
			}
		}//ClearCombo

		void AddToCombo(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string itemString = args[3];

			if (name == "menuSetting") {
				menuSettings.push_back(itemString);
			}
		}//AddToCombo

		void SelectCombo(std::vector<std::string> args) {
			spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			int selectedIndex = std::stoi(args[3]);

			if (name == "menuSetting") {
				if (selectedIndex >= 0 && selectedIndex < menuItems.size()) {
					selectedSetting = selectedIndex;
				}
			}
		}//SelectCombo

		typedef void(*MenuCommandFunc) (std::vector<std::string> args);
		std::map<std::string, MenuCommandFunc> menuCommands;
		void AddMenuCommands() {
			menuCommands["SetContent"] = SetContent;
			menuCommands["SetText"] = SetText;
			menuCommands["SetTextBox"] = SetTextBox;
			menuCommands["UiElementVisible"] = UiElementVisible;
			menuCommands["ClearTable"] = ClearTable;
			menuCommands["AddToTable"] = AddToTable;
			menuCommands["UpdateTable"] = UpdateTable;
			menuCommands["SelectItem"] = SelectItem;
			menuCommands["ClearCombo"] = ClearCombo;
			menuCommands["AddToCombo"] = AddToCombo;
			menuCommands["SelectCombo"] = SelectCombo;
			//SelectAllText
		}//AddMenuCommands

		//DEBUGNOW TODO: break out into util
		std::vector<std::string> split(const std::string& str, const std::string& delim) {
			std::vector<std::string> tokens;
			size_t prev = 0, pos = 0;
			do {
				pos = str.find(delim, prev);
				if (pos == std::string::npos) pos = str.length();
				std::string token = str.substr(prev, pos - prev);
				if (!token.empty()) tokens.push_back(token);
				prev = pos + delim.length();
			} while (pos < str.length() && prev < str.length());
			return tokens;
		}//split

		void MenuMessage(const char* cmd, const char* message) {
			//spdlog::trace(__func__);
			if (menuCommands.count(cmd) == 0) {
				spdlog::warn("MenuMessage: Could not find menuCommand {}", cmd);
				return;
			}

			std::vector<std::string> args = split(message, "|");

			MenuCommandFunc MenuCommand = menuCommands[cmd];
			MenuCommand(args);
		}//MenuMessage

		//IHMenu > IH/Lua
		//tex: simplest way to allow lua access pipe due to threading
		std::queue<std::string> messagesIn;

		std::mutex inMutex;

		void QueueMessageIn(std::string message) {
			std::unique_lock<std::mutex> inLock(inMutex);
			messagesIn.push(message);
		}//QueueMessageIn

	}//namespace IHMenu
}//namespace IHHook