//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUIWINDOWHANDLER_H
#define IMGUIWINDOWHANDLER_H
#include <string>
#include <GLFW/glfw3.h>

#include "core/IWindowHandler.h"

class ImguiWindowHandler final : public IWindowHandler {
public:
    ImguiWindowHandler(
        int width,
        int height,
        const std::string &title
    );

    explicit ImguiWindowHandler(
        const std::string &title
    );

    void run(std::function<void()> renderCallback) override;

    void shutdown() override;

private:
    void init();

    void createWindow();

    GLFWwindow *window;
    std::optional<int> windowWidth, windowHeight;
    std::string windowTitle;
};

#endif //IMGUIWINDOWHANDLER_H
