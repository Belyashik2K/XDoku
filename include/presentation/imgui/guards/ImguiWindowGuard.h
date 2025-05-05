//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUIWINDOWGUARD_H
#define IMGUIWINDOWGUARD_H
#include <imgui.h>

class ImguiWindowGuard {
public:
    explicit ImguiWindowGuard(
        const char *name,
        ImGuiWindowFlags flags = ImGuiWindowFlags_None,
        bool *p_open = nullptr
    );

    ~ImguiWindowGuard();

    ImguiWindowGuard(const ImguiWindowGuard &) = delete;
    ImguiWindowGuard &operator=(const ImguiWindowGuard &) = delete;
private:
    const char *m_Name;
    ImGuiWindowFlags m_Flags;
    bool *m_Open = nullptr;
    bool m_DefaultOpenState = true;
};

#endif //IMGUIWINDOWGUARD_H
