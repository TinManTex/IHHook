#pragma once

#include <imgui/imgui.h>

namespace IHHook {
	void ShowStyleEditor(bool* p_open, bool openPrev, ImGuiStyle* ref);
	void LoadSelectedInitial(ImGuiStyle* ref);
}//namespace IHHook