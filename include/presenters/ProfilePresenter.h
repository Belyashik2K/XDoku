//
// Created by belyashik2k on 5/3/25.
//

#ifndef PROFILEPRESENTER_H
#define PROFILEPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "views/IProfileView.h"

class ProfilePresenter final :
        public IPresenter<IProfileView, ProfilePresenter>,
        public std::enable_shared_from_this<ProfilePresenter> {
    std::shared_ptr<EventBus> eventBus;
public:
    explicit ProfilePresenter(const std::shared_ptr<EventBus> &eventBus) : eventBus(eventBus) {
    }

    void init(std::unique_ptr<IProfileView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //PROFILEPRESENTER_H
