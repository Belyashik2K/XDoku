//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUIFRAMEHANDLER_H
#define IMGUIFRAMEHANDLER_H
#include <string>
#include <GLFW/glfw3.h>

#include "core/IFrameHandler.h"

class ImguiFrameHandler final : public IFrameHandler {
public:
    ImguiFrameHandler(
        int width,
        int height,
        const std::string &title
    );

    explicit ImguiFrameHandler(
        const std::string &title
    );

    void run(std::function<void()> renderCallback) override;

    void afterRender() const;

    void shutdown() override;

private:
    void init();
    void createWindow();

    GLFWwindow *window;
    std::optional<int> windowWidth, windowHeight;
    std::string windowTitle;
};

#endif //IMGUIFRAMEHANDLER_H
