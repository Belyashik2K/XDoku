#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


#include "core/Application.h"
#include "core/AppMediator.h"
#include "core/EventBus.h"

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "presenters/LoginPresenter.h"
#include "views/imgui/ImguiWindowHandler.h"

#include "views/imgui/login/ImguiLoginView.h"

int main() {
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

        auto windowHandler = std::make_unique<ImguiWindowHandler>("XDoku");
        const Application app(std::move(windowHandler), appMediator.get());
        app.start();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
