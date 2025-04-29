//
// Created by belyashik2k on 4/29/25.
//

#include "core/Application.h"

Application::Application(std::unique_ptr<IWindowHandler> handler, AppMediator *mediator) {
    this->appMediator = mediator;
    this->windowHandler = std::move(handler);
}

void Application::start() const {
    this->windowHandler->run([this]() {
        this->appMediator->render();
    });
}

Application::~Application() {
    this->windowHandler->shutdown();
}

