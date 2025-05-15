//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPMEDIATOR_H
#define APPMEDIATOR_H
#include <memory>
#include <stack>

#include "EventBus.h"
#include "domain/custom_types/stack/DokuStack.h"
#include "interfaces/IPresenter.h"
#include "presenters/HowToPlayPresenter.h"
#include "presenters/LeaderboardPresenter.h"
#include "presenters/MainMenuPresenter.h"
#include "presenters/ProfilePresenter.h"
#include "presenters/SignInPresenter.h"
#include "presenters/SignUpPresenter.h"
#include "presenters/game/SudokuGameDifficultySelectorPresenter.h"
#include "presenters/game/SudokuGamePresenter.h"
#include "presenters/game/SudokuGameSummaryPresenter.h"

class AppMediator {

    DokuStack<std::shared_ptr<IBaseView>> viewStack;

    std::shared_ptr<IBaseView> currentView;
    std::shared_ptr<EventBus> eventBus;

    std::shared_ptr<ISignUpView> signUpView;
    std::shared_ptr<ISignInView> signInView;
    std::shared_ptr<IMainMenuView> mainMenuView;
    std::shared_ptr<IProfileView> profileView;
    std::shared_ptr<ILeaderboardView> leaderboardView;
    std::shared_ptr<IHowToPlayView> howToPlayView;
    std::shared_ptr<ISudokuGameView> sudokuGameView;
    std::shared_ptr<ISudokuGameDifficultySelectorView> sudokuGameDifficultySelectorView;
    std::shared_ptr<ISudokuGameSummaryView> sudokuGameSummaryView;

    void navigateBack();

    void navigateTo(const std::shared_ptr<IBaseView> &view);

    void resetToRoot();

    void subscribeToEvents();
public:
    explicit AppMediator(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<ISignUpView> &signUpView,
        const std::shared_ptr<ISignInView> &signInView,
        const std::shared_ptr<IMainMenuView> &mainMenuView,
        const std::shared_ptr<IProfileView> &profileView,
        const std::shared_ptr<ILeaderboardView> &leaderboardView,
        const std::shared_ptr<IHowToPlayView> &howToPlayView,
        const std::shared_ptr<ISudokuGameView> &sudokuGameView,
        const std::shared_ptr<ISudokuGameDifficultySelectorView> &sudokuGameDifficultySelectorView,
        const std::shared_ptr<ISudokuGameSummaryView> &sudokuGameSummaryView
    ) : eventBus(eventBus),
        signUpView(signUpView),
        signInView(signInView),
        mainMenuView(mainMenuView),
        profileView(profileView),
        leaderboardView(leaderboardView),
        howToPlayView(howToPlayView),
        sudokuGameView(sudokuGameView),
        sudokuGameDifficultySelectorView(sudokuGameDifficultySelectorView),
        sudokuGameSummaryView(sudokuGameSummaryView) {
        subscribeToEvents();
    }

    void setCurrentView(const std::shared_ptr<IBaseView> &view);

    void render() const;
};

#endif //APPMEDIATOR_H
