//
// Created by belyashik2k on 5/3/25.
//

#ifndef PROFILEPRESENTER_H
#define PROFILEPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"

class ProfilePresenter final : public IPresenter {
    std::shared_ptr<EventBus> eventBus;
public:
    explicit ProfilePresenter(const std::shared_ptr<EventBus> &eventBus) : eventBus(eventBus) {}
};

#endif //PROFILEPRESENTER_H
