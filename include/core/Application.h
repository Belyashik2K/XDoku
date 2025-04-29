//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <memory>

#include "AppMediator.h"
#include "IWindowHandler.h"

class Application {
    std::unique_ptr<IWindowHandler> windowHandler;
    AppMediator* appMediator;
public:
    Application(std::unique_ptr<IWindowHandler> handler, AppMediator* mediator);
    void start() const;
    ~Application();
};

#endif //APPLICATION_H
