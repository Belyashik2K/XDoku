//
// Created by belyashik2k on 4/25/25.
//

#include <core/AppMediator.h>
#include <core/EventBus.h>

#include "core/app_events/UserEvents.h"

void AppMediator::render() const {
    if (currentPresenter) {
        currentPresenter->render();
    }
}

AppMediator::AppMediator(std::shared_ptr<EventBus> eventBus, IPresenter *presenter) {
    this->eventBus = std::move(eventBus);
    this->currentPresenter = presenter;
}


void AppMediator::subscribeToEvents() {
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
}
