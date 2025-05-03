//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPMEDIATOR_H
#define APPMEDIATOR_H
#include <memory>

#include "EventBus.h"
#include "IPresenter.h"
#include "presenters/LeaderboardPresenter.h"
#include "presenters/MainMenuPresenter.h"
#include "presenters/SignInPresenter.h"
#include "presenters/SignUpPresenter.h"
#include "presenters/game/SudokuGameDifficultySelectorPresenter.h"
#include "presenters/game/SudokuGamePresenter.h"

class AppMediator {
    IPresenter *currentPresenter = nullptr;
    std::shared_ptr<EventBus> eventBus;

    SignUpPresenter *signUpPresenter = nullptr;
    SignInPresenter *signInPresenter = nullptr;
    MainMenuPresenter *mainMenuPresenter = nullptr;
    LeaderboardPresenter * leaderboardPresenter = nullptr;
    SudokuGamePresenter *sudokuGamePresenter = nullptr;
    SudokuGameDifficultySelectorPresenter *sudokuGameDifficultySelectorPresenter = nullptr;

    void subscribeToEvents();
public:
    explicit AppMediator(std::shared_ptr<EventBus> eventBus, IPresenter *presenter = nullptr);

    void setCurrentPresenter(IPresenter *presenter) {
        currentPresenter = presenter;
    }
    void setSignUpPresenter(SignUpPresenter *presenter) {
        signUpPresenter = presenter;
    }
    void setSignInPresenter(SignInPresenter *presenter) {
        signInPresenter = presenter;
    }
    void setMainMenuPresenter(MainMenuPresenter *presenter) {
        mainMenuPresenter = presenter;
    }
    void setLeaderboardPresenter(LeaderboardPresenter *presenter) {
        leaderboardPresenter = presenter;
    }
    void setSudokuGamePresenter(SudokuGamePresenter *presenter) {
        sudokuGamePresenter = presenter;
    }
    void setSudokuGameDifficultySelectorPresenter(SudokuGameDifficultySelectorPresenter *presenter) {
        sudokuGameDifficultySelectorPresenter = presenter;
    }
    void render() const;
};

#endif //APPMEDIATOR_H
