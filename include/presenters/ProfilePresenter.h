//
// Created by belyashik2k on 5/3/25.
//

#ifndef PROFILEPRESENTER_H
#define PROFILEPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"

class ProfilePresenter final : public IPresenter {
    EventBus* eventBus = nullptr;
public:
    explicit ProfilePresenter(EventBus* eventBus) : eventBus(eventBus) {}
};

#endif //PROFILEPRESENTER_H
