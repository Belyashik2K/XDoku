//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef LEADERBOARDPRESENTER_H
#define LEADERBOARDPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IRatingRepository.h"
#include "models/leaderboard/LeaderboardPlace.h"

using LeaderboardPlaces = std::optional<std::vector<LeaderboardPlace>>;

class LeaderboardPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;
    IRatingRepository *ratingRepository = nullptr;
    bool isLoading = false;
    LeaderboardPlaces leaderboardPlaces = std::nullopt;

    void loadLeaderboard();
    void subscribeToEvents();

public:
    explicit LeaderboardPresenter(
        EventBus *eventBus,
        IRatingRepository *ratingRepository
    ) : eventBus(eventBus), ratingRepository(ratingRepository) {
        subscribeToEvents();
    }

    void onBackButtonClicked() const;
    void onRefreshButtonClicked();

    bool isOnLoading() const { return isLoading; }
    LeaderboardPlaces getLeaderboardPlaces() const { return leaderboardPlaces; }
};

#endif //LEADERBOARDPRESENTER_H
