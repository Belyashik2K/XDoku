//
// Created by belyashik2k on 5/3/25.
//

#ifndef PROFILEPRESENTER_H
#define PROFILEPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "application/managers/SessionManager.h"
#include "interfaces/IPresenter.h"
#include "interfaces/views/IProfileView.h"

class ProfilePresenter final :
        public IPresenter<IProfileView, ProfilePresenter>,
        public std::enable_shared_from_this<ProfilePresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<SessionManager> sessionManager;

public:
    explicit ProfilePresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<SessionManager> &sessionManager
    ) : eventBus(eventBus), sessionManager(sessionManager) {
    }

    void onLogoutButtonClicked() const;

    void onBackButtonClicked() const;

    const User *getCurrentUser() const {
        return sessionManager->getCurrentUser();
    }

    void init(std::unique_ptr<IProfileView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //PROFILEPRESENTER_H
