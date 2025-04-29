//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUIWINDOW_H
#define IMGUIWINDOW_H
#include <imgui.h>

class ImguiWindow {
public:
    explicit ImguiWindow(
        const char *name,
        ImGuiWindowFlags flags = ImGuiWindowFlags_None,
        bool *p_open = nullptr
    );

    ~ImguiWindow();

    ImguiWindow(const ImguiWindow &) = delete;
    ImguiWindow &operator=(const ImguiWindow &) = delete;
private:
    const char *m_Name;
    ImGuiWindowFlags m_Flags;
    bool *m_Open = nullptr;
    bool m_DefaultOpenState = true;
};

#endif //IMGUIWINDOW_H
