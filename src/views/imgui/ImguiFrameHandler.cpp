//
// Created by belyashik2k on 4/29/25.
//

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include <views/imgui/ImguiFrameHandler.h>

#include "managers/FontManager.h"

bool loaded = false;

ImguiFrameHandler::ImguiFrameHandler(
    int width,
    int height,
    const std::string &title
) {
    windowWidth = width;
    windowHeight = height;
    windowTitle = title;
    window = nullptr;
}

ImguiFrameHandler::ImguiFrameHandler(
    const std::string &title
) {
    windowWidth = std::nullopt;
    windowHeight = std::nullopt;
    windowTitle = title;
    window = nullptr;
}

bool initGLFW() {
    return glfwInit();
}

bool initOpenGL() {
    return gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}

void ImguiFrameHandler::createWindow() {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    if (!windowWidth || !windowHeight) {
        printf("[ImguiFrameHandler] Window size is not set. Using monitor resolution.\n");
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        windowWidth = std::make_optional(mode->width);
        windowHeight = std::make_optional(mode->height);
    }

    GLFWwindow *window = glfwCreateWindow(
        windowWidth.value(),
        windowHeight.value(),
        windowTitle.c_str(),
        monitor,
        nullptr
    );
    this->window = window;
}

void ImguiFrameHandler::init() {
    if (!initGLFW()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    createWindow();
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!initOpenGL()) {
        std::cerr << "Failed to initialize OpenGL" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    ImGui::CreateContext();
    const ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();

    FontManager::getInstance().setFontPath("../assets/fonts/regular.ttf");
    if (!loaded) {
        for (int i = 1; i < 40; ++i) {
            FontManager::getInstance().getFont(i);
            loaded = true;
        }
    }

    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = ImVec4(0.196f, 0.196f, 0.196f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.160f, 0.160f, 0.160f, 1.00f);

    style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.196f, 0.196f, 0.196f, 1.00f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ImguiFrameHandler::run(const std::function<void()> renderCallback) {
    init();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(windowWidth.value(), windowHeight.value()), ImGuiCond_FirstUseEver);
        ImGui::PushFont(FontManager::getInstance().getFont(28));
        renderCallback();
        ImGui::PopFont();
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void ImguiFrameHandler::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
