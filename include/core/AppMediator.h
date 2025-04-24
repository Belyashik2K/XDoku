//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPMEDIATOR_H
#define APPMEDIATOR_H
#include <memory>

#include "EventBus.h"

class AppMediator {
    std::shared_ptr<EventBus> eventBus;
public:
    explicit AppMediator(std::shared_ptr<EventBus> eventBus);
    void draw();

    // TODO: Implement the rest of the methods

    std::shared_ptr<EventBus> getEventBus();
};

#endif //APPMEDIATOR_H
