//
// Created by belyashik2k on 4/29/25.
//

#include <presentation/imgui/guards/ImguiWindowGuard.h>

ImguiWindowGuard::ImguiWindowGuard(
    const char *name,
    const ImGuiWindowFlags flags,
    bool *p_open
) : m_Name(name),
    m_Flags(
        flags | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoDecoration),
    m_Open(p_open) {
    ImGui::Begin(m_Name, m_Open ? m_Open : &m_DefaultOpenState, m_Flags);
}

ImguiWindowGuard::~ImguiWindowGuard() {
    ImGui::End();
}
