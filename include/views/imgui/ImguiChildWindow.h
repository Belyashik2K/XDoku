//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUICHILDWINDOW_H
#define IMGUICHILDWINDOW_H

#include <imgui.h>

class ImguiChildWindow {
public:
    explicit ImguiChildWindow(const char *str_id, const ImVec2 &size = ImVec2(0, 0),
                              ImGuiChildFlags flags = ImGuiChildFlags_None, bool isCentered = false);

    explicit ImguiChildWindow(ImGuiID id, const ImVec2 &size = ImVec2(0, 0),
                              ImGuiChildFlags flags = ImGuiChildFlags_None, bool isCentered = false);

    ~ImguiChildWindow();

    explicit operator bool() const { return m_Started; }

    ImguiChildWindow(const ImguiChildWindow &) = delete;

    ImguiChildWindow &operator=(const ImguiChildWindow &) = delete;

private:
    static ImVec2 getGlobalWindowSize();

    static void setCentered(const ImVec2 &size);

    bool m_Started;
};

#endif //IMGUICHILDWINDOW_H
