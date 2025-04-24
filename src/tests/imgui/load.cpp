//
// Created by Belyashik2K on 06.04.2025.
//
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <imgui.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

bool initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }
    return true;
}

bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height)
{
    FILE* f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    const size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    const bool ret = LoadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}

bool initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return false;
    }

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark(); // Темная тема

    ImFont *font = io.Fonts->AddFontFromFileTTF("../assets/fonts/regular.ttf", 18.0f);
    if (!font) {
        printf("Font not set!");
        exit(EXIT_FAILURE);
    }

    // Персонализируем цвета
    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = ImVec4(0.196f, 0.196f, 0.196f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.160f, 0.160f, 0.160f, 1.00f);

    style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.196f, 0.196f, 0.196f, 1.00f);
    return true;
}

void testLoadImgui() {
    if (!initGLFW()) return;

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "ImGui Login Menu", monitor, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!initOpenGL()) return;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    const bool ret = LoadTextureFromFile("../assets/textures/background.jpg", &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);

    char username[128] = "";
    char password[128] = "";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin(
            "Login Menu",
            nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
        );

        ImVec2 windowPos = ImGui::GetWindowPos();
        const ImVec2 windowSize = ImGui::GetWindowSize();
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddImage(
            my_image_texture,
            windowPos,
            ImVec2(windowPos.x + windowSize.x,
                   windowPos.y + windowSize.y),
            ImVec2(0, 0),
            ImVec2(1, 1),
            IM_COL32(255, 255, 255, 255)
        );

        constexpr int childWidth = 650;
        constexpr int childHeight = 350;
        ImVec2 childSize(childWidth, childHeight);

        ImVec2 childPosition;
        childPosition.x = (windowSize.x - childSize.x) * 0.5f;
        childPosition.y = (windowSize.y - childSize.y) * 0.5f;

        ImGui::SetCursorPos(childPosition);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::BeginChild("CenteredChild", childSize, ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize);
        ImGui::PopStyleVar();

        float textWidth = ImGui::CalcTextSize("Please log in to your account").x;
        ImGui::SetCursorPosX((childWidth - textWidth) * 0.5f);
        ImGui::Text("Please log in to your account");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushItemWidth(childWidth);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 15.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

        ImGui::InputText("##Username", username, IM_ARRAYSIZE(username), ImGuiInputTextFlags_CharsNoBlank);
        ImGui::Spacing();
        ImGui::InputText("##Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::PopItemWidth();

        const auto &buttonSize = ImVec2(childWidth, 50.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

        ImGui::PushID("login_button");
        ImGui::Button("Log In", buttonSize);
        ImGui::PopID();
        ImGui::Spacing();
        if (ImGui::IsItemClicked(0)) {
            if (std::string(username) == "admin" && std::string(password) == "admin") {
                printf("Login successful!\n");
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            } else {
                printf("Login failed!\n");
            }
        }

        ImGui::PushID("exit_button");
        ImGui::Button("Exit", buttonSize);
        ImGui::PopID();
        if (ImGui::IsItemClicked(0)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(3);

        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
