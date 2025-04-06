//
// Created by Belyashik2K on 06.04.2025.
//
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <imgui.h>
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

// Инициализация OpenGL и ImGui
bool initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return false;
    }

    // Инициализация ImGui
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();  // Темная тема

    // Персонализируем цвета
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);  // Тёмный фон
    style.Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.56f, 0.77f, 1.00f);      // Голубая кнопка
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.70f, 0.94f, 1.00f); // Светлая кнопка при наведении
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.09f, 0.45f, 0.64f, 1.00f);  // Темно-голубая кнопка при активации

    style.Colors[ImGuiCol_Border] = ImVec4(0.24f, 0.36f, 0.47f, 0.92f);      // Цвет границ
    style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);         // Белый текст
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);  // Серый текст
    return true;
}

// Главная функция
void testLoadImgui() {
    // Инициализация GLFW
    if (!initGLFW()) return;

    // Получаем главный монитор и разрешение
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Создаем окно с размерами монитора
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "ImGui Login Menu", monitor, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Настроим окно так, чтобы оно не растягивалось на оба монитора
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Включение вертикальной синхронизации

    // Инициализация OpenGL и ImGui
    if (!initOpenGL()) return;

    // Инициализация ImGui для GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Переменные для логина и пароля
    char username[128] = "";
    char password[128] = "";
    bool loginSuccess = false;

    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();  // Обработка событий

        // Начало нового кадра ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Окно для авторизации
        ImGui::Begin("Login Menu");

        // Убираем рамки и фоновое изображение
        ImGui::SetWindowSize(ImVec2(mode->width, mode->height), ImGuiCond_Always);  // Полноэкранный размер
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);  // Окно на весь экран

        // Центрирование формы авторизации
        ImVec2 window_pos = ImVec2((mode->width - 400) / 2, (mode->height - 300) / 2);
        ImGui::SetCursorPos(window_pos);  // Ставим курсор в центр экрана

        // Заголовок
        ImGui::Text("Please log in to your account");
        ImGui::Spacing();

        // Поле для ввода логина
        ImGui::InputText("Username", username, IM_ARRAYSIZE(username));

        // Поле для ввода пароля
        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        // Кнопка для входа
        if (ImGui::Button("Log In")) {
            // Вставь логику аутентификации здесь
            if (std::string(username) == "admin" && std::string(password) == "password") {
                loginSuccess = true;
                ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Login successful!");
            } else {
                loginSuccess = false;
                ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "Invalid username or password.");
            }
        }

        // Кнопка для регистрации
        if (ImGui::Button("Register")) {
            // Здесь можно добавить логику для регистрации
            std::cout << "Registration button clicked\n";
        }

        // Кнопка выхода
        if (ImGui::Button("Exit")) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        ImGui::End();

        // Рендеринг интерфейса
        ImGui::Render();
        glClearColor(0.05f, 0.05f, 0.05f, 1.00f);  // Темный фон
        glClear(GL_COLOR_BUFFER_BIT);

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

