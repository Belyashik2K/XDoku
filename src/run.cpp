#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


#include "core/AppMediator.h"
#include "core/EventBus.h"

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "presenters/LoginPresenter.h"

#include "views/imgui/login/ImguiLoginView.h"

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


int main() {

    // testLoadImgui();

    try {
        // const std::string connectionString =
        //         "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@xdoku.belyashik2k.ru:5432/xdoku";
        //
        // auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        // const auto userRepository = std::make_shared<PostgreSQLUserRepository>(database);
        // const auto sessionRepository = std::make_shared<PostgreSQLSessionRepository>(database);
        // const PostgreSQLRatingRepository ratingRepository(database);
        // PostgreSQLMoveRepository moveRepository(database);
        // PostgreSQLGameRepository gameRepository(database);

        auto eventBus = std::make_shared<EventBus>();
        const auto appMediator = std::make_shared<AppMediator>(eventBus);

        const auto loginView = std::make_shared<ImguiLoginView>();
        const auto loginPresenter = std::make_shared<LoginPresenter>(eventBus.get());

        loginPresenter->setView(loginView.get());
        loginView->setPresenter(loginPresenter.get());

        appMediator->setCurrentPresenter(loginPresenter.get());

        initGLFW();

        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "ImGui Login Menu", monitor, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

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

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            appMediator->render();
            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
        glfwTerminate();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
