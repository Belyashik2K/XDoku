//
// Created by belyashik2k on 5/3/25.
//

#include "application/managers/SudokuGameManager.h"

#include "application/app_events/ApplicationEvents.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"
#include "domain/sudoku/utils/SudokuFactory.h"

void SudokuGameManager::loadActiveGame() {
    printf("[SudokuGameManager] Getting active game...\n");
    const User *currentUser = sessionManager->getCurrentUser();
    if (!currentUser) {
        printf("[SudokuGameManager] No active user found\n");
        return;
    }
    if (currentGame) {
        printf("[SudokuGameManager] Active game already loaded\n");
        return;
    }

    std::optional<SudokuGame> game = gameRepository->getUserCurrentGame(currentUser->getId());
    if (game.has_value()) {
        printf("[SudokuGameManager] Found active game for user %d\n", currentUser->getId());
        std::optional<std::vector<SudokuMove> > moves = moveRepository->getMovesByGameId(game->getId());
        if (moves.has_value()) {
            printf("[SudokuGameManager] Found %zu moves for game with ID: %d\n", moves->size(), game->getId());
            for (const auto &move: *moves) {
                auto [fst, snd] = move.coords();
                game->createMove(fst, snd, move.getValue());
            }
        } else {
            printf("[SudokuGameManager] No moves found for game with ID: %d\n", game->getId());
        }
        setCurrentGame(std::make_unique<SudokuGame>(game.value()));
    } else {
        printf("[SudokuGameManager] No active game found for user %d\n", currentUser->getId());
    }
}

void SudokuGameManager::createSudokuGame(const SudokuDifficultyEnum &difficulty) {
    const User *currentUser = sessionManager->getCurrentUser();
    printf("[SudokuGameManager] Creating new sudoku game for user %d\n", currentUser->getId());
    const SudokuGame game = SudokuGameFactory::createNewGame(currentUser->getId(), difficulty);
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
    // TODO: Fix bug with fixed cells
    moveRepository->createMove(move);
    printf("[SudokuGameManager] Move created successfully\n");
    return move.isValidMove();
}

void SudokuGameManager::findActiveGame() const {
    printf("[SudokuGameManager] Finding active game...\n");
    if (currentGame) {
        eventBus->publish(OnActiveSudokuGameFound());
        return;
    }
    eventBus->publish(OnActiveSudokuGameNotFound());
}

void SudokuGameManager::subscribeToEvents() {
    printf("[SudokuGameManager] Subscribing to events...\n");

    eventBus->subscribe<OnApplicationStartup>([this](const OnApplicationStartup &) {
        this->loadActiveGame();
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &) {
        this->loadActiveGame();
    });
    eventBus->subscribe<OnUserLoggedOut>([this](const OnUserLoggedOut &) {
        this->clearCurrentGame();
    });
    eventBus->subscribe<OnPlayButtonClicked>([this](const OnPlayButtonClicked &) {
        this->findActiveGame();
    });
    eventBus->subscribe<OnSudokuDifficultySelected>([this](const OnSudokuDifficultySelected &event) {
            this->createSudokuGame(event.difficulty);
        }
    );
}
