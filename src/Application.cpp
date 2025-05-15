//
// Created by belyashik2k on 4/29/25.
//

#include "Application.h"
#include "factories/ViewFactory.h"
#include "application/app_events/ApplicationEvents.h"
#include "infrastructure/database/PostgreSQL/factories/PostgreSQLRepositoryFactory.h"
#include "presentation/imgui/ImguiFrameHandler.h"
#include "presentation/imgui/managers/ImguiAudioManager.h"
#include "presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.h"
#include "presentation/imgui/views/game/ImguiSudokuGameSummaryView.h"
#include "presentation/imgui/views/game/ImguiSudokuGameView.h"
#include "presentation/imgui/views/how_to_play/ImguiHowToPlayView.h"
#include "presentation/imgui/views/leaderboard/ImguiLeaderboardView.h"
#include "presentation/imgui/views/main_menu/ImguiMainMenuView.h"
#include "presentation/imgui/views/profile/ImguiProfileView.h"
#include "presentation/imgui/views/sign_in/ImguiSignInView.h"
#include "presentation/imgui/views/sign_up/ImguiSignUpView.h"

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
        signUpView,
        signInView,
        mainMenuView,
        profileView,
        leaderboardView,
        howToPlayView,
        sudokuGameView,
        sudokuGameDifficultySelectorView,
        sudokuGameSummaryView
    );
    appMediator->setCurrentView(signInView);
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
    ViewFactory viewFactory;
    signInView = viewFactory.create<ImguiSignInView, SignInPresenter>(eventBus, userRepository);
    signUpView = viewFactory.create<ImguiSignUpView, SignUpPresenter>(eventBus, userRepository);
    mainMenuView = viewFactory.create<ImguiMainMenuView, MainMenuPresenter>(eventBus);
    profileView = viewFactory.create<ImguiProfileView, ProfilePresenter>(eventBus, sessionManager);
    howToPlayView = viewFactory.create<ImguiHowToPlayView, HowToPlayPresenter>(eventBus);
    leaderboardView = viewFactory.create<ImguiLeaderboardView, LeaderboardPresenter>(
        eventBus, ratingRepository
    );
    sudokuGameDifficultySelectorView = viewFactory.create<ImguiSudokuGameDifficultySelectorView,
        SudokuGameDifficultySelectorPresenter>(eventBus);
    sudokuGameView = viewFactory.create<ImguiSudokuGameView,
        SudokuGamePresenter>(eventBus, sudokuGameManager
    );
    sudokuGameSummaryView = viewFactory.create<ImguiSudokuGameSummaryView, SudokuGameSummaryPresenter>(
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
