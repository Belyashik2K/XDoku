//
// Created by Belyashik2K on 02.05.2025.
//

#include "presenters/LeaderboardPresenter.h"

#include "core/app_events/ButtonEvents.h"

void LeaderboardPresenter::loadLeaderboard() {
    printf("[LeaderboardPresenter] Loading/refreshing leaderboard...\n");
    isLoading = true;
    leaderboardPlaces = ratingRepository->getLeaderboard(10);
    isLoading = false;
}

void LeaderboardPresenter::subscribeToEvents() {
    printf("[LeaderboardPresenter] Subscribing to events...\n");
    eventBus->subscribe<OnLeaderboardButtonClicked>([this](const OnLeaderboardButtonClicked &) {
        loadLeaderboard();
    });
}

void LeaderboardPresenter::onBackButtonClicked() const {
    printf("[LeaderboardPresenter] Back button clicked\n");
    // TODO: Screen stack
    eventBus->publish(OnMainMenuButtonClicked());
}

void LeaderboardPresenter::onRefreshButtonClicked() {
    printf("[LeaderboardPresenter] Refresh button clicked\n");
    loadLeaderboard();
}

