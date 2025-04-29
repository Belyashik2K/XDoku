#include <iostream>
#include "core/Application.h"
#include "core/AppMediator.h"
#include "core/EventBus.h"

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "presenters/LoginPresenter.h"
#include "views/imgui/ImguiFrameHandler.h"

#include "views/imgui/login/ImguiLoginView.h"
#include "views/imgui/sign_up/ImguiSignUpView.h"

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

        const auto eventBus = std::make_shared<EventBus>();
        const auto appMediator = std::make_shared<AppMediator>(eventBus);

        const auto loginView = std::make_shared<ImguiLoginView>();
        const auto loginPresenter = std::make_shared<LoginPresenter>(eventBus.get());
        const auto registerView = std::make_shared<ImguiSignUpView>();
        const auto registerPresenter = std::make_shared<RegisterPresenter>();

        loginPresenter->setView(loginView.get());
        loginView->setPresenter(loginPresenter.get());

        registerPresenter->setView(registerView.get());
        registerView->setPresenter(registerPresenter.get());

        appMediator->setCurrentPresenter(loginPresenter.get());
        appMediator->setRegisterPresenter(registerPresenter.get());
        appMediator->subscribeToEvents();

        auto frameHandler = std::make_unique<ImguiFrameHandler>("XDoku");
        const Application app(std::move(frameHandler), appMediator.get());
        app.start();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
