//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <memory>

#include "AppMediator.h"
#include "IFrameHandler.h"

class Application {
    std::unique_ptr<IFrameHandler> frameHandler;
    AppMediator* appMediator;
public:
    Application(std::unique_ptr<IFrameHandler> handler, AppMediator* mediator);
    void start() const;
    ~Application();
};

#endif //APPLICATION_H
