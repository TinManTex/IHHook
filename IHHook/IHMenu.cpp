#include <string>
#include <vector>
#include <map>
#include <imgui/imgui.h>
#include "spdlog/spdlog.h"
#include <queue>
#include "Util.h"
#include "IHHook.h"//SetDrawUI
#include "IHMenu.h"

namespace IHHook {
	namespace IHMenu {
		std::string modTitle = "IH";
		std::string titleHelp = "[F3] Menu, [F2] Cursor";

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

		const int bufferSize = 1024;
		char inputBuffer[bufferSize] = "";
		char settingInputBuffer[bufferSize] = "";

		void DrawList(float contentHeight, int helpHeightInItems);
		bool TextInputComboBox(const char* id, char* buffer, size_t maxInputSize, std::vector<std::string> items, size_t showMaxItems);

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
					//DEBUGNOW g_ihhook->SetCursor(true);//tex now handled by ivars.menu_enableCursorOnMenuOpen
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
				else {
					spdlog::warn("IHMenu.SelectItem: itemIndex {} out of bounds: {}",itemIndex, menuItems.size());
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
				settingInputBuffer[0] = '\0';
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
				if (selectedIndex >= 0 && selectedIndex < menuSettings.size()) {
					selectedSetting = selectedIndex;
					strcpy_s(settingInputBuffer, bufferSize, menuSettings[selectedSetting].c_str());//DEBUGNOW
				}
				else {
					spdlog::warn("IHMenu.SelectCombo: itemIndex {} out of bounds: {}", selectedIndex, menuSettings.size());
				}
			}
		}//SelectCombo

		void ToggleStyleEditor(std::vector<std::string> args) {
			g_ihhook->ToggleStyleEditor();
		}//ToggleStyleEditor

		void ToggleImguiDemo(std::vector<std::string> args) {
			g_ihhook->ToggleImguiDemo();
		}//ToggleImguiDemo

		void EnableCursor(std::vector<std::string> args) {
			g_ihhook->SetCursor(true);
		}//EnableCursor

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
			menuCommands["ToggleStyleEditor"] = ToggleStyleEditor;
			menuCommands["ToggleImguiDemo"] = ToggleImguiDemo;
			menuCommands["EnableCursor"] = EnableCursor;
			//SelectAllText
		}//AddMenuCommands

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

		//CALLER: FramInitialize firstFrame
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

		// HWL NOTE: should we get rid of openPrev?
		void DrawMenu(bool* p_open, bool openPrev) {
			ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_::ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_::ImGuiCond_FirstUseEver);

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigWindowsMoveFromTitleBarOnly = true;

			ImGuiWindowFlags windowFlags = 0;
			//windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
			//windowFlags |= ImGuiWindowFlags_NoSavedSettings;
			windowFlags |= ImGuiWindowFlags_NoScrollbar;
			windowFlags |= ImGuiWindowFlags_NoScrollWithMouse;

			if (ihVersion != 0) {
				windowTitle = modTitle + " r" + std::to_string(ihVersion) + " : " + titleHelp;
			}
		
			//tex: GOTCHA name acts as id by default so setting it to something dynamic like menuTitle means each submenu is a new window so it will have individual position and size if user changes it.
			//Alternative is to menuTitle + "##menuTitle"? or pushID, popID
			//if (!
			ImGui::Begin(windowTitle.c_str(), p_open, windowFlags); //tex: TODO: there's probably a better way to handle the x/close button somehow rather than this which just flips a bool
				//QueueMessageIn("togglemenu|1");
			//}

			ImGui::Text(menuTitle.c_str());
			ImGui::PushItemWidth(-1);//tex push out label

			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();

			float contentHeight = vMax.y - vMin.y;

			//DEBUG draw content bounds
			//{
			//	ImVec2 drawMin = vMin;
			//	ImVec2 drawMax = vMax;
			//	vMin.x += ImGui::GetWindowPos().x;
			//	vMin.y += ImGui::GetWindowPos().y;
			//	vMax.x += ImGui::GetWindowPos().x;
			//	vMax.y += ImGui::GetWindowPos().y;

			//	ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
			//}
			int helpHeightInItems = 4;
			if (menuHelp == "") {//tex: 'turning off help' simply sets an empty string
				helpHeightInItems = 1;//tex leave a lines worth of buffer otherwise the window drag corner icon clashes visually with the combo box
			}

			if (menuItems.size() > 0) {
				DrawList(contentHeight, helpHeightInItems);
			}//if menuItems

			ImGuiInputTextFlags inputFlags = 0;
			inputFlags |= ImGuiInputTextFlags_EnterReturnsTrue;
			inputFlags |= ImGuiInputTextFlags_AutoSelectAll;
			if (ImGui::InputText("##menuLine", inputBuffer, IM_ARRAYSIZE(inputBuffer), inputFlags)) {
				menuLine = inputBuffer;
				QueueMessageIn("EnterText|menuLine|" + menuLine);
			}
			//ImGui::Text(inputBuffer); //DEBUG

			//CULL
			///*if (menuSettings.size() == 0) {
			//	//DEBUGNOW CULL ImGui::Text("");
			//	ImGui::Selectable("menuSettingsDummy", false, 0);
			//} else*/ if (menuSettings.size() == 1) {//tex just a value
			//	ImGuiInputTextFlags settingInputFlags = 0;
			//	settingInputFlags |= ImGuiInputTextFlags_EnterReturnsTrue;
			//	if (ImGui::InputText("##menuSettingInput", settingInputBuffer, IM_ARRAYSIZE(settingInputBuffer), settingInputFlags)) {
			//		if (menuSettings.size() == 1) {
			//			menuSettings[0] = settingInputBuffer;
			//			QueueMessageIn("input|menuSetting|" + menuSettings[0]);
			//		}
			//	}
			//} else {//tex use combo box
			//	const char* comboLabel = "";// Label to preview before opening the combo (technically it could be anything)
			//	if (menuSettings.size() > 0 && selectedSetting < menuSettings.size()) {
			//		comboLabel = menuSettings[selectedSetting].c_str();
			//	}
			//	static ImGuiComboFlags flags = 0;
			//	if (ImGui::BeginCombo("##menuSettings", comboLabel, flags)) {
			//		for (int i = 0; i < menuSettings.size(); i++) {
			//			ImGui::PushID(i);
			//			bool selected = (selectedSetting == i);
			//			if (ImGui::Selectable(menuSettings[i].c_str(), selected)) {
			//				selectedSetting = i;
			//				QueueMessageIn("selectedcombo|menuSetting|" + std::to_string(selectedSetting));
			//			}

			//			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			//			if (selected) {
			//				//DEBUGNOW ImGui::SetItemDefaultFocus();
			//			}
			//			ImGui::PopID();
			//		}
			//		ImGui::EndCombo();
			//	}//if Combo
			//}//menuSetting

			//DEBUGNOW
			size_t maxItemsShown = 7;//0 == show all, but you don't get a scroll bar so it's unusable and will be off screen for large lists anyhoo
			if (TextInputComboBox("##menuSettings", settingInputBuffer, bufferSize, menuSettings, maxItemsShown)) {
				if (menuSettings.size() == 1) {
					menuSettings[0] = settingInputBuffer;
					QueueMessageIn("input|menuSetting|" + menuSettings[0]);
				}
				else {
					bool didSelect = false;
					for (int i = 0; i < menuSettings.size(); i++) {
						if (menuSettings[i].compare(settingInputBuffer) == 0) {//tex settingInputBuffer matches a setting
							selectedSetting = i;
							didSelect = true;
							QueueMessageIn("selectedcombo|menuSetting|" + std::to_string(selectedSetting));
							break;
						}
					}
					if (!didSelect) {
						QueueMessageIn("input|menuSetting|" + std::string(settingInputBuffer));
					}
				}//if menuSettings.size
			}//if TextInputComboBox

			ImGui::BeginChild("ChildHelp", ImVec2(0, ImGui::GetFontSize() * helpHeightInItems), false, 0);
			ImGui::TextWrapped("%s", menuHelp.c_str());//tex WORKAROUND: Text widget takes fmted text, so slap it in like this so it doesn't choke on stuff like %, there's also ::TextUnformatted that's more performant, but it doesn't wrap.
			ImGui::EndChild();
			
			ImGui::End();

			//ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(0, -1));//DEBUGNOW
		}//DrawMenu

		void DrawList(float contentHeight, int helpHeightInItems) {
			//float numItemsF = (contentHeight * 0.50f)/ ImGui::GetFontSize();
			float fontSize = ImGui::GetFontSize();
			float padding = 4;//tex TODO: calculate from actual padding
			float otherItems = 4;//tex menu title, setting name, setting value + 1 for a buffer
			float numItemsF = (contentHeight / (fontSize + padding)) - (otherItems + helpHeightInItems);
			int listboxHeightInItems = static_cast<int>(std::round(numItemsF));
			//listboxHeightInItems = std::min(listboxHeightInItems, (int)menuItems.size());//tex still deciding whether size menu to its number of items (this line uncommented), or to fill menu to window (this line commented out), and what to do with the bottom of the window
			if (listboxHeightInItems > 0) {
				if (ImGui::ListBoxHeader("##menuItems", (int)menuItems.size(), listboxHeightInItems)) {
					for (int i = 0; i < menuItems.size(); i++) {
						ImGui::PushItemWidth(-1);//tex push out label
						ImGui::PushID(i);//tex in theory shouldnt be a problem as menu items have a number prefixed
						bool selected = (selectedItem == i);
						//tex putting this before -v- means that ih/lua can set selectedItem (call SelectItem on keyboard scroll)
						//and have this scroll the selection into the view, but let ImGui::Selectable  //DEBUGNOW unless there's a loop with togamecmd 'selected' that calls SelectItem again?
						if (selected && prevSelectedItem != selectedItem) {
							prevSelectedItem = selectedItem;
							float center_y_ratio = 0.15f;
							if (listboxHeightInItems <= 2) {
								center_y_ratio = 1.0f;
							}
							ImGui::SetScrollHereY(center_y_ratio);
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
						//if (*p_open && *p_open != openPrev) {
							//DEBUGNOW ImGui::SetItemDefaultFocus();
							//DEBUGNOW ImGui::SetKeyboardFocusHere();
						//}
						ImGui::PopID();
					}
					ImGui::ListBoxFooter();
				}//if ListBox
			}//if listboxHeightInItems>0
		}//DrawList

		//TextInputComboBox https://github.com/ocornut/imgui/issues/2057 
		bool identical(const char* buf, const char* item) {
			size_t buf_size = strlen(buf);
			size_t item_size = strlen(item);
			//Check if the item length is shorter or equal --> exclude
			if (buf_size >= item_size) return false;
			for (int i = 0; i < strlen(buf); ++i)
				// set the current pos if matching or return the pos if not
				if (buf[i] != item[i]) return false;
			// Complete match
			// and the item size is greater --> include
			return true;
		}//identical

		int propose(ImGuiInputTextCallbackData* data) {
			//tex TODO: needs a lot more work

			//We don't want to "preselect" anything
			if (strlen(data->Buf) == 0) return 0;

			//Get our items back
			std::vector<std::string>* items = static_cast<std::vector<std::string>*> (data->UserData);
			//WORKAROUND: tex setting is a direct value, don't autocomplete cause its annoying
			if (items->size() == 0 || items->size() == 1) {
				return 0;
			}

			//We need to give the user a chance to remove wrong input
			if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Backspace))) {
				//We delete the last char automatically, since it is what the user wants to delete, but only if there is something (selected/marked/hovered)
				//FIXME: This worked fine, when not used as helper function
				if (data->SelectionEnd != data->SelectionStart)
					if (data->BufTextLen > 0) //...and the buffer isn't empty			
						if (data->CursorPos > 0) //...and the cursor not at pos 0
							data->DeleteChars(data->CursorPos - 1, 1);
				return 0;
			}
			//if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete))) return 0;

			//tex TODO: will pretty much just override deletions
			//only does exact match
			for (int i = 0; i < items->size(); i++) {
				if (identical(data->Buf, items->at(i).c_str())) {
					const int cursor = data->CursorPos;
					//Insert the first match
					data->DeleteChars(0, data->BufTextLen);
					data->InsertChars(0, items->at(i).c_str());
					//Reset the cursor position
					data->CursorPos = cursor;
					//Select the text, so the user can simply go on writing
					data->SelectionStart = cursor;
					data->SelectionEnd = data->BufTextLen;

					break;
				}
			}
			return 0;
		}//propose

		//DEBUGNOW figure this out and fold into main TextInputComboBox 
		//bool TextInputComboBox(const char* id, std::string& str, size_t maxInputSize, std::vector<std::string> items, short maxItemsShown) {
		//	if (str.size() > maxInputSize) { // too large for editing
		//		ImGui::Text(str.c_str());
		//		return false;
		//	}

		//	std::string buffer(str);
		//	buffer.resize(maxInputSize);
		//	bool changed = TextInputComboBox(id, &buffer[0], maxInputSize, items, maxItemsShown);
		//	// using string as char array
		//	if (changed) {
		//		auto i = buffer.find_first_of('\0');
		//		str = buffer.substr(0u, i);
		//	}
		//	return changed;
		//}//TextInputComboBox
	

		// Creates a ComboBox with free text input and completion proposals
		// Pass your items via items
		// maxItemsShown determines how many items are shown, when the dropdown is open; if 0 is passed the complete list will be shown; you will want normaly a value of 8
		// tex adapted from https://github.com/ocornut/imgui/issues/2057 to be kinda ihmenu specific
		bool TextInputComboBox(const char* id, char* buffer, size_t maxInputSize, std::vector<std::string> items, size_t showMaxItems) {
			//Check if both strings matches
			if (showMaxItems == 0)
				showMaxItems = items.size();

			if (showMaxItems > items.size()) {
				showMaxItems = items.size();
			}

			ImGui::PushID(id);
			//std::pair<const char**, size_t> pass(items, item_len); //We need to pass the array length as well//DEBUGNOW
			ImGui::PushItemWidth(-ImGui::GetFrameHeight());//tex decrease size by Arrow button default size
			ImGuiInputTextFlags inputFlags = 0;
			inputFlags |= ImGuiInputTextFlags_EnterReturnsTrue;
			inputFlags |= ImGuiInputTextFlags_CallbackAlways;
			bool ret = ImGui::InputText("##in", buffer, maxInputSize, inputFlags, propose, static_cast<void*>(&items));

			ImGui::OpenPopupOnItemClick("combobox"); //Enable right-click
			ImVec2 pos = ImGui::GetItemRectMin();
			ImVec2 size = ImGui::GetItemRectSize();

			ImGui::SameLine(0, 0);
			if (ImGui::ArrowButton("##openCombo", ImGuiDir_Down)) {
				ImGui::OpenPopup("combobox");
			}
			ImGui::OpenPopupOnItemClick("combobox"); //Enable right-click

			if (items.size() > 0 && selectedSetting < items.size()) {
				//strcpy_s(buffer, bufferSize, items[selectedSetting].c_str());//DEBUGNOW
			}

			float baseHeight = size.y;
			pos.y += baseHeight;
			size.x += ImGui::GetItemRectSize().x;
			size.y += 8 + (baseHeight * (showMaxItems - 1));
			//tex TODO: if bottom of popup below bottom of screen then have popup above input/selected line like vanilla comboboxes behaviour.
			ImGuiIO& io = ImGui::GetIO();
			float windowHeight = io.DisplaySize.y;
			float bottom = pos.y + size.y;
			if (bottom > windowHeight) {
				pos.y -= baseHeight;//tex undo above
				pos.y -= size.y;
			}

			ImGui::SetNextWindowPos(pos);
			ImGui::SetNextWindowSize(size);
			if (ImGui::BeginPopup("combobox", ImGuiWindowFlags_::ImGuiWindowFlags_NoMove)) {
				//ImGui::Text("Select one item or type");
				//ImGui::Separator();
				for (size_t i = 0; i < items.size(); i++) {
					int si = static_cast<int>(i);
					ImGui::PushID(si);//tex in theory shouldnt be a problem as menu items have a number prefixed
					bool selected = (selectedSetting == i);
					if (ImGui::Selectable(items[i].c_str(), selected)) {
						selectedSetting = si; //tex IHMenu
						strcpy_s(buffer, bufferSize, items[selectedSetting].c_str());//DEBUGNOW
						QueueMessageIn("selectedcombo|menuSetting|" + std::to_string(selectedSetting));//tex IHMenu
					}
					ImGui::PopID();
				}

				ImGui::EndPopup();
			}
			ImGui::PopID();
			//label
			//ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
			//ImGui::Text(id);

			return ret;
		}//TextInputComboBox

		////
	}//namespace IHMenu
}//namespace IHHook