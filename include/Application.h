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

    std::shared_ptr<SignInPresenter> signInPresenter;
    std::shared_ptr<SignUpPresenter> signUpPresenter;
    std::shared_ptr<MainMenuPresenter> mainMenuPresenter;
    std::shared_ptr<ProfilePresenter> profilePresenter;
    std::shared_ptr<LeaderboardPresenter> leaderboardPresenter;
    std::shared_ptr<HowToPlayPresenter> howToPlayPresenter;
    std::shared_ptr<SudokuGamePresenter> sudokuGamePresenter;
    std::shared_ptr<SudokuGameDifficultySelectorPresenter> sudokuGameDifficultySelectorPresenter;
    std::shared_ptr<SudokuGameSummaryPresenter> sudokuGameSummaryPresenter;

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
