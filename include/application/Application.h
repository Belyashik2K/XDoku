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
    std::shared_ptr<AppMediator> appMediator;
    std::shared_ptr<EventBus> eventBus;
public:
    Application(
        std::unique_ptr<IFrameHandler> frameHandler,
        const std::shared_ptr<AppMediator> &appMediator,
        const std::shared_ptr<EventBus> &eventBus
    );
    void start() const;

    void subscribeToEvents() const;

    ~Application();
};

#endif //APPLICATION_H
