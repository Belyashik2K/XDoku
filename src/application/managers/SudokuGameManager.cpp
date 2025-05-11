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

int SudokuGameManager::calculateRating() const {
    // Рейтинг = max(0, (1000 - (ошибки × 50) - (время_сек × 2)) × коэф_сложности + бонус_за_идеал)
    if (!currentGame) {
        return 0;
    }

    if (currentGame->getStatus() == SudokuGameStatusEnum::SURRENDERED) {
        return -100;
    }

    constexpr int maxRating = 1000;
    constexpr float minRating = 0.0f;
    constexpr int mistakesMultiplier = 50;
    constexpr int timeMultiplier = 2;
    const float difficultyMultiplier = SudokuDifficulty::getSettings(currentGame->getDifficulty()).ratingMultiplier;
    const int elapsedTime = currentGame->getElapsedTime();

    const int mistakes = currentGame->getMistakesCount();
    float rating = maxRating - (mistakes * mistakesMultiplier) - (elapsedTime * timeMultiplier) * difficultyMultiplier;
    if (!mistakes) {
        constexpr int bonus = 200;
        rating += bonus;
    }

    return std::max(minRating, rating);
}

bool SudokuGameManager::isGridComplete() const {
    return getCurrentGame()->isSudokuSolved();
}

void SudokuGameManager::finishGame() const {
    if (!currentGame) {
        printf("[SudokuGameManager] No active game to finish\n");
        return;
    }
    currentGame->finish();
    const bool result = gameRepository->updateGame(
        currentGame->getId(),
        SudokuGameStatusEnum::FINISHED,
        Timestamp::now()
    );
    if (result) {
        printf("[SudokuGameManager] Game with ID: %d finished successfully\n", currentGame->getId());
        updateRating(calculateRating(), "Game №" + std::to_string(currentGame->getId()) + " finished");
    } else {
        printf("[SudokuGameManager] Failed to finish game with ID: %d\n", currentGame->getId());
    }
}

void SudokuGameManager::surrenderGame() const {
    if (!currentGame) {
        printf("[SudokuGameManager] No active game to surrender\n");
        return;
    }
    currentGame->surrender();
    const bool result = gameRepository->updateGame(
        currentGame->getId(),
        SudokuGameStatusEnum::SURRENDERED,
        Timestamp::now()
    );
    if (result) {
        printf("[SudokuGameManager] Game with ID: %d surrendered successfully\n", currentGame->getId());
        updateRating(calculateRating(), "Game №" + std::to_string(currentGame->getId()) + " surrendered");
    } else {
        printf("[SudokuGameManager] Failed to surrender game with ID: %d\n", currentGame->getId());
    }
}

void SudokuGameManager::updateRating(
    const int ratingChange,
    const std::string &message
) const {
    if (!currentGame) {
        printf("[SudokuGameManager] No active game to update rating\n");
        return;
    }
    const User *currentUser = sessionManager->getCurrentUser();
    const int newRating = ratingRepository->createRatingHistoryRecord(
        currentUser->getId(),
        currentGame->getId(),
        currentUser->getRating() + ratingChange >= 0 ? ratingChange : -currentUser->getRating(),
        message
    );
    sessionManager->addRating(ratingChange);
    if (newRating) {
        printf("[SudokuGameManager] Rating history record created successfully\n");
    } else {
        printf("[SudokuGameManager] Failed to create rating history record\n");
    }
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
    eventBus->subscribe<OnSummaryViewClosed>([this](const OnSummaryViewClosed &) {
        this->clearCurrentGame();
    });
    eventBus->subscribe<OnSudokuGameFinished>([this](const OnSudokuGameFinished &) {
        this->finishGame();
    });
    eventBus->subscribe<OnSudokuGameSurrendered>([this](const OnSudokuGameSurrendered &) {
        this->surrenderGame();
    });
}
