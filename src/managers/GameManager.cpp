//
// Created by belyashik2k on 5/3/25.
//

#include "managers/GameManager.h"

#include "core/app_events/ButtonEvents.h"
#include "core/app_events/UserEvents.h"

void GameManager::getActiveGame() const {
    std::optional<SudokuGame> game = gameRepository->getGame(16); // TODO: make it dynamic for current user
    if (game.has_value()) {
        printf("[GameManager] Found active game");
        eventBus->publish(OnActiveSudokuGameFound(game.value()));
    } else {
        printf("[GameManager] No active game found\n");
        eventBus->publish(OnActiveSudokuGameNotFound());
    }
}


void GameManager::subscribeToEvents() const {
    printf("[GameManager] Subscribing to events...\n");
    eventBus->subscribe<OnPlayButtonClicked>([this](const OnPlayButtonClicked &) {
        this->getActiveGame();
    });
}
