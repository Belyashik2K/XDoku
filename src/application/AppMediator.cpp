//
// Created by belyashik2k on 4/25/25.
//

#include "application/AppMediator.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

void AppMediator::render() const {
    if (currentView) {
        currentView->render();
    }
}

void AppMediator::setCurrentView(const std::shared_ptr<IBaseView> &view) {
    currentView = view;
    if (view) {
        viewStack.push(view);
    }
}

void AppMediator::navigateBack() {
    if (viewStack.size() > 1) {
        viewStack.pop();
        currentView = viewStack.top();
    }
}

void AppMediator::navigateTo(const std::shared_ptr<IBaseView> &view) {
    if (view) {
        currentView = view;
        viewStack.push(view);
    }
}

void AppMediator::resetToRoot() {
    while (viewStack.size() > 1) {
        viewStack.pop();
    }
    if (!viewStack.empty()) {
        currentView = viewStack.top();
    }
}


void AppMediator::subscribeToEvents() {
    printf("[AppMediator] Subscribing to events...\n");
    eventBus->subscribe<OnSignUpButtonClicked>([this](const OnSignUpButtonClicked &) {
        if (signUpView) {
            navigateTo(signUpView);
        }
    });
    eventBus->subscribe<OnSignInButtonClicked>([this](const OnSignInButtonClicked &) {
        if (signInView) {
            navigateTo(signInView);
        }
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &) {
        if (mainMenuView) {
            resetToRoot();
            navigateTo(mainMenuView);
        }
    });
    eventBus->subscribe<OnLeaderboardButtonClicked>([this](const OnLeaderboardButtonClicked &) {
        if (leaderboardView) {
            navigateTo(leaderboardView);
        }
    });
    eventBus->subscribe<OnMainMenuButtonClicked>([this](const OnMainMenuButtonClicked &) {
        if (mainMenuView) {
            resetToRoot();
            navigateTo(mainMenuView);
        }
    });
    eventBus->subscribe<OnActiveSudokuGameFound>([this](const OnActiveSudokuGameFound &) {
        if (sudokuGameView) {
            navigateTo(sudokuGameView);
        }
    });
    eventBus->subscribe<OnActiveSudokuGameNotFound>([this](const OnActiveSudokuGameNotFound &) {
        if (sudokuGameDifficultySelectorView) {
            navigateTo(sudokuGameDifficultySelectorView);
        }
    });
    eventBus->subscribe<OnProfileButtonClicked>([this](const OnProfileButtonClicked &) {
        if (profileView) {
            navigateTo(profileView);
        }
    });
    eventBus->subscribe<OnHowToPlayButtonClicked>([this](const OnHowToPlayButtonClicked &) {
        if (howToPlayView) {
            navigateTo(howToPlayView);
        }
    });
    eventBus->subscribe<OnUserLoggedOut>([this](const OnUserLoggedOut &) {
        if (signInView) {
            resetToRoot();
            navigateTo(signInView);
        }
    });
    eventBus->subscribe<OnSudokuGameCreated>([this](const OnSudokuGameCreated &) {
        if (sudokuGameView) {
            navigateTo(sudokuGameView);
        }
    });
    eventBus->subscribe<OnSudokuGameFinished>([this](const OnSudokuGameFinished &) {
        if (sudokuGameSummaryView) {
            navigateTo(sudokuGameSummaryView);
        }
    });
    eventBus->subscribe<OnSudokuGameSurrendered>([this](const OnSudokuGameSurrendered &) {
        if (sudokuGameSummaryView) {
            navigateTo(sudokuGameSummaryView);
        }
    });
    eventBus->subscribe<OnSummaryViewClosed>([this](const OnSummaryViewClosed &) {
        if (mainMenuView) {
            resetToRoot();
            navigateTo(mainMenuView);
        }
    });
    eventBus->subscribe<OnBackButtonClicked>([this](const OnBackButtonClicked &) {
        navigateBack();
    });
}