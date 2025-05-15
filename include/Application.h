//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <memory>

#include "application/AppMediator.h"
#include "interfaces/IFrameHandler.h"
#include "interfaces/database/repositories/IRepositoryFactory.h"

class Application {
    std::unique_ptr<IRepositoryFactory> repositoryFactory;
    std::shared_ptr<IUserRepository> userRepository;
    std::shared_ptr<ISessionRepository> sessionRepository;
    std::shared_ptr<IGameRepository> gameRepository;
    std::shared_ptr<IMoveRepository> moveRepository;
    std::shared_ptr<IRatingRepository> ratingRepository;

    std::shared_ptr<SessionManager> sessionManager;
    std::shared_ptr<SudokuGameManager> sudokuGameManager;

    std::shared_ptr<ISignInView> signInView;
    std::shared_ptr<ISignUpView> signUpView;
    std::shared_ptr<IMainMenuView> mainMenuView;
    std::shared_ptr<IProfileView> profileView;
    std::shared_ptr<ILeaderboardView> leaderboardView;
    std::shared_ptr<IHowToPlayView> howToPlayView;
    std::shared_ptr<ISudokuGameView> sudokuGameView;
    std::shared_ptr<ISudokuGameDifficultySelectorView> sudokuGameDifficultySelectorView;
    std::shared_ptr<ISudokuGameSummaryView> sudokuGameSummaryView;

    std::unique_ptr<IFrameHandler> frameHandler;
    std::shared_ptr<AppMediator> appMediator;
    std::shared_ptr<EventBus> eventBus;

    void subscribeToEvents() const;

    void initFrameHandler();

    void initEventBus();

    void initAppMediator();

    void initManagers();

    void initPresentersAndViews();

    void initRepositories();


public:
    Application();
    ~Application();

    void start() const;
};

#endif //APPLICATION_H
