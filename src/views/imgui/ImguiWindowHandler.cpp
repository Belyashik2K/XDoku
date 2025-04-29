//
// Created by belyashik2k on 4/29/25.
//

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include <views/imgui/ImguiWindowHandler.h>

ImguiWindowHandler::ImguiWindowHandler(
    int width,
    int height,
    const std::string &title
) {
    windowWidth = width;
    windowHeight = height;
    windowTitle = title;
    window = nullptr;
}

ImguiWindowHandler::ImguiWindowHandler(
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

void ImguiWindowHandler::createWindow() {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    if (!windowWidth || !windowHeight) {
        printf("Window size not set, using monitor resolution\n");
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

void ImguiWindowHandler::init() {
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

    ImFont *font = io.Fonts->AddFontFromFileTTF("../assets/fonts/regular.ttf", 22.0f);
    if (!font) {
        printf("Font not set!");
        exit(EXIT_FAILURE);
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

void ImguiWindowHandler::run(const std::function<void()> renderCallback) {
    init();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        renderCallback();
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void ImguiWindowHandler::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
