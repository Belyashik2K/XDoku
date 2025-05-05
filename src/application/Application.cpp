//
// Created by belyashik2k on 4/29/25.
//

#include "application/Application.h"

#include "application/app_events/ApplicationEvents.h"

Application::Application(std::unique_ptr<IFrameHandler> handler, AppMediator *mediator, EventBus *eventBus) {
    this->frameHandler = std::move(handler);
    this->appMediator = mediator;
    this->eventBus = eventBus;
}

void Application::start() const {
    subscribeToEvents();
    printf("[Application] Starting application...\n");
    this->eventBus->publish(OnApplicationStartup());
    this->frameHandler->run([this] {
        this->appMediator->render();
    });
}

void Application::subscribeToEvents() const {
    printf("[Application] Subscribing to events...\n");
    this->eventBus->subscribe<OnApplicationShutdown>([this](const OnApplicationShutdown &) {
        this->frameHandler->shutdown();
    });
}

Application::~Application() {
    printf("[Application] Shutting down application...\n");
}

