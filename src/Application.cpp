//
// Created by belyashik2k on 4/29/25.
//

#include "core/Application.h"

Application::Application(std::unique_ptr<IFrameHandler> handler, AppMediator *mediator) {
    this->appMediator = mediator;
    this->frameHandler = std::move(handler);
}

void Application::start() const {
    this->frameHandler->run([this] {
        this->appMediator->render();
    });
}

Application::~Application() {
    this->frameHandler->shutdown();
}

