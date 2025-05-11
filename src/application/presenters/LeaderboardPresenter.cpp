//
// Created by Belyashik2K on 02.05.2025.
//

#include "application/presenters/LeaderboardPresenter.h"

#include "application/app_events/ButtonEvents.h"

void LeaderboardPresenter::loadLeaderboard() {
    printf("[LeaderboardPresenter] Loading/refreshing leaderboard...\n");
    isLoading = true;
    leaderboardPlaces = ratingRepository->getLeaderboard(10);
    isLoading = false;
}

void LeaderboardPresenter::subscribeToEvents() {
    printf("[LeaderboardPresenter] Subscribing to events...\n");
    eventBus->subscribe<OnLeaderboardButtonClicked>([this](const OnLeaderboardButtonClicked &) {
        if (getLeaderboardPlaces()) {
            return;
        }
        loadLeaderboard();
    });
}

void LeaderboardPresenter::onBackButtonClicked() const {
    printf("[LeaderboardPresenter] Back button clicked\n");
    eventBus->publish(OnBackButtonClicked());
}

void LeaderboardPresenter::onRefreshButtonClicked() {
    printf("[LeaderboardPresenter] Refresh button clicked\n");
    loadLeaderboard();
}

