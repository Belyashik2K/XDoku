//
// Created by belyashik2k on 4/24/25.
//

#ifndef APPMEDIATOR_H
#define APPMEDIATOR_H
#include <memory>

#include "EventBus.h"
#include "IPresenter.h"

class AppMediator {
    IPresenter *currentPresenter = nullptr;
    std::shared_ptr<EventBus> eventBus;

public:
    explicit AppMediator(std::shared_ptr<EventBus> eventBus, IPresenter *presenter = nullptr);

    void setCurrentPresenter(IPresenter *presenter) {
        currentPresenter = presenter;
    }
    void render() const;
};

#endif //APPMEDIATOR_H
