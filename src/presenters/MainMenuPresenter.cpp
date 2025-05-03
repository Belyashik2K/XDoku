//
// Created by belyashik2k on 5/2/25.
//

#include "presenters/MainMenuPresenter.h"

#include "core/app_events/ApplicationEvents.h"
#include "core/app_events/ButtonEvents.h"

void MainMenuPresenter::onPlayButtonClicked() const {
    printf("[MainMenuPresenter] Play button clicked\n");
    eventBus->publish(OnPlayButtonClicked());
}

void MainMenuPresenter::onLeaderboardButtonClicked() const {
    printf("[MainMenuPresenter] Leaderboard button clicked\n");
    eventBus->publish(OnLeaderboardButtonClicked());
}

void MainMenuPresenter::onProfileButtonClicked() const {
    printf("[MainMenuPresenter] Profile button clicked\n");
    eventBus->publish(OnProfileButtonClicked());
}

void MainMenuPresenter::onHowToPlayButtonClicked() const {
    printf("[MainMenuPresenter] How play button clicked\n");
    eventBus->publish(OnHowToPlayButtonClicked());
}

void MainMenuPresenter::onExitButtonClicked() const {
    printf("[MainMenuPresenter] Exit button clicked\n");
    eventBus->publish(OnApplicationShutdown());
}

