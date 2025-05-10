//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPMEDIATOR_H
#define APPMEDIATOR_H
#include <memory>

#include "EventBus.h"
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
    std::shared_ptr<IBasePresenter> currentPresenter;
    std::shared_ptr<EventBus> eventBus;

    std::shared_ptr<SignUpPresenter> signUpPresenter;
    std::shared_ptr<SignInPresenter> signInPresenter;
    std::shared_ptr<MainMenuPresenter> mainMenuPresenter;
    std::shared_ptr<ProfilePresenter> profilePresenter;
    std::shared_ptr<LeaderboardPresenter> leaderboardPresenter;
    std::shared_ptr<HowToPlayPresenter> howToPlayPresenter;
    std::shared_ptr<SudokuGamePresenter> sudokuGamePresenter;
    std::shared_ptr<SudokuGameDifficultySelectorPresenter> sudokuGameDifficultySelectorPresenter;
    std::shared_ptr<SudokuGameSummaryPresenter> sudokuGameSummaryPresenter;

    void subscribeToEvents();
public:
    explicit AppMediator(const std::shared_ptr<EventBus> &eventBus,
                         const std::shared_ptr<IBasePresenter> &presenter = nullptr);

    void setCurrentPresenter(const std::shared_ptr<IBasePresenter> &presenter) {
        currentPresenter = presenter;
    }
    void setSignUpPresenter(const std::shared_ptr<SignUpPresenter> &presenter) {
        signUpPresenter = presenter;
    }
    void setSignInPresenter(const std::shared_ptr<SignInPresenter> &presenter) {
        signInPresenter = presenter;
    }
    void setMainMenuPresenter(const std::shared_ptr<MainMenuPresenter> &presenter) {
        mainMenuPresenter = presenter;
    }
    void setLeaderboardPresenter(const std::shared_ptr<LeaderboardPresenter> &presenter) {
        leaderboardPresenter = presenter;
    }
    void setSudokuGamePresenter(const std::shared_ptr<SudokuGamePresenter> &presenter) {
        sudokuGamePresenter = presenter;
    }
    void setSudokuGameDifficultySelectorPresenter(const std::shared_ptr<SudokuGameDifficultySelectorPresenter> &presenter) {
        sudokuGameDifficultySelectorPresenter = presenter;
    }
    void setProfilePresenter(const std::shared_ptr<ProfilePresenter> &presenter) {
        profilePresenter = presenter;
    }
    void setHowToPlayPresenter(const std::shared_ptr<HowToPlayPresenter> &presenter) {
        howToPlayPresenter = presenter;
    }
    void setSudokuGameSummaryPresenter(const std::shared_ptr<SudokuGameSummaryPresenter> &presenter) {
        sudokuGameSummaryPresenter = presenter;
    }
    void render() const;
};

#endif //APPMEDIATOR_H
