//
// Created by belyashik2k on 5/3/25.
//

#include "application/managers/SudokuGameManager.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

void SudokuGameManager::loadActiveGame() {
    printf("[SudokuGameManager] Getting active game...\n");
    const User *currentUser = sessionManager->getCurrentUser();

    std::optional<SudokuGame> game = gameRepository->getUserCurrentGame(currentUser->getId());
    std::optional<std::vector<SudokuMove>> moves = moveRepository->getMovesByGameId(game->getId());
    if (moves.has_value()) {
        printf("[SudokuGameManager] Found %zu moves for game with ID: %d\n", moves->size(), game->getId());
        for (const auto &move : *moves) {
            auto [fst, snd] = move.coords();
            game->createMove(fst, snd, move.getValue());
            printf("[SudokuGameManager] Move: (%d, %d) = %d\n", fst, snd, move.getValue());
        }
    } else {
        printf("[SudokuGameManager] No moves found for game with ID: %d\n", game->getId());
    }
    if (game.has_value()) {
        printf("[SudokuGameManager] Found active game for user %d\n", currentUser->getId());
        setCurrentGame(std::make_unique<SudokuGame>(game.value()));
        eventBus->publish(OnActiveSudokuGameFound());
    } else {
        printf("[SudokuGameManager] No active game found for user %d\n", currentUser->getId());
        eventBus->publish(OnActiveSudokuGameNotFound());
    }
    actualizeCurrentGrid();
}

void SudokuGameManager::createSudokuGame(const SudokuDifficultyEnum &difficulty) {
    const User *currentUser = sessionManager->getCurrentUser();
    printf("[SudokuGameManager] Creating new sudoku game for user %d\n", currentUser->getId());
    const SudokuGame game = SudokuGame::startNewGame(currentUser->getId(), difficulty);
    std::optional<SudokuGame> createdGame = gameRepository->createGame(currentUser->getId(), game);
    if (createdGame.has_value()) {
        printf("[SudokuGameManager] Created new sudoku game for user %d\n", currentUser->getId());
        setCurrentGame(std::make_unique<SudokuGame>(createdGame.value()));
        eventBus->publish(OnSudokuGameCreated());
    } else {
        printf("[SudokuGameManager] Failed to create new sudoku game for user %d\n", currentUser->getId());
    }
}

bool SudokuGameManager::createMove(const int selected_row, const int selected_col, const int value) const {
    printf("[SudokuGameManager] Creating move (row: %d, col: %d, value: %d) in game with ID: %d\n",
           selected_row, selected_col, value, currentGame->getId());
    const SudokuMove move = currentGame->createMove(selected_row, selected_col, value);
    moveRepository->createMove(move);
    printf("[SudokuGameManager] Move created successfully\n");
    actualizeCurrentGrid();
    return move.isValidMove();
}

void SudokuGameManager::actualizeCurrentGrid() const {
    if (!currentGame) {
        printf("[SudokuGameManager] No current game found, skipping actualization...\n");
        return;
    }
    printf("[SudokuGameManager] Actualizing current grid...\n");
    currentGame->actualizeCurrentGrid();
}

void SudokuGameManager::subscribeToEvents() {
    printf("[SudokuGameManager] Subscribing to events...\n");
    eventBus->subscribe<OnPlayButtonClicked>([this](const OnPlayButtonClicked &) {
        this->loadActiveGame();
    });
    eventBus->subscribe<OnSudokuDifficultySelected> (
        [this](const OnSudokuDifficultySelected &event) {
            this->createSudokuGame(event.difficulty);
        }
    );
}
