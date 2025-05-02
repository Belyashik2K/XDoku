//
// Created by belyashik2k on 5/2/25.
//

#include "presenters/MainMenuPresenter.h"

#include "core/app_events/ApplicationEvents.h"

void MainMenuPresenter::onPlayButtonClicked() {
    printf("[MainMenuPresenter] Play button clicked\n");
}


void MainMenuPresenter::onLeaderboardButtonClicked() {
    printf("[MainMenuPresenter] Leaderboard button clicked\n");
}

void MainMenuPresenter::onProfileButtonClicked() {
    printf("[MainMenuPresenter] Profile button clicked\n");
}

void MainMenuPresenter::onHowToPlayButtonClicked() {
    printf("[MainMenuPresenter] How play button clicked\n");
}

void MainMenuPresenter::onExitButtonClicked() {
    printf("[MainMenuPresenter] Exit button clicked\n");
    eventBus->publish(OnApplicationShutdown());
}

