//
// Created by belyashik2k on 4/27/25.
//

#ifndef IMGUIVIEW_H
#define IMGUIVIEW_H
#include <functional>
#include <imgui.h>
#include <string>

#include "core/IView.h"

class IImguiView : public IView {
    static void centerCursor(const ImVec2 &sizeOfObject) ;
public:
    static void updateBackground(const std::string & filePath);
    static void createButton(
        const char *id,
        const char *label,
        const ImVec2 &size = ImVec2(0, 0),
        const std::function<void()>& onLeftClick = nullptr,
        const std::function<void()>& onRightClick = nullptr
    );
    static void printText(
        const char *text,
        const ImColor &color = ImColor(255, 255, 255),
        int fontSize = 16,
        bool isCentered = false
    ) ;
    static void createInputField(
        const char *id,
        const char *label,
        char *buffer,
        int bufferSize,
        const ImVec2 &size = ImVec2(0, 0),
        ImGuiInputTextFlags flags = ImGuiInputFlags_None,
        bool isLabelHidden = false
    );
    static void addVerticalSpacing(int count = 1);

    void render() override = 0;
};

#endif //IMGUIVIEW_H
