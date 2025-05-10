//
// Created by belyashik2k on 4/29/25.
//


#include <cstdio>
#include <presentation/imgui/guards/ImguiChildWindowGuard.h>

ImguiChildWindowGuard::~ImguiChildWindowGuard() {
    if (m_Started) {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }
}

ImguiChildWindowGuard::ImguiChildWindowGuard(
    const ImGuiID id,
    const ImVec2 &size,
    const ImGuiChildFlags flags,
    const bool isCentered
) : m_Started(false) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (isCentered) {
        setCentered(size);
    }
    m_Started = ImGui::BeginChild(id, size, flags, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
}


ImguiChildWindowGuard::ImguiChildWindowGuard(
    const char *str_id,
    const ImVec2 &size,
    const ImGuiChildFlags flags,
    const bool isCentered
) : m_Started(false) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (isCentered) {
        setCentered(size);
    }
    m_Started = ImGui::BeginChild(str_id, size, flags, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
}

ImVec2 ImguiChildWindowGuard::getGlobalWindowSize() {
    return ImGui::GetWindowSize();
}


void ImguiChildWindowGuard::setCentered(const ImVec2 &size) {
    const ImVec2 windowSize = getGlobalWindowSize();
    ImVec2 childPosition;
    childPosition.x = (windowSize.x - size.x) * 0.5f;
    childPosition.y = (windowSize.y - size.y) * 0.5f;
    ImGui::SetCursorPos(childPosition);
}
