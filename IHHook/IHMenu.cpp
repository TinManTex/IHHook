#include <string>
#include <vector>
#include <map>
#include <imgui/imgui.h>
#include "spdlog/spdlog.h"
#include <queue>
#include "IHHook.h"//SetDrawUI
#include "IHMenu.h"

namespace IHHook {
	namespace IHMenu {
		//tex would like to keep it const char* all the way through from lua to imgui instead of back and forthing bewtween char* and string, but imgui shits the bed at some point when I try that
		//try converting just menuItems to see
		std::string windowTitle{ "windowTitle" };

		std::string menuTitle{ "menuTitle" };

		int selectedItem = 0;
		int prevSelectedItem = 0;
		int maxStrLength = 0;//tex length of longest string in menuItems
		std::vector<std::string> menuItems{
			"1:Menu line test = 1:SomeSetting",
			"2:Menu line test = 1:SomeSetting",
			"3:Menu line test = 1:SomeSetting",
			"4:Menu line test = 1:SomeSetting",
			"5:Menu line test = 1:SomeSetting",
		};

		std::string menuLine{ "1:Menu line test:" };
		int selectedSetting = 0;
		std::vector<std::string> menuSettings{
			"1:SomeSetting",
			"2:SomeSetting",
			"3:SomeSetting",
			"4:SomeSetting",
		};

		std::string menuHelp = "Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.And more.Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.How much more.Some super long textand stuff that might describeand option.Yet more text lets see how this wraps.So much more.Some super long textand stuff that might describeand option.Yet more text letst see how this wraps.";

		char inputBuffer[1024] = "";
		char settingInputBuffer[1024] = "";

		//IH/Lua > IHMenu
		//DEBUGNOW tex: this is pretty trash, it's really just getting the IHExt api (which was also trash but atleas more flexible so since pushing through WPF) satisfied with the least fuss.
		//If IHHook and D3D hook turns out to be robust enough for users then IHExt can be ditched and this should be overhauled along with the IH side where it pushes menu or imgui specific stuff and leaves ExtCmd/Pipe stuff for other purposes

		void SetContent(std::vector<std::string> args) {
			//spdlog::trace(__func__);
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
			//spdlog::trace(__func__);
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
			//spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string content = args[3];

			if (name == "menuLine") {
				menuLine = content;
				strcpy(inputBuffer, menuLine.c_str());//DEBUGNOW
			}
		}//SetTextBox

		//args: string name, bool visible
		void UiElementVisible(std::vector<std::string> args) {
			//spdlog::trace(__func__);
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
			//DEBUGNOW dont like this
			else if (name == "menuTitle") {
				if (visible == 1) {
					g_ihhook->SetDrawUI(true);
					g_ihhook->SetCursor(true);
				}
				else {
					g_ihhook->SetDrawUI(false);
					g_ihhook->SetCursor(false);
				}
			}
		}//UiElementVisible

		void ClearTable(std::vector<std::string> args) {
			//spdlog::trace(__func__);
			if (args.size() < 1 + 1) {
				return;
			}

			std::string name = args[2];

			if (name == "menuItems") {
				menuItems.clear();
				maxStrLength = 0;
			}
		}//ClearTable

		void AddToTable(std::vector<std::string> args) {
			//spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string itemString = args[3];

			if (name == "menuItems") {
				menuItems.push_back(itemString);
				if (itemString.length() > maxStrLength) {
					maxStrLength = (int)itemString.length();
				}
			}
		}//AddToTable

		//args: string name, int itemIndex, string itemString
		void UpdateTable(std::vector<std::string> args) {
			//spdlog::trace(__func__);
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
			//spdlog::trace(__func__);
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
			//spdlog::trace(__func__);
			if (args.size() < 1 + 1) {
				return;
			}

			std::string name = args[2];

			if (name == "menuSetting") {
				menuSettings.clear();
			}
		}//ClearCombo

		void AddToCombo(std::vector<std::string> args) {
			//spdlog::trace(__func__);
			if (args.size() < 1 + 2) {
				return;
			}

			std::string name = args[2];
			std::string itemString = args[3];

			if (name == "menuSetting") {
				menuSettings.push_back(itemString);
				if (menuSettings.size() == 1) {
					strcpy(settingInputBuffer, menuSettings[0].c_str());
				}
			}
		}//AddToCombo

		void SelectCombo(std::vector<std::string> args) {
			//spdlog::trace(__func__);
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
		//DEBUGNOW
		void MenuMessage(std::string message) {
			//spdlog::trace(__func__);
			std::vector<std::string> args = split(message, "|");
			std::string cmd = args[1];

			if (menuCommands.count(cmd) == 0) {
				spdlog::warn("MenuMessage: Could not find menuCommand {}", cmd);
				return;
			}

			MenuCommandFunc MenuCommand = menuCommands[cmd];
			MenuCommand(args);
		}//MenuMessage

		void ProcessMessages() {
			//tex process messagesOut (lua > ihmenu commands) on this thread DEBUGNOW
			std::optional <std::string> messageOpt = messagesOut.pop();//tex waits if empty
			while (messageOpt) {
				std::string message = *messageOpt;

				MenuMessage(message);

				messageOpt = messagesOut.pop();
			}
		}//ProcessMessages
		//< IH/Lua > IHMenu 

		//IHMenu > IH/Lua
		//tex: needs to be thread safe since game/lua is different thread than IHMenu (which is on d3d present)
		//DEBUGNOW TODO rename to menuMessagesIn to differentiate from pipe?
		SafeQueue<std::string> messagesIn;
		SafeQueue<std::string> messagesOut;
		//tex lua > ihmenu (via l_MenuMessage)
		void QueueMessageOut(std::string message) {
			messagesOut.push(message);
		}//QueueMessageOut
		//tex ihmenu > lua (via l_GetMenuMessages)
		void QueueMessageIn(std::string message) {
			spdlog::trace("QueueMessageIn: " + message);
			messagesIn.push(message);
		}//QueueMessageIn

		void SetInitialText() {
			windowTitle = "Infinite Heaven";

			menuTitle = std::string("IHHook r") + std::to_string(Version);

			menuItems.clear();
			//menuItems.push_back(std::string("IHHook r") + std::to_string(Version));
			menuItems.push_back("This window should close shortly");
			menuItems.push_back("If it doesn't there may");
			menuItems.push_back("be an issue with IH");
			menuItems.push_back("If IH is not installed then");
			menuItems.push_back("delete MGS_TPP\\dinput8.dll");
			menuItems.push_back("to remove IHHook");
			menuItems.push_back("");

			if (errorMessages.size() > 0) {
				for each (std::string message in errorMessages) {
					menuItems.push_back(message);
				}
			}

			menuLine = "";

			menuSettings.clear();

			menuHelp = "";
		}//SetInitialText

		void DrawMenu(bool* p_open, bool lastOpen) {
			ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_::ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_::ImGuiCond_Once);
			//DEBUGNOW ImGui::SetNextWindowSize(ImVec2(0, 0));
			ImGui::SetNextWindowBgAlpha(0.30f);

			ImGuiWindowFlags windowFlags = 0;
			//windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
			//windowFlags |= ImGuiWindowFlags_NoSavedSettings;
		
			//tex: GOTCHA name acts as id by default so setting it to something dynamic like menuTitle means each submenu is a new window so it will have individual position and size if user changes it.
			//Alternative is to menuTitle + "##menuTitle"? or pushID, popID
			//if (!
			ImGui::Begin(windowTitle.c_str(), p_open, windowFlags); //tex: TODO: there's probably a better way to handle the x/close button somehow rather than this which just flips a bool
				//QueueMessageIn("togglemenu|1");
			//}

			ImGui::Text(menuTitle.c_str());
			ImGui::PushItemWidth(-1);//tex push out label
			if (menuItems.size() > 0) {
				int listboxHeightInItems = 20;
				if (ImGui::ListBoxHeader("##menuItems", (int)menuItems.size(), listboxHeightInItems)) {
					for (int i = 0; i < menuItems.size(); i++) {
						ImGui::PushItemWidth(-1);//tex push out label
						ImGui::PushID(i);//tex in theory shouldnt be a problem as menu items have a number prefixed
						bool selected = (selectedItem == i);
						//tex putting this before -v- means that ih/lua can set selectedItem (call SelectItem on keyboard scroll)
						//and have this scroll the selection into the view, but let ImGui::Selectable  //DEBUGNOW unless there's a loop with togamecmd 'selected' that calls SelectItem again?
						if (selected && prevSelectedItem != selectedItem) {
							prevSelectedItem = selectedItem;
							ImGui::SetScrollHereY(0.15f);
						}

						if (ImGui::Selectable(menuItems[i].c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick)) {
							selectedItem = i;
							prevSelectedItem = selectedItem;//tex to stop autoscroll from kicking off since we changed selectedItem
							QueueMessageIn("selected|menuItems|" + std::to_string(selectedItem));

							if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
								QueueMessageIn("activate|menuItems|" + std::to_string(selectedItem));
							}
						}
						//tex set selected as focus otherwise if inputtext has focus on menu open it's annoying
						if (*p_open && *p_open != lastOpen) {
							//DEBUGNOW ImGui::SetItemDefaultFocus();
							//DEBUGNOW ImGui::SetKeyboardFocusHere();
						}
						ImGui::PopID();
					}
					ImGui::ListBoxFooter();
				}//if ListBox
			}//if menuItems

			ImGuiInputTextFlags inputFlags = 0;
			inputFlags |= ImGuiInputTextFlags_EnterReturnsTrue;
			inputFlags |= ImGuiInputTextFlags_AutoSelectAll;
			if (ImGui::InputText("##menuLine", inputBuffer, IM_ARRAYSIZE(inputBuffer), inputFlags)) {
				menuLine = inputBuffer;
				QueueMessageIn("EnterText|menuLine|" + menuLine);
			}
			//ImGui::Text(inputBuffer); //DEBUG

			if (menuSettings.size() == 0) {
				ImGui::Text("");
			} else if (menuSettings.size() == 1) {//tex just a value
				ImGuiInputTextFlags settingInputFlags = 0;
				settingInputFlags |= ImGuiInputTextFlags_EnterReturnsTrue;
				if (ImGui::InputText("##menuSettingInput", settingInputBuffer, IM_ARRAYSIZE(settingInputBuffer), settingInputFlags)) {
					if (menuSettings.size() == 1) {
						menuSettings[0] = settingInputBuffer;
						QueueMessageIn("input|menuSetting|" + menuSettings[0]);
					}
				}
			} else {//tex use combo box
				const char* comboLabel = "";// Label to preview before opening the combo (technically it could be anything)
				if (menuSettings.size() > 0 && selectedSetting < menuSettings.size()) {
					comboLabel = menuSettings[selectedSetting].c_str();
				}
				static ImGuiComboFlags flags = 0;
				if (ImGui::BeginCombo("##menuSettings", comboLabel, flags)) {
					for (int i = 0; i < menuSettings.size(); i++) {
						ImGui::PushID(i);
						bool selected = (selectedSetting == i);
						if (ImGui::Selectable(menuSettings[i].c_str(), selected)) {
							selectedSetting = i;
							QueueMessageIn("selectedcombo|menuSetting|" + std::to_string(selectedSetting));
						}

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (selected) {
							//DEBUGNOW ImGui::SetItemDefaultFocus();
						}
						ImGui::PopID();
					}
					ImGui::EndCombo();
				}//if Combo
			}//menuSetting

			ImGui::TextWrapped("%s", menuHelp.c_str());//tex WORKAROUND: Text widget takes fmted text, so slap it in like this so it doesn't choke on stuff like %, there's also ::TextUnformatted that's more performant, but it doesn't wrap.
			ImGui::End();

			//ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(0, -1));//DEBUGNOW
		}//DrawMenu

	}//namespace IHMenu
}//namespace IHHook