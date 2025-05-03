//
// Created by belyashik2k on 5/3/25.
//

#include "managers/SudokuGameManager.h"

#include "core/app_events/ButtonEvents.h"
#include "core/app_events/UserEvents.h"

void SudokuGameManager::getActiveGame() const {
    std::optional<SudokuGame> game = gameRepository->getGame(16); // TODO: make it dynamic for current user
    if (game.has_value()) {
        printf("[SudokuGameManager] Found active game\n");
        eventBus->publish(OnActiveSudokuGameFound(game.value()));
    } else {
        printf("[SudokuGameManager] No active game found\n");
        eventBus->publish(OnActiveSudokuGameNotFound());
    }
}


void SudokuGameManager::subscribeToEvents() const {
    printf("[SudokuGameManager] Subscribing to events...\n");
    eventBus->subscribe<OnPlayButtonClicked>([this](const OnPlayButtonClicked &) {
        this->getActiveGame();
    });
}
