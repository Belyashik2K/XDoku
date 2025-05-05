//
// Created by belyashik2k on 5/3/25.
//

#ifndef HOWTOPLAYPRESENTER_H
#define HOWTOPLAYPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "interfaces/IPresenter.h"
#include "interfaces/views/IHowToPlayView.h"

class HowToPlayPresenter final :
        public IPresenter<IHowToPlayView, HowToPlayPresenter>,
        public std::enable_shared_from_this<HowToPlayPresenter> {
    std::shared_ptr<EventBus> eventBus;

public:
    explicit HowToPlayPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {
    }

    void init(std::unique_ptr<IHowToPlayView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //HOWTOPLAYPRESENTER_H
