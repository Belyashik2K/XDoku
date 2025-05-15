//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef LEADERBOARDPRESENTER_H
#define LEADERBOARDPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "domain/leaderboard/LeaderboardPlace.h"
#include "interfaces/IPresenter.h"
#include "interfaces/database/repositories/IRatingRepository.h"
#include "interfaces/views/ILeaderboardView.h"

using LeaderboardPlaces = std::optional<std::vector<LeaderboardPlace>>;

class LeaderboardPresenter final : public IPresenter<ILeaderboardView> {
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
};

#endif //LEADERBOARDPRESENTER_H
