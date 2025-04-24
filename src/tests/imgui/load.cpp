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

// Инициализация GLFW
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

// Инициализация OpenGL и ImGui
bool initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return false;
    }

    // Инициализация ImGui
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
    // style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f); // Тёмный фон
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.160f, 0.160f, 0.160f, 1.00f);

    style.Colors[ImGuiCol_Border] = ImVec4(0.24f, 0.36f, 0.47f, 0.92f); // Цвет границ
    style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f); // Серый текст
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
    bool loginSuccess = false;

    // Главный цикл
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
        ImVec2 windowSize = ImGui::GetWindowSize();

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Рисуем текстуру как фон
        drawList->AddImage(
            my_image_texture,                           // ID текстуры
            windowPos,                                 // Левый верхний угол
            ImVec2(windowPos.x + windowSize.x,         // Правый нижний угол
                   windowPos.y + windowSize.y),
            ImVec2(0, 0),                              // UV-координаты левого верхнего угла текстуры
            ImVec2(1, 1),                              // UV-координаты правого нижнего угла текстуры
            IM_COL32(255, 255, 255, 255)               // Цвет (белый, без прозрачности)
        );

        // Получаем размер текста
        // ImVec2 textSize = ImGui::CalcTextSize(text);
        //
        // // Рассчитываем позицию текста (центр окна)
        // ImVec2 textPosition;
        // textPosition.x = (windowSize.x - textSize.x) * 0.5f; // Центрирование по горизонтали
        // textPosition.y = (windowSize.y - textSize.y) * 0.5f; // Центрирование по вертикали
        //
        // // Устанавливаем позицию текста
        // ImGui::SetCursorPos(textPosition);
        //
        // // Отображаем текст
        // ImGui::Text("%s", text);

        // Центрирование формы авторизации
        // ImVec2 window_pos = ImVec2((mode->width - 400) / 2, (mode->height - 300) / 2);
        // ImGui::SetCursorPos(window_pos); // Ставим курсор в центр экрана

        // Заголовок
        // ImGui::Text("Please log in to your account");
        // ImGui::Spacing();

        // ImGui::PushItemWidth(500.0f);
        // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 15.0f));
        //
        // // Поле для ввода логина
        // // ImGui::InputText("Username", username, IM_ARRAYSIZE(username), ImGuiInputTextFlags_CharsNoBlank);
        //
        // // Поле для ввода пароля
        // // ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
        //
        // ImGui::PopStyleVar();
        // ImGui::PopItemWidth();

        // Кнопка для входа

        const auto &buttonSize = ImVec2(300.0f, 50.0f);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Красный текст

        ImGui::PushID("login_button");
        ImGui::Button("Log In", buttonSize);
        ImGui::PopID();

        ImGui::SameLine();

        ImGui::PushID("register_button");
        ImGui::Button("Register", buttonSize);
        ImGui::PopID();

        ImGui::PushID("exit_button");
        ImGui::Button("Exit", buttonSize);
        ImGui::PopID();

        ImGui::PopStyleColor();

        ImGui::PushID("login_button");
        if (ImGui::IsItemClicked(0)) {
            // Вставь логику аутентификации здесь
            if (std::string(username) == "admin" && std::string(password) == "password") {
                printf("Login successful!\n");
            } else {
                printf("Login failed!\n");
            }
        }
        ImGui::PopID();

        ImGui::PushID("register_button");
        if (ImGui::IsItemClicked(0)) {
            std::cout << "Registration button clicked\n";
        }
        ImGui::PopID();

        ImGui::PushID("exit_button");
        if (ImGui::IsItemClicked(0)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        ImGui::PopID();

        ImGui::End();

        ImGui::Render();
        // glClearColor(0.05f, 0.05f, 0.05f, 1.00f); // Темный фон
        // glClear(GL_COLOR_BUFFER_BIT);

        // Рендерим все данные ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Обмен буферов
        glfwSwapBuffers(window);
    }

    // Очистка ресурсов ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
