#include <iostream>

#include "core/Application.h"
#include "core/AppMediator.h"
#include "core/EventBus.h"

#include "managers/GameManager.h"
#include "managers/SessionManager.h"

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "presenters/MainMenuPresenter.h"
#include "presenters/SignInPresenter.h"

#include "views/imgui/ImguiFrameHandler.h"
#include "views/imgui/leaderboard/ImguiLeaderboardView.h"
#include "views/imgui/main_menu/ImguiMainMenuView.h"
#include "views/imgui/sign_in/ImguiSignInView.h"
#include "views/imgui/sign_up/ImguiSignUpView.h"

int main() {
    try {
        const std::string connectionString =
        "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@xdoku.belyashik2k.ru:5432/xdoku";

        auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        const auto userRepository = std::make_shared<PostgreSQLUserRepository>(database);
        const auto sessionRepository = std::make_shared<PostgreSQLSessionRepository>(database);
        const auto ratingRepository = std::make_shared<PostgreSQLRatingRepository>(database);
        const auto gameRepository = std::make_shared<PostgreSQLGameRepository>(database);
        const auto moveRepository = std::make_shared<PostgreSQLMoveRepository>(database);

        const auto eventBus = std::make_shared<EventBus>();
        const auto appMediator = std::make_shared<AppMediator>(eventBus);

        const auto sessionManager = std::make_shared<SessionManager>(eventBus.get(), sessionRepository.get());
        const auto gameManager = std::make_shared<GameManager>(eventBus.get(), gameRepository.get());

        auto frameHandler = std::make_unique<ImguiFrameHandler>("XDoku");
        const auto signInView = std::make_shared<ImguiSignInView>();
        const auto signInPresenter = std::make_shared<SignInPresenter>(eventBus.get(), userRepository.get());
        const auto signUpView = std::make_shared<ImguiSignUpView>();
        const auto signUpPresenter = std::make_shared<SignUpPresenter>(eventBus.get(), userRepository.get());
        const auto mainMenuView = std::make_shared<ImguiMainMenuView>();
        const auto mainMenuPresenter = std::make_shared<MainMenuPresenter>(eventBus.get());
        const auto leaderboardView = std::make_shared<ImguiLeaderboardView>();
        const auto leaderboardPresenter = std::make_shared<LeaderboardPresenter>(eventBus.get(), ratingRepository.get());

        signInPresenter->setView(signInView.get());
        signInView->setPresenter(signInPresenter.get());

        signUpPresenter->setView(signUpView.get());
        signUpView->setPresenter(signUpPresenter.get());

        mainMenuPresenter->setView(mainMenuView.get());
        mainMenuView->setPresenter(mainMenuPresenter.get());

        leaderboardPresenter->setView(leaderboardView.get());
        leaderboardView->setPresenter(leaderboardPresenter.get());

        appMediator->setCurrentPresenter(signInPresenter.get());
        appMediator->setSignUpPresenter(signUpPresenter.get());
        appMediator->setSignInPresenter(signInPresenter.get());
        appMediator->setMainMenuPresenter(mainMenuPresenter.get());
        appMediator->setLeaderboardPresenter(leaderboardPresenter.get());

        const Application app(std::move(frameHandler), appMediator.get(), eventBus.get());
        app.start();

    } catch (const std::exception &e) {
        printf("Oops! An error occurred: %s\n", e.what());
    }

    return 0;
}
