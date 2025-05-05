#include <iostream>

#include "core/Application.h"
#include "core/AppMediator.h"
#include "core/EventBus.h"

#include "managers/SudokuGameManager.h"
#include "managers/SessionManager.h"

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "presenters/MainMenuPresenter.h"
#include "presenters/SignInPresenter.h"

#include "views/imgui/ImguiFrameHandler.h"
#include "views/imgui/game/ImguiSudokuGameDifficultySelectorView.h"
#include "views/imgui/game/ImguiSudokuGameView.h"
#include "views/imgui/how_to_play/ImguiHowToPlayView.h"
#include "views/imgui/leaderboard/ImguiLeaderboardView.h"
#include "views/imgui/main_menu/ImguiMainMenuView.h"
#include "views/imgui/profile/ImguiProfileView.h"
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

        const auto sessionManager = std::make_shared<SessionManager>(eventBus, sessionRepository);
        const auto sudokuGameManager = std::make_shared<SudokuGameManager>(eventBus, gameRepository, moveRepository);

        auto frameHandler = std::make_unique<ImguiFrameHandler>("XDoku");

        auto signInView = std::make_unique<ImguiSignInView>();
        const auto signInPresenter = std::make_shared<SignInPresenter>(eventBus, userRepository);
        signInPresenter->init(std::move(signInView));

        auto signUpView = std::make_unique<ImguiSignUpView>();
        const auto signUpPresenter = std::make_shared<SignUpPresenter>(eventBus, userRepository);
        signUpPresenter->init(std::move(signUpView));

        auto mainMenuView = std::make_unique<ImguiMainMenuView>();
        const auto mainMenuPresenter = std::make_shared<MainMenuPresenter>(eventBus);
        mainMenuPresenter->init(std::move(mainMenuView));

        auto profileView = std::make_unique<ImguiProfileView>();
        const auto profilePresenter = std::make_shared<ProfilePresenter>(eventBus);
        profilePresenter->init(std::move(profileView));

        auto howToPlayView = std::make_unique<ImguiHowToPlayView>();
        const auto howToPlayPresenter = std::make_shared<HowToPlayPresenter>(eventBus);
        howToPlayPresenter->init(std::move(howToPlayView));

        auto leaderboardView = std::make_unique<ImguiLeaderboardView>();
        const auto leaderboardPresenter = std::make_shared<LeaderboardPresenter>(eventBus, ratingRepository);
        leaderboardPresenter->init(std::move(leaderboardView));

        auto sudokuGameDifficultySelectorView = std::make_unique<ImguiSudokuGameDifficultySelectorView>();
        const auto sudokuGameDifficultySelectorPresenter = std::make_shared<SudokuGameDifficultySelectorPresenter>(
            eventBus
        );
        sudokuGameDifficultySelectorPresenter->init(std::move(sudokuGameDifficultySelectorView));

        auto sudokuGameView = std::make_unique<ImguiSudokuGameView>();
        const auto sudokuGamePresenter = std::make_shared<SudokuGamePresenter>(
            eventBus, gameRepository, moveRepository
        );
        sudokuGamePresenter->init(std::move(sudokuGameView));

        appMediator->setCurrentPresenter(signInPresenter.get()); // TODO: Encapsulate this logic in AppMediator
        appMediator->setSignUpPresenter(signUpPresenter.get());
        appMediator->setSignInPresenter(signInPresenter.get());
        appMediator->setMainMenuPresenter(mainMenuPresenter.get());
        appMediator->setProfilePresenter(profilePresenter.get());
        appMediator->setLeaderboardPresenter(leaderboardPresenter.get());
        appMediator->setHowToPlayPresenter(howToPlayPresenter.get());
        appMediator->setSudokuGamePresenter(sudokuGamePresenter.get());
        appMediator->setSudokuGameDifficultySelectorPresenter(sudokuGameDifficultySelectorPresenter.get());

        const Application app(std::move(frameHandler), appMediator.get(), eventBus.get());
        app.start();
    } catch (const std::exception &e) {
        printf("Oops! An error occurred: %s\n", e.what());
    }

    return 0;
}
