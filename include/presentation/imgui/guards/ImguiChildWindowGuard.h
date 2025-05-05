//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUICHILDWINDOWGUARD_H
#define IMGUICHILDWINDOWGUARD_H

#include <imgui.h>

class ImguiChildWindowGuard {
public:
    explicit ImguiChildWindowGuard(const char *str_id, const ImVec2 &size = ImVec2(0, 0),
                              ImGuiChildFlags flags = ImGuiChildFlags_None, bool isCentered = false);

    explicit ImguiChildWindowGuard(ImGuiID id, const ImVec2 &size = ImVec2(0, 0),
                              ImGuiChildFlags flags = ImGuiChildFlags_None, bool isCentered = false);

    ~ImguiChildWindowGuard();

    explicit operator bool() const { return m_Started; }

    ImguiChildWindowGuard(const ImguiChildWindowGuard &) = delete;

    ImguiChildWindowGuard &operator=(const ImguiChildWindowGuard &) = delete;

private:
    static ImVec2 getGlobalWindowSize();

    static void setCentered(const ImVec2 &size);

    bool m_Started;
};

#endif //IMGUICHILDWINDOWGUARD_H
