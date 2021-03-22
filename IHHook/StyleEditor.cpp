#include "spdlog/spdlog.h"

// save guistyle
#include <iostream>
#include <fstream>
// Parse guistyle
#include <sstream>
#include <string>

#include <filesystem>
#include "Util.h"

#include <imgui/imgui.h>

#include "IHHook.h"
#include "StyleEditor.h"

namespace IHHook {
	//Style to string>
	std::string BoolToString(bool b) {
		return b ? "true" : "false";
	}
	std::string DumpImVec2(ImVec2 imVec2) {
		return "{" + std::to_string(imVec2.x) + "," + std::to_string(imVec2.y) + "}";//DEBUGNOW decimal format depend on locale?
	}
	std::string DumpImVec4(ImVec4 imVec4) {
		return "{" + std::to_string(imVec4.x) + "," + std::to_string(imVec4.y) + "," + std::to_string(imVec4.z) + "," + std::to_string(imVec4.w) + "}";//DEBUGNOW decimal format depend on locale?
	}

	//Dumps style except for Colors
	void GetStyle(std::list<std::string>& savedStyle, ImGuiStyle* src) {
		ImGuiStyle* style = src ? src : &ImGui::GetStyle();

		savedStyle.push_back("Alpha=" + std::to_string(style->Alpha));
		savedStyle.push_back("WindowPadding=" + DumpImVec2(style->WindowPadding));
		savedStyle.push_back("WindowRounding=" + std::to_string(style->WindowRounding));
		savedStyle.push_back("WindowBorderSize=" + std::to_string(style->WindowBorderSize));
		savedStyle.push_back("WindowMinSize=" + DumpImVec2(style->WindowMinSize));
		savedStyle.push_back("WindowTitleAlign=" + DumpImVec2(style->WindowTitleAlign));
		savedStyle.push_back("WindowMenuButtonPosition=" + std::to_string(style->WindowMenuButtonPosition));
		savedStyle.push_back("ChildRounding=" + std::to_string(style->ChildRounding));
		savedStyle.push_back("ChildBorderSize=" + std::to_string(style->ChildBorderSize));
		savedStyle.push_back("PopupRounding=" + std::to_string(style->PopupRounding));
		savedStyle.push_back("PopupBorderSize=" + std::to_string(style->PopupBorderSize));
		savedStyle.push_back("FramePadding=" + DumpImVec2(style->FramePadding));
		savedStyle.push_back("FrameRounding=" + std::to_string(style->FrameRounding));
		savedStyle.push_back("FrameBorderSize=" + std::to_string(style->FrameBorderSize));
		savedStyle.push_back("ItemSpacing=" + DumpImVec2(style->ItemSpacing));
		savedStyle.push_back("ItemInnerSpacing=" + DumpImVec2(style->ItemInnerSpacing));
		savedStyle.push_back("TouchExtraPadding=" + DumpImVec2(style->TouchExtraPadding));
		savedStyle.push_back("IndentSpacing=" + std::to_string(style->IndentSpacing));
		savedStyle.push_back("ColumnsMinSpacing=" + std::to_string(style->ColumnsMinSpacing));
		savedStyle.push_back("ScrollbarSize=" + std::to_string(style->ScrollbarSize));
		savedStyle.push_back("ScrollbarRounding=" + std::to_string(style->ScrollbarRounding));
		savedStyle.push_back("GrabMinSize=" + std::to_string(style->GrabMinSize));
		savedStyle.push_back("GrabRounding=" + std::to_string(style->GrabRounding));
		savedStyle.push_back("LogSliderDeadzone=" + std::to_string(style->LogSliderDeadzone));
		savedStyle.push_back("TabRounding=" + std::to_string(style->TabRounding));
		savedStyle.push_back("TabBorderSize=" + std::to_string(style->TabBorderSize));
		savedStyle.push_back("TabMinWidthForCloseButton=" + std::to_string(style->TabMinWidthForCloseButton));
		savedStyle.push_back("ColorButtonPosition=" + std::to_string(style->ColorButtonPosition));
		savedStyle.push_back("ButtonTextAlign=" + DumpImVec2(style->ButtonTextAlign));
		savedStyle.push_back("SelectableTextAlign=" + DumpImVec2(style->SelectableTextAlign));
		savedStyle.push_back("DisplayWindowPadding=" + DumpImVec2(style->DisplayWindowPadding));
		savedStyle.push_back("DisplaySafeAreaPadding=" + DumpImVec2(style->DisplaySafeAreaPadding));
		savedStyle.push_back("MouseCursorScale=" + std::to_string(style->MouseCursorScale));
		savedStyle.push_back("AntiAliasedLines=" + BoolToString(style->AntiAliasedLines));
		savedStyle.push_back("AntiAliasedLinesUseTex=" + BoolToString(style->AntiAliasedLinesUseTex));
		savedStyle.push_back("AntiAliasedFill=" + BoolToString(style->AntiAliasedFill));
		savedStyle.push_back("CurveTessellationTol=" + std::to_string(style->CurveTessellationTol));
		savedStyle.push_back("CircleSegmentMaxError=" + std::to_string(style->CircleSegmentMaxError));

		//ImVec4      Colors[ImGuiCol_COUNT];

	}//GetStyle

	//DEBUGNOW ImGui style management
	std::vector<std::string> ImGuiCol_str{
		"ImGuiCol_Text",
		"ImGuiCol_TextDisabled",
		"ImGuiCol_WindowBg",              // Background of normal windows
		"ImGuiCol_ChildBg",               // Background of child windows
		"ImGuiCol_PopupBg",               // Background of popups, menus, tooltips windows
		"ImGuiCol_Border",
		"ImGuiCol_BorderShadow",
		"ImGuiCol_FrameBg",               // Background of checkbox, radio button, plot, slider, text input
		"ImGuiCol_FrameBgHovered",
		"ImGuiCol_FrameBgActive",
		"ImGuiCol_TitleBg",
		"ImGuiCol_TitleBgActive",
		"ImGuiCol_TitleBgCollapsed",
		"ImGuiCol_MenuBarBg",
		"ImGuiCol_ScrollbarBg",
		"ImGuiCol_ScrollbarGrab",
		"ImGuiCol_ScrollbarGrabHovered",
		"ImGuiCol_ScrollbarGrabActive",
		"ImGuiCol_CheckMark",
		"ImGuiCol_SliderGrab",
		"ImGuiCol_SliderGrabActive",
		"ImGuiCol_Button",
		"ImGuiCol_ButtonHovered",
		"ImGuiCol_ButtonActive",
		"ImGuiCol_Header",                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
		"ImGuiCol_HeaderHovered",
		"ImGuiCol_HeaderActive",
		"ImGuiCol_Separator",
		"ImGuiCol_SeparatorHovered",
		"ImGuiCol_SeparatorActive",
		"ImGuiCol_ResizeGrip",
		"ImGuiCol_ResizeGripHovered",
		"ImGuiCol_ResizeGripActive",
		"ImGuiCol_Tab",
		"ImGuiCol_TabHovered",
		"ImGuiCol_TabActive",
		"ImGuiCol_TabUnfocused",
		"ImGuiCol_TabUnfocusedActive",
		"ImGuiCol_PlotLines",
		"ImGuiCol_PlotLinesHovered",
		"ImGuiCol_PlotHistogram",
		"ImGuiCol_PlotHistogramHovered",
		"ImGuiCol_TextSelectedBg",
		"ImGuiCol_DragDropTarget",
		"ImGuiCol_NavHighlight",          // Gamepad/keyboard: current highlighted item
		"ImGuiCol_NavWindowingHighlight", // Highlight window when using CTRL+TAB
		"ImGuiCol_NavWindowingDimBg",     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
		"ImGuiCol_ModalWindowDimBg",      // Darken/colorize entire screen behind a modal window, when one is active
		"ImGuiCol_COUNT",
	};//ImGuiCol_str

	void GetColors(std::list<std::string>& savedColors, ImGuiStyle* src) {
		ImGuiStyle* style = src ? src : &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		for (int i = 0; i < ImGuiCol_COUNT; i++) {
			savedColors.push_back(ImGuiCol_str[i] + "=" + DumpImVec4(colors[i]));
		}//for ImGuiCol_COUNT
	}//GetColors

	//DEBUGNOW encoding utf8?
	void SaveGuiStyle(std::string fileName) {
		spdlog::debug("SaveGuiStyle");

		std::list<std::string> dumpedStyle{};
		GetStyle(dumpedStyle, NULL);
		std::list<std::string> dumpedColors{};
		GetColors(dumpedColors, NULL);

		std::ofstream styleFile;
		styleFile.open(fileName, std::ios::out | std::ios::trunc);

		if (styleFile.is_open()) {
			styleFile << "--" << fileName << "\n";
			styleFile << "\n";
			styleFile << "local this={\n";
			for each (std::string line in dumpedStyle) {
				styleFile << "\t" << line << ",\n";
			}
			//styleFile << "\tColors={\n";
			for each (std::string line in dumpedColors) {
				styleFile << "\t\t" << line << ",\n";
			}
			//styleFile << "\t},\n";

			styleFile << "}\n";
			styleFile << "return this\n";
		}//if styleFile
		styleFile.close();
	}//SaveGuiStyle
	//Style to string <

	//Util
		//DEBUGNOW a propper str enum
	//ASSUMPTION: consecutive enum
	int EnumForStr(const std::vector<std::string>& strEnum, std::string key) {
		for (int i = 0; i < strEnum.size(); i++) {
			if (strEnum[i] == key) {
				return i;
			}
		}
		return -1;
	}//EnumForStr

	//String to style>
	//REF {1.000000,1.000000,1.000000,1.000000}
	//for any number of values
	//FRAGILE: does not handle no whitespace
	std::vector<std::string> ParseLuaValueArray(std::string valueStr) {
		valueStr = valueStr.substr(1, valueStr.size() - 2);//strip leading { trailing }
		return split(valueStr, ",");
	}//ParseLuaValueArray

	//REF {1.000000,1.000000}
	ImVec2 ParseImVec2(std::string valueStr) {
		std::vector<std::string> values = ParseLuaValueArray(valueStr);
		float x = std::stof(values[0]);
		float y = std::stof(values[1]);
		return ImVec2(x, y);
	}//ParseImVec2

	//REF {1.000000,1.000000,1.000000,1.000000}
	ImVec4 ParseImVec4(std::string valueStr) {
		std::vector<std::string> values = ParseLuaValueArray(valueStr);
		float x = std::stof(values[0]);
		float y = std::stof(values[1]);
		float z = std::stof(values[2]);
		float w = std::stof(values[3]);
		return ImVec4(x, y, z, w);
	}//ParseImVec4

	bool ParseBool(std::string valueStr) {
		if (valueStr == "true") {
			return true;
		}
		else {
			return false;
		}
	}//ParseBool

	//REF
	//--styledumptest.lua
	//--saved by gui style editor
	//local this={
	//	Alpha=1.000000,
	//	WindowPadding={8.000000,8.000000},
	//	ColorButtonPosition=1,
	//	ButtonTextAlign={0.500000,0.500000},
	//	DisplaySafeAreaPadding={3.000000,3.000000},
	//	MouseCursorScale=1.000000,
	//	AntiAliasedLines=true,
	//	AntiAliasedFill=true,
	//	--Colors array
	//	ImGuiCol_Text={1.000000,1.0000001.000000,1.000000},
	//	ImGuiCol_TextDisabled={0.500000,0.5000000.500000,1.000000},
	//	ImGuiCol_WindowBg={0.060000,0.0600000.060000,0.940000},
	//}
	//return this

	//tex: even though it's saved as valid lua, we'll just parse it as text on IHHook side rather than dealing with back and forth through lua
	bool ParseGuiStyle(std::string fileName, ImGuiStyle* ref) {
		std::ifstream infile(fileName);
		if (infile.fail()) {
			spdlog::warn("ParseGuiStyle ifstream.fail for {}", fileName);
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

			//tex ugh
			if (varName == "Alpha") {
				ref->Alpha = std::stof(valueStr);
			}
			else if (varName == "WindowPadding") {
				ref->WindowPadding = ParseImVec2(valueStr);
			}
			else if (varName == "WindowRounding") {
				ref->WindowRounding = std::stof(valueStr);
			}
			else if (varName == "WindowBorderSize") {
				ref->WindowBorderSize = std::stof(valueStr);
			}
			else if (varName == "WindowMinSize") {
				ref->WindowMinSize = ParseImVec2(valueStr);
			}
			else if (varName == "WindowTitleAlign") {
				ref->WindowTitleAlign = ParseImVec2(valueStr);
			}
			else if (varName == "WindowMenuButtonPosition") {
				ref->WindowMenuButtonPosition = std::stoi(valueStr);
			}
			else if (varName == "ChildRounding") {
				ref->ChildRounding = std::stof(valueStr);
			}
			else if (varName == "ChildBorderSize") {
				ref->ChildBorderSize = std::stof(valueStr);
			}
			else if (varName == "PopupRounding") {
				ref->PopupRounding = std::stof(valueStr);
			}
			else if (varName == "PopupBorderSize") {
				ref->PopupBorderSize = std::stof(valueStr);
			}
			else if (varName == "FramePadding") {
				ref->FramePadding = ParseImVec2(valueStr);
			}
			else if (varName == "FrameRounding") {
				ref->FrameRounding = std::stof(valueStr);
			}
			else if (varName == "FrameBorderSize") {
				ref->FrameBorderSize = std::stof(valueStr);
			}
			else if (varName == "ItemSpacing") {
				ref->ItemSpacing = ParseImVec2(valueStr);
			}
			else if (varName == "ItemInnerSpacing") {
				ref->ItemInnerSpacing = ParseImVec2(valueStr);
			}
			else if (varName == "TouchExtraPadding") {
				ref->TouchExtraPadding = ParseImVec2(valueStr);
			}
			else if (varName == "IndentSpacing") {
				ref->IndentSpacing = std::stof(valueStr);
			}
			else if (varName == "ColumnsMinSpacing") {
				ref->ColumnsMinSpacing = std::stof(valueStr);
			}
			else if (varName == "ScrollbarSize") {
				ref->ScrollbarSize = std::stof(valueStr);
			}
			else if (varName == "ScrollbarRounding") {
				ref->ScrollbarRounding = std::stof(valueStr);
			}
			else if (varName == "GrabMinSize") {
				ref->GrabMinSize = std::stof(valueStr);
			}
			else if (varName == "GrabRounding") {
				ref->GrabRounding = std::stof(valueStr);
			}
			else if (varName == "LogSliderDeadzone") {
				ref->LogSliderDeadzone = std::stof(valueStr);
			}
			else if (varName == "TabRounding") {
				ref->TabRounding = std::stof(valueStr);
			}
			else if (varName == "TabBorderSize") {
				ref->TabBorderSize = std::stof(valueStr);
			}
			else if (varName == "TabMinWidthForCloseButton") {
				ref->TabMinWidthForCloseButton = std::stof(valueStr);
			}
			else if (varName == "ColorButtonPosition") {
				ref->ColorButtonPosition = std::stoi(valueStr);
			}
			else if (varName == "ButtonTextAlign") {
				ref->ButtonTextAlign = ParseImVec2(valueStr);
			}
			else if (varName == "SelectableTextAlign") {
				ref->SelectableTextAlign = ParseImVec2(valueStr);
			}
			else if (varName == "DisplayWindowPadding") {
				ref->DisplayWindowPadding = ParseImVec2(valueStr);
			}
			else if (varName == "DisplaySafeAreaPadding") {
				ref->DisplaySafeAreaPadding = ParseImVec2(valueStr);
			}
			else if (varName == "MouseCursorScale") {
				ref->MouseCursorScale = std::stof(valueStr);
			}
			else if (varName == "AntiAliasedLines") {
				ref->AntiAliasedLines = ParseBool(valueStr);
			}
			else if (varName == "AntiAliasedLinesUseTex") {
				ref->AntiAliasedLinesUseTex = ParseBool(valueStr);
			}
			else if (varName == "AntiAliasedFill") {
				ref->AntiAliasedFill = ParseBool(valueStr);
			}
			else if (varName == "CurveTessellationTol") {
				ref->CurveTessellationTol = std::stof(valueStr);
			}
			else if (varName == "CircleSegmentMaxError") {
				ref->CircleSegmentMaxError = std::stof(valueStr);
			}
			else {
				int ImGuiCol = EnumForStr(ImGuiCol_str, varName);
				if (ImGuiCol != -1) {
					ImVec4 color = ParseImVec4(valueStr);
					ref->Colors[ImGuiCol] = color;
				}
			}
		}//while line

		return true;
	}//ParseGuiStyle
	//String to style<

	//DEBUGNOW
	//style editor windows>
	std::string stylesPath = "mod\\guiStyles\\";

	int selectedSetting = -1;
	std::vector<std::filesystem::path> fileList{};
	char inputBuffer[1024] = "";//SaveBox
	bool showSaveBox = false;

	//IN: stylesPath
	//OUT: fileList, selectedSetting
	void RefreshFileList() {
		int prevNumFiles = fileList.size();
		fileList.clear();

		if (!std::filesystem::exists(stylesPath)) {
			spdlog::error("RefreshFileList: path does not exist: {}", stylesPath);
			//DEBUGNOW user facing error
			selectedSetting = -1;
			return;
		}

		for (const auto& entry : std::filesystem::directory_iterator(stylesPath)) {
			if (entry.path().extension() == ".lua") {
				fileList.push_back(entry.path());
			}
		}

		int numFiles = fileList.size();
		if (numFiles == 0) {
			selectedSetting = -1;
		}
		else if (numFiles != prevNumFiles) {
			selectedSetting = 0;
		}
	}//RefreshFileList

	// Helper to display a little (?) mark which shows a tooltip when hovered.
	// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
	static void HelpMarker(const char* desc) {
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}//HelpMarker

	static void ShowSaveBox(bool* p_open) {
		ImGui::SetNextWindowSize(ImVec2(300, 100));
		if (!ImGui::Begin("Save style", p_open)) {
			ImGui::End();
			return;
		}

		ImGuiInputTextFlags inputFlags = 0;
		inputFlags |= ImGuiInputTextFlags_EnterReturnsTrue;
		if (ImGui::InputText("file name", inputBuffer, IM_ARRAYSIZE(inputBuffer), inputFlags)) {
			std::string fileName(inputBuffer);
			if (fileName != "" && fileName != "Default") {
				SaveGuiStyle(stylesPath + fileName + ".lua");
				RefreshFileList();
				*p_open = false;
			}
		}//InputText

		std::string fileName(inputBuffer);
		bool modifyOK = fileName != "" && fileName != "Default";
		if (!modifyOK) {
			//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}
		if (ImGui::Button("Save")) {
			
			if (fileName != "" && fileName != "Default") {
				SaveGuiStyle(stylesPath + fileName + ".lua");
				RefreshFileList();
				*p_open = false;
			}
		}//Button Save
		if (!modifyOK) {
			//ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			*p_open = false;
		}//Button Cancel
		ImGui::SameLine();
		HelpMarker(std::string("Styles are saved to " + stylesPath).c_str());

		ImGui::End();
	}//ShowSaveBox

	// Play it nice with Windows users (Update: May 2018, Notepad now supports Unix-style carriage returns!)
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif

	// [Internal] Display details for a single font, called by ShowStyleEditor().
	static void NodeFont(ImFont* font) {
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		bool font_details_opened = ImGui::TreeNode(font, "Font: \"%s\"\n%.2f px, %d glyphs, %d file(s)",
			font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
		ImGui::SameLine(); if (ImGui::SmallButton("Set as default")) { io.FontDefault = font; }
		if (!font_details_opened)
			return;

		ImGui::PushFont(font);
		ImGui::Text("The quick brown fox jumps over the lazy dog");
		ImGui::PopFont();
		ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
		ImGui::SameLine(); HelpMarker(
			"Note than the default embedded font is NOT meant to be scaled.\n\n"
			"Font are currently rendered into bitmaps at a given size at the time of building the atlas. "
			"You may oversample them to get some flexibility with scaling. "
			"You can also render at multiple sizes and select which one to use at runtime.\n\n"
			"(Glimmer of hope: the atlas system will be rewritten in the future to make scaling more flexible.)");
		ImGui::Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
		ImGui::Text("Fallback character: '%c' (U+%04X)", font->FallbackChar, font->FallbackChar);
		ImGui::Text("Ellipsis character: '%c' (U+%04X)", font->EllipsisChar, font->EllipsisChar);
		const int surface_sqrt = (int)sqrtf((float)font->MetricsTotalSurface);
		ImGui::Text("Texture Area: about %d px ~%dx%d px", font->MetricsTotalSurface, surface_sqrt, surface_sqrt);
		for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
			if (font->ConfigData)
				if (const ImFontConfig* cfg = &font->ConfigData[config_i])
					ImGui::BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d, Offset: (%.1f,%.1f)",
						config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH, cfg->GlyphOffset.x, cfg->GlyphOffset.y);
		if (ImGui::TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size)) {
			// Display all glyphs of the fonts in separate pages of 256 characters
			const ImU32 glyph_col = ImGui::GetColorU32(ImGuiCol_Text);
			for (unsigned int base = 0; base <= IM_UNICODE_CODEPOINT_MAX; base += 256) {
				// Skip ahead if a large bunch of glyphs are not present in the font (test in chunks of 4k)
				// This is only a small optimization to reduce the number of iterations when IM_UNICODE_MAX_CODEPOINT
				// is large // (if ImWchar==ImWchar32 we will do at least about 272 queries here)
				if (!(base & 4095) && font->IsGlyphRangeUnused(base, base + 4095)) {
					base += 4096 - 256;
					continue;
				}

				int count = 0;
				for (unsigned int n = 0; n < 256; n++)
					if (font->FindGlyphNoFallback((ImWchar)(base + n)))
						count++;
				if (count <= 0)
					continue;
				if (!ImGui::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
					continue;
				float cell_size = font->FontSize * 1;
				float cell_spacing = style.ItemSpacing.y;
				ImVec2 base_pos = ImGui::GetCursorScreenPos();
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				for (unsigned int n = 0; n < 256; n++) {
					// We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions
					// available here and thus cannot easily generate a zero-terminated UTF-8 encoded string.
					ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size + cell_spacing), base_pos.y + (n / 16) * (cell_size + cell_spacing));
					ImVec2 cell_p2(cell_p1.x + cell_size, cell_p1.y + cell_size);
					const ImFontGlyph* glyph = font->FindGlyphNoFallback((ImWchar)(base + n));
					draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255, 255, 255, 100) : IM_COL32(255, 255, 255, 50));
					if (glyph)
						font->RenderChar(draw_list, cell_size, cell_p1, glyph_col, (ImWchar)(base + n));
					if (glyph && ImGui::IsMouseHoveringRect(cell_p1, cell_p2)) {
						ImGui::BeginTooltip();
						ImGui::Text("Codepoint: U+%04X", base + n);
						ImGui::Separator();
						ImGui::Text("Visible: %d", glyph->Visible);
						ImGui::Text("AdvanceX: %.1f", glyph->AdvanceX);
						ImGui::Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
						ImGui::Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
						ImGui::EndTooltip();
					}
				}
				ImGui::Dummy(ImVec2((cell_size + cell_spacing) * 16, (cell_size + cell_spacing) * 16));
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}//NodeFont

	//tex REWORKED imgui_demo to allow load/save
	void ShowStyleEditor(ImGuiStyle* ref) {
		//tex>
		if (showSaveBox) {
			ShowSaveBox(&showSaveBox);//DEBUGNOW
		}

		// DEBUGNOW if (showStyleEditorPrev == false) {
		//showStyleEditorPrev=true;
		//RefreshFileList();
		//< tex

		// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to
		// (without a reference style pointer, we will use one compared locally as a reference)
		ImGuiStyle& style = ImGui::GetStyle();
		static ImGuiStyle ref_saved_style;

		// Default to using internal storage as reference
		static bool init = true;
		if (init && ref == NULL)
			ref_saved_style = style;
		init = false;
		if (ref == NULL)
			ref = &ref_saved_style;

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

		//DEBUGNOW HIDE once refresh on open
		if (ImGui::Button("Refresh List")) {
			RefreshFileList();
		}

		//tex >DEBUGNOW
		std::string comboLabel = "";// Label to preview before opening the combo (technically it could be anything)
		if (fileList.size() > 0 && selectedSetting < fileList.size()) {
			comboLabel = fileList[selectedSetting].stem().string();
		}
		static ImGuiComboFlags flags = 0;
		if (ImGui::BeginCombo("Styles", comboLabel.c_str(), flags)) {
			for (int i = 0; i < fileList.size(); i++) {
				ImGui::PushID(i);
				bool selected = (selectedSetting == i);
				std::string name = fileList[i].stem().string();
				if (ImGui::Selectable(name.c_str(), selected)) {
					selectedSetting = i;
					//load
					std::string fileName = fileList[selectedSetting].string();
					bool ok = ParseGuiStyle(fileName, ref);//tex DEBUGNOW sets the saved ref? pass in style to set current?
					if (ok) {
						style = *ref;
					}
					//DEBUGNOW if (!ok) { name = <fileName> - Load Failed }
					//but need it to persist
				}//if IMGui::Selectable
				ImGui::PopID();
			}
			ImGui::EndCombo();
		}//if Combo

		bool modifyOK = false;
		std::string fileName = "";
		if (selectedSetting >= 0 && selectedSetting < fileList.size()) {
			fileName = fileList[selectedSetting].string();
			if (fileList[selectedSetting].stem().string() != "Default") {
				modifyOK = true;
			}
		}
		//WORKAROUND: https://github.com/ocornut/imgui/issues/1889
		if (!modifyOK) {
			//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}
		if (ImGui::Button("Save")) {
			if (modifyOK && fileName != "") {
				SaveGuiStyle(fileName);
			}
		}//Button Save
		if (!modifyOK) {
			//ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}
		ImGui::SameLine();
		if (ImGui::Button("Save As..")) {
			showSaveBox = true;
		}
		ImGui::SameLine();
		if (!modifyOK) {
			//ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}
		if (ImGui::Button("Delete")) {
			if (modifyOK && fileName != "") {
				auto path = fileList[selectedSetting];
				std::error_code ec;
				std::filesystem::remove(path, ec);
				RefreshFileList();
			}
		}//Button Delete
		if (!modifyOK) {
			//ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}
		//< tex


		//ORIG
		/*
		if (ImGui::Button("Save Ref"))
			*ref = ref_saved_style = style;
		ImGui::SameLine();
		if (ImGui::Button("Revert Ref"))
			style = *ref;
		ImGui::SameLine();
		HelpMarker(
			"Save/Revert in local non-persistent storage. Default Colors definition are not affected. "
			"Use \"Export\" below to save them somewhere.");
		*/

		ImGui::Separator();

		//DEBUGNOW HIDE
		if (ImGui::ShowStyleSelector("Colors##Selector"))
			ref_saved_style = style;
		//OFF ImGui::ShowFontSelector("Fonts##Selector"); //tex no much sense showing this unless I actually add a font loading system

		// Simplified Settings (expose floating-pointer border sizes as boolean representing 0.0f or 1.0f)
		if (ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
			style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
		{ bool border = (style.WindowBorderSize > 0.0f); if (ImGui::Checkbox("WindowBorder", &border)) { style.WindowBorderSize = border ? 1.0f : 0.0f; } }
		ImGui::SameLine();
		{ bool border = (style.FrameBorderSize > 0.0f);  if (ImGui::Checkbox("FrameBorder", &border)) { style.FrameBorderSize = border ? 1.0f : 0.0f; } }
		ImGui::SameLine();
		{ bool border = (style.PopupBorderSize > 0.0f);  if (ImGui::Checkbox("PopupBorder", &border)) { style.PopupBorderSize = border ? 1.0f : 0.0f; } }

		ImGui::Separator();

		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None)) {
			if (ImGui::BeginTabItem("Sizes")) {
				ImGui::Text("Main");
				ImGui::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
				ImGui::SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
				ImGui::SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
				ImGui::SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
				ImGui::SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
				ImGui::SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
				ImGui::SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
				ImGui::SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
				ImGui::Text("Borders");
				ImGui::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
				ImGui::SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
				ImGui::SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
				ImGui::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
				ImGui::SliderFloat("TabBorderSize", &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
				ImGui::Text("Rounding");
				ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("LogSliderDeadzone", &style.LogSliderDeadzone, 0.0f, 12.0f, "%.0f");
				ImGui::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");
				ImGui::Text("Alignment");
				ImGui::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
				int window_menu_button_position = style.WindowMenuButtonPosition + 1;
				if (ImGui::Combo("WindowMenuButtonPosition", (int*)&window_menu_button_position, "None\0Left\0Right\0"))
					style.WindowMenuButtonPosition = window_menu_button_position - 1;
				ImGui::Combo("ColorButtonPosition", (int*)&style.ColorButtonPosition, "Left\0Right\0");
				ImGui::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
				ImGui::SameLine(); HelpMarker("Alignment applies when a button is larger than its text content.");
				ImGui::SliderFloat2("SelectableTextAlign", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f");
				ImGui::SameLine(); HelpMarker("Alignment applies when a selectable is larger than its text content.");
				ImGui::Text("Safe Area Padding");
				ImGui::SameLine(); HelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
				ImGui::SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Colors")) {
				static int output_dest = 0;
				static bool output_only_modified = true;
				if (ImGui::Button("Export")) {
					if (output_dest == 0)
						ImGui::LogToClipboard();
					else
						ImGui::LogToTTY();
					ImGui::LogText("ImVec4* colors = ImGui::GetStyle().Colors;" IM_NEWLINE);
					for (int i = 0; i < ImGuiCol_COUNT; i++) {
						const ImVec4& col = style.Colors[i];
						const char* name = ImGui::GetStyleColorName(i);
						if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(ImVec4)) != 0)
							ImGui::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE,
								name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
					}
					ImGui::LogFinish();
				}
				ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0");
				ImGui::SameLine(); ImGui::Checkbox("Only Modified Colors", &output_only_modified);

				static ImGuiTextFilter filter;
				filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

				static ImGuiColorEditFlags alpha_flags = 0;
				if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None)) { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
				if (ImGui::RadioButton("Alpha", alpha_flags == ImGuiColorEditFlags_AlphaPreview)) { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
				if (ImGui::RadioButton("Both", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();
				HelpMarker(
					"In the color list:\n"
					"Left-click on colored square to open color picker,\n"
					"Right-click to open edit options menu.");

				ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
				ImGui::PushItemWidth(-160);
				for (int i = 0; i < ImGuiCol_COUNT; i++) {
					const char* name = ImGui::GetStyleColorName(i);
					if (!filter.PassFilter(name))
						continue;
					ImGui::PushID(i);
					ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
					if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0) {
						// Tips: in a real user application, you may want to merge and use an icon font into the main font,
						// so instead of "Save"/"Revert" you'd use icons!
						// Read the FAQ and docs/FONTS.md about using icon fonts. It's really easy and super convenient!
						ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Save")) { ref->Colors[i] = style.Colors[i]; }
						ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Revert")) { style.Colors[i] = ref->Colors[i]; }
					}
					ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
					ImGui::TextUnformatted(name);
					ImGui::PopID();
				}
				ImGui::PopItemWidth();
				ImGui::EndChild();

				ImGui::EndTabItem();
			}

			/* //tex OFF DEBUGNOW think this through
			if (ImGui::BeginTabItem("Fonts")) {
				ImGuiIO& io = ImGui::GetIO();
				ImFontAtlas* atlas = io.Fonts;
				HelpMarker("Read FAQ and docs/FONTS.md for details on font loading.");
				ImGui::PushItemWidth(120);
				for (int i = 0; i < atlas->Fonts.Size; i++) {
					ImFont* font = atlas->Fonts[i];
					ImGui::PushID(font);
					NodeFont(font);
					ImGui::PopID();
				}
				if (ImGui::TreeNode("Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight)) {
					ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
					ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
					ImGui::Image(atlas->TexID, ImVec2((float)atlas->TexWidth, (float)atlas->TexHeight), ImVec2(0, 0), ImVec2(1, 1), tint_col, border_col);
					ImGui::TreePop();
				}

				// Post-baking font scaling. Note that this is NOT the nice way of scaling fonts, read below.
				// (we enforce hard clamping manually as by default DragFloat/SliderFloat allows CTRL+Click text to get out of bounds).
				const float MIN_SCALE = 0.3f;
				const float MAX_SCALE = 2.0f;
				HelpMarker(
					"Those are old settings provided for convenience.\n"
					"However, the _correct_ way of scaling your UI is currently to reload your font at the designed size, "
					"rebuild the font atlas, and call style.ScaleAllSizes() on a reference ImGuiStyle structure.\n"
					"Using those settings here will give you poor quality results.");
				static float window_scale = 1.0f;
				if (ImGui::DragFloat("window scale", &window_scale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp)) // Scale only this window
					ImGui::SetWindowFontScale(window_scale);
				ImGui::DragFloat("global scale", &io.FontGlobalScale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp); // Scale everything
				ImGui::PopItemWidth();

				ImGui::EndTabItem();
			}
			*/

			if (ImGui::BeginTabItem("Rendering")) {
				ImGui::Checkbox("Anti-aliased lines", &style.AntiAliasedLines);
				ImGui::SameLine();
				HelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");

				ImGui::Checkbox("Anti-aliased lines use texture", &style.AntiAliasedLinesUseTex);
				ImGui::SameLine();
				HelpMarker("Faster lines using texture data. Require back-end to render with bilinear filtering (not point/nearest filtering).");

				ImGui::Checkbox("Anti-aliased fill", &style.AntiAliasedFill);
				ImGui::PushItemWidth(100);
				ImGui::DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, 10.0f, "%.2f");
				if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;

				// When editing the "Circle Segment Max Error" value, draw a preview of its effect on auto-tessellated circles.
				ImGui::DragFloat("Circle Segment Max Error", &style.CircleSegmentMaxError, 0.01f, 0.10f, 10.0f, "%.2f");
				if (ImGui::IsItemActive()) {
					ImGui::SetNextWindowPos(ImGui::GetCursorScreenPos());
					ImGui::BeginTooltip();
					ImVec2 p = ImGui::GetCursorScreenPos();
					ImDrawList* draw_list = ImGui::GetWindowDrawList();
					float RAD_MIN = 10.0f, RAD_MAX = 80.0f;
					float off_x = 10.0f;
					for (int n = 0; n < 7; n++) {
						const float rad = RAD_MIN + (RAD_MAX - RAD_MIN) * (float)n / (7.0f - 1.0f);
						draw_list->AddCircle(ImVec2(p.x + off_x + rad, p.y + RAD_MAX), rad, ImGui::GetColorU32(ImGuiCol_Text), 0);
						off_x += 10.0f + rad * 2.0f;
					}
					ImGui::Dummy(ImVec2(off_x, RAD_MAX * 2.0f));
					ImGui::EndTooltip();
				}
				ImGui::SameLine();
				HelpMarker("When drawing circle primitives with \"num_segments == 0\" tesselation will be calculated automatically.");

				ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
				ImGui::PopItemWidth();

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::PopItemWidth();
	}//ShowStyleEditor
	//style editor windows<
}//namespace IHHook