//
// Created by belyashik2k on 5/3/25.
//

#ifndef PROFILEPRESENTER_H
#define PROFILEPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "application/app_events/ButtonEvents.h"
#include "application/managers/SessionManager.h"
#include "interfaces/IPresenter.h"
#include "interfaces/views/IProfileView.h"

using Stats = std::optional<UserStats>;

class ProfilePresenter final :
        public IPresenter<IProfileView, ProfilePresenter>,
        public std::enable_shared_from_this<ProfilePresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<SessionManager> sessionManager;

    Stats userStats = std::nullopt;

public:
    explicit ProfilePresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<SessionManager> &sessionManager
    ) : eventBus(eventBus), sessionManager(sessionManager) {
        subscribeToEvents();
    }

    void loadUserStats() {
        userStats = sessionManager->getUserStats();
    }

    void clearUserStats() {
        userStats = std::nullopt;
    }

    void subscribeToEvents() {
        eventBus->subscribe<OnProfileButtonClicked>([this](const OnProfileButtonClicked &event) {
            if (userStats) return;
            loadUserStats();
        });
        eventBus->subscribe<OnSudokuGameFinished>([this](const OnSudokuGameFinished &event) {
            loadUserStats();
        });
        eventBus->subscribe<OnSudokuGameSurrendered>([this](const OnSudokuGameSurrendered &event) {
            loadUserStats();
        });
        eventBus->subscribe<OnUserLoggedOut>([this](const OnUserLoggedOut &event) {
            clearUserStats();
        });
    }

    void onLogoutButtonClicked() const;

    int getGamesCount() const;

    int getFinishedGamesCount() const;

    int getCompletionRate() const;

    std::string getMostCommonDifficulty() const;

    std::string getAverageSolutionTime() const;

    void onBackButtonClicked() const;

    const User *getCurrentUser() const {
        return sessionManager->getCurrentUser();
    }

    UserStats getCurrentUserStats() const {
        return sessionManager->getUserStats();
    }

    void init(std::unique_ptr<IProfileView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //PROFILEPRESENTER_H
