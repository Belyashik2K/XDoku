//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef LEADERBOARDPRESENTER_H
#define LEADERBOARDPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IRatingRepository.h"
#include "models/leaderboard/LeaderboardPlace.h"
#include "views/ILeaderboardView.h"

using LeaderboardPlaces = std::optional<std::vector<LeaderboardPlace>>;

class LeaderboardPresenter final :
        public IPresenter<ILeaderboardView, LeaderboardPresenter>,
        public std::enable_shared_from_this<LeaderboardPresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IRatingRepository> ratingRepository;

    bool isLoading = false;
    LeaderboardPlaces leaderboardPlaces = std::nullopt;

    void loadLeaderboard();

    void subscribeToEvents();

public:
    explicit LeaderboardPresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IRatingRepository> &ratingRepository
    ) : eventBus(eventBus), ratingRepository(ratingRepository) {
        subscribeToEvents();
    }

    void onBackButtonClicked() const;

    void onRefreshButtonClicked();

    bool isOnLoading() const { return isLoading; }
    LeaderboardPlaces getLeaderboardPlaces() const { return leaderboardPlaces; }

    void init(std::unique_ptr<ILeaderboardView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //LEADERBOARDPRESENTER_H
