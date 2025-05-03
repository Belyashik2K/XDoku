//
// Created by belyashik2k on 5/3/25.
//

#ifndef HOWTOPLAYPRESENTER_H
#define HOWTOPLAYPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"

class HowToPlayPresenter final : public IPresenter {
    EventBus* eventBus = nullptr;
public:
    explicit HowToPlayPresenter(EventBus* eventBus) : eventBus(eventBus) {}
};

#endif //HOWTOPLAYPRESENTER_H
