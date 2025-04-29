//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/ImguiChildWindow.h"

ImguiChildWindow::~ImguiChildWindow() {
    if (m_Started) {
        ImGui::EndChild();
    }
}

ImguiChildWindow::ImguiChildWindow(
    const ImGuiID id,
    const ImVec2 &size,
    const ImGuiChildFlags flags
) : m_Started(false) {
    m_Started = ImGui::BeginChild(id, size, flags);
}

ImguiChildWindow::ImguiChildWindow(
    const char *str_id,
    const ImVec2 &size,
    const ImGuiChildFlags flags
) : m_Started(false) {
    m_Started = ImGui::BeginChild(str_id, size, flags);
}
