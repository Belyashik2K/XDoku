//
// Created by belyashik2k on 5/3/25.
//

#ifndef HOWTOPLAYPRESENTER_H
#define HOWTOPLAYPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"

class HowToPlayPresenter final : public IPresenter {
    std::shared_ptr<EventBus> eventBus;

public:
    explicit HowToPlayPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {
    }
};

#endif //HOWTOPLAYPRESENTER_H
