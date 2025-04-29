//
// Created by belyashik2k on 4/29/25.
//

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include <views/imgui/ImguiWindowHandler.h>

ImguiWindowHandler::ImguiWindowHandler(const int width, const int height, const std::string &title) {
    windowWidth = width;
    windowHeight = height;
    windowTitle = title;
    window = nullptr;
}

bool initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }
    return true;
}

bool initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return false;
    }


    return true;
}


void ImguiWindowHandler::init() {
    initGLFW();
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    GLFWwindow *newWindow = glfwCreateWindow(mode->width, mode->height, "ImGui Login Menu", monitor, nullptr);
    if (!newWindow) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    windowHeight = mode->height;
    windowWidth = mode->width;
    windowTitle = glfwGetWindowTitle(newWindow);
    window = newWindow;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    initOpenGL();

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




