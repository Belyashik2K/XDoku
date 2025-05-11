//
// Created by belyashik2k on 4/29/25.
//

#include "../include/Application.h"
#include "../include/application/app_events/ApplicationEvents.h"
#include "../include/application/factories/PresenterFactory.h"
#include "../include/infrastructure/database/PostgreSQL/factories/PostgreSQLRepositoryFactory.h"
#include "../include/presentation/imgui/ImguiFrameHandler.h"
#include "../include/presentation/imgui/managers/ImguiAudioManager.h"
#include "../include/presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.h"
#include "../include/presentation/imgui/views/game/ImguiSudokuGameSummaryView.h"
#include "../include/presentation/imgui/views/game/ImguiSudokuGameView.h"
#include "../include/presentation/imgui/views/how_to_play/ImguiHowToPlayView.h"
#include "../include/presentation/imgui/views/leaderboard/ImguiLeaderboardView.h"
#include "../include/presentation/imgui/views/main_menu/ImguiMainMenuView.h"
#include "../include/presentation/imgui/views/profile/ImguiProfileView.h"
#include "../include/presentation/imgui/views/sign_in/ImguiSignInView.h"
#include "../include/presentation/imgui/views/sign_up/ImguiSignUpView.h"

Application::Application() {
    initRepositories();
    initFrameHandler();
    initEventBus();
    initManagers();
    initPresentersAndViews();
    initAppMediator();
}

void Application::initRepositories() {
    printf("[Application] Initializing repositories...\n");
    const std::string connectionString = "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@localhost:5432/xdoku";
    repositoryFactory = std::make_unique<PostgreSQLRepositoryFactory>(connectionString);
    userRepository = repositoryFactory->createUserRepository();
    sessionRepository = repositoryFactory->createSessionRepository();
    ratingRepository = repositoryFactory->createRatingRepository();
    gameRepository = repositoryFactory->createGameRepository();
    moveRepository = repositoryFactory->createMoveRepository();
    printf("[Application] Repositories initialized\n");
}

void Application::initFrameHandler() {
    printf("[Application] Initializing frame handler...\n");
    frameHandler = std::make_unique<ImguiFrameHandler>("XDoku");
    printf("[Application] Frame handler initialized\n");
}

void Application::initEventBus() {
    printf("[Application] Initializing event bus...\n");
    eventBus = std::make_shared<EventBus>();
    printf("[Application] Event bus initialized\n");
}

void Application::initAppMediator() {
    printf("[Application] Initializing app mediator...\n");
    appMediator = std::make_shared<AppMediator>(
        eventBus,
        signInPresenter,
        signUpPresenter,
        mainMenuPresenter,
        profilePresenter,
        howToPlayPresenter,
        leaderboardPresenter,
        sudokuGameDifficultySelectorPresenter,
        sudokuGamePresenter,
        sudokuGameSummaryPresenter
    );
    appMediator->setCurrentPresenter(signInPresenter);
    printf("[Application] App mediator initialized\n");
}

void Application::initManagers() {
    printf("[Application] Initializing managers...\n");
    sessionManager = std::make_shared<SessionManager>(eventBus, sessionRepository, userRepository);
    sudokuGameManager = std::make_shared<SudokuGameManager>(
        eventBus, gameRepository, moveRepository, ratingRepository, sessionManager
    );
    printf("[Application] Managers initialized\n");
}

void Application::initPresentersAndViews() {
    printf("[Application] Initializing presenters...\n");
    PresenterFactory presenterFactory;
    signInPresenter = presenterFactory.create<ImguiSignInView, SignInPresenter>(eventBus, userRepository);
    signUpPresenter = presenterFactory.create<ImguiSignUpView, SignUpPresenter>(eventBus, userRepository);
    mainMenuPresenter = presenterFactory.create<ImguiMainMenuView, MainMenuPresenter>(eventBus);
    profilePresenter = presenterFactory.create<ImguiProfileView, ProfilePresenter>(eventBus, sessionManager);
    howToPlayPresenter = presenterFactory.create<ImguiHowToPlayView, HowToPlayPresenter>(eventBus);
    leaderboardPresenter = presenterFactory.create<ImguiLeaderboardView, LeaderboardPresenter>(
        eventBus, ratingRepository
    );
    sudokuGameDifficultySelectorPresenter = presenterFactory.create<ImguiSudokuGameDifficultySelectorView,
        SudokuGameDifficultySelectorPresenter>(eventBus);
    sudokuGamePresenter = presenterFactory.create<ImguiSudokuGameView,
        SudokuGamePresenter>(eventBus, sudokuGameManager
    );
    sudokuGameSummaryPresenter = presenterFactory.create<ImguiSudokuGameSummaryView, SudokuGameSummaryPresenter>(
        eventBus, sudokuGameManager
    );
    printf("[Application] Presenters initialized\n");
}

void Application::start() const {
    subscribeToEvents();
    printf("[Application] Starting application...\n");
    this->eventBus->publish(OnApplicationStartup());
    this->frameHandler->run([this] {
        this->appMediator->render();
    });
}

void Application::subscribeToEvents() const {
    printf("[Application] Subscribing to events...\n");
    this->eventBus->subscribe<OnApplicationShutdown>([this](const OnApplicationShutdown &) {
        this->frameHandler->shutdown();
    });
}

Application::~Application() {
    printf("[Application] Shutting down application...\n");
}
