//
// Created by belyashik2k on 4/30/25.
//

#include "views/imgui/ImguiStyleColorGuard.h"

ImguiStyleColorGuard::ImguiStyleColorGuard(const std::vector<std::pair<ImGuiCol, AvailableTypes>> &styles) {
    for (const auto& [col, color] : styles) {
        ImGui::PushStyleColor(col, color);
        count++;
    }
}


ImguiStyleColorGuard::~ImguiStyleColorGuard() {
    ImGui::PopStyleColor(count);
}
