//
// Created by belyashik2k on 4/25/25.
//

#include <core/AppMediator.h>
#include <core/EventBus.h>

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
            printf("Switching to register presenter\n");
            this->currentPresenter = signUpPresenter;
        }
    });
}
