//
// Created by belyashik2k on 5/3/25.
//

#include "application/managers/SudokuGameManager.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

void SudokuGameManager::getActiveGame() {
    printf("[SudokuGameManager] Getting active game...\n");
    const User *currentUser = sessionManager->getCurrentUser();

    std::optional<SudokuGame> game = gameRepository->getUserCurrentGame(currentUser->getId());
    if (game.has_value()) {
        printf("[SudokuGameManager] Found active game for user %d\n", currentUser->getId());
        eventBus->publish(OnActiveSudokuGameFound(game.value()));
    } else {
        printf("[SudokuGameManager] No active game found for user %d\n", currentUser->getId());
        eventBus->publish(OnActiveSudokuGameNotFound());
    }
}

void SudokuGameManager::createSudokuGame(const SudokuDifficultyEnum &difficulty) {
    const User *currentUser = sessionManager->getCurrentUser();
    printf("[SudokuGameManager] Creating new sudoku game for user %d\n", currentUser->getId());
    const SudokuGame game = SudokuGame::startNewGame(currentUser->getId(), difficulty);
    std::optional<SudokuGame> createdGame = gameRepository->createGame(currentUser->getId(), game);
    if (createdGame.has_value()) {
        printf("[SudokuGameManager] Created new sudoku game for user %d\n", currentUser->getId());
        eventBus->publish(OnSudokuGameCreated());
    } else {
        printf("[SudokuGameManager] Failed to create new sudoku game for user %d\n", currentUser->getId());
        // eventBus->publish(OnSudokuGameCreationFailed());
    }
}

void SudokuGameManager::subscribeToEvents() {
    printf("[SudokuGameManager] Subscribing to events...\n");
    eventBus->subscribe<OnPlayButtonClicked>([this](const OnPlayButtonClicked &) {
        this->getActiveGame();
    });
    eventBus->subscribe<OnSudokuDifficultySelected> (
        [this](const OnSudokuDifficultySelected &event) {
            this->createSudokuGame(event.difficulty);
        }
    );
}
