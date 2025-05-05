//
// Created by belyashik2k on 4/27/25.
//

#ifndef IMGUIUTILS_H
#define IMGUIUTILS_H
#include <functional>
#include <imgui.h>
#include <string>

namespace ImguiUtils {
    void centerCursor(const ImVec2 &sizeOfObject) ;
    void updateBackground(const std::string & filePath);
    void createButton(
        const char *id,
        const char *label,
        const ImVec2 &size = ImVec2(0, 0),
        const std::function<void()>& onLeftClick = nullptr,
        const std::function<void()>& onRightClick = nullptr
    );
    void printText(
        const char *text,
        const ImColor &color = ImColor(255, 255, 255),
        int fontSize = 16,
        bool isCentered = false
    ) ;
    void createInputField(
        const char *id,
        const char *label,
        char *buffer,
        int bufferSize,
        const ImVec2 &size = ImVec2(0, 0),
        ImGuiInputTextFlags flags = ImGuiInputFlags_None,
        bool isLabelHidden = false
    );
    void addVerticalSpacing(int count = 1);
}

#endif //IMGUIUTILS_H
