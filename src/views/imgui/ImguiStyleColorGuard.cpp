//
// Created by belyashik2k on 4/30/25.
//

#include "views/imgui/ImguiStyleColorGuard.h"

ImguiStyleColorGuard::ImguiStyleColorGuard(const std::vector<std::pair<ImGuiCol, AvailableTypes>> &styles) {
    for (const auto& [col, color] : styles) {
        if (std::holds_alternative<ImVec4>(color)) {
            ImGui::PushStyleColor(col, std::get<ImVec4>(color));
        } else if (std::holds_alternative<ImColor>(color)) {
            const ImU32 imColor = std::get<ImColor>(color);
            ImGui::PushStyleColor(col, imColor);
        }
        count++;
    }
}


ImguiStyleColorGuard::~ImguiStyleColorGuard() {
    ImGui::PopStyleColor(count);
}
