//
// Created by belyashik2k on 4/29/25.
//

#include "application/Application.h"
#include "application/app_events/ApplicationEvents.h"

Application::Application(
    std::unique_ptr<IFrameHandler> frameHandler,
    const std::shared_ptr<AppMediator> &appMediator,
    const std::shared_ptr<EventBus> &eventBus
) {
    this->appMediator = appMediator;
    this->frameHandler = std::move(frameHandler);
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

void Application::subscribeToEvents() const { // TODO: weak_ptr instead of this
    printf("[Application] Subscribing to events...\n");
    this->eventBus->subscribe<OnApplicationShutdown>([this](const OnApplicationShutdown &) {
        this->frameHandler->shutdown();
    });
}

Application::~Application() {
    printf("[Application] Shutting down application...\n");
}
