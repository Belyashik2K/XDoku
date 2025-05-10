#include <iostream>

#include "application/Application.h"
#include "application/AppMediator.h"
#include "application/EventBus.h"
#include "application/managers/SessionManager.h"
#include "application/managers/SudokuGameManager.h"

#include "infrastructure/database/PostgreSQL/PostgreSQLDatabase.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"

#include "presentation/imgui/ImguiFrameHandler.h"
#include "presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.h"
#include "presentation/imgui/views/game/ImguiSudokuGameView.h"
#include "presentation/imgui/views/how_to_play/ImguiHowToPlayView.h"
#include "presentation/imgui/views/leaderboard/ImguiLeaderboardView.h"
#include "presentation/imgui/views/main_menu/ImguiMainMenuView.h"
#include "presentation/imgui/views/profile/ImguiProfileView.h"
#include "presentation/imgui/views/sign_in/ImguiSignInView.h"
#include "presentation/imgui/views/sign_up/ImguiSignUpView.h"

int main() {
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

        const auto sessionManager = std::make_shared<SessionManager>(eventBus, sessionRepository, userRepository);
        const auto sudokuGameManager = std::make_shared<SudokuGameManager>(eventBus, gameRepository, moveRepository, sessionManager);

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
        const auto profilePresenter = std::make_shared<ProfilePresenter>(eventBus, sessionManager);
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
            eventBus, sudokuGameManager
        );
        sudokuGamePresenter->init(std::move(sudokuGameView));

        appMediator->setCurrentPresenter(signInPresenter); // TODO: Encapsulate this logic in AppMediator
        appMediator->setSignUpPresenter(signUpPresenter);
        appMediator->setSignInPresenter(signInPresenter);
        appMediator->setMainMenuPresenter(mainMenuPresenter);
        appMediator->setProfilePresenter(profilePresenter);
        appMediator->setLeaderboardPresenter(leaderboardPresenter);
        appMediator->setHowToPlayPresenter(howToPlayPresenter);
        appMediator->setSudokuGamePresenter(sudokuGamePresenter);
        appMediator->setSudokuGameDifficultySelectorPresenter(sudokuGameDifficultySelectorPresenter);

        const Application XDoku(
            std::move(frameHandler),
            appMediator,
            eventBus
        );
        XDoku.start();

    return 0;
}
