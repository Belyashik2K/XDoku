#include <iostream>
#include "core/Application.h"
#include "core/AppMediator.h"
#include "core/EventBus.h"

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "presenters/SignInPresenter.h"
#include "views/imgui/ImguiFrameHandler.h"

#include "views/imgui/sign_in/ImguiSignInView.h"
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

        const auto signInView = std::make_shared<ImguiSignInView>();
        const auto signInPresenter = std::make_shared<SignInPresenter>(eventBus.get());
        const auto signUpView = std::make_shared<ImguiSignUpView>();
        const auto signUpPresenter = std::make_shared<SignUpPresenter>(eventBus.get());

        signInPresenter->setView(signInView.get());
        signInView->setPresenter(signInPresenter.get());

        signUpPresenter->setView(signUpView.get());
        signUpView->setPresenter(signUpPresenter.get());

        appMediator->setCurrentPresenter(signInPresenter.get());
        appMediator->setSignUpPresenter(signUpPresenter.get());
        appMediator->setSignInPresenter(signInPresenter.get());
        appMediator->subscribeToEvents();

        auto frameHandler = std::make_unique<ImguiFrameHandler>("XDoku");
        const Application app(std::move(frameHandler), appMediator.get());
        app.start();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
