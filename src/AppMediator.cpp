//
// Created by belyashik2k on 4/25/25.
//

#include <core/AppMediator.h>
#include <core/EventBus.h>

#include "core/app_events/ButtonEvents.h"
#include "core/app_events/UserEvents.h"

void AppMediator::render() const {
    if (currentPresenter) {
        currentPresenter->render();
    }
}

AppMediator::AppMediator(std::shared_ptr<EventBus> eventBus, IPresenter *presenter) {
    this->eventBus = std::move(eventBus);
    this->currentPresenter = presenter;
    subscribeToEvents();
}


void AppMediator::subscribeToEvents() {
    printf("[AppMediator] Subscribing to events...\n");
    eventBus->subscribe<OnSignUpButtonClicked>([this](const OnSignUpButtonClicked &) {
        if (signUpPresenter) {
            this->currentPresenter = signUpPresenter;
        }
    });
    eventBus->subscribe<OnSignInButtonClicked>([this](const OnSignInButtonClicked &) {
        if (currentPresenter) {
            this->currentPresenter = signInPresenter;
        }
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &) {
        if (mainMenuPresenter) {
            this->currentPresenter = mainMenuPresenter;
        }
    });
    eventBus->subscribe<OnLeaderboardButtonClicked>([this](const OnLeaderboardButtonClicked &) {
        if (leaderboardPresenter) {
            this->currentPresenter = leaderboardPresenter;
        }
    });
    eventBus->subscribe<OnMainMenuButtonClicked>([this](const OnMainMenuButtonClicked &) {
        if (mainMenuPresenter) {
            this->currentPresenter = mainMenuPresenter;
        }
    });
    eventBus->subscribe<OnActiveSudokuGameFound>([this](const OnActiveSudokuGameFound &) {
        if (sudokuGamePresenter) {
            this->currentPresenter = sudokuGamePresenter;
        }
    });
    eventBus->subscribe<OnActiveSudokuGameNotFound>([this](const OnActiveSudokuGameNotFound &) {
        if (sudokuGameDifficultySelectorPresenter) {
            this->currentPresenter = sudokuGameDifficultySelectorPresenter;
        }
    });
    eventBus->subscribe<OnProfileButtonClicked>([this](const OnProfileButtonClicked &) {
        if (profilePresenter) {
            this->currentPresenter = profilePresenter;
        }
    });
    eventBus->subscribe<OnHowToPlayButtonClicked>([this](const OnHowToPlayButtonClicked &) {
        if (howToPlayPresenter) {
            this->currentPresenter = howToPlayPresenter;
        }
    });
}
