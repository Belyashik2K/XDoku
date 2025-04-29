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
public:
    static void updateBackground(const std::string & filePath);
    static void createButton(
        const char *id,
        const char *label,
        const ImVec2 & size = ImVec2(0, 0),
        const std::function<void()>& onLeftClick = nullptr,
        const std::function<void()>& onRightClick = nullptr
    );
    static void addVerticalSpacing(int count = 1);
    void render() override = 0;
};

#endif //IMGUIVIEW_H
