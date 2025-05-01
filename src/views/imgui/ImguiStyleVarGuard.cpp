//
// Created by belyashik2k on 4/30/25.
//

#include "views/imgui/ImguiStyleVarGuard.h"

#include <variant>

ImguiStyleVarGuard::ImguiStyleVarGuard(const std::vector<std::pair<ImGuiStyleVar, AvailableTypes> > &styles) {
    for (const auto& [var, value] : styles) {
        if (std::holds_alternative<ImVec2>(value)) {
            ImGui::PushStyleVar(var, std::get<ImVec2>(value));
        } else if (std::holds_alternative<float>(value)) {
            ImGui::PushStyleVar(var, std::get<float>(value));
        }
        count++;
    }
}

ImguiStyleVarGuard::~ImguiStyleVarGuard()  {
    ImGui::PopStyleVar(count);
}

