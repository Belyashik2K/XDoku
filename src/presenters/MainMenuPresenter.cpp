//
// Created by belyashik2k on 5/2/25.
//

#include "presenters/MainMenuPresenter.h"

#include "core/app_events/ApplicationEvents.h"
#include "core/app_events/ButtonEvents.h"

void MainMenuPresenter::onPlayButtonClicked() {
    printf("[MainMenuPresenter] Play button clicked\n");
    eventBus->publish(OnPlayButtonClicked());
}

void MainMenuPresenter::onLeaderboardButtonClicked() const {
    printf("[MainMenuPresenter] Leaderboard button clicked\n");
    eventBus->publish(OnLeaderboardButtonClicked());
}

void MainMenuPresenter::onProfileButtonClicked() {
    printf("[MainMenuPresenter] Profile button clicked\n");
    eventBus->publish(OnProfileButtonClicked());
}

void MainMenuPresenter::onHowToPlayButtonClicked() {
    printf("[MainMenuPresenter] How play button clicked\n");
}

void MainMenuPresenter::onExitButtonClicked() {
    printf("[MainMenuPresenter] Exit button clicked\n");
    eventBus->publish(OnApplicationShutdown());
}

