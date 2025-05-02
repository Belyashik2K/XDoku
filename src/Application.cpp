//
// Created by belyashik2k on 4/29/25.
//

#include "core/Application.h"

#include "core/app_events/ApplicationEvents.h"

Application::Application(std::unique_ptr<IFrameHandler> handler, AppMediator *mediator, EventBus *eventBus) {
    this->frameHandler = std::move(handler);
    this->appMediator = mediator;
    this->eventBus = eventBus;
}

void Application::start() const {
    this->eventBus->publish(OnApplicationStartup());
    this->frameHandler->run([this] {
        this->appMediator->render();
    });
}

Application::~Application() {
    this->frameHandler->shutdown();
}

