//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/ImguiChildWindow.h"

ImguiChildWindow::~ImguiChildWindow() {
    if (m_Started) {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }
}

ImguiChildWindow::ImguiChildWindow(
    const ImGuiID id,
    const ImVec2 &size,
    const ImGuiChildFlags flags,
    const bool isCentered
) : m_Started(false) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (isCentered) {
        setCentered(size);
    }
    m_Started = ImGui::BeginChild(id, size, flags);
}

ImguiChildWindow::ImguiChildWindow(
    const char *str_id,
    const ImVec2 &size,
    const ImGuiChildFlags flags,
    const bool isCentered
) : m_Started(false) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (isCentered) {
        setCentered(size);
    }
    m_Started = ImGui::BeginChild(str_id, size, flags);
}

ImVec2 ImguiChildWindow::getGlobalWindowSize() {
    return ImGui::GetWindowSize();
}


void ImguiChildWindow::setCentered(const ImVec2 &size) {
    const ImVec2 windowSize = getGlobalWindowSize();
    ImVec2 childPosition;
    childPosition.x = (windowSize.x - size.x) * 0.5f;
    childPosition.y = (windowSize.y - size.y) * 0.5f;
    ImGui::SetCursorPos(childPosition);
}
