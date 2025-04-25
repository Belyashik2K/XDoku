//
// Created by belyashik2k on 4/25/25.
//

#include <core/AppMediator.h>
#include <core/EventBus.h>

void AppMediator::draw() {
    throw std::runtime_error("Not implemented yet");
}

std::shared_ptr<EventBus> AppMediator::getEventBus() {
    return eventBus;
}

AppMediator::AppMediator(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = std::move(eventBus);
}
