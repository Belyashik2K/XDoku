//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <memory>

#include "AppMediator.h"
#include "interfaces/IFrameHandler.h"

class Application {
    std::unique_ptr<IFrameHandler> frameHandler;
    AppMediator* appMediator;
    EventBus *eventBus = nullptr;
public:
    Application(std::unique_ptr<IFrameHandler> handler, AppMediator* mediator, EventBus *eventBus = nullptr);
    void start() const;

    void subscribeToEvents() const;

    ~Application();
};

#endif //APPLICATION_H
