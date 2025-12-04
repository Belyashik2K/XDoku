//
// Created by belyashik2k on 5/3/25.
//

#include "application/managers/SudokuGameManager.h"

#include "application/app_events/ApplicationEvents.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"
#include "application/managers/ProfilingManager.h"
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

    std::optional<std::unique_ptr<SudokuGame>> game = gameRepository->getUserCurrentGame(currentUser->getId());
    if (game.has_value()) {
        printf("[SudokuGameManager] Found active game for user %d\n", currentUser->getId());
        flushPendingMoves();
        setCurrentGame(std::move(game.value()));
    } else {
        printf("[SudokuGameManager] No active game found for user %d\n", currentUser->getId());
    }
}

void SudokuGameManager::createSudokuGame(const SudokuDifficultyEnum &difficulty) {
    FunctionTimerManager& manager = FunctionTimerManager::instance();
    manager.track(
        "SudokuGameManager::createSudokuGame",
        [this] (const SudokuDifficultyEnum &difficulty) {
            this->createSudokuGamerInternal(
                difficulty
            );
            return 1;
        },
        difficulty
    );
}

void SudokuGameManager::createSudokuGamerInternal(const SudokuDifficultyEnum &difficulty) {
    const User *currentUser = sessionManager->getCurrentUser();
    printf("[SudokuGameManager] Creating new sudoku game for user %d\n", currentUser->getId());
    std::unique_ptr<SudokuGame> game = SudokuGameFactory::createNewGame(currentUser->getId(), difficulty);
    std::optional<std::unique_ptr<SudokuGame>> createdGame = gameRepository->createGame(currentUser->getId(), std::move(game));
    if (createdGame.has_value()) {
        printf("[SudokuGameManager] Created new sudoku game for user %d\n", currentUser->getId());
        flushPendingMoves();
        setCurrentGame(std::move(createdGame.value()));
        eventBus->publish(OnSudokuGameCreated());
    } else {
        printf("[SudokuGameManager] Failed to create new sudoku game for user %d\n", currentUser->getId());
    }
}

bool SudokuGameManager::createMove(const int selected_row, const int selected_col, const int value) {
    printf("[SudokuGameManager] Creating move (row: %d, col: %d, value: %d) in game with ID: %d\n",
           selected_row, selected_col, value, currentGame->getId());
    std::unique_ptr<SudokuMove> move = currentGame->createMove(selected_row, selected_col, value);
    const bool isValid = move->isValidMove();
    enqueueMove(std::move(move));
    printf("[SudokuGameManager] Move queued successfully\n");
    return isValid;
}

void SudokuGameManager::flushPendingMoves() {
    if (pendingMoves.empty()) {
        return;
    }
    printf("[SudokuGameManager] Flushing %zu pending moves...\n", pendingMoves.size());
    if (!moveRepository->createMoves(pendingMoves)) {
        printf("[SudokuGameManager] Failed to persist pending moves\n");
    }
    pendingMoves.clear();
}

void SudokuGameManager::enqueueMove(std::unique_ptr<SudokuMove> move) {
    pendingMoves.push_back(std::move(move));
    if (pendingMoves.size() >= MOVE_FLUSH_THRESHOLD || !pendingMoves.back()->isValidMove()) {
        flushPendingMoves();
    }
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
    float rating = (maxRating - (mistakes * mistakesMultiplier) - (elapsedTime * timeMultiplier)) * difficultyMultiplier;
    if (!mistakes) {
        constexpr int bonus = 200;
        rating += bonus;
    }

    return std::max(minRating, rating);
}

bool SudokuGameManager::isGridComplete() const {
    return getCurrentGame()->isSudokuSolved();
}

void SudokuGameManager::finishGame() {
    if (!currentGame) {
        printf("[SudokuGameManager] No active game to finish\n");
        return;
    }
    flushPendingMoves();
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

void SudokuGameManager::surrenderGame() {
    if (!currentGame) {
        printf("[SudokuGameManager] No active game to surrender\n");
        return;
    }
    flushPendingMoves();
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
) {
    if (!currentGame) {
        printf("[SudokuGameManager] No active game to update rating\n");
        return;
    }
    flushPendingMoves();
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
        flushPendingMoves();
        this->loadActiveGame();
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &) {
        flushPendingMoves();
        this->loadActiveGame();
    });
    eventBus->subscribe<OnUserLoggedOut>([this](const OnUserLoggedOut &) {
        flushPendingMoves();
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
        flushPendingMoves();
        this->clearCurrentGame();
    });
    eventBus->subscribe<OnSudokuGameFinished>([this](const OnSudokuGameFinished &) {
        flushPendingMoves();
        this->finishGame();
    });
    eventBus->subscribe<OnSudokuGameSurrendered>([this](const OnSudokuGameSurrendered &) {
        flushPendingMoves();
        this->surrenderGame();
    });
}
