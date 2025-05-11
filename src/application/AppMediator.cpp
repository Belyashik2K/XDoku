//
// Created by belyashik2k on 4/25/25.
//

#include "application/AppMediator.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

void AppMediator::render() const {
    if (currentPresenter) {
        currentPresenter->render();
    }
}

void AppMediator::setCurrentPresenter(const std::shared_ptr<IBasePresenter> &presenter) {
    currentPresenter = presenter;
    if (presenter) {
        presenterStack.push(presenter);
    }
}

void AppMediator::navigateBack() {
    if (presenterStack.size() > 1) {
        presenterStack.pop();
        currentPresenter = presenterStack.top();
    }
}

void AppMediator::navigateTo(const std::shared_ptr<IBasePresenter> &presenter) {
    if (presenter) {
        currentPresenter = presenter;
        presenterStack.push(presenter);
    }
}

void AppMediator::resetToRoot() {
    while (presenterStack.size() > 1) {
        presenterStack.pop();
    }
    if (!presenterStack.empty()) {
        currentPresenter = presenterStack.top();
    }
}

void AppMediator::subscribeToEvents() {
    printf("[AppMediator] Subscribing to events...\n");
    eventBus->subscribe<OnSignUpButtonClicked>([this](const OnSignUpButtonClicked &) {
        if (signUpPresenter) {
            navigateTo(signUpPresenter);
        }
    });
    eventBus->subscribe<OnSignInButtonClicked>([this](const OnSignInButtonClicked &) {
        if (signInPresenter) {
            navigateTo(signInPresenter);
        }
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &) {
        if (mainMenuPresenter) {
            resetToRoot();
            navigateTo(mainMenuPresenter);
        }
    });
    eventBus->subscribe<OnLeaderboardButtonClicked>([this](const OnLeaderboardButtonClicked &) {
        if (leaderboardPresenter) {
            navigateTo(leaderboardPresenter);
        }
    });
    eventBus->subscribe<OnMainMenuButtonClicked>([this](const OnMainMenuButtonClicked &) {
        if (mainMenuPresenter) {
            resetToRoot();
            navigateTo(mainMenuPresenter);
        }
    });
    eventBus->subscribe<OnActiveSudokuGameFound>([this](const OnActiveSudokuGameFound &) {
        if (sudokuGamePresenter) {
            navigateTo(sudokuGamePresenter);
        }
    });
    eventBus->subscribe<OnActiveSudokuGameNotFound>([this](const OnActiveSudokuGameNotFound &) {
        if (sudokuGameDifficultySelectorPresenter) {
            navigateTo(sudokuGameDifficultySelectorPresenter);
        }
    });
    eventBus->subscribe<OnProfileButtonClicked>([this](const OnProfileButtonClicked &) {
        if (profilePresenter) {
            navigateTo(profilePresenter);
        }
    });
    eventBus->subscribe<OnHowToPlayButtonClicked>([this](const OnHowToPlayButtonClicked &) {
        if (howToPlayPresenter) {
            navigateTo(howToPlayPresenter);
        }
    });
    eventBus->subscribe<OnUserLoggedOut>([this](const OnUserLoggedOut &) {
        if (signInPresenter) {
            resetToRoot();
            navigateTo(signInPresenter);
        }
    });
    eventBus->subscribe<OnSudokuGameCreated>([this](const OnSudokuGameCreated &) {
        if (sudokuGamePresenter) {
            navigateTo(sudokuGamePresenter);
        }
    });
    eventBus->subscribe<OnSudokuGameFinished>([this](const OnSudokuGameFinished &) {
        if (sudokuGameSummaryPresenter) {
            navigateTo(sudokuGameSummaryPresenter);
        }
    });
    eventBus->subscribe<OnSudokuGameSurrendered>([this](const OnSudokuGameSurrendered &) {
        if (sudokuGameSummaryPresenter) {
            navigateTo(sudokuGameSummaryPresenter);
        }
    });
    eventBus->subscribe<OnSummaryViewClosed>([this](const OnSummaryViewClosed &) {
        if (mainMenuPresenter) {
            resetToRoot();
            navigateTo(mainMenuPresenter);
        }
    });
    eventBus->subscribe<OnBackButtonClicked>([this](const OnBackButtonClicked &) {
        navigateBack();
    });
}