#include "views/imgui/ImguiWindow.h"
//
// Created by belyashik2k on 4/29/25.
//
ImguiWindow::ImguiWindow(
    const char *name,
    const ImGuiWindowFlags flags,
    bool *p_open
) : m_Name(name), m_Flags(flags | ImGuiWindowFlags_NoSavedSettings), m_Open(p_open) {
    ImGui::Begin(m_Name, m_Open ? m_Open : &m_DefaultOpenState, m_Flags);
}

ImguiWindow::~ImguiWindow() {
    ImGui::End();
}
